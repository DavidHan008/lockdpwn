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
