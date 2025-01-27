
#ifndef ARDUINO_MOTOR_H
#define ARDUINO_MOTOR_H

#include "Arduino.h"
#pragma once

class motor  
{
	private:
	int pin1_;
	int pin2_;
	int speed_;


	public:

		motor();
		motor(int pin1, int pin2, int speed);
		//setters
		void setPin1_(int pin1){pin1_ = pin1;};
		void setPin2_(int pin2){pin2_ = pin2;};
		void setSpeed_(int speed){speed_ = speed;};
		//getters
		int getPin1_(){return pin1_;};
		int getPin2_(){return pin2_;};
		int getSpeed_(){return speed_;};
		//methods
		void forward();
		void backward();
		void stop();
		void startMotors();
		void SetSpeed(int pwm, int speed);
		void InitializeDriver();
		void MoveMotor1();
		void MoveMotor2();
		void MoveMotor3();
		void MoveMotor4();
		float GetRPM();
		float GetAngularVelocity();
		float GetDegree(;)

};
#endif
