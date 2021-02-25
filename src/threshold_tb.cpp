#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"
#include"utils.hpp"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {
  
  cv::Mat diff, image;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");
  #if GRAY
    image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
  #else
    image = cv::imread(imagePath.c_str() , cv::IMREAD_COLOR);
  #endif
  // imageGold = cv::imread("SARSA.png" ,cv::IMREAD_COLOR);
  
  if(! image.data) {
      std::cout << "Image not found or unable to open" << std::endl ;
      return -1;
    }

  cv::Mat imageGold, dest;
  #if GRAY
    imageGold =  cv::Mat::zeros(image.rows, image.cols, CV_8U);
    dest =  cv::Mat::zeros(image.rows, image.cols, CV_8U);
  #else
    imageGold =  cv::Mat::zeros(image.size(), CV_8UC3);
    dest =  cv::Mat::zeros(image.size(), CV_8UC3);
  #endif

  unsigned char maxval = 50;
  unsigned char thresh = 100;
  const char* thresholdStrings[] = {    "THRESH_BINARY",   
                                        "THRESH_BINARY_INV", 
                                        "THRESH_TRUNC", 
                                        "THRESH_TOZERO", 
                                        "THRESH_TOZERO_INV"};

  unsigned char threshType = cv::THRESH_TOZERO_INV;

  std::cout << image.rows << " " << image.cols << std::endl;
  std::cout << "Threshold type used " << thresholdStrings[threshType] << std::endl; 
 
  //OpenCV function
  cv::threshold(image, imageGold, thresh, maxval, threshType);

  //Replicated CPU function(without mask support)
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::threshold(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                    maxval, thresh, threshType);
  }
  //reset
  #if GRAY
    dest =  cv::Mat::zeros(image.rows, image.cols, CV_8U);
  #else
    dest =  cv::Mat::zeros(image.size(), CV_8UC3);
  #endif

  {
    cpu::Timer timer;
    cpu::threshold(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                    maxval, thresh, threshType);
  }

  cv::absdiff(imageGold, dest, diff);
  // Save the difference image
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/threshold_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/threshold_out.png"));
  cv::imwrite(outImagePath.c_str(), dest);
  #if DEBUG
    cv::namedWindow( "OpenCV Test Program", cv::WINDOW_AUTOSIZE );
    cv::Mat writtenImg = cv::imread(outImagePath.c_str(),cv::IMREAD_COLOR);
    cv::imshow("OpenCV Test Program", writtenImg);
  #endif

  //verification
  float err_per;
    analyzeDiff(diff, 0, err_per);

  if (err_per > 0.0f) {
      return EXIT_FAILURE;
  }
  
  cv::waitKey(0);
  return 0;
}
