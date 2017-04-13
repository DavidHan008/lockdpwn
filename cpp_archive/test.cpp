#include <iostream>
#include <string>

#define PI 3.14159
using namespace std;

class Circle {
	int radius;

public:
	void setRadius(int radius);
	double getArea();
};

void Circle::setRadius(int radius) {
	this->radius = radius;
}

double Circle::getArea() {
	return this->radius * this->radius * PI;
}

int main(int argc, const char *argv[]) {
	int numCircle;
	int rad;
	int count = 0;
	cout << "원의 개수 >> ";
	cin >> numCircle;

	Circle *c = new Circle[numCircle];

	for (int i = 1; i <= numCircle; i++){
		cout << "원" << i << "의 반지름 >> ";
		cin >> rad;
		c[i - 1].setRadius(rad);
	}

	for (int j = 0; j < numCircle; j++){
		if (c[j].getArea() >= 100)
			count++;
	}

	cout << "면적이 100보다 큰 원은 " << count << "개 입니다" << endl;
	return 0;
}

