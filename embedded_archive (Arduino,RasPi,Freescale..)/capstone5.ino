/*
  arduino ==> 캡스톤,
 */
#include <MsTimer2.h>

int n = 0;
int dt = 100;
float rpm = 0;

void get_rpm()
{
  // rpm이므로 60을 곱한다.
  // 극이 2개이므로 2로 나눈다 (밀리세컨이므로 1000으로 나눈다)
  rpm = (n*60) / (dt * 0.002);
  Serial.println(rpm);
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
  MsTimer2::set(dt, get_rpm);
  MsTimer2::start();
}

void loop()
{

}