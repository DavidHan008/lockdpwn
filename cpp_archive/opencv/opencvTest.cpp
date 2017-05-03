/*
  c++ ==> opencvTest
          g++ -o opencvTest opencvTest.cpp `pkg-config opencv --cflags --libs`
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

cv::Mat function(){
  // 영상 생성
  cv::Mat ima(240, 320, CV_8U, cv::Scalar(100));

  // 영상 반환
  return ima;
}

int main(int argc, char *argv[]){
  cv::Mat image;

  cout << "size: " << image.size().height << ", "
       << image.size().width << endl;

  image = cv::imread("lenna.jpg");

  if(!image.data)
    return 0;

  cout << "size (after reading): "<< image.size().height << ", " << image.size().width << endl;

  cv::namedWindow("Original Image");
  cv::imshow("Original Image", image);

  cv::Mat result;

  cv::flip(image, result, 1);

  cv::namedWindow("Output Image");
  cv::imshow("Output Image", result);

  cv::waitKey(0);
  cv::imwrite("output.bmp", result);


  return 0;
}
