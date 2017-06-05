/*
 * c++ ==> 객체지향 p
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]){
	string src = "C:\\windows\\system.ini";
	string word;
	string tmp;
	vector<string> vs;

	ifstream fin(src);   // 파일 읽기

	if(!fin){
		cout << src << " 열기 오류 " << endl;
		return 0;
	}
	else
		cout << src << "... word.txt 파일 로딩 완료" << endl;
	
	while(!fin.eof()){
		getline(fin, word,' ');
		vs.push_back(word);
	}

	cout << vs.

	cout << "검색을 시작합니다. 단어를 입력해주세요" << endl;

	while(1){
		cout << "단어>> ";
		cin >> tmp;

	}

	fin.close();

	return 0;
}
