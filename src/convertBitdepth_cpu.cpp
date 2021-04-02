#include "cpu_kernels.h"

namespace cpu {

    int convertBitdepth(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                        unsigned char* dest, int destRows, int destCols, int destStep, int destChannels,
                        int shift, int rtype){

        //for 8U
        int max, min;
        max = 255;
        min = 0;
        int val;

        
        assert(srcRows == destRows && srcCols == destCols && srcStep == destStep && srcChannels == destChannels);   


        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                    for(int k=0; k<srcChannels; ++k){

                        // std::cout << srcRows << " " << srcStep << " " << srcChannels << std::endl;
                        // std::cout << i << " " << j << " " << k << std::endl;
                        int t = src[i*srcCols    + j*srcChannels + k];
                        if(t<min) val = min;
                        else if(t>max) val = max;
                        else val = t;
                        dest[i*destStep + j*srcChannels + k] = t;
                    }
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}