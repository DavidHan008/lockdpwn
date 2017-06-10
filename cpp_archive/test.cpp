/*
 * c++ ==> 객체지향 p
 * */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
  int year;
  string title;
	string name;

 public:
  Book(int year, string title, string name)
			: year(year), title(title), name(name)	
	{}
  void show() {
    cout << year << ' ' << title << "원 " << pages << " 페이지" << endl;
  }
  string getTitle() { return this->title; }
};
