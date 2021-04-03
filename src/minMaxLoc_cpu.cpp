#include "cpu_kernels.h"

namespace cpu {

    int minMaxLoc(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                        double &minVal, double &maxVal, int &minXLoc, int &minYLoc, int &maxXLoc, int &maxYLoc){


        for(int i=0; i<srcRows; ++i){
            for(int j=0; j<srcCols; ++j){
                for(int k=0; k<srcChannels; ++k){
                    double t = src[i*srcStep + j*srcChannels + k];
                    if(t<minVal){
                        minVal = t;
                        minXLoc = i;
                        minYLoc = j;
                    }
                    if(t>maxVal){
                        maxVal = t;
                        maxXLoc = i;
                        maxYLoc = j;
                    }
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}