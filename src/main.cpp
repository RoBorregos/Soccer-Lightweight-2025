#include "Arduino.h"
#include "stateMachineStricker.h"
#include "SingleEMAFilterLib.h"
#include "motors.h"
#include "ConstantsStricker.h"
#include "Photo.h"
#include "constants.h"

Photo robotPthototransistors;
stateMachineStricker robotStricker;

ConstantsStricker:: stateMachine state;
ConstantsStricker:: sides atackSide=ConstantsStricker::sides::yellow;

void setup(){
    Serial.begin(115200);
    Serial.println("Start");
    robotStricker.startObjects();
    delay(1600);
}
void loop(){
    bool leftLine=robotPthototransistors.CheckPhotoLeft();
    Serial.println("frontLine check");
    bool rightLine=robotPthototransistors.CheckPhotoRight();
    Serial.println("frontLine check");
    bool frontLine=robotPthototransistors.CheckPhotoFront();
    Serial.println("frontLine check");

    state=ConstantsStricker::nothing;
    if((leftLine== false)||(rightLine== false)||(frontLine== false)){
        Serial.println("entrando a line");
        state=ConstantsStricker::line;
    }else{
        state=ConstantsStricker::searchBall;
    }
    //Line
   if(state==ConstantsStricker::stateMachine::line){
        if(leftLine== false){
            robotStricker.avoidLine(-45);
            state=ConstantsStricker::searchBall;
            Serial.println("searchBall left");
    
        }else if(rightLine== false){
            robotStricker.avoidLine(45);
            state=ConstantsStricker::searchBall;
            Serial.println("searchBall right");
        }else if (frontLine== false){
            robotStricker.avoidLine(-90);
            state=ConstantsStricker::searchBall;
            Serial.println("searchBall front");
   }}
  
  //Check if have posesion of the ball
  /*if(state==ConstantsStricker::ballDetected){
        robotIrRing.UpdateData();
        state=(robotStricker.detector()>15&&abs(robotIrRing.GetAngle())<20)?ConstantsStricker::scoreGoal:ConstantsStricker::searchBall;
    Serial.println("ballDetected");

  }*/ //Esto para más adelante 
  //Search ball
  if(state==ConstantsStricker::searchBall){
    Serial.println("search");
    robotStricker.searchBall();
    state=ConstantsStricker::scoreGoal;

  }
  //Go to the goal with the ball
  if(state==ConstantsStricker::scoreGoal){
    Serial.println("gol");
    robotStricker.goToGoal();
}
}