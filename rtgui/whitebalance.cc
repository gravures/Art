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
#include "whitebalance.h"
#include "../rtengine/refreshmap.h"
#include "eventmapper.h"
#include "../rtengine/colortemp.h"

#include <iomanip>

#include "rtimage.h"
#include "options.h"


using namespace rtengine;
using namespace rtengine::procparams;

std::vector<Glib::RefPtr<Gdk::Pixbuf>> WhiteBalance::wbPixbufs;

namespace {

constexpr double CENTERTEMP = 4750;

const std::vector<std::string> labels = {
    "TP_WBALANCE_CAMERA",
    "TP_WBALANCE_AUTO",
    "TP_WBALANCE_CUSTOM",
    "TP_WBALANCE_CUSTOM_MULT"
};

} // namespace

void WhiteBalance::init ()
{
    wbPixbufs.push_back(RTImage::createPixbufFromFile("wb-camera-small.png"));
    wbPixbufs.push_back(RTImage::createPixbufFromFile("wb-auto-small.png"));
    wbPixbufs.push_back(RTImage::createPixbufFromFile("wb-custom-small.png"));
    wbPixbufs.push_back(RTImage::createPixbufFromFile("wb-custom2-small.png"));
}

void WhiteBalance::cleanup ()
{
    for (size_t i = 0; i < wbPixbufs.size(); ++i) {
        wbPixbufs[i].reset();
    }
}


namespace {

constexpr double wbgamma = 3.0;

double wbSlider2Temp(double sval)
{
    double r = (MAXTEMP - MINTEMP);
    double v = (sval - MINTEMP) / r;
    return rtengine::LIM(MINTEMP + std::pow(v, wbgamma) * r, MINTEMP, MAXTEMP);

    // if (sval <= 5000) {
    //     // linear below center-temp
    //     temp = MINTEMP + (sval / 5000.0) * (CENTERTEMP - MINTEMP);
    // } else {
    //     const double slope = (double)(CENTERTEMP - MINTEMP) / (MAXTEMP - CENTERTEMP);
    //     double x = (sval - 5000) / 5000; // x 0..1
    //     double y = x * slope + (1.0 - slope) * pow(x, 4.0);
    //     //double y = pow(x, 4.0);
    //     temp = CENTERTEMP + y * (MAXTEMP - CENTERTEMP);
    // }

    // if (temp < MINTEMP) {
    //     temp = MINTEMP;
    // }

    // if (temp > MAXTEMP) {
    //     temp = MAXTEMP;
    // }

    // return temp;
}


double wbTemp2Slider(double temp)
{
    double r = (MAXTEMP - MINTEMP);
    double v = (temp - MINTEMP) / r;
    return rtengine::LIM(MINTEMP + std::pow(v, 1.0/wbgamma) * r, MINTEMP, MAXTEMP);
    
    // double sval;

    // if (temp <= CENTERTEMP) {
    //     sval = ((temp - MINTEMP) / (CENTERTEMP - MINTEMP)) * 5000.0;
    // } else {
    //     const double slope = (double)(CENTERTEMP - MINTEMP) / (MAXTEMP - CENTERTEMP);
    //     const double y = (temp - CENTERTEMP) / (MAXTEMP - CENTERTEMP);
    //     double x = pow(y, 0.25); // rough guess of x, will be a little lower
    //     double k = 0.1;
    //     bool add = true;

    //     // the y=f(x) function is a mess to invert, therefore we have this trial-refinement loop instead.
    //     // from tests, worst case is about 20 iterations, ie no problem
    //     for (;;) {
    //         double y1 = x * slope + (1.0 - slope) * pow(x, 4.0);

    //         if (5000 * fabs(y1 - y) < 0.1) {
    //             break;
    //         }

    //         if (y1 < y) {
    //             if (!add) {
    //                 k /= 2;
    //             }

    //             x += k;
    //             add = true;
    //         } else {
    //             if (add) {
    //                 k /= 2;
    //             }

    //             x -= k;
    //             add = false;
    //         }
    //     }

    //     sval = 5000.0 + x * 5000.0;
    // }

    // if (sval < 0) {
    //     sval = 0;
    // }

    // if (sval > 10000) {
    //     sval = 10000;
    // }

    // return sval;
}

} // namespace


WhiteBalance::WhiteBalance () : FoldableToolPanel(this, "whitebalance", M("TP_WBALANCE_LABEL"), false, true, true), wbp(nullptr), wblistener(nullptr)
{
    auto m = ProcEventMapper::getInstance();
    EvToolReset.set_action(WHITEBALANCE);
    EvWBMult = m->newEvent(WHITEBALANCE, "HISTORY_MSG_WBALANCE_MULT");

    Gtk::Grid* methodgrid = Gtk::manage(new Gtk::Grid());
    methodgrid->get_style_context()->add_class("grid-spacing");
    setExpandAlignProperties(methodgrid, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);

    Gtk::Label* lab = Gtk::manage (new Gtk::Label (M("TP_WBALANCE_METHOD") + ":"));
    setExpandAlignProperties(lab, false, false, Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

    // Create the Tree model
    refTreeModel = Gtk::TreeStore::create(methodColumns);
    // Create the Combobox
    method = Gtk::manage (new MyComboBox ());
    setExpandAlignProperties(method, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);
    // Assign the model to the Combobox
    method->set_model(refTreeModel);

//    fillMethods();

    //Add the model columns to the Combo (which is a kind of view),
    //rendering them in the default way:
    method->pack_start(methodColumns.colIcon, false);
    method->pack_start(methodColumns.colLabel, true);

    std::vector<Gtk::CellRenderer*> cells = method->get_cells();
    Gtk::CellRendererText* cellRenderer = dynamic_cast<Gtk::CellRendererText*>(cells.at(1));
    cellRenderer->property_ellipsize() = Pango::ELLIPSIZE_MIDDLE;

    method->set_active (0); // Camera
    methodgrid->attach (*lab, 0, 0, 1, 1);
    methodgrid->attach (*method, 1, 0, 1, 1);
    pack_start (*methodgrid, Gtk::PACK_SHRINK, 0 );
    opt = 0;

    Gtk::Grid* spotgrid = Gtk::manage(new Gtk::Grid());
    spotgrid->get_style_context()->add_class("grid-spacing");
    setExpandAlignProperties(spotgrid, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);

    spotbutton = Gtk::manage (new Gtk::Button (M("TP_WBALANCE_PICKER")));
    setExpandAlignProperties(spotbutton, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);
    spotbutton->get_style_context()->add_class("independent");
    spotbutton->set_tooltip_text(M("TP_WBALANCE_SPOTWB"));
    spotbutton->set_image (*Gtk::manage (new RTImage ("color-picker-small.png")));

    Gtk::Label* slab = Gtk::manage (new Gtk::Label (M("TP_WBALANCE_SIZE")));
    setExpandAlignProperties(slab, false, false, Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

    Gtk::Grid* wbsizehelper = Gtk::manage(new Gtk::Grid());
    wbsizehelper->set_name("WB-Size-Helper");
    setExpandAlignProperties(wbsizehelper, false, false, Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

    spotsize = Gtk::manage (new MyComboBoxText ());
    setExpandAlignProperties(spotsize, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);
    spotsize->append ("2");

    if (options.whiteBalanceSpotSize == 2) {
        spotsize->set_active(0);
    }

    spotsize->append ("4");

    if (options.whiteBalanceSpotSize == 4) {
        spotsize->set_active(1);
    }

    spotsize->append ("8");

    if (options.whiteBalanceSpotSize == 8) {
        spotsize->set_active(2);
    }

    spotsize->append ("16");

    if (options.whiteBalanceSpotSize == 16) {
        spotsize->set_active(3);
    }

    spotsize->append ("32");

    if (options.whiteBalanceSpotSize == 32) {
        spotsize->set_active(4);
    }

    wbsizehelper->attach (*spotsize, 0, 0, 1, 1);

    spotgrid->attach (*spotbutton, 0, 0, 1, 1);
    spotgrid->attach (*slab, 1, 0, 1, 1);
    spotgrid->attach (*wbsizehelper, 2, 0, 1, 1);
    pack_start (*spotgrid, Gtk::PACK_SHRINK, 0 );

    Gtk::HSeparator *separator = Gtk::manage (new  Gtk::HSeparator());
    separator->get_style_context()->add_class("grid-row-separator");
    pack_start (*separator, Gtk::PACK_SHRINK, 0);

    Gtk::Image* itempL =  Gtk::manage (new RTImage ("circle-blue-small.png"));
    Gtk::Image* itempR =  Gtk::manage (new RTImage ("circle-yellow-small.png"));
    Gtk::Image* igreenL = Gtk::manage (new RTImage ("circle-magenta-small.png"));
    Gtk::Image* igreenR = Gtk::manage (new RTImage ("circle-green-small.png"));
    Gtk::Image* iblueredL = Gtk::manage (new RTImage ("circle-blue-small.png"));
    Gtk::Image* iblueredR = Gtk::manage (new RTImage ("circle-red-small.png"));

    temp = Gtk::manage (new Adjuster (M("TP_WBALANCE_TEMPERATURE"), MINTEMP, MAXTEMP, 5, CENTERTEMP, itempL, itempR, &wbSlider2Temp, &wbTemp2Slider));
    green = Gtk::manage (new Adjuster (M("TP_WBALANCE_GREEN"), MINGREEN, MAXGREEN, 0.001, 1.0, igreenL, igreenR));
    green->setLogScale(100, 1, true);
    equal = Gtk::manage (new Adjuster (M("TP_WBALANCE_EQBLUERED"), MINEQUAL, MAXEQUAL, 0.001, 1.0, iblueredL, iblueredR));
    // cache_customTemp (0);
    // cache_customGreen (0);
    // cache_customEqual (0);
    equal->set_tooltip_markup (M("TP_WBALANCE_EQBLUERED_TOOLTIP"));
    temp->show ();
    green->show ();
    equal->show ();

    temp->delay = options.adjusterMaxDelay;
    green->delay = options.adjusterMaxDelay;
    equal->delay = options.adjusterMaxDelay;
    
    tempBox = Gtk::manage(new Gtk::VBox());

    tempBox->pack_start(*temp);
    tempBox->pack_start(*green);
    tempBox->pack_start(*equal);
    tempBox->show();
    pack_start(*tempBox);

    temp->setAdjusterListener(this);
    green->setAdjusterListener(this);
    equal->setAdjusterListener(this);

    multBox = Gtk::manage(new Gtk::VBox());
    {
        static const std::vector<std::string> label = {
            "TP_COLORCORRECTION_CHANNEL_R",
            "TP_COLORCORRECTION_CHANNEL_G",
            "TP_COLORCORRECTION_CHANNEL_B"
        };
        static const std::vector<std::string> icon = {
            "circle-red-small.png",
            "circle-green-small.png",
            "circle-blue-small.png"
        };
        for (size_t i = 0; i < 3; ++i) {
            mult[i] = Gtk::manage(new Adjuster(M(label[i]), 0.1, 10, 0.0001, 1, Gtk::manage(new RTImage(icon[i]))));
            multBox->pack_start(*mult[i]);
            mult[i]->show();
            mult[i]->setAdjusterListener(this);
            mult[i]->setLogScale(100, 1, true);
            mult[i]->delay = options.adjusterMaxDelay;
        }
    }
    multBox->show();
    pack_start(*multBox);
    
    spotbutton->signal_pressed().connect( sigc::mem_fun(*this, &WhiteBalance::spotPressed) );
    methconn = method->signal_changed().connect( sigc::mem_fun(*this, &WhiteBalance::methodChanged) );
    spotsize->signal_changed().connect( sigc::mem_fun(*this, &WhiteBalance::spotSizeChanged) );
}


WhiteBalance::~WhiteBalance()
{
    idle_register.destroy();
}


void WhiteBalance::enabledChanged()
{
    if (listener) {
        if (get_inconsistent()) {
            listener->panelChanged(EvWBEnabled, M("GENERAL_UNCHANGED"));
        } else if (getEnabled()) {
            listener->panelChanged(EvWBEnabled, M("GENERAL_ENABLED"));
        } else {
            listener->panelChanged(EvWBEnabled, M("GENERAL_DISABLED"));
        }
    }
}


void WhiteBalance::adjusterChanged(Adjuster* a, double newval)
{
    {
        int m = getActiveMethod();
        ConnectionBlocker blocker(methconn);
        if (m <= int(WBParams::AUTO)) {
            method->set_active(int(WBParams::CUSTOM_TEMP));
        }
    }

    updateMethodGui();
    
    if (listener && getEnabled()) {
        if (a == temp) {
            listener->panelChanged (EvWBTemp, Glib::ustring::format ((int)a->getValue()));
        } else if (a == green) {
            listener->panelChanged (EvWBGreen, Glib::ustring::format (std::setw(4), std::fixed, std::setprecision(3), a->getValue()));
        } else if (a == equal) {
            listener->panelChanged (EvWBequal, Glib::ustring::format (std::setw(4), std::fixed, std::setprecision(3), a->getValue()));
        } else if (a == mult[0] || a == mult[1] || a == mult[2]) {
            listener->panelChanged(EvWBMult, Glib::ustring::compose("%1 %2 %3", mult[0]->getTextValue(), mult[1]->getTextValue(), mult[2]->getTextValue()));
        }
    }
}


void WhiteBalance::adjusterAutoToggled(Adjuster* a, bool newval)
{
}


void WhiteBalance::methodChanged()
{
    int m = getActiveMethod();
    auto row = *(method->get_active());
    int preset = row[methodColumns.colPreset];
    bool update_scale = true;

    disableListener();

    if (preset >= 0) {
        ConnectionBlocker methblock(methconn);
        method->set_active(WBParams::CUSTOM_MULT);
        for (int i = 0; i < 3; ++i) {
            mult[i]->setValue(presets[preset].mult[i]);
        }
    }

    Glib::ustring label;
    switch (m) {
    case int(WBParams::CAMERA): {
        if (wbp) {
            double ctemp, cgreen;
            wbp->getCamWB(ctemp, cgreen);
            temp->setValue(ctemp);
            green->setValue(cgreen);
            equal->setValue(1.0);
        }
    } break;
    case int(WBParams::CUSTOM_TEMP):
    case int(WBParams::CUSTOM_MULT):
        update_scale = false;
        break;
    default:
        break;
    }

    if (m < int(labels.size())) {
        label = M(labels[m]);
    }

    if (update_scale) {
        green->setLogScale(100, green->getValue(), true);
    }

    updateMethodGui();

    if (preset >= 0) {
        method->set_active(WBParams::CUSTOM_TEMP);
        updateMethodGui();
        label = M("TP_WBALANCE_PRESET") + ": " + presets[preset].label;
    }
    
    enableListener();

    if (listener && getEnabled()) {
        listener->panelChanged(EvWBMethod, label);
    }
}


void WhiteBalance::spotPressed ()
{
    if (wblistener) {
        wblistener->spotWBRequested (getSize());
    }
}


void WhiteBalance::spotSizeChanged ()
{
    options.whiteBalanceSpotSize = getSize();

    if (wblistener) {
        wblistener->spotWBRequested (getSize());
    }
}


void WhiteBalance::read(const ProcParams* pp)
{
    disableListener();

    ConnectionBlocker blocker(methconn);

    fillMethods();
    method->set_active(int(pp->wb.method));

    temp->setValue(pp->wb.temperature);
    green->setValue(pp->wb.green);
    equal->setValue(pp->wb.equal);
    for (int i = 0; i < 3; ++i) {
        mult[i]->setValue(1.0 / pp->wb.mult[i]);
    }

    if (pp->wb.method == WBParams::CAMERA) {
        if (wbp) {
            double ctemp = -1.0;
            double cgreen = -1.0;
            wbp->getCamWB(ctemp, cgreen);

            if (ctemp != -1.0) {
                temp->setValue(ctemp);
                green->setValue(cgreen);
                equal->setValue(1.);
            }
        }
    }

    switch (pp->wb.method) {
    case WBParams::AUTO:
        break;
    case WBParams::CUSTOM_MULT: {
        rtengine::ColorTemp ct(mult[0]->getValue(), mult[1]->getValue(), mult[2]->getValue(), 1.0);
        equal->setValue(1.0);
        temp->setValue(ct.getTemp());
        green->setValue(ct.getGreen());
    } break;
    default: {
        rtengine::ColorTemp ct(temp->getValue(), green->getValue(), equal->getValue(), "Custom");
        double m[3];
        ct.getMultipliers(m[0], m[1], m[2]);
        for (int i = 0; i < 3; ++i) {
            mult[i]->setValue(m[i]);
        }
    } break;
    }

    setEnabled(pp->wb.enabled);
    green->setLogScale(100, green->getValue(), true);
    updateMethodGui();

    enableListener();
}


void WhiteBalance::write(ProcParams* pp)
{
    pp->wb.enabled = getEnabled();
    pp->wb.method = WBParams::Type(getActiveMethod());
    pp->wb.temperature = temp->getIntValue ();
    pp->wb.green = green->getValue ();
    pp->wb.equal = equal->getValue ();
    for (int i = 0; i < 3; ++i) {
        pp->wb.mult[i] = 1.0 / mult[i]->getValue();
    }
}


void WhiteBalance::setDefaults(const ProcParams* defParams)
{

    equal->setDefault (defParams->wb.equal);

    if (wbp && defParams->wb.method == WBParams::CAMERA) {
        double ctemp;
        double cgreen;
        wbp->getCamWB(ctemp, cgreen);

        // FIXME: Seems to be always -1.0, called too early? Broken!
        if (ctemp != -1.0) {
            temp->setDefault(ctemp);
            green->setDefault(cgreen);
        }
    } else {
        temp->setDefault(defParams->wb.temperature);
        green->setDefault(defParams->wb.green);
    }
    // Recomputing AutoWB if it's the current method will happen in improccoordinator.cc

    for (int i = 0; i < 3; ++i) {
        mult[i]->setDefault(defParams->wb.mult[i]);
    }

    initial_params = defParams->wb;
}


int WhiteBalance::getSize ()
{
    return atoi(spotsize->get_active_text().c_str());
}


void WhiteBalance::setWB(int vtemp, double vgreen)
{
    disableListener();
    int m = getActiveMethod();
    {
        ConnectionBlocker methblocker(methconn);
        if (m <= int(WBParams::AUTO)) {
            method->set_active(int(WBParams::CUSTOM_TEMP));
        }
    }
    setEnabled(true);
    temp->setValue(vtemp);
    green->setValue(vgreen);
    double e = m == int(WBParams::CUSTOM_MULT) ? 1.0 : equal->getValue();
    rtengine::ColorTemp ctemp(vtemp, vgreen, e, "Custom");
    double mm[3];
    ctemp.getMultipliers(mm[0], mm[1], mm[2]);
    for (int i = 0; i < 3; ++i) {
        mult[i]->setValue(mm[i]);
    }
    updateMethodGui();

    if (listener) {
        listener->panelChanged (EvWBTemp, Glib::ustring::compose("%1, %2", (int)temp->getValue(), Glib::ustring::format (std::setw(4), std::fixed, std::setprecision(3), green->getValue())));
    }

    green->setLogScale(100, vgreen, true);
}


void WhiteBalance::trimValues (rtengine::procparams::ProcParams* pp)
{
    temp->trimValue(pp->wb.temperature);
    green->trimValue(pp->wb.green);
    equal->trimValue(pp->wb.equal);
    for (int i = 0; i < 3; ++i) {
        mult[i]->trimValue(pp->wb.mult[i]);
    }
}


void WhiteBalance::WBChanged(double temperature, double greenVal)
{
    idle_register.add(
        [this, temperature, greenVal]() -> bool
        {
            disableListener();
            setEnabled(true);
            temp->setValue(temperature);
            green->setValue(greenVal);
            temp->setDefault(temperature);
            green->setDefault(greenVal);
            rtengine::ColorTemp ctemp(temperature, greenVal, equal->getValue(), "Custom");
            double m[3];
            ctemp.getMultipliers(m[0], m[1], m[2]);
            for (int i = 0; i < 3; ++i) {
                mult[i]->setValue(1.0 / (m[i] / m[1]));
            }
            enableListener();
            green->setLogScale(100, greenVal, true);

            return false;
        }
    );
}


void WhiteBalance::updateMethodGui()
{
    if (getActiveMethod() == int(WBParams::CUSTOM_MULT)) {
        tempBox->hide();
        multBox->show();

        disableListener();
        rtengine::ColorTemp ct(1.0 / mult[0]->getValue(), 1.0 / mult[1]->getValue(), 1.0 / mult[2]->getValue(), 1.0);
        temp->setValue(ct.getTemp());
        green->setValue(ct.getGreen());
        equal->setValue(1.0);
        enableListener();
    } else {
        tempBox->show();
        multBox->hide();

        disableListener();
        rtengine::ColorTemp ct(temp->getValue(), green->getValue(), equal->getValue(), "Custom");
        double m[3];
        ct.getMultipliers(m[0], m[1], m[2]);
        for (int i = 0; i < 3; ++i) {
            mult[i]->setValue(1.0 / (m[i] / m[1]));
        }
        enableListener();
    }
}


void WhiteBalance::toolReset(bool to_initial)
{
    ProcParams pp;
    if (to_initial) {
        pp.wb = initial_params;
    }
    pp.wb.enabled = getEnabled();
    read(&pp);
}


inline int WhiteBalance::getActiveMethod()
{
    return std::min(method->get_active_row_number(), int(WBParams::CUSTOM_MULT));
}


void WhiteBalance::fillMethods()
{
    refTreeModel->clear();
    presets.clear();

    Gtk::TreeModel::Row row, childrow;

    for (size_t i = 0; i < wbPixbufs.size(); ++i) {
        row = *(refTreeModel->append());
        row[methodColumns.colIcon] = wbPixbufs[i];
        row[methodColumns.colLabel] = M(labels[i]);
        row[methodColumns.colPreset] = -1;
    }

    if (wbp) {
        presets = wbp->getWBPresets();
        if (!presets.empty()) {
            row = *(refTreeModel->append());
            row[methodColumns.colIcon] = wbPixbufs[0];
            row[methodColumns.colLabel] = M("TP_WBALANCE_PRESET");
            row[methodColumns.colPreset] = -1;
        }
        int i = 0;
        for (auto &p : presets) {
            childrow = *(refTreeModel->append(row.children()));
            childrow[methodColumns.colLabel] = p.label;
            childrow[methodColumns.colPreset] = i;
            ++i;
        }
    }
}
