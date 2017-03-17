/*
   arduino ==> 캡스톤, 16 세그먼트를 1초에 1씩 증가시키면서 스위치를 누르면 다시 0부터 시작하는 코드
 */
#include <MsTimer2.h>

int i = 0;

void InitializeZero()
{
	i = 0;
}

void reset()
{
	for(int i=3; i<13; i++)
	{
		if (i == 12)
		{
			continue;
		}
		else 
		{
			digitalWrite(i, HIGH);
		}
	}	
}

void LEDControl(int a)
{
	reset();

	if(a == 1)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 4 or i == 5)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 0)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 9 or i == 7 or i == 8 or i == 5 or i == 4)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	
	}
	else if(a == 2)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i== 5 or i ==10 or i == 11 or i == 7 or i==8)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 3)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 5 or i == 10 or i == 11 or i == 4 or i == 8)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 4)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 9 or i == 11 or i == 10 or i == 5 or i == 4)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}	
	}
	else if(a == 5)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i == 4 or i == 8)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 6)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i == 7 or i == 4 or i == 8)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 7)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 9 or i == 6 or i == 5 or i == 4)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
	else if(a == 8)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else 
			{
				digitalWrite(i, LOW);
			}
		}
	}
	else if(a == 9)
	{
		for(int i = 3; i <= 13 ; i++)
		{
			if (i == 12)
			{
				continue;
			}
			else if (i == 3 or i == 6 or i == 9 or i == 11 or i == 10 or i== 5 or i== 4)
			{
				digitalWrite(i, LOW);
			}
			else
			{
				continue;
			}
		}
	}
}

void IncreaseNumber()
{
	LEDControl(i++);

	if (i > 9)
	{
		i = 0;
	}
}

void setup()
{
	for(int i=3; i<13; i++)
	{
		pinMode(i, OUTPUT);
	}	

	MsTimer2::set(1000, IncreaseNumber);
	MsTimer2::start();
	attachInterrupt(0, InitializeZero, HIGH);
}


void loop()
{
}


