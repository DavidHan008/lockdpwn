/*
	arduino ==> 속도를 조절하며 dc모터를 돌리는 코드
 */
#define EA 3
#define M_IN1 4
#define M_IN2 5

void setup() 
{
  // put your setup code here, to run once:
  pinMode(EA,OUTPUT);
  pinMode(M_IN1,OUTPUT);
  pinMode(M_IN2,OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(M_IN1,1);
  digitalWrite(M_IN2,0);

  for(int i =10 ; i<=255 ; i += 10)
  {
    analogWrite(EA,i);
    delay(100);
  }
  
}
