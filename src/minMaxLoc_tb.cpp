#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"cpu_kernels.h"
#include"timer.h"


#define CACHE_WARMUP 5


int main( int argc, char** argv ) {
  
  cv::Mat diff, image;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");
  image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);//only grayscale supported for minMaxLoc
  
  if(! image.data) {
      std::cout << "Image not found or unable to open" << std::endl ;
      return -1;
    }


  image.convertTo(image, CV_8U); 


  const int channels = image.channels();

  double cvMinval = 0, cvMaxval = 0;
  double minVal = INT_MAX, maxVal = INT_MIN;
  int minXLoc;
  int minYLoc;
  int maxXLoc;
  int maxYLoc;
  cv::Point cvMinloc, cvMaxloc;
 
  //OpenCV function
  cv::minMaxLoc(image, &cvMinval, &cvMaxval, &cvMinloc, &cvMinloc, cv::noArray());


  //Replicated CPU function(without mask support)
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i)
    cpu::minMaxLoc(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    minVal, maxVal, minXLoc, minYLoc, maxXLoc, maxYLoc);
  //reset
  minVal = INT_MAX;
  maxVal = INT_MIN;

  {
    cpu::Timer timer;
    cpu::minMaxLoc(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    minVal, maxVal, minXLoc, minYLoc, maxXLoc, maxYLoc);
  }

  /////// OpenCV output ////////
  std::cout << "OCV-Minvalue = " << cvMinval << std::endl;
  std::cout << "OCV-Maxvalue = " << cvMaxval << std::endl;
  std::cout << "OCV-Min Location.x = " << cvMinloc.x << "  OCV-Min Location.y = " << cvMinloc.y << std::endl;
  std::cout << "OCV-Max Location.x = " << cvMaxloc.x << "  OCV-Max Location.y = " << cvMaxloc.y << std::endl;

  /////// Kernel output ////////
  std::cout << "DSA-Minvalue = " << minVal << std::endl;
  std::cout << "DSA-Maxvalue = " << maxVal << std::endl;
  std::cout << "DSA-Min Location.x = " << minXLoc << "  DSA-Min Location.y = " << minYLoc << std::endl;
  std::cout << "DSA-Max Location.x = " << maxXLoc << "  DSA-Max Location.y = " << maxYLoc << std::endl;

  /////// printing the difference in min and max, values and locations of both OpenCV and Kernel function /////
  printf("Difference in Minimum value: %lf \n", (cvMinval - minVal));
  printf("Difference in Maximum value: %lf \n", (cvMaxval - maxVal));
  printf("Difference in Minimum value location: (%d,%d) \n", (cvMinloc.y - minYLoc), (cvMinloc.x - minXLoc));
  printf("Difference in Maximum value location: (%d,%d) \n", (cvMaxloc.y - maxYLoc), (cvMaxloc.x - maxXLoc));

  if (((cvMinloc.y - minYLoc) > 1) | ((cvMinloc.x - minXLoc) > 1)) {
      fprintf(stderr, "ERROR: Test Failed.\n ");
      return -1;
  }
  
  cv::waitKey(0);
  return 0;
}