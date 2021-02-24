#include "cpu_kernels.h"

namespace cpu {

    //extract a given channel
    int channelExtract(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                       unsigned char* dest, int destRows, int destCols, int destStep, uint16_t channel){

        assert(srcRows == destRows && srcCols == destCols);
        // std::cout << "Kernel " <<  srcCols << std::endl;
        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                    dest[i*destStep + j] = src[i*srcStep + j*srcChannels + channel];
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}