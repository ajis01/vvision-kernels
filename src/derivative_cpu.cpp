#include "cpu_kernels.h"

namespace cpu {

    int derivative(float const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
              float* derVHelper, int derVHelperRows, int derVHelperCols, int derVHelperStep, int derVHelperChannels,
              float* derHHelper, int derHHelperRows, int derHHelperCols, int derHHelperStep, int derHHelperChannels,
              float* Ix, int IxRows, int IxCols, int IxStep, int IxChannels,
              float* Iy, int IyRows, int IyCols, int IyStep, int IyChannels,
              float* Ixy, int IxyRows, int IxyCols, int IxyStep, int IxyChannels){

        // assert(src1Rows == IxRows && src1Cols == IxCols && src1Step == IxStep && src1Channels==IxChannels);
        // assert(src2Rows == IxRows && src2Cols == IxCols && src2Step == IxStep && src2Channels==IxChannels);
        

        for(int r=1; r<srcRows-1; r++) {
            for(int c=0; c<srcCols; c++) {
                int rowOffset = r*srcStep;
                float a1 = src[rowOffset-srcStep+c];
                float a2 = src[rowOffset+c];
                float a3 = src[rowOffset+srcStep+c];

                derVHelper[rowOffset-srcStep+c] = a1 + a2 + a2 + a3;
            }
        }

        for(int r=0; r<srcRows; r++) {
            for(int c=1; c<srcCols-1; c++) {
                int rowOffset = r*srcStep;
                float a1 = src[rowOffset + c-1];
                float a2 = src[rowOffset + c];
                float a3 = src[rowOffset + c+1];

                derHHelper[rowOffset+c-1] = a1 + a2 + a2 + a3;
            }
        }

        for(int r=0; r<srcRows-2; r++) {
            for(int c=0; c<srcCols-2; c++) {
                int rowOffset = r*srcStep;
                Ix[rowOffset+c] = derHHelper[rowOffset+c] - derHHelper[rowOffset+2*srcStep+c];
                Iy[rowOffset+c] = - derVHelper[rowOffset+c] + derVHelper[rowOffset+c+2];
                Ixy[rowOffset+c] = Ix[rowOffset+c] * Iy[rowOffset+c];
            }
        }

        return KERNEL_SUCCESS;

    }


}