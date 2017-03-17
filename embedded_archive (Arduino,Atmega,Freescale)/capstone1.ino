/*
	arduino ==> 캡스톤, 12번과 7번핀, 스위치와 LED를 사용해 LED를 껏다 켯다 하는 코드
						그 다음 인터럽트를 사용해 스위치를 누를 떄마다 LED 끄고 키는 코드
*/
volatile int STATE = LOW;

void setup()
{
	pinMode(12, OUTPUT);
	//pinMode(7,INPUT);
	attachInterrupt(0, blink, CHANGE);
}

void blink()
{
	STATE = !STATE;
}

void loop()
{
	digitalWrite(12,STATE);
}

