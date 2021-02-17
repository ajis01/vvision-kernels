#include "cpu_kernels.h"
#include<assert.h>

namespace cpu {

    //accumalate src into dest with mask
    int accumulateSquare(const cv::Mat &src, cv::Mat &dest){

        assert(src.rows == dest.rows && src.cols == dest.cols && src.channels() == dest.channels());

        #if GRAY
            for(uint i=0; i<src.rows; ++i){
                for(uint j=0; j<src.cols; ++j){
                    float t = src.at<float>(i,j);
                    dest.at<float>(i,j) += t*t;
                }
            }
        #else 
            for(uint i=0; i<src.rows; ++i){
                for(uint j=0; j<src.cols; ++j){
                    for(uint k =0; k<src.channels(); ++k){
                        float t = src.at<cv::Vec3f>(i,j)[k];
                        dest.at<cv::Vec3f>(i,j)[k] += t*t;
                    }
                }
            }
        #endif

        return KERNEL_SUCCESS;

    }


}