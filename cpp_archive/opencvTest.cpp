/*
  c++ ==> opencv Test
          컴파일 할 때 g++ -o main main.cpp `pkg-config opencv --cflags --libs` 와 같이 해줘야 한다
 */
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**)
{
  //웹캡으로 부터 데이터 읽어오기 위해 준비
  VideoCapture cap1(0);

  if (!cap1.isOpened())
  {
    printf("첫번째 카메라를 열수 없습니다. \n");
  }

  Mat frame1;
  namedWindow("camera1", 1);

  for (;;)
  {
    //웹캡으로부터 한 프레임을 읽어옴
    cap1 >> frame1;
    imshow("camera1", frame1);
    if (waitKey(20) >= 0) break;
  }

  return 0;
}
