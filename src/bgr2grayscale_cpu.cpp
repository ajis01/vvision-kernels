#include "cpu_kernels.h"

namespace cpu {

    int bgr2grayscale(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    float* dest, int destRows, int destCols, int destStep, int destChannels){

        assert(srcRows == destRows && srcCols == destCols);

        for(int i=0; i<srcRows; ++i){
            for(int j=0; j<srcCols; ++j){
                int indexSrc = i*srcStep + j;
                int indexDest = i*destStep + j;
                int indexColor = i*srcStep + j*srcChannels;
                dest[indexDest] = 
                    0.0722 * src[indexColor] +
                    0.7152 * src[indexColor+1] +
                    0.2126 * src[indexColor+2];
            }
        }

        return KERNEL_SUCCESS;

    }


}