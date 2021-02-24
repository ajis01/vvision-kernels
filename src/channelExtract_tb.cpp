#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {
  
  cv::Mat diff, image, in_rgba;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");

  image = cv::imread(imagePath.c_str() , cv::IMREAD_COLOR);
  
  if(! image.data) {
      std::cout << "Image not found or unable to open" << std::endl ;
      return -1;
    }

  cv::Mat dest;

  dest =  cv::Mat::zeros(image.size(), CV_8U);


  // image.convertTo(image, CV_8UC3);
  uint16_t channel = 2;



  std::cout << image.rows << " " << image.cols << std::endl;
 
  //OpenCV function
  std::vector<cv::Mat> bgr_planes;
  cv::split(image, bgr_planes);
  // // write output and OpenCV reference image
  // cv::imwrite("out_ocv.png", bgr_planes[2]);

  //Replicated CPU function(without mask support)
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::channelExtract(image.data, image.rows, image.cols, image.step1(), image.channels(),
                        dest.data, dest.rows, dest.cols, dest.step1(), channel);
  }
  //reset
  dest =  cv::Mat::zeros(image.size(), CV_8U);


  {
    cpu::Timer timer;
    cpu::channelExtract(image.data, image.rows, image.cols, image.step1(), image.channels(),
                        dest.data, dest.rows, dest.cols, dest.step1(), channel);
  }

  cv::absdiff(bgr_planes[channel], dest, diff);
  // Save the difference image
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/channelExtract_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/channelExtract_out.png"));
  cv::imwrite(outImagePath.c_str(), dest);
  #if DEBUG
    cv::namedWindow( "OpenCV Test Program", cv::WINDOW_AUTOSIZE );
    cv::Mat writtenImg = cv::imread(outImagePath.c_str(),cv::IMREAD_COLOR);
    cv::imshow("OpenCV Test Program", writtenImg);
  #endif


  // Find minimum and maximum differences.
  double minval = 256, maxval = 0;
  int cnt = 0;
  for (int i = 0; i < diff.rows; i++) {
      for (int j = 0; j < diff.cols; j++) {
          unsigned char v = diff.at<unsigned char>(i, j);
          if (v > 0) cnt++;
          if (minval > v) minval = v;
          if (maxval < v) maxval = v;
      }
  }
  float err_per = 100.0 * (float)cnt / (image.rows * image.cols);

  std::cout << "Minimum error in intensity = " << minval << "\n"
            << "Maximum error in intensity = " << maxval << "\n"
            << "Percentage of pixels above error = " << err_per << std::endl;

  if (err_per > 0.0f) return EXIT_FAILURE;
  
  cv::waitKey(0);
  return 0;
}
