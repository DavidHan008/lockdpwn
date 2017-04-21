/*
  c++ ==> 객체지향 p309 8, 디버깅에 필요한 Trace 클래스를 만들어 f() 함수가 동작하는 동안 Trace 정보를 저장해서 필요할 때 출력하는 코드
*/
#include <iostream>
#include <string>
using namespace std;

// 우선 100개의 트레이스 정보만 저장한다. 프로그램 확장시 동적으로 받도록 변경한다
static string trace[100] = string();
static int count =0;

class Trace{

 public:
  Trace() {}
  static void put(string func, string sentence);
  static void print(string func);
};

void Trace::put(string func, string sentence){
  trace[count] += func + ": " + sentence;
  count++;
}

void Trace::print(string func = string()){
  if(func == string()){
    cout << "------ 모든 Trace 정보를 출력합니다 -------" << endl;

    for (int i =0 ; i < count ; i++)
      cout << trace[i] << endl;
    return;
  }

  int len = func.length();
  int isThere = 0;

  cout << "------ " << func << "태그의 정보를 출력합니다 -------" << endl;
  for(int i = 0 ; i < count ; i++){
    isThere = trace[i].find(func, 0);
    if(isThere != -1)
      cout << trace[i] << endl;
  }
}

void f(){
  int a,b,c;
  cout << "두 개의 정수를 입력하세요>> ";
  cin >> a >> b;

  Trace::put("f()", "정수를 입력 받았음");  // 디버깅 정보 저장
  c = a + b;
  Trace::put("f()", "합 계산"); // 디버깅 정보 저장
  cout << "합은 " << c << endl;
}


int main(int argc, char *argv[]){
  Trace::put("main()", "프로그램 시작합니다");
  f();
  Trace::put("main()" , "종료");

  Trace::print("f()");  // f() 태그를 가진 디버깅 정보를 모두 출력한다
  Trace::print();  // 모든 디버깅 정보를 출력한다
  return 0;
}
