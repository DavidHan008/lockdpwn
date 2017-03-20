/*
	arduino ==> 적외선센서
 */

void setup() 
{
	Serial.begin(9600);
	pinMode(2,INPUT);
}

void loop() 
{
	if(!digitalRead(2))
	{
		Serial.print("ON\n");
	}
	else
	{
		Serial.print("OFF\n");
	}
}

