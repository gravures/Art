#include <map>
#include <set>

#include "filmsimulation.h"

#include <chrono>

#include "options.h"
#include "../rtengine/clutstore.h"
#include "eventmapper.h"

using namespace rtengine;
using namespace rtengine::procparams;

namespace
{

Glib::ustring stripPrefixDir(const Glib::ustring& filename, const Glib::ustring& dir)
{
    const Glib::ustring full_dir =
        !Glib::str_has_suffix(dir, G_DIR_SEPARATOR_S)
            ? dir + G_DIR_SEPARATOR_S
            : dir;
    return
        Glib::str_has_prefix(filename, full_dir)
            ? filename.substr(full_dir.size())
            : filename;
}

bool notifySlowParseDir (const std::chrono::system_clock::time_point& startedAt)
{
    enum Decision {
        UNDECIDED,
        CANCEL,
        CONTINUE
    };

    static Decision decision = UNDECIDED;

    if (decision == CANCEL) {
        return false;
    } else if (decision == CONTINUE) {
        return true;
    }

    const auto now = std::chrono::system_clock::now();
    if (now - startedAt < std::chrono::seconds(10)) {
        return true;
    }

    Gtk::MessageDialog dialog(M("TP_FILMSIMULATION_SLOWPARSEDIR"), false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO, true);
    if (dialog.run() == Gtk::RESPONSE_YES) {
        decision = CANCEL;
        return false;
    } else {
        decision = CONTINUE;
        return true;
    }
}

}

FilmSimulation::FilmSimulation():
    FoldableToolPanel(this, "filmsimulation", M("TP_FILMSIMULATION_LABEL"), false, true, true)
{
    EvToolEnabled.set_action(RGBCURVE);
    
    m_clutComboBox = Gtk::manage( new ClutComboBox(options.clutsDir) );
    int foundClutsCount = m_clutComboBox->foundClutsCount();

    if ( foundClutsCount == 0 ) {
        pack_start( *Gtk::manage( new Gtk::Label( M("TP_FILMSIMULATION_ZEROCLUTSFOUND") ) ) );
    }

    m_clutComboBoxConn = m_clutComboBox->signal_changed().connect( sigc::mem_fun( *this, &FilmSimulation::onClutSelected ) );
    pack_start( *m_clutComboBox );

    m_strength = Gtk::manage( new Adjuster( M("TP_FILMSIMULATION_STRENGTH"), 0., 100, 1., 100 ) );
    m_strength->setAdjusterListener( this );

    pack_start( *m_strength, Gtk::PACK_SHRINK, 0 );

}

void FilmSimulation::onClutSelected()
{
    Glib::ustring currentClutFilename = m_clutComboBox->getSelectedClut();

    if ( getEnabled() && !currentClutFilename.empty() && listener && currentClutFilename != m_oldClutFilename ) {
        Glib::ustring clutName, dummy;
        HaldCLUT::splitClutFilename( currentClutFilename, clutName, dummy, dummy );
        listener->panelChanged( EvFilmSimulationFilename, clutName );

        m_oldClutFilename = currentClutFilename;
    }
}

void FilmSimulation::enabledChanged ()
{

    if (listener) {
        if (get_inconsistent()) {
            listener->panelChanged (EvFilmSimulationEnabled, M("GENERAL_UNCHANGED"));
        } else if (getEnabled()) {
            listener->panelChanged (EvFilmSimulationEnabled, M("GENERAL_ENABLED"));
        } else {
            listener->panelChanged (EvFilmSimulationEnabled, M("GENERAL_DISABLED"));
        }
    }
}

void FilmSimulation::adjusterChanged(Adjuster* a, double newval)
{
    if (listener && getEnabled()) {
        const Glib::ustring value = a->getTextValue();
        listener->panelChanged(EvFilmSimulationStrength, value);
    }
}

void FilmSimulation::adjusterAutoToggled(Adjuster* a, bool newval)
{
}

void FilmSimulation::read( const rtengine::procparams::ProcParams* pp)
{
    //copypasted from lensprofile.cc & sharpening.cc
    disableListener();
    updateDisable(true);

    setEnabled(pp->filmSimulation.enabled);

    if (!pp->filmSimulation.clutFilename.empty()) {
        m_clutComboBox->setSelectedClut(
            !Glib::path_is_absolute(pp->filmSimulation.clutFilename)
                ? Glib::ustring(Glib::build_filename(options.clutsDir, pp->filmSimulation.clutFilename))
                : pp->filmSimulation.clutFilename
        );
        m_oldClutFilename = m_clutComboBox->getSelectedClut();
    } else {
        m_clutComboBox->set_active(-1);
    }

    m_strength->setValue(pp->filmSimulation.strength);

    if (!get_inconsistent() && !pp->filmSimulation.enabled) {
        if (options.clutCacheSize == 1) {
            CLUTStore::getInstance().clearCache();
        }
    }

    updateDisable(false);
    enableListener();
}

void FilmSimulation::updateDisable( bool value )
{
    m_clutComboBoxConn.block( value );
}

void FilmSimulation::write( rtengine::procparams::ProcParams* pp)
{
    pp->filmSimulation.enabled = getEnabled();
    const Glib::ustring clutFName = m_clutComboBox->getSelectedClut();

    if (clutFName != "NULL") { // We do not want to set "NULL" in clutFilename, even if "unedited"
        pp->filmSimulation.clutFilename = stripPrefixDir(clutFName, options.clutsDir);
    }

    pp->filmSimulation.strength = m_strength->getValue();
}

void FilmSimulation::trimValues( rtengine::procparams::ProcParams* pp )
{
    m_strength->trimValue( pp->filmSimulation.strength );
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


std::unique_ptr<ClutComboBox::ClutModel> ClutComboBox::cm;
std::unique_ptr<ClutComboBox::ClutModel> ClutComboBox::cm2;

ClutComboBox::ClutComboBox(const Glib::ustring &path):
    MyComboBox()
{
    if (!cm) {
        cm.reset(new ClutModel(path));
    }
    if (!cm2 && options.multiDisplayMode) {
        cm2.reset(new ClutModel(path));
    }

    set_model(m_model());

    if (cm->count > 0) {
        pack_start(m_columns().label, false);
    }

    if (!options.multiDisplayMode) {
        signal_map().connect(sigc::mem_fun(*this, &ClutComboBox::updateUnchangedEntry));
    }
}


inline Glib::RefPtr<Gtk::TreeStore> &ClutComboBox::m_model()
{
    if (!options.multiDisplayMode) {
        return cm->m_model;
    } else {
        return cm2->m_model;
    }
}


inline ClutComboBox::ClutColumns &ClutComboBox::m_columns()
{
    if (!options.multiDisplayMode) {
        return cm->m_columns;
    } else {
        return cm2->m_columns;
    }
}


void ClutComboBox::cleanup()
{
    cm.reset();
    cm2.reset();
}


void ClutComboBox::updateUnchangedEntry()
{
    auto c = m_model()->children();

    if (c.size() > 0) {
        Gtk::TreeModel::Row row = c[c.size()-1];
        if (row[m_columns().clutFilename] == "NULL") {
            m_model()->erase(row);
        }
    }
}

ClutComboBox::ClutColumns::ClutColumns()
{
    add( label );
    add( clutFilename );
}

ClutComboBox::ClutModel::ClutModel(const Glib::ustring &path)
{
    m_model = Gtk::TreeStore::create (m_columns);
    //set_model (m_model);
    count = parseDir(path);
}

int ClutComboBox::ClutModel::parseDir(const Glib::ustring& path)
{
    if (path.empty() || !Glib::file_test(path, Glib::FILE_TEST_IS_DIR)) {
        return 0;
    }

    const auto sorted_dir_dirs = [](const Glib::ustring& path) -> std::map<std::string, std::string>
        {
            std::map<std::string, std::string> res;

            for (const auto& dir : Glib::Dir(path)) {
                const std::string full_path = Glib::build_filename(path, dir);

                if (Glib::file_test(full_path, Glib::FILE_TEST_IS_DIR)) {
                    res.emplace(dir, full_path);
                }
            }

            return res;
        };

    const auto startedAt = std::chrono::system_clock::now();

    // Build menu of limited directory structure using breadth-first search
    using Dirs = std::vector<std::pair<Glib::ustring, Gtk::TreeModel::Row>>;
    Dirs dirs;

    {
        Dirs currDirs;
        Dirs nextDirs;

        currDirs.emplace_back(path, Gtk::TreeModel::Row());

        while (!currDirs.empty()) {
            for (auto& dir : currDirs) {
                const auto& path = dir.first;
                const auto& row = dir.second;

                try {
                    for (const auto& entry : sorted_dir_dirs(path)) {
                        auto newRow = row ? *m_model->append(row.children()) : *m_model->append();
                        newRow[m_columns.label] = entry.first;

                        nextDirs.emplace_back(entry.second, newRow);
                    }
                } catch (Glib::Exception&) {}

                dirs.push_back(std::move(dir));

                if (!notifySlowParseDir(startedAt)) {
                    m_model->clear();
                    return 0;
                }
            }

            currDirs.clear();
            currDirs.swap(nextDirs);
        }
    }

    // Fill menu structure with CLUT files
    std::set<Glib::ustring> entries;

    unsigned long fileCount = 0;

    for (const auto& dir : dirs) {
        const auto& path = dir.first;
        const auto& row = dir.second;

        entries.clear();

        try {
            for (const auto& entry : Glib::Dir(path)) {
                const auto entryPath = Glib::build_filename(path, entry);

                if (!Glib::file_test(entryPath, Glib::FILE_TEST_IS_REGULAR)) {
                    continue;
                }

                entries.insert(entryPath);
            }
        } catch (Glib::Exception&) {}

        for (const auto& entry : entries) {
            Glib::ustring name;
            Glib::ustring extension;
            Glib::ustring profileName;
            HaldCLUT::splitClutFilename (entry, name, extension, profileName);

            extension = extension.casefold();
            if (extension.compare("tif") != 0 && extension.compare("png") != 0) {
                continue;
            }

            auto newRow = row ? *m_model->append(row.children()) : *m_model->append();
            newRow[m_columns.label] = name;
            newRow[m_columns.clutFilename] = entry;

            ++fileCount;

            if (!notifySlowParseDir(startedAt)) {
                m_model->clear();
                return 0;
            }
        }
    }

    return fileCount;
}

int ClutComboBox::foundClutsCount() const
{
    return cm->count;
}

Glib::ustring ClutComboBox::getSelectedClut()
{
    Glib::ustring result;
    Gtk::TreeModel::iterator current = get_active();
    Gtk::TreeModel::Row row = *current;

    if ( row ) {
        result = row[ m_columns().clutFilename ];
    }

    return result;
}

void ClutComboBox::setSelectedClut( Glib::ustring filename )
{
    if ( !filename.empty() ) {
        Gtk::TreeIter found = findRowByClutFilename( m_model()->children(), filename );

        if ( found ) {
            set_active( found );
        } else {
            set_active(-1);
        }
    }
}

Gtk::TreeIter ClutComboBox::findRowByClutFilename( Gtk::TreeModel::Children childs, Glib::ustring filename )
{
    Gtk::TreeIter result = childs.end();

    for( Gtk::TreeModel::Children::iterator it = childs.begin(); !result && it != childs.end(); ++it ) {
        Gtk::TreeModel::Row row = *it;

        if ( row[ m_columns().clutFilename ] == filename ) {
            result = it;
        } else {
            result = findRowByClutFilename( it->children(), filename );
        }
    }

    return result;
}


void FilmSimulation::setDefaults(const ProcParams *defParams)
{
    initial_params = defParams->filmSimulation;
}


void FilmSimulation::toolReset(bool to_initial)
{
    ProcParams pp;
    if (to_initial) {
        pp.filmSimulation = initial_params;
    }
    pp.filmSimulation.enabled = getEnabled();
    read(&pp);
}
