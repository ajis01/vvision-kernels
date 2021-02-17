#include <iostream>
#include<string>
#include"cpu_kernels.h"
#include"timer.h"

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
    imageGold =  cv::Mat::zeros(image.rows, image.cols, CV_32F);
    dest =  cv::Mat::zeros(image.rows, image.cols, CV_32F);
  #else
    imageGold =  cv::Mat::zeros(image.size(), CV_32FC3);
    dest =  cv::Mat::zeros(image.size(), CV_32FC3);
  #endif
  cv::Mat aux;

  #if GRAY  
    image.convertTo(image, CV_32F); 
  #else 
    image.convertTo(image, CV_32FC3); 
  #endif
 
  //OpenCV function
  cv::accumulateSquare(image, imageGold, cv::noArray());

  //Replicated CPU function(without mask support)
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i)
    cpu::accumulateSquare(image, dest);
  //reset
  #if GRAY
    dest =  cv::Mat::zeros(image.rows, image.cols, CV_32F);
  #else
    dest =  cv::Mat::zeros(image.size(), CV_32FC3);
  #endif

  {
    cpu::Timer timer;
    cpu::accumulateSquare(image, dest);
  }

  cv::absdiff(imageGold, dest, diff);
  // Save the difference image
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/accumulateSquared_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/accumulateSquared_out.png"));
  cv::imwrite(outImagePath.c_str(), dest);
  #if DEBUG
    cv::namedWindow( "OpenCV Test Program", cv::WINDOW_AUTOSIZE );
    cv::Mat writtenImg = cv::imread(outImagePath.c_str(),cv::IMREAD_COLOR);
    cv::imshow("OpenCV Test Program", writtenImg);
  #endif


  double minval = 256, maxval = 0;
  int cnt = 0;
  for (int i = 0; i < image.rows; i++) {
      for (int j = 0; j < image.cols; j++) {
  #if 1
          float v = diff.at<short>(i, j);
          if (v > 0.0f) cnt++;
          if (minval > v) minval = v;
          if (maxval < v) maxval = v;
  #else
          cv::Vec3s v = diff.at<cv::Vec3s>(i, j);
          if (v[0] > 0.0f) cnt++;
          if (minval > v[0]) minval = v[0];
          if (maxval < v[0]) maxval = v[0];

          if (v[1] > 0.0f) cnt++;
          if (minval > v[1]) minval = v[1];
          if (maxval < v[1]) maxval = v[1];

          if (v[2] > 0.0f) cnt++;
          if (minval > v[2]) minval = v[2];
          if (maxval < v[2]) maxval = v[2];
  #endif
      }
  }
  float err_per = 100.0 * (float)cnt / (image.rows * image.cols * image.channels());

  std::cout << "INFO: Verification results:" << std::endl;
  std::cout << "\tMinimum error in intensity = " << minval << std::endl;
  std::cout << "\tMaximum error in intensity = " << maxval << std::endl;
  std::cout << "\tPercentage of pixels above error threshold = " << err_per << std::endl;

  if (err_per > 0.0f) {
      fprintf(stderr, "ERROR: Test Failed.\n ");
      return EXIT_FAILURE;
  }
  
  cv::waitKey(0);
  return 0;
}