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
#include "toneequalizer.h"
#include "eventmapper.h"

using namespace rtengine;
using namespace rtengine::procparams;


ToneEqualizer::ToneEqualizer(): FoldableToolPanel(this, "toneequalizer", M("TP_TONE_EQUALIZER_LABEL"), false, true, true)
{
    auto m = ProcEventMapper::getInstance();
    EvEnabled = m->newEvent(RGBCURVE, "HISTORY_MSG_TONE_EQUALIZER_ENABLED");
    EvBands = m->newEvent(RGBCURVE, "HISTORY_MSG_TONE_EQUALIZER_BANDS");
    EvRegularization = m->newEvent(RGBCURVE, "HISTORY_MSG_TONE_EQUALIZER_REGULARIZATION");
    EvColormap = m->newEvent(RGBCURVE, "HISTORY_MSG_TONE_EQUALIZER_SHOW_COLOR_MAP");
    EvToolReset.set_action(RGBCURVE);

    std::array<const char *, 5> images = {
        "purple",
        "blue",
        "gray",
        "yellow",
        "red"
    };
    for (size_t i = 0; i < bands.size(); ++i) {
        bands[i] = Gtk::manage(new Adjuster(M("TP_TONE_EQUALIZER_BAND_" + std::to_string(i)), -100, 100, 1, 0, Gtk::manage(new RTImage(Glib::ustring("circle-") + images[i] + "-small.png"))));
        bands[i]->setAdjusterListener(this);
        pack_start(*bands[i]);
        bands[i]->showIcons(false);
    }
    pack_start(*Gtk::manage(new Gtk::HSeparator()));
    regularization = Gtk::manage(new Adjuster(M("TP_TONE_EQUALIZER_DETAIL"), 0, 4, 1, 4));//-5, 5, 1, 5));
    regularization->setAdjusterListener(this);
    pack_start(*regularization);
    show_colormap = Gtk::manage(new Gtk::CheckButton(M("TP_TONE_EQUALIZER_SHOW_COLOR_MAP")));
    pack_start(*show_colormap);
    show_colormap->signal_toggled().connect(sigc::mem_fun(this, &ToneEqualizer::colormapToggled));
    
    show_all_children ();
}


void ToneEqualizer::read(const ProcParams *pp)
{
    disableListener();

    setEnabled(pp->toneEqualizer.enabled);

    for (size_t i = 0; i < bands.size(); ++i) {
        bands[i]->setValue(pp->toneEqualizer.bands[i]);
        bands[i]->showIcons(pp->toneEqualizer.show_colormap);
    }
    regularization->setValue(pp->toneEqualizer.regularization);

    show_colormap->set_active(pp->toneEqualizer.show_colormap);
    
    enableListener();
}


void ToneEqualizer::write(ProcParams *pp)
{
    for (size_t i = 0; i < bands.size(); ++i) {
        pp->toneEqualizer.bands[i] = bands[i]->getValue();
    }
    pp->toneEqualizer.enabled = getEnabled();
    pp->toneEqualizer.regularization = regularization->getValue();
    pp->toneEqualizer.show_colormap = show_colormap->get_active();
}


void ToneEqualizer::setDefaults(const ProcParams *defParams)
{
    for (size_t i = 0; i < bands.size(); ++i) {
        bands[i]->setDefault(defParams->toneEqualizer.bands[i]);
    }
    regularization->setDefault(defParams->toneEqualizer.regularization);

    inital_params = defParams->toneEqualizer;
}


void ToneEqualizer::adjusterChanged(Adjuster *a, double newval)
{
    if (listener && getEnabled()) {
        if (a == regularization) {
            listener->panelChanged(EvRegularization, Glib::ustring::format(a->getValue()));
        } else {
            Glib::ustring s;
            for (size_t i = 0; i < bands.size(); ++i) {
                s += Glib::ustring::format((int)bands[i]->getValue()) + " ";
            }
            listener->panelChanged(EvBands, s);
        }
    }
}


void ToneEqualizer::adjusterAutoToggled(Adjuster *a, bool newval)
{
}


void ToneEqualizer::enabledChanged()
{
    if (listener) {
        if (get_inconsistent()) {
            listener->panelChanged(EvEnabled, M("GENERAL_UNCHANGED"));
        } else if (getEnabled()) {
            listener->panelChanged(EvEnabled, M("GENERAL_ENABLED"));
        } else {
            listener->panelChanged(EvEnabled, M("GENERAL_DISABLED"));
        }
    }
}


void ToneEqualizer::colormapToggled()
{
    for (size_t i = 0; i < bands.size(); ++i) {
        bands[i]->showIcons(show_colormap->get_active());
    }
    if (listener && getEnabled()) {
        listener->panelChanged(EvColormap, show_colormap->get_active() ? M("GENERAL_ENABLED") : M("GENERAL_DISABLED"));
    }
}


void ToneEqualizer::trimValues(rtengine::procparams::ProcParams *pp)
{
    for (size_t i = 0; i < bands.size(); ++i) {
        bands[i]->trimValue(pp->toneEqualizer.bands[i]);
    }
    regularization->trimValue(pp->toneEqualizer.regularization);
}


void ToneEqualizer::toolReset(bool to_initial)
{
    ProcParams pp;
    if (to_initial) {
        pp.toneEqualizer = inital_params;
    }
    pp.toneEqualizer.enabled = getEnabled();
    read(&pp);
}
