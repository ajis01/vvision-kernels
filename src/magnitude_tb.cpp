#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 


////////////    Reference for L1NORM    //////////
int ComputeMagnitude(cv::Mat gradx, cv::Mat grady, cv::Mat& dst) {
    int row, col;
    int16_t gx, gy, tmp_res;
    int16_t tmp1, tmp2;
    int16_t res;
    for (row = 0; row < gradx.rows; row++) {
        for (col = 0; col < gradx.cols; col++) {
            gx = gradx.at<int16_t>(row, col);
            gy = grady.at<int16_t>(row, col);
            tmp1 = abs(gx);
            tmp2 = abs(gy);
            tmp_res = tmp1 + tmp2;
            res = (int16_t)tmp_res;
            dst.at<int16_t>(row, col) = res;
        }
    }
    return 0;
}

int main( int argc, char** argv ) {
  
  cv::Mat diff, image;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");
  image = cv::imread(imagePath.c_str() , cv::IMREAD_GRAYSCALE);
  
  if(! image.data) {
      std::cout << "Image not found or unable to open" << std::endl ;
      return -1;
    }

  cv::Mat imageGold, imageGoldTemp, dest, cGradX, cGradY, cGradX1, cGradY1;

  int scale = 1;
  int delta = 0;
  int filter_size = 3;

  /*  convert to gray  */
  cv::Sobel(image, cGradX, CV_16S, 1, 0, filter_size, scale, delta, cv::BORDER_CONSTANT);
  cv::Sobel(image, cGradY, CV_16S, 0, 1, filter_size, scale, delta, cv::BORDER_CONSTANT);

  dest.create(image.rows, image.cols, CV_16S);
  imageGold.create(image.rows, image.cols, CV_16S);
  imageGoldTemp.create(image.rows, image.cols, CV_32F);
  diff.create(image.rows, image.cols, CV_16S);

  std::cout << image.rows << " " << image.cols << std::endl;

  normTypeEnum normType = L2Norm;
 
  //OpenCV function
  if(normType ==  L1Norm)
    ComputeMagnitude(cGradX, cGradY, imageGold);
  else if(normType ==  L2Norm){
    cv::Sobel(image, cGradX1, CV_32FC1, 1, 0, filter_size, scale, delta, cv::BORDER_CONSTANT);
    cv::Sobel(image, cGradY1, CV_32FC1, 0, 1, filter_size, scale, delta, cv::BORDER_CONSTANT);
    cv::magnitude(cGradX1, cGradY1, imageGoldTemp);
    imageGoldTemp.convertTo(imageGold, CV_16S);
  }

  //Replicated CPU function
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::magnitude((int16_t*)cGradX.data, cGradX.rows, cGradX.cols, cGradX.step1(), cGradX.channels(),
                    (int16_t*)cGradY.data, cGradY.rows, cGradY.cols, cGradY.step1(), cGradY.channels(),
                    (int16_t*)dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(), normType);
  }
  //reset

  dest =  cv::Mat::zeros(image.rows, image.cols, CV_16S);

  {
    cpu::Timer timer;
    cpu::magnitude((int16_t*)cGradX.data, cGradX.rows, cGradX.cols, cGradX.step1(), cGradX.channels(),
                    (int16_t*)cGradY.data, cGradY.rows, cGradY.cols, cGradY.step1(), cGradY.channels(),
                    (int16_t*)dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(), normType);
  }

  cv::absdiff(imageGold, dest, diff);
  // Save the difference image
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/magnitude_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/magnitude_out.png"));
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
          uchar v = diff.at<uchar>(i, j);

          if (v > 1) cnt++;
          if (minval > v) minval = v;
          if (maxval < v) maxval = v;
      }
  }

  float err_per = 100.0 * (float)cnt / (image.rows * image.cols);
  std::cout << "Minimum error in intensity = " << minval << "\n"
            << "Maximum error in intensity = " << maxval << "\n"
            << "Percentage of pixels above error = " << err_per << std::endl;

  if (err_per > 0.0f) {
      return 1;
  }
  
  cv::waitKey(0);
  return 0;
}
