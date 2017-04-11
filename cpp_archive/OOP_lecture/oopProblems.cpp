
------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------



------------------------------------------------------
/*
	c++ ==> 객체지향 p88 7, yes가 입력되는 종료되는 프로그램 작성하기
*/
#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	char str[] = { 0 };

	while (1)
	{
		cout << "종료하고 싶으면 yes를 입력하세요 >> ";
		cin.getline(str, 10);

		if (strcmp(str, "yes") == 0)
		{
			exit(0);
		}
	}
	return 0;
}

------------------------------------------------------
/*
  c++ ==> 객체지향, p206 #6 동적으로 Circle 객체를 할당받아 원의 반지름을 입력하고
                           너비가 100 이상인 원의 개수를 출력하는 코드
*/
#include <iostream>

using namespace std;

class Circle
{
  int radius;

 public:
  void setRadius(int radius);
  double getArea();
};

void Circle::setRadius(int radius)
{
  this->radius = radius;
}

double Circle::getArea()
{
  return this->radius * this->radius;
}

int main(int argc, char *argv[])
{
  int num = 0;

  cout << "원의 갯수를 입력해주세요 : " ;
  cin >> num;

  Circle *cp = new Circle[num];
  int *rad = new int[num];

  for (int i = 0; i < num; i++)
  {
    cout << "c" << i << "의 반지름 >> ";
    cin >> rad[i];
  }

  for (int i = 0; i < num; i++)
  {
    cp[i].setRadius(rad[i]);
  }

  int count = 0;

  for (int i = 0; i < num ; i++)
  {
    if (cp[i].getArea() > 100)
    {
      count++;
    }
  }
  cout << "면적이 100보다 큰 원은 " << count << " 개 입니다"<< endl;

  return 0;
}

--------------------------------------------------------------------------
/*
  c++ ==> 객체지향, p206 #5 Circle 객체를 생성해서 setradius, getarea 함수를 구현해보고
                          원을 3개 선언해서 100보다 큰 원을 찾는 코드
*/
#include <iostream>

using namespace std;

class Circle
{
  int radius;

 public:
  void setRadius(int radius);
  double getArea();
};

void Circle::setRadius(int radius)
{
  this->radius = radius;
}

double Circle::getArea()
{
  return this->radius * this->radius;
}

int main(int argc, char *argv[])
{
  Circle c1;
  Circle c2;
  Circle c3;

  int rad, rad2, rad3;
  int count = 0;

  cout << "c1의 반지름 >> ";
  cin >> rad;
  cout << "c2의 반지름 >> ";
  cin >> rad2;
  cout << "c3의 반지름 >> ";
  cin >> rad3;

  c1.setRadius(rad);
  c2.setRadius(rad2);
  c3.setRadius(rad3);

  if(c1.getArea() > 100)
    count++;

  if(c2.getArea() > 100)
    count++;

  if(c3.getArea() > 100)
    count++;

  cout << "면적이 100보다 큰 원은 " << count << " 개 입니다"<< endl;

  return 0;
}
