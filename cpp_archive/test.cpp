/*
 * c++ ==> 객체지향 p455 3, LoopAdder 클래슬르 상속받는 ForLoopAdder를 구현하고 원하는 두 숫자를 입력하면 그 사이의 합을 리턴하는 코드
 */
#include <iostream>
#include <string>

using namespace std;

class LoopAdder {
	string name;  // 루프의 이름
	int x,y,sum;  
	void read();
	void write();

protected:
	LoopAdder(string name=""){  // 루프의 이름을 받는다
		this->name = name;
	}
	int getX() {return x;}
	int getY() {return y;}

	virtual int calculate() = 0;  // 루프를 돌면서 합을 구하는 순수가상함수

public:
	void run();
};

void LoopAdder::read(){
	cout << name << " : " << endl;
	cout << "처음 수에서 두번째 수까지 더합니다. 두 수를 입력하세요>> ";
	cin >> this->x >> this->y;
}

void LoopAdder::write(){
	cout << this->x << "에서 " << this->y << "까지의 합 = " << sum << " 입니다" << endl;
}

void LoopAdder::run(){
	read();
	sum = calculate();
	write();
}

class ForLoopAdder : public LoopAdder {
			
public:
	ForLoopAdder(string name) : LoopAdder(name) {}
	virtual int calculate(); 
};


int ForLoopAdder::calculate(){
	int tmp = 0;
	for(int i = getX() ; i <= getY() ; i++)
			tmp += i;

	return tmp;
}



int main(int argc, const char *argv[]){
	ForLoopAdder forLoop("For Loop");
	forLoop.run();

	return 0;
}
