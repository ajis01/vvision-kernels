#pragma once
#include<assert.h>
#include<stdint.h>
#include<cmath>
#include<algorithm>
#include<iostream>

#define KERNEL_SUCCESS 0
#define KERNEL_FAILURE 1
#define GRAY 0
#define DEBUG 0
#define BLOCK_SIZE 8

enum normTypeEnum{
        L1Norm = 0,
        L2Norm
};

enum ccmTypeEnum{
        bt2020_bt709 = 0, 
        bt709_bt2020, 
        rgb_yuv_601, 
        rgb_yuv_709, 
        rgb_yuv_2020, 
        yuv_rgb_601, 
        yuv_rgb_709, 
        yuv_rgb_2020, 
        full_to_16_235, 
        full_from_16_235
};

//Required??
int inputImageSetup(float* src, float* goldRef, float *ref);

namespace cpu {
    int accumulate(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    float* dest, int destRows, int destCols, int destStep, int destChannels);
    int accumulateSquare(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    float* dest, int destRows, int destCols, int destStep, int destChannels);
    int accumulateWeighted(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    float* dest, int destRows, int destCols, int destStep, int destChannels, float ALPHA);
    int addWeighted(unsigned char const* src1, int src1Rows, int src1Cols, int src1Step, int src1Channels,
                    unsigned char const* src2, int src2Rows, int src2Cols, int src2Step, int src2Channels,
                    unsigned char* dest, int destRows, int destCols, int destStep, int destChannels, 
                    float ALPHA, float BETA, float GAMMA);
    int channelExtract(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                       unsigned char* dest, int destRows, int destCols, int destStep, uint16_t channel);
    int sum(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
            double* scl);
    int threshold(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest, int destRows, int destCols, int destStep, int destChannels, 
                  unsigned char maxval, unsigned char thresh, unsigned char thresh_type);
    int reduce(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest, int destRows, int destCols, int destStep, int destChannels, 
                  unsigned char dimension, unsigned char reduction);

    int magnitude(int16_t const* src1, int src1Rows, int src1Cols, int src1Step, int src1Channels,
                    int16_t const* src2, int src2Rows, int src2Cols, int src2Step, int src2Channels,
                    int16_t* dest, int destRows, int destCols, int destStep, int destChannels,
                    normTypeEnum normType);
                    
    int lut(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest, int destRows, int destCols, int destStep, int destChannels, 
                  unsigned char correctionLut[256]);

    int gammaCorrection(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest, int destRows, int destCols, int destStep, int destChannels,
                  float gammaVal);

    int histogram(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest);

    int colorCorrectionMatrix(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
            unsigned char* dest, int destRows, int destCols, int destStep, int destChannels,
            ccmTypeEnum ccmType);



}