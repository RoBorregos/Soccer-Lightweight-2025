#include "stateMachineStriker.h"  

stateMachineStriker::stateMachineStriker(IRRing *robotIRRing, PixyCam *robotPixyCam, Motors *robotMotors, Bno *robotBNO, PID *robotPID, Photo *robotPhoto)
{
    this->robotIRRing = robotIRRing;
    this->robotPixyCam = robotPixyCam;
    this->robotMotors = robotMotors;
    this->robotBNO = robotBNO;
    this->robotPID = robotPID;
    this->robotPhoto = robotPhoto;


}
void stateMachineStriker::InitializeStateMachine()
{
  
    goalDetected = false;
    ballControlled = false;
    lastKnownGoalX = 0;
    lastKnownGoalY = 0;
    currentTime=millis();
    robotIRRing->init(&currentTime);
    robotIRRing->UpdateData();
    robotMotors->InitializeMotors();
    robotPixyCam->Init(Constants_striker().kCommunicationMode);
    robotPixyCam->updateData();
    robotBNO->InitializeBNO();
}
void stateMachineStriker::flippingRobot()
{
    Serial.println("Flipping the robot");
    robotIRRing->UpdateData();
    double ballAngle = robotIRRing->GetAngle(Constants_striker(). kBallFollowOffsetBack,Constants_striker(). kBallFollowOffsetSide,Constants_striker(). kBallFollowOffsetFront);
    Serial.println("Ball angle");
    Serial.println(ballAngle);
    if (ballAngle>120 || ballAngle<-120){
        robotMotors->MoveOmnidirectionalBase(0,0,0.5);
        delay(1000);
        robotMotors->StopAllMotors();
    }
    else{
        Serial.println("The robot is facing the front, it isn't necessary to rotate it");
    }
    
}
void stateMachineStriker::searchBall()
{
    Serial.println("Searching for the ball");
    robotIRRing->UpdateData();
    double ballAngle = robotIRRing->GetAngle(Constants_striker().kBallFollowOffsetBack,Constants_striker(). kBallFollowOffsetSide,Constants_striker(). kBallFollowOffsetFront);
    double yaw = robotBNO->GetBNOData();
    double speedW=robotPID->Calculate(setpoint,yaw);
    robotMotors->MoveOmnidirectionalBase(ballAngle,Constants_striker().kVelocitySearchBall,0);
    if (speedW>0.1 || speedW<-0.1) {
        robotMotors->StopAllMotors();
        robotMotors->MoveOmnidirectionalBase(0,0,speedW);
    }
}
int stateMachineStriker::searchGoal()
{
    Serial.println("Searching for the goal");
    robotPixyCam->updateData();
    int numberObjects=robotPixyCam->numBlocks();
    Serial.println("Number of objects");
    Serial.println(numberObjects);
    int bestBlock=-1;
    for(int i=0;i<numberObjects;i++){
        int signature=robotPixyCam->getSignature();

        if (signature== Constants_striker().kTargetSignature){
                    bestBlock=i;
                    return bestBlock;
                
        }
    }
    return -1;
}
void stateMachineStriker::goToGoal()
{

    Serial.println("Going to the goal");
    int bestBlock=searchGoal();
        //Step 3-Checking if the goal is detected, and go to it
        if (bestBlock!= -1 ){
            float x=robotPixyCam->getX(bestBlock);
            Serial.println("best x");
            Serial.println(x);
            float y=robotPixyCam->getY(bestBlock);
            Serial.println("best y");
            Serial.println(y);
            lastKnownGoalX=x;
            lastKnownGoalY=y;
            goalDetected=true;
            float angle = (x-158)*(60.0/316.0)*-1;
            robotMotors->MoveOmnidirectionalBase(angle,Constants_striker().kVelocityAtack,0);
            double yaw = robotBNO->GetBNOData();
            double speedW=robotPID->Calculate(setpoint,yaw);
            if (speedW>0.1 || speedW<-0.1) {
                robotMotors->StopAllMotors();
                robotMotors->MoveOmnidirectionalBase(0,0,speedW);
            }
            if (isOnLine()){
                robotMotors->StopAllMotors();
                lineCorrection();
            }
        }else if(goalDetected){
            Serial.println("Goal not detected, going to the last known goal");
            goToLastKnownGoal();
        }else{
            Serial.println("Goal not detected, searching for it");
            robotMotors->MoveOmnidirectionalBase(0,Constants_striker().kVelocitySearchBall,0.4);
        }
}
void stateMachineStriker::goToLastKnownGoal()
{
    Serial.println("Going to the last known goal");
    if (goalDetected){
        float angle = (lastKnownGoalX-158)*(60.0/316.0)*-1;
        robotMotors->MoveOmnidirectionalBase(angle,Constants_striker().kVelocityAtack,0);
        double yaw = robotBNO->GetBNOData();
        double speedW=robotPID->Calculate(setpoint,yaw);
        if (speedW>0.1 || speedW<-0.1) {
            robotMotors->StopAllMotors();
            robotMotors->MoveOmnidirectionalBase(0,0,speedW);
        }
    }
}
bool stateMachineStriker::checkBallControlled()
{
    Serial.println("Checking if the ball is controlled");
    robotIRRing->UpdateData();
    double ballAngle = robotIRRing->GetAngle(Constants_striker().kBallFollowOffsetBack,Constants_striker(). kBallFollowOffsetSide,Constants_striker(). kBallFollowOffsetFront);
  return abs(ballAngle)<10;
}
bool stateMachineStriker::isOnLine()
{
    Serial.println("Checking if on line");
    PhotoData photoDataLeft = robotPhoto->CheckPhotosOnField(Side::Left);
    PhotoData photoDataRight =robotPhoto->CheckPhotosOnField(Side::Right);
    PhotoData photoDataFront =robotPhoto->CheckPhotosOnField(Side::Front);
    if (photoDataLeft.is_on_line || photoDataRight.is_on_line  || photoDataFront.is_on_line ) {
        return true;
    } else {
        return false;
    }
}
void stateMachineStriker::lineCorrection()
{
    Serial.println("Line correction");
    currentTime = millis();
    
    PhotoData photoDataLeft = robotPhoto->CheckPhotosOnField(Side::Left);
    PhotoData photoDataRight =robotPhoto->CheckPhotosOnField(Side::Right);
    PhotoData photoDataFront =robotPhoto->CheckPhotosOnField(Side::Front);

    if (photoDataLeft.is_on_line) {
        robotMotors->MoveOmnidirectionalBase(photoDataLeft.correction_degree, 1, 0);
        delay (Constants_striker().kLineCorrectionTime);
        robotMotors->StopAllMotors();
    }
    else if (photoDataRight.is_on_line) {
        robotMotors->MoveOmnidirectionalBase(photoDataRight.correction_degree, 1, 0);
        delay (Constants_striker().kLineCorrectionTime);
        robotMotors->StopAllMotors();
    }
    else if (photoDataFront.is_on_line) {
        robotMotors->MoveOmnidirectionalBase(photoDataFront.correction_degree, 1, 0);
        delay (Constants_striker().kLineCorrectionTime);
        robotMotors->StopAllMotors();
    }
}
