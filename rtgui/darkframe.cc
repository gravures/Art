/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2004-2010 Gabor Horvath <hgabor@rawtherapee.com>
 *
 *  RawTherapee is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  RawTherapee is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RawTherapee.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "darkframe.h"
#include "options.h"
#include "guiutils.h"
#include <sstream>
#include "rtimage.h"
#include "../rtengine/refreshmap.h"

using namespace rtengine;
using namespace rtengine::procparams;

DarkFrame::DarkFrame () :
    FoldableToolPanel(this, "darkframe", M("TP_DARKFRAME_LABEL"), false, true, true),
    dfChanged(false), lastDFauto(false), dfp(nullptr), israw(true)
{
    EvToolEnabled.set_action(DARKFRAME);
    EvToolReset.set_action(DARKFRAME);
    
    hbdf = Gtk::manage(new Gtk::HBox());
    hbdf->set_spacing(4);
    darkFrameFile = Gtk::manage(new MyFileChooserButton(M("TP_DARKFRAME_LABEL"), Gtk::FILE_CHOOSER_ACTION_OPEN));
    bindCurrentFolder (*darkFrameFile, options.lastDarkframeDir);
    dfLabel = Gtk::manage(new Gtk::Label(M("GENERAL_FILE")));
    btnReset = Gtk::manage(new Gtk::Button());
    btnReset->set_image (*Gtk::manage(new RTImage ("cancel-small.png")));
    hbdf->pack_start(*dfLabel, Gtk::PACK_SHRINK, 0);
    hbdf->pack_start(*darkFrameFile);
    hbdf->pack_start(*btnReset, Gtk::PACK_SHRINK, 0);
    dfAuto = Gtk::manage(new Gtk::CheckButton((M("TP_DARKFRAME_AUTOSELECT"))));
    dfInfo = Gtk::manage(new Gtk::Label(""));
    dfInfo->set_alignment(0, 0); //left align

    pack_start( *hbdf, Gtk::PACK_SHRINK, 0);
    pack_start( *dfAuto, Gtk::PACK_SHRINK, 0);
    pack_start( *dfInfo, Gtk::PACK_SHRINK, 0);

    dfautoconn = dfAuto->signal_toggled().connect ( sigc::mem_fun(*this, &DarkFrame::dfAutoChanged), true);
    dfFile = darkFrameFile->signal_file_set().connect ( sigc::mem_fun(*this, &DarkFrame::darkFrameChanged)); //, true);
    btnReset->signal_clicked().connect( sigc::mem_fun(*this, &DarkFrame::darkFrameReset), true );

    // Set filename filters
    b_filter_asCurrent = false;
    Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
    filter_any->add_pattern("*");
    filter_any->set_name(M("FILECHOOSER_FILTER_ANY"));
    darkFrameFile->add_filter (filter_any);

    // filters for all supported non-raw extensions
    for (size_t i = 0; i < options.parseExtensions.size(); i++) {
        if (options.parseExtensionsEnabled[i] && options.parseExtensions[i].uppercase() != "JPG" && options.parseExtensions[i].uppercase() != "JPEG" && options.parseExtensions[i].uppercase() != "PNG" && options.parseExtensions[i].uppercase() != "TIF" && options.parseExtensions[i].uppercase() != "TIFF"  ) {
            Glib::RefPtr<Gtk::FileFilter> filter_df = Gtk::FileFilter::create();
            filter_df->add_pattern("*." + options.parseExtensions[i]);
            filter_df->add_pattern("*." + options.parseExtensions[i].uppercase());
            filter_df->set_name(options.parseExtensions[i].uppercase());
            darkFrameFile->add_filter (filter_df);
            //printf("adding filter %s \n",options.parseExtensions[i].uppercase().c_str());
        }
    }
}

void DarkFrame::read(const rtengine::procparams::ProcParams* pp)
{
    disableListener ();
    dfautoconn.block(true);

    setEnabled(pp->raw.enable_darkframe);

    dfAuto->set_active( pp->raw.df_autoselect );

    if (Glib::file_test (pp->raw.dark_frame, Glib::FILE_TEST_EXISTS)) {
        darkFrameFile->set_filename (pp->raw.dark_frame);
    } else {
        darkFrameReset();
    }

    hbdf->set_sensitive( !pp->raw.df_autoselect );

    lastDFauto = pp->raw.df_autoselect;

    if( pp->raw.df_autoselect  && dfp) {
        // retrieve the auto-selected df filename
        rtengine::RawImage *img = dfp->getDF();

        if( img ) {
            dfInfo->set_text( Glib::ustring::compose("%1: %2ISO %3s", Glib::path_get_basename(img->get_filename()), img->get_ISOspeed(), img->get_shutter()) );
        } else {
            dfInfo->set_text(Glib::ustring(M("TP_PREPROCESS_NO_FOUND")));
        }
    } else {
        dfInfo->set_text("");
    }

    dfChanged = false;

    dfautoconn.block(false);
    enableListener ();

    // Add filter with the current file extension if the current file is raw
    if (dfp) {

        if (b_filter_asCurrent) {
            //First, remove last filter_asCurrent if it was set for a raw file
            std::vector< Glib::RefPtr<Gtk::FileFilter> > filters = darkFrameFile->list_filters();
            darkFrameFile->remove_filter(*(filters.end() - 1));
            b_filter_asCurrent = false;
        }

        Glib::ustring fname = Glib::path_get_basename(dfp->GetCurrentImageFilePath());
        Glib::ustring filetype;

        if (fname != "") {
            // get image filetype, set filter to the same as current image's filetype
            std::string::size_type idx;
            idx = fname.rfind('.');

            if(idx != std::string::npos) {
                filetype = fname.substr(idx + 1);
                israw = filetype.uppercase() != "JPG" && filetype.uppercase() != "JPEG" && filetype.uppercase() != "PNG" && filetype.uppercase() != "TIF" && filetype.uppercase() != "TIFF";

                //exclude non-raw
                if (israw) {
                    b_filter_asCurrent = true;
                    Glib::RefPtr<Gtk::FileFilter> filter_asCurrent = Gtk::FileFilter::create();
                    filter_asCurrent->add_pattern("*." + filetype);
                    filter_asCurrent->set_name(M("FILECHOOSER_FILTER_SAME") + " (" + filetype + ")");
                    darkFrameFile->add_filter (filter_asCurrent);
                    darkFrameFile->set_filter (filter_asCurrent);
                }
            }
        }
    }

}

void DarkFrame::write( rtengine::procparams::ProcParams* pp)
{
    pp->raw.enable_darkframe = getEnabled();
    pp->raw.dark_frame = darkFrameFile->get_filename();
    if (!Glib::file_test(pp->raw.dark_frame, Glib::FILE_TEST_EXISTS)) {
        pp->raw.dark_frame = "";
    }
    pp->raw.df_autoselect = dfAuto->get_active();
}

void DarkFrame::dfAutoChanged()
{
    if(dfAuto->get_active() && dfp) {
        // retrieve the auto-selected df filename
        rtengine::RawImage *img = dfp->getDF();

        if( img ) {
            dfInfo->set_text( Glib::ustring::compose("%1: %2ISO %3s", Glib::path_get_basename(img->get_filename()), img->get_ISOspeed(), img->get_shutter()) );
        } else {
            dfInfo->set_text(Glib::ustring(M("TP_PREPROCESS_NO_FOUND")));
        }
    } else {
        dfInfo->set_text("");
    }

    hbdf->set_sensitive( !dfAuto->get_active() );

    if (listener && getEnabled()) {
        listener->panelChanged (EvPreProcessAutoDF, dfAuto->get_active() ? M("GENERAL_ENABLED") : M("GENERAL_DISABLED"));
    }
}

void DarkFrame::darkFrameChanged()
{
    dfChanged = true;

    if (listener && getEnabled()) {
        listener->panelChanged (EvPreProcessDFFile, Glib::path_get_basename(darkFrameFile->get_filename()));
    }
}

void DarkFrame::darkFrameReset()
{
    dfChanged = true;

// caution: I had to make this hack, because set_current_folder() doesn't work correctly!
//          Because szeva doesn't exist since he was committed to happy hunting ground in Issue 316
//          we can use him now for this hack
    darkFrameFile->set_filename (options.lastDarkframeDir + "/szeva");
// end of the hack

    if (!options.lastDarkframeDir.empty()) {
        darkFrameFile->set_current_folder(options.lastDarkframeDir);
    }

    dfInfo->set_text("");

    if (listener && getEnabled()) {
        listener->panelChanged (EvPreProcessDFFile, M("GENERAL_NONE"));
    }

}


void DarkFrame::setDefaults(const ProcParams *def)
{
    initial_params = def->raw;
}


void DarkFrame::toolReset(bool to_initial)
{
    ProcParams pp;
    if (to_initial) {
        pp.raw = initial_params;
    }
    pp.raw.enable_darkframe = getEnabled();
    read(&pp);
}
