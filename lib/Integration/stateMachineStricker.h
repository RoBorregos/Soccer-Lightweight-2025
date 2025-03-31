
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
	IRRing *robotIrRing;
	PID *robotPid;
	//Bno gyro;
	PixyCam *Pixy;
	Motors *motorsRobot;
	Photo *robotPthototransistors;
	Bno *bno;
	unsigned long current_time;
	int last=1;
	int lastP=1;
	ConstantsStricker:: stateMachine state;
	ConstantsStricker:: sides atack=ConstantsStricker::sides::yellow;
	int setpoint = 0;
	int translation_angle = 0;
	int adjust_angle = 0;
	float x=0;
	int angle=0;
	int numberObjects=0;
	int heightGoal=10;
	const int heightGoalMax=20;
	uint8_t block;
	float weidthBlock1=0;
	float weidthBlock2=0;
	float weidthBlock3=0;


	public:

	stateMachineStricker() : robotIrRing(nullptr), robotPid(nullptr), Pixy(nullptr),motorsRobot(nullptr),robotPthototransistors(nullptr),bno(nullptr), current_time(0), last(1), lastP(1), state(), atack(ConstantsStricker::sides::yellow), setpoint(0), translation_angle(0), adjust_angle(0), x(0), angle(0), numberObjects(0), heightGoal(10), block(0), weidthBlock1(0), weidthBlock2(0), weidthBlock3(0) {}
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
		void goToGoal();
		void avoidLine(int angle);

	
		

};
#endif
