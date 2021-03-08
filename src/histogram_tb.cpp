#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {
  
  cv::Mat image;
  cv::Mat diff;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");

  image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
  // imageGold = cv::imread("SARSA.png" ,cv::IMREAD_COLOR);
  
  if(! image.data) {
      std::cout << "Image not found or unable to open" << std::endl ;
      return -1;
    }

  int histSize = 256;
  /// Set the ranges ( for B,G,R) )
  float range[] = {0, 255};
  const float* histRange [] = {range};

  cv::Mat imageGold, dest;
  imageGold =  cv::Mat::zeros(histSize, 1, CV_8U);
  dest =  cv::Mat::zeros(histSize, 1, CV_8U);

  image.convertTo(image, CV_8U); 

  std::cout << image.rows << " " << image.cols << std::endl;
 
  //OpenCV function
  cv::calcHist(&image, 1, 0, cv::Mat(), imageGold, 1, &histSize, histRange, 1, 0);
  imageGold.convertTo(imageGold, CV_8U); 

  //Replicated CPU function
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::histogram(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    dest.data);
  }
  //reset
  dest =  cv::Mat::zeros(histSize, 1, CV_8U);

  {
    cpu::Timer timer;
    cpu::histogram(image.data, image.rows, image.cols, image.step1(), image.channels(),
                   dest.data);
  }

  cv::absdiff(imageGold, dest, diff); 
  // Save the difference image(only grayscale supported for visual diff)
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/histogram_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/histogram_out.png"));
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
        float v = diff.at<short>(i, j);
        if (fabs(v) > 0.0f) cnt++;
        if (minval > v) minval = v;
        if (maxval < v) maxval = v;
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
