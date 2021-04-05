#include "cpu_kernels.h"

namespace cpu {

    int integral(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
              float* dest, int destRows, int destCols, int destStep, int destChannels,
              int range){

        // assert(src1Rows == destRows && src1Cols == destCols && src1Step == destStep && src1Channels==destChannels);
        // assert(src2Rows == destRows && src2Cols == destCols && src2Step == destStep && src2Channels==destChannels);
        

        dest[0] = src[0];

        for (int i = 1; i < srcCols; i++) {
            dest[i] = 
                dest[i-1] 
                + src[i];
        }

        for (int j = 1; j < srcRows; j++) {
            dest[j*srcStep] = 
                dest[(j-1)*srcStep] 
                + src[j*srcStep];
        }    

        for (int i = 1; i < srcRows; i++) {
            for (int j = 1; j < srcCols; j++) {
                int rowOffset = i*srcStep;
                dest[rowOffset + j] = 
                    src[rowOffset + j]
                    +dest[rowOffset + j-1]
                    +dest[rowOffset-srcStep + j]
                    -dest[rowOffset-srcStep + j-1];
            }
        }

        return KERNEL_SUCCESS;

    }


}