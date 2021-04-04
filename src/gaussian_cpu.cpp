#include "cpu_kernels.h"

namespace cpu {

    int gaussian(float const* src1, int src1Rows, int src1Cols, int src1Step, int src1Channels,
              float* src2, int src2Rows, int src2Cols, int src2Step, int src2Channels,
              float* dest, int destRows, int destCols, int destStep, int destChannels,
              int range){

        // assert(src1Rows == destRows && src1Cols == destCols && src1Step == destStep && src1Channels==destChannels);
        // assert(src2Rows == destRows && src2Cols == destCols && src2Step == destStep && src2Channels==destChannels);
        
        for(int r=range; r<src1Rows-range; r++) {
            for(int c=range; c<src1Step-range; c++) {
                float res = 0;
                int index = (r-range)*src1Step + (c-range);
                for(int x = -range; x<=range; x++) {
                    float m = 1/sqrt(2*M_PI)*exp(-0.5*x*x);
                    // std::cout << index << " " << r << " " << c << std::endl;
                    res += m * src1[index];
                }
                src2[index] = res;
            }
        }

        for(int r=range; r<src1Rows-range; r++) {
            for(int c=range; c<src1Step-range; c++) {
                float res = 0;
                int index = (r-range)*src1Step + (c-range);
                for(int x = -range; x<=range; x++) {
                    float m = 1/sqrt(2*M_PI)*exp(-0.5*x*x);
                    res += m * src2[index];
                }
                dest[index] = res;
            }
        }

        return KERNEL_SUCCESS;

    }


}