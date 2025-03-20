
#ifndef ARDUINO_STATUSMACHINESTRICKER_H
#define ARDUINO_STATUSMACHINESTRICKER_H
#include <Arduino.h>
#include "Adafruit_ADS1X15.h"
#include "ADS.h"
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
#include "Pixy2I2C.h"

class statusMachineStricker  
{
	private:
	IRRing robotIrRing;
	PID robotPid;
	Bno gyro;
	PixyCam Pixy;
	Motors motorsRobot;

	int last=1;
	int lastP=1;
	int atack=1;
	ConstantsStricker:: stateMachine state;
	ConstantsStricker:: sides atack=ConstantsStricker::sides::yellow;


	public:

		statusMachineStricker();
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
		

};
#endif
