#include "GoalKeeper.h"

stateMachineGoalkeeper::stateMachineGoalkeeper() {
    // Constructor implementation
}

void stateMachineGoalkeeper::initializeStateMachineGoalkeeper() {
    // Initialization code
    Serial.begin(115200);
    unsigned long currentTime = millis();
    robotPid.setKp(0.2);
    robotPid.setMinToMove(40);
    bno.InitializeBNO();
    robotIrRing.Init(&current_time);
    robotIrRing.UpdateData();
    motorsRobot.InitializeMotors();
}

void stateMachineGoalkeeper::getInsideLimits() {
    // Initialization code
}

void stateMachineGoalkeeper::moveToIntercept() {
    // Initialization code
}

void stateMachineGoalkeeper::passToTeammate() {
    // Update state machine
}

