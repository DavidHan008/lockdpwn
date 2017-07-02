/*
   arduino ==> 
 */
#include <PID_v1.h>
#include <LMotorController.h>
#define MIN_SPEED 30  	// 모터의 최저속도를 설정합니다
#define MAX_SPEED 255   // 최고속도 0~255 범위

//---------------------------------------------------------------
int a,b,c,d,e;
int rightFlag = 0;
int leftFlag = 0;

// 적외선 센서를 편리하게 사용하기 위한 구조체 선언
struct SENSOR{
	union{
		int R;
		struct{
			 int :5;
			 int sensor1:1;
			 int sensor2:1;
			 int sensor3:1;
			 int sensor4:1;
			 int sensor5:1;
		}B;
	}sen;
};

// SENSOR의 구조체 이름을 tracesensor로 선언합니다
struct SENSOR tracesensor;

// 모터 제어용 변수 선언
// EnA, EnB는 속도제어용(pwm), IN1,2,3,4는 방향제어용 핀입니다
int ENA = 10;
int IN1 = 12;
int IN2 = 7;
int IN3 = 9;
int IN4 = 8;
int ENB = 11;

// motorController 객체 생성, 맨 끝 파라미터 1,1은 각각 좌측, 우측모터의 최대속도(%) 입니다.
LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);

// 적외선 센서값을 읽어서 tracesensor 구조체 안에 저장하는 함수
// sensorValues[] 배열 안에도 넣어서 Servo Motor의 PID 제어에 활용합니다
void Sensing(){
	a=0;b=0;c=0;d=0;e=0;

	if(!digitalRead(2)){
		Serial.print("2 ");
		a = 1;
	}
	if(!digitalRead(3)){
		Serial.print("3 ");
		b = 1;
	}
	if(!digitalRead(4)){
		Serial.print("4 ");
		c = 1;
	}
	if(!digitalRead(5)){
		Serial.print("5 ");
		d = 1;
	}

	if(!digitalRead(6)){
		Serial.println("6");
		e = 1;
	}

	tracesensor.sen.B.sensor1 = a;
	tracesensor.sen.B.sensor2 = b;
	tracesensor.sen.B.sensor3 = c;
	tracesensor.sen.B.sensor4 = d;
	tracesensor.sen.B.sensor5 = e;
}

void setup() {
	Serial.begin(115200);

	pinMode(2,INPUT);
	pinMode(3,INPUT);
	pinMode(4,INPUT);
	pinMode(5,INPUT);
	pinMode(6,INPUT);
}


void loop() {
	Sensing();

	//Serial.println(tracesensor.sen.R, BIN);

	// move(a,b,minSpeed)  a : 위에서봤을 때 오른쪽
	//                     b : 위에서봤을 때 왼쪽
	switch(tracesensor.sen.R){
		// 전부 흰색인 경우
		case 0b1111100000:
			Serial.print("                           ");
			Serial.print(leftFlag);
			Serial.println(rightFlag);
			if(rightFlag == 0 && leftFlag == 1)
				motorController.move(MAX_SPEED - 90, -MAX_SPEED, MIN_SPEED); 
			else if(rightFlag == 1 && leftFlag == 0)
				motorController.move(-MAX_SPEED, MAX_SPEED - 90, MIN_SPEED); 
			else
	//			motorController.move(0,0, MIN_SPEED); 

			break;
		// 전부 검정색인 경우
		case 0b0000000000:
			break;
		// 정중앙에 검정선이 있는 경우
		case 0b1101100000:
			Serial.println("11011");
			motorController.move(-MAX_SPEED, -MAX_SPEED, MIN_SPEED); 

			rightFlag = 0;
			leftFlag = 0;
			break;

		// 가장자리1
		case 0b0111100000:
			Serial.println("01111");
			motorController.move(0, -MAX_SPEED, MIN_SPEED); 

			rightFlag = 1;
			leftFlag = 0;

			break;
		case 0b0011100000:
			Serial.println("00111");
			motorController.move(0, -MAX_SPEED + 40, MIN_SPEED); 

			break;
		case 0b1001100000:
			Serial.println("10011");
			motorController.move(0, -MAX_SPEED + 50, MIN_SPEED); 

			break;
		case 0b1100100000:
			Serial.println("11001");
			motorController.move(-MAX_SPEED + 50, 0, MIN_SPEED); 

			break;
		case 0b1110000000:
			Serial.println("11100");
			motorController.move(-MAX_SPEED + 40, 0, MIN_SPEED); 

			break;

		// 가장자리2
		case 0b1111000000:
			Serial.println("11110");
			motorController.move(-MAX_SPEED, 0, MIN_SPEED); 

			rightFlag = 0;
			leftFlag = 1;

			break;
		case 0b1110100000:
			Serial.println("11101");
			motorController.move(-MAX_SPEED + 30, 0, MIN_SPEED); 

			break;
		case 0b1011100000:
			Serial.println("10111");
			motorController.move(0, -MAX_SPEED + 30, MIN_SPEED); 

			break;
		default:
			motorController.move(0, 0, MIN_SPEED); 

			break;
	}
	
//	delay(1000);
}


