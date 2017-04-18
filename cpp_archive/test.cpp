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

Book::Book(char* title, int price){
	this->title = title;
	this->price = price;
}

Book::Book(Book& b){
	int len = strlen(b.title);

	this->title = new char[len + 1];
	this->title = "명품자바";
	this->price = b.price;
}

Book::~Book(){
	delete[] title;
}

void Book::set(char* title, int price){
	this->title = title;
	this->price = price;
}


int main(int argc, const char *argv[]){
	Book cpp("명품C++", 10000);
	Book java = cpp;

	cpp.show();
	java.show();
	
	return 0;
}

















