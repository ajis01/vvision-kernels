#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {
  
  cv::Mat diff, image;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");
  image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
  //  imageGold = cv::imread("SARSA.png" ,cv::IMREAD_COLOR);
  
  if(! image.data) {
      std::cout << "image not found or unable to open" << std::endl ;
      return -1;
    }

  cv::Mat imageGold, dest;
  cv::Mat  gradX, gradY;
  cv::Mat  gradXDSA, gradYDSA;

  imageGold =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  dest =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);


  image.convertTo(image, CV_32FC1);  


  std::cout << image.rows << " " << image.cols << std::endl;

  int scale = 1;
  int delta = 0;
  int filterSize = 3;
 
  //OpenCV function
  cv::Sobel(image, gradX, CV_32FC1, 1, 0, filterSize, scale, delta, cv::BORDER_CONSTANT);
  cv::Sobel(image, gradY, CV_32FC1, 0, 1, filterSize, scale, delta, cv::BORDER_CONSTANT);
  cv::phase(gradX, gradY, imageGold, false);//in radians

  //Replicated CPU function
  cv::Sobel(image, gradXDSA, CV_32FC1, 1, 0, filterSize, scale, delta, cv::BORDER_CONSTANT);
  cv::Sobel(image, gradYDSA, CV_32FC1, 0, 1, filterSize, scale, delta, cv::BORDER_CONSTANT);
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::phase((float*)gradXDSA.data, gradXDSA.rows, gradXDSA.cols, gradXDSA.step1(), gradXDSA.channels(),
                (float*)gradYDSA.data, gradYDSA.rows, gradYDSA.cols, gradYDSA.step1(), gradYDSA.channels(),
                (float*)dest.data, dest.rows, dest.cols, dest.step1(), dest.channels());
  }
  //reset
  dest =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);


  {
    cpu::Timer timer;
    cpu::phase((float*)gradXDSA.data, gradXDSA.rows, gradXDSA.cols, gradXDSA.step1(), gradXDSA.channels(),
                (float*)gradYDSA.data, gradYDSA.rows, gradYDSA.cols, gradYDSA.step1(), gradYDSA.channels(),
                (float*)dest.data, dest.rows, dest.cols, dest.step1(), dest.channels());
  }

  cv::absdiff(imageGold, dest, diff);
  // Save the difference image
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/phase_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/phase_out.png"));
  cv::imwrite(outImagePath.c_str(), dest);
  #if DEBUG
    cv::namedWindow( "OpenCV Test Program", cv::WINDOW_AUTOSIZE );
    cv::Mat writtenImg = cv::imread(outImagePath.c_str(),cv::IMREAD_COLOR);
    cv::imshow("OpenCV Test Program", writtenImg);
  #endif

  // float ocvminvalue, ocvmaxvalue;
  // float dsaminvalue=65535, dsamaxvalue=0;
  // double minval = 65535, maxval = 0;
  // int cnt = 0;
  // for (int i = 0; i < image.rows; i++) {
  //     for (int j = 0; j < image.cols; j++) {
  //         short int v3 = dest.at<short int>(i, j);
  //         float v2 = imageGold.at<float>(i, j);
  //         float v1;

  //         v1 = v3 / (pow(2.0, 12)); // converting the output fixed point format from Q4.12 format to float

  //         float v = (v2 - v1);

  //         if (v > 1) cnt++;
  //         if (minval > v) {
  //             minval = v;
  //             ocvminvalue = v2;
  //             dsaminvalue = v1;
  //         }
  //         if (maxval < v) {
  //             maxval = v;
  //             ocvmaxvalue = v2;
  //             dsamaxvalue = v1;
  //         }
  //     }
  // }
  // printf("Minimum value ocv = %f Minimum value dsa = %f\n", ocvminvalue, dsaminvalue);
  // printf("Maximum value ocv = %f Maximum value dsa = %f\n", ocvmaxvalue, dsamaxvalue);

  
  cv::waitKey(0);
  return 0;
}
