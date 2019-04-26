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
#include "paramsedited.h"
#include <cstring>
#include "options.h"
#include "addsetids.h"

ParamsEdited::ParamsEdited(bool value)
{

    set(value);
}

void ParamsEdited::set(bool v)
{

    general.rank         = v;
    general.colorlabel   = v;
    general.intrash      = v;
    toneCurve.curve      = v;
    toneCurve.curve2     = v;
    toneCurve.curveMode  = v;
    toneCurve.curveMode2 = v;
    toneCurve.brightness = v;
    toneCurve.black      = v;
    toneCurve.contrast   = v;
    toneCurve.saturation = v;
    toneCurve.shcompr    = v;
    toneCurve.hlcompr    = v;
    toneCurve.hlcomprthresh = v;
    toneCurve.autoexp    = v;
    toneCurve.clip       = v;
    toneCurve.expcomp    = v;
    toneCurve.hrenabled   = v;
    toneCurve.method    = v;
    toneCurve.histmatching = v;
    toneCurve.fromHistMatching = v;
    toneCurve.clampOOG = v;
    labCurve.enabled = v;
    labCurve.lcurve      = v;
    labCurve.acurve      = v;
    labCurve.bcurve      = v;
    labCurve.cccurve     = v;
    labCurve.chcurve     = v;
    labCurve.lhcurve     = v;
    labCurve.hhcurve     = v;
    labCurve.lccurve    = v;
    labCurve.clcurve    = v;
    labCurve.brightness  = v;
    labCurve.contrast    = v;
    labCurve.chromaticity    = v;
    labCurve.avoidcolorshift = v;
    labCurve.rstprotection   = v;
    labCurve.lcredsk         = v;
    localContrast.enabled = v;
    localContrast.mode = v;
    localContrast.radius = v;
    localContrast.amount = v;
    localContrast.darkness = v;
    localContrast.lightness = v;
    localContrast.contrast = v;
    localContrast.curve = v;
    rgbCurves.enabled = v;
    rgbCurves.lumamode       = v;
    rgbCurves.rcurve         = v;
    rgbCurves.gcurve         = v;
    rgbCurves.bcurve         = v;

    sharpening.enabled            = v;
    sharpening.contrast           = v;
    sharpening.radius             = v;
    sharpening.blurradius         = v;
    sharpening.amount             = v;
    sharpening.threshold          = v;
    sharpening.edgesonly          = v;
    sharpening.edges_radius       = v;
    sharpening.edges_tolerance    = v;
    sharpening.halocontrol        = v;
    sharpening.halocontrol_amount = v;
    sharpening.method         = v;
    sharpening.deconvamount   = v;
    sharpening.deconvradius   = v;
    sharpening.deconviter     = v;
    sharpening.deconvdamping  = v;
    prsharpening.enabled            = v;
    prsharpening.contrast           = v;
    prsharpening.radius             = v;
    prsharpening.amount             = v;
    prsharpening.threshold          = v;
    prsharpening.edgesonly          = v;
    prsharpening.edges_radius       = v;
    prsharpening.edges_tolerance    = v;
    prsharpening.halocontrol        = v;
    prsharpening.halocontrol_amount = v;
    prsharpening.method         = v;
    prsharpening.deconvamount   = v;
    prsharpening.deconvradius   = v;
    prsharpening.deconviter     = v;
    prsharpening.deconvdamping  = v;
    sharpenMicro.enabled      = v;
    sharpenMicro.matrix       = v;
    sharpenMicro.contrast     = v;
    sharpenMicro.amount       = v;
    sharpenMicro.uniformity   = v;
    //colorBoost.amount         = v;
    //colorBoost.avoidclip      = v;
    //colorBoost.enable_saturationlimiter = v;
    //colorBoost.saturationlimit = v;
    wb.enabled                 = v;
    wb.method                  = v;
    wb.green                   = v;
    wb.temperature             = v;
    wb.equal                   = v;
    wb.tempBias                = v;
    //colorShift.a               = v;
    //colorShift.b               = v;
    //lumaDenoise.enabled        = v;
    //lumaDenoise.radius         = v;
    //lumaDenoise.edgetolerance  = v;
    //colorDenoise.enabled       = v;
    //colorDenoise.amount        = v;
    defringe.enabled           = v;
    defringe.radius            = v;
    defringe.threshold         = v;
    defringe.huecurve          = v;
    impulseDenoise.enabled     = v;
    impulseDenoise.thresh      = v;
    denoise.enabled = v;
    denoise.colorSpace = v;
    denoise.aggressive = v;
    denoise.gamma = v;
    denoise.luminanceMethod = v;
    denoise.luminance = v;
    denoise.luminanceCurve = v;
    denoise.luminanceDetail = v;
    denoise.chrominanceMethod = v;
    denoise.chrominanceAutoFactor = v;
    denoise.chrominance = v;
    denoise.chrominanceCurve = v;
    denoise.chrominanceRedGreen = v;
    denoise.chrominanceBlueYellow = v;
    denoise.smoothingEnabled = v;
    denoise.smoothingMethod = v;
    denoise.medianType = v;
    denoise.medianMethod = v;
    denoise.medianIterations = v;
    denoise.guidedLumaRadius = v;
    denoise.guidedLumaStrength = v;
    denoise.guidedChromaRadius = v;
    denoise.guidedChromaStrength = v;
    epd.enabled                = v;
    epd.regions = v;
    epd.showMask = v;
    // epd.strength            = v;
    // epd.gamma            = v;
    // epd.edgeStopping        = v;
    // epd.scale               = v;
    // epd.reweightingIterates = v;
    fattal.enabled   = v;
    fattal.threshold = v;
    fattal.amount    = v;
    fattal.anchor    = v;
    logenc.enabled   = v;
    logenc.autocompute = v;
    logenc.autogray = v;
    logenc.sourceGray = v;
    logenc.blackEv = v;
    logenc.whiteEv = v;
    logenc.targetGray = v;
    logenc.detail = v;
    sh.enabled       = v;
    sh.highlights    = v;
    sh.htonalwidth   = v;
    sh.shadows       = v;
    sh.stonalwidth   = v;
    sh.radius        = v;
    sh.lab           = v;
    toneEqualizer.enabled = v;
    toneEqualizer.bands = v;
    toneEqualizer.detail = v;
    crop.enabled = v;
    crop.x       = v;
    crop.y       = v;
    crop.w       = v;
    crop.h       = v;
    crop.fixratio = v;
    crop.ratio   = v;
    crop.orientation = v;
    crop.guide   = v;
    coarse.rotate = v;
    coarse.hflip = v;
    coarse.vflip = v;
    commonTrans.autofill = v;
    rotate.degree = v;
    distortion.amount = v;
    lensProf.lcMode = v;
    lensProf.lcpFile = v;
    lensProf.useDist = v;
    lensProf.useVign = v;
    lensProf.useCA = v;
    lensProf.useLensfun = v;
    lensProf.lfAutoMatch = v;
    lensProf.lfCameraMake = v;
    lensProf.lfCameraModel = v;
    lensProf.lfLens = v;
    perspective.horizontal = v;
    perspective.vertical = v;
    gradient.enabled = v;
    gradient.degree = v;
    gradient.feather = v;
    gradient.strength = v;
    gradient.centerX = v;
    gradient.centerY = v;
    pcvignette.enabled = v;
    pcvignette.strength = v;
    pcvignette.feather = v;
    pcvignette.roundness = v;
    cacorrection.red = v;
    cacorrection.blue = v;
    vignetting.amount = v;
    vignetting.radius = v;
    vignetting.strength = v;
    vignetting.centerX = v;
    vignetting.centerY = v;
    chmixer.enabled = v;
    chmixer.red[0] = v;
    chmixer.red[1] = v;
    chmixer.red[2] = v;
    chmixer.green[0] = v;
    chmixer.green[1] = v;
    chmixer.green[2] = v;
    chmixer.blue[0] = v;
    chmixer.blue[1] = v;
    chmixer.blue[2] = v;
    blackwhite.enabled   = v;
    blackwhite.mixerRed   = v;
    blackwhite.mixerGreen   = v;
    blackwhite.mixerBlue   = v;
    blackwhite.gammaRed   = v;
    blackwhite.gammaGreen   = v;
    blackwhite.gammaBlue   = v;
    blackwhite.filter   = v;
    blackwhite.setting   = v;
    blackwhite.method   = v;
    blackwhite.luminanceCurve = v;

    resize.scale     = v;
    resize.appliesTo = v;
    resize.method    = v;
    resize.dataspec  = v;
    resize.width     = v;
    resize.height    = v;
    resize.enabled   = v;
    resize.allowUpscaling = v;
    icm.inputProfile = v;
    icm.toneCurve = v;
    icm.applyLookTable = v;
    icm.applyBaselineExposureOffset = v;
    icm.applyHueSatMap = v;
    icm.dcpIlluminant = v;
    icm.workingProfile = v;
    icm.outputProfile = v;
    icm.outputIntent = v;
    icm.outputBPC = v;
    raw.bayersensor.method = v;
    raw.bayersensor.border = v;
    raw.bayersensor.imageNum = v;
    raw.bayersensor.ccSteps = v;
    raw.bayersensor.exBlack0 = v;
    raw.bayersensor.exBlack1 = v;
    raw.bayersensor.exBlack2 = v;
    raw.bayersensor.exBlack3 = v;
    raw.bayersensor.exTwoGreen = v;
    raw.bayersensor.dcbIterations = v;
    raw.bayersensor.dcbEnhance = v;
    //raw.bayersensor.allEnhance = v;
    raw.bayersensor.lmmseIterations = v;
    raw.bayersensor.dualDemosaicAutoContrast = v;
    raw.bayersensor.dualDemosaicContrast = v;
    raw.bayersensor.pixelShiftMotionCorrectionMethod = v;
    raw.bayersensor.pixelShiftEperIso = v;
    raw.bayersensor.pixelShiftSigma = v;
    raw.bayersensor.pixelShiftShowMotion = v;
    raw.bayersensor.pixelShiftShowMotionMaskOnly = v;
    raw.bayersensor.pixelShiftHoleFill = v;
    raw.bayersensor.pixelShiftMedian = v;
    raw.bayersensor.pixelShiftGreen = v;
    raw.bayersensor.pixelShiftBlur = v;
    raw.bayersensor.pixelShiftSmooth = v;
    raw.bayersensor.pixelShiftEqualBright = v;
    raw.bayersensor.pixelShiftEqualBrightChannel = v;
    raw.bayersensor.pixelShiftNonGreenCross = v;
    raw.bayersensor.pixelShiftDemosaicMethod = v;
    raw.bayersensor.greenEq = v;
    raw.bayersensor.linenoise = v;
    raw.bayersensor.linenoiseDirection = v;
    raw.bayersensor.pdafLinesFilter = v;
    raw.xtranssensor.method = v;
    raw.xtranssensor.dualDemosaicAutoContrast = v;
    raw.xtranssensor.dualDemosaicContrast = v;
    raw.xtranssensor.border = v;
    raw.xtranssensor.ccSteps = v;
    raw.xtranssensor.exBlackRed = v;
    raw.xtranssensor.exBlackGreen = v;
    raw.xtranssensor.exBlackBlue = v;
    raw.ca_autocorrect = v;
    raw.ca_avoidcolourshift = v;
    raw.caautoiterations  = v;
    raw.cablue  = v;
    raw.cared   = v;
    raw.hotPixelFilter = v;
    raw.deadPixelFilter = v;
    raw.hotdeadpix_thresh = v;
    raw.darkFrame = v;
    raw.df_autoselect = v;
    raw.ff_file = v;
    raw.ff_AutoSelect = v;
    raw.ff_BlurRadius = v;
    raw.ff_BlurType = v;
    raw.ff_AutoClipControl = v;
    raw.ff_clipControl = v;
    raw.exPos = v;

    dirpyrequalizer.enabled = v;
    dirpyrequalizer.levels = v;
    dirpyrequalizer.showMask = v;

    filmSimulation.enabled = v;
    filmSimulation.clutFilename = v;
    filmSimulation.strength = v;
    softlight.enabled = v;
    softlight.strength = v;
    dehaze.enabled = v;
    dehaze.strength = v;
    dehaze.showDepthMap = v;
    dehaze.depth = v;
    grain.enabled = v;
    grain.iso = v;
    grain.strength = v;
    grain.scale = v;
    smoothing.enabled = v;
    smoothing.regions = v;
    smoothing.showMask = v;
    colorcorrection.enabled = v;
    colorcorrection.regions = v;
    colorcorrection.showMask = v;
    metadata.mode = v;

    exif = v;
    iptc = v;
}

using namespace rtengine;
using namespace rtengine::procparams;

void ParamsEdited::initFrom(const std::vector<rtengine::procparams::ProcParams>& src)
{
#define SETVAL_(name) name = name && p. name == other. name

    set(true);

    if (src.empty()) {
        return;
    }

    const ProcParams& p = src[0];

    for (size_t i = 1; i < src.size(); i++) {
        const ProcParams& other = src[i];
        toneCurve.curve = toneCurve.curve && p.toneCurve.curve == other.toneCurve.curve;
        toneCurve.curve2 = toneCurve.curve2 && p.toneCurve.curve2 == other.toneCurve.curve2;
        toneCurve.curveMode = toneCurve.curveMode && p.toneCurve.curveMode == other.toneCurve.curveMode;
        toneCurve.curveMode2 = toneCurve.curveMode2 && p.toneCurve.curveMode2 == other.toneCurve.curveMode2;
        toneCurve.brightness = toneCurve.brightness && p.toneCurve.brightness == other.toneCurve.brightness;
        toneCurve.black = toneCurve.black && p.toneCurve.black == other.toneCurve.black;
        toneCurve.contrast = toneCurve.contrast && p.toneCurve.contrast == other.toneCurve.contrast;
        toneCurve.saturation = toneCurve.saturation && p.toneCurve.saturation == other.toneCurve.saturation;
        toneCurve.shcompr = toneCurve.shcompr && p.toneCurve.shcompr == other.toneCurve.shcompr;
        toneCurve.hlcompr = toneCurve.hlcompr && p.toneCurve.hlcompr == other.toneCurve.hlcompr;
        toneCurve.hlcomprthresh = toneCurve.hlcomprthresh && p.toneCurve.hlcomprthresh == other.toneCurve.hlcomprthresh;
        toneCurve.autoexp = toneCurve.autoexp && p.toneCurve.autoexp == other.toneCurve.autoexp;
        toneCurve.clip = toneCurve.clip && p.toneCurve.clip == other.toneCurve.clip;
        toneCurve.expcomp = toneCurve.expcomp && p.toneCurve.expcomp == other.toneCurve.expcomp;
        toneCurve.hrenabled = toneCurve.hrenabled && p.toneCurve.hrenabled == other.toneCurve.hrenabled;
        toneCurve.method = toneCurve.method && p.toneCurve.method == other.toneCurve.method;
        toneCurve.histmatching = toneCurve.histmatching && p.toneCurve.histmatching == other.toneCurve.histmatching;
        toneCurve.fromHistMatching = toneCurve.fromHistMatching && p.toneCurve.fromHistMatching == other.toneCurve.fromHistMatching;
        toneCurve.clampOOG = toneCurve.clampOOG && p.toneCurve.clampOOG == other.toneCurve.clampOOG;
        labCurve.enabled = labCurve.enabled && p.labCurve.enabled == other.labCurve.enabled;
        labCurve.lcurve = labCurve.lcurve && p.labCurve.lcurve == other.labCurve.lcurve;
        labCurve.acurve = labCurve.acurve && p.labCurve.acurve == other.labCurve.acurve;
        labCurve.bcurve = labCurve.bcurve && p.labCurve.bcurve == other.labCurve.bcurve;
        labCurve.cccurve = labCurve.cccurve && p.labCurve.cccurve == other.labCurve.cccurve;
        labCurve.chcurve = labCurve.chcurve && p.labCurve.chcurve == other.labCurve.chcurve;
        labCurve.lhcurve = labCurve.lhcurve && p.labCurve.lhcurve == other.labCurve.lhcurve;
        labCurve.hhcurve = labCurve.hhcurve && p.labCurve.hhcurve == other.labCurve.hhcurve;
        labCurve.lccurve = labCurve.lccurve && p.labCurve.lccurve == other.labCurve.lccurve;
        labCurve.clcurve = labCurve.clcurve && p.labCurve.clcurve == other.labCurve.clcurve;
        labCurve.brightness = labCurve.brightness && p.labCurve.brightness == other.labCurve.brightness;
        labCurve.contrast = labCurve.contrast && p.labCurve.contrast == other.labCurve.contrast;
        labCurve.chromaticity = labCurve.chromaticity && p.labCurve.chromaticity == other.labCurve.chromaticity;
        labCurve.avoidcolorshift = labCurve.avoidcolorshift && p.labCurve.avoidcolorshift == other.labCurve.avoidcolorshift;
        labCurve.rstprotection = labCurve.rstprotection && p.labCurve.rstprotection == other.labCurve.rstprotection;
        labCurve.lcredsk = labCurve.lcredsk && p.labCurve.lcredsk == other.labCurve.lcredsk;

        localContrast.enabled = localContrast.enabled && p.localContrast.enabled == other.localContrast.enabled;
        localContrast.radius = localContrast.radius && p.localContrast.radius == other.localContrast.radius;
        localContrast.amount = localContrast.amount && p.localContrast.amount == other.localContrast.amount;
        localContrast.darkness = localContrast.darkness && p.localContrast.darkness == other.localContrast.darkness;
        localContrast.lightness = localContrast.lightness && p.localContrast.lightness == other.localContrast.lightness;
        SETVAL_(localContrast.mode);
        SETVAL_(localContrast.contrast);
        SETVAL_(localContrast.curve);

        rgbCurves.enabled = rgbCurves.enabled && p.rgbCurves.enabled == other.rgbCurves.enabled;
        rgbCurves.lumamode = rgbCurves.lumamode && p.rgbCurves.lumamode == other.rgbCurves.lumamode;
        rgbCurves.rcurve = rgbCurves.rcurve && p.rgbCurves.rcurve == other.rgbCurves.rcurve;
        rgbCurves.gcurve = rgbCurves.gcurve && p.rgbCurves.gcurve == other.rgbCurves.gcurve;
        rgbCurves.bcurve = rgbCurves.bcurve && p.rgbCurves.bcurve == other.rgbCurves.bcurve;
        sharpenMicro.enabled = sharpenMicro.enabled && p.sharpenMicro.enabled == other.sharpenMicro.enabled;
        sharpenMicro.matrix = sharpenMicro.matrix && p.sharpenMicro.matrix == other.sharpenMicro.matrix;
        sharpenMicro.amount = sharpenMicro.amount && p.sharpenMicro.amount == other.sharpenMicro.amount;
        sharpenMicro.contrast = sharpenMicro.contrast && p.sharpenMicro.contrast == other.sharpenMicro.contrast;
        sharpenMicro.uniformity = sharpenMicro.uniformity && p.sharpenMicro.uniformity == other.sharpenMicro.uniformity;
        sharpening.enabled = sharpening.enabled && p.sharpening.enabled == other.sharpening.enabled;
        sharpening.contrast = sharpening.contrast && p.sharpening.contrast == other.sharpening.contrast;
        sharpening.radius = sharpening.radius && p.sharpening.radius == other.sharpening.radius;
        sharpening.blurradius = sharpening.blurradius && p.sharpening.blurradius == other.sharpening.blurradius;
        sharpening.amount = sharpening.amount && p.sharpening.amount == other.sharpening.amount;
        sharpening.threshold = sharpening.threshold && p.sharpening.threshold == other.sharpening.threshold;
        sharpening.edgesonly = sharpening.edgesonly && p.sharpening.edgesonly == other.sharpening.edgesonly;
        sharpening.edges_radius = sharpening.edges_radius && p.sharpening.edges_radius == other.sharpening.edges_radius;
        sharpening.edges_tolerance = sharpening.edges_tolerance && p.sharpening.edges_tolerance == other.sharpening.edges_tolerance;
        sharpening.halocontrol = sharpening.halocontrol && p.sharpening.halocontrol == other.sharpening.halocontrol;
        sharpening.halocontrol_amount = sharpening.halocontrol_amount && p.sharpening.halocontrol_amount == other.sharpening.halocontrol_amount;
        sharpening.method = sharpening.method && p.sharpening.method == other.sharpening.method;
        sharpening.deconvamount = sharpening.deconvamount && p.sharpening.deconvamount == other.sharpening.deconvamount;
        sharpening.deconvradius = sharpening.deconvradius && p.sharpening.deconvradius == other.sharpening.deconvradius;
        sharpening.deconviter = sharpening.deconviter && p.sharpening.deconviter == other.sharpening.deconviter;
        sharpening.deconvdamping = sharpening.deconvdamping && p.sharpening.deconvdamping == other.sharpening.deconvdamping;
        prsharpening.enabled = prsharpening.enabled && p.prsharpening.enabled == other.prsharpening.enabled;
        prsharpening.contrast = prsharpening.contrast && p.prsharpening.contrast == other.prsharpening.contrast;
        prsharpening.radius = prsharpening.radius && p.prsharpening.radius == other.prsharpening.radius;
        prsharpening.amount = prsharpening.amount && p.prsharpening.amount == other.prsharpening.amount;
        prsharpening.threshold = prsharpening.threshold && p.prsharpening.threshold == other.prsharpening.threshold;
        prsharpening.edgesonly = prsharpening.edgesonly && p.prsharpening.edgesonly == other.prsharpening.edgesonly;
        prsharpening.edges_radius = prsharpening.edges_radius && p.prsharpening.edges_radius == other.prsharpening.edges_radius;
        prsharpening.edges_tolerance = prsharpening.edges_tolerance && p.prsharpening.edges_tolerance == other.prsharpening.edges_tolerance;
        prsharpening.halocontrol = prsharpening.halocontrol && p.prsharpening.halocontrol == other.prsharpening.halocontrol;
        prsharpening.halocontrol_amount = prsharpening.halocontrol_amount && p.prsharpening.halocontrol_amount == other.prsharpening.halocontrol_amount;
        prsharpening.method = prsharpening.method && p.prsharpening.method == other.prsharpening.method;
        prsharpening.deconvamount = prsharpening.deconvamount && p.prsharpening.deconvamount == other.prsharpening.deconvamount;
        prsharpening.deconvradius = prsharpening.deconvradius && p.prsharpening.deconvradius == other.prsharpening.deconvradius;
        prsharpening.deconviter = prsharpening.deconviter && p.prsharpening.deconviter == other.prsharpening.deconviter;
        prsharpening.deconvdamping = prsharpening.deconvdamping && p.prsharpening.deconvdamping == other.prsharpening.deconvdamping;

        //colorBoost.amount = colorBoost.amount && p.colorBoost.amount == other.colorBoost.amount;
        //colorBoost.avoidclip = colorBoost.avoidclip && p.colorBoost.avoidclip == other.colorBoost.avoidclip;
        //colorBoost.enable_saturationlimiter = colorBoost.enable_saturationlimiter && p.colorBoost.enable_saturationlimiter == other.colorBoost.enable_saturationlimiter;
        //colorBoost.saturationlimit = colorBoost.saturationlimit && p.colorBoost.saturationlimit == other.colorBoost.saturationlimit;
        wb.enabled = wb.enabled && p.wb.enabled == other.wb.enabled;
        wb.method = wb.method && p.wb.method == other.wb.method;
        wb.green = wb.green && p.wb.green == other.wb.green;
        wb.equal = wb.equal && p.wb.equal == other.wb.equal;
        wb.temperature = wb.temperature && p.wb.temperature == other.wb.temperature;
        wb.tempBias = wb.tempBias && p.wb.tempBias == other.wb.tempBias;
        //colorShift.a = colorShift.a && p.colorShift.a == other.colorShift.a;
        //colorShift.b = colorShift.b && p.colorShift.b == other.colorShift.b;
        //lumaDenoise.enabled = lumaDenoise.enabled && p.lumaDenoise.enabled == other.lumaDenoise.enabled;
        //lumaDenoise.radius = lumaDenoise.radius && p.lumaDenoise.radius == other.lumaDenoise.radius;
        //lumaDenoise.edgetolerance = lumaDenoise.edgetolerance && p.lumaDenoise.edgetolerance == other.lumaDenoise.edgetolerance;
        //colorDenoise.enabled = colorDenoise.enabled && p.colorDenoise.enabled == other.colorDenoise.enabled;
        //colorDenoise.amount = colorDenoise.amount && p.colorDenoise.amount == other.colorDenoise.amount;
        defringe.enabled = defringe.enabled && p.defringe.enabled == other.defringe.enabled;
        defringe.radius = defringe.radius && p.defringe.radius == other.defringe.radius;
        defringe.threshold = defringe.threshold && p.defringe.threshold == other.defringe.threshold;
        defringe.huecurve = defringe.huecurve && p.defringe.huecurve == other.defringe.huecurve;

        impulseDenoise.enabled = impulseDenoise.enabled && p.impulseDenoise.enabled == other.impulseDenoise.enabled;
        impulseDenoise.thresh = impulseDenoise.thresh && p.impulseDenoise.thresh == other.impulseDenoise.thresh;

        SETVAL_(denoise.enabled);
        SETVAL_(denoise.colorSpace);
        SETVAL_(denoise.aggressive);
        SETVAL_(denoise.gamma);
        SETVAL_(denoise.luminanceMethod);
        SETVAL_(denoise.luminance);
        SETVAL_(denoise.luminanceCurve);
        SETVAL_(denoise.luminanceDetail);
        SETVAL_(denoise.chrominanceMethod);
        SETVAL_(denoise.chrominanceAutoFactor);
        SETVAL_(denoise.chrominance);
        SETVAL_(denoise.chrominanceCurve);
        SETVAL_(denoise.chrominanceRedGreen);
        SETVAL_(denoise.chrominanceBlueYellow);
        SETVAL_(denoise.smoothingEnabled);
        SETVAL_(denoise.smoothingMethod);
        SETVAL_(denoise.medianType);
        SETVAL_(denoise.medianMethod);
        SETVAL_(denoise.medianIterations);
        SETVAL_(denoise.guidedLumaRadius);
        SETVAL_(denoise.guidedLumaStrength);
        SETVAL_(denoise.guidedChromaRadius);
        SETVAL_(denoise.guidedChromaStrength);

        epd.enabled = epd.enabled && p.epd.enabled == other.epd.enabled;
        SETVAL_(epd.regions);
        SETVAL_(epd.showMask);
        // epd.strength = epd.strength && p.epd.strength == other.epd.strength;
        // epd.gamma = epd.gamma && p.epd.gamma == other.epd.gamma;
        // epd.edgeStopping = epd.edgeStopping && p.epd.edgeStopping == other.epd.edgeStopping;
        // epd.scale = epd.scale && p.epd.scale == other.epd.scale;
        // epd.reweightingIterates = epd.reweightingIterates && p.epd.reweightingIterates == other.epd.reweightingIterates;

        fattal.enabled = fattal.enabled && p.fattal.enabled == other.fattal.enabled;
        fattal.threshold = fattal.threshold && p.fattal.threshold == other.fattal.threshold;
        fattal.amount = fattal.amount && p.fattal.amount == other.fattal.amount;
        fattal.anchor = fattal.anchor && p.fattal.anchor == other.fattal.anchor;
        SETVAL_(logenc.enabled);
        SETVAL_(logenc.autocompute);
        SETVAL_(logenc.autogray);
        SETVAL_(logenc.sourceGray);
        SETVAL_(logenc.blackEv);
        SETVAL_(logenc.whiteEv);
        SETVAL_(logenc.targetGray);
        SETVAL_(logenc.detail);

        sh.enabled = sh.enabled && p.sh.enabled == other.sh.enabled;
        sh.highlights = sh.highlights && p.sh.highlights == other.sh.highlights;
        sh.htonalwidth = sh.htonalwidth && p.sh.htonalwidth == other.sh.htonalwidth;
        sh.shadows = sh.shadows && p.sh.shadows == other.sh.shadows;
        sh.stonalwidth = sh.stonalwidth && p.sh.stonalwidth == other.sh.stonalwidth;
        sh.radius = sh.radius && p.sh.radius == other.sh.radius;
        sh.lab = sh.lab && p.sh.lab == other.sh.lab;

        SETVAL_(toneEqualizer.enabled);
        SETVAL_(toneEqualizer.bands);
        SETVAL_(toneEqualizer.detail);

        crop.enabled = crop.enabled && p.crop.enabled == other.crop.enabled;
        crop.x = crop.x && p.crop.x == other.crop.x;
        crop.y = crop.y && p.crop.y == other.crop.y;
        crop.w = crop.w && p.crop.w == other.crop.w;
        crop.h = crop.h && p.crop.h == other.crop.h;
        crop.fixratio = crop.fixratio && p.crop.fixratio == other.crop.fixratio;
        crop.ratio = crop.ratio && p.crop.ratio == other.crop.ratio;
        crop.orientation = crop.orientation && p.crop.orientation == other.crop.orientation;
        crop.guide = crop.guide && p.crop.guide == other.crop.guide;
        coarse.rotate = coarse.rotate && p.coarse.rotate == other.coarse.rotate;
        coarse.hflip = coarse.hflip && p.coarse.hflip == other.coarse.hflip;
        coarse.vflip = coarse.vflip && p.coarse.vflip == other.coarse.vflip;
        commonTrans.autofill = commonTrans.autofill && p.commonTrans.autofill == other.commonTrans.autofill;
        rotate.degree = rotate.degree && p.rotate.degree == other.rotate.degree;
        distortion.amount = distortion.amount && p.distortion.amount == other.distortion.amount;
        lensProf.lcMode = lensProf.lcMode && p.lensProf.lcMode == other.lensProf.lcMode;
        lensProf.lcpFile = lensProf.lcpFile && p.lensProf.lcpFile == other.lensProf.lcpFile;
        lensProf.useDist = lensProf.useDist && p.lensProf.useDist == other.lensProf.useDist;
        lensProf.useVign = lensProf.useVign && p.lensProf.useVign == other.lensProf.useVign;
        lensProf.useCA = lensProf.useCA && p.lensProf.useCA == other.lensProf.useCA;
        lensProf.useLensfun = lensProf.useLensfun && p.lensProf.useLensfun() == other.lensProf.useLensfun();
        lensProf.lfAutoMatch = lensProf.lfAutoMatch && p.lensProf.lfAutoMatch() == other.lensProf.lfAutoMatch();
        lensProf.lfCameraMake = lensProf.lfCameraMake && p.lensProf.lfCameraMake == other.lensProf.lfCameraMake;
        lensProf.lfCameraModel = lensProf.lfCameraModel && p.lensProf.lfCameraModel == other.lensProf.lfCameraModel;
        lensProf.lfLens = lensProf.lfLens && p.lensProf.lfLens == other.lensProf.lfLens;
        perspective.horizontal = perspective.horizontal && p.perspective.horizontal == other.perspective.horizontal;
        perspective.vertical = perspective.vertical && p.perspective.vertical == other.perspective.vertical;
        gradient.enabled = gradient.enabled && p.gradient.enabled == other.gradient.enabled;
        gradient.degree = gradient.degree && p.gradient.degree == other.gradient.degree;
        gradient.feather = gradient.feather && p.gradient.feather == other.gradient.feather;
        gradient.strength = gradient.strength && p.gradient.strength == other.gradient.strength;
        gradient.centerX = gradient.centerX && p.gradient.centerX == other.gradient.centerX;
        gradient.centerY = gradient.centerY && p.gradient.centerY == other.gradient.centerY;
        pcvignette.enabled = pcvignette.enabled && p.pcvignette.enabled == other.pcvignette.enabled;
        pcvignette.strength = pcvignette.strength && p.pcvignette.strength == other.pcvignette.strength;
        pcvignette.feather = pcvignette.feather && p.pcvignette.feather == other.pcvignette.feather;
        pcvignette.roundness = pcvignette.roundness && p.pcvignette.roundness == other.pcvignette.roundness;
        cacorrection.red = cacorrection.red && p.cacorrection.red == other.cacorrection.red;
        cacorrection.blue = cacorrection.blue && p.cacorrection.blue == other.cacorrection.blue;
        vignetting.amount = vignetting.amount && p.vignetting.amount == other.vignetting.amount;
        vignetting.radius = vignetting.radius && p.vignetting.radius == other.vignetting.radius;
        vignetting.strength = vignetting.strength && p.vignetting.strength == other.vignetting.strength;
        vignetting.centerX = vignetting.centerX && p.vignetting.centerX == other.vignetting.centerX;
        vignetting.centerY = vignetting.centerY && p.vignetting.centerY == other.vignetting.centerY;
        chmixer.enabled = chmixer.enabled && p.chmixer.enabled == other.chmixer.enabled;
        chmixer.red[0] = chmixer.red[0] && p.chmixer.red[0] == other.chmixer.red[0];
        chmixer.red[1] = chmixer.red[1] && p.chmixer.red[1] == other.chmixer.red[1];
        chmixer.red[2] = chmixer.red[2] && p.chmixer.red[2] == other.chmixer.red[2];
        chmixer.green[0] = chmixer.green[0] && p.chmixer.green[0] == other.chmixer.green[0];
        chmixer.green[1] = chmixer.green[1] && p.chmixer.green[1] == other.chmixer.green[1];
        chmixer.green[2] = chmixer.green[2] && p.chmixer.green[2] == other.chmixer.green[2];
        chmixer.blue[0] = chmixer.blue[0] && p.chmixer.blue[0] == other.chmixer.blue[0];
        chmixer.blue[1] = chmixer.blue[1] && p.chmixer.blue[1] == other.chmixer.blue[1];
        chmixer.blue[2] = chmixer.blue[2] && p.chmixer.blue[2] == other.chmixer.blue[2];
        blackwhite.enabled = blackwhite.enabled && p.blackwhite.enabled == other.blackwhite.enabled;
        blackwhite.mixerRed = blackwhite.mixerRed && p.blackwhite.mixerRed == other.blackwhite.mixerRed;
        blackwhite.mixerGreen = blackwhite.mixerGreen && p.blackwhite.mixerGreen == other.blackwhite.mixerGreen;
        blackwhite.mixerBlue = blackwhite.mixerBlue && p.blackwhite.mixerBlue == other.blackwhite.mixerBlue;
        blackwhite.gammaRed = blackwhite.gammaRed && p.blackwhite.gammaRed == other.blackwhite.gammaRed;
        blackwhite.gammaGreen = blackwhite.gammaGreen && p.blackwhite.gammaGreen == other.blackwhite.gammaGreen;
        blackwhite.gammaBlue = blackwhite.gammaBlue && p.blackwhite.gammaBlue == other.blackwhite.gammaBlue;
        blackwhite.filter = blackwhite.filter && p.blackwhite.filter == other.blackwhite.filter;
        blackwhite.setting = blackwhite.setting && p.blackwhite.setting == other.blackwhite.setting;
        blackwhite.luminanceCurve = blackwhite.luminanceCurve && p.blackwhite.luminanceCurve == other.blackwhite.luminanceCurve;
        blackwhite.method = blackwhite.method && p.blackwhite.method == other.blackwhite.method;
        resize.scale = resize.scale && p.resize.scale == other.resize.scale;
        resize.appliesTo = resize.appliesTo && p.resize.appliesTo == other.resize.appliesTo;
        resize.method = resize.method && p.resize.method == other.resize.method;
        resize.dataspec = resize.dataspec && p.resize.dataspec == other.resize.dataspec;
        resize.width = resize.width && p.resize.width == other.resize.width;
        resize.height = resize.height && p.resize.height == other.resize.height;
        resize.enabled = resize.enabled && p.resize.enabled == other.resize.enabled;
        resize.allowUpscaling = resize.allowUpscaling && p.resize.allowUpscaling == other.resize.allowUpscaling;
        icm.inputProfile = icm.inputProfile && p.icm.inputProfile == other.icm.inputProfile;
        icm.toneCurve = icm.toneCurve && p.icm.toneCurve == other.icm.toneCurve;
        icm.applyLookTable = icm.applyLookTable && p.icm.applyLookTable == other.icm.applyLookTable;
        icm.applyBaselineExposureOffset = icm.applyBaselineExposureOffset && p.icm.applyBaselineExposureOffset == other.icm.applyBaselineExposureOffset;
        icm.applyHueSatMap = icm.applyHueSatMap && p.icm.applyHueSatMap == other.icm.applyHueSatMap;
        icm.dcpIlluminant = icm.dcpIlluminant && p.icm.dcpIlluminant == other.icm.dcpIlluminant;
        icm.workingProfile = icm.workingProfile && p.icm.workingProfile == other.icm.workingProfile;
        icm.outputProfile = icm.outputProfile && p.icm.outputProfile == other.icm.outputProfile;
        icm.outputIntent = icm.outputIntent && p.icm.outputIntent == other.icm.outputIntent;
        icm.outputBPC = icm.outputBPC && p.icm.outputBPC == other.icm.outputBPC ;
        raw.bayersensor.method = raw.bayersensor.method && p.raw.bayersensor.method == other.raw.bayersensor.method;
        raw.bayersensor.border = raw.bayersensor.border && p.raw.bayersensor.border == other.raw.bayersensor.border;
        raw.bayersensor.imageNum = raw.bayersensor.imageNum && p.raw.bayersensor.imageNum == other.raw.bayersensor.imageNum;
        raw.bayersensor.ccSteps = raw.bayersensor.ccSteps && p.raw.bayersensor.ccSteps == other.raw.bayersensor.ccSteps;
        raw.bayersensor.exBlack0 = raw.bayersensor.exBlack0 && p.raw.bayersensor.black0 == other.raw.bayersensor.black0;
        raw.bayersensor.exBlack1 = raw.bayersensor.exBlack1 && p.raw.bayersensor.black1 == other.raw.bayersensor.black1;
        raw.bayersensor.exBlack2 = raw.bayersensor.exBlack2 && p.raw.bayersensor.black2 == other.raw.bayersensor.black2;
        raw.bayersensor.exBlack3 = raw.bayersensor.exBlack3 && p.raw.bayersensor.black3 == other.raw.bayersensor.black3;
        raw.bayersensor.exTwoGreen = raw.bayersensor.exTwoGreen && p.raw.bayersensor.twogreen == other.raw.bayersensor.twogreen;
        raw.bayersensor.dcbIterations = raw.bayersensor.dcbIterations && p.raw.bayersensor.dcb_iterations == other.raw.bayersensor.dcb_iterations;
        raw.bayersensor.dcbEnhance = raw.bayersensor.dcbEnhance && p.raw.bayersensor.dcb_enhance == other.raw.bayersensor.dcb_enhance;
        //raw.bayersensor.allEnhance = raw.bayersensor.allEnhance && p.raw.bayersensor.all_enhance == other.raw.bayersensor.all_enhance;
        raw.bayersensor.lmmseIterations = raw.bayersensor.lmmseIterations && p.raw.bayersensor.lmmse_iterations == other.raw.bayersensor.lmmse_iterations;
        raw.bayersensor.dualDemosaicAutoContrast = raw.bayersensor.dualDemosaicAutoContrast && p.raw.bayersensor.dualDemosaicAutoContrast == other.raw.bayersensor.dualDemosaicAutoContrast;
        raw.bayersensor.dualDemosaicContrast = raw.bayersensor.dualDemosaicContrast && p.raw.bayersensor.dualDemosaicContrast == other.raw.bayersensor.dualDemosaicContrast;
        raw.bayersensor.pixelShiftMotionCorrectionMethod = raw.bayersensor.pixelShiftMotionCorrectionMethod && p.raw.bayersensor.pixelShiftMotionCorrectionMethod == other.raw.bayersensor.pixelShiftMotionCorrectionMethod;
        raw.bayersensor.pixelShiftEperIso = raw.bayersensor.pixelShiftEperIso && p.raw.bayersensor.pixelShiftEperIso == other.raw.bayersensor.pixelShiftEperIso;
        raw.bayersensor.pixelShiftSigma = raw.bayersensor.pixelShiftSigma && p.raw.bayersensor.pixelShiftSigma == other.raw.bayersensor.pixelShiftSigma;
        raw.bayersensor.pixelShiftShowMotion = raw.bayersensor.pixelShiftShowMotion && p.raw.bayersensor.pixelShiftShowMotion == other.raw.bayersensor.pixelShiftShowMotion;
        raw.bayersensor.pixelShiftShowMotionMaskOnly = raw.bayersensor.pixelShiftShowMotionMaskOnly && p.raw.bayersensor.pixelShiftShowMotionMaskOnly == other.raw.bayersensor.pixelShiftShowMotionMaskOnly;
        raw.bayersensor.pixelShiftHoleFill = raw.bayersensor.pixelShiftHoleFill && p.raw.bayersensor.pixelShiftHoleFill == other.raw.bayersensor.pixelShiftHoleFill;
        raw.bayersensor.pixelShiftMedian = raw.bayersensor.pixelShiftMedian && p.raw.bayersensor.pixelShiftMedian == other.raw.bayersensor.pixelShiftMedian;
        raw.bayersensor.pixelShiftGreen = raw.bayersensor.pixelShiftGreen && p.raw.bayersensor.pixelShiftGreen == other.raw.bayersensor.pixelShiftGreen;
        raw.bayersensor.pixelShiftBlur = raw.bayersensor.pixelShiftBlur && p.raw.bayersensor.pixelShiftBlur == other.raw.bayersensor.pixelShiftBlur;
        raw.bayersensor.pixelShiftSmooth = raw.bayersensor.pixelShiftSmooth && p.raw.bayersensor.pixelShiftSmoothFactor == other.raw.bayersensor.pixelShiftSmoothFactor;
        raw.bayersensor.pixelShiftEqualBright = raw.bayersensor.pixelShiftEqualBright && p.raw.bayersensor.pixelShiftEqualBright == other.raw.bayersensor.pixelShiftEqualBright;
        raw.bayersensor.pixelShiftEqualBrightChannel = raw.bayersensor.pixelShiftEqualBrightChannel && p.raw.bayersensor.pixelShiftEqualBrightChannel == other.raw.bayersensor.pixelShiftEqualBrightChannel;
        raw.bayersensor.pixelShiftNonGreenCross = raw.bayersensor.pixelShiftNonGreenCross && p.raw.bayersensor.pixelShiftNonGreenCross == other.raw.bayersensor.pixelShiftNonGreenCross;
        raw.bayersensor.pixelShiftDemosaicMethod = raw.bayersensor.pixelShiftDemosaicMethod && p.raw.bayersensor.pixelShiftDemosaicMethod == other.raw.bayersensor.pixelShiftDemosaicMethod;
        raw.bayersensor.greenEq = raw.bayersensor.greenEq && p.raw.bayersensor.greenthresh == other.raw.bayersensor.greenthresh;
        raw.bayersensor.linenoise = raw.bayersensor.linenoise && p.raw.bayersensor.linenoise == other.raw.bayersensor.linenoise;
        raw.bayersensor.linenoiseDirection = raw.bayersensor.linenoiseDirection && p.raw.bayersensor.linenoiseDirection == other.raw.bayersensor.linenoiseDirection;
        raw.bayersensor.pdafLinesFilter = raw.bayersensor.pdafLinesFilter && p.raw.bayersensor.pdafLinesFilter == other.raw.bayersensor.pdafLinesFilter;
        raw.xtranssensor.method = raw.xtranssensor.method && p.raw.xtranssensor.method == other.raw.xtranssensor.method;
        raw.xtranssensor.dualDemosaicAutoContrast = raw.xtranssensor.dualDemosaicAutoContrast && p.raw.xtranssensor.dualDemosaicAutoContrast == other.raw.xtranssensor.dualDemosaicAutoContrast;
        raw.xtranssensor.dualDemosaicContrast = raw.xtranssensor.dualDemosaicContrast && p.raw.xtranssensor.dualDemosaicContrast == other.raw.xtranssensor.dualDemosaicContrast;
        raw.xtranssensor.border = raw.xtranssensor.border && p.raw.xtranssensor.border == other.raw.xtranssensor.border;
        raw.xtranssensor.ccSteps = raw.xtranssensor.ccSteps && p.raw.xtranssensor.ccSteps == other.raw.xtranssensor.ccSteps;
        raw.xtranssensor.exBlackRed = raw.xtranssensor.exBlackRed && p.raw.xtranssensor.blackred == other.raw.xtranssensor.blackred;
        raw.xtranssensor.exBlackGreen = raw.xtranssensor.exBlackGreen && p.raw.xtranssensor.blackgreen == other.raw.xtranssensor.blackgreen;
        raw.xtranssensor.exBlackBlue = raw.xtranssensor.exBlackBlue && p.raw.xtranssensor.blackblue == other.raw.xtranssensor.blackblue;
        raw.ca_autocorrect = raw.ca_autocorrect && p.raw.ca_autocorrect == other.raw.ca_autocorrect;
        raw.ca_avoidcolourshift = raw.ca_avoidcolourshift && p.raw.ca_avoidcolourshift == other.raw.ca_avoidcolourshift;
        raw.caautoiterations = raw.caautoiterations && p.raw.caautoiterations == other.raw.caautoiterations;
        raw.cared = raw.cared && p.raw.cared == other.raw.cared;
        raw.cablue = raw.cablue && p.raw.cablue == other.raw.cablue;
        raw.hotPixelFilter = raw.hotPixelFilter && p.raw.hotPixelFilter == other.raw.hotPixelFilter;
        raw.deadPixelFilter = raw.deadPixelFilter && p.raw.deadPixelFilter == other.raw.deadPixelFilter;
        raw.hotdeadpix_thresh = raw.hotdeadpix_thresh && p.raw.hotdeadpix_thresh == other.raw.hotdeadpix_thresh;
        raw.darkFrame = raw.darkFrame && p.raw.dark_frame == other.raw.dark_frame;
        raw.df_autoselect = raw.df_autoselect && p.raw.df_autoselect == other.raw.df_autoselect;
        raw.ff_file = raw.ff_file && p.raw.ff_file == other.raw.ff_file;
        raw.ff_AutoSelect = raw.ff_AutoSelect && p.raw.ff_AutoSelect == other.raw.ff_AutoSelect;
        raw.ff_BlurRadius = raw.ff_BlurRadius && p.raw.ff_BlurRadius == other.raw.ff_BlurRadius;
        raw.ff_BlurType = raw.ff_BlurType && p.raw.ff_BlurType == other.raw.ff_BlurType;
        raw.ff_AutoClipControl = raw.ff_AutoClipControl && p.raw.ff_AutoClipControl == other.raw.ff_AutoClipControl;
        raw.ff_clipControl = raw.ff_clipControl && p.raw.ff_clipControl == other.raw.ff_clipControl;
        raw.exPos = raw.exPos && p.raw.expos == other.raw.expos;

        SETVAL_(dirpyrequalizer.enabled);
        SETVAL_(dirpyrequalizer.levels);
        SETVAL_(dirpyrequalizer.showMask);

        filmSimulation.enabled = filmSimulation.enabled && p.filmSimulation.enabled == other.filmSimulation.enabled;
        filmSimulation.clutFilename = filmSimulation.clutFilename && p.filmSimulation.clutFilename == other.filmSimulation.clutFilename;
        filmSimulation.strength = filmSimulation.strength && p.filmSimulation.strength == other.filmSimulation.strength;
        softlight.enabled = softlight.enabled && p.softlight.enabled == other.softlight.enabled;
        softlight.strength = softlight.strength && p.softlight.strength == other.softlight.strength;
        dehaze.enabled = dehaze.enabled && p.dehaze.enabled == other.dehaze.enabled;
        dehaze.strength = dehaze.strength && p.dehaze.strength == other.dehaze.strength;
        dehaze.showDepthMap = dehaze.showDepthMap && p.dehaze.showDepthMap == other.dehaze.showDepthMap;
        dehaze.depth = dehaze.depth && p.dehaze.depth == other.dehaze.depth;

        SETVAL_(grain.enabled);
        SETVAL_(grain.iso);
        SETVAL_(grain.strength);
        SETVAL_(grain.scale);

        SETVAL_(smoothing.enabled);
        SETVAL_(smoothing.regions);
        SETVAL_(smoothing.showMask);

        SETVAL_(colorcorrection.enabled);
        SETVAL_(colorcorrection.regions);
        SETVAL_(colorcorrection.showMask);
        
        metadata.mode = metadata.mode && p.metadata.mode == other.metadata.mode;

//      How the hell can we handle that???
//      exif = exif && p.exif==other.exif
//      iptc = other.iptc;
    }

#undef SETVAL_
}

void ParamsEdited::combine(rtengine::procparams::ProcParams& toEdit, const rtengine::procparams::ProcParams& mods, bool forceSet)
{
#define ADDSETVAL_(v, i)                                                                        \
    do {                                                                                        \
        if ( v ) {                                                                              \
            toEdit. v = dontforceSet && options.baBehav[ i ] ? toEdit. v + mods. v : mods. v ;  \
        }                                                                                       \
    } while (false)

#define SETVAL_(name) do { if (name) toEdit. name = mods. name; } while (false)


    bool dontforceSet = !forceSet;

    if (toneCurve.curve) {
        toEdit.toneCurve.curve      = mods.toneCurve.curve;
    }

    if (toneCurve.curve2) {
        toEdit.toneCurve.curve2     = mods.toneCurve.curve2;
    }

    if (toneCurve.curveMode) {
        toEdit.toneCurve.curveMode  = mods.toneCurve.curveMode;
    }

    if (toneCurve.curveMode2) {
        toEdit.toneCurve.curveMode2 = mods.toneCurve.curveMode2;
    }

    if (toneCurve.brightness) {
        toEdit.toneCurve.brightness = dontforceSet && options.baBehav[ADDSET_TC_BRIGHTNESS] ? toEdit.toneCurve.brightness + mods.toneCurve.brightness : mods.toneCurve.brightness;
    }

    if (toneCurve.black) {
        toEdit.toneCurve.black        = dontforceSet && options.baBehav[ADDSET_TC_BLACKLEVEL] ? toEdit.toneCurve.black + mods.toneCurve.black : mods.toneCurve.black;
    }

    if (toneCurve.contrast) {
        toEdit.toneCurve.contrast     = dontforceSet && options.baBehav[ADDSET_TC_CONTRAST] ? toEdit.toneCurve.contrast + mods.toneCurve.contrast : mods.toneCurve.contrast;
    }

    if (toneCurve.saturation) {
        toEdit.toneCurve.saturation = dontforceSet && options.baBehav[ADDSET_TC_SATURATION] ? toEdit.toneCurve.saturation + mods.toneCurve.saturation : mods.toneCurve.saturation;
    }

    if (toneCurve.shcompr) {
        toEdit.toneCurve.shcompr  = dontforceSet && options.baBehav[ADDSET_TC_SHCOMP] ? toEdit.toneCurve.shcompr + mods.toneCurve.shcompr : mods.toneCurve.shcompr;
    }

    if (toneCurve.autoexp) {
        toEdit.toneCurve.autoexp  = mods.toneCurve.autoexp;
    }

    if (toneCurve.clip) {
        toEdit.toneCurve.clip         = mods.toneCurve.clip;
    }

    if (toneCurve.expcomp) {
        toEdit.toneCurve.expcomp  = dontforceSet && options.baBehav[ADDSET_TC_EXPCOMP] ? toEdit.toneCurve.expcomp + mods.toneCurve.expcomp : mods.toneCurve.expcomp;
    }

    if (toneCurve.hlcompr) {
        toEdit.toneCurve.hlcompr  = dontforceSet && options.baBehav[ADDSET_TC_HLCOMPAMOUNT] ? toEdit.toneCurve.hlcompr + mods.toneCurve.hlcompr : mods.toneCurve.hlcompr;
    }

    if (toneCurve.hlcomprthresh) {
        toEdit.toneCurve.hlcomprthresh   = dontforceSet && options.baBehav[ADDSET_TC_HLCOMPTHRESH] ? toEdit.toneCurve.hlcomprthresh + mods.toneCurve.hlcomprthresh : mods.toneCurve.hlcomprthresh;
    }

    if (toneCurve.hrenabled) {
        toEdit.toneCurve.hrenabled    = mods.toneCurve.hrenabled;
    }

    if (toneCurve.method) {
        toEdit.toneCurve.method   = mods.toneCurve.method;
    }

    if (toneCurve.histmatching) {
        toEdit.toneCurve.histmatching   = mods.toneCurve.histmatching;
    }

    if (toneCurve.fromHistMatching) {
        toEdit.toneCurve.fromHistMatching   = mods.toneCurve.fromHistMatching;
    }

    if (toneCurve.clampOOG) {
        toEdit.toneCurve.clampOOG = mods.toneCurve.clampOOG;
    }

    if (labCurve.enabled) {
        toEdit.labCurve.enabled = mods.labCurve.enabled;
    }

    if (labCurve.lcurve) {
        toEdit.labCurve.lcurve        = mods.labCurve.lcurve;
    }

    if (labCurve.acurve) {
        toEdit.labCurve.acurve        = mods.labCurve.acurve;
    }

    if (labCurve.bcurve) {
        toEdit.labCurve.bcurve        = mods.labCurve.bcurve;
    }

    if (labCurve.cccurve) {
        toEdit.labCurve.cccurve     = mods.labCurve.cccurve;
    }

    if (labCurve.chcurve) {
        toEdit.labCurve.chcurve     = mods.labCurve.chcurve;
    }

    if (labCurve.lhcurve) {
        toEdit.labCurve.lhcurve     = mods.labCurve.lhcurve;
    }

    if (labCurve.hhcurve) {
        toEdit.labCurve.hhcurve     = mods.labCurve.hhcurve;
    }

    if (labCurve.lccurve) {
        toEdit.labCurve.lccurve    = mods.labCurve.lccurve;
    }

    if (labCurve.clcurve) {
        toEdit.labCurve.clcurve    = mods.labCurve.clcurve;
    }

    if (labCurve.brightness) {
        toEdit.labCurve.brightness   = dontforceSet && options.baBehav[ADDSET_LC_BRIGHTNESS] ? toEdit.labCurve.brightness + mods.labCurve.brightness : mods.labCurve.brightness;
    }

    if (labCurve.contrast) {
        toEdit.labCurve.contrast     = dontforceSet && options.baBehav[ADDSET_LC_CONTRAST] ? toEdit.labCurve.contrast + mods.labCurve.contrast : mods.labCurve.contrast;
    }

    if (labCurve.chromaticity) {
        toEdit.labCurve.chromaticity = dontforceSet && options.baBehav[ADDSET_LC_CHROMATICITY] ? toEdit.labCurve.chromaticity + mods.labCurve.chromaticity : mods.labCurve.chromaticity;
    }

    if (labCurve.avoidcolorshift) {
        toEdit.labCurve.avoidcolorshift = mods.labCurve.avoidcolorshift;
    }

    if (labCurve.rstprotection) {
        toEdit.labCurve.rstprotection = mods.labCurve.rstprotection;
    }

    if (labCurve.lcredsk) {
        toEdit.labCurve.lcredsk     = mods.labCurve.lcredsk;
    }

    if (localContrast.enabled) {
        toEdit.localContrast.enabled = mods.localContrast.enabled;
    }

    ADDSETVAL_(localContrast.radius, ADDSET_LOCALCONTRAST_RADIUS);
    ADDSETVAL_(localContrast.amount, ADDSET_LOCALCONTRAST_AMOUNT);
    ADDSETVAL_(localContrast.darkness, ADDSET_LOCALCONTRAST_DARKNESS);
    ADDSETVAL_(localContrast.lightness, ADDSET_LOCALCONTRAST_LIGHTNESS);
    SETVAL_(localContrast.mode);
    SETVAL_(localContrast.contrast);
    SETVAL_(localContrast.curve);

    if (rgbCurves.enabled) {
        toEdit.rgbCurves.enabled = mods.rgbCurves.enabled;
    }

    if (rgbCurves.lumamode) {
        toEdit.rgbCurves.lumamode   = mods.rgbCurves.lumamode;
    }

    if (rgbCurves.rcurve) {
        toEdit.rgbCurves.rcurve     = mods.rgbCurves.rcurve;
    }

    if (rgbCurves.gcurve) {
        toEdit.rgbCurves.gcurve     = mods.rgbCurves.gcurve;
    }

    if (rgbCurves.bcurve) {
        toEdit.rgbCurves.bcurve     = mods.rgbCurves.bcurve;
    }

    if (sharpenMicro.enabled) {
        toEdit.sharpenMicro.enabled   = mods.sharpenMicro.enabled;
    }

    if (sharpenMicro.matrix) {
        toEdit.sharpenMicro.matrix    = mods.sharpenMicro.matrix;
    }

    if (sharpenMicro.amount) {
        toEdit.sharpenMicro.amount    = dontforceSet && options.baBehav[ADDSET_SHARPENMICRO_AMOUNT] ? toEdit.sharpenMicro.amount + mods.sharpenMicro.amount : mods.sharpenMicro.amount;
    }

    if (sharpenMicro.contrast) {
        toEdit.sharpenMicro.contrast    = dontforceSet && options.baBehav[ADDSET_SHARPENMICRO_CONTRAST] ? toEdit.sharpenMicro.contrast + mods.sharpenMicro.contrast : mods.sharpenMicro.contrast;
    }

    if (sharpenMicro.uniformity) {
        toEdit.sharpenMicro.uniformity    = dontforceSet && options.baBehav[ADDSET_SHARPENMICRO_UNIFORMITY] ? toEdit.sharpenMicro.uniformity + mods.sharpenMicro.uniformity : mods.sharpenMicro.uniformity;
    }

    if (sharpening.enabled) {
        toEdit.sharpening.enabled     = mods.sharpening.enabled;
    }

    if (sharpening.contrast) {
        toEdit.sharpening.contrast  = dontforceSet && options.baBehav[ADDSET_SHARP_CONTRAST] ? toEdit.sharpening.contrast + mods.sharpening.contrast : mods.sharpening.contrast;
    }

    if (sharpening.radius) {
        toEdit.sharpening.radius  = dontforceSet && options.baBehav[ADDSET_SHARP_RADIUS] ? toEdit.sharpening.radius + mods.sharpening.radius : mods.sharpening.radius;
    }

    if (sharpening.blurradius) {
        toEdit.sharpening.blurradius  = dontforceSet && options.baBehav[ADDSET_SHARP_RADIUS] ? toEdit.sharpening.blurradius + mods.sharpening.blurradius : mods.sharpening.blurradius;
    }

    if (sharpening.amount) {
        toEdit.sharpening.amount  = dontforceSet && options.baBehav[ADDSET_SHARP_AMOUNT] ? toEdit.sharpening.amount + mods.sharpening.amount : mods.sharpening.amount;
    }

    if (sharpening.threshold) {
        toEdit.sharpening.threshold = mods.sharpening.threshold;
    }

    if (sharpening.edgesonly) {
        toEdit.sharpening.edgesonly   = mods.sharpening.edgesonly;
    }

    if (sharpening.edges_radius) {
        toEdit.sharpening.edges_radius = dontforceSet && options.baBehav[ADDSET_SHARP_RADIUS] ? toEdit.sharpening.edges_radius + mods.sharpening.edges_radius : mods.sharpening.edges_radius;
    }

    if (sharpening.edges_tolerance) {
        toEdit.sharpening.edges_tolerance = dontforceSet && options.baBehav[ADDSET_SHARP_EDGETOL] ? toEdit.sharpening.edges_tolerance + mods.sharpening.edges_tolerance : mods.sharpening.edges_tolerance;
    }

    if (sharpening.halocontrol) {
        toEdit.sharpening.halocontrol = mods.sharpening.halocontrol;
    }

    if (sharpening.halocontrol_amount) {
        toEdit.sharpening.halocontrol_amount = dontforceSet && options.baBehav[ADDSET_SHARP_HALOCTRL] ? toEdit.sharpening.halocontrol_amount + mods.sharpening.halocontrol_amount : mods.sharpening.halocontrol_amount;
    }

    if (sharpening.method) {
        toEdit.sharpening.method      = mods.sharpening.method;
    }

    if (sharpening.deconvamount) {
        toEdit.sharpening.deconvamount  = dontforceSet && options.baBehav[ADDSET_SHARP_AMOUNT] ? toEdit.sharpening.deconvamount + mods.sharpening.deconvamount : mods.sharpening.deconvamount;
    }

    if (sharpening.deconvradius) {
        toEdit.sharpening.deconvradius  = dontforceSet && options.baBehav[ADDSET_SHARP_RADIUS] ? toEdit.sharpening.deconvradius + mods.sharpening.deconvradius : mods.sharpening.deconvradius;
    }

    if (sharpening.deconviter) {
        toEdit.sharpening.deconviter    = dontforceSet && options.baBehav[ADDSET_SHARP_ITER] ? toEdit.sharpening.deconviter + mods.sharpening.deconviter : mods.sharpening.deconviter;
    }

    if (sharpening.deconvdamping) {
        toEdit.sharpening.deconvdamping = dontforceSet && options.baBehav[ADDSET_SHARP_DAMPING] ? toEdit.sharpening.deconvdamping + mods.sharpening.deconvdamping : mods.sharpening.deconvdamping;
    }

    if (prsharpening.enabled) {
        toEdit.prsharpening.enabled   = mods.prsharpening.enabled;
    }

    if (prsharpening.contrast) {
        toEdit.prsharpening.contrast  = dontforceSet && options.baBehav[ADDSET_SHARP_CONTRAST] ? toEdit.prsharpening.contrast + mods.prsharpening.contrast : mods.prsharpening.contrast;
    }

    if (prsharpening.radius) {
        toEdit.prsharpening.radius  = dontforceSet && options.baBehav[ADDSET_SHARP_RADIUS] ? toEdit.prsharpening.radius + mods.prsharpening.radius : mods.prsharpening.radius;
    }

    if (prsharpening.amount) {
        toEdit.prsharpening.amount    = dontforceSet && options.baBehav[ADDSET_SHARP_AMOUNT] ? toEdit.prsharpening.amount + mods.prsharpening.amount : mods.prsharpening.amount;
    }

    if (prsharpening.threshold) {
        toEdit.prsharpening.threshold = mods.prsharpening.threshold;
    }

    if (prsharpening.edgesonly) {
        toEdit.prsharpening.edgesonly     = mods.prsharpening.edgesonly;
    }

    if (prsharpening.edges_radius) {
        toEdit.prsharpening.edges_radius  = dontforceSet && options.baBehav[ADDSET_SHARP_RADIUS] ? toEdit.prsharpening.edges_radius + mods.prsharpening.edges_radius : mods.prsharpening.edges_radius;
    }

    if (prsharpening.edges_tolerance) {
        toEdit.prsharpening.edges_tolerance = dontforceSet && options.baBehav[ADDSET_SHARP_EDGETOL] ? toEdit.prsharpening.edges_tolerance + mods.prsharpening.edges_tolerance : mods.prsharpening.edges_tolerance;
    }

    if (prsharpening.halocontrol) {
        toEdit.prsharpening.halocontrol        = mods.prsharpening.halocontrol;
    }

    if (prsharpening.halocontrol_amount) {
        toEdit.prsharpening.halocontrol_amount = dontforceSet && options.baBehav[ADDSET_SHARP_HALOCTRL] ? toEdit.prsharpening.halocontrol_amount + mods.prsharpening.halocontrol_amount : mods.prsharpening.halocontrol_amount;
    }

    if (prsharpening.method) {
        toEdit.prsharpening.method        = mods.prsharpening.method;
    }

    if (prsharpening.deconvamount) {
        toEdit.prsharpening.deconvamount  = dontforceSet && options.baBehav[ADDSET_SHARP_AMOUNT] ? toEdit.prsharpening.deconvamount + mods.prsharpening.deconvamount : mods.prsharpening.deconvamount;
    }

    if (prsharpening.deconvradius) {
        toEdit.prsharpening.deconvradius  = dontforceSet && options.baBehav[ADDSET_SHARP_RADIUS] ? toEdit.prsharpening.deconvradius + mods.prsharpening.deconvradius : mods.prsharpening.deconvradius;
    }

    if (prsharpening.deconviter) {
        toEdit.prsharpening.deconviter    = dontforceSet && options.baBehav[ADDSET_SHARP_ITER] ? toEdit.prsharpening.deconviter + mods.prsharpening.deconviter : mods.prsharpening.deconviter;
    }

    if (prsharpening.deconvdamping) {
        toEdit.prsharpening.deconvdamping = dontforceSet && options.baBehav[ADDSET_SHARP_DAMPING] ? toEdit.prsharpening.deconvdamping + mods.prsharpening.deconvdamping : mods.prsharpening.deconvdamping;
    }

    if (wb.enabled) {
        toEdit.wb.enabled = mods.wb.enabled;
    }

    if (wb.method) {
        toEdit.wb.method  = mods.wb.method;
    }

    if (wb.equal) {
        toEdit.wb.equal   = dontforceSet && options.baBehav[ADDSET_WB_EQUAL] ? toEdit.wb.equal + mods.wb.equal : mods.wb.equal;
    }

    if (wb.tempBias) {
        toEdit.wb.tempBias   = dontforceSet && options.baBehav[ADDSET_WB_TEMPBIAS] ? toEdit.wb.tempBias + mods.wb.tempBias : mods.wb.tempBias;
    }

    if (wb.green) {
        toEdit.wb.green   = dontforceSet && options.baBehav[ADDSET_WB_GREEN] ? toEdit.wb.green + mods.wb.green : mods.wb.green;
    }

    if (wb.temperature) {
        toEdit.wb.temperature     = dontforceSet && options.baBehav[ADDSET_WB_TEMPERATURE] ? toEdit.wb.temperature + mods.wb.temperature : mods.wb.temperature;
    }

    //if (colorShift.a)                     toEdit.colorShift.a     = dontforceSet && options.baBehav[ADDSET_CS_BLUEYELLOW] ? toEdit.colorShift.a + mods.colorShift.a : mods.colorShift.a;
    //if (colorShift.b)                     toEdit.colorShift.b     = dontforceSet && options.baBehav[ADDSET_CS_GREENMAGENTA] ? toEdit.colorShift.b + mods.colorShift.b : mods.colorShift.b;
    //if (lumaDenoise.enabled)              toEdit.lumaDenoise.enabled  = mods.lumaDenoise.enabled;
    //if (lumaDenoise.radius)                   toEdit.lumaDenoise.radius   = mods.lumaDenoise.radius;
    //if (lumaDenoise.edgetolerance)            toEdit.lumaDenoise.edgetolerance    = dontforceSet && options.baBehav[ADDSET_LD_EDGETOLERANCE] ? toEdit.lumaDenoise.edgetolerance + mods.lumaDenoise.edgetolerance : mods.lumaDenoise.edgetolerance;
    //if (colorDenoise.enabled)             toEdit.colorDenoise.enabled     = mods.colorDenoise.enabled;
    //if (colorDenoise.amount)              toEdit.colorDenoise.amount  = mods.colorDenoise.amount;

    if (defringe.enabled) {
        toEdit.defringe.enabled   = mods.defringe.enabled;
    }

    if (defringe.radius) {
        toEdit.defringe.radius    = mods.defringe.radius;
    }

    if (defringe.threshold) {
        toEdit.defringe.threshold = mods.defringe.threshold;
    }

    if (defringe.huecurve) {
        toEdit.defringe.huecurve  = mods.defringe.huecurve;
    }

    if (impulseDenoise.enabled) {
        toEdit.impulseDenoise.enabled     = mods.impulseDenoise.enabled;
    }

    if (impulseDenoise.thresh) {
        toEdit.impulseDenoise.thresh  = mods.impulseDenoise.thresh;
    }

    SETVAL_(denoise.enabled);
    SETVAL_(denoise.colorSpace);
    SETVAL_(denoise.aggressive);
    ADDSETVAL_(denoise.gamma, ADDSET_DIRPYRDN_GAMMA);
    SETVAL_(denoise.luminanceMethod);
    ADDSETVAL_(denoise.luminance, ADDSET_DIRPYRDN_LUMA);
    SETVAL_(denoise.luminanceCurve);
    ADDSETVAL_(denoise.luminanceDetail, ADDSET_DIRPYRDN_LUMDET);
    SETVAL_(denoise.chrominanceMethod);
    SETVAL_(denoise.chrominanceAutoFactor);
    ADDSETVAL_(denoise.chrominance, ADDSET_DIRPYRDN_CHROMA);
    SETVAL_(denoise.chrominanceCurve);
    ADDSETVAL_(denoise.chrominanceRedGreen, ADDSET_DIRPYRDN_CHROMARED);
    ADDSETVAL_(denoise.chrominanceBlueYellow, ADDSET_DIRPYRDN_CHROMABLUE);
    SETVAL_(denoise.smoothingEnabled);
    SETVAL_(denoise.smoothingMethod);
    SETVAL_(denoise.medianType);
    SETVAL_(denoise.medianMethod);
    ADDSETVAL_(denoise.medianIterations, ADDSET_DIRPYRDN_PASSES);
    SETVAL_(denoise.guidedLumaRadius);
    SETVAL_(denoise.guidedLumaStrength);
    SETVAL_(denoise.guidedChromaRadius);
    SETVAL_(denoise.guidedChromaStrength);

    SETVAL_(epd.enabled);
    if (epd.regions) {
        toEdit.epd.regions = mods.epd.regions;
        toEdit.epd.labmasks = mods.epd.labmasks;
    }
    SETVAL_(epd.showMask);
    // if (epd.enabled) {
    //     toEdit.epd.enabled                = mods.epd.enabled;
    // }

    // if (epd.strength) {
    //     toEdit.epd.strength               = mods.epd.strength;
    // }

    // if (epd.gamma) {
    //     toEdit.epd.gamma              = mods.epd.gamma;
    // }

    // if (epd.edgeStopping) {
    //     toEdit.epd.edgeStopping           = mods.epd.edgeStopping;
    // }

    // if (epd.scale) {
    //     toEdit.epd.scale              = mods.epd.scale;
    // }

    // if (epd.reweightingIterates) {
    //     toEdit.epd.reweightingIterates    = mods.epd.reweightingIterates;
    // }

    if (fattal.enabled) {
        toEdit.fattal.enabled = mods.fattal.enabled;
    }

    if (fattal.threshold) {
        toEdit.fattal.threshold = mods.fattal.threshold;
    }

    if (fattal.amount) {
        toEdit.fattal.amount = mods.fattal.amount;
    }

    if (fattal.anchor) {
        toEdit.fattal.anchor = mods.fattal.anchor;
    }

    SETVAL_(logenc.enabled);
    SETVAL_(logenc.autocompute);
    SETVAL_(logenc.autogray);
    SETVAL_(logenc.sourceGray);
    SETVAL_(logenc.blackEv);
    SETVAL_(logenc.whiteEv);
    SETVAL_(logenc.targetGray);
    SETVAL_(logenc.detail);

    if (sh.enabled) {
        toEdit.sh.enabled         = mods.sh.enabled;
    }

    if (sh.highlights) {
        toEdit.sh.highlights  = dontforceSet && options.baBehav[ADDSET_SH_HIGHLIGHTS] ? toEdit.sh.highlights + mods.sh.highlights : mods.sh.highlights;
    }

    if (sh.htonalwidth) {
        toEdit.sh.htonalwidth     = mods.sh.htonalwidth;
    }

    if (sh.shadows) {
        toEdit.sh.shadows         = dontforceSet && options.baBehav[ADDSET_SH_SHADOWS] ? toEdit.sh.shadows + mods.sh.shadows : mods.sh.shadows;
    }

    if (sh.stonalwidth) {
        toEdit.sh.stonalwidth     = mods.sh.stonalwidth;
    }

    if (sh.radius) {
        toEdit.sh.radius      = mods.sh.radius;
    }

    if (sh.lab) {
        toEdit.sh.lab      = mods.sh.lab;
    }

    SETVAL_(toneEqualizer.enabled);
    SETVAL_(toneEqualizer.bands);
    SETVAL_(toneEqualizer.detail);

    if (crop.enabled) {
        toEdit.crop.enabled = mods.crop.enabled;
    }

    if (crop.x) {
        toEdit.crop.x         = mods.crop.x;
    }

    if (crop.y) {
        toEdit.crop.y         = mods.crop.y;
    }

    if (crop.w) {
        toEdit.crop.w         = mods.crop.w;
    }

    if (crop.h) {
        toEdit.crop.h         = mods.crop.h;
    }

    if (crop.fixratio) {
        toEdit.crop.fixratio  = mods.crop.fixratio;
    }

    if (crop.ratio) {
        toEdit.crop.ratio         = mods.crop.ratio;
    }

    if (crop.orientation) {
        toEdit.crop.orientation = mods.crop.orientation;
    }

    if (crop.guide) {
        toEdit.crop.guide         = mods.crop.guide;
    }

    if (coarse.rotate) {
        toEdit.coarse.rotate  = mods.coarse.rotate;
    }

    if (coarse.hflip) {
        toEdit.coarse.hflip   = mods.coarse.hflip;
    }

    if (coarse.vflip) {
        toEdit.coarse.vflip   = mods.coarse.vflip;
    }

    if (commonTrans.autofill) {
        toEdit.commonTrans.autofill       = mods.commonTrans.autofill;
    }

    if (rotate.degree) {
        toEdit.rotate.degree          = dontforceSet && options.baBehav[ADDSET_ROTATE_DEGREE] ? toEdit.rotate.degree + mods.rotate.degree : mods.rotate.degree;
    }

    if (distortion.amount) {
        toEdit.distortion.amount      = dontforceSet && options.baBehav[ADDSET_DIST_AMOUNT] ? toEdit.distortion.amount + mods.distortion.amount : mods.distortion.amount;
    }

    if (lensProf.lcMode) {
        toEdit.lensProf.lcMode         = mods.lensProf.lcMode;
    }

    if (lensProf.lcpFile) {
        toEdit.lensProf.lcpFile         = mods.lensProf.lcpFile;
    }

    if (lensProf.useDist) {
        toEdit.lensProf.useDist         = mods.lensProf.useDist;
    }

    if (lensProf.useVign) {
        toEdit.lensProf.useVign         = mods.lensProf.useVign;
    }

    if (lensProf.useCA) {
        toEdit.lensProf.useCA           = mods.lensProf.useCA;
    }

    if (lensProf.lfCameraMake) {
        toEdit.lensProf.lfCameraMake = mods.lensProf.lfCameraMake;
    }

    if (lensProf.lfCameraModel) {
        toEdit.lensProf.lfCameraModel = mods.lensProf.lfCameraModel;
    }

    if (lensProf.lfLens) {
        toEdit.lensProf.lfLens = mods.lensProf.lfLens;
    }

    if (perspective.horizontal) {
        toEdit.perspective.horizontal     = dontforceSet && options.baBehav[ADDSET_PERSPECTIVE] ? toEdit.perspective.horizontal + mods.perspective.horizontal : mods.perspective.horizontal;
    }

    if (perspective.vertical) {
        toEdit.perspective.vertical   = dontforceSet && options.baBehav[ADDSET_PERSPECTIVE] ? toEdit.perspective.vertical + mods.perspective.vertical : mods.perspective.vertical;
    }

    if (gradient.enabled) {
        toEdit.gradient.enabled   = mods.gradient.enabled;
    }

    if (gradient.degree) {
        toEdit.gradient.degree    = dontforceSet && options.baBehav[ADDSET_GRADIENT_DEGREE] ? toEdit.gradient.degree + mods.gradient.degree : mods.gradient.degree;
    }

    if (gradient.feather) {
        toEdit.gradient.feather   = dontforceSet && options.baBehav[ADDSET_GRADIENT_FEATHER] ? toEdit.gradient.feather + mods.gradient.feather : mods.gradient.feather;
    }

    if (gradient.strength) {
        toEdit.gradient.strength  = dontforceSet && options.baBehav[ADDSET_GRADIENT_STRENGTH] ? toEdit.gradient.strength + mods.gradient.strength : mods.gradient.strength;
    }

    if (gradient.centerX) {
        toEdit.gradient.centerX   = dontforceSet && options.baBehav[ADDSET_GRADIENT_CENTER] ? toEdit.gradient.centerX + mods.gradient.centerX : mods.gradient.centerX;
    }

    if (gradient.centerY) {
        toEdit.gradient.centerY   = dontforceSet && options.baBehav[ADDSET_GRADIENT_CENTER] ? toEdit.gradient.centerY + mods.gradient.centerY : mods.gradient.centerY;
    }

    if (pcvignette.enabled) {
        toEdit.pcvignette.enabled     = mods.pcvignette.enabled;
    }

    if (pcvignette.strength) {
        toEdit.pcvignette.strength  = dontforceSet && options.baBehav[ADDSET_PCVIGNETTE_STRENGTH] ? toEdit.pcvignette.strength + mods.pcvignette.strength : mods.pcvignette.strength;
    }

    if (pcvignette.feather) {
        toEdit.pcvignette.feather   = dontforceSet && options.baBehav[ADDSET_PCVIGNETTE_FEATHER] ? toEdit.pcvignette.feather + mods.pcvignette.feather : mods.pcvignette.feather;
    }

    if (pcvignette.roundness) {
        toEdit.pcvignette.roundness = dontforceSet && options.baBehav[ADDSET_PCVIGNETTE_ROUNDNESS] ? toEdit.pcvignette.roundness + mods.pcvignette.roundness : mods.pcvignette.roundness;
    }

    if (cacorrection.red) {
        toEdit.cacorrection.red   = dontforceSet && options.baBehav[ADDSET_CA] ? toEdit.cacorrection.red + mods.cacorrection.red : mods.cacorrection.red;
    }

    if (cacorrection.blue) {
        toEdit.cacorrection.blue  = dontforceSet && options.baBehav[ADDSET_CA] ? toEdit.cacorrection.blue + mods.cacorrection.blue : mods.cacorrection.blue;
    }

    if (vignetting.amount) {
        toEdit.vignetting.amount  = dontforceSet && options.baBehav[ADDSET_VIGN_AMOUNT] ? toEdit.vignetting.amount + mods.vignetting.amount : mods.vignetting.amount;
    }

    if (vignetting.radius) {
        toEdit.vignetting.radius  = dontforceSet && options.baBehav[ADDSET_VIGN_RADIUS] ? toEdit.vignetting.radius + mods.vignetting.radius : mods.vignetting.radius;
    }

    if (vignetting.strength) {
        toEdit.vignetting.strength = dontforceSet && options.baBehav[ADDSET_VIGN_STRENGTH] ? toEdit.vignetting.strength + mods.vignetting.strength : mods.vignetting.strength;
    }

    if (vignetting.centerX) {
        toEdit.vignetting.centerX = dontforceSet && options.baBehav[ADDSET_VIGN_CENTER] ? toEdit.vignetting.centerX + mods.vignetting.centerX : mods.vignetting.centerX;
    }

    if (vignetting.centerY) {
        toEdit.vignetting.centerY = dontforceSet && options.baBehav[ADDSET_VIGN_CENTER] ? toEdit.vignetting.centerY + mods.vignetting.centerY : mods.vignetting.centerY;
    }

    if (chmixer.enabled) {
        toEdit.chmixer.enabled = mods.chmixer.enabled;
    }

    for (int i = 0; i < 3; i++) {
        if (chmixer.red[i]) {
            toEdit.chmixer.red[i]     = dontforceSet && options.baBehav[ADDSET_CHMIXER] ? toEdit.chmixer.red[i] + mods.chmixer.red[i] : mods.chmixer.red[i];
        }

        if (chmixer.green[i]) {
            toEdit.chmixer.green[i]   = dontforceSet && options.baBehav[ADDSET_CHMIXER] ? toEdit.chmixer.green[i] + mods.chmixer.green[i] : mods.chmixer.green[i];
        }

        if (chmixer.blue[i]) {
            toEdit.chmixer.blue[i]    = dontforceSet && options.baBehav[ADDSET_CHMIXER] ? toEdit.chmixer.blue[i] + mods.chmixer.blue[i] : mods.chmixer.blue[i];
        }
    }

    if (blackwhite.enabled) {
        toEdit.blackwhite.enabled         = mods.blackwhite.enabled;
    }

    if (blackwhite.method) {
        toEdit.blackwhite.method          = mods.blackwhite.method;
    }

    if (blackwhite.luminanceCurve) {
        toEdit.blackwhite.luminanceCurve  = mods.blackwhite.luminanceCurve;
    }

    if (blackwhite.setting) {
        toEdit.blackwhite.setting         = mods.blackwhite.setting;
    }

    if (blackwhite.filter) {
        toEdit.blackwhite.filter          = mods.blackwhite.filter;
    }

    if (blackwhite.mixerRed) {
        toEdit.blackwhite.mixerRed            = dontforceSet && options.baBehav[ADDSET_BLACKWHITE_HUES] ? toEdit.blackwhite.mixerRed + mods.blackwhite.mixerRed : mods.blackwhite.mixerRed;
    }

    if (blackwhite.mixerGreen) {
        toEdit.blackwhite.mixerGreen      = dontforceSet && options.baBehav[ADDSET_BLACKWHITE_HUES] ? toEdit.blackwhite.mixerGreen + mods.blackwhite.mixerGreen : mods.blackwhite.mixerGreen;
    }

    if (blackwhite.mixerBlue) {
        toEdit.blackwhite.mixerBlue       = dontforceSet && options.baBehav[ADDSET_BLACKWHITE_HUES] ? toEdit.blackwhite.mixerBlue + mods.blackwhite.mixerBlue : mods.blackwhite.mixerBlue;
    }

    if (blackwhite.gammaRed) {
        toEdit.blackwhite.gammaRed            = dontforceSet && options.baBehav[ADDSET_BLACKWHITE_GAMMA] ? toEdit.blackwhite.gammaRed + mods.blackwhite.gammaRed : mods.blackwhite.gammaRed;
    }

    if (blackwhite.gammaGreen) {
        toEdit.blackwhite.gammaGreen      = dontforceSet && options.baBehav[ADDSET_BLACKWHITE_GAMMA] ? toEdit.blackwhite.gammaGreen + mods.blackwhite.gammaGreen : mods.blackwhite.gammaGreen;
    }

    if (blackwhite.gammaBlue) {
        toEdit.blackwhite.gammaBlue       = dontforceSet && options.baBehav[ADDSET_BLACKWHITE_GAMMA] ? toEdit.blackwhite.gammaBlue + mods.blackwhite.gammaBlue : mods.blackwhite.gammaBlue;
    }

    if (resize.scale) {
        toEdit.resize.scale   = dontforceSet && options.baBehav[ADDSET_RESIZE_SCALE] ? toEdit.resize.scale + mods.resize.scale : mods.resize.scale;
    }

    if (resize.appliesTo) {
        toEdit.resize.appliesTo = mods.resize.appliesTo;
    }

    if (resize.method) {
        toEdit.resize.method  = mods.resize.method;
    }

    if (resize.dataspec) {
        toEdit.resize.dataspec    = mods.resize.dataspec;
    }

    if (resize.width) {
        toEdit.resize.width   = mods.resize.width;
    }

    if (resize.height) {
        toEdit.resize.height  = mods.resize.height;
    }

    if (resize.enabled) {
        toEdit.resize.enabled     = mods.resize.enabled;
    }

    if (resize.allowUpscaling) {
        toEdit.resize.allowUpscaling = mods.resize.allowUpscaling;
    }

    if (icm.inputProfile) {
        toEdit.icm.inputProfile = mods.icm.inputProfile;
    }

    if (icm.toneCurve) {
        toEdit.icm.toneCurve = mods.icm.toneCurve;
    }

    if (icm.applyLookTable) {
        toEdit.icm.applyLookTable = mods.icm.applyLookTable;
    }

    if (icm.applyBaselineExposureOffset) {
        toEdit.icm.applyBaselineExposureOffset = mods.icm.applyBaselineExposureOffset;
    }

    if (icm.applyHueSatMap) {
        toEdit.icm.applyHueSatMap = mods.icm.applyHueSatMap;
    }

    if (icm.dcpIlluminant) {
        toEdit.icm.dcpIlluminant = mods.icm.dcpIlluminant;
    }

    if (icm.workingProfile) {
        toEdit.icm.workingProfile = mods.icm.workingProfile;
    }

    if (icm.outputProfile) {
        toEdit.icm.outputProfile = mods.icm.outputProfile;
    }

    if (icm.outputIntent) {
        toEdit.icm.outputIntent = mods.icm.outputIntent;
    }

    if (icm.outputBPC) {
        toEdit.icm.outputBPC = mods.icm.outputBPC;
    }

    if (raw.bayersensor.method) {
        toEdit.raw.bayersensor.method           = mods.raw.bayersensor.method;
    }

    if (raw.bayersensor.border) {
        toEdit.raw.bayersensor.border         = mods.raw.bayersensor.border;
    }

    if (raw.bayersensor.imageNum) {
        toEdit.raw.bayersensor.imageNum         = mods.raw.bayersensor.imageNum;
    }

    if (raw.bayersensor.ccSteps) {
        toEdit.raw.bayersensor.ccSteps          = mods.raw.bayersensor.ccSteps;
    }

    if (raw.bayersensor.exBlack0) {
        toEdit.raw.bayersensor.black0           = dontforceSet && options.baBehav[ADDSET_RAWEXPOS_BLACKS] ? toEdit.raw.bayersensor.black0 + mods.raw.bayersensor.black0 : mods.raw.bayersensor.black0;
    }

    if (raw.bayersensor.exBlack1) {
        toEdit.raw.bayersensor.black1           = dontforceSet && options.baBehav[ADDSET_RAWEXPOS_BLACKS] ? toEdit.raw.bayersensor.black1 + mods.raw.bayersensor.black1 : mods.raw.bayersensor.black1;
    }

    if (raw.bayersensor.exBlack2) {
        toEdit.raw.bayersensor.black2           = dontforceSet && options.baBehav[ADDSET_RAWEXPOS_BLACKS] ? toEdit.raw.bayersensor.black2 + mods.raw.bayersensor.black2 : mods.raw.bayersensor.black2;
    }

    if (raw.bayersensor.exBlack3) {
        toEdit.raw.bayersensor.black3           = dontforceSet && options.baBehav[ADDSET_RAWEXPOS_BLACKS] ? toEdit.raw.bayersensor.black3 + mods.raw.bayersensor.black3 : mods.raw.bayersensor.black3;
    }

    if (raw.bayersensor.exTwoGreen) {
        toEdit.raw.bayersensor.twogreen         = mods.raw.bayersensor.twogreen;
    }

    if (raw.bayersensor.dcbIterations) {
        toEdit.raw.bayersensor.dcb_iterations   = mods.raw.bayersensor.dcb_iterations;
    }

    if (raw.bayersensor.dcbEnhance) {
        toEdit.raw.bayersensor.dcb_enhance      = mods.raw.bayersensor.dcb_enhance;
    }

    if (raw.bayersensor.lmmseIterations) {
        toEdit.raw.bayersensor.lmmse_iterations = mods.raw.bayersensor.lmmse_iterations;
    }

    if (raw.bayersensor.dualDemosaicAutoContrast) {
        toEdit.raw.bayersensor.dualDemosaicAutoContrast = mods.raw.bayersensor.dualDemosaicAutoContrast;
    }

    if (raw.bayersensor.dualDemosaicContrast) {
        toEdit.raw.bayersensor.dualDemosaicContrast = mods.raw.bayersensor.dualDemosaicContrast;
    }

    if (raw.bayersensor.pixelShiftMotionCorrectionMethod) {
        toEdit.raw.bayersensor.pixelShiftMotionCorrectionMethod = mods.raw.bayersensor.pixelShiftMotionCorrectionMethod;
    }

    if (raw.bayersensor.pixelShiftEperIso) {
        toEdit.raw.bayersensor.pixelShiftEperIso = mods.raw.bayersensor.pixelShiftEperIso;
    }

    if (raw.bayersensor.pixelShiftSigma) {
        toEdit.raw.bayersensor.pixelShiftSigma = mods.raw.bayersensor.pixelShiftSigma;
    }

    if (raw.bayersensor.pixelShiftShowMotion) {
        toEdit.raw.bayersensor.pixelShiftShowMotion = mods.raw.bayersensor.pixelShiftShowMotion;
    }

    if (raw.bayersensor.pixelShiftShowMotionMaskOnly) {
        toEdit.raw.bayersensor.pixelShiftShowMotionMaskOnly = mods.raw.bayersensor.pixelShiftShowMotionMaskOnly;
    }

    if (raw.bayersensor.pixelShiftHoleFill) {
        toEdit.raw.bayersensor.pixelShiftHoleFill = mods.raw.bayersensor.pixelShiftHoleFill;
    }

    if (raw.bayersensor.pixelShiftMedian) {
        toEdit.raw.bayersensor.pixelShiftMedian = mods.raw.bayersensor.pixelShiftMedian;
    }

    if (raw.bayersensor.pixelShiftGreen) {
        toEdit.raw.bayersensor.pixelShiftGreen = mods.raw.bayersensor.pixelShiftGreen;
    }

    if (raw.bayersensor.pixelShiftBlur) {
        toEdit.raw.bayersensor.pixelShiftBlur = mods.raw.bayersensor.pixelShiftBlur;
    }

    if (raw.bayersensor.pixelShiftSmooth) {
        toEdit.raw.bayersensor.pixelShiftSmoothFactor = mods.raw.bayersensor.pixelShiftSmoothFactor;
    }

    if (raw.bayersensor.pixelShiftEqualBright) {
        toEdit.raw.bayersensor.pixelShiftEqualBright = mods.raw.bayersensor.pixelShiftEqualBright;
    }

    if (raw.bayersensor.pixelShiftEqualBrightChannel) {
        toEdit.raw.bayersensor.pixelShiftEqualBrightChannel = mods.raw.bayersensor.pixelShiftEqualBrightChannel;
    }

    if (raw.bayersensor.pixelShiftNonGreenCross) {
        toEdit.raw.bayersensor.pixelShiftNonGreenCross = mods.raw.bayersensor.pixelShiftNonGreenCross;
    }

    if (raw.bayersensor.pixelShiftDemosaicMethod) {
        toEdit.raw.bayersensor.pixelShiftDemosaicMethod = mods.raw.bayersensor.pixelShiftDemosaicMethod;
    }

    if (raw.bayersensor.greenEq) {
        toEdit.raw.bayersensor.greenthresh      = dontforceSet && options.baBehav[ADDSET_PREPROCESS_GREENEQUIL] ? toEdit.raw.bayersensor.greenthresh + mods.raw.bayersensor.greenthresh : mods.raw.bayersensor.greenthresh;
    }

    if (raw.bayersensor.linenoise) {
        toEdit.raw.bayersensor.linenoise        = dontforceSet && options.baBehav[ADDSET_PREPROCESS_LINEDENOISE] ? toEdit.raw.bayersensor.linenoise + mods.raw.bayersensor.linenoise : mods.raw.bayersensor.linenoise;
    }

    if (raw.bayersensor.linenoiseDirection) {
        toEdit.raw.bayersensor.linenoiseDirection = mods.raw.bayersensor.linenoiseDirection;
    }

    if (raw.bayersensor.pdafLinesFilter) {
        toEdit.raw.bayersensor.pdafLinesFilter = mods.raw.bayersensor.pdafLinesFilter;
    }

    if (raw.xtranssensor.method) {
        toEdit.raw.xtranssensor.method          = mods.raw.xtranssensor.method;
    }

    if (raw.xtranssensor.dualDemosaicAutoContrast) {
        toEdit.raw.xtranssensor.dualDemosaicAutoContrast          = mods.raw.xtranssensor.dualDemosaicAutoContrast;
    }

    if (raw.xtranssensor.dualDemosaicContrast) {
        toEdit.raw.xtranssensor.dualDemosaicContrast          = mods.raw.xtranssensor.dualDemosaicContrast;
    }

    if (raw.xtranssensor.ccSteps) {
        toEdit.raw.xtranssensor.ccSteps         = mods.raw.xtranssensor.ccSteps;
    }

    if (raw.xtranssensor.border) {
        toEdit.raw.xtranssensor.border         = mods.raw.xtranssensor.border;
    }

    if (raw.xtranssensor.exBlackRed) {
        toEdit.raw.xtranssensor.blackred        = dontforceSet && options.baBehav[ADDSET_RAWEXPOS_BLACKS] ? toEdit.raw.xtranssensor.blackred + mods.raw.xtranssensor.blackred : mods.raw.xtranssensor.blackred;
    }

    if (raw.xtranssensor.exBlackGreen) {
        toEdit.raw.xtranssensor.blackgreen      = dontforceSet && options.baBehav[ADDSET_RAWEXPOS_BLACKS] ? toEdit.raw.xtranssensor.blackgreen + mods.raw.xtranssensor.blackgreen : mods.raw.xtranssensor.blackgreen;
    }

    if (raw.xtranssensor.exBlackBlue) {
        toEdit.raw.xtranssensor.blackblue       = dontforceSet && options.baBehav[ADDSET_RAWEXPOS_BLACKS] ? toEdit.raw.xtranssensor.blackblue + mods.raw.xtranssensor.blackblue : mods.raw.xtranssensor.blackblue;
    }

    if (raw.ca_autocorrect) {
        toEdit.raw.ca_autocorrect  = mods.raw.ca_autocorrect;
    }

    if (raw.ca_avoidcolourshift) {
        toEdit.raw.ca_avoidcolourshift  = mods.raw.ca_avoidcolourshift;
    }

    if (raw.caautoiterations) {
        toEdit.raw.caautoiterations           = dontforceSet && options.baBehav[ADDSET_RAWCACORR] ? toEdit.raw.caautoiterations + mods.raw.caautoiterations : mods.raw.caautoiterations;
    }

    if (raw.cared) {
        toEdit.raw.cared           = dontforceSet && options.baBehav[ADDSET_RAWCACORR] ? toEdit.raw.cared + mods.raw.cared : mods.raw.cared;
    }

    if (raw.cablue) {
        toEdit.raw.cablue          = dontforceSet && options.baBehav[ADDSET_RAWCACORR] ? toEdit.raw.cablue + mods.raw.cablue : mods.raw.cablue;
    }

    if (raw.exPos) {
        toEdit.raw.expos           = dontforceSet && options.baBehav[ADDSET_RAWEXPOS_LINEAR] ? toEdit.raw.expos + mods.raw.expos : mods.raw.expos;
    }

    if (raw.hotPixelFilter) {
        toEdit.raw.hotPixelFilter    = mods.raw.hotPixelFilter;
    }

    if (raw.deadPixelFilter) {
        toEdit.raw.deadPixelFilter   = mods.raw.deadPixelFilter;
    }

    if (raw.hotdeadpix_thresh) {
        toEdit.raw.hotdeadpix_thresh = mods.raw.hotdeadpix_thresh;
    }

    if (raw.darkFrame) {
        toEdit.raw.dark_frame        = mods.raw.dark_frame;
    }

    if (raw.df_autoselect) {
        toEdit.raw.df_autoselect     = mods.raw.df_autoselect;
    }

    if (raw.ff_file) {
        toEdit.raw.ff_file            = mods.raw.ff_file;
    }

    if (raw.ff_AutoSelect) {
        toEdit.raw.ff_AutoSelect      = mods.raw.ff_AutoSelect;
    }

    if (raw.ff_BlurRadius) {
        toEdit.raw.ff_BlurRadius      = mods.raw.ff_BlurRadius;
    }

    if (raw.ff_BlurType) {
        toEdit.raw.ff_BlurType        = mods.raw.ff_BlurType;
    }

    if (raw.ff_AutoClipControl) {
        toEdit.raw.ff_AutoClipControl = mods.raw.ff_AutoClipControl;
    }

    if (raw.ff_clipControl) {
        toEdit.raw.ff_clipControl     = dontforceSet && options.baBehav[ADDSET_RAWFFCLIPCONTROL] ? toEdit.raw.ff_clipControl + mods.raw.ff_clipControl : mods.raw.ff_clipControl;
    }

    SETVAL_(dirpyrequalizer.enabled);
    if (dirpyrequalizer.levels) {
        toEdit.dirpyrequalizer.levels = mods.dirpyrequalizer.levels;
        toEdit.dirpyrequalizer.labmasks = mods.dirpyrequalizer.labmasks;
    }
    SETVAL_(dirpyrequalizer.showMask);

    if (filmSimulation.enabled) {
        toEdit.filmSimulation.enabled     = mods.filmSimulation.enabled;
    }

    if (filmSimulation.clutFilename) {
        toEdit.filmSimulation.clutFilename    = mods.filmSimulation.clutFilename;
    }

    if (filmSimulation.strength) {
        toEdit.filmSimulation.strength        = dontforceSet && options.baBehav[ADDSET_FILMSIMULATION_STRENGTH] ? toEdit.filmSimulation.strength + mods.filmSimulation.strength : mods.filmSimulation.strength;
    }

    if (softlight.enabled) {
        toEdit.softlight.enabled     = mods.softlight.enabled;
    }

    if (softlight.strength) {
        toEdit.softlight.strength        = dontforceSet && options.baBehav[ADDSET_SOFTLIGHT_STRENGTH] ? toEdit.softlight.strength + mods.softlight.strength : mods.softlight.strength;
    }

    if (dehaze.enabled) {
        toEdit.dehaze.enabled     = mods.dehaze.enabled;
    }

    if (dehaze.strength) {
        toEdit.dehaze.strength        = dontforceSet && options.baBehav[ADDSET_DEHAZE_STRENGTH] ? toEdit.dehaze.strength + mods.dehaze.strength : mods.dehaze.strength;
    }
    
    if (dehaze.depth) {
        toEdit.dehaze.depth     = mods.dehaze.depth;
    }

    if (dehaze.showDepthMap) {
        toEdit.dehaze.showDepthMap     = mods.dehaze.showDepthMap;
    }

    SETVAL_(grain.enabled);
    SETVAL_(grain.iso);
    SETVAL_(grain.strength);
    SETVAL_(grain.scale);

    SETVAL_(smoothing.enabled);
    if (smoothing.regions) {
        toEdit.smoothing.regions = mods.smoothing.regions;
        toEdit.smoothing.labmasks = mods.smoothing.labmasks;
    }
    SETVAL_(smoothing.showMask);

    SETVAL_(colorcorrection.enabled);
    if (colorcorrection.regions) {
        toEdit.colorcorrection.regions = mods.colorcorrection.regions;
        toEdit.colorcorrection.labmasks = mods.colorcorrection.labmasks;
    }
    SETVAL_(colorcorrection.showMask);

    if (metadata.mode) {
        toEdit.metadata.mode     = mods.metadata.mode;
    }

    // Exif changes are added to the existing ones
    if (exif)
        for (procparams::ExifPairs::const_iterator i = mods.exif.begin(); i != mods.exif.end(); ++i) {
            toEdit.exif[i->first] = i->second;
        }

    // IPTC changes are added to the existing ones
    if (iptc)
        for (procparams::IPTCPairs::const_iterator i = mods.iptc.begin(); i != mods.iptc.end(); ++i) {
            toEdit.iptc[i->first] = i->second;
        }

#undef SETVAL_
#undef ADDSETVAL_
}

bool RAWParamsEdited::BayerSensor::isUnchanged() const
{
    return  method && border && imageNum && dcbIterations && dcbEnhance && lmmseIterations && dualDemosaicAutoContrast && dualDemosaicContrast /*&& allEnhance*/ &&  greenEq
            && pixelShiftMotionCorrectionMethod && pixelShiftEperIso && pixelShiftSigma && pixelShiftShowMotion && pixelShiftShowMotionMaskOnly
            && pixelShiftHoleFill && pixelShiftMedian && pixelShiftNonGreenCross && pixelShiftDemosaicMethod && pixelShiftGreen && pixelShiftBlur && pixelShiftSmooth && pixelShiftEqualBright && pixelShiftEqualBrightChannel
            && linenoise && linenoiseDirection && pdafLinesFilter && exBlack0 && exBlack1 && exBlack2 && exBlack3 && exTwoGreen;
}

bool RAWParamsEdited::XTransSensor::isUnchanged() const
{
    return method && border && exBlackRed && exBlackGreen && exBlackBlue && dualDemosaicAutoContrast && dualDemosaicContrast;
}

bool RAWParamsEdited::isUnchanged() const
{
    return  bayersensor.isUnchanged() && xtranssensor.isUnchanged() && ca_autocorrect && ca_avoidcolourshift && caautoiterations && cared && cablue && hotPixelFilter && deadPixelFilter && hotdeadpix_thresh && darkFrame
            && df_autoselect && ff_file && ff_AutoSelect && ff_BlurRadius && ff_BlurType && exPos && ff_AutoClipControl && ff_clipControl;
}

bool LensProfParamsEdited::isUnchanged() const
{
    return lcMode && lcpFile && useVign && lfLens;
}

