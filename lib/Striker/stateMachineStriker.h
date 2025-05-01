
#ifndef ARDUINO_STATEMACHINESTRICKER_H
#define ARDUINO_STATEMACHINESTRICKER_H
#include <Arduino.h>
#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "PixyCam.h" 
#include "Photo.h"
#include "Constants_striker.h"

class stateMachineStriker  
{
	private:
	int setpoint = 0;
	unsigned long currentTime = millis();
	float lastKnownGoalX = 0;
	float lastKnownGoalY = 0;
	bool goalDetected = false;
	bool ballControlled = false;
	
	Constants_striker:: stateMachine state;
	public:
		IRRing *robotIRRing;
		PixyCam *robotPixyCam;
		Motors *robotMotors;
		Bno *robotBNO;
		PID *robotPID;
		Photo *robotPhoto;
		stateMachineStriker(IRRing *robotIRRing, PixyCam *robotPixyCam, Motors *robotMotors, Bno *robotBNO, PID *robotPID, Photo *robotPhoto);
		void InitializeStateMachine();
		void flippingRobot();
		void searchBall();
		int searchGoal();
		void goToGoal();
		void goToLastKnownGoal();
		bool isOnLine();
		bool checkBallControlled();
		void lineCorrection();


};
#endif
