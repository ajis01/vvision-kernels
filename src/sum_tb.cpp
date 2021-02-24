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

  #if GRAY  
    image.convertTo(image, CV_32F); 
  #else 
    image.convertTo(image, CV_32FC3); 
  #endif

  std::cout << image.rows << " " << image.cols << std::endl;

  // OpenCV function
  std::vector<double> sumGold(image.channels());

  for (int i = 0; i < image.channels(); ++i) sumGold[i] = cv::sum(image)[i];

  double* sumCPU = (double*)malloc(image.channels() * sizeof(double));


  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::sum((float*)image.data, image.rows, image.cols, image.step1(), image.channels(),
                      sumCPU);
  }
  //reset
  for (int i = 0; i < image.channels(); ++i) sumCPU[i] = 0;

  {
    cpu::Timer timer;
    cpu::sum((float*)image.data, image.rows, image.cols, image.step1(), image.channels(),
                      sumCPU);
  }


  for (int i = 0; i < image.channels(); i++) {
      printf("sum of opencv is === %lf\n", sumGold[i]);
      printf("sum of cpu is ====== %lf\n", sumCPU[i]);
  }

  // Results verification:
  int cnt = 0;

  for (int i = 0; i < image.channels(); i++) {
      if (abs(double(sumGold[i]) - sumCPU[i]) > 0.01f) cnt++;
  }

  if (cnt > 0) {
      fprintf(stderr, "INFO: Error percentage = %f. Test Failed.\n ", 100.0 * float(cnt) / float(image.channels()));
      return EXIT_FAILURE;
  } else
      std::cout << "Test Passed." << std::endl;
  
  free(sumCPU);
  cv::waitKey(0);
  return 0;
}
