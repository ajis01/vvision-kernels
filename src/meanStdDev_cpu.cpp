#include "cpu_kernels.h"

namespace cpu {

    int meanStdDev(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                        float** meanDSA, float** stdDevDSA, double* sumDSA, double* xDSA){


        for(int i=0; i<srcRows; ++i){
            for(int j=0; j<srcStep; ++j){
                for(int k=0; k<srcChannels; ++k){
                    unsigned char t = src[i*srcStep + j*srcChannels + k];
                    sumDSA[k] += t;
                }
            }
        }

        for(int k=0; k<srcChannels; ++k){
            // std::cout << sumDSA[k] << std::endl;
            // std::cout << srcRows*srcCols << std::endl;
            *meanDSA[k] = sumDSA[k]/(srcRows*srcCols);
            // std::cout << *meanDSA[k] << std::endl;

        }

        for(int i=0; i<srcRows; ++i){
            for(int j=0; j<srcStep; ++j){
                for(int k=0; k<srcChannels; ++k){
                    double t = *meanDSA[k] - src[i*srcStep + j*srcChannels + k];
                    t *= t;
                    xDSA[k] += t;
                }
            }
        }

        for(int k=0; k<srcChannels; ++k){
            *stdDevDSA[k] = std::sqrt(xDSA[k]/(srcRows*srcCols));
            // std::cout << *stdDevDSA[k] << std::endl;
        }

        return KERNEL_SUCCESS;

    }


}