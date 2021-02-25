#pragma once 

#include <iostream>
#include <cmath>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

void analyzeDiff(cv::Mat& diff_img, int err_thresh, float& err_per) {
    int cv_bitdepth;
    if (diff_img.depth() == CV_8U) {
        cv_bitdepth = 8;
    } else if (diff_img.depth() == CV_16U || diff_img.depth() == CV_16S) {
        cv_bitdepth = 16;
    } else if (diff_img.depth() == CV_32S || diff_img.depth() == CV_32F) {
        cv_bitdepth = 32;
    } else {
        fprintf(stderr, "OpenCV image's depth not supported for this function\n ");
        return;
    }

    int cnt = 0;
    double minval = std::pow(2.0, cv_bitdepth), maxval = 0;
    int max_fix = (int)(std::pow(2.0, cv_bitdepth) - 1.0);
    for (int i = 0; i < diff_img.rows; i++) {
        for (int j = 0; j < diff_img.cols; j++) {
            int v = 0;
            for (int k = 0; k < diff_img.channels(); k++) {
                int v_tmp = 0;
                if (diff_img.channels() == 1) {
                    if (cv_bitdepth == 8)
                        v_tmp = (int)diff_img.at<unsigned char>(i, j);
                    else if (cv_bitdepth == 16 && diff_img.depth() == CV_16U) // 16 bitdepth
                        v_tmp = (int)diff_img.at<unsigned short>(i, j);
                    else if (cv_bitdepth == 16 && diff_img.depth() == CV_16S) // 16 bitdepth
                        v_tmp = (int)diff_img.at<short>(i, j);
                    else if (cv_bitdepth == 32 && diff_img.depth() == CV_32S)
                        v_tmp = (int)diff_img.at<int>(i, j);
                } else // 3 channels
                    v_tmp = (int)diff_img.at< ::cv::Vec3b>(i, j)[k];

                if (v_tmp > v) v = v_tmp;
            }
            if (v > err_thresh) {
                cnt++;
                if (diff_img.depth() == CV_8U)
                    diff_img.at<unsigned char>(i, j) = max_fix;
                else if (diff_img.depth() == CV_16U)
                    diff_img.at<unsigned short>(i, j) = max_fix;
                else if (diff_img.depth() == CV_16S)
                    diff_img.at<short>(i, j) = max_fix;
                else if (diff_img.depth() == CV_32S)
                    diff_img.at<int>(i, j) = max_fix;
                else
                    diff_img.at<float>(i, j) = (float)max_fix;
            }
            if (minval > v) minval = v;
            if (maxval < v) maxval = v;
        }
    }
    err_per = 100.0 * (float)cnt / (diff_img.rows * diff_img.cols);
    std::cout << "\tMinimum error in intensity = " << minval << std::endl;
    std::cout << "\tMaximum error in intensity = " << maxval << std::endl;
    std::cout << "\tPercentage of pixels above error threshold = " << err_per << std::endl;
}