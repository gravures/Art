/* -*- C++ -*-
 *
 *  This file is part of ART.
 *
 *  Copyright (c) 2020 Alberto Griggio <alberto.griggio@gmail.com>
 *
 *  ART is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ART is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ART.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <glib/gstdio.h>
#include <iostream>
#include <unistd.h>
#include <giomm.h>

#include <set>

#ifdef WIN32
#  include <windows.h>
#  include <io.h>
#  include <fcntl.h>
#else
#  include <sys/types.h>
#  include <sys/wait.h>
#endif

#include "subprocess.h"
#include "settings.h"


namespace rtengine {

extern const Settings *settings;

namespace subprocess {


std::wstring to_wstr(const Glib::ustring &s)
{
    auto *ws = g_utf8_to_utf16(s.c_str(), -1, nullptr, nullptr, nullptr);
    std::wstring ret(reinterpret_cast<wchar_t *>(ws));
    g_free(ws);
    return ret;
}


#ifdef WIN32

std::vector<Glib::ustring> split_command_line(const Glib::ustring &cmdl)
{
    std::wstring w = to_wstr(cmdl);
    int n;
    LPWSTR *a = CommandLineToArgvW(w.c_str(), &n);
    if (!a) {
        throw (error() << "impossible to split command line: " << cmdl);
    }
    
    std::vector<Glib::ustring> ret;
    for (int i = 0; i < n; ++i) {
        auto *s = g_utf16_to_utf8(reinterpret_cast<gunichar2 *>(a[i]), -1, nullptr, nullptr, nullptr);
        if (!s) {
            throw (error() << "impossible to split command line: " << cmdl);
        }
        ret.push_back(s);
        g_free(s);
    }
    LocalFree(a);

    return ret;
}


// Glib::spawn_sync opens a console window for command-line apps, I wasn't
// able to find out how not to do that (see also:
// http://gtk.10911.n7.nabble.com/g-spawn-on-windows-td84743.html).
// Therefore, we roll our own
void exec_sync(const Glib::ustring &workdir, const std::vector<Glib::ustring> &argv, bool search_in_path, std::string *out, std::string *err)
{
    const auto add_quoted =
        [](std::wostream &out, const std::wstring &ws) -> void
        {
            for (size_t j = 0; j < ws.size(); ) {
                int backslashes = 0;
                while (j < ws.size() && ws[j] == '\\') {
                    ++backslashes;
                    ++j;
                }
                if (j == ws.size()) {
                    backslashes = backslashes * 2;
                } else if (ws[j] == '"') {
                    backslashes = backslashes * 2 + 1;
                }
                for (int i = 0; i < backslashes; ++i) {
                    out << '\\';
                }
                if (j < ws.size()) {
                    if (isspace(ws[j])) {
                        out << '"' << ws[j] << '"';
                    } else {
                        out << ws[j];
                    }
                    ++j;
                } else {
                    break;
                }
            }
        };

    struct HandleCloser {
        ~HandleCloser()
        {
            for (auto h : toclose) {
                CloseHandle(h);
            }
        }
        std::set<HANDLE> toclose;
    };

    HANDLE fds_from[2];
    HANDLE fds_from_e[2];
    SECURITY_ATTRIBUTES sa;
    HandleCloser hc;

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    const auto mkpipe =
        [&](HANDLE *fd) -> bool
        {
            if (!CreatePipe(&(fd[0]), &(fd[1]), &sa, 0)) {
                return false;
            }
            hc.toclose.insert(fd[0]);
            hc.toclose.insert(fd[1]);
            if (!SetHandleInformation(fd[0], HANDLE_FLAG_INHERIT, 0)) {
                return false;
            }
            return true;
        };

    if (out || err) {
        if (!mkpipe(fds_from) || !mkpipe(fds_from_e)) {
            throw (error() << "mkpipe failed");
        }
    }

    PROCESS_INFORMATION pi;
    STARTUPINFOW si;

    ZeroMemory(&si, sizeof(STARTUPINFOW));
    si.cb = sizeof(STARTUPINFOW);
    si.wShowWindow = SW_HIDE;
    if (out || err) {
        si.dwFlags = STARTF_USESTDHANDLES;
        si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
        si.hStdOutput = fds_from[1];
        si.hStdError = fds_from_e[1];
    }

    std::wstring pth = to_wstr(argv[0]);
    if (search_in_path && Glib::path_get_basename(argv[0]) == argv[0]) {
        wchar_t pathbuf[MAX_PATH+1];
        int n = SearchPathW(nullptr, pth.c_str(), nullptr, MAX_PATH+1, pathbuf, nullptr);
        if (n > 0) {
            pth = pathbuf;
        }
    }

    wchar_t *cmdline = nullptr;
    {
        std::wostringstream cmdlinebuf;
        add_quoted(cmdlinebuf, pth);
        for (size_t i = 1; i < argv.size(); ++i) {
            cmdlinebuf << ' ';
            add_quoted(cmdlinebuf, to_wstr(argv[i]));
        }
        std::wstring s = cmdlinebuf.str();
        cmdline = new wchar_t[s.size()+1];
        memcpy(cmdline, s.c_str(), s.size() * sizeof(wchar_t));
        cmdline[s.size()] = 0;
    }

    std::wstring wd = to_wstr(workdir);
    if (!CreateProcessW(pth.c_str(), cmdline, nullptr, nullptr, TRUE,
                        CREATE_NO_WINDOW,
                        (LPVOID)nullptr, wd.empty() ? nullptr : wd.c_str(),
                        &si, &pi)) {
        delete[] cmdline;
        throw (error() << "impossible to create process");
    } else {
        hc.toclose.insert(pi.hProcess);
        hc.toclose.insert(pi.hThread);
    }
    delete[] cmdline;

    const auto read_pipe =
        [&](HANDLE *fd) -> std::string
        {
            constexpr size_t bufsize = 4096;
            unsigned char buf[bufsize];
            std::ostringstream sbuf;
            DWORD n;

            hc.toclose.erase(fd[1]);
            CloseHandle(fd[1]);

            while (ReadFile(fd[0], buf, bufsize, &n, nullptr)) {
                buf[n] = 0;
                sbuf << buf;
                if (n < bufsize) {
                    break;
                }
            }
            return sbuf.str();
        };

    if (out || err) {
        std::string o = read_pipe(fds_from);
        if (out) {
            *out = std::move(o);
        }
        std::string e = read_pipe(fds_from_e);
        if (err) {
            *err = std::move(e);
        }
    }

    unsigned int status = 255;
    const DWORD wait_timeout_ms = INFINITE;
    if (WaitForSingleObject(pi.hProcess, wait_timeout_ms) != WAIT_OBJECT_0) {
        TerminateProcess(pi.hProcess, status);
    }
    if (!GetExitCodeProcess(pi.hProcess, (LPDWORD)&status)) {
        status = 255;
    }

    if (status != 0) {
        throw (error() << "exit status: " << status);
    }
}


#else // WIN32


std::vector<Glib::ustring> split_command_line(const Glib::ustring &cmdl)
{
    try {
        auto argv = Glib::shell_parse_argv(cmdl);
        std::vector<Glib::ustring> ret;
        for (const auto &a : argv) {
            ret.push_back(Glib::filename_to_utf8(a));
        }
        return ret;
    } catch (Glib::Error &e) {
        throw (error() << e.what());
    }
}


void exec_sync(const Glib::ustring &workdir, const std::vector<Glib::ustring> &argv, bool search_in_path, std::string *out, std::string *err)
{
    std::vector<std::string> args;
    args.reserve(argv.size());
    for (auto &s : argv) {
        args.push_back(Glib::filename_from_utf8(s));
    }
    try {
        int exit_status = -1;
        auto flags = Glib::SPAWN_DEFAULT;
        if (search_in_path) {
            flags |= Glib::SPAWN_SEARCH_PATH;
        }
        std::string wd = Glib::filename_from_utf8(workdir);
        Glib::spawn_sync(wd, args, flags, Glib::SlotSpawnChildSetup(), out, err, &exit_status);
        if (!(WIFEXITED(exit_status) && WEXITSTATUS(exit_status) == 0)) {
            throw (error() << "exit status: " << exit_status);
        }
    } catch (Glib::Exception &e) {
        throw (error() << e.what());
    }
}

#endif // WIN32


}} // namespace rtengine::subprocess
