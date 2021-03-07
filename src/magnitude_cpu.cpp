#include "cpu_kernels.h"

namespace cpu {

    //compute L1NORM or L2NORM
    int magnitude(int16_t const* src1, int src1Rows, int src1Cols, int src1Step, int src1Channels,
                    int16_t const* src2, int src2Rows, int src2Cols, int src2Step, int src2Channels,
                    int16_t* dest, int destRows, int destCols, int destStep, int destChannels,
                    normTypeEnum normType){

        int16_t p, q, result;

        assert(src1Rows == src2Rows && src1Cols == src2Cols && src1Step == src2Step && src1Channels==src2Channels);
        for(int jj=0; jj<src1Cols; jj+=BLOCK_SIZE){
            for(int i=0; i<src1Rows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,src1Cols); ++j){
                    for(int k=0; k<src1Channels; ++k){
                        p = static_cast<int16_t>(src1[i*src1Step + j*src1Channels + k]);
                        q = static_cast<int16_t>(src2[i*src1Step + j*src1Channels + k]);
                        switch(normType){
                            case L1Norm:
                                result = std::abs(p) + std::abs(q);
                                break;
                            case L2Norm:
                                int tempgx = p*p;
                                int tempgy = q*q;
                                int temp = std::sqrt(tempgx + tempgy);
                                result = static_cast<int16_t>(temp);
                        }
                        dest[i*destStep + j*src1Channels + k] = result;
                    }
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}