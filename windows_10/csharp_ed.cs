
<C# LANGUAGE>

	$ 자료형
		$ var 
		$ object

		$ 실수 자료형
			$ float
			$ double
			$ decimal



	$ 반복문
		$ foreach

			int[] arr = new int[]{0,1,2,3,4};  /// 배열 선언은 이렇게 하는군
			foreach (int a in arr)
			{
				Console.WriteLine(a);
			}

	


	$ ref : 참조에 의한 전달 

		static void Swap(ref int a, ref int b) 
		{
			int temp = b;
			b = a;
			a = temp;
		}
		Swap(ref x,ref y);
		




	$ out : 출력 전용 매개변수

		void Divide(int a, int b, out int quotient, out int remainder)
		{
			quotient = a/b;
			remainder = a%b;
		}





	$ params : 가변길이 매개변수

			int Sum(params int[] args)
			{
				int sum = 0;

				for(int i=0; i<args.Length; i++)
				{
					sum += args[i]
				}
				return sum;
			}







	$ 명명된 매개변수 ==> 가독성을 좋게 해준다

			static void PrintProfile(string name, string phone)
			{}

			PrintProfile(name:"edward", phone:"010-1234-5678");





	
	$ CLR의 가비지 컬렉터가 객체를 제거하므로 C#은 왠만하면 소멸자를 쓰지 않는다고 한다






	$ class 클래스
		$ sealed : 상속을 받지 못하게 할 때 사용한다
	
			sealed class Base
			{
				...
			}

		$ is 와 as 

			Mammal mammal = new Dog();
			Dog dog;

			if (mammal is Dog)   // is 연산자 활용
			{...}
			
			Dog dog = mammal as Dog; // as 연산자 활용
			




		$ 오버라이딩과 다형성 overriding and polymorphism

			$ virtual, override
			




			$ new : 메소드 숨기기를 사용한다 (new 할당연산자하고 다르다)

				class Derived : Base
				{
					public new void MyMethod()
					{...}
				}






			$ sealed : 오버라이딩을 봉인한다 
					
				class Derived : Base
				{
					public sealed void SealMe()
					{...}
				}





		
			$ partial class : 분할 클래스 (한 클래스가 길 경우 여러번에 나눠서 작성한다)

				partial class Myclass
				{...}
				partial class Myclass
				{...}
		





	
	$ 인터페이스 interface 와 추상클래스 abstract

		$ 인터페이스
			$ Ilogger 인터페이스를 상속받는 클래스는 반드시 WriteLog를 구현해야 한다
		
			interface Ilogger 
			{
				void WriteLog(string log);
			}

			class Derived : Ilogger
			{
				void WriteLog(string log)
				{...}
			}
	


		$ 추상클래스
			$ 인터페이스와 달리 구현할 수 있지만 인스턴스를 만들진 못한다
			
			abstract class AbstractBase
			{
				public abstract void SomeMethod()
				{
					Console.WriteLine("hey");
				}
			}
			
			class Derived : AbstractBase
			{
				public override void SomeMethod()
				{...}
			}


	



	$ 프로퍼티 property
		$ get, set 을 이용해 은닉성과 편의성을 둘 다 만족시킬 수 있다고 한다

		class Myclass
		{
			private int a;
			public int a;
			{
				get
				{
					return a;
				}
				set
				{
					a = value;
				}
			}
		}

	
		$ 자동 프로퍼티는 그냥 get; set; 









	$ 배열 Array

		int[] arr = new int[5];
		string[] arr2 = new string[5]{"hi","yo","man"};
		
		$ Array 메소드와 프로퍼티
			$ Array.Sort()
			$ Array.BinarySearch()
			$ Array.IndexOf()
			$ Array.TrueForAll()
			$ Array.Resize<T>
			$ Array.Clear()
			$ Array.GetLength()
			$ Array.Length
			$ Array.Rank


	


	
	$ 컬렉션 == c++ 자료구조 STL 

		$ ICollection 인터페이스를 상속한다


		$ ArrayList
					.Add()
					.RemoveAt()
					.Insert()
		
		$ Queue
				.Enqueue()
				.Dequeue()

		$ Stack
				.Push()
				.Pop()

		$ Hashtable
				


	




	$ 인덱서 Indexer
		$ 인덱스를 이용해 객체 내부에 접근할 수 있다

		static int this[int index]
		{
			get
			{
				return array[index];
			}
			set
			{
				if(index >= array.Length)
				{
					Array.Resize<int>(ref array, index + 1);
				}
				array[index] = value;
			}
		}






	


	$ 일반화 프로그래밍 generic Programming
		
		$ 일반화 메소드
			
			void CopyArray<T> (T[] source, T[] target)
			{...}




		$ 일반화 클래스
				
			class Array_generic<T>
			{
				private T[] array;
				public T GetElement(int index) 
				{
					return array[index];
				}
			}
			Array_generic<int> intArr = new Array_generic<int>();
			Array_generic<string> intArr = new Array_generic<string>();



			$ 형식 매개변수 제약하기 where
				$ 특정 조건만 만족하는 T를 사용하고 싶을 때
					$ where T : struct
					$ where T :	class
					$ where T : new()
					$ where T : U

				class BaseArray<T> where T: struct
				{...}


		





	$ delegate, event, lambda
		
		$ delegate
			$ c++의 함수인자 Functor와 비슷하다
			
			delegate int Compare(int a, int b)
			
			static int AscendComparer(int a,int b)
			{...}
			static int DescendComparer(int a,int b)
			{...}
			static void BubbleSort(int[] data, Compare Comparer)
			{...}
			BubbleSort(data, new Compare(AscendComparer));


			$ 익명 메소드
				
				Calculate Cacl = delegate (int a, int b)
								{
									return a + b;
								}

	
		$ event
			$ delegate 와 사실상 기능이 똑같지만 선언된 클래스 내에서만 호출이 가능하다

				delegate void Eventhandler(string msg);
				
				class mine
				{
					public event Eventhandler SomethingHappend;
					public void DoSomething(int number)
					{
						...	
					}
				}

				




		$ lambda
			$ C#3.0 부터 생긴 기능으로 delegate 와 기능이 똑같고 더 간편하다
			$ delegate 가 먼저 C#2.0에 나왔기 때문에 delegate 를 안버리고 계속 사용하고 있다고 한다 
			
			delegate int Calculate(int a,int b);
			Calculate calc = (int a, int b) => a + b;


			
			delegate void DoSomething();
			DoSomething doit = () => {
										Console.WriteLine("hello");
										Console.WriteLine("hello2");
										Console.WriteLine("hello3");
				      				 };


			$ Func 과 Action 
				$ Func은 값을 반환하고 Action은 람다식만 실행한다
				
				Func<int> func1 = () => 10;
	
				Action<int,int> act1 = (x,y) => {
													int z = x ** y;  
													Console.WriteLine(z);
				                                }				






	$ LINQ Language INtegrated Query
		$ SQL 구문과 상당히 비슷하다 
			
			System.LINQ;
			class profile
			{
				public string Name
				{
					get;
					set;
				}
				public int Height
				{
					get;
					set;
				}
			}
		
			profile[] arrProfile =
			{
				new profile() {Name = "one" , Height = 170 },
				new profile() {Name = "two" , Height = 180 },
				new profile() {Name = "three" , Height = 160 },
				new profile() {Name = "four" , Height = 175 },
				new profile() {Name = "five" , Height = 185 },
			};

			var profiles = from profile in arrProfile
						  where profile.Height < 175
						  orderby profile.Height
						  select profile;

			foreach (var profile in profiles)
			{
				Console.WriteLine("{0}, {1}", profile.Name, profile.Height);
			}



		$ from
		$ where
		$ orderby
		$ select
		$ group by
		$ join





	

	$ 리플렉션 Reflection





	$ 애트리뷰트 Attribute






	$ dynamic 키워드 
		
		$ C# <==> COM 의 관계는 서먹했었는데 dynamic 키워드 이후로 C# 에서 COM을 원활하게 사용할 수 있다.





	$ 파일 다루기
		$ FileStream
			$ BinrayWriter & BinaryReader
			$ StreamWriter & StreamReader






	$ 스레드와 태스크
		$ 스레드 Thread
				$ lock, Monitor 클래스 : 크리티컬 섹션을 만들어 한 번에 한 스레드만 작업할 수 있도록 한다



				


		$ 태스크 Task
				$ Task, Task<TResult>, Pararrel 클래스

				$ 병렬과 비동기의 차이점
					$ 비동기 코딩을 가능하게 해주는 async, await 키워드























