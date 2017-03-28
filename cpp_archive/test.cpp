#include <iostream>
#include <cctype>
#include <cstdio>

using namespace std;

int main(int argc, const char *argv[])
{
	int ch;

	cout << "알파벳 소문자, 대문자, 숫자 0-9 중 하나를 입력하세요 : ";
	cin >> ch;

	switch(ch)
	{
		case isalnum(ch):
			oss << ch;
			break;
		default:
			cout << "잘못 입력했습니다." << endl;
			break;
	}
	return 0;
}

