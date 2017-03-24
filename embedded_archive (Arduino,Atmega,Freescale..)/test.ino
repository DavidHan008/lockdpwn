/*
  arduino ==> 캡스톤, 평균이동필터를 사용해 초음파센서를 안정시키고 거리값을 읽어 서보모터를 구동시키는 예제코드
*/
#include <Servo.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 15
#define TRIG 2
#define ECHO 3

Servo myservo;
int pos;
int i =0 ;
float dist;
float distFiltered[MAXNUM] = {0};
float final = 0;

void setup()
{
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  myservo.attach(9);

  Serial.begin(9600);
}

float getMean(float dist[])
{
  float mean = 0;
  for(int k = 0 ; k < MAXNUM ; k++)
  {
    mean += dist[k];
  }

  return mean / MAXNUM;
}

void loop()
{
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG,LOW);
  dist = pulseIn(ECHO,HIGH)/58.82;

  distFiltered[i++] = dist;

  if (i > MAXNUM)
  {
    i = 0;
  }

  final = getMean(distFiltered);

  myservo.write(final * 3);

  Serial.println(final);
}
