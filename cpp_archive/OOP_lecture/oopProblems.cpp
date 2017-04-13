
------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------
/*
 *	c++ ==> 객체지향 p207 7, Person 클래스에서
 */
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




------------------------------------------------------
/*
 * c++ ==> 객체지향 p207 6, Circle의 객체의 갯수를 동적할당 받아 원의 넓이를 구하는 코드
 */
#include <iostream>

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

  // 동적으로 Circle 객체의 수를 지정하는 코드!
  Circle *c = new Circle[numCircle];

  for (int i = 0; i < numCircle; i++){
    cout << "원" << i+1 << "의 반지름 >> ";
    cin >> rad;
    c[i].setRadius(rad);
  }

  for (int j = 0; j < numCircle; j++){
    if (c[j].getArea() >= 100)
      count++;
  }

  cout << "면적이 100보다 큰 원은 " << count << "개 입니다" << endl;
  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p205 3, string 클래스를 이용하여 사용자가 입력한 영문 한 줄을 글자하나만 랜덤하게 수정하는 코드
 */
#include <iostream>
#include <string>
#include <random>
#include <ctime>
using namespace std;

// 랜덤한 문자 하나를 출력하기 위해 선언한 배열
static const char alphanum[] =
                                                               "0123456789"
                                                               "!@#$%^&*"
                                                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                               "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

// 랜덤한 문자 하나를 반환하는 함수
char genRandom()  
{
  return alphanum[rand() % stringLength];
}

class String {
  string sentence;

 public:
  String() {}
  ~String() {}
  void setSentence(string sen);
  void modifyRandomOneWord();
  string getSentence();
  void exitProgram();
};

// 문장을 받아서 저장하는 멤버함수
void String::setSentence(string sen) {
  if (sen == "exit")
    this->exitProgram();

  this->sentence = sen;
}

// 문장의 임의의 한 단어를 바꾸는 멤버함수
void String::modifyRandomOneWord() {
  int index = rand() % sentence.length();
  string r(1, genRandom());

  // 특정한 Index 부분의 1단어를 랜덤한 문자로 바꾼다
  this->sentence.replace(index, 1,r);
}

string String::getSentence() {
  return this->sentence;
}

void String::exitProgram() {
  cout << "Bye! " << endl;
  exit(0);
}

int main() {
  srand((unsigned)time(0));
  String s;
  string tmp;
	
  cout << "아래에 한 줄을 입력하세요 (exit를 입력하면 종료합니다)" << endl;
  while (1) {
    cout << ">> ";
    getline(cin, tmp, '\n');

    s.setSentence(tmp);
    s.modifyRandomOneWord();
    cout << s.getSentence() << endl;
  }
  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p198 open challange, 한글 끝말잇기 게임을 수행하는 코드
 */
#include <iostream>
#include <string>

class Player {
  string name;

 public:
  Player() {}
  void setName(string name);
  string getName();

};

class WordGame{
  string word[2];

 public:
  WordGame() {}
  void startGame();
  void runGame(Player *p, int arrayLen);
  void loseGame(Player p);
};


void WordGame::startGame() {
  cout << "시작하는 단어는 아버지입니다" << endl;
}

void WordGame::runGame(Player *p, int arrayLen){
  int i = 0;
  int j = 0;
  bool isFirst = true;
  string startWord = "아버지";

  while (1){
    cout << p[i].getName() << ">> ";
    cin >> this->word[j];

    /// 첫판인 경우 : 아버지 --> 지oo
    if (i == 0 && isFirst == true)
      if (word[0].at(0) != startWord.at(startWord.length() - 2) || word[0].at(1) != startWord.at(startWord.length() - 1))
        this->loseGame(p[i]);
      else {
        i++;
        j = 1;
        isFirst = false;
        continue;
      }

    /// 두번째 판부터 아래 코드로 동작한다
    if (j == 0) {
      if (word[j].at(0) != word[j+1].at(word[j+1].length()-2) || word[j].at(1) != word[j+1].at(word[j+1].length()-1))
        this->loseGame(p[i]);
      j = 1;
    }
    else if (j == 1) {
      if (word[j].at(0) != word[j - 1].at(word[j - 1].length()-2) || word[j].at(1) != word[j - 1].at(word[j - 1].length()-1))
        this->loseGame(p[i]);
      j = 0;
    }

    i++;
    if (i > arrayLen - 1) i = 0;
  }
}

void WordGame::loseGame(Player p) {
  cout << "틀렸습니다 " << p.getName() << endl;
  exit(0);
}

void Player::setName(string name){
  this->name = name;
}

string Player::getName() {
  return this->name;
}

int main(int argc, const char *argv[]){
  string tmp;
  int numOfPlayer;
  WordGame wg;

  cout << "끝말잇기 게임을 시작합니다" << endl;
  cout << "게임에 참가하는 인원은 몇명입니까? >> ";
  cin >> numOfPlayer;

  Player *p = new Player[numOfPlayer];

  for (int i = 0; i < numOfPlayer; i++){
    cout << "참가자의 이름을 입력하세요. 빈칸 없이 >> ";
    cin >> tmp;
    p[i].setName(tmp);
  }

  /// 끝말잇기 게임을 시작한다
  wg.startGame();
  wg.runGame(p, numOfPlayer);

  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p149 10, RAM을 추상화한 Ram 클래스를 만들어보고 실제로 사용해본 코드
 */
#include <iostream>
#include <string>

class Ram{
  char mem[100 * 1024];
  int size;

 public:
  Ram();
  ~Ram();
  char read(int address);
  void write(int address, char value);
};

Ram::Ram(){
  mem[100 * 1024] = { 0, };
}

Ram::~Ram(){
  cout << "메모리 제거됨" << endl;
}

char Ram::read(int address){
  return mem[address];
}

void Ram::write(int address, char value){
  mem[address] = value;
}


int main(int argc, const char *argv[]){
  Ram ram;
  ram.write(100, 20);
  ram.write(101, 30);
  char res = ram.read(100) + ram.read(101);
  ram.write(102, res);
  cout << "102 번지의 값 = " << (int)ram.read(102) << endl;
  return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p147 7, 타원객체 Oval을 만들고 소멸자에 특별한 메세지를 넣어 사용해본 코드
 */
#include <iostream>
#include <string>
using namespace std;

class Oval
{
  int width;
  int height;

 public:
  Oval() : width(1), height(1) {}
  Oval(int w, int h) : width(w), height(h) {}

  int getWidth();
  int getHeight();
  void set(int w, int h);
  void show();
  ~Oval();
};

int Oval::getWidth()
{
  return width;
}

int Oval::getHeight()
{
  return height;
}

void Oval::set(int w, int h)
{
  this->width = w;
  this->height = h;
}

void Oval::show()
{
  cout << "width is : " << this->width << " and height is : " << this->height << endl;
}

Oval::~Oval()
{
  cout << "Oval 소멸 : width = " << this->width << ", height = " << this->height << endl;
}


int main(int argc, const char *argv[])
{
  Oval a, b(3, 4);
  a.set(10, 20);
  a.show();
  cout << b.getWidth() << "," << b.getHeight() << endl;

  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p146 6, int 타입의 정수를 객체화한 Integer 클래스를 작성하고 이를 사용해본 코드
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Integer
{
  int intnum;

 public:
  Integer(int n) : intnum(n) {}
  Integer(string str) : intnum(stoi(str)) {}

  int get(){
    return intnum;
  }
  void set(int a){
    this->intnum = a;
  }
  bool isEven() {
    if (intnum % 2 == 0) return true;
		
    return false;
  }
  bool isOdd() {
    if (intnum % 2 != 0 && (intnum % 3 == 0 || intnum % 5 == 0 || intnum % 7 == 0)) return true;

    return false;
  }
};

int main(int argc, const char *argv[])
{
  Integer n(30);
  cout << n.get() << ' ';
  n.set(50);
  cout << n.get() << ' ';

  Integer m("300");
  cout << m.get() << ' ';
  cout << m.isEven();

  return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p145 5, 짝수 또는 홀수 난수만 생성하는 SelectableRandom 클래스를 만들고 이를 사용하는 코드
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class SelectableRandom
{
 private:
  int ranNum;

 public:
  SelectableRandom()
  {
    // 난수를 발생시키는 코드 2줄!
    srand((unsigned)time(0));
    ranNum = rand() % (RAND_MAX + 1);
  }
  int nextOdd();
  int nextEven();
  int nextInRangeOdd(int min, int max);
  int nextInRangeEven(int min, int max);
};

int SelectableRandom::nextOdd()
{
  while (1)
  {
    ranNum = rand() % RAND_MAX;
    if ((ranNum % 3 == 0  || intnum % 5 == 0 || intnum % 7 == 0) && ranNum % 2 != 0 || ranNum == 1) break;
  }
  return ranNum;
}

int SelectableRandom::nextEven()
{
  while (1)
  {
    ranNum = rand() % RAND_MAX;
    if (ranNum % 2 == 0) break;
  }
  return ranNum;
}

int SelectableRandom::nextInRangeOdd(int min, int max)
{
  while (1)
  {
    ranNum = rand() % (max + 1);
    if (ranNum >= min && ((ranNum % 3 == 0 || intnum % 5 == 0 || intnum % 7 == 0) && ranNum % 2 != 0 || ranNum == 1)) break;
  }
  return ranNum;
}

int SelectableRandom::nextInRangeEven(int min, int max)
{
  while (1)
  {
    ranNum = rand() % (max + 1);
    if (ranNum >= min && ranNum % 2 == 0) break;
  }
  return ranNum;
}

int main(int argc, const char *argv[])
{
  SelectableRandom r;
  cout << "-- 0에서 " << RAND_MAX << "까지의 짝수 랜덤 정수 10개--" << endl;

  for (int i = 0; i< 10; i++)
  {
    int n = r.nextEven();
    cout << n << ' ';
  }

  cout << endl << endl << "-- 2에서 " << " 4까지의 홀수 랜덤 정수 10개 --" << endl;

  for (int i = 0; i<10; i++)
  {
    int n = r.nextInRangeOdd(2, 90);
    cout << n << ' ';
  }
  cout << endl;

  return 0;
}




------------------------------------------------------
/*
 * 	c++ ==> 객체지향 p144 3, 랜덤수를 발생시키는 Random 클래스를 만들어서 next(), nextInRange() 함수를 통해 랜덤수를 출력하는 코드
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Random
{
 private:
  int ranNum;

 public:
  Random()
  {
    // 난수를 발생시키는 코드 2줄!
    srand((unsigned)time(0));
    ranNum = rand() % (RAND_MAX + 1);
  }
  int next();
  int nextInRange(int min, int max);
};

int Random::next()
{
  ranNum = rand() % RAND_MAX;
  return ranNum;
}

// 최대 최소가 있는 난수를 발생시키는 함수
int Random::nextInRange(int min, int max)
{
  while (1)
  {
    ranNum = rand() % (max + 1);
    if (ranNum >= min) break;
  }
  return ranNum;
}


int main(int argc, const char *argv[])
{
  Random r;
  cout << "-- 0에서 " << RAND_MAX << "까지의 랜덤 정수 10개--" << endl;

  for (int i = 0; i< 10; i++)
  {
    int n = r.next();
    cout << n << ' ';
  }

  cout << endl << endl << "-- 2에서 " << " 4까지의 랜덤 정수 10개 --" << endl;

  for (int i = 0; i<10; i++)
  {
    int n = r.nextInRange(2, 4);
    cout << n << ' ';
  }
  cout << endl;

  return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p144 2, 날짜 클래스 Date를 작성하고 main문을 통해 사용해보는 코드
 */
#include <iostream>
#include <string>

using namespace std;

class Date
{
 private:
  int year;
  int month;
  int day;

 public:
  Date(int y, int m, int d) : year(y), month(m), day(d)
  {}

  Date(string str)
  {
    year = stoi(str.substr(0, 4));
    month = stoi(str.substr(5, 1));
    day = stoi(str.substr(7, 2));
  }

  void show();
  int getYear();
  int getMonth();
  int getDay();
};

void Date::show()
{
  cout << this->year << "년 " << this->month << "월 " << this->day << "일 " << endl;
}

int Date::getYear()
{
  return this->year;
}

int Date::getMonth()
{
  return this->month;
}

int Date::getDay()
{
  return this->day;
}

int main()
{
  Date birth(2014, 3, 20);
  Date indepen("1945/8/15");
	
  indepen.show();
  cout << birth.getYear() << ", " << birth.getMonth() << ", " << birth.getDay() << endl;

  return 0;
}




------------------------------------------------------
/*
 *  c++ ==> 객체지향 p137 open challange, 지수를 표현하는 클래스를 작성해본 코드
 */
@======== Exp.h ==========
                                                                                   class Exp
                                                                                   {
                                                                                    private:
                                                                                     float base;
                                                                                     float exp;
                                                                                     float result;

                                                                                    public:
                                                                                     Exp(float a, float b) : base(a), exp(b)
                                                                                     {}

                                                                                     Exp(float a) : base(a)
                                                                                     {
                                                                                       exp = 1;
                                                                                     }

                                                                                     Exp()
                                                                                     {
                                                                                       base = 1; exp = 1;
                                                                                     }

                                                                                     float getValue();
                                                                                     float getBase();
                                                                                     float getExp();
                                                                                     bool equals(Exp b);
                                                                                   };

@======== main.cpp ==========
#include "Exp.h"
#include <iostream>
#include <string>
#include <cmath>

                                                                                   using namespace std;

float Exp::getBase()
{
  return this->base;
}

float Exp::getExp()
{
  return this->exp;
}

float Exp::getValue()
{
  result = pow(base,exp);
  return this->result;
}

bool Exp::equals(Exp b)
{
  if (this->getValue() == b.getValue())
    return true;

  return false;
}

int main()
{
  Exp a(3, 2);
  Exp b(9);
  Exp c;

  cout << a.getValue() << endl;
  cout << b.getValue() << endl;
  cout << c.getValue() << endl;

  cout << "a의 베이스 " << a.getBase() << ',' << "지수 " << a.getExp() << endl;
	
  if (a.equals(b))
    cout << "Same" << endl;
  else
    cout << "Diff" << endl;

  return 0;
}





------------------------------------------------------
/*
 * c++ ==> 객체지향 p91 14, 영문텍스트를 ;가 입력될때까지 입력받아 글자의 수와 알파벳의 수를 모두 집계해서 히스토그램을 그려주는 코드
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, const char *argv[])
{
  string sentence;
  int numAlpha = 0;
  int len = 0;
  int spaceLen = 0;
  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
  char star = '*';

  cout << "영문 텍스트를 입력하세요. 히스토그램을 그립니다" << endl;
  cout << "텍스트의 끝은 ; 입니다. 10000개까지 가능합니다" << endl;
  getline(cin, sentence, ';');
	
  // 대문자를 소문자로 바꿔주는 구문!
  transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);

  // 총 글자의 수 = 총 문장 단어수 - 스페이스의 갯수로 구한다
  len = sentence.length();
  spaceLen = count(sentence.begin(), sentence.end(), ' ');
  numAlpha = len - spaceLen;

  cout << "총 알파벳 개수 : " << numAlpha << endl;

  // count 함수를 사용해 알파벳의 갯수를 리턴한다
  a = count(sentence.begin(), sentence.end(), 'a');
  b = count(sentence.begin(), sentence.end(), 'b');
  c = count(sentence.begin(), sentence.end(), 'c');
  d = count(sentence.begin(), sentence.end(), 'd');
  e = count(sentence.begin(), sentence.end(), 'e');
  f = count(sentence.begin(), sentence.end(), 'f');
  g = count(sentence.begin(), sentence.end(), 'g');
  h = count(sentence.begin(), sentence.end(), 'h');
  i = count(sentence.begin(), sentence.end(), 'i');
  j = count(sentence.begin(), sentence.end(), 'j');
  k = count(sentence.begin(), sentence.end(), 'k');
  l = count(sentence.begin(), sentence.end(), 'l');
  m = count(sentence.begin(), sentence.end(), 'm');
  n = count(sentence.begin(), sentence.end(), 'n');
  o = count(sentence.begin(), sentence.end(), 'o');
  p = count(sentence.begin(), sentence.end(), 'p');
  q = count(sentence.begin(), sentence.end(), 'q');
  r = count(sentence.begin(), sentence.end(), 'r');
  s = count(sentence.begin(), sentence.end(), 's');
  t = count(sentence.begin(), sentence.end(), 't');
  u = count(sentence.begin(), sentence.end(), 'u');
  v = count(sentence.begin(), sentence.end(), 'v');
  w = count(sentence.begin(), sentence.end(), 'w');
  x = count(sentence.begin(), sentence.end(), 'x');
  y = count(sentence.begin(), sentence.end(), 'y');
  z = count(sentence.begin(), sentence.end(), 'z');
	
  cout << "a(" << a <<") " << string(a,star) << endl;
  cout << "b(" << b <<") " << string(b,star) << endl;
  cout << "c(" << c <<") " << string(c,star) << endl;
  cout << "d(" << d <<") " << string(d,star) << endl;
  cout << "e(" << e <<") " << string(e,star) << endl;
  cout << "f(" << f <<") " << string(f,star) << endl;
  cout << "g(" << g <<") " << string(g,star) << endl;
  cout << "h(" << h <<") " << string(h,star) << endl;
  cout << "i(" << i <<") " << string(i,star) << endl;
  cout << "j(" << j <<") " << string(j,star) << endl;
  cout << "k(" << k <<") " << string(k,star) << endl;
  cout << "l(" << l <<") " << string(l,star) << endl;
  cout << "m(" << m <<") " << string(m,star) << endl;
  cout << "n(" << n <<") " << string(n,star) << endl;
  cout << "o(" << o <<") " << string(o,star) << endl;
  cout << "p(" << p <<") " << string(p,star) << endl;
  cout << "q(" << q <<") " << string(q,star) << endl;
  cout << "r(" << r <<") " << string(r,star) << endl;
  cout << "s(" << s <<") " << string(s,star) << endl;
  cout << "t(" << t <<") " << string(t,star) << endl;
  cout << "u(" << u <<") " << string(u,star) << endl;
  cout << "v(" << v <<") " << string(v,star) << endl;
  cout << "w(" << w <<") " << string(w,star) << endl;
  cout << "x(" << x <<") " << string(x,star) << endl;
  cout << "y(" << y <<") " << string(y,star) << endl;
  cout << "z(" << z <<") " << string(z,star) << endl;

  return 0;
}







------------------------------------------------------
/*
 * c++ ==> 객체지향 p89 11, 끝수를 입력받아 1부터 끝수까지 합을 출력하는 코드
 */
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
  int k, n = 0;
  int sum =0;

  cout << "끝 수를 입력하세요>> ";
  cin >> n;

  for(k =1 ; k <= n ; k++)
    sum += k;
	
  cout << "1에서 " << n << "까지의 합은 " << sum << " 입니다" << endl;

  return 0;
}






------------------------------------------------------
/*
  c++ ==> 객체지향 p88 8, 한 라인에 이름을 ;로 구분해서 받고
  각각 끊어낸 다음 가장 긴 이름을 출력하는 코드
*/
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
  string name;
  string man[5];
  string finalName;
  int i = 0;
  int count = 0;

  cout << "5명의 이름을 ';'으로 구분하여 입력하세요" << endl;
  cout << ">> ";
  cin >> name;

  int startIndex = 0;
  int fIndex = 0;
  while (1)
  {
    fIndex = name.find(';', startIndex);
	
    if (fIndex == -1)  break;

    count = fIndex - startIndex;
    man[i++] = name.substr(startIndex, count);
    startIndex = fIndex + 1;

    if (i > 4) break;
  }
	
  for (int i = 0; i < 5 - 1; i++)
  {
    if (man[i].length() > man[i + 1].length())
      finalName = man[i];
    else
      finalName = man[i + 1];

  }

  cout << "가장 긴 이름은 " << finalName << endl;
  return 0;
}





------------------------------------------------------
/*
  c++ ==> 객체지향 p88 7, yes가 입력되는 종료되는 프로그램 작성하기
*/
#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
  char str[] = { 0 };

  while (1)
  {
    cout << "종료하고 싶으면 yes를 입력하세요 >> ";
    cin.getline(str, 10);

    if (strcmp(str, "yes") == 0)
    {
      exit(0);
    }
  }
  return 0;
}

------------------------------------------------------
/*
  c++ ==> 객체지향, p206 #6 동적으로 Circle 객체를 할당받아 원의 반지름을 입력하고
  너비가 100 이상인 원의 개수를 출력하는 코드
*/
#include <iostream>

using namespace std;

class Circle
{
  int radius;

 public:
  void setRadius(int radius);
  double getArea();
};

void Circle::setRadius(int radius)
{
  this->radius = radius;
}

double Circle::getArea()
{
  return this->radius * this->radius;
}

int main(int argc, char *argv[])
{
  int num = 0;

  cout << "원의 갯수를 입력해주세요 : " ;
  cin >> num;

  Circle *cp = new Circle[num];
  int *rad = new int[num];

  for (int i = 0; i < num; i++)
  {
    cout << "c" << i << "의 반지름 >> ";
    cin >> rad[i];
  }

  for (int i = 0; i < num; i++)
  {
    cp[i].setRadius(rad[i]);
  }

  int count = 0;

  for (int i = 0; i < num ; i++)
  {
    if (cp[i].getArea() > 100)
    {
      count++;
    }
  }
  cout << "면적이 100보다 큰 원은 " << count << " 개 입니다"<< endl;

  return 0;
}

--------------------------------------------------------------------------
/*
  c++ ==> 객체지향, p206 #5 Circle 객체를 생성해서 setradius, getarea 함수를 구현해보고
  원을 3개 선언해서 100보다 큰 원을 찾는 코드
*/
#include <iostream>

using namespace std;

class Circle
{
  int radius;

 public:
  void setRadius(int radius);
  double getArea();
};

void Circle::setRadius(int radius)
{
  this->radius = radius;
}

double Circle::getArea()
{
  return this->radius * this->radius;
}

int main(int argc, char *argv[])
{
  Circle c1;
  Circle c2;
  Circle c3;

  int rad, rad2, rad3;
  int count = 0;

  cout << "c1의 반지름 >> ";
  cin >> rad;
  cout << "c2의 반지름 >> ";
  cin >> rad2;
  cout << "c3의 반지름 >> ";
  cin >> rad3;

  c1.setRadius(rad);
  c2.setRadius(rad2);
  c3.setRadius(rad3);

  if(c1.getArea() > 100)
    count++;

  if(c2.getArea() > 100)
    count++;

  if(c3.getArea() > 100)
    count++;

  cout << "면적이 100보다 큰 원은 " << count << " 개 입니다"<< endl;

  return 0;
}
