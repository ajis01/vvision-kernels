#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {
  
  cv::Mat diff, image1, image2;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");
  #if GRAY
    image1 = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
    image2 = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
  #else
    image1 = cv::imread(imagePath.c_str() , cv::IMREAD_COLOR);
    image2 = cv::imread(imagePath.c_str() , cv::IMREAD_COLOR);
  #endif
  // imageGold = cv::imread("SARSA.png" ,cv::IMREAD_COLOR);
  
  if(! image1.data) {
      std::cout << "image1 not found or unable to open" << std::endl ;
      return -1;
    }

  if(! image2.data) {
    std::cout << "image2 not found or unable to open" << std::endl ;
    return -1;
  }

  cv::Mat imageGold, dest;
  #if GRAY
    imageGold =  cv::Mat::zeros(image1.rows, image1.cols, CV_8UC1);
    dest =  cv::Mat::zeros(image1.rows, image1.cols, CV_8UC1);
  #else
    imageGold =  cv::Mat::zeros(image1.size(), CV_8UC3);
    dest =  cv::Mat::zeros(image1.size(), CV_8UC3);
  #endif

  #if GRAY  
    image1.convertTo(image1, CV_8UC1); 
    image2.convertTo(image2, CV_8UC1); 
  #else 
    image1.convertTo(image1, CV_8UC3); 
    image2.convertTo(image2, CV_8UC3); 
  #endif

  std::cout << image1.rows << " " << image1.cols << std::endl;
  float ALPHA = 0.2;
  float BETA = 0.3;
  float GAMMA = 0.0;
  //OpenCV function
  cv::addWeighted(image1, ALPHA, image2, BETA, GAMMA, imageGold);

  //Replicated CPU function(without mask support)
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::addWeighted(image1.data, image1.rows, image1.cols, image1.step1(), image1.channels(),
                     image2.data, image2.rows, image2.cols, image2.step1(), image2.channels(),
                     dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                     ALPHA, BETA, GAMMA);
  }
  //reset
  #if GRAY
    dest =  cv::Mat::zeros(image1.rows, image1.cols, CV_8UC1);
  #else
    dest =  cv::Mat::zeros(image1.size(), CV_8UC3);
  #endif

  {
    cpu::Timer timer;
    cpu::addWeighted(image1.data, image1.rows, image1.cols, image1.step1(), image1.channels(),
                     image2.data, image2.rows, image2.cols, image2.step1(), image2.channels(),
                     dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                     ALPHA, BETA, GAMMA);
  }

  cv::absdiff(imageGold, dest, diff);
  // Save the difference image
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/addWeighted_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/addWeighted_out.png"));
  cv::imwrite(outImagePath.c_str(), dest);
  #if DEBUG
    cv::namedWindow( "OpenCV Test Program", cv::WINDOW_AUTOSIZE );
    cv::Mat writtenImg = cv::imread(outImagePath.c_str(),cv::IMREAD_COLOR);
    cv::imshow("OpenCV Test Program", writtenImg);
  #endif

  // Find minimum and maximum differences
  double minval = 256, maxval = 0;
  int cnt = 0;
  for (int i = 0; i < image1.rows; i++) {
      for (int j = 0; j < image1.cols; j++) {
          unsigned char v = diff.at<unsigned char>(i, j);
          
          if (v > 2){ //2 instead of 1 to account for absence of ap_fixed<16,8,AP_RND>
            cnt++;
            std::cout << static_cast<int>(v) << " count " << cnt << std::endl;
          }
          if (minval > v) minval = v;
          if (maxval < v) maxval = v;
      }
  }

  float err_per = 100.0 * (float)cnt / (image1.rows * image1.cols);

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
