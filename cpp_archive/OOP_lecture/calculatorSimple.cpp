/*
 * c++ ==> 객체지향수업, add,sub,mul,div 클래스를 생성해 계산기를 간단하게 구현해본 코드
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstdlib>

using namespace std;

class Add
{
private:
	int a, b;

public:
	void setValue(int x, int y);
	int calculate();
};

class Sub
{
private:
	int a, b;

public:
	void setValue(int x, int y);
	int calculate();
};

class Mul
{
private:
	int a, b;

public:
	void setValue(int x, int y);
	int calculate();
};

class Div
{
private:
	int a, b;

public:
	void setValue(int x, int y);
	int calculate();
};

void Add::setValue(int x, int y)
{
	a = x;
	b = y;
}

int Add::calculate()
{
	return a + b;
}

void Sub::setValue(int x, int y)
{
	a = x;
	b = y;
}

int Sub::calculate()
{
	return a - b;
}

void Mul::setValue(int x, int y)
{
	a = x;
	b = y;
}

int Mul::calculate()
{
	return a * b;
}

void Div::setValue(int x, int y)
{
	a = x;
	b = y;
}

int Div::calculate()
{
	return a / b;
}

int operatorChecker(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/')
	{
		return 1;
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	int first, second;
	char op;

	Add a;
	Sub s;
	Mul m;
	Div d;

	while (1)
	{
		cout << endl;
		cout << "두 정수와 연산자를 입력하세요 >> ";
		cin >> first >> second >> op;

		if (isdigit(first) || isdigit(second))
		{
			cout << "다시 해주세요" << endl;
			continue;
		}
		
		if (!operatorChecker(op))
		{
			cout << "다시 해주세요" << endl;
			continue;
		}

		switch (op)
		{
		case '+':
			a.setValue(first, second);
			cout << a.calculate();
			break;
		case '-':
			s.setValue(first, second);
			cout << s.calculate();
			break;

		case '*':
			m.setValue(first, second);
			cout << m.calculate();
			break;

		case '/':
			d.setValue(first, second);
			cout << d.calculate();
			break;

		}
	}

	return 0;
}


