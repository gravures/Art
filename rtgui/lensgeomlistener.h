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
#pragma once

namespace rtengine {
class ControlLine;
class ProcEvent;
} // namespace rtengine


class LensGeomListener {
public:
    virtual ~LensGeomListener() = default;
    virtual void straightenRequested() = 0;
    virtual void autoCropRequested() = 0;
    virtual double autoDistorRequested() = 0;
    virtual void autoPerspectiveRequested(
        bool horiz, bool vert,
        double &angle, double &horizontal, double &vertical, double &shear,
        const std::vector<rtengine::ControlLine> *lines=nullptr) = 0;
    virtual void updateTransformPreviewRequested (rtengine::ProcEvent event, bool render_perspective) = 0;
};

