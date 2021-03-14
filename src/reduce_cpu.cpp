#include "cpu_kernels.h"
#include"opencv2/core/core_c.h"

namespace cpu {

    //reduce to a vector
    int reduce(unsigned char const* src, int srcRows, int srcCols, int srcStep, int srcChannels,
                  unsigned char* dest, int destRows, int destCols, int destStep, int destChannels, 
                  unsigned char dimension, unsigned char reduction){

        unsigned char internal_res;
        unsigned char* line_buf = (unsigned char*) malloc(srcCols * sizeof(unsigned char));
        unsigned int var;
        unsigned long long int p = 0, q = 0;
        unsigned char max = 0;
        unsigned char val_src, val_dst;

        if (dimension == 0) {
            var = 1;
        } else {
            var = 0;
        }

        if (dimension == 0) {
            for (int i = 0; i < (srcCols); i++) {
                line_buf[i] = src[i];
            }
        }

        for(int jj=0; jj<srcCols; jj+=BLOCK_SIZE){
            for(int i=0; i<srcRows; ++i){

                if (reduction == cv::REDUCE_MIN) {
                    internal_res = -1;
                    max = 255;
                } else {
                    internal_res = 0;
                    max = 0;
                }

                for(int j=jj; j<std::min(jj+BLOCK_SIZE,srcCols); ++j){
                    val_src = src[i*srcStep + j*srcChannels];

                    if (dimension == 0) {
                        internal_res = line_buf[j];
                    }

                    switch (reduction) {
                        case cv::REDUCE_SUM:
                            internal_res = internal_res + val_src;
                            break;
                        case cv::REDUCE_AVG:
                            internal_res = internal_res + val_src;
                            break;
                        case cv::REDUCE_MAX:
                            internal_res =
                                internal_res > val_src ? internal_res : val_src;
                            break;
                        case cv::REDUCE_MIN:
                            internal_res =
                                internal_res < val_src ? internal_res : val_src;
                            break;
                    }
                    if (dimension == 1 && j == srcCols - 1) {
                        if (reduction == cv::REDUCE_AVG) {
                            val_dst = internal_res / srcCols;
                        } else {
                            val_dst = internal_res;
                        }
                    }
                    if (dimension == 0) {
                        val_dst = internal_res;
                        line_buf[j] = val_dst;
                    }
                }//end of j=jj
                if (dimension == 1) {
                    dest[q] =  val_dst;
                    q++;
                }
            }
        }


        if (dimension == 0) {
            for (unsigned int out = 0; out < srcCols; out++) {
                if ((reduction == cv::REDUCE_SUM)) {
                    dest[q] =  line_buf[out];
                    q++;
                } else if (reduction == cv::REDUCE_AVG) {
                    dest[q] =  line_buf[out] / srcRows;
                    q++;
                } else {
                    dest[q] =  line_buf[out];
                    q = q + 1;
                }
            }
        }

        // free(line_buf);
        return KERNEL_SUCCESS;

    }


}