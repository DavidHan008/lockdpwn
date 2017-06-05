/*
 * c++ ==> 객체지향 예제 
 */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]){
	char* file = "c:\\test.txt";

	ifstream fin(file);
	if(!fin){
		cout << file << " 열기 오류 " << endl;
		return 0;
	}

	int count = 0;
	int c;
	int lineNum = 1;

	while((c=fin.get()) != EOF){
		cout << lineNum++ << " : " << (char)c;
		if(c == '\n') 
			cout << lineNum++ << " : " << (char)c;

		cout << (char)c;
		count++;
	}

	cout << "읽은 바이트 수는 " << count << endl;
	fin.close();

	return 0;
}
