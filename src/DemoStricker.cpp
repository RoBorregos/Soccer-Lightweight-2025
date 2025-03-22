#include "stateMachineStricker.h"
#include "Arduino.h"
#include "SingleEMAFilterLib.h"
#include "motors.h"
#include "ConstantsStricker.h"

int atack=1;
IRRing robotIrRing;
stateMachineStricker robotStricker;

Motors motorsRobot(kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2,
    kMotor4Pwm, kMotor4In1, kMotor4In2);

ConstantsStricker:: stateMachine state;
ConstantsStricker:: sides atackSide=ConstantsStricker::sides::yellow;

void setup(){
    robotStricker.startObjects();
    delay(1600);
}
void loop(){
    state=ConstantsStricker::searchBall;
   
   /* if(stateMachine==ConstantsStricker::stateMachine::line){
        Serial.println(kReceiveLineAngle);
        if(ultrasoncio<30){
            kReceiveLineAngle=0;
        }
  */ ///Cuando tenga el código se foto
  //Check if have posesion of the ball
  if(state==ConstantsStricker::ballDetected){
        robotIrRing.UpdateData();
        state=(robotStricker.detector()>15&&abs(robotIrRing.GetAngle())<20)?ConstantsStricker::scoreGoal:ConstantsStricker::searchBall;

  }
  //Search ball
  if(state==ConstantsStricker::searchBall){
    if(robotStricker.detectLeftLine()== false){
        state=ConstantsStricker::line;
        robotStricker.goOutOfLine(-45);
        state=ConstantsStricker::searchBall;
    
    }else if(robotStricker.detectRightLine()== false){
        state=ConstantsStricker::line;
        robotStricker.goOutOfLine(45);
        state=ConstantsStricker::searchBall;
    }else if (robotStricker.detectFrontLine()== false){
        state=ConstantsStricker::line;
        robotStricker.goOutOfLine(-90);
        state=ConstantsStricker::searchBall;
    }
    Serial.println("search");
    robotStricker.searchBall();
  }
  //Go to the goal with the ball
  if(state==ConstantsStricker::scoreGoal){
    Serial.println("gol");
    robotStricker.updateGoalData();
  }
}