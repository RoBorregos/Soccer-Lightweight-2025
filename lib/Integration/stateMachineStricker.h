
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
	Bno gyro;
	PixyCam Pixy;
	Motors motorsRobot;
	Photo robotPthototransistors;

	int last=1;
	int lastP=1;
	ConstantsStricker:: stateMachine state;
	ConstantsStricker:: sides atack=ConstantsStricker::sides::yellow;


	public:

		stateMachineStricker() : robotIrRing(), robotPid(), gyro(), Pixy(), motorsRobot(), robotPthototransistors(), last(1), lastP(1), state(), atack(ConstantsStricker::sides::yellow) {}
		void searchBall();
		void gol(int xPosition, int y1);
		void attackGoal(int xPosition, int y1);
		int getCorrectionsImu();
		int getCorrectionsImuTarget(int target);
		void goOutOfLine(int angleC);
		bool hasPosesion();
		int detector();
		void updateGoalData();
		void startObjects();
		bool detectLeftLine();
		bool detectRightLine();
		bool detectFrontLine();
	
		

};
#endif
