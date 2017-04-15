#include <iostream>
#include <string>
using namespace std;

class Morse{
	string alphabet[26];
	string digit[10];
	string slash, question, comma, period, plus, equal;

public:
	Morse();
	void text2Morse(string text, string& morse);
	void morse2Text(string morse, string& text);
}

Morse::Morse(){
	alphabet[0] = " ";
	alphabet[1] = " ";
	alphabet[2] = " ";
	alphabet[3] = " ";
	alphabet[4] = " ";
	alphabet[5] = " ";
	alphabet[6] = " ";
	alphabet[7] = " ";
	alphabet[8] = " ";
	alphabet[9] = " ";
	alphabet[10] = " ";
	alphabet[11] = " ";
	alphabet[12] = " ";
	alphabet[13] = " ";
	alphabet[14] = " ";
	alphabet[15] = " ";
	alphabet[16] = " ";
	alphabet[17] = " ";
	alphabet[18] = " ";
	alphabet[19] = " ";
	alphabet[20] = " ";
	alphabet[21] = " ";
	alphabet[22] = " ";
	alphabet[23] = " ";
	alphabet[24] = " ";
	alphabet[25] = " ";
	
	digit[0] = " ";
	digit[1] = " ";
	digit[2] = " ";
	digit[3] = " ";
	digit[4] = " ";
	digit[5] = " ";
	digit[6] = " ";
	digit[7] = " ";
	digit[8] = " ";
	digit[9] = " ";

	slash = " ";
	question = " ";
	comma = " ";
	period = " ";
	plus = " ";
	equal = " ";
}


int main(int argc, const char *argv[]){
	Morse m;
	string sentence;
	string Mor;
	string Sen;

	cout << "아래에 영문 텍스트를 입력하세요. 모스 부호로 바꿉니다" << endl;
	cin >> sentence;
	m.text2Morse(sentence, Mor);

	cout << "모스 부호를 다시 영문 텍스트로 바꿉니다" << endl;
	m.morse2Text(Mor, Sen);
	return 0;
}
