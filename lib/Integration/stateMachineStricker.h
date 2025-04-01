
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

	unsigned long current_time;
	uint8_t last=1;
	uint8_t lastP=1;
	ConstantsStricker:: stateMachine state;
	ConstantsStricker:: sides atack=ConstantsStricker::sides::yellow;
	uint8_t setpoint = 0;
	uint8_t translation_angle = 0;
	uint8_t adjust_angle = 0;
	float x=0;
	uint8_t angle=0;
	uint8_t numberObjects=0;
	uint8_t heightGoal=10;
	const uint8_t heightGoalMax=20;
	uint8_t block;
	float weidthBlock1=0;
	float weidthBlock2=0;
	float weidthBlock3=0;


	public:

	//stateMachineStricker() : robotIrRing(nullptr), pidRobot(nullptr), Pixy(nullptr),motorsRobot(nullptr),robotPthototransistors(nullptr),bno(nullptr), current_time(0), last(1), lastP(1), state(), atack(ConstantsStricker::sides::yellow), setpoint(0), translation_angle(0), adjust_angle(0), x(0), angle(0), numberObjects(0), heightGoal(10), block(0), weidthBlock1(0), weidthBlock2(0), weidthBlock3(0) {}
	stateMachineStricker(IRRing *ir, PID *pidRobot, PixyCam *pixy, Motors *robotMotors, Photo *phot, Bno *bnoRobot);	
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
		IRRing *robotIrRing;
		PID *robotPid;
	//Bno gyro;
		PixyCam *Pixy;
		Motors *motorsRobot;
		Photo *robotPthototransistors;
		Bno *bno;

	
		

};
#endif
