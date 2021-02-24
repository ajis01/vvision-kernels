#include "cpu_kernels.h"

namespace cpu {

    //sum of individual channels
    int sum(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
            double* scl){

        for(int i=0; i<srcChannels; ++i){
            scl[i] = 0;
        }

        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                    for(int k=0; k<srcChannels; ++k){
                        scl[k] += src[i*srcStep + j*srcChannels + k];
                    }
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}