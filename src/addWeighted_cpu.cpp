#include "cpu_kernels.h"

namespace cpu {

    //accumalate src into dest with mask
    int addWeighted(unsigned char const* src1, int src1Rows, int src1Cols, int src1Step, int src1Channels,
                    unsigned char const* src2, int src2Rows, int src2Cols, int src2Step, int src2Channels,
                    unsigned char* dest, int destRows, int destCols, int destStep, int destChannels, 
                    float ALPHA, float BETA, float GAMMA){

        assert(src1Rows == destRows && src1Cols == destCols && src1Step == destStep && src1Channels==destChannels);
        assert(src2Rows == destRows && src2Cols == destCols && src2Step == destStep && src2Channels==destChannels);
        
        
        for(int jj=0; jj<src1Cols; jj+=BLOCK_SIZE){
            for(int i=0; i<src1Rows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,src1Cols); ++j){
                    for(int k=0; k<src1Channels; ++k){
                        int32_t firstcmp = src1[i*src1Step + j*src1Channels + k] * ALPHA;
                        int32_t secondcmp = src2[i*src1Step + j*src1Channels + k] * BETA;
                        int16_t t = (firstcmp + secondcmp + GAMMA);
                        if (t > 255) {
                            t = 255;
                        } else if (t < 0) {
                            t = 0;
                        }
                        dest[i*destStep + j*src1Channels + k] = (unsigned char)t;
                    }
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}