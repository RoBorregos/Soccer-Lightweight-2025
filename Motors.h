
#ifndef ARDUINO_MOTORS_H
#define ARDUINO_MOTORS_H

#include "Arduino.h"
#include "Motor.h"


class Motors  
{

	public:
		motor motor1;
		motor motor2;
		motor motor3;
		motor motor4;
		Motors(int pin1_1, int pin2_2, int speed_1, 
		int pin1_2, int pin2_2, int speed_2,
		int pin1_3, int pin2_3, int speed_3,
		int pin1_4, int pin2_4, int speed_4),;
		void InitializeMotors();
		void InitializeDriver();
		void SetSpeed(int pwm, int speed);
		void SetAllSpeeds(int speed);
		void StopMotors();
		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
		void MoveMotor1();
		void MoveMotor2();
		void MoveMotor3();
		void MoveMotor4();
		void MoveMotors(int degree, int speed);
		void IndividualMotor(int motor, int speed);
		void GetAllSpeeds();
		void MoveOneMotor(int motor, int speed);
		void MoveMotorsImu(double target_angle, double speed_w, int speed);
		void MoveMotorsProportional(double target_angle, int setpoint);
		

};
#endif
