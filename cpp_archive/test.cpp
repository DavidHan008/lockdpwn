#include <iostream>
#include <string>
using namespace std;

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

	wg.startGame();
	wg.runGame(p, numOfPlayer);

	return 0;
}

