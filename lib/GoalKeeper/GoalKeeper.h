#ifndef STATEMACHINEGOALKEEPER_H
#define STATEMACHINEGOALKEEPER_H

#include <Arduino.h>
#include "BNO.h"
#include "constants.h"
#include "IRRing.h"
#include "motor.h"
#include "motors.h"
#include "PixyCam.h"
#include "SingleEMAFilterLib.h"
#include "PID.h"
#include <Wire.h>
#include "Photo.h"
#include <Pixy2I2C.h>
#include <Pixy2.h>
#include "constantsGoalKeeper.h"

class stateMachineGoalKeeper {

public:
    stateMachineGoalKeeper() : robotIrRing(), robotPid(1.5, 0.00735, 45, 200), bno(), Pixy(), motorsRobot(9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 11, 10), robotPthototransistors(), last(1), lastP(1), state(), {}
    void initializeStateMachineGoalKeeper();
    void getInsideLimits();
    void moveToIntercept();
    void passToTeammate();

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
	ConstantsGoalKeeper:: stateMachine state;
	ConstantsGoalKeeper:: sides defend = ConstantsGoalKeeper::sides::yellow;
	int setpoint = 0;
	int translation_angle = 0;
	int adjust_angle = 0;
	float x=0;
	int angle=0;
};

#endif // GOALKEEPER_H