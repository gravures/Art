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
#ifndef _CROP_H_
#define _CROP_H_

#include <gtkmm.h>
#include "cropguilistener.h"
#include "toolpanel.h"
#include "guiutils.h"
#include <vector>

class CropPanelListener
{
public:
    virtual ~CropPanelListener() = default;

    virtual void cropSelectRequested() = 0;
    virtual void cropEnableChanged(bool enabled) = 0;
    // virtual void cropResetRequested() = 0;
};

class Crop final :
    public ToolParamBlock,
    public CropGUIListener,
    public FoldableToolPanel,
    public rtengine::SizeListener
{
public:
    Crop();
    ~Crop() override;

    void read(const rtengine::procparams::ProcParams* pp) override;
    void write(rtengine::procparams::ProcParams* pp) override;

    void ratioChanged   ();
    void ratioFixedChanged ();  // The toggle button
    void refreshSize    ();
    void selectPressed  ();
    void doresetCrop(bool notify=true);
    void setDimensions   (int mw, int mh);
    void enabledChanged () override;
    void positionChanged ();
    void widthChanged   ();
    void heightChanged  ();
    bool refreshSpins   (bool notify = false);
    void notifyListener ();
    void sizeChanged    (int w, int h, int ow, int oh) override;
    void trim           (rtengine::procparams::ProcParams* pp, int ow, int oh);
    void readOptions    ();
    void writeOptions   ();

    void cropMoved          (int &x, int &y, int &w, int &h) override;
    void cropWidth1Resized  (int &x, int &y, int &w, int &h, float custom_ratio=0.f) override;
    void cropWidth2Resized  (int &x, int &y, int &w, int &h, float custom_ratio=0.f) override;
    void cropHeight1Resized (int &x, int &y, int &w, int &h, float custom_ratio=0.f) override;
    void cropHeight2Resized (int &x, int &y, int &w, int &h, float custom_ratio=0.f) override;
    void cropTopLeftResized     (int &x, int &y, int &w, int &h, float custom_ratio=0.f) override;
    void cropTopRightResized    (int &x, int &y, int &w, int &h, float custom_ratio=0.f) override;
    void cropBottomLeftResized  (int &x, int &y, int &w, int &h, float custom_ratio=0.f) override;
    void cropBottomRightResized (int &x, int &y, int &w, int &h, float custom_ratio=0.f) override;
    void cropInit           (int &x, int &y, int &w, int &h) override;
    void cropResized        (int &x, int &y, int& x2, int& y2) override;
    void cropManipReady(int &x, int &y, int &w, int &h) override;
    bool inImageArea        (int x, int y) override;
    double getRatio         () const override;

    void setCropPanelListener (CropPanelListener* cl)
    {
        clistener = cl;
    }

    void resizeScaleChanged (double rsc);
    void hFlipCrop          ();
    void vFlipCrop          ();
    void rotateCrop         (int deg, bool hflip, bool vflip);

    void setDefaults(const rtengine::procparams::ProcParams *def) override;
    void toolReset(bool to_initial) override;

    void setSelecting(bool yes);

private:
    struct CropRatio {
        Glib::ustring label;
        double value;
    };

    std::vector<CropRatio> crop_ratios;

    void adjustCropToRatio();
    void updateCurrentRatio();

    Gtk::CheckButton* fixr;
    MyComboBoxText* ratio;
    MyComboBoxText* orientation;
    MyComboBoxText* guide;

    Gtk::Button* selectCrop;
    Gtk::Button* resetCrop;
    CropPanelListener* clistener;
    int opt;
    MySpinButton* x;
    MySpinButton* y;
    MySpinButton* w;
    MySpinButton* h;
    MySpinButton* ppi;
    Gtk::Label* sizecm;
    Gtk::Label* sizein;
    Gtk::Grid* ppigrid;
    Gtk::Grid* methodgrid;
    Gtk::Label *customRatioLabel;

    int maxw, maxh;
    double nx, ny;
    int nw, nh;
    int lastRotationDeg;
    sigc::connection xconn, yconn, wconn, hconn, fconn, rconn, oconn, gconn;
    bool wDirty, hDirty, xDirty, yDirty, lastFixRatio;
    bool selecting_;

    IdleRegister idle_register;

    rtengine::procparams::CropParams initial_params;
};

#endif
