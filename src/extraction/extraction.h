/*
 * extraction.h
 *
 *  Created on: Oct 3, 2017
 *      Author: ferdinandvonhagen
 */

#ifndef EXTRACTION_EXTRACTION_H_
#define EXTRACTION_EXTRACTION_H_

#include <stdbool.h>

typedef struct
{
    int x;
    int y;
    bool max;
} point;

int smoothecg(int ecg0d, int ecg1d);
int smoothgsr(int gsrd);
bool gsrdetection(int gsr, int mtime);
bool peakdetection(int ecgavg, int ecg0, int ecg1, int mtime);
void extractfeatures(int *feat, int mtime);
void extractfeatures2(int mtime, float *features);
void resetExtraction(int gsr, int mtime);



#endif /* EXTRACTION_EXTRACTION_H_ */
