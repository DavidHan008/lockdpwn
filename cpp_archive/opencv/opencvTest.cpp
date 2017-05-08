/*
   c++ ==> opencv,

		   g++ -o opencvTest opencvTest.cpp `pkg-config opencv --cflags --libs`
*/

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

int main(int argc, const char *argv[]){
	Mat image = imread("lenna.jpg");

	if(!image.data) return 0;
	
	Rect rect(100,30, 150, 300);
	
	Mat subImage = image(rect);

	imshow("image.jpg", subImage);

	return 0;
}
