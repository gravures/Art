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
#include <array>
#include <utility>

#include "saveformatpanel.h"
#include "multilangmgr.h"
#include "guiutils.h"
#include "../rtengine/imgiomanager.h"

namespace
{

const std::array<std::pair<const char*, SaveFormat>, 7> sf_templates = {{
     {"JPEG (8-bit)", SaveFormat("jpg", 8, 8, false)},
     {"TIFF (8-bit)", SaveFormat("tif", 8, 8, false)},
     {"TIFF (16-bit)", SaveFormat("tif", 8, 16, false)},
     {"TIFF (16-bit float)", SaveFormat("tif", 8, 16, true)},
     {"TIFF (32-bit float)", SaveFormat("tif", 8, 32, true)},
     {"PNG (8-bit)", SaveFormat("png", 8, 8, false)},
     {"PNG (16-bit)", SaveFormat("png", 16, 8, false)}
}};

}


SaveFormatPanel::SaveFormatPanel(): listener(nullptr)
{
    extrafmts_ = rtengine::ImageIOManager::getInstance()->getSaveFormats();
    
    // ---------------------  FILE FORMAT SELECTOR
    Gtk::Grid* hb1 = Gtk::manage (new Gtk::Grid ());
    hb1->set_column_spacing(5);
    hb1->set_row_spacing(5);
    setExpandAlignProperties(hb1, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);
    Gtk::Label* flab = Gtk::manage (new Gtk::Label (M("SAVEDLG_FILEFORMAT") + ":"));
    setExpandAlignProperties(flab, false, false, Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
    format = Gtk::manage (new MyComboBoxText ());
    setExpandAlignProperties(format, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);
    format->signal_changed ().connect (sigc::mem_fun (*this, &SaveFormatPanel::formatChanged));

    for (const auto& sf_template : sf_templates) {
        format->append(sf_template.first);
    }
    for (auto &p : extrafmts_) {
        format->append(p.second);
    }

    hb1->attach (*flab, 0, 0, 1, 1);
    hb1->attach (*format, 1, 0, 1, 1);
    hb1->show_all();

    // ---------------------  JPEG OPTIONS
    jpegOpts = new Gtk::Grid();
    jpegOpts->set_column_spacing(15);
    jpegOpts->set_row_spacing(5);
    setExpandAlignProperties(jpegOpts, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);

    jpegQual = new Adjuster (M("SAVEDLG_JPEGQUAL"), 0, 100, 1, 100);
    setExpandAlignProperties(jpegQual, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);
    jpegQual->setAdjusterListener (this);

    jpegSubSampLabel = Gtk::manage (new Gtk::Label (M("SAVEDLG_SUBSAMP") + Glib::ustring(":")) );
    setExpandAlignProperties(jpegSubSampLabel, true, false, Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

    jpegSubSamp = Gtk::manage (new MyComboBoxText ());
    setExpandAlignProperties(jpegSubSamp, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);
    jpegSubSamp->append (M("SAVEDLG_SUBSAMP_1"));
    jpegSubSamp->append (M("SAVEDLG_SUBSAMP_2"));
    jpegSubSamp->append (M("SAVEDLG_SUBSAMP_3"));
    jpegSubSamp->set_tooltip_text (M("SAVEDLG_SUBSAMP_TOOLTIP"));
    jpegSubSamp->set_active (2);
    jpegSubSamp->signal_changed().connect( sigc::mem_fun(*this, &SaveFormatPanel::formatChanged) );

    jpegOpts->attach(*jpegQual, 0, 0, 1, 2);
    jpegOpts->attach(*jpegSubSampLabel, 1, 0, 1, 1);
    jpegOpts->attach(*jpegSubSamp, 1, 1, 1, 1);
    jpegOpts->show_all ();

    // ---------------------  TIFF OPTIONS
    tiffUncompressed = new Gtk::CheckButton (M("SAVEDLG_TIFFUNCOMPRESSED"));
    setExpandAlignProperties(tiffUncompressed, true, false, Gtk::ALIGN_FILL, Gtk::ALIGN_CENTER);
    tiffUncompressed->signal_toggled().connect( sigc::mem_fun(*this, &SaveFormatPanel::formatChanged));
    tiffUncompressed->show_all();


    // ---------------------  MAIN BOX
    savesPP = Gtk::manage (new Gtk::CheckButton (M("SAVEDLG_SAVESPP")));
    savesPP->signal_toggled().connect( sigc::mem_fun(*this, &SaveFormatPanel::formatChanged));
    savesPP->show_all();

    set_column_spacing(5);
    set_row_spacing(5);

    attach (*hb1, 0, 0, 1, 1);
    //attach (*jpegOpts, 0, 1, 1, 1);
    //attach (*tiffUncompressed, 0, 2, 1, 1);
    attach (*savesPP, 0, 4, 1, 2);

    format->set_active(0);
    formatChanged();
}


SaveFormatPanel::~SaveFormatPanel ()
{
    delete tiffUncompressed;
    delete jpegOpts;
    delete jpegQual;
}


void SaveFormatPanel::init(SaveFormat &sf)
{
    FormatChangeListener* const tmp = listener;
    listener = nullptr;

    std::pair<int, std::size_t> index;

    for (std::size_t i = 0; i < sf_templates.size(); ++i) {
        // Without relating the other SaveFormat fields to the
        // SaveFormat::format by additional logic the best
        // way is computing a weight for fitting the input
        // to one of the sf_templates.
        // The format field must match exactly, tiffBits,
        // tiffFloat, and pngBits fields all weigh the same.
        // By providing sane sets of parameters in getFormat()
        // we have perfect matches. If the parameters were
        // tampered with, some entry within SaveFormat::format
        // will be selected, which will be consistent again.

        const int weight =
            10 * (sf.format == sf_templates[i].second.format)
            + (sf.tiffBits == sf_templates[i].second.tiffBits)
            + (sf.tiffFloat == sf_templates[i].second.tiffFloat)
            + (sf.pngBits == sf_templates[i].second.pngBits);

        if (weight > index.first) {
            index = {weight, i};
        }
    }
    for (size_t i = 0; i < extrafmts_.size(); ++i) {
        int w = 10 * (sf.format == extrafmts_[i].first);

        if (w > index.first) {
            index = {w, i + sf_templates.size()};
        }
    }

    format->set_active(index.second);

    jpegSubSamp->set_active(sf.jpegSubSamp - 1);
    jpegQual->setValue(sf.jpegQuality);
    savesPP->set_active(sf.saveParams);
    tiffUncompressed->set_active(sf.tiffUncompressed);

    formatChanged();

    listener = tmp;
}


SaveFormat SaveFormatPanel::getFormat ()
{
    SaveFormat sf;

    const unsigned int sel = format->get_active_row_number();

    if (sel < sf_templates.size()) {
        sf = sf_templates[sel].second;
    } else if (sel - sf_templates.size() < extrafmts_.size()) {
        sf.format = extrafmts_[sel - sf_templates.size()].first;
    }

    sf.jpegQuality = jpegQual->getValue();
    sf.jpegSubSamp = jpegSubSamp->get_active_row_number() + 1;
    sf.tiffUncompressed = tiffUncompressed->get_active();
    sf.saveParams = savesPP->get_active();

    return sf;
}


void SaveFormatPanel::formatChanged ()
{
    const unsigned int act = format->get_active_row_number();

    Glib::ustring fr = "";
    
    if (act < sf_templates.size()) {
        fr = sf_templates[act].second.format;

        removeIfThere(this, jpegOpts, false);
        removeIfThere(this, tiffUncompressed, false);

        if (fr == "jpg") {
            attach (*jpegOpts, 0, 1, 1, 1);
            // jpegOpts->show_all();
            // tiffUncompressed->hide();
        } else if (fr == "png") {
            // jpegOpts->hide();
            // tiffUncompressed->hide();
        } else if (fr == "tif") {
            attach (*tiffUncompressed, 0, 2, 1, 1);
            // jpegOpts->hide();
            // tiffUncompressed->show_all();
        }
    } else if (act - sf_templates.size() < extrafmts_.size()) {
        fr = extrafmts_[act - sf_templates.size()].first;

        removeIfThere(this, jpegOpts, false);
        removeIfThere(this, tiffUncompressed, false);        
    } else {
        return;
    }

    if (listener) {
        listener->formatChanged(fr);
    }
}


void SaveFormatPanel::adjusterChanged(Adjuster* a, double newval)
{
    const unsigned int act = format->get_active_row_number();

    if (listener) {
        if (act < sf_templates.size()) {
            listener->formatChanged(sf_templates[act].second.format);
        } else if (act - sf_templates.size() < extrafmts_.size()) {
            listener->formatChanged(extrafmts_[act - sf_templates.size()].first);
        }
    }
}


void SaveFormatPanel::adjusterAutoToggled(Adjuster* a, bool newval)
{
}
