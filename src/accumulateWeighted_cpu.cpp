#include "cpu_kernels.h"

namespace cpu {

    //accumalate src into dest with mask
    int accumulateWeighted(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                    float* dest, int destRows, int destCols, int destStep, int destChannels, float alpha){

        assert(srcRows == destRows && srcCols == destCols && srcStep == destStep && srcChannels==destChannels);

        uint32_t temp = (alpha * ((1<<23) - 1));
        uint32_t temp1 = ((1<<23) - 1) - temp + 1;

        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                    for(int k=0; k<srcChannels; ++k){
                        uint64_t firstcmp = src[i*srcStep + j*srcChannels + k] * temp;
                        uint64_t secondcmp = dest[i*srcStep + j*srcChannels + k] * temp1;
                        float t = (firstcmp + secondcmp) >> 23;
                        dest[i*destStep + j*srcChannels + k] = t;
                    }
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}