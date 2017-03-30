/*
  arduino ==> 캡스톤, 모터의 회전을 홀센서로 읽어들인 다음 저역통과필터를 통해 서보모터를 구동하는 코드
 */
#include <MsTimer2.h>
#include <Servo.h>

#define alpha 0.3

Servo myservo;
int n = 0;
int dt = 100;
float rpm = 0;
float LPFvalue = 0;

void getRpm()
{
  // rpm이므로 60을 곱한다.
  // 극이 2개이므로 2로 나눈다 (밀리세컨이므로 1000으로 나눈다)
  rpm = (n * 60) / (dt * 0.002);
  Serial.println(rpm);
  LPFvalue = 0.7*LPFvalue + 0.3*rpm/30.0;

  // Serial.print("LPFval is : ");
  // Serial.println(LPFvalue);
  n = 0;
}

void Encoder()
{
  n += 1;
}

void setup()
{
  Serial.begin(115200);
  attachInterrupt(0, Encoder, CHANGE);
  MsTimer2::set(dt, getRpm);
  MsTimer2::start();

  myservo.attach(9);
}

void loop()
{
  myservo.write(LPFvalue);
}