#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"cpu_kernels.h"
#include"timer.h"


#define CACHE_WARMUP 5

template <int CHNLS>
float* meanCV(cv::Mat& img) {
    unsigned long Sum[CHNLS] = {0};
    int i, j, c, k;
    float* val = (float*)malloc(CHNLS * sizeof(float));

    /* Sum of All Pixels */
    for (i = 0; i < img.rows; ++i) {
        for (j = 0; j < img.cols; ++j) {
            for (k = 0; k < CHNLS; ++k) {
                if (CHNLS == 1)
                    Sum[k] += img.at<uchar>(i, j); // imag.data[i]}
                else
                    Sum[k] += img.at<cv::Vec3b>(i, j)[k]; // imag.data[i]}
            }
        }
    }
    for (int ch = 0; ch < CHNLS; ++ch) {
        val[ch] = (float)Sum[ch] / (float)(img.rows * img.cols);
    }
    return val;
}
template <int CHNLS>
void varianceCV(cv::Mat& Img, float* mean, double* var) {
    double sum[CHNLS], b_sum = 0.0, g_sum = 0.0, r_sum = 0.0;
    int k;
    double x[CHNLS];
    for (int i = 0; i < Img.rows; i++) {
        for (int j = 0; j < Img.cols; j++) {
            for (k = 0; k < CHNLS; ++k) {
                if (CHNLS == 1)
                    x[k] = (double)mean[k] - ((double)Img.at<uint8_t>(i, j));
                else
                    x[k] = (double)mean[k] - ((double)Img.at<cv::Vec3b>(i, j)[k]);

                sum[k] = sum[k] + pow(x[k], (double)2.0);
            }
        }
    }
    for (int ch = 0; ch < CHNLS; ++ch) {
        var[ch] = (sum[ch] / (double)(Img.rows * Img.cols));
    }
}


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

  const int channels = image.channels();
 
  //OpenCV function
  float* mean = (float*)malloc(channels * sizeof(float));
  float* stddev = (float*)malloc(channels * sizeof(float));
  float* meanDSA = (float*)malloc(channels * sizeof(float));
  float* stddevDSA = (float*)malloc(channels * sizeof(float));
  double* sumDSA = (double*)malloc(channels * sizeof(double));
  double* xDSA = (double*)malloc(channels * sizeof(double));
  float* diffMean = (float*)malloc(channels * sizeof(float));
  float* diffStddev = (float*)malloc(channels * sizeof(float));
  double* var = (double*)malloc(channels * sizeof(double));


  #if GRAY
    mean = meanCV<1>(image);
    varianceCV<1>(image, mean, var);
  #else
    mean = meanCV<3>(image);
    varianceCV<3>(image, mean, var);
  #endif

  //Replicated CPU function(without mask support)
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i)
    cpu::meanStdDev(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    &meanDSA, &stddevDSA, sumDSA, xDSA);
  //reset
  #if GRAY
    sumDSA[0] = 0;
    xDSA[0] = 0;
  #else
    sumDSA[0] = 0;
    xDSA[0] = 0;
    sumDSA[1] = 0;
    xDSA[1] = 0;
    sumDSA[2] = 0;
    xDSA[2] = 0;
  #endif

  {
    cpu::Timer timer;
    cpu::meanStdDev(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    &meanDSA, &stddevDSA, sumDSA, xDSA);
  }

  // cv::absdiff(imageGold, dest, diff);
  // // Save the difference image
  // std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/accumulateSquared_diff.png"));
  // cv::imwrite(diffImagePath, diff);


  // std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/accumulateSquared_out.png"));
  // cv::imwrite(outImagePath.c_str(), dest);
  // #if DEBUG
  //   cv::namedWindow( "OpenCV Test Program", cv::WINDOW_AUTOSIZE );
  //   cv::Mat writtenImg = cv::imread(outImagePath.c_str(),cv::IMREAD_COLOR);
  //   cv::imshow("OpenCV Test Program", writtenImg);
  // #endif


  // double minval = 256, maxval = 0;
  // int cnt = 0;
  // for (int i = 0; i < image.rows; i++) {
  //     for (int j = 0; j < image.cols; j++) {
  // #if GRAY
  //         float v = diff.at<short>(i, j);
  //         if (v > 0.0f) cnt++;
  //         if (minval > v) minval = v;
  //         if (maxval < v) maxval = v;
  // #else
  //         cv::Vec3s v = diff.at<cv::Vec3s>(i, j);
  //         if (v[0] > 0.0f) cnt++;
  //         if (minval > v[0]) minval = v[0];
  //         if (maxval < v[0]) maxval = v[0];

  //         if (v[1] > 0.0f) cnt++;
  //         if (minval > v[1]) minval = v[1];
  //         if (maxval < v[1]) maxval = v[1];

  //         if (v[2] > 0.0f) cnt++;
  //         if (minval > v[2]) minval = v[2];
  //         if (maxval < v[2]) maxval = v[2];
  // #endif
  //     }
  // }
  // float err_per = 100.0 * (float)cnt / (image.rows * image.cols * image.channels());

  // std::cout << "INFO: Verification results:" << std::endl;
  // std::cout << "\tMinimum error in intensity = " << minval << std::endl;
  // std::cout << "\tMaximum error in intensity = " << maxval << std::endl;
  // std::cout << "\tPercentage of pixels above error threshold = " << err_per << std::endl;

  // if (err_per > 0.0f) {
  //     fprintf(stderr, "ERROR: Test Failed.\n ");
  //     return EXIT_FAILURE;
  // }

  for (int c = 0; c < channels; c++) {
      stddev[c] = sqrt(var[c]);
      // meanDSA[c] = (float)mean[c] / 256;
      // stddevDSA[c] = (float)stddev[c] / 256;
      diffMean[c] = mean[c] - meanDSA[c];
      diffStddev[c] = stddev[c] - stddevDSA[c];
      std::cout << "Ref. Mean =" << mean[c] << "\t"
                << "Result =" << meanDSA[c] << "\t"
                << "ERROR =" << diffMean[c] << std::endl;
      std::cout << "Ref. Std.Dev. =" << stddev[c] << "\t"
                << "Result =" << stddevDSA[c] << "\t"
                << "ERROR =" << diffStddev[c] << std::endl;

      if (abs(diffMean[c]) > 0.5f | abs(diffStddev[c]) > 0.5f) {
          fprintf(stderr, "ERROR: Test Failed.\n ");
          return -1;
      }
  }

  free(mean);
  free(stddev);
  free(meanDSA);
  free(stddevDSA);
  free(sumDSA);
  free(xDSA);
  free(var);
  free(diffMean);
  free(diffStddev);
  
  cv::waitKey(0);
  return 0;
}
