/*
 * extraction.c
 *
 *  Created on: Oct 3, 2017
 *      Author: ferdinandvonhagen
 */
#include "extraction.h"
#include "loop.h"
#include <math.h>
#include <arm_math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

bool calculate_max_peak(point* lastp, point *p1, point *p2, point *p3, point *curr, point* lastMin, int thr_v, int thr_h) {
    bool res = false;
    if(curr->y > p3->y && p3->x != -1) {
        if(p1->y + thr_v < p2->y && p3->y + thr_v < p2->y && lastp->x + thr_h < p2->x) {
            lastp->x = p2->x;
            lastp->y = p2->y;
            lastMin->y = p1->y;
            lastMin->x = p1->x;

            res = true;
        }

        p1->y = p3->y;
        p1->x = p3->x;
        p2->y = p3->y;
        p2->x = p3->x;
        p3->x = -1;
    }

    if(curr->y < p2->y) {
        p3->y = curr->y;
        p3->x = curr->x;
    }

    if(p1->y > curr->y && p3->x == -1) {
        p1->y = curr->y;
        p1->x = curr->x;
        p2->y = curr->y;
        p2->x = curr->x;
    }

    if(p2->y < curr->y && p3->x == -1) {
        p2->y = curr->y;
        p2->x = curr->x;
    }

    return res;
}

int gsr[64];
int gsrp, gsrsum;
int smoothgsr(int gsrd) {
    if(gsrp == 64) {
        gsrp = 0;
    }

    gsrsum += gsrd - gsr[gsrp];
    gsr[gsrp] = gsrd;
    ++gsrp;

    return gsrsum / 64;
}

int ecgsum, ecgp;
int ecg[32];
int maxecgp;
int maxecg[128];
int maxecgd = 0;
int smoothecg(int ecg0d, int ecg1d) {
    if(ecgp == 32) {
        ecgp = 0;
    }

    if(maxecgp == 128) {
        maxecgp = 0;
    }

    if(ecg0d > ecg1d) {
        maxecg[maxecgp++] = ecg0d;
    } else {
        maxecg[maxecgp++] = ecg1d;
    }


    int i;
    maxecgd = 0;
    for(i = 0; i < 128; i = i + 4) {
        maxecgd = max(maxecgd, max(maxecg[i], max(maxecg[i + 1], max(maxecg[i + 2], maxecg[i + 3]))));
    }

    ecgsum += ecg0d - ecg[ecgp];
    ecg[ecgp++] = ecg0d;
    ecgsum += ecg1d - ecg[ecgp];
    ecg[ecgp++] = ecg1d;

    return ecgsum / 32;
}

int lastp, rrdiffp;
int rrdiff[1024];
bool peakdetection(int ecgavg, int ecg0, int ecg1, int mtime) {
    int offset = (maxecgd - ecgavg) / 2;
    offset += offset / 4;
    if ((ecg0 - offset > ecgavg || ecg1 - offset > ecgavg) && (mtime - lastp) > 32) {
        rrdiff[rrdiffp++] = (mtime - lastp);
        lastp = mtime;
        return true;
    }

    return false;
}

point p1, p2, p3, lastP, curr, lastMin;
int totalStartle, totalDiffH, totalDiffV, meangsr;
bool gsrdetection(int gsr, int mtime) {
    meangsr += gsr;

    curr.x = mtime;
    curr.y = gsr;

    if(calculate_max_peak(&lastP, &p1, &p2, &p3, &curr, &lastMin, 200, 2)) {
        ++totalStartle;
        totalDiffH += lastP.x - lastMin.x;
        totalDiffV += lastP.y = lastMin.y;
        return true;
    } else {
        return false;
    }
}

void resetExtraction(int gsr, int mtime) {
    p1.x = mtime;
    p1.y = gsr;
    p2.x = mtime;
    p2.y = gsr;
    p3.x = -1;
    lastP.x = mtime;
    lastP.y = gsr;
    totalStartle = 0;
    totalDiffV = 0;
    totalDiffH = 0;
    meangsr = 0;

    rrdiffp = 0;
    lastp = 0;
}

//float features[8];
float scaling[8][16];
float mean[8];
int scalep;
bool init = true;
void extractfeatures2(int mtime, float *features) {
    int nn50 = 0;
    int lastrr = rrdiff[0];
    int meanrr = 0;
    int rmssd = 0;
    int i;

    loop(rrdiff, rrdiffp, &nn50, &meanrr, &rmssd);

    /**
    for(i = 0; i < rrdiffp; ++i) {
        // NN50 detection
        if(abs(rrdiff[i] - lastrr) > 6) {
            ++nn50;
        }
        lastrr = rrdiff[i];

        // MEANRR
        meanrr += rrdiff[i];

        // RMSSD
        rmssd += rrdiff[i] * rrdiff[i];
    }
    */

    meanrr = meanrr / rrdiffp;

    long sdsd;
    arm_offset_q31(&rrdiff, -meanrr, &rrdiff, rrdiffp);
    arm_power_q31(&rrdiff, rrdiffp, &sdsd);

    features[0] = (float)meanrr;
    features[1] = (float)meangsr/(float)mtime;
    features[2] = (float)totalStartle;
    features[3] = (float)nn50;

    arm_sqrt_f32((float)rmssd / (float)rrdiffp, &features[4]);
    arm_sqrt_f32((float)sdsd / (float)rrdiffp, &features[5]);

    features[6] = (float)totalDiffH;
    features[7] = (float)totalDiffV;

    if(scalep == 16) {
        scalep = 0;
    }

    if(init) {
        for(i = 0; i < 16; ++i) {
            arm_fill_f32(features[i], scaling[i], 16);
        }
        arm_copy_f32(features, mean, 8);
        arm_scale_f32(mean, 16.0f, mean, 8);
        init = false;
    }

    for(i = 0; i < 8; ++i) {
        mean[i] += features[i] - scaling[i][scalep];
        scaling[i][scalep] = features[i];
        float m = mean[i] / 16.0f;
        features[i] = features[i] - m;
        float mx, mn, d;

        arm_max_f32(&scaling[i], 16, &mx, &d);
        arm_min_f32(&scaling[i], 16, &mn, &d);

        if((mx - mn) != 0.0f) {
            features[i] = 2 * features[i] / (mx - mn);
        }
    }
}


void extractfeatures(int *feat, int mtime) {
    int nn50 = 0;
    int lastrr = rrdiff[0];
    int meanrr = 0;
    int rmssd = 0;
    int i;
    for(i = 0; i < rrdiffp; ++i) {
        // NN50 detection
        if(abs(rrdiff[i] - lastrr) > 12) {
            ++nn50;
        }
        lastrr = rrdiff[i];

        // MEANRR
        meanrr += rrdiff[i];

        // RMSSD
        rmssd += rrdiff[i] * rrdiff[i];
    }

    meanrr = meanrr / rrdiffp;
    rmssd = sqrt(rmssd / rrdiffp);

    int sdsd = 0;
    for(i = 0; i < rrdiffp; ++i) {
        // SDSD
        sdsd += (rrdiff[i] - meanrr) * (rrdiff[i] - meanrr);
    }
    sdsd = sqrt(sdsd / rrdiffp);

    meangsr = meangsr / mtime;

    feat[0] = nn50;
    feat[1] = rmssd;
    feat[2] = sdsd;
    feat[3] = totalDiffH;
    feat[4] = totalDiffV;
    feat[5] = meanrr;
    feat[6] = meangsr;
    feat[7] = totalStartle;
}

