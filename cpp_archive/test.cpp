/*
 * c++ ==> 객체지향 p410 5,6 , BaseArray 클래스를 상속받는 MyQueue 클래스와 MyStack 클래스를 작성하고 사용해 본 코드
 */
#include <iostream>
#include <string>

using namespace std;

class BaseArray {
private:
	int capacity;
	int *mem;

protected:
	BaseArray(int capacity=100){
		this->capacity = capacity; 
		mem = new int[capacity];
	}
	~BaseArray() { delete[] mem; }

	void put(int index, int val) { mem[index] = val; }
	int get(int index) { return mem[index]; }
	int getCapacity() { return capacity; }
};

class MyQueue : public BaseArray {
	int count;
public:
	MyQueue(int cap) : BaseArray(cap) {
		count = 0;
	}

	int capacity();
	void enqueue(int val);
	int dequeue();
	int length();
};

int MyQueue::capacity(){
	return getCapacity();
}

void MyQueue::enqueue(int val){
	put(count++, val);
}

int MyQueue::dequeue(){
	return get(--count);
}

int MyQueue::length(){
	return count;
}

class MyStack : public BaseArray {

public:
		
};

int main(int argc, const char *argv[]){
	MyQueue mQ(100);

	int n;
	cout << "큐에 삽입할 5개의 정수를 입력하라>> ";

	for(int i =0 ; i< 5; i++){
		cin >> n;
		mQ.enqueue(n);
	}

	cout << "큐의 용량: " << mQ.capacity() << ", 큐의 크기: " << mQ.length() << endl;

	cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";

	while(mQ.length() != 0){
		cout << mQ.dequeue() << ' ';
	}

	cout << endl << "큐의 현재 크기 : " << mQ.length() << endl;

	return 0;
}




