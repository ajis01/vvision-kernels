#include "cpu_kernels.h"

namespace cpu {

    //accumalate src into dest with mask
    int phase(float const* src1, int src1Rows, int src1Cols, int src1Step, int src1Channels,
              float const* src2, int src2Rows, int src2Cols, int src2Step, int src2Channels,
              float* dest, int destRows, int destCols, int destStep, int destChannels){

        assert(src1Rows == destRows && src1Cols == destCols && src1Step == destStep && src1Channels==destChannels);
        assert(src2Rows == destRows && src2Cols == destCols && src2Step == destStep && src2Channels==destChannels);
        
        
        for(int i=0; i<src1Rows; ++i){
            for(int j=0; j<src1Step; ++j){
                for(int k=0; k<src1Channels; ++k){
                    float t1 = src1[i*src1Step + j*src1Channels + k];
                    float t2 = src2[i*src1Step + j*src1Channels + k];
                    if(t1==0 && t2==0) dest[i*src1Step + j*src1Channels + k] = 0;
                    else dest[i*src1Step + j*src1Channels + k] = std::atan2(t2,t1);
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}