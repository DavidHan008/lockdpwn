/*
 * c++ ==> 객체지향수업, EvenRandom 클래스를 생성해 최소값과 최대값 사이의 짝수인 난수를 10개 발생시키는 코드
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class EvenRandom
{
private:
	int modular;
	int minimum;
	int tmpNum;
	int *EvenNums;

public:
	EvenRandom(int mod, int min);
	~EvenRandom();
	void printEvenNumbers();

};

EvenRandom::EvenRandom(int mod, int min)
	: modular(mod), minimum(min)
{
	EvenNums = new int[10];
}

EvenRandom::~EvenRandom()
{
	delete[] EvenNums;
}

void EvenRandom::printEvenNumbers()
{
	int i = 0;

	srand((unsigned)time(NULL));
	while (true)
	{
		tmpNum = rand() % modular;

		if (tmpNum % 2 == 0 && tmpNum > minimum)
		{
			EvenNums[i++] = tmpNum;
		}

		if (i >= 10)
		{
			break;
		}
	}

	cout << "[*] "<< minimum << " 부터 " << modular << " 까지의 짝수인 난수 10개는 " << endl;
	for (int j = 0; j < 10; j++)
	{
		cout << EvenNums[j] << " ";
	}
	cout << " 입니다" << endl;
}

int main(int argc, const char *argv[])
{
	int max, min;

	while (1)
	{
		cout << "[+] 난수의 최대값과 최소값을 설정해주세요 a,b : ";
		cin >> max >> min;

		if (max > min)
		{
			break;
		}
		else
		{
			cout << "[-] 다시 입력해주세요" << endl;
		}
	}
	EvenRandom er(max,min);
	er.printEvenNumbers();

	return 0;
}

