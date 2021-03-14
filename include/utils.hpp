#pragma once 

#include <iostream>
#include <fstream>
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

int dumpImage(const uint16_t* img, int rows, int cols, int step, int channels, std::string fileName){

    std::ofstream imgTextFile((std::string("textdata/") + fileName).c_str(), std::ios::out);
    if(imgTextFile.is_open())
    {
        imgTextFile << "Rows" << " " << "Cols" << " " << "Step" << " " << "Channels" << "\n";
        imgTextFile << rows << " " << cols << " " << step << " " << channels << "\n";
        
        for(int i=0; i<rows; ++i){
            for(int j=0; j<cols; ++j){
                for(int k=0; k<channels; ++k){
                    // std::cout << i << " " << j << " " << k << std::endl;
                    imgTextFile << img[i*cols + j*channels + k] << " ";  
                }
                imgTextFile << "\n";

            }
            imgTextFile << "\n\n";
        }

    }

    else return EXIT_FAILURE;

    return EXIT_SUCCESS;


}

int createImage(uint16_t* destData, std::string fileName){
    std::ifstream imgTextFile((std::string("textdata/") + fileName).c_str(), std::ios::in);
    std::string line;
    int rows, cols, step, channels;
    if(imgTextFile.is_open())
    {

        std::getline(imgTextFile, line); //Rows Cols Steps Channels string
        std::getline(imgTextFile, line); //Rows Cols Steps Channels values
        
        std::stringstream ss(line);
        ss >> rows;
        ss >> cols;
        ss >> step;
        ss >> channels;

        std::cout << "Read" << std::endl;
        std::cout << rows << " " << cols << " " << step << " " << channels << "\n";

        for(int i=0; i<rows; ++i){
            for(int j=0; j<cols; ++j){
                std::getline(imgTextFile, line);
                std::stringstream ss1(line);
                for(int k=0; k<channels; ++k){
                    ss1 >> destData[i*cols + j*channels + k];
                }
            }
        }

    }

    else EXIT_FAILURE;
    #if GRAY
        cv::Mat dest(rows, cols, CV_16SC1);
    #else
        cv::Mat dest(rows, cols, CV_16SC3);
    #endif
    uint16_t* destPtr = (uint16_t*)dest.data;
    for(int i=0; i<rows; ++i){
        for(int j=0; j<cols; ++j){
            for(int k=0; k<channels; ++k){
                destPtr[i*cols + j*channels + k] = destData[i*cols + j*channels + k];
            }
        }
    }   
    #if GRAY
        std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string("/1080x1920_gray.png");
    #else
        std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string("/1080x1920_color.png");
    #endif
    cv::imwrite(outImagePath.c_str(), dest);

    return EXIT_SUCCESS;
}