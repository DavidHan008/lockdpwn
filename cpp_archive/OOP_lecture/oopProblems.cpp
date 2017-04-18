
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
 * c++ ==> 객체지향 p   , Book 클래스에서 깊은 복사를 사용해 복사를 해본 코드
 */
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Book{
	char *title;
	int price;

public:
	Book(char* title, int price);
	Book(Book& b);
	~Book();
	void set(char* title, int price);
	void show() { cout << title << ' ' << price << "원" << endl; }
};

Book::Book(char* title, int price) : price(price){
	this->title = new char[strlen(title) +1];
	strcpy(this->title, title);
}

Book::Book(Book& b) : price(b.price){ 
	this->title = new char[strlen(b.title) + 1];
	strcpy(this->title, b.title);
	this->title = "명품자바";
}

Book::~Book(){
	cout << this->title << " deleted!" << endl;
	delete[] title;
}

void Book::set(char* title, int price){
	this->title = new char[strlen(title) +1];
	strcpy(this->title, title);
	this->price = price;
}


int main(int argc, const char *argv[]){
	Book cpp("명품C++", 10000);
	Book java = cpp;

	cpp.show();
	java.show();
	
	return 0;
}




------------------------------------------------------
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
	Accumulator& add(int n);  // 값을 계속 누적하기 위해 참조리턴을 하는 함수
	int get();
};

Accumulator::Accumulator(int value) : value(value)
{}

Accumulator::Accumulator(Accumulator& a) {
	this->value = a.value;
}

// add 함수를 통해 value 값을 계속해서 누적하기 위해 *this를 반환하는 함수
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




------------------------------------------------------
/*
 * c++ ==> 객체지향 p265 6, p265 5번문제에 스택에 저장할 수 있는 크기를 동적할당하게 작성하고 복사생성자 또한 구현해본 코드
*/
#include <iostream>
#include <string>
using namespace std;

class MyIntStack {
	int *p;
	int size;
	int tos; // stack의 꼭대기를 가르키는 인덱스

public:
	MyIntStack();
	MyIntStack(int size);
	MyIntStack(MyIntStack& s); // 복사생성자 구현
	~MyIntStack();

	bool push(int n);
	bool pop(int &n);
};

MyIntStack::MyIntStack() :tos(0) {
	p = new int[10];
}

MyIntStack::MyIntStack(int size) : size(size), tos(0) {
	p = new int[size];
}

// 복사생성자를 사용해본 코드 
MyIntStack::MyIntStack(MyIntStack& s) {
	this->size = s.size;
	this->tos = s.tos;

	// 배열에 대한 복사가 이뤄져야하므로 아래와 같이 복사한다
	this->p = new int[size];
	for(int i = 0 ; i < s.size ; i++)
		this->p[i] = s.p[i];
}

MyIntStack::~MyIntStack() {
	delete[] this->p;
}

bool MyIntStack::push(int n) {
	if (tos < size) {
		p[tos] = n;
		tos++;
		return true;
	}
	return false;
}

bool MyIntStack::pop(int &n) {
	if (tos >= 0) {
		n = p[tos - 1];
		tos--;
		return true;
	}
	return false;
}

int main(int argc, const char *argv[]) {
	MyIntStack a(10);
	a.push(10);
	a.push(20);

	MyIntStack b = a;
	b.push(30);

	int n;
	a.pop(n);
	cout << "스택 a에서 팝한 값 " << n << endl;
	b.pop(n);
	cout << "스택 b에서 팝한 값 " << n << endl;

	return 0;
}




------------------------------------------------------
/*
 * c++ ==> 객체지향 p265 5, 정수를 저장하는 MyIntStack 클래스를 작성하고 10개의 배열만 push, pop을 통해 입력출하는 코드
 */
#include <iostream>
#include <string>

class MyIntStack{
	int p[10]; // 최대 10개의 정수 저장
	int tos; // stack의 꼭대기를 가르키는 인덱스

public:
	MyIntStack();
	bool push(int n);
	bool pop(int &n);
};

MyIntStack::MyIntStack() : tos(0) {
	p[10] = {0,};
}

bool MyIntStack::push(int n){
	if(tos < 10){
		p[tos] = n;
		tos++;
		return true;
	}
	return false;
}

bool MyIntStack::pop(int &n){
	if(tos >= 0){
		n = p[tos];
		tos--;
		return true;
	}
	return false;
}

int main(int argc, const char *argv[]){
	MyIntStack a;

	for (int i = 0; i < 11; i++) {
		if(a.push(i))  cout << i << ' ';
		else cout<< endl << i + 1 << " 번째 stack full" << endl;
	}
	int n;

	for (int i = 0; i < 11 ; i++) {
		if(a.pop(n)) cout << n << ' ';
		else cout << endl << i + 1 << " 번째 stack empty";
	}
	cout << endl;
	
	return 0;
}



------------------------------------------------------
/*
 * c++ ==> 객체지향 p265 4, 참조자를 리턴하는 find() 함수를 작성하고 Mike에서 M 문자를 찾은 다음 m으로 수정하는 코드
 */
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// a 문자열에서 c를 찾아 참조자를 리턴하는 함수
char& find(char a[], char c, bool& success) {
	int len = strlen(a);
	
	for (int i = 0; i < len; i++) {
		if (a[i] == c) {
			success = true;
			return a[i];
		}
	}
	success = false;
}

int main(int argc, const char *argv[]) {
	char s[] = "Mike";
	bool b = false;
	char& loc = find(s, 'M', b);

	if (b == false) {
		cout << "M을 발견할 수 없다" << endl;
		return 0;
	}

	loc = 'm';
	cout << s << endl;
	return 0;
}




------------------------------------------------------
/*
 *	c++ ==> 객체지향 p259 open challange, 영문텍스트와 모스부호 변환기를 만들어본 코드. 영문자 + 특수문자 <==> 모스부호가 상호변환 가능하다
 */
#include <iostream>
#include <string>
using namespace std;

// 알파벳과 숫자를 상수로 선언한다
const string ALPHA = "abcdefghijklmnopqrstuvwxyz";
const char DIGIT[10] = {'0','1','2','3','4','5','6','7','8','9'};

// 문자 하나를 입력받아 그 문자가 어느 위치에 있는지 알려주는 함수 
int getpos(char c) {
	int pos;
	const char * alphabet = "abcdefghijklmnopqrstuvwxyz0123456789/?,.+=";
	const char * found;

	c = tolower((unsigned char)c);
	found = strchr(alphabet, c);
	pos = found - alphabet;
	if (!found)
		pos = 0;
	else if (pos == 42)
		pos = 0;
	else
		pos++;
	return pos - 1;
}

// 모스부호 <==> 영문자특수문자 변환을 해주는 클래스
class Morse {
	string alphabet[26];
	string digit[10];
	string slash, question, comma, period, plus, equal;

public:
	Morse();
	void text2Morse(string text, string& morse);
	void morse2Text(string morse, string& text);
};

// 각각의 모스부호를 입력한다
Morse::Morse() {
	alphabet[0] = ".-";   //a
	alphabet[1] = "-..."; //b
	alphabet[2] = "-.-."; //c
	alphabet[3] = "-..";  //d
	alphabet[4] = ".";    //e
	alphabet[5] = "..-."; //f
	alphabet[6] = "--."; //g
	alphabet[7] = "....";//h
	alphabet[8] = "..";//i
	alphabet[9] = ".---";//j
	alphabet[10] = "-.-";//k
	alphabet[11] = ".-..";//l
	alphabet[12] = "--";//m
	alphabet[13] = "-.";//n
	alphabet[14] = "---";//o
	alphabet[15] = ".--.";//p
	alphabet[16] = "--.-";//q
	alphabet[17] = ".-.";//r
	alphabet[18] = "...";//s
	alphabet[19] = "-";//t
	alphabet[20] = "..-";//u
	alphabet[21] = "...-";//v
	alphabet[22] = ".--";//w
	alphabet[23] = "-..-";//x
	alphabet[24] = "-.--";//y
	alphabet[25] = "--..";//z

	digit[0] = "-----";
	digit[1] = ".----";
	digit[2] = "..---";
	digit[3] = "...--";
	digit[4] = "....-";
	digit[5] = ".....";
	digit[6] = "-....";
	digit[7] = "--...";
	digit[8] = "----..";
	digit[9] = "----.";

	slash = "-..-.";
	question = "..--..";
	comma = "--..--";
	period = ".-.-.-";
	plus = ".-.-.";
	equal = "-...-";
}

// 텍스트를 입력받으면 모스부호를 반환하는 멤버함수
void Morse::text2Morse(string text, string& morse) {
	int i = 0;
	int j = 0;
	int len = text.length();

	while (1) {
		j = getpos(text[i]);

		if (text[i] == ' ')
			morse += "  ";

		if (j >= 0 && j < 26)
			morse += this->alphabet[j] + ' ';
		else if (j >= 26 && j < 36)
			morse += this->digit[j - 26] + ' ';
		else if (j == 36)
			morse += this->slash + ' ';
		else if (j == 37)
			morse += this->question + ' ';
		else if (j == 38)
			morse += this->comma + ' ';
		else if (j == 39)
			morse += this->period + ' ';
		else if (j == 40)
			morse += this->plus + ' ';
		else if (j == 41)
			morse += this->equal + ' ';

		i++;
		if (i == len) break;
	}
}

// 모스부호를 입력받으면 텍스트를 반환하는 멤버함수
void Morse::morse2Text(string morse, string& text) {
	int first = 0;
	int last = 0;
	int i = 0;
	int space = 0;
	int lenMorse = morse.length();
	string tmp;

	while (1) {
		// ' ' 스페이스가 모스부호 한 단어를 구분하므로 find로 인덱스값을 찾는다
		last = morse.find(' ', first);
		
		// 문장의 끝에 도달하면 루프탈출
		if (last == -1)
			break;

		// 한 단어를 tmp에만 뽑아서 저장한다
		tmp = morse.substr(first, last - first);
		
		// 무한루프 2개를 돌면서 알파벳과 숫자를 발견하면 text에 더해준다 
		while (1) {
			if (tmp == this->alphabet[i])
				text += ALPHA[i];
			i++;
			if (i == 26) {
				i = 0;
				break;
			}
		}

		while (1) {
			if (tmp == this->digit[i])
				text += DIGIT[i];
			i++;
			if (i == 10) {
				i = 0;
				break;
			}
		}

		// 특수문자를 발견하면 text에 더해준다
		if (tmp == this->slash)
			text += '/';
		else if (tmp == this->question)
			text += '?';
		else if (tmp == this->comma)
			text += ',';
		else if (tmp == this->period)
			text += '.';
		else if (tmp == this->plus)
			text += '+';
		else if (tmp == this->equal)
			text += '=';

		// "   " 3칸의 빈칸이 띄어쓰기를 의미하므로 이를 발견하면 현재 위치(last)와 비교해서 문장을 띄울 타이밍에 한 칸 띄어쓴다
		space = morse.find("   ", last);
		if(space == last)
			text += " ";

		// 다음 루프를 위해 first에 last를 넣는다
		first = last + 1;
	}
}


int main(int argc, const char *argv[]) {
	Morse m;
	string sentence;
	string Mor;
	string Sen;

	cout << "아래에 영문 텍스트를 입력하세요. 모스 부호로 바꿉니다" << endl;
	getline(cin, sentence, '\n');
	m.text2Morse(sentence, Mor);
	cout << Mor << endl;

	cout << "모스 부호를 다시 영문 텍스트로 바꿉니다" << endl;
	m.morse2Text(Mor, Sen);
	cout << Sen << endl;
	return 0;
}



------------------------------------------------------
/*
 *	c++ ==> 객체지향 p211 11, 겜블링 게임을 만들어서 두 플레이어가 엔터를 칠 때마다 0~2의 숫자가 나와서 일치하면 이기는 게임을 만들어본 코드
 */	
#include <iostream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

// 플레이어 클래스
class Player{
	string name;

public:
	void setName(string name);
	string getName();
};

// 게임 전체를 담당하는 클래스
class GamblingGame{
	Player *p;

public:
	GamblingGame();
	void setPlayer(Player p1, Player p2);
	void run();
	bool isWin(int arr[]);
	int randomGenerate();
};

// 2명의 플레이어 객체를 초기화하는 함수
GamblingGame::GamblingGame(){
	p = new Player[2];
}

// 3개의 숫자가 모두 일치하면 true를 반환하는 함수
bool GamblingGame::isWin(int arr[]){
	if(arr[0] == arr[1])
		if(arr[1] == arr[2])
			return true;
	return false;
}

// 2명의 플레이어를 세팅하는 함수
void GamblingGame::setPlayer(Player p1, Player p2){
	p[0] = p1;
	p[1] = p2;
}

// 게임 시작 함수
void GamblingGame::run(){
	int gameArray[3] = {0};

	// 무한루프를 돌면서 2명의 플레이어가 엔터를 누를때마다 겜블링 숫자를 받는다
	while (1){
		cout << p[0].getName()	<<": <Enter>";
		cin.get();
		gameArray[0] = randomGenerate();
		gameArray[1] = randomGenerate();
		gameArray[2] = randomGenerate();

		if(isWin(gameArray)){
			cout << gameArray[0] << "     " << gameArray[1] << "    " << gameArray[2] << "   " << p[0].getName() << "님 승리!!" << endl;
			exit(0);
		}
		else
			cout << gameArray[0] << "     " << gameArray[1] << "    " << gameArray[2] << "   아쉽군요!" << endl;


		cout << p[1].getName()	<<": <Enter>";
		cin.get();
		gameArray[0] = randomGenerate();
		gameArray[1] = randomGenerate();
		gameArray[2] = randomGenerate();

		if(isWin(gameArray)){
			cout << gameArray[0] << "     " << gameArray[1] << "    " << gameArray[2] << "   " << p[1].getName() << "님 승리!!" << endl;
			exit(0);
		}
		else
			cout << gameArray[0] << "     " << gameArray[1] << "    " << gameArray[2] << "   아쉽군요!" << endl;
	}
}

// 난수를 리턴하는 함수
int GamblingGame::randomGenerate(){
	int tmp;
	tmp = rand() % 3;
	return tmp;
}

string Player::getName(){
	return this->name;
}

void Player::setName(string name){
	this->name = name;
}

int main(int argc, const char *argv[]){
	// 난수 생성용 코드
	srand((unsigned)time(0));
	GamblingGame gg;
	Player p1;
	Player p2;
	string tmp;

	cout << "***** 갬블링 게임을 시작합니다. *****" << endl;
	cout << "첫번째 선수 이름>> ";
	cin >> tmp;
	p1.setName(tmp);

	cout << "두번째 선수 이름>> ";
	cin >> tmp;
	cin.ignore();
	p2.setName(tmp);

	gg.setPlayer(p1,p2);
	gg.run();
	return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p305 2, 디폴트 매개변수와 생성자를 활용해 id와 이름, 몸무게를 받는 코드
 * 							디폴트매개변수 선언은 클래스 안에서만 해줘야한다!
 */
#include <iostream>
#include <string>
using namespace std;

class Person{
	int id;
	string name;
	double weight;

public:
	Person(int id = 1, string name = "Grace", double weight= 20.5);
	void show() { cout << id << ' ' << weight << ' ' << name << endl; }
}; 

Person::Person(int id, string name, double weight){
	this->id = id;
	this->name = name;
	this->weight = weight;
}

int main(int argc, const char *argv[]){
	Person grace, ashley(2, "Ashley"), helen(3, "Helen", 32.5);
	grace.show();
	ashley.show();
	helen.show();

	return 0;
}


------------------------------------------------------
/*
 * c++ ==> 객체지향 p210 10, 영어 문장의 글자 수를 입력받아서 문장에 포함된 알파벳의 개수만큼 histogram 히스토그램을 생성하는 Histogram 클래스를 생성하고 이를 사용한 코드
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/regex.hpp>

// regex를 사용하기 위해 boost를 추가해준다
using namespace std;
using namespace boost;

class Histogram{
  string sentence;

 public:
  Histogram(string str) : sentence(str) {
    sentence += '\n';
  }

  void put(string str);
  void putc(char ch);
  void print();
};

void Histogram::put(string str){
  this->sentence += str;
}

void Histogram::putc(char ch){
  string oneWord(1, ch);
  this->sentence += oneWord;
}

void Histogram::print(){
  int numAlpha = 0;
  int len = 0;
  int spaceLen = 0;
  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
  char star = '*';

  cout << this->sentence << endl;

  // 대문자를 소문자로 바꿔주는 구문!
  transform(this->sentence.begin(), this->sentence.end(), this->sentence.begin(), ::tolower);

  len = this->sentence.length();

  // regex 정규표현식을 사용해서 특수문자의 갯수만큼 빼준다
  regex rx("[^a-zA-z]");

  // 알파벳을 제외한 나머지 특수문자의 개수를 세는 코드!
  int match_count(distance(sregex_iterator(this->sentence.begin(), this->sentence.end(), rx), sregex_iterator()));

  len -= match_count;

  cout << "총 알파벳 개수 : " << len << endl;

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
}

int main(int argc, const char *argv[])
{
  Histogram elvisHisto("Wise men say, only fools rush in But I can't help. ");
  elvisHisto.put("falling in love with you");
  elvisHisto.putc('-');
  elvisHisto.put("Elvis Presley");
  elvisHisto.print();

  return 0;
}




------------------------------------------------------
/*
  c++ ==> 객체지향 p209 9, Circle, CircleManager 클래스를 만들고 원의 이름과 반지름을 입력한 다음 검색을 통해 원하는 결과를 출력하는 코드
*/
#include <iostream>
#include <string>
using namespace std;

static const double PI = 3.14159;
static int index = 0;

class Circle{
  int radius;
  string name;

 public:
  void setCircle(string name, int radius);
  double getArea();
  string getName();
};

// Circle 클래스를 관리하는 CircleManager 객체 선언
class CircleManager{
  Circle *p;
  int size;

 public:
  CircleManager(int size);
  ~CircleManager();
  void setCircle(string name, int radius);
  void searchByName(string name);
  void searchByArea(int area);
};


void Circle::setCircle(string name, int radius){
  this->name = name;
  this->radius = radius;
}

double Circle::getArea(){
  return this->radius * this->radius * PI;
}

string Circle::getName(){
  return this->name;
}

// 원의 개수를 입력받으면 개수만큼의 Circle 객체를 생성한다
CircleManager::CircleManager(int size)
    : size(size){
  p = new Circle[this->size];
}

// 소멸자에서 Circle 객체배열을 제거해준다
CircleManager::~CircleManager(){
  delete[] p;
}

// Circle 객체배열에 값을 입력하는 함수
void CircleManager::setCircle(string name, int radius){
  p[index].setCircle(name, radius);
  index++;
}

// 이름을 검색해서 출력하는 함수
void CircleManager::searchByName(string name){
  int findIndex = 0;

  while (1){
    if (p[findIndex].getName() == name)
      break;

    if(findIndex > 1000){
      break;
    }
    findIndex++;
  }
  cout << p[findIndex].getName() << "의 면적은 " << p[findIndex].getArea() << endl;
}

// 원의 넓이를 검색해서 출력하는 함수
void CircleManager::searchByArea(int area){
  int findIndex = 0;
  int i = 0;
  int findIndexArray[1000] = {0};

  while (1){
    if (p[findIndex].getArea() >= area){
      findIndexArray[i] = findIndex;
      i++;
    }
    if(findIndex > 1000){
      break;
    }
    findIndex++;
  }

  for (int j = 0; j < i - 1 ; j++) {
    cout << p[findIndexArray[j]].getName() << "의 면적은 " << p[findIndexArray[j]].getArea() << endl;
  }
}


int main(int argc, char *argv[]){
  int numOfCircle;
  int fIndex;
  int lastIndex;
  double circleArea;
  string tmp;
  string circleName;


  cout << "원의 개수 >> ";
  cin >> numOfCircle;
  cin.ignore();

  CircleManager cm(numOfCircle);

  for (int i = 0; i < numOfCircle ; i++) {
    cout << "원 " << i+1 << "의 이름과 반지름 >> ";
    getline(cin, tmp, '\n');

    lastIndex = tmp.at(tmp.length() - 1);
    fIndex = tmp.find(' ' , 0);
    cm.setCircle(tmp.substr(0,fIndex), stoi(tmp.substr(fIndex,lastIndex)));
  }

  cout << "검색하고자 하는 원이 이름 >> ";
  cin >> circleName;
  cm.searchByName(circleName);

  cout << "최소 면적을 정수로 입력하세요 >> ";
  cin >> circleArea;
  cout << circleArea << "보다 큰 원을 검색합니다" << endl;
  cm.searchByArea(circleArea);

  return 0;
}




------------------------------------------------------
/*
  c++ ==> 객체지향 p208 8, Person과 Family 클래스를 만들고 각각의 이름을 받아 출력하는 코드
*/
#include <iostream>
#include <string>
using namespace std;

static int numOfFamily = 0;

class Person{
  string name;

 public:
  Person() {}
  Person(string name) : name(name) {}
  void setName(string name);
  string getName() { return name;}
};

class Family{
  Person *p;
  string familyName;
  int size;
  int *index;

 public:
  Family(string name, int size);
  void show();
  void setName(int index, string name);
  ~Family();
};

void Person::setName(string name){
  this->name = name;
}

Family::Family(string name, int size)
    :familyName(name) , size(size) {

  // p와 index 객체를 3개 길이의 배열로 초기화시킨다
  this->p = new Person[3];
  this->index = new int[3];
}

// 소멸자에 배열에 대한 처리를 해줘야한다
Family::~Family() {
  delete[] p;
  delete[] index;
}

void Family::show(){
  cout << p[0].getName() << "   " << p[1].getName() << "   " << p[2].getName() << endl;
}

void Family::setName(int index, string name){
  this->index[numOfFamily] = index;
  this->p[numOfFamily].setName(name);
  numOfFamily++;
}

int main(int argc, char *argv[]) {
  Family *simpson = new Family("Simpson", 3);
  simpson->setName(0, "Mr. Simpson");
  simpson->setName(1, "Mrs. Simpson");
  simpson->setName(2, "Bart Simpson");

  cout << "Simpson 가족은 다음과 같이 3명 입니다" << endl;
  simpson->show();
  delete simpson;

  return 0;
}




------------------------------------------------------
/*
 *	c++ ==> 객체지향 p207 7, Person 클래스에서 이름과 전화번호를 받고 이를 입력받아 출력하는 코드
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

  // 이름과 전화번호의 칸만큼 substr로 구분해서 받아들인다
  // 한글은 한 글자당 3비트씩 먹어서 substr로 0,9까지 자른다
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
 * c++ ==> 객체지향 p91 14, 영문텍스트를 ;가 입력될때까지 입력받아 글자의 수와 알파벳의 수를 모두 집계해서 히스토그램 histogram을 그려주는 코드
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
