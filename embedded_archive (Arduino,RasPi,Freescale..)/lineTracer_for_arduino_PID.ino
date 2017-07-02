/*
   arduino ==> 
 */
#include <PID_v1.h>
#include <LMotorController.h>
#define MIN_SPEED 30  	// 모터의 최저속도를 설정합니다
#define MAX_SPEED 255   // 최고속도 0~255 범위

//---------------------------------------------------------------
int a,b,c,d,e;

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


//------------------------------------------------------------
// PID 제어용 변수 선언
double kp = 60;
double ki = 10;
double kd = 4;

double setpoint = 0;
// PID 제어용 input, output 변수를 선언합니다
double input_left, output_left;
double input_right, output_right;

// PID 제어를 하기 위한 변수
int rightFlag = 0;
int leftFlag = 0;

// PID값을 설정해준다
PID pid_left(&input_left, &output_left, &setpoint, kp, ki, kd, DIRECT);
PID pid_right(&input_right, &output_right, &setpoint, kp, ki, kd, DIRECT);

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

	pid_left.SetMode(AUTOMATIC);
	pid_left.SetSampleTime(10);
	pid_left.SetOutputLimits(0, MAX_SPEED);  

	pid_right.SetMode(AUTOMATIC);
	pid_right.SetSampleTime(10);
	pid_right.SetOutputLimits(0, MAX_SPEED);  

	pinMode(2,INPUT);
	pinMode(3,INPUT);
	pinMode(4,INPUT);
	pinMode(5,INPUT);
	pinMode(6,INPUT);
}


void loop() {

	Sensing();

	Serial.println(tracesensor.sen.R, BIN);

	switch(tracesensor.sen.R){
		// 전부 흰색인 경우
		case 0b1111100000:
			input_left += 0;
			input_right -= 0;

			Serial.print(leftFlag);
			Serial.println(rightFlag);

			break;
		// 전부 검정색인 경우
		case 0b0000000000:
			input_left += 0;
			input_right -= 0;

			break;
		// 정중앙에 검정선이 있는 경우
		case 0b1101100000:
			input_left -= 5;
			input_right -= 5;

			rightFlag = 0;
			leftFlag = 0;

			break;
		case 0b0111100000:
			input_left -= 5;
			input_right += 5;

			rightFlag = 1;
			leftFlag = 0;

			break;
		case 0b0011100000:
			input_left -= 2.5;
			input_right += 2.5;

			break;
		case 0b0001100000:
			input_left -= 2;
			input_right += 2;

			break;
		case 0b1001100000:
			input_left -= 1;
			input_right += 1;

			break;
		case 0b1100100000:
			input_left += 1;
			input_right -= 1;


			break;
		case 0b1100000000:
			input_left += 2;
			input_right -= 2;

			break;
		case 0b1110000000:
			input_left += 2.5;
			input_right -= 2.5;

			break;
		case 0b1111000000:
			input_left += 5;
			input_right -= 5;

			rightFlag = 0;
			leftFlag = 1;

			break;
		case 0b1110100000:
			input_left += 3;
			input_right -= 3;

			break;
		case 0b1011100000:
			input_left -= 3;
			input_right += 3;

			break;
		default:
			input_left += 0;
			input_right -= 0;

			break;
	}
	
//	delay(1000);

	if(input_left >= 100 || input_left <= -100) input_left = 0;
	if(input_right >= 100 || input_right <= -100) input_right = 0;

	pid_left.Compute();
	pid_right.Compute();


	// move(a,b,minSpeed)  a : 위에서봤을 때 오른쪽
	//                     b : 위에서봤을 때 왼쪽
	if(rightFlag == 1 && leftFlag == 0)
		motorController.move(0, -MAX_SPEED, MIN_SPEED); // pid 연산으로 나온 output 값을 motorController로 전송합니다. (모터제어)
	else if(rightFlag == 0 && leftFlag == 1)
		motorController.move(-MAX_SPEED, 0, MIN_SPEED); // pid 연산으로 나온 output 값을 motorController로 전송합니다. (모터제어)
	else
		motorController.move(-output_right, -output_left, MIN_SPEED); // pid 연산으로 나온 output 값을 motorController로 전송합니다. (모터제어)

	Serial.print("i_left , i_right : "); 
	Serial.print(input_left);
	Serial.print("     ");
	Serial.println(input_right);
	Serial.print("                     o_left , o_right : "); 
	Serial.print("     ");
	Serial.print(output_left);
	Serial.print("     ");
	Serial.println(output_right);
}


