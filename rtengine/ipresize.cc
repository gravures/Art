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

#include "improcfun.h"

#include "alignedbuffer.h"
#include "opthelper.h"
#include "rt_math.h"
#include "sleef.h"

//#define PROFILE

#ifdef PROFILE
#   include <iostream>
#endif


namespace rtengine
{

static inline float Lanc (float x, float a)
{
    if (x * x < 1e-6f) {
        return 1.0f;
    } else if (x * x > a * a) {
        return 0.0f;
    } else {
        x = static_cast<float> (rtengine::RT_PI) * x;
        return a * xsinf (x) * xsinf (x / a) / (x * x);
    }
}


void ImProcFunctions::Lanczos(Imagefloat *src, Imagefloat *dst, float scale)
{
    auto mode = src->mode();
    src->setMode(Imagefloat::Mode::LAB, multiThread);
    dst->assignMode(Imagefloat::Mode::LAB);

    const int sW = src->getWidth();
    const int sH = src->getHeight();
    const int dW = dst->getWidth();
    const int dH = dst->getHeight();
    
    const float delta = 1.0f / scale;
    const float a = 3.0f;
    const float sc = min (scale, 1.0f);
    const int support = static_cast<int> (2.0f * a / sc) + 1;

    // storage for precomputed parameters for horizontal interpolation
    float* const wwh = new float[support * dW];
    int* const jj0 = new int[dW];
    int* const jj1 = new int[dW];

    const auto sL = src->g.ptrs;
    const auto sa = src->r.ptrs;
    const auto sb = src->b.ptrs;

    auto dL = dst->g.ptrs;
    auto da = dst->r.ptrs;
    auto db = dst->b.ptrs;

    // Phase 1: precompute coefficients for horizontal interpolation
    for (int j = 0; j < dW; j++) {

        // x coord of the center of pixel on src image
        float x0 = (static_cast<float> (j) + 0.5f) * delta - 0.5f;

        // weights for interpolation in horizontal direction
        float * w = wwh + j * support;

        // sum of weights used for normalization
        float ws = 0.0f;

        jj0[j] = max (0, static_cast<int> (floorf (x0 - a / sc)) + 1);
        jj1[j] = min (sW, static_cast<int> (floorf (x0 + a / sc)) + 1);

        // calculate weights
        for (int jj = jj0[j]; jj < jj1[j]; jj++) {
            int k = jj - jj0[j];
            float z = sc * (x0 - static_cast<float> (jj));
            w[k] = Lanc (z, a);
            ws += w[k];
        }

        // normalize weights
        for (int k = 0; k < support; k++) {
            w[k] /= ws;
        }
    }

#ifdef _OPENMP
    #pragma omp parallel
#endif
    {
        // temporal storage for vertically-interpolated row of pixels
        AlignedBuffer<float> aligned_buffer_ll(sW);
        AlignedBuffer<float> aligned_buffer_la(sW);
        AlignedBuffer<float> aligned_buffer_lb(sW);
        float* const lL = aligned_buffer_ll.data;
        float* const la = aligned_buffer_la.data;
        float* const lb = aligned_buffer_lb.data;
        // weights for interpolation in y direction
        float w[support] ALIGNED64;
        memset(w, 0, sizeof(w));

        // Phase 2: do actual interpolation
#ifdef _OPENMP
        #pragma omp for
#endif

        for (int i = 0; i < dH; i++) {
            // y coord of the center of pixel on src image
            float y0 = (static_cast<float> (i) + 0.5f) * delta - 0.5f;

            // sum of weights used for normalization
            float ws = 0.0f;

            int ii0 = max (0, static_cast<int> (floorf (y0 - a / sc)) + 1);
            int ii1 = min (sH, static_cast<int> (floorf (y0 + a / sc)) + 1);

            // calculate weights for vertical interpolation
            for (int ii = ii0; ii < ii1; ii++) {
                int k = ii - ii0;
                float z = sc * (y0 - static_cast<float> (ii));
                w[k] = Lanc (z, a);
                ws += w[k];
            }

            // normalize weights
            for (int k = 0; k < support; k++) {
                w[k] /= ws;
            }

            // Do vertical interpolation. Store results.
#ifdef __SSE2__
            int j;
            __m128 Lv, av, bv, wkv;

            for (j = 0; j < sW - 3; j += 4) {
                Lv = _mm_setzero_ps();
                av = _mm_setzero_ps();
                bv = _mm_setzero_ps();

                for (int ii = ii0; ii < ii1; ii++) {
                    int k = ii - ii0;
                    wkv = _mm_set1_ps (w[k]);
                    Lv += wkv * LVFU (sL[ii][j]);
                    av += wkv * LVFU (sa[ii][j]);
                    bv += wkv * LVFU (sb[ii][j]);
                }

                STVF (lL[j], Lv);
                STVF (la[j], av);
                STVF (lb[j], bv);
            }

#else
            int j = 0;
#endif

            for (; j < sW; j++) {
                float L = 0.0f, a = 0.0f, b = 0.0f;

                for (int ii = ii0; ii < ii1; ii++) {
                    int k = ii - ii0;

                    L += w[k] * sL[ii][j];
                    a += w[k] * sa[ii][j];
                    b += w[k] * sb[ii][j];
                }

                lL[j] = L;
                la[j] = a;
                lb[j] = b;
            }

            // Do horizontal interpolation
            for (int j = 0; j < dW; j++) {

                float * wh = wwh + support * j;

                float L = 0.0f, a = 0.0f, b = 0.0f;

                for (int jj = jj0[j]; jj < jj1[j]; jj++) {
                    int k = jj - jj0[j];

                    L += wh[k] * lL[jj];
                    a += wh[k] * la[jj];
                    b += wh[k] * lb[jj];
                }

                dL[i][j] = L;
                da[i][j] = a;
                db[i][j] = b;
            }
        }
    }
    delete[] jj0;
    delete[] jj1;
    delete[] wwh;

    dst->setMode(mode, multiThread);
}


float ImProcFunctions::resizeScale (const ProcParams* params, int fw, int fh, int &imw, int &imh)
{
    imw = fw;
    imh = fh;

    if (!params || !params->resize.enabled) {
        return 1.0;
    }

    // get the resize parameters
    int refw, refh;
    double dScale;

    if (params->crop.enabled && params->resize.appliesTo == "Cropped area") {
        // the resize values applies to the crop dimensions
        refw = params->crop.w;
        refh = params->crop.h;
    } else {
        // the resize values applies to the image dimensions
        // if a crop exists, it will be resized to the calculated scale
        refw = fw;
        refh = fh;
    }

    int r_width = params->resize.get_width();
    int r_height = params->resize.get_height();

    switch (params->resize.dataspec) {
        case (1):
            // Width
            dScale = (double)r_width / (double)refw;
            break;

        case (2):
            // Height
            dScale = (double)r_height / (double)refh;
            break;

        case (3):

            // FitBox
            if ((double)refw / (double)refh > (double)r_width / (double)r_height) {
                dScale = (double)r_width / (double)refw;
            } else {
                dScale = (double)r_height / (double)refh;
            }
            dScale = (dScale > 1.0 && !params->resize.allowUpscaling) ? 1.0 : dScale;

            break;

        default:
            // Scale
            dScale = params->resize.scale;
            break;
    }

    if (fabs (dScale - 1.0) <= 1e-5) {
        return 1.0;
    }

    if (params->crop.enabled && params->resize.appliesTo == "Full image") {
        imw = params->crop.w;
        imh = params->crop.h;
    } else {
        imw = refw;
        imh = refh;
    }

    imw = (int) ( (double)imw * dScale + 0.5 );
    imh = (int) ( (double)imh * dScale + 0.5 );
    return (float)dScale;
}

void ImProcFunctions::resize (Imagefloat* src, Imagefloat* dst, float dScale)
{
#ifdef PROFILE
    time_t t1 = clock();
#endif

    Lanczos (src, dst, dScale);

#ifdef PROFILE
    time_t t2 = clock();
    std::cout << "Resize: "
              << (float) (t2 - t1) / CLOCKS_PER_SEC << std::endl;
#endif
}

}
