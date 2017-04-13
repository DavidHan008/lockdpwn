#include <iostream>
#include <string>
using namespace std;

class Person{
  string name;
  string tel;

 public:
  Person() {}
  string getName() { return name; }
  string getTel() { return tel; }
  void set(string name, string tel);
};

void Person::set(string name, string tel){
  this->name = name;
  this->tel = tel;
}

int main(int argc, const char *argv[]){
  int i = 0;
  Person *p = new Person[3];
  string str[3];
  string name;

  cout << "이름과 전화번호를 입력해 주세요" << endl;
  cout << "사람 1>> ";
  getline(cin, str[0], '\n');
  cout << "사람 2>> ";
  getline(cin, str[1], '\n');
  cout << "사람 3>> ";
  getline(cin, str[2], '\n');

  p[0].set(str[0].substr(0,9), str[0].substr(10,13));
  p[1].set(str[1].substr(0,9), str[1].substr(10,13));
  p[2].set(str[2].substr(0,9), str[2].substr(10,13));

  cout << "모든 사람의 이름은 " << p[0].getName() << ", " << p[1].getName() << ", " << p[2].getName() << endl;
  cout << "전화번호를 검색합니다. 이름을 입력하세요 >> ";
  cin >> name;

  for (i = 0; i < 3; i++)
    if (name == p[i].getName())
      break;

  cout << "전화번호는 " << p[i].getTel();
  return 0;
}
