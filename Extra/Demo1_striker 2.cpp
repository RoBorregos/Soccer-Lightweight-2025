#include "stateMachineStriker.h"
#include "Constants_striker.h"
#include "constants.h"

stateMachineStriker *striker =nullptr;
IRRing robotIRRing;
PixyCam robotPixyCam;
Motors robotMotors{
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2
};
Bno robotBNO;
PID robotPID(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);
Photo robotPhoto;

Constants_striker::stateMachine state;

void setup() {
    Serial.begin(9600);
    stateMachineStriker robotStriker(&robotIRRing, &robotPixyCam, &robotMotors, &robotBNO, &robotPID, &robotPhoto);
    striker = &robotStriker;
    striker->InitializeStateMachine();
    
}
void loop(){
    if (striker->isOnLine()){
        Serial.println("On line");
        state = Constants_striker::line;
    }else{
        Serial.println("Not on line");
        state = Constants_striker::searchBall;
    }

    if (state == Constants_striker::line){
        striker->lineCorrection();
        if(!striker->isOnLine()){
            state = Constants_striker::searchBall;
        }   
    }else if(state == Constants_striker::searchBall){
        striker->searchBall();
        if (striker->checkBallControlled()){
            state = Constants_striker::hasBall;
        }
    }else if(state == Constants_striker::hasBall){
        striker->searchGoal();
        state = Constants_striker::scoreGoal;
    }else if(state == Constants_striker::scoreGoal){
        striker->goToGoal();
    } 
}