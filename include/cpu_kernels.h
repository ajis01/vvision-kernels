#pragma once

#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

#define KERNEL_SUCCESS 0
#define KERNEL_FAILURE 1
#define GRAY 1
#define DEBUG 0

namespace cpu {
    int accumulate(const cv::Mat &src, cv::Mat &dest);
    
}