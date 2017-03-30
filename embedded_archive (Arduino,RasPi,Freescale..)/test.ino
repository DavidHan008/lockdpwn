#include <MSTimer2.h>
#include <Servo.h>

volatile int STATE = LOW;

void setup()
{
	pinMode(12, OUTPUT);
	attachInterrupt(0, blink, CHANGE);
	
	MSTimer2::set(1000, IncreaseNumber);
	MSTimer2::start();

	attachInterrupt(0, IncreaseNumber, HIGH);
}

void blink()
{
	state = !state;
}


void loop()
{
	digitalWrite(12, STATE);
}



