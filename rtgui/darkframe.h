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
#ifndef _DARKFRAME_H_
#define _DARKFRAME_H_

#include <memory>
#include <gtkmm.h>
#include "toolpanel.h"
#include "../rtengine/rawimage.h"
#include "guiutils.h"

class DFProvider
{
public:
    virtual rtengine::RawImage* getDF() = 0;
    virtual Glib::ustring GetCurrentImageFilePath() = 0;
    // add other info here
};

class DarkFrame : public ToolParamBlock, public FoldableToolPanel
{

protected:

    MyFileChooserButton *darkFrameFile;
    Gtk::HBox *hbdf;
    Gtk::Button *btnReset;
    Gtk::Label *dfLabel;
    Gtk::Label *dfInfo;
    Gtk::CheckButton* dfAuto;
    bool dfChanged;
    bool lastDFauto;
    DFProvider *dfp;
    sigc::connection dfautoconn, dfFile;
    bool b_filter_asCurrent;
    bool israw;

    rtengine::procparams::RAWParams initial_params;

public:

    DarkFrame();

    void read(const rtengine::procparams::ProcParams* pp) override;
    void write(rtengine::procparams::ProcParams* pp) override;

    void darkFrameChanged ();
    void darkFrameReset   ();
    void dfAutoChanged    ();
    void setDFProvider    (DFProvider* p)
    {
        dfp = p;
    }

    void setDefaults(const rtengine::procparams::ProcParams *def) override;
    void toolReset(bool to_initial) override;
};

#endif
