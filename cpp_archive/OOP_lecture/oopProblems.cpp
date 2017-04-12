
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
#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char *argv[])
{
	string sentence;
	int numAlpha = 0;

	cout << "영문 텍스트를 입력하세요. 히스토그램을 그립니다" << endl;
	cout << "텍스트의 끝은 ; 입니다. 10000개까지 입력가능합니다";
	cin >> sentence;

	numAlpha = sentence.length();
	

	cout << "총 알파벳 수 : " << numAlpha << endl;



	return 0;
}








------------------------------------------------------
/*
 * c++ ==> 객체지향 p89 11, 끝수를 입력받아 1부터 끝수까지 합을 출력하는 코드
 */
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
	int k, n = 0;
	int sum =0;

	cout << "끝 수를 입력하세요>> ";
	cin >> n;

	for(k =1 ; k <= n ; k++)
		sum += k;
	
	cout << "1에서 " << n << "까지의 합은 " << sum << " 입니다" << endl;

	return 0;
}




------------------------------------------------------
/*
	c++ ==> 객체지향 p88 8, 한 라인에 이름을 ;로 구분해서 받고 
							각각 끊어낸 다음 가장 긴 이름을 출력하는 코드
*/
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name;
	string man[5];
	string finalName;
	int i = 0;
	int count = 0;

	cout << "5명의 이름을 ';'으로 구분하여 입력하세요" << endl;
	cout << ">> ";
	cin >> name;

	int startIndex = 0;
	int fIndex = 0;
	while (1)
	{
		fIndex = name.find(';', startIndex);
	
		if (fIndex == -1)  break;

		count = fIndex - startIndex;
		man[i++] = name.substr(startIndex, count);
		startIndex = fIndex + 1;

		if (i > 4) break;
	}
	
	for (int i = 0; i < 5 - 1; i++)
	{
		if (man[i].length() > man[i + 1].length())
			finalName = man[i];
		else
			finalName = man[i + 1];

	}

	cout << "가장 긴 이름은 " << finalName << endl;
	return 0;
}





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
