#include "cpu_kernels.h"

namespace cpu {

    int meanFilter(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
              float* dest, int destRows, int destCols, int destStep, int destChannels,
              int range){

        // assert(src1Rows == destRows && src1Cols == destCols && src1Step == destStep && src1Channels==destChannels);
        // assert(src2Rows == destRows && src2Cols == destCols && src2Step == destStep && src2Channels==destChannels);
        
        for (int r = range; r < srcRows-range; r++) {
            for (int c = range; c < srcStep-range; c++) {
                int lowerLeft = (r+range)*srcStep + c-range;
                int upperLeft = (r-range)*srcStep + c-range;
                int lowerRight = (r+range)*srcStep + c+range;
                int upperRight = (r-range)*srcStep + c+range;
                dest[upperLeft] = 
                    src[lowerRight]
                    + src[upperLeft]
                    - src[lowerLeft]
                    - src[upperRight];
            }
        }

        return KERNEL_SUCCESS;

    }


}