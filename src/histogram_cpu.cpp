#include "cpu_kernels.h"

namespace cpu {

    //histogram with 256 bins
    int histogram(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest){

        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                    dest[src[i*srcStep + j*srcChannels]] += 1;
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}