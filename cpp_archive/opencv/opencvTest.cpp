/*
  c++ ==> opencvTest
          g++ -o opencvTest opencvTest.cpp `pkg-config opencv --cflags --libs`
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;


Mat function(){
  // 영상 생성
  Mat ima(240, 320, CV_8U, Scalar(100));

  // 영상 반환
  return ima;
}

int main(int argc, char *argv[]){
  Mat image;

  cout << "size: " << image.size().height << ", "
       << image.size().width << endl;

  image = imread("lenna.jpg");

  if(!image.data)
    return 0;

  cout << "size (after reading): "<< image.size().height << ", " << image.size().width << endl;

  namedWindow("Original Image");
  imshow("Original Image", image);

  Mat result;

  flip(image, result, 1);

  namedWindow("Output Image");
  imshow("Output Image", result);

  waitKey(0);
  imwrite("output.bmp", result);


  return 0;
}
