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
#ifndef _EDITID_H_
#define _EDITID_H_


/// @brief List of pipette editing operation
enum EditUniqueID {
    EUID_None,  /// special value (default)

    EUID_DehazeStrength,
    EUID_ToneCurve1,
    EUID_ToneCurve2,
    EUID_ToneCurveSaturation,
    EUID_Lab_LCurve,
    EUID_Lab_aCurve,
    EUID_Lab_bCurve,
    EUID_RGB_R,
    EUID_RGB_G,
    EUID_RGB_B,
    EUID_HSL_H,
    EUID_HSL_S,
    EUID_HSL_V,
    EUID_ColorCorrection_Wheel,
    EUID_LabMasks_H1,
    EUID_LabMasks_C1,
    EUID_LabMasks_L1,
    EUID_LabMasks_H2,
    EUID_LabMasks_C2,
    EUID_LabMasks_L2,
    EUID_LabMasks_H3,
    EUID_LabMasks_C3,
    EUID_LabMasks_L3,
    EUID_LabMasks_H4,
    EUID_LabMasks_C4,
    EUID_LabMasks_L4,
    EUID_LabMasks_DE1, // color correction
    EUID_LabMasks_DE2, // local contrast
    EUID_LabMasks_DE3, // smoothing
    EUID_LabMasks_DE4  // texture boost
};

/// @brief Editing mechanisms
//  TODO: Look out if it has to be a bitfield to allow both mechanisms at a time
enum EditType {
    ET_PIPETTE,  /// Will trigger dedicated methods; can have a geometry list to be displayed, but without "mouse over" capabilities
    ET_OBJECTS   /// The objects are geometrical widgets with "mouse over" capabilities
};

/// @brief Buffer type for ET_PIPETTE type editing
enum BufferType {
    BT_IMAGEFLOAT,          /// Imagefloat buffer type (3 channels of float values)
    BT_LABIMAGE,            /// LabImage buffer type (3 channels of float values)
    BT_SINGLEPLANE_FLOAT    /// All purpose, 1 channel buffer of float values
};

/// @brief Number of object to be handled (for optimization purpose)
enum ObjectMode {
    OM_255,   /// less or equal than 255 objects
    OM_65535  /// less or equal than 65535 objects
};

#endif
