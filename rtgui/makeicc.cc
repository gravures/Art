/* -*- C++ -*-
 *
 *  This file is part of ART.
 *
 *  Copyright 2022 Alberto Griggio <alberto.griggio@gmail.com>
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

#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>
#include <vector>
#include <lcms2.h>
#include "../rtengine/color.h"

namespace {

struct Options {
    std::pair<float, float> whitepoint;
    float gamma;
    float slope;
    std::string desc;
    std::array<float, 6> primaries;
    std::string output;
    bool v2;
    Options() = default;
};


bool getopts(std::ostream &sout, const std::vector<std::string> &args, Options &out)
{
    int argc = args.size();
    auto &argv = args;
    
    const auto getstr =
        [&](int i, std::string &out) -> bool
        {
            if (i < argc) {
                std::istringstream tmp(argv[i]);
                if (!(tmp >> out)) {
                    return false;
                } else {
                    for (auto &c : out) {
                        c = std::tolower(c);
                    }
                    return true;
                }
            } else {
                return false;
            }
        };

    const auto getflt =
        [&](int i, float &out) -> bool
        {
            if (i < argc) {
                std::istringstream tmp(argv[i]);
                if (!(tmp >> out)) {
                    return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        };
    
    out = Options();
    out.gamma = 1;
    out.slope = 0;
    
    std::string err;
    for (int i = 0; err.empty() && i < argc; ++i) {
        std::string a = argv[i];
        if (a == "-v2") {
            out.v2 = true;
        } else if (a == "-w") {
            if (!getflt(i+1, out.whitepoint.first) ||
                !getflt(i+2, out.whitepoint.second)) {
                err = "Invalid whitepoint (-w)";
            } else {
                i += 2;
            }
        } else if (a == "-i") {
            std::string val;
            if (!getstr(i+1, val)) {
                err = "Invalid illuminant (-i)";
            } else {
                ++i;
                if (val == "d50") {
                    out.whitepoint = {0.3457, 0.3585};
                } else if (val == "d60") {
                    out.whitepoint = {0.32168, 0.33767};
                } else if (val == "d65") {
                    out.whitepoint = {0.312700492, 0.329000939};
                } else {
                    err = "Invalid illuminant (-i)";
                }
            }
        } else if (a == "-t") {
            std::string val;
            if (!getstr(i+1, val)) {
                err = "Invalid TRC (-t)";
            } else {
                ++i;
                if (val == "linear") {
                    out.gamma = 1;
                    out.slope = 0;
                } else if (val == "srgb") {
                    out.gamma = 2.4;
                    out.slope = 12.9231;
                } else if (val == "hlg") {
                    out.gamma = -1;
                    out.slope = 0;
                } else if (val == "pq") {
                    out.gamma = -2;
                    out.slope = 0;
                } else {
                    err = "Invalid TRC (-t)";
                }
            }
        } else if (a == "-c") {
            for (int j = 1; j <= 6; ++j) {
                if (!getflt(i+j, out.primaries[j-1])) {
                    err = "Invalid primaries coordinates (-c)";
                    break;
                }
            }
            if (err.empty()) {
                i += 6;
            }
        } else if (a == "-p") {
            std::string val;
            if (!getstr(i+1, val)) {
                err = "Invalid primaries preset (-p)";
            } else {
                ++i;
                if (val == "srgb") {
                    out.primaries = {
                        0.64, 0.33,
                        0.3, 0.6,
                        0.15, 0.06
                    };
                } else if (val == "adobergb") {
                    out.primaries = {
                        0.64, 0.33,
                        0.21, 0.71,
                        0.15, 0.06
                    };
                } else if (val == "prophoto") {
                    out.primaries = {
                        0.7347, 0.2653,
                        0.1596, 0.8404,
                        0.0366, 0.0001
                    };
                } else if (val == "rec2020") {
                    out.primaries = {
                        0.708, 0.292,
                        0.17, 0.797,
                        0.131, 0.046
                    };
                } else if (val == "acesp0") {
                    out.primaries = {
                        0.7347, 0.2653,
                        0, 1,
                        0.0001, -0.0770
                    };
                } else if (val == "acesp1") {
                    out.primaries = {
                        0.713, 0.293,
                        0.165, 0.83,
                        0.128, 0.044
                    };
                } else {
                    err = "Invalid primaries preset (-p)";
                }
            }
        } else if (a == "-g") {
            if (!getflt(i+1, out.gamma) || out.gamma <= 0) {
                err = "Invalid gamma (-g)";
            } else {
                ++i;
            }
        } else if (a == "-s") {
            if (!getflt(i+1, out.slope) || out.slope < 0) {
                err = "Invalid slope (-s)";
            } else {
                ++i;
            }
        } else if (a == "-d") {
            if (i+1 < argc) {
                out.desc = argv[i+1];
                ++i;
            } else {
                err = "Invalid description (-d)";
            }
        } else if (a == "-o") {
            if (i+1 < argc) {
                out.output = argv[i+1];
                ++i;
            } else {
                err = "Invalid output (-o)";
            }
        } else {
            err = "unknown option " + a;
        }
    }
    if (out.output.empty()) {
        err = "missing output name";
    }
    if (out.desc.empty()) {
        err = "missing profile description";
    }
    if (!err.empty()) {
        sout << "ERROR: " << err << std::endl;
        return false;
    } else {
        return true;
    }
}


//-----------------------------------------------------------------------------
// adapted from darktable (src/common/colorspaces.c)
/*
    This file is part of darktable,
    Copyright (C) 2010-2022 darktable developers.

    darktable is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    darktable is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with darktable.  If not, see <http://www.gnu.org/licenses/>.
*/

cmsHPROFILE create_profile(bool v2, const std::pair<float, float> &whitept, const std::array<float, 6> &primaries, cmsToneCurve *trc, const std::string &desc, float gamma, float slope)
{
    cmsMLU *mlu1 = cmsMLUalloc(NULL, 1);
    cmsMLU *mlu2 = cmsMLUalloc(NULL, 1);
    cmsMLU *mlu3 = cmsMLUalloc(NULL, 1);
    cmsMLU *mlu4 = cmsMLUalloc(NULL, 1);

    cmsToneCurve *out_curves[3] = { trc, trc, trc };
    cmsCIExyY whitepoint = { whitept.first, whitept.second, 1.0 };
    cmsCIExyYTRIPLE prim = {
        {primaries[0], primaries[1], 1.0},
        {primaries[2], primaries[3], 1.0},
        {primaries[4], primaries[5], 1.0},
    };
    
    cmsHPROFILE profile = cmsCreateRGBProfile(&whitepoint, &prim, out_curves);
    //cmsSetDeviceClass(profile, cmsSigOutputClass);

    if (v2) {
        cmsSetProfileVersion(profile, 2.4);
    }

    cmsSetHeaderFlags(profile, cmsEmbeddedProfileTrue);

    cmsMLUsetASCII(mlu1, "en", "US", "Public Domain");
    cmsWriteTag(profile, cmsSigCopyrightTag, mlu1);

    if (v2 && gamma > 0) {
        std::ostringstream buf;
        buf << "g" << std::setw(6) << std::fixed << std::setprecision(6) << gamma << "s" << std::setw(6) << std::fixed << std::setprecision(5) << slope << "!";
        auto s = buf.str();
        cmsMLUsetASCII(mlu2, "en", "US", s.c_str());
        cmsWriteTag(profile, cmsSigDeviceModelDescTag, mlu2);
    }

    cmsMLUsetASCII(mlu3, "en", "US", desc.c_str());
    cmsWriteTag(profile, cmsSigProfileDescriptionTag, mlu3);

    cmsMLUsetASCII(mlu4, "en", "US", "ART");
    cmsWriteTag(profile, cmsSigDeviceMfgDescTag, mlu4);

    cmsMLUfree(mlu1);
    cmsMLUfree(mlu2);
    cmsMLUfree(mlu3);
    cmsMLUfree(mlu4);

    return profile;
}


// https://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.2100-2-201807-I!!PDF-F.pdf
// Perceptual Quantization / SMPTE standard ST.2084
float PQ(float x)
{
    constexpr float M1 = 2610.0 / 16384.0;
    constexpr float M2 = (2523.0 / 4096.0) * 128.0;
    constexpr float C1 = 3424.0 / 4096.0;
    constexpr float C2 = (2413.0 / 4096.0) * 32.0;
    constexpr float C3 = (2392.0 / 4096.0) * 32.0;

    if (x == 0.0) {
        return 0.0;
    }

    float xpo = std::pow(x, 1.f / M2);
    float num = std::max(xpo - C1, 0.f);
    float den = C2 - C3 * xpo;
    float res = std::pow(num / den, 1.f / M1);

    return res;
}

// https://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.2100-2-201807-I!!PDF-F.pdf
// Hybrid Log-Gamma
float HLG(float x)
{
    constexpr float Beta  = 0.04;
    constexpr float RA    = 5.591816309728916; // 1.0 / A where A = 0.17883277
    constexpr float B     = 0.28466892; // 1.0 - 4.0 * A
    constexpr float C     = 0.5599107295; // 0,5 –aln(4a)

    float e = std::max(x * (1.f - Beta) + Beta, 0.f);

    if (e == 0.0) {
        return 0.0;
    }

    float res = 0.0;

    if (e <= 0.5) {
        res = e * e / 3.0;
    } else {
        res = (std::exp((e - C) * RA) + B) / 12.0;
    }

    return res;
}

cmsToneCurve *make_trc(size_t size, float (*trcFunc)(float))
{
    std::vector<float> values(size);

    for (size_t i = 0; i < size; ++i) {
        float x = float(i) / (size - 1);
        float y = std::min(trcFunc(x), 1.0f);
        values[i] = y;
    }

    cmsToneCurve *result = cmsBuildTabulatedToneCurveFloat(NULL, size, &values[0]);
    return result;
}

//-----------------------------------------------------------------------------


cmsToneCurve *make_trc(float gamma, float slope)
{
    if (slope == 0.f) {
        return cmsBuildGamma(NULL, gamma);
    } else {
        constexpr double eps = 0.000000001; // not divide by zero
        double pwr = 1.0 / gamma;
        double ts = slope;
        double slope2 = slope == 0 ? eps : slope;

        rtengine::GammaValues out;
        rtengine::Color::calcGamma(pwr, ts, out);

        double params[5];
        params[0] = gamma;
        params[1] = 1. / (1.0 + out[4]);
        params[2] = out[4] / (1.0 + out[4]);
        params[3] = 1. / slope2;
        params[4] = out[3] * ts;

        return cmsBuildParametricToneCurve(NULL, 5, params);
    }
}

} // namespace

int ART_makeicc_main(std::ostream &out, const std::vector<std::string> &args)
{
    Options opts;
    if (!getopts(out, args, opts)) {
        return 1;
    }

    cmsToneCurve *trc = nullptr;
    if (opts.gamma == -2) {
        trc = make_trc(4096, PQ);
    } else if (opts.gamma == -1) {
        trc = make_trc(4096, HLG);
    } else {
        trc = make_trc(opts.gamma, opts.slope);
    }

    cmsHPROFILE prof = create_profile(opts.v2, opts.whitepoint, opts.primaries, trc, opts.desc, opts.gamma, opts.slope);

    if (trc) {
        cmsFreeToneCurve(trc);
    }
        
    if (prof) {
        cmsSaveProfileToFile(prof, opts.output.c_str());
    } else {
        out << "ERROR: impossible to create profile" << std::endl;
        return 1;
    }

    return 0;
}


void ART_makeicc_help(std::ostream &out, int indent)
{
    std::string pad(indent, ' ');
    out << pad << " -w x y : white point coordinates\n"
        << pad << " -i VAL : illuminant. Possible values (case insensitive):\n"
        << pad << "          - D50\n"
        << pad << "          - D60\n"
        << pad << "          - D65\n"
        << pad << " -t VAL : TRC to use. Possible values (case insensitive):\n"
        << pad << "          - linear (default)\n"
        << pad << "          - sRGB\n"
        << pad << "          - HLG\n"
        << pad << "          - PQ\n"
        << pad << " -c Rx Ry Gx Gy Bx By : xy coordinates of primaries\n"
        << pad << " -p VAL : primaries preset. Possible values (case insensitive):\n"
        << pad << "          - sRGB\n"
        << pad << "          - AdobeRGB\n"
        << pad << "          - ProPhoto\n"
        << pad << "          - Rec2020\n"
        << pad << "          - ACESP0\n"
        << pad << "          - ACESP1\n"
        << pad << " -g VAL : TRC gamma (overrides -t)\n"
        << pad << " -s VAL : TRC slope (overrides -t)\n"
        << pad << " -d VAL : profile description (mandatory)\n"
        << pad << " -v2 : generate a V2 profile\n"
        << pad << " -o NAME : output file name (mandatory)" << std::endl;
}
