/*
	arduino ==> 
 */
#include <PID_v1.h>
#include <LMotorController.h>
#define MIN_ABS_SPEED 30  	// 모터의 최저속도를 설정합니다

//------------------------------------------------------------
// PID 제어용 변수 선언
double kp = 6.;
double ki = 20.;
double kd = 1.5;


double setpoint = 255.0;
// PID 제어용 input, output 변수를 선언합니다
double input_left, output_left;
double input_right, output_right;

// PID값을 설정해준다
PID pid_left(&input_left, &output_left, &setpoint, kp, ki, kd, DIRECT);
PID pid_right(&input_right, &output_right, &setpoint, kp, ki, kd, DIRECT);

// 모터 제어용 변수 선언
// EnA, EnB는 속도제어용(pwm), IN1,2,3,4는 방향제어용 핀입니다
int ENA = 10;
int IN1 = 12;
int IN2 = 6;
int IN3 = 9;
int IN4 = 8;
int ENB = 11;


// motorController 객체 생성, 맨 끝 파라미터 1,1은 각각 좌측, 우측모터의 최대속도(%) 입니다.
LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);


void setup() {
	Serial.begin(115200);

	pid_left.SetMode(AUTOMATIC);
	pid_left.SetSampleTime(10);
	pid_left.SetOutputLimits(0, 255);  
	
	pid_right.SetMode(AUTOMATIC);
	pid_right.SetSampleTime(10);
	pid_right.SetOutputLimits(0, 255);  

	pinMode(2,INPUT);
	pinMode(3,INPUT);
	//pinMode(4,INPUT);
}


void loop() {
	pid_left.Compute();
	pid_right.Compute();

	// move(a,b,minSpeed)  a : 위에서봤을 때 오른쪽
	//                     b : 위에서봤을 때 왼쪽
	motorController.move(-output_right, -output_left, MIN_ABS_SPEED); // pid 연산으로 나온 output 값을 motorController로 전송합니다. (모터제어)

	if(!digitalRead(2)){
		input_left += 5;
		input_right -= 5;
	}
	if(!digitalRead(3)){
		input_left -= 5;
		input_right += 5;
	}
	if(!digitalRead(2) && !digitalRead(3)){
		input_left -= 5;
		input_right -= 5;
	}

	if(input_left >= 255 || input_left <= -255) input_left = 0;
	if(input_right >= 255 || input_right <= -255) input_right = 0;

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

