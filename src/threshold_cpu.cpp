#include "cpu_kernels.h"
#include<opencv2/imgproc.hpp>

namespace cpu {


    int threshold(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest, int destRows, int destCols, int destStep, int destChannels, 
                  unsigned char maxval, unsigned char thresh, unsigned char thresh_type){

        assert(srcRows == destRows && srcCols == destCols && srcStep == destStep && srcChannels==destChannels);
        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){
                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                    for(int k=0; k<srcChannels; ++k){

                        switch (thresh_type)
                        {
                        case cv::THRESH_BINARY:
                            dest[i*destStep + j*srcChannels + k] = src[i*srcStep + j*srcChannels + k] > thresh ? 
                                                                    maxval : 0;
                            break;

                        case cv::THRESH_BINARY_INV:
                            dest[i*destStep + j*srcChannels + k] = src[i*srcStep + j*srcChannels + k] > thresh ? 
                                                                    0 : maxval;
                            break;

                        case cv::THRESH_TRUNC:
                            dest[i*destStep + j*srcChannels + k] = src[i*srcStep + j*srcChannels + k] > thresh ? 
                                                                    thresh : src[i*srcStep + j*srcChannels + k];
                            break;

                        case cv::THRESH_TOZERO:
                            dest[i*destStep + j*srcChannels + k] = src[i*srcStep + j*srcChannels + k] > thresh ? 
                                                                    src[i*srcStep + j*srcChannels + k] : 0;
                            break;

                        case cv::THRESH_TOZERO_INV:
                            dest[i*destStep + j*srcChannels + k] = src[i*srcStep + j*srcChannels + k] > thresh ? 
                                                                    0 : src[i*srcStep + j*srcChannels + k];
                            break;
                        
                        default:
                            dest[i*destStep + j*srcChannels + k] = src[i*srcStep + j*srcChannels + k];
                            break;
                        }
                    }
                }
            }
        }

        return KERNEL_SUCCESS;

    }


}