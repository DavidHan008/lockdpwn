/*
 * c++ ==> 객체지향 p361 10, Stack 클래스르 만들고 Push를 << 연산자를, Pop으로 >> 연산자를 오버로딩한 코드
 */
#include <iostream>
#include <string>
using namespace std;

static int count = 0;

class Stack{
  int *data;

 public:
  Stack();
  ~Stack();
  Stack& operator<<(int x);
  void operator>>(int& x);
  bool operator!();
};

Stack::Stack(){
  data = new int[3];
}

Stack::~Stack(){
  delete[] data;
}

Stack& Stack::operator<<(int x){
  this->data[count] = x;
  count++;
  return *this;
}

void Stack::operator>>(int& x){
  x = this->data[count - 1];
  count--;
}

bool Stack::operator!(){
  if(count == 0) return true;
  return false;
}

int main(int argc, char *argv[]){
  Stack stack;
  stack << 3 << 5 << 10;

  while(true){
    if(!stack) break;
    int x;
    stack >> x;
    cout << x << ' ';
  }

  cout << endl;
  return 0;
}
