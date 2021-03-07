#include "cpu_kernels.h"

namespace cpu {

    //lut correction
    int lut(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest, int destRows, int destCols, int destStep, int destChannels, 
                  unsigned char correctionLut[256]){

        assert(srcRows == destRows && srcCols == destCols && srcStep == destStep && srcChannels==destChannels);
        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                    for(int k=0; k<srcChannels; ++k)
                        dest[i*destStep + j*srcChannels + k] = correctionLut[src[i*srcStep + j*srcChannels + k]];
                                                               //just for CV_8U
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}