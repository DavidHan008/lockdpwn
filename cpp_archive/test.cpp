/*
 * c++ ==> 객체지향 p614 3, 영문텍스트 파일을 읽고 대문자로 출력하는 코드
 */
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

int main(int argc, const char *argv[]){
	char* file = "c:\\windows\\system.ini";

	ifstream fin(file);
	if(!fin){
		cout << file << " 열기 오류 " << endl;
		return 0;
	}

	int count = 0;
	char c;

	while((c = fin.get()) != EOF){
		cout << char(toupper(c));
		count++;
	}

	cout << "읽은 바이트 수는 " << count << endl;
	fin.close();

	return 0;
}
