#include "statusMachineStricker.h"
#include "Arduino.h"
#include "SingleEMAFilterLib.h"
#include "motors.h"
#include "ConstantsStricker.h"

int atack=1;
SingleEMAFilter<int>filterAnlogo(0.6);
Motors motorsRobot(kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2,
    kMotor4Pwm, kMotor4In1, kMotor4In2);

ConstantsStricker:: stateMachine state;
ConstantsStricker:: sides atack=ConstantsStricker::sides::yellow;
void setup();
    startObjects();
    delay(1600);
void loop(){
    state=ConstantsStricker::searchBall;
   
   /* if(stateMachine==ConstantsStricker::stateMachine::line{
        Serial.println(kReceiveLineAngle);
        if(ultrasoncio<30){
            kReceiveLineAngle=0;
        }
  */ ///Cuando tenga el código se foto
  //Check if have posesion of the ball
  if(state==ConstantsStricker::ballDetected){
        robotIrRing.UpdateData();
        state=(detector()>15&&abs(robotIrRing.GetAngle())<20)?ConstantsStricker::scoreGoal:ConstantsStricker::searchBall;

  }
  //Search ball
  if(state==ConstantsStricker::searchBall){
    Serial.println("search");
    searchBall();
  }
  //Go to the goal with the ball
  if(state==ConstantsStricker::scoreGoal){
    Serial.println("gol");
    updateGoalData();
  }
}