/*
 	arduino ==> 초음파센서로 거리읽는 코드
 */
#define TRIG 7
#define ECHO 6

void setup()
{
	Serial.begin(9600);
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);
}

void loop()
{
	digitalWrite(TRIG,LOW);
	delayMicroseconds(2);
	digitalWrite(TRIG,HIGH);
	delayMicroseconds(5);
	digitalWrite(TRIG,LOW);

	long distance = pulseIn(ECHO,HIGH,5800)/58;

	Serial.print("d: ");
	Serial.print(distance);
	Serial.print("cm\n");
	delay(15);
}

