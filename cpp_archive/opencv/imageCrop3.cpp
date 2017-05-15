/*
	c++ ==> opencv, hangeulSample.png�� grid�� ������ �� ������ �ѱ۵����͸� ���� �߶� �����ϴ� �ڵ�
*/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace cv;

/// ���콺�� Ŭ���ϸ� �߻��ϸ� �ݹ��Լ�
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

	// �̹��� ũ�⸦ �Է��Ѵ�
	int horizontal = 55;
	int vertical = 77;
	Mat tile;
	stringstream ss;
	string name = "cropped_";
	string type = ".jpg";
	string filename = "";
	int count = 0;

	// rows : ���� �ȼ� ����
	// cols : ���� �ȼ� ���� 
	// �̹����� (horizontal,vertical) ������� �ڸ����� image%d.jpg�� �ݺ��ؼ� �����ϴ� �ڵ�
	for (int r = 0; r < image.rows; r += vertical)
		for (int c = 0; c < image.cols; c += horizontal){
			tile = image(Range(r, min(r + vertical, image.rows)),
				Range(c, min(c + horizontal, image.cols)));//no data copying here

			// �ʹ� ���� �̹������� skip �Ѵ�
			if (tile.rows < vertical - 5 ||  tile.cols < horizontal -5)
				continue;
			
			// �̹��� �׵θ��� �����Ѵ�
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

