/*
	c++ ==> opencv, hangeulSample.png를 grid를 제거한 후 각각의 한글데이터만 따로 잘라서 저장하는 코드
*/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace cv;

/// 마우스를 클릭하면 발생하면 콜백함수
void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
	if (event == EVENT_LBUTTONDOWN) {
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN) {
		cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN) {
		cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
}


int main(int argc, const char *argv[]) {
	Mat image = imread("hangeulSample.png");
	if (!image.data) return 0;

	// 이미지 크기를 입력한다
	int horizontal = 55;
	int vertical = 77;
	Mat tile;
	stringstream ss;
	string name = "cropped_";
	string type = ".jpg";
	string filename = "";
	int count = 0;

	// rows : 세로 픽셀 길이
	// cols : 가로 픽셀 길이 
	// 이미지를 (horizontal,vertical) 사이즈로 자른다음 image%d.jpg로 반복해서 저장하는 코드
	for (int r = 0; r < image.rows; r += vertical)
		for (int c = 0; c < image.cols; c += horizontal){
			tile = image(Range(r, min(r + vertical, image.rows)),
				Range(c, min(c + horizontal, image.cols)));//no data copying here

			// 너무 작은 이미지들은 skip 한다
			if (tile.rows < vertical - 5 ||  tile.cols < horizontal -5)
				continue;
			
			// 이미지 테두리를 제거한다
			tile = tile(Rect(5,10, 50, 55));
			
			ss << name << (count + 1) << type;
			count++;
			filename = ss.str();
			ss.str("");
			imwrite(filename, tile);
		}



	waitKey(0);
	return 0;
}

