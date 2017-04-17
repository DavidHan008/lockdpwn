/*
 * c++ ==> 객체지향 p267 7, add를 통해 값을 누적하는 Accumulator 클래스를 생성ㅎ고 .add(5).add(6).add(7)을 통해 값을 계속 누적시킨후 출력하는 코드
 */
#include <iostream>
#include <string>
using namespace std;

class Accumulator {
	int value;

public:
	Accumulator(int value);
	Accumulator(Accumulator& a);
	Accumulator& add(int n);
	int get();
};

Accumulator::Accumulator(int value) : value(value)
{}

Accumulator::Accumulator(Accumulator& a) {
	this->value = a.value;
}

Accumulator& Accumulator::add(int n) {
	this->value += n;
	return *this;
}

int Accumulator::get() {
	return this->value;
}

int main(int argc, const char *argv[]) {
	Accumulator acc(10);

	acc.add(5).add(6).add(7);
	cout << acc.get() << endl;

	return 0;
}


