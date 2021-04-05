#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {
  
  cv::Mat diff, image, dest;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/128x128.png");
  image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
  //  imageGold = cv::imread("SARSA.png" ,cv::IMREAD_COLOR);
  
  if(! image.data) {
      std::cout << "image not found or unable to open" << std::endl ;
      return -1;
    }

  int range = 3;


  dest =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);

  image.convertTo(image, CV_32FC1);  


  std::cout << image.rows << " " << image.cols << std::endl;

 
  std::vector<cornerXY> points;
  float percentage=1;
  int filterRange=3, suppressionRadius=10;

  //Replicated CPU function
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::nonMaximaSuppression((float*)image.data, image.rows, image.cols, image.step1(), image.channels(),
                (float*)dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                points, percentage, filterRange, suppressionRadius);
  }
  //reset
  dest =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);

  {
    cpu::Timer timer;
    cpu::nonMaximaSuppression((float*)image.data, image.rows, image.cols, image.step1(), image.channels(),
                (float*)dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                points, percentage, filterRange, suppressionRadius);
  }



  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/nonMaximaSuppression_out.png"));
  cv::imwrite(outImagePath.c_str(), dest);
  #if DEBUG
    cv::namedWindow( "OpenCV Test Program", cv::WINDOW_AUTOSIZE );
    cv::Mat writtenImg = cv::imread(outImagePath.c_str(),cv::IMREAD_COLOR);
    cv::imshow("OpenCV Test Program", writtenImg);
  #endif

  
  cv::waitKey(0);
  return 0;
}
