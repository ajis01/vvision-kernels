#pragma once
#include<assert.h>
#include<algorithm>

#define KERNEL_SUCCESS 0
#define KERNEL_FAILURE 1
#define GRAY 1
#define DEBUG 0
#define BLOCK_SIZE 8

namespace cpu {
    int accumulate(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    float* dest, int destRows, int destCols, int destStep, int destChannels);
    int accumulateSquare(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    float* dest, int destRows, int destCols, int destStep, int destChannels);
    
}