#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include"cpu_kernels.h"
#include"timer.h"


#define CACHE_WARMUP 5


int main( int argc, char** argv ) {
  
  cv::Mat diff, image, dest, destDSA;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");
  image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);//only grayscale supported for minMaxLoc
  
  if(! image.data) {
      std::cout << "Image not found or unable to open" << std::endl ;
      return -1;
    }


  image.convertTo(image, CV_8U); 


  const int channels = image.channels();

  std::vector<cv::KeyPoint> keypoints;

  unsigned char threshold = 20; // threshold
 
  //OpenCV function
  cv::FAST(image, keypoints, threshold, true);


  //Replicated CPU function
  xy* keypointsDSA;
  int numCorners;
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i)
    keypointsDSA = cpu::fast(image.data, image.cols, image.rows, image.step1(), threshold, &numCorners);

  {
    cpu::Timer timer;
    keypointsDSA = cpu::fast(image.data, image.cols, image.rows, image.step1(), threshold, &numCorners);
  }

  // for(int i=0; i<numCorners; ++i){
  //   std::cout << "x=" << keypointsDSA[i].x << " y=" << keypointsDSA[i].y << std::endl; 
  // }
  std::cout << "Number of Keypoints from DSA " << numCorners << std::endl;
  std::cout << "Number of Keypoints from OCV " << keypoints.size() << std::endl;

  dest = image.clone();
  destDSA = image.clone();

  int x = 0, y = 0;

  for (int cnt1 = 0; cnt1 < numCorners; cnt1++) {
      x = keypointsDSA[cnt1].x;
      y = keypointsDSA[cnt1].y;
      cv::circle(destDSA, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), 2, 8, 0);
  }

  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/fastCornerDSA_out.png"));
  cv::imwrite(outImagePath.c_str(), destDSA);

  for (int cnt1 = 0; cnt1 < numCorners; cnt1++) {
      x = keypointsDSA[cnt1].x;
      y = keypointsDSA[cnt1].y;
      cv::circle(dest, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), 2, 8, 0);
  }

  outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/fastCorner_out.png"));
  cv::imwrite(outImagePath.c_str(), dest);
  
  cv::waitKey(0);
  return 0;
}