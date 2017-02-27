#include "stdafx.h"


int Fibo(int n)
{
	printf("func call param %d\n", n);
	if (n == 1)
		return 0;
	else if(n == 2)
		return 1;
	else
		return Fibo(n - 1) + Fibo(n - 2);

}


void main()
{

	printf("피보나치 수열: \n");
	for (int i = 1; i < 20; i++)
	{
		printf("%d ", Fibo(i));
	}
	
	puts("");
}