#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

int main( int argc, char** argv ) {


  unsigned char lut[256] = {
    0,   16,  23,  28,  32,  36,  39,  42,  45,  48,  50,  53,  55,  58,  60,  62,  64,  66,  68,  70,  71,  73,
    75,  77,  78,  80,  81,  83,  84,  86,  87,  89,  90,  92,  93,  94,  96,  97,  98,  100, 101, 102, 103, 105,
    106, 107, 108, 109, 111, 112, 113, 114, 115, 116, 117, 118, 119, 121, 122, 123, 124, 125, 126, 127, 128, 129,
    130, 131, 132, 133, 134, 135, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 145, 146, 147, 148, 149,
    150, 151, 151, 152, 153, 154, 155, 156, 156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 164, 165, 166, 167,
    167, 168, 169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178, 179, 179, 180, 181, 181, 182, 183,
    183, 184, 185, 186, 186, 187, 188, 188, 189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 196, 196, 197, 198,
    198, 199, 199, 200, 201, 201, 202, 203, 203, 204, 204, 205, 206, 206, 207, 208, 208, 209, 209, 210, 211, 211,
    212, 212, 213, 214, 214, 215, 215, 216, 217, 217, 218, 218, 219, 220, 220, 221, 221, 222, 222, 223, 224, 224,
    225, 225, 226, 226, 227, 228, 228, 229, 229, 230, 230, 231, 231, 232, 233, 233, 234, 234, 235, 235, 236, 236,
    237, 237, 238, 238, 239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246, 247, 247, 248,
    248, 249, 249, 250, 250, 251, 251, 252, 252, 253, 253, 254, 254, 255};
  
  cv::Mat diff, image, lutMat;
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
    imageGold =  cv::Mat::zeros(image.rows, image.cols, CV_8U);
    dest =  cv::Mat::zeros(image.rows, image.cols, CV_8U);
  #else
    imageGold =  cv::Mat::zeros(image.size(), CV_8UC3);
    dest =  cv::Mat::zeros(image.size(), CV_8UC3);
  #endif
  cv::Mat aux;

//simplifying depth
//only doing for CV_8U
  #if GRAY  
    image.convertTo(image, CV_8U); 
  #else 
    image.convertTo(image, CV_8UC3); 
  #endif

  std::cout << image.rows << " " << image.cols << std::endl;
 
  //OpenCV function
  lutMat = cv::Mat(1, 256, CV_8UC1, lut);
  cv::LUT(image, lutMat, imageGold);

  //Replicated CPU function
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::lut(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                    lut);
  }
  //reset
  #if GRAY
    dest =  cv::Mat::zeros(image.rows, image.cols, CV_8U);
  #else
    dest =  cv::Mat::zeros(image.size(), CV_8UC3);
  #endif

  {
    cpu::Timer timer;
    cpu::lut(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                    lut);
  }

  cv::absdiff(imageGold, dest, diff);
  // Save the difference image
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/lut_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/lut_out.png"));
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
  #if GRAY
          float v = diff.at<uchar>(i, j);
          if (fabs(v) > 0.0f) cnt++;
          if (minval > v) minval = v;
          if (maxval < v) maxval = v;
  #else
          cv::Vec3s v = diff.at<cv::Vec3b>(i, j);
          if (fabs(v[0]) > 0.0f) cnt++;
          if (minval > v[0]) minval = v[0];
          if (maxval < v[0]) maxval = v[0];

          if (fabs(v[1]) > 0.0f) cnt++;
          if (minval > v[1]) minval = v[1];
          if (maxval < v[1]) maxval = v[1];

          if (fabs(v[2]) > 0.0f) cnt++;
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
