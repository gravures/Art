/* -*- C++ -*-
 *  
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
#ifndef _PROFILEPANEL_
#define _PROFILEPANEL_

#include <gtkmm.h>
#include <vector>
#include "../rtengine/rtengine.h"
#include "pparamschangelistener.h"
#include "profilechangelistener.h"
#include "partialpastedlg.h"
#include "guiutils.h"
#include "profilestorecombobox.h"
#include "rtimage.h"

class ProfilePanel : public Gtk::Grid, public PParamsChangeListener, public ProfileStoreListener
{

private:

    rtengine::procparams::ProcParams stored_pp_;
    Glib::ustring storedValue;
    Glib::ustring lastFilename;
    Glib::ustring imagePath;
    RTImage *append_mode_on_image_;
    RTImage *append_mode_off_image_;
    Gtk::ToggleButton *append_mode_;
    Gtk::TreeIter currRow;
    ProfileStoreEntry *lastSavedPSE;
    ProfileStoreEntry *customPSE;
    ProfileStoreEntry *defaultPSE;

    void appendModeToggled();
    bool isCustomSelected();
    bool isLastSavedSelected();
    bool isDefaultSelected();
    Gtk::TreeIter getCustomRow();
    Gtk::TreeIter getLastSavedRow ();
    Gtk::TreeIter addCustomRow ();
    Gtk::TreeIter addLastSavedRow ();
    Gtk::TreeIter addDefaultRow();

//protected:

    static PartialPasteDlg* partialProfileDlg;
    Gtk::Button* save;
    Gtk::Button* load;
    Gtk::Button* copy;
    Gtk::Button* paste;
    ProfileStoreComboBox* profiles;
    rtengine::procparams::PartialProfile *custom;
    rtengine::procparams::PartialProfile *lastsaved;
    rtengine::procparams::PartialProfile *defprofile;
    ProfileChangeListener* tpc;
    bool dontupdate;
    sigc::connection changeconn;
    static Gtk::Window* parent;
    void changeTo (const rtengine::procparams::PartialProfile* newpp, Glib::ustring profname);

public:

    explicit ProfilePanel ();
    ~ProfilePanel () override;

    void setProfileChangeListener (ProfileChangeListener* ppl)
    {
        tpc = ppl;
    }

    static void init (Gtk::Window* parentWindow);
    static void cleanup ();
    void storeCurrentValue() override;
    void updateProfileList () override;
    void restoreValue() override;

    void initProfile (const Glib::ustring& profileFullPath, rtengine::procparams::ProcParams* lastSaved, const rtengine::FramesMetaData *metadata);
    void setInitialFileName (const Glib::ustring& filename);

    // PParamsChangeListener interface
    void procParamsChanged(
        const rtengine::procparams::ProcParams* params,
        const rtengine::ProcEvent& ev,
        const Glib::ustring& descr,
        const ParamsEdited* paramsEdited = nullptr
    ) override;
    void clearParamChanges() override;

    // gui callbacks
    void save_clicked (GdkEventButton* event);
    void load_clicked (GdkEventButton* event);
    void copy_clicked (GdkEventButton* event);
    void paste_clicked (GdkEventButton* event);
    void selection_changed ();
    void writeOptions();
};

#endif
