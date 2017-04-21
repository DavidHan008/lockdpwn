/*
 * c++ ==> 객체지향 p358 5, 2차원 행렬을 추상화한 Matrix 클래스를 생성해서 행렬값을 입력받고 + , +=, == 연산자를 오버로딩해 본 코드
 */ 
#include <iostream>
#include <string>
using namespace std;

class Matrix {
	int mat[4];

public:
	Matrix(int a, int b, int c, int d);
	void show();
	Matrix operator+(Matrix a);
	Matrix operator+=(Matrix a);
	bool operator==(Matrix m);
};

Matrix::Matrix(int a = 0, int b = 0, int c = 0, int d=0) {
	mat[0] = a;
	mat[1] = b;
	mat[2] = c;
	mat[3] = d;
}

void Matrix::show() {
	cout << "{ " << mat[0] << " " << mat[1] << " " << mat[2] << " " << mat[3] << " }" << endl;
}

bool Matrix::operator==(Matrix m) {
	if (mat[0] == m.mat[0])
		if (mat[1] == m.mat[1])
			if (mat[2] == m.mat[2])
				if (mat[3] == m.mat[3])
					return true;
	return false;
}

Matrix Matrix::operator+(Matrix a) {
	Matrix tmp(a.mat[0] + this->mat[0], a.mat[1] + this->mat[1], a.mat[2] + this->mat[2], a.mat[3] + this->mat[3]);
	return tmp;
}

Matrix Matrix::operator+=(Matrix a) {
	this->mat[0] += a.mat[0];
	this->mat[1] += a.mat[1];
	this->mat[2] += a.mat[2];
	this->mat[3] += a.mat[3];
	return *this;
}

int main(int argc, const char *argv[]) {
	Matrix a(1, 2, 3, 4);
	Matrix b(2, 3, 4, 5);
	Matrix c;
	Matrix d(4,3,2,1);
	Matrix e;

	c = a + b;
	a += b;
	a.show();
	b.show();
	c.show();

	if (a == c)
		cout << "a and c are the same" << endl;

	





	return 0;
}

