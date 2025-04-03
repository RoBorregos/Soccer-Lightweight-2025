#include "Arduino.h"
#include "stateMachineStricker.h"
#include "SingleEMAFilterLib.h"
#include "motors.h"
#include "ConstantsStricker.h"
#include "Photo.h"
#include "constants.h"

//Photo &robotPthototransistors;
stateMachineStricker *robot = nullptr;
Bno bno;
IRRing robotIrRing;
Motors motorsRobot(4, 22,23,5,24,25,6,26,27);
PixyCam Pixy;
PID robotPid(0.2, 0.0735,45,200);
Photo robotPthototransistors;

ConstantsStricker:: stateMachine state;
ConstantsStricker:: sides atackSide=ConstantsStricker::sides::yellow;

void setup(){
    Serial.begin(19200);
    Serial.println("Start");
    stateMachineStricker robotStricker(&robotIrRing,&robotPid,&Pixy, &motorsRobot, &robotPthototransistors,&bno);
    robot = &robotStricker;
    robot->startObjects();
    delay(1600);
}

void loop(){
    bool leftLine=robot->robotPthototransistors->CheckPhotoLeft();
    Serial.println("frontLine check");
    bool rightLine=robot->robotPthototransistors->CheckPhotoRight();
    Serial.println("frontLine check");
    bool frontLine=robot->robotPthototransistors->CheckPhotoFront();
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
            robot->avoidLine(-45);
            state=ConstantsStricker::searchBall;
            Serial.println("searchBall left");
    
        }else if(rightLine== false){
            robot->avoidLine(45);
            state=ConstantsStricker::searchBall;
            Serial.println("searchBall right");
        }else if (frontLine== false){
            robot->avoidLine(-90);
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
    robot->searchBall();
    state=ConstantsStricker::scoreGoal;

  }
  //Go to the goal with the ball
  if(state==ConstantsStricker::scoreGoal){
    Serial.println("gol");
    robot->goToGoal();
}
}