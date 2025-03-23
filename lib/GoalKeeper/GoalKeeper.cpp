#include "stateMachineGoalKeeper.h"

stateMachineGoalkeeper::stateMachineGoalkeeper() {}

void stateMachineGoalkeeper::initializeStateMachineGoalkeeper() {
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
    Pixy.updateData();
    Pixy.GetSignature();
    Pixy.angleGoal();
    Pixy.GetHeight();

    if (Pixy.GetSignature() == 1) {
        if (Pixy.angleGoal() > 25) {
            motorsRobot.MoveBaseRight();
        } else if (Pixy.angleGoal() < -25) {
            motorsRobot.MoveBaseLeft();
        }

        if (Pixy.GetHeight() > 100) {
            motorsRobot.MoveBaseForward();
        } else if (Pixy.GetHeight() < 100) {
            motorsRobot.MoveBaseBackward();
        }
    } 
}

void stateMachineGoalkeeper::moveToIntercept() {
    robotIrRing.UpdateData();
    double angle = irring.GetAngle();
    double newAngle = (angle<0 ? 360+angle:angle);

    if (newAngle > 10 && newAngle < 350) {
        motorsRobot.MoveBaseWithImu(newAngle, 150, 0);
        Serial.println("fuera de rango");
    } else if (newAngle < 10 || newAngle > 350) {
        motorsRobot.StopAllMotors();
        Serial.println("dentro de rango");
    }
}

void stateMachineGoalkeeper::passToTeammate() {
    motors.MoveBaseWithImu(0, speed, speed_w);
    if Pixy.GetHight() > 100 {
        motors.StopAllMotors();
        currentStates = limits;
    }
}

