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
    
}