#include "cpu_kernels.h"
#include<assert.h>

namespace cpu {

    //accumalate src into dest with mask
    int accumulateSquare(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    float* dest, int destRows, int destCols, int destStep, int destChannels){

        assert(srcRows == destRows && srcCols == destCols && srcStep == destStep && srcChannels == destChannels);


        for(int i=0; i<srcRows; ++i){
            for(int j=0; j<srcCols; ++j){
                for(int k=0; k<srcChannels; ++k){
                    float t = src[i*srcStep + j*srcChannels + k];
                    dest[i*destStep + j*srcChannels + k] += t*t;
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}