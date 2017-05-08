#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat function(){
	Mat ima(240, 320, CV_8U, Scalar(100));
	return ima;
}

int main(int argc, const char *argv[]){
	Mat image;

	cout << "size : " << image.size().height << ", " << image.size().width << endl;




	
	return 0;
}


























