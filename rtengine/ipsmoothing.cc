/* -*- C++ -*-
 *
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2018 Alberto Griggio <alberto.griggio@gmail.com>
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

#include "improcfun.h"
#include "guidedfilter.h"
#include "rt_math.h"
#include "rt_algo.h"
#include "curves.h"
#include "labmasks.h"
#include "sleef.h"
#include "gauss.h"
#include "alignedbuffer.h"
#include <iostream>
#include <queue>

extern Options options;

namespace rtengine {

namespace {

enum class Channel {
    L,
    C,
    LC
};


template <bool use_blending>
void guided_smoothing(array2D<float> &R, array2D<float> &G, array2D<float> &B, const TMatrix &ws, const TMatrix &iws, Channel chan, int radius, float epsilon, int strength, double scale, bool multithread)
{
    const auto rgb2yuv =
        [&](float R, float G, float B, float &Y, float &u, float &v) -> void
        {
            Color::rgb2yuv(R, G, B, Y, u, v, ws);
        };

    const auto yuv2rgb =
        [&](float Y, float u, float v, float &R, float &G, float &B) -> void
        {
            Color::yuv2rgb(Y, u, v, R, G, B, ws);
        };
        
    int r = max(int(round(radius / scale)), 0);
    if (r > 0 && strength > 0) {
        const int W = R.width();
        const int H = R.height();

        array2D<float> iR(W, H, R, ARRAY2D_ALIGNED);
        array2D<float> iG(W, H, G, ARRAY2D_ALIGNED);
        array2D<float> iB(W, H, B, ARRAY2D_ALIGNED);

        const float blend = LIM01(float(strength) / 100.f);
        const bool rgb = (chan == Channel::LC);
        const bool luminance = (chan == Channel::L);
        const bool do_blend = use_blending && strength < 100;

        if (rgb) {
            rtengine::guidedFilterLog(10.f, R, r, epsilon, multithread);
            rtengine::guidedFilterLog(10.f, G, r, epsilon, multithread);
            rtengine::guidedFilterLog(10.f, B, r, epsilon, multithread);
            if (!do_blend) {
                return;
            }
        } else {
            array2D<float> guide(W, H, ARRAY2D_ALIGNED);
#ifdef _OPENMP
#           pragma omp parallel for if (multithread)
#endif
            for (int y = 0; y < H; ++y) {
                for (int x = 0; x < W; ++x) {
                    float l = Color::rgbLuminance(R[y][x], G[y][x], B[y][x], ws);
                    guide[y][x] = xlin2log(max(l, 0.f), 10.f);
                }
            }
            rtengine::guidedFilterLog(guide, 10.f, R, r, epsilon, multithread);
            rtengine::guidedFilterLog(guide, 10.f, G, r, epsilon, multithread);
            rtengine::guidedFilterLog(guide, 10.f, B, r, epsilon, multithread);
        }

#ifdef _OPENMP
        #pragma omp parallel for if (multithread)
#endif
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                float rr = R[y][x];
                float gg = G[y][x];
                float bb = B[y][x];
                float ir = iR[y][x];
                float ig = iG[y][x];
                float ib = iB[y][x];
                
                const float bf = blend;
                if (rgb) {
                    R[y][x] = intp(bf, rr, ir);
                    G[y][x] = intp(bf, gg, ig);
                    B[y][x] = intp(bf, bb, ib);
                } else {
                    float iY, iu, iv;
                    float oY, ou, ov;
                    rgb2yuv(ir, ig, ib, iY, iu, iv);
                    rgb2yuv(rr, gg, bb, oY, ou, ov);
                    if (luminance) {
                        if (do_blend) {
                            oY = intp(bf, oY, iY);
                        }
                        ou = iu;
                        ov = iv;
                    } else {
                        float bump = oY > 1e-5f ? iY / oY : 1.f;
                        if (do_blend) {
                            ou = intp(bf, ou, iu) * bump;
                            ov = intp(bf, ov, iv) * bump;
                        } else {
                            ou *= bump;
                            ov *= bump;
                        }
                        oY = iY;
                    }
                    yuv2rgb(oY, ou, ov, R[y][x], G[y][x], B[y][x]);
                }
            }
        }
    }
}

void find_region(const array2D<float> &mask, int &min_x, int &min_y, int &max_x, int &max_y)
{
    const int W = mask.width();
    const int H = mask.height();
    
    min_x = W - 1;
    min_y = H - 1;
    max_x = 0;
    max_y = 0;

    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            if (mask[y][x] > 0.f) {
                min_x = std::min(min_x, x);
                max_x = std::max(max_x, x);
                min_y = std::min(min_y, y);
                max_y = std::max(max_y, y);
            }
        }
    }

    ++max_x;
    ++max_y;
}


void gaussian_smoothing(array2D<float> &R, array2D<float> &G, array2D<float> &B, float *buf, const TMatrix &ws, Channel chan, double sigma, double scale, bool multithread)
{
    double s = sigma / scale;
    const int W = R.width();
    const int H = R.height();

    const auto blur =
        [&](array2D<float> &a) -> void
        {
#ifdef _OPENMP
#           pragma omp parallel if (multithread)
#endif
            {
                gaussianBlur(a, a, W, H, s, buf);
            }
        };

    if (chan == Channel::LC) {
        blur(R);
        blur(G);
        blur(B);
    } else {
        const bool luminance = (chan == Channel::L);
        array2D<float> iR(W, H, R, ARRAY2D_ALIGNED);
        array2D<float> iG(W, H, G, ARRAY2D_ALIGNED);
        array2D<float> iB(W, H, B, ARRAY2D_ALIGNED);

        blur(R);
        blur(G);
        blur(B);

#ifdef _OPENMP
#       pragma omp parallel for if (multithread)
#endif
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                float iY, iu, iv;
                float oY, ou, ov;
                Color::rgb2yuv(iR[y][x], iG[y][x], iB[y][x], iY, iu, iv, ws);
                Color::rgb2yuv(R[y][x], G[y][x], B[y][x], oY, ou, ov, ws);
                if (luminance) {
                    Color::yuv2rgb(oY, iu, iv, R[y][x], G[y][x], B[y][x], ws);
                } else {
                    Color::yuv2rgb(iY, ou, ov, R[y][x], G[y][x], B[y][x], ws);
                }
            }
        }
    }
}

} // namespace


namespace denoise {

void denoiseGuidedSmoothing(ImProcData &im, Imagefloat *rgb)
{
    if (!im.params->denoise.smoothingEnabled || im.params->denoise.guidedChromaRadius == 0) {
        return;
    }

    rgb->normalizeFloatTo1(im.multiThread);

    const int W = rgb->getWidth();
    const int H = rgb->getHeight();
    array2D<float> R(W, H, rgb->r.ptrs, ARRAY2D_BYREFERENCE);
    array2D<float> G(W, H, rgb->g.ptrs, ARRAY2D_BYREFERENCE);
    array2D<float> B(W, H, rgb->b.ptrs, ARRAY2D_BYREFERENCE);

    TMatrix ws = ICCStore::getInstance()->workingSpaceMatrix(im.params->icm.workingProfile);
    TMatrix iws = ICCStore::getInstance()->workingSpaceInverseMatrix(im.params->icm.workingProfile);

    const float c_eps = 0.001f;

    guided_smoothing<false>(R, G, B, ws, iws, Channel::C, im.params->denoise.guidedChromaRadius, c_eps, 100, im.scale, im.multiThread);
    
    rgb->normalizeFloatTo65535(im.multiThread);
}


} // namespace denoise


bool ImProcFunctions::guidedSmoothing(Imagefloat *rgb)
{
    PlanarWhateverData<float> *editWhatever = nullptr;
    EditUniqueID eid = pipetteBuffer ? pipetteBuffer->getEditID() : EUID_None;

    if ((eid == EUID_LabMasks_H3 || eid == EUID_LabMasks_C3 || eid == EUID_LabMasks_L3) && pipetteBuffer->getDataProvider()->getCurrSubscriber()->getPipetteBufferType() == BT_SINGLEPLANE_FLOAT) {
        editWhatever = pipetteBuffer->getSinglePlaneBuffer();
    }

    if (eid == EUID_LabMasks_DE3) {
        if (getDeltaEColor(rgb, deltaE.x, deltaE.y, offset_x, offset_y, full_width, full_height, scale, deltaE.L, deltaE.C, deltaE.H)) {
            deltaE.ok = true;
        }
    }
        
    if (params->smoothing.enabled) {
        if (editWhatever) {
            LabMasksEditID id = static_cast<LabMasksEditID>(int(eid) - EUID_LabMasks_H3);
            fillPipetteLabMasks(rgb, editWhatever, id, multiThread);
        }
        
        int n = params->smoothing.regions.size();
        int show_mask_idx = params->smoothing.showMask;
        if (show_mask_idx >= n || (cur_pipeline != Pipeline::PREVIEW && cur_pipeline != Pipeline::OUTPUT)) {
            show_mask_idx = -1;
        }
        std::vector<array2D<float>> mask(n);
        if (!generateLabMasks(rgb, params->smoothing.labmasks, offset_x, offset_y, full_width, full_height, scale, multiThread, show_mask_idx, nullptr, &mask)) {
            return true; // show mask is active, nothing more to do
        }

        const int W = rgb->getWidth();
        const int H = rgb->getHeight();

        Imagefloat working;
        rgb->setMode(Imagefloat::Mode::RGB, multiThread);
        rgb->normalizeFloatTo1(multiThread);

        TMatrix ws = ICCStore::getInstance()->workingSpaceMatrix(params->icm.workingProfile);
        TMatrix iws = ICCStore::getInstance()->workingSpaceInverseMatrix(params->icm.workingProfile);

        for (int i = 0; i < n; ++i) {
            if (!params->smoothing.labmasks[i].enabled) {
                continue;
            }

            int min_x, min_y, max_x, max_y;
            const auto &blend = mask[i];

            find_region(blend, min_x, min_y, max_x, max_y);
            int ww = max_x - min_x;
            int hh = max_y - min_y;

            if (ww * hh < (W * H) / 2) {
                working.allocate(ww, hh);
#ifdef _OPENMP
#               pragma omp parallel for if (multiThread)
#endif
                for (int y = min_y; y < max_y; ++y) {
                    int yy = y - min_y;
                    for (int x = min_x; x < max_x; ++x) {
                        int xx = x - min_x;
                        working.r(yy, xx) = rgb->r(y, x);
                        working.g(yy, xx) = rgb->g(y, x);
                        working.b(yy, xx) = rgb->b(y, x);
                    }
                }
            } else {
                min_x = 0;
                min_y = 0;
                max_x = W;
                max_y = H;
                ww = W;
                hh = H;

                rgb->copyTo(&working);
            }

            auto &r = params->smoothing.regions[i];
            array2D<float> R(ww, hh, working.r.ptrs, ARRAY2D_BYREFERENCE);
            array2D<float> G(ww, hh, working.g.ptrs, ARRAY2D_BYREFERENCE);
            array2D<float> B(ww, hh, working.b.ptrs, ARRAY2D_BYREFERENCE);

            Channel ch = Channel(int(r.channel));
            if (r.mode == SmoothingParams::Region::Mode::GAUSSIAN) {
                // do a gaussian blur here
                AlignedBuffer<float> buf(ww * hh);
                for (int i = 0; i < r.iterations; ++i) {
                    gaussian_smoothing(R, G, B, buf.data, ws, ch, r.sigma, scale, multiThread);
                }
            } else {
                const float epsilon = std::max(0.001f * std::pow(2, -r.epsilon), 1e-6);
                for (int i = 0; i < r.iterations; ++i) {
                    guided_smoothing<false>(R, G, B, ws, iws, ch, r.radius, epsilon, 100, scale, multiThread);
                }
            }
            
#ifdef _OPENMP
#           pragma omp parallel for if (multiThread)
#endif
            for (int y = min_y; y < max_y; ++y) {
                int yy = y - min_y;
                for (int x = min_x; x < max_x; ++x) {
                    int xx = x - min_x;
                    rgb->r(y, x) = intp(blend[y][x], working.r(yy, xx), rgb->r(y, x));
                    rgb->g(y, x) = intp(blend[y][x], working.g(yy, xx), rgb->g(y, x));
                    rgb->b(y, x) = intp(blend[y][x], working.b(yy, xx), rgb->b(y, x));
                }
            }
        }

        rgb->normalizeFloatTo65535(multiThread);
    } else if (editWhatever) {
        editWhatever->fill(0.f);
    }

    return false;
}

} // namespace rtengine
