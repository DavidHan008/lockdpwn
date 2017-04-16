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

