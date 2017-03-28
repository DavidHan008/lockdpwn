
-----------------------------------------------------------------------------------


-----------------------------------------------------------------------------------


-----------------------------------------------------------------------------------


-----------------------------------------------------------------------------------
170328_화

# 얕은 복사와 깊은 복사
# 복사 생성자

	# 얕은 복사
		Circle::Circle(Circle& c)  // 복사 생성자
		{
			this->radius = c.radius;
			cout << "복사 생성자 실행 radius = " << radius << endl;
		}

	# 깊은 복사
		Person::Person(Person& person)  // 복사 생성자 
		{
			this->id = person.id; 					// id 값 복사
			int len = strlen(person.name);			// name의 문자 개수
			this->name = new char [len+1]; 			// name을 위한 공간 핟당
			strcpy(this->name, person.name); 		// name의 문자열 복사
			cout << "복사 생성자 실행. 원본 객체의 이름 " << this->name << endl;
		}




	$$ 206p 4번 문제 풀어보기
		$ 2주 뒤에 제출하기 4/11(화)까지









-----------------------------------------------------------------------------------
170327_월

# 값에 의한 호출 <==> 주소에 의한 호출
	void swap(int a, int b)
	void swap(int *a, int *b)


# 객체 치환 및 객체 리턴
	Circle getCircle()
	{
		Circle tmp(30);
		return tmp;
	}


# 참조자 &
	# 주로 call by reference를 위해 사용한다
	void increaseCircle(Circle &c)
	{
		int r = c.getRadius();
		c.setRadius(r+1);
	}


	# 참조 리턴
		char& find(char s[], int index)
		{
			return s[index];
		}

		int main()
		{
			char name[] = "Mike";
			cout << name << endl;
			
			find(name,0) = 'S';    // 이런 문법이 가능하다

			char& ref = find(name,2);
			ref = 't';
			cout << name << endl;
		}














-----------------------------------------------------------------------------------
170321_화

# 1024크기 만큼 메모리 누수 발생한다
	char n = 'a';
	char *p = new char[1024];
	p = &n;


# this 포인터
	this->radius = radius;
	또는
	return this;



# string 클래스
		#include <string>
		using namespace std;
		string str = "I love ";
		str.append("C++");
	
	# 문자열 복사
		string address("abcdef");
		string copyAddress(address);
	
		char text[] = {'L','o','v','e',',','C','+','+','\0'};
		string title(text);

	# 문자열 --> 숫자 변환
		string s = "123";
		int n = stoi(s);

		string *p = new string("C++");
		cout << *p;
		p->append(" good man");
		delete p;


	# getline() 함수로 string을 입력받는다

	string names[5]; // 문자열 배열 선언
	for(int i=0; i<5; i++) 
	{
		cout << "이름 >> ";
		getline(cin, names[i], '\n');
	}

	string latter = names[0];

	for(int i=1; i<5; i++) 
	{
		if(latter < names[i]) // 사전 순으로 latter 문자열이 앞에 온다면
		{ 
			latter = names[i]; // latter 문자열 변경
		}
	}
	cout << "사전에서 가장 뒤에 나오는 문자열은 " << latter << endl;















-----------------------------------------------------------------------------------
170320_월

# 포인터는 c와 거의 똑같다

# 객체 배열
	Circle circleArray[3]; 
		# 항상 파라미터가없는 생성자가 호출된다


# 동적메모리 할당
	# malloc, free ==> new, delete
	







-----------------------------------------------------------------------------------
170314_화


# 지역객체와 전역객체 
	# 소멸자의 소멸 순서


# 캡슐화
	# 접근지정자
		# private :
		# public :
		# protected :


# inline  인라인 함수
	# 오버헤드를 막을 수 있다 
	# 컴파일러에 의해 함수의 코드가 main에(주로) 삽입된다

inline int odd(int x)
{ ... }




# struct 구조체
	# c언어와 호환성을 위해 그대로 사용한다
	# 클래스와 똑같이 private, public 작성 가능하다
		# 기본 접근지정자는 public이다 (class는 private)

	
# 아래 구문을 이용해 중복호출을 막는다
	#ifndef CIRCLE_H
	#define CIRCLE_H
	...
	#endif




	$ p145 실습문제 4 
	  p147 실습문제 8
	  결과값이 의미하는 건 뭐다
	
	$ 프린트로 2주 뒤 28일_화 까지 제출













-----------------------------------------------------------------------------------
170313_월

# Object Oriented Programming 객체지향 프로그래밍
	# 캡슐화

	# class 클래스
		# 멤버변수
		# 멤버함수



	







-----------------------------------------------------------------------------------
170307_화

# 임베디드 시스템이란
	# 프로그래밍하는 host와 실제 사용할 target이 다르다


# cin.getline() 을 이용해 문자열을 입력받을 수 있다
	
	int main()
	{
		cout << "주소를 입력하세요" << endl;

		char address[100];
		cin.getline(address, 100, '\n');

		cout << "주소는 " << address << " 입니다\n";

		return 0;
	}



# iostream.h 는 구버전 c++의 헤더파일이다




















