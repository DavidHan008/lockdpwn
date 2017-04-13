#include <iostream>
#include <string>

using namespace std;

class Date
{
private:
	int year;
	int month;
	int day;

public:
	Date(int y, int m, int d) : year(y), month(m), day(d)
	{}

	Date(string str)
	{
		year = stoi(str.substr(0, 4));
		month = stoi(str.substr(5, 1));
		day = stoi(str.substr(7, 2));
	}

	void show();
	int getYear();
	int getMonth();
	int getDay();
};

void Date::show()
{
	cout << this->year << "년 " << this->month << "월 " << this->day << "일 " << endl;
}

int Date::getYear()
{
	return this->year;
}

int Date::getMonth()
{
	return this->month;
}

int Date::getDay()
{
	return this->day;
}

int main()
{
	Date birth(2014, 3, 20);
	Date indepen("1945/8/15");
	
	indepen.show();
	cout << birth.getYear() << ", " << birth.getMonth() << ", " << birth.getDay() << endl;

	return 0;
}

