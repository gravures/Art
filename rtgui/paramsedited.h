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
#ifndef _PARAMEDITED_H_
#define _PARAMEDITED_H_

#include <glibmm.h>
#include <vector>
#include "../rtengine/procparams.h"
#include "../rtengine/rtengine.h"

class GeneralParamsEdited
{

public:
    bool rank;
    bool colorlabel;
    bool intrash;
};

class ToneCurveParamsEdited
{

public:
    bool curve;
    bool curve2;
    bool curveMode;
    bool curveMode2;
    bool brightness;
    bool black;
    bool contrast;
    bool saturation;
    bool shcompr;
    bool hlcompr;
    bool hlcomprthresh;
    bool autoexp;
    bool clip;
    bool expcomp;
    bool hrenabled;
    bool method;
    bool histmatching;
    bool fromHistMatching;
    bool clampOOG;
};


class LCurveParamsEdited
{
public:
    bool enabled;
    bool brightness;
    bool contrast;
    bool chromaticity;
    bool avoidcolorshift;
    bool rstprotection;
    bool lcurve;
    bool acurve;
    bool bcurve;
    bool lcredsk;
    bool cccurve;
    bool chcurve;
    bool lhcurve;
    bool hhcurve;
    bool lccurve;
    bool clcurve;
};


class LocalContrastParamsEdited
{
public:
    bool enabled;
    bool mode;
    bool radius;
    bool amount;
    bool darkness;
    bool lightness;
    bool contrast;
    bool curve;
};


class RGBCurvesParamsEdited
{

public:
    bool enabled;
    bool lumamode;
    bool rcurve;
    bool gcurve;
    bool bcurve;
};


class SharpenMicroParamsEdited
{
public :
    bool enabled;
    bool matrix;
    bool amount;
    bool contrast;
    bool uniformity;

};

class SharpeningParamsEdited
{

public:
    bool enabled;
    bool contrast;
    bool blurradius;
    bool radius;
    bool amount;
    bool threshold;
    bool edgesonly;
    bool edges_radius;
    bool edges_tolerance;
    bool halocontrol;
    bool halocontrol_amount;

    bool method;
    bool deconvamount;
    bool deconvradius;
    bool deconviter;
    bool deconvdamping;
};


class WBParamsEdited
{

public:
    bool enabled;
    bool method;
    bool temperature;
    bool green;
    bool equal;
    bool tempBias;
};


class DefringeParamsEdited
{

public:
    bool enabled;
    bool radius;
    bool threshold;
    bool huecurve;
};

class ImpulseDenoiseParamsEdited
{

public:
    bool enabled;
    bool thresh;
};


class DenoiseParamsEdited
{

public:
    bool enabled;
    bool colorSpace;
    bool aggressive;
    bool gamma;
    bool luminanceMethod;
    bool luminance;
    bool luminanceCurve;
    bool luminanceDetail;
    bool chrominanceMethod;
    bool chrominanceAutoFactor;
    bool chrominance;
    bool chrominanceCurve;
    bool chrominanceRedGreen;
    bool chrominanceBlueYellow;
    bool smoothingEnabled;
    bool smoothingMethod;
    bool medianType;
    bool medianMethod;
    bool medianIterations;
    bool guidedLumaRadius;
    bool guidedLumaStrength;
    bool guidedChromaRadius;
    bool guidedChromaStrength;
};

class EPDParamsEdited
{
public:
    bool enabled;
    bool regions;
    bool showMask;
    /* bool strength; */
    /* bool gamma; */
    /* bool edgeStopping; */
    /* bool scale; */
    /* bool reweightingIterates; */
};


class LogEncodingParamsEdited
{
public:
    bool enabled;
    bool autocompute;
    bool autogray;
    bool sourceGray;
    bool targetGray;
    bool blackEv;
    bool whiteEv;
    bool detail;
};


class FattalToneMappingParamsEdited
{
public:
    bool enabled;
    bool threshold;
    bool amount;
    bool anchor;
};


class SHParamsEdited
{

public:
    bool enabled;
    bool highlights;
    bool htonalwidth;
    bool shadows;
    bool stonalwidth;
    bool radius;
    bool lab;
};


class ToneEqualizerParamsEdited
{
public:
    bool enabled;
    bool bands;
    bool detail;
};


class CropParamsEdited
{

public:
    bool enabled;
    bool x;
    bool y;
    bool w;
    bool h;
    bool fixratio;
    bool ratio;
    bool orientation;
    bool guide;
};

class CoarseTransformParamsEdited
{

public:
    bool rotate;
    bool hflip;
    bool vflip;
};

class CommonTransformParamsEdited
{

public:
    bool autofill;
};

class RotateParamsEdited
{

public:
    bool degree;
};

class DistortionParamsEdited
{

public:
    bool amount;
};

class LensProfParamsEdited
{
public:
    bool lcpFile, useDist, useVign, useCA;
    bool useLensfun, lfAutoMatch, lfCameraMake, lfCameraModel, lfLens;
    bool lcMode;

    bool isUnchanged() const;
};

class PerspectiveParamsEdited
{

public:
    bool horizontal;
    bool vertical;
};

class GradientParamsEdited
{

public:
    bool enabled;
    bool degree;
    bool feather;
    bool strength;
    bool centerX;
    bool centerY;
};

class PCVignetteParamsEdited
{

public:
    bool enabled;
    bool strength;
    bool feather;
    bool roundness;
};

class VignettingParamsEdited
{

public:
    bool amount;
    bool radius;
    bool strength;
    bool centerX;
    bool centerY;
};

class ChannelMixerParamsEdited
{

public:
    bool enabled;
    bool red[3];
    bool green[3];
    bool blue[3];

};
class BlackWhiteParamsEdited
{

public:
    bool enabled;
    bool method;
    bool filter;
    bool setting;
    bool mixerRed;
    bool mixerGreen;
    bool mixerBlue;
    bool gammaRed;
    bool gammaGreen;
    bool gammaBlue;
    bool luminanceCurve;
};

class CACorrParamsEdited
{

public:
    bool red;
    bool blue;
};
/*
class HRecParamsEdited {

    public:
        bool enabled;
        bool method;
};
*/
class ResizeParamsEdited
{

public:
    bool scale;
    bool appliesTo;
    bool method;
    bool dataspec;
    bool width;
    bool height;
    bool enabled;
    bool allowUpscaling;
};

class ColorManagementParamsEdited
{

public:
    bool inputProfile;
    bool toneCurve;
    bool applyLookTable;
    bool applyBaselineExposureOffset;
    bool applyHueSatMap;
    bool dcpIlluminant;

    bool workingProfile;
    bool workingTRC;
    bool workingTRCGamma;
    bool workingTRCSlope;

    bool outputProfile;
    bool outputIntent;
    bool outputBPC;
};


class DirPyrEqualizerParamsEdited
{

public:
    bool enabled;
    bool levels;
    bool showMask;
    // bool gamutlab;
    // bool mult[6];
    // bool cbdlMethod;
    // bool threshold;
    // bool skinprotect;
    // bool hueskin;
    //     bool algo;
};

class FilmSimulationParamsEdited
{
public:
    bool enabled;
    bool clutFilename;
    bool strength;
};

class SoftLightParamsEdited
{
public:
    bool enabled;
    bool strength;
};

class DehazeParamsEdited
{
public:
    bool enabled;
    bool strength;
    bool showDepthMap;
    bool depth;
};


class GrainParamsEdited
{
public:
    bool enabled;
    bool iso;
    bool strength;
    bool scale;
};


class GuidedSmoothingParamsEdited
{
public:
    bool enabled;
    bool regions;
    bool showMask;
};


class ColorCorrectionParamsEdited
{
public:
    bool enabled;
    bool regions;
    bool showMask;
};


class RAWParamsEdited
{

public:
    class BayerSensor
    {

    public:
        bool method;
        bool border;
        bool imageNum;
        bool ccSteps;
        bool exBlack0;
        bool exBlack1;
        bool exBlack2;
        bool exBlack3;
        bool exTwoGreen;
        bool dcbIterations;
        bool dcbEnhance;
        bool lmmseIterations;
        bool dualDemosaicAutoContrast;
        bool dualDemosaicContrast;
        bool pixelShiftMotionCorrectionMethod;
        bool pixelShiftEperIso;
        bool pixelShiftSigma;
        bool pixelShiftShowMotion;
        bool pixelShiftShowMotionMaskOnly;
        bool pixelShiftHoleFill;
        bool pixelShiftMedian;
        bool pixelShiftGreen;
        bool pixelShiftBlur;
        bool pixelShiftSmooth;
        bool pixelShiftEqualBright;
        bool pixelShiftEqualBrightChannel;
        bool pixelShiftNonGreenCross;
        bool pixelShiftDemosaicMethod;

        //bool allEnhance;
        bool greenEq;
        bool linenoise;
        bool linenoiseDirection;
        bool pdafLinesFilter;

        bool isUnchanged() const;
    };

    class XTransSensor
    {

    public:
        bool method;
        bool dualDemosaicAutoContrast;
        bool dualDemosaicContrast;
        bool border;
        bool ccSteps;
        bool exBlackRed;
        bool exBlackGreen;
        bool exBlackBlue;

        bool isUnchanged() const;
    };

    BayerSensor bayersensor;
    XTransSensor xtranssensor;

    bool ca_autocorrect;
    bool ca_avoidcolourshift;
    bool caautoiterations;
    bool cared;
    bool cablue;
    bool hotPixelFilter;
    bool deadPixelFilter;
    bool hotdeadpix_thresh;
    bool darkFrame;
    bool df_autoselect;
    bool ff_file;
    bool ff_AutoSelect;
    bool ff_BlurRadius;
    bool ff_BlurType;
    bool ff_AutoClipControl;
    bool ff_clipControl;
    bool exPos;

    bool isUnchanged() const;
};


class MetaDataParamsEdited
{
public:
    bool mode;
};


class ParamsEdited
{

public:
    GeneralParamsEdited           general;
    ToneCurveParamsEdited         toneCurve;
    LCurveParamsEdited            labCurve;
    LocalContrastParamsEdited     localContrast;
    RGBCurvesParamsEdited         rgbCurves;
    SharpeningParamsEdited        sharpening;
    SharpeningParamsEdited        prsharpening;
    SharpenMicroParamsEdited      sharpenMicro;
    WBParamsEdited                wb;
    DefringeParamsEdited          defringe;
    DenoiseParamsEdited           denoise;
    EPDParamsEdited               epd;
    FattalToneMappingParamsEdited fattal;
    LogEncodingParamsEdited       logenc;
    ImpulseDenoiseParamsEdited    impulseDenoise;
    SHParamsEdited                sh;
    ToneEqualizerParamsEdited     toneEqualizer;
    CropParamsEdited              crop;
    CoarseTransformParamsEdited   coarse;
    CommonTransformParamsEdited   commonTrans;
    RotateParamsEdited            rotate;
    DistortionParamsEdited        distortion;
    LensProfParamsEdited          lensProf;
    PerspectiveParamsEdited       perspective;
    GradientParamsEdited          gradient;
    PCVignetteParamsEdited        pcvignette;
    CACorrParamsEdited            cacorrection;
    VignettingParamsEdited        vignetting;
    ChannelMixerParamsEdited      chmixer;
    BlackWhiteParamsEdited        blackwhite;
    ResizeParamsEdited            resize;
    ColorManagementParamsEdited   icm;
    RAWParamsEdited               raw;
    DirPyrEqualizerParamsEdited   dirpyrequalizer;
    FilmSimulationParamsEdited    filmSimulation;
    SoftLightParamsEdited         softlight;
    DehazeParamsEdited            dehaze;
    GrainParamsEdited             grain;
    GuidedSmoothingParamsEdited   smoothing;
    ColorCorrectionParamsEdited   colorcorrection;
    MetaDataParamsEdited          metadata;
    bool                          exif;
    bool                          iptc;

    explicit ParamsEdited(bool value = false);

    void set(bool v);
    void initFrom(const std::vector<rtengine::procparams::ProcParams>& src);
    void combine(rtengine::procparams::ProcParams& toEdit, const rtengine::procparams::ProcParams& mods, bool forceSet);
};
#endif
