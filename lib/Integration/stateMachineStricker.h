
#ifndef ARDUINO_STATEMACHINESTRICKER_H
#define ARDUINO_STATEMACHINESTRICKER_H
#include <Arduino.h>
#include "BNO.h"
#include "constants.h"
#include "IRRing.h"
#include "motor.h"
#include "motors.h"
#include "PixyCam.h"
#include "SingleEMAFilterLib.h"
#include "ConstantsStricker.h"
#include "PID.h"
#include <Wire.h>
#include "Photo.h"
#include "SingleEMAFilterLib.h"
#include <Pixy2I2C.h>
#include <Pixy2.h>

class stateMachineStricker  
{
	private:
	IRRing robotIrRing;
	PID robotPid;
	//Bno gyro;
	PixyCam Pixy;
	Motors motorsRobot;
	Photo robotPthototransistors;
	Bno bno;
	unsigned long current_time = millis();
	int last=1;
	int lastP=1;
	ConstantsStricker:: stateMachine state;
	ConstantsStricker:: sides atack=ConstantsStricker::sides::yellow;
	int setpoint = 0;
	int translation_angle = 0;
	int adjust_angle = 0;
	float x=0;
	int angle=0;


	public:

	stateMachineStricker() : robotIrRing(), robotPid(1.5, 0.00735, 45, 200), bno(), Pixy(), motorsRobot(9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 11, 10), robotPthototransistors(), last(1), lastP(1), state(), atack(ConstantsStricker::sides::yellow) {}
		// void searchBall(); // Duplicate declaration removed
		/*void gol(int xPosition, int y1);
		int getCorrectionsImu();
		int getCorrectionsImuTarget(int target);
		void goOutOfLine(int angleC);
		bool hasPosesion();
		int detector();
		void attackGoal(int xPosition, int y1);
		void updateGoalData();*/
		void startObjects();
		void searchBall();
		void goToGoAL();
		void avoidLine(int angle);

	
		

};
#endif
