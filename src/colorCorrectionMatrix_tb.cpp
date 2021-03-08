#include <iostream>
#include<string>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include"math.h"
#include"cpu_kernels.h"
#include"timer.h"

#define CACHE_WARMUP 5 

const float bt2020_bt709_arr[3][3] = {
    {1.6605, -0.5876, -0.0728}, {-0.1246, 1.1329, -0.0083}, {-0.0182, -0.1006, 1.1187}};

const float bt2020_bt709_off[3] = {0.0, 0.0, 0.0};

const float bt709_bt2020_arr[3][3] = {{0.627, 0.329, 0.0433}, {0.0691, 0.92, 0.0113}, {0.0164, 0.088, 0.896}};

const float bt709_bt2020_off[3] = {0.0, 0.0, 0.0};

const float rgb_yuv_601_arr[3][3] = {{0.257, 0.504, 0.098}, {-0.148, -0.291, 0.439}, {0.439, -0.368, -0.071}};

const float rgb_yuv_601_off[3] = {0.0625, 0.500, 0.500};

const float rgb_yuv_709_arr[3][3] = {{0.183, 0.614, 0.062}, {-0.101, -0.338, 0.439}, {0.439, -0.399, -0.040}};

const float rgb_yuv_709_off[3] = {0.0625, 0.500, 0.500};

const float rgb_yuv_2020_arr[3][3] = {
    {0.225613, 0.582282, 0.050928}, {-0.119918, -0.309494, 0.429412}, {0.429412, -0.394875, -0.034537}};

const float rgb_yuv_2020_off[3] = {0.062745, 0.500, 0.500};

const float yuv_rgb_601_arr[3][3] = {{1.164, 0.000, 1.596}, {1.164, -0.813, -0.391}, {1.164, 2.018, 0.000}};

const float yuv_rgb_601_off[3] = {-0.87075, 0.52925, -1.08175};

const float yuv_rgb_709_arr[3][3] = {{1.164, 0.000, 1.793}, {1.164, -0.213, -0.534}, {1.164, 2.115, 0.000}};

const float yuv_rgb_709_off[3] = {-0.96925, 0.30075, -1.13025};

const float yuv_rgb_2020_arr[3][3] = {
    {1.164384, 0.000000, 1.717000}, {1.164384, -0.191603, -0.665274}, {1.164384, 2.190671, 0.000000}};

const float yuv_rgb_2020_off[3] = {-0.931559, 0.355379, -1.168395};

const float full_to_16_235_arr[3][3] = {
    {0.856305, 0.000000, 0.000000}, {0.000000, 0.856305, 0.000000}, {0.000000, 0.000000, 0.856305}};

const float full_to_16_235_off[3] = {0.0625, 0.0625, 0.0625};

const float full_from_16_235_arr[3][3] = {
    {1.167808, 0.000000, 0.000000}, {0.000000, 1.167808, 0.000000}, {0.000000, 0.000000, 1.167808}};

const float full_from_16_235_off[3] = {-0.0729880, -0.0729880, -0.0729880};

void colorcorrectionmatrix(cv::Mat& _src, cv::Mat& _dst, ccmTypeEnum ccmType) {
    float ccm_matrix[3][3];
    float offsetarray[3];

    switch (ccmType) {
        case bt2020_bt709:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = bt2020_bt709_arr[i][j];
                }
                offsetarray[i] = bt2020_bt709_off[i];
            }

            break;
        case bt709_bt2020:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = bt709_bt2020_arr[i][j];
                }
                offsetarray[i] = bt709_bt2020_off[i];
            }

            break;
        case rgb_yuv_601:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = rgb_yuv_601_arr[i][j];
                }
                offsetarray[i] = rgb_yuv_601_off[i];
            }

            break;
        case rgb_yuv_709:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = rgb_yuv_709_arr[i][j];
                }
                offsetarray[i] = rgb_yuv_709_off[i];
            }

            break;
        case rgb_yuv_2020:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = rgb_yuv_2020_arr[i][j];
                }
                offsetarray[i] = rgb_yuv_2020_off[i];
            }

            break;
        case yuv_rgb_601:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = yuv_rgb_601_arr[i][j];
                }
                offsetarray[i] = yuv_rgb_601_off[i];
            }

            break;
        case yuv_rgb_709:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = yuv_rgb_709_arr[i][j];
                }
                offsetarray[i] = yuv_rgb_709_off[i];
            }

            break;
        case yuv_rgb_2020:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = yuv_rgb_2020_arr[i][j];
                }
                offsetarray[i] = yuv_rgb_2020_off[i];
            }

            break;
        case full_to_16_235:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = full_to_16_235_arr[i][j];
                }
                offsetarray[i] = full_to_16_235_off[i];
            }

            break;
        case full_from_16_235:
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ccm_matrix[i][j] = full_from_16_235_arr[i][j];
                }
                offsetarray[i] = full_from_16_235_off[i];
            }

            break;
        default:
            break;
    }

    for (int i = 0; i < _src.rows; i++) {
        for (int j = 0; j < _src.cols; j++) {


          float _src_r = _src.at<cv::Vec3b>(i, j)[0];
          float _src_g = _src.at<cv::Vec3b>(i, j)[1];
          float _src_b = _src.at<cv::Vec3b>(i, j)[2];

          float value1 = (_src_r * ccm_matrix[0][0]);
          float value2 = (_src_g * ccm_matrix[0][1]);
          float value3 = (_src_b * ccm_matrix[0][2]);

          float value4 = (_src_r * ccm_matrix[1][0]);
          float value5 = (_src_g * ccm_matrix[1][1]);
          float value6 = (_src_b * ccm_matrix[1][2]);

          float value7 = (_src_r * ccm_matrix[2][0]);
          float value8 = (_src_g * ccm_matrix[2][1]);
          float value9 = (_src_b * ccm_matrix[2][2]);

          int value_r = (int)(value1 + value2 + value3 + offsetarray[0]);
          int value_g = (int)(value4 + value5 + value6 + offsetarray[1]);
          int value_b = (int)(value7 + value8 + value9 + offsetarray[2]);

          _dst.at<cv::Vec3b>(i, j)[0] = cv::saturate_cast<unsigned char>(value_r); // value_r;
          _dst.at<cv::Vec3b>(i, j)[1] = cv::saturate_cast<unsigned char>(value_g); // value_g;
          _dst.at<cv::Vec3b>(i, j)[2] = cv::saturate_cast<unsigned char>(value_b); // value_b;
        }
    }
}

int main( int argc, char** argv ) {
  
  cv::Mat diff, image;
  std::string imagePath = std::string(std::getenv("DATA")) + std::string("/SARSA.png");
  image = cv::imread(imagePath.c_str() , cv::IMREAD_COLOR);
  // imageGold = cv::imread("SARSA.png" ,cv::IMREAD_COLOR);
  
  if(! image.data) {
      std::cout << "Image not found or unable to open" << std::endl ;
      return -1;
    }

  cv::Mat imageGold, dest;
  imageGold =  cv::Mat::zeros(image.size(), CV_8UC3);
  dest =  cv::Mat::zeros(image.size(), CV_8UC3);

  image.convertTo(image, CV_8UC3); 

  std::cout << image.rows << " " << image.cols << std::endl;
 
  //OpenCV function
  ccmTypeEnum ccmType = bt2020_bt709;
  colorcorrectionmatrix(image, imageGold, ccmType);

  //Replicated CPU function
  //cache warmpup
  for(int i=0; i<CACHE_WARMUP; ++i){
    cpu::colorCorrectionMatrix(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                    ccmType);
  }
  //reset
  dest =  cv::Mat::zeros(image.size(), CV_8UC3);

  {
    cpu::Timer timer;
    cpu::colorCorrectionMatrix(image.data, image.rows, image.cols, image.step1(), image.channels(),
                    dest.data, dest.rows, dest.cols, dest.step1(), dest.channels(),
                    ccmType);
  }

  cv::absdiff(imageGold, dest, diff);
  // Save the difference image
  std::string diffImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/ccm_diff.png"));
  cv::imwrite(diffImagePath, diff);


  std::string outImagePath = std::string(std::getenv("OUTPUT")) + std::string(std::string("/ccm_out.png"));
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

        cv::Vec3s v = diff.at<cv::Vec3s>(i, j);
        if (fabs(v[0]) > 0.0f) cnt++;
        if (minval > v[0]) minval = v[0];
        if (maxval < v[0]) maxval = v[0];

        if (fabs(v[1]) > 0.0f) cnt++;
        if (minval > v[1]) minval = v[1];
        if (maxval < v[1]) maxval = v[1];

        if (fabs(v[2]) > 0.0f) cnt++;
        if (minval > v[2]) minval = v[2];
        if (maxval < v[2]) maxval = v[2];
      }
  }
  float err_per = 100.0 * (float)cnt / (image.rows * image.cols * image.channels());

  std::cout << "INFO: Verification results:" << std::endl;
  std::cout << "\tMinimum error in intensity = " << minval << std::endl;
  std::cout << "\tMaximum error in intensity = " << maxval << std::endl;
  std::cout << "\tPercentage of pixels above error threshold = " << err_per << std::endl;

  if (err_per > 1.0f) { //account for float precision
      fprintf(stderr, "ERROR: Test Failed.\n ");
      return EXIT_FAILURE;
  }
  
  cv::waitKey(0);
  return 0;
}
