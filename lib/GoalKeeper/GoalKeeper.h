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

class stateMachineGoalKeeper {

public:
    stateMachineGoalKeeper();
    void update();
    void changeState(State newState);

private:
    State currentState;
    void handleIdleState();
    void handleMoveToPositionState();
    void handleBlockShotState();
    void handleClearBallState();
};

#endif // GOALKEEPER_H