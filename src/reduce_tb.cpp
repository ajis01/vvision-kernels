#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"opencv2/core/core_c.h"
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {
  
  cv::Mat diff, image;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");
  image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
  
  if(! image.data) {
      std::cout << "Image not found or unable to open" << std::endl ;
      return -1;
    }

  cv::Mat imageGold, dest;

  unsigned char dimension = 1;
  unsigned char reduction = CV_REDUCE_AVG;
  
  #if dimension
    if ((reduction == CV_REDUCE_AVG) || (reduction == CV_REDUCE_SUM)) {
        dest.create(image.rows, 1, CV_32SC1);
        imageGold.create(image.rows, 1, CV_32SC1);
    } else {
        dest.create(image.rows, 1, CV_8UC1);
        imageGold.create(image.rows, 1, CV_8UC1);
    }

  #else
    if ((reduction == CV_REDUCE_AVG) || (reduction == CV_REDUCE_SUM)) {
        dest.create(1, image.cols, CV_32SC1);
        imageGold.create(1, image.cols, CV_32SC1);
    } else {
        dest.create(1, image.cols, CV_8UC1);
        imageGold.create(1, image.cols, CV_8UC1);
    }
  #endif

  std::cout << image.rows << " " << image.cols << std::endl;
 
  //OpenCV function
  if ((reduction == CV_REDUCE_AVG) || (reduction == CV_REDUCE_SUM))
      cv::reduce(image, imageGold, dimension, reduction, CV_32SC1); // avg, sum
  else
      cv::reduce(image, imageGold, dimension, reduction, CV_8UC1);

  //Replicated CPU function(without mask support)
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::reduce(image.data, image.rows, image.cols, image.step1(), image.channels(),
                dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                dimension, reduction);
  }
  //reset
  //not required as dest is assigned not updated

  {
    cpu::Timer timer;
    cpu::reduce(image.data, image.rows, image.cols, image.step1(), image.channels(),
                dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                dimension, reduction);
  }

  //Verification
  int err_cnt = 0;
  #if dimension
    for (unsigned int i = 0; i < dest.rows; i++) {
        unsigned int diff = imageGold.data[i] - (unsigned char)dest.data[i];
        if (diff > 1) err_cnt++;
    }

    std::cout << "INFO: Percentage of pixels with an error = " << (float)err_cnt * 100 / (float)dest.rows << "%"
              << std::endl;

  #endif
  #if dimension == 0
    for (int i = 0; i < dest.cols; i++) {
        unsigned int diff = imageGold.data[i] - (unsigned char)dest.data[i];
        if (diff > 1) err_cnt++;
    }

    std::cout << "INFO: Percentage of pixels with an error = " << (float)err_cnt * 100 / (float)dest.cols << "%"
              << std::endl;

  #endif

  if (err_cnt > 0) {
      fprintf(stderr, "ERROR: Test Failed.\n ");
      return EXIT_FAILURE;
  }

  else{
    std::cout << "Test passed." << std::endl;
  }
    
  cv::waitKey(0);
  return 0;
}
