#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {
  
  cv::Mat derHHelper, derVHelper, image, Ix, Iy, Ixy;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/128x128.png");
  image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
  //  imageGold = cv::imread("SARSA.png" ,cv::IMREAD_COLOR);
  
  if(! image.data) {
      std::cout << "image not found or unable to open" << std::endl ;
      return -1;
    }



  Ix =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  Iy =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  Ixy =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  derHHelper =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  derVHelper =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);

  image.convertTo(image, CV_32FC1);  


  std::cout << image.rows << " " << image.cols << std::endl;

 
  //OpenCV function

  //Replicated CPU function
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::derivative((float*)image.data, image.rows, image.cols, image.step1(), image.channels(),
                (float*)derHHelper.data, derHHelper.rows, derHHelper.cols, derHHelper.step1(), derHHelper.channels(),
                (float*)derVHelper.data, derVHelper.rows, derVHelper.cols, derVHelper.step1(), derVHelper.channels(),
                (float*)Ix.data, Ix.rows, Ix.cols, Ix.step1(), Ix.channels(),
                (float*)Iy.data, Iy.rows, Iy.cols, Iy.step1(), Iy.channels(),
                (float*)Ixy.data, Ixy.rows, Ixy.cols, Ixy.step1(), Ixy.channels());
  }
  //reset
  Ix =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  Iy =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  Ixy =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  derHHelper =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);
  derVHelper =  cv::Mat::zeros(image.rows, image.cols, CV_32FC1);

  {
    cpu::Timer timer;
    cpu::derivative((float*)image.data, image.rows, image.cols, image.step1(), image.channels(),
                (float*)derHHelper.data, derHHelper.rows, derHHelper.cols, derHHelper.step1(), derHHelper.channels(),
                (float*)derVHelper.data, derVHelper.rows, derVHelper.cols, derVHelper.step1(), derVHelper.channels(),
                (float*)Ix.data, Ix.rows, Ix.cols, Ix.step1(), Ix.channels(),
                (float*)Iy.data, Iy.rows, Iy.cols, Iy.step1(), Iy.channels(),
                (float*)Ixy.data, Ixy.rows, Ixy.cols, Ixy.step1(), Ixy.channels());
  }



  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/derivative_out.png"));
  cv::imwrite(outImagePath.c_str(), Ixy);
  #if DEBUG
    cv::namedWindow( "OpenCV Test Program", cv::WINDOW_AUTOSIZE );
    cv::Mat writtenImg = cv::imread(outImagePath.c_str(),cv::IMREAD_COLOR);
    cv::imshow("OpenCV Test Program", writtenImg);
  #endif

  
  cv::waitKey(0);
  return 0;
}
