#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "PixyCam.h" 

int setpoint = 0;
const int kBallFollowOffset=1.1;
const int HeightGoalMax= 3;
unsigned long currentTime = millis();
float lastKnownGoalX=0;
float lastKnownGoalY=0;
int targetSignature=1;
bool goalDetected=false;
bool ballControlled=false;

Bno bno;
PixyCam pixy;
IRRing irring;
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

void setup() {
    Serial.begin(9600);
    Serial3.begin(19200);
    irring.init(&currentTime);
    irring.SetOffset(0.0);
    pixy.Init();
}
void loop() {
    currentTime = millis();
    irring.UpdateData();
    double ballAngle = irring.GetAngle();
    double yaw = bno.GetBNOData();

    //Step 1 -Searching for the ball
    if (abs(ballAngle) > 10) {
        Serial.println("Searching ball");
        motors.MoveOmnidirectionalBase(ballAngle*kBallFollowOffset, 0.5, 0);
        double speed_w = pid.Calculate(setpoint, yaw);
        if (speed_w > 0.1 || speed_w < -0.1) {
            motors.StopAllMotors();
            motors.MoveOmnidirectionalBase(0, 0, speed_w);
        }
    }else{
        Serial.println("Ball found");
        ballControlled=true;
    }
    //Step 2-Searching for the goal
    if (ballControlled){
        pixy.updateData();
        int numberObjects=pixy.numBlocks();
        int bestBlock=-1;
        int maxWidth=0;
        int bestHeight=0;
        for(int i=0;i<numberObjects;i++){
            int height=pixy.getHeight(i);
            Serial.println(height);
            int width= pixy.getWidth(i);
            Serial.println(width);
            int signature=pixy.getSignature();

            if (signature==targetSignature){
                if (height> HeightGoalMax){
                    if(width>maxWidth){
                        maxWidth=width;
                        bestBlock=i;
                        bestHeight=height;
                    }
                }
            }
        }
        //Step 3-Checking if the goal is detected, and go to it
        if (bestBlock!= -1 ){
            float x=pixy.getX(bestBlock);
            Serial.println("best x");
            Serial.println(x);
            float y=pixy.getY(bestBlock);
            Serial.println("best y");
            Serial.println(y);
            lastKnownGoalX=x;
            lastKnownGoalY=y;
            goalDetected=true;
            float setpointGoal= x-160;
            motors.MoveOmnidirectionalBase(setpointGoal,0.7, 0);
            delay(1000);
            motors.StopAllMotors();
            Serial.println("Goal reached");
        }
        //Step 4-Checking if the goal is lost
        else{
            if(goalDetected){
                float setpointGoal= lastKnownGoalX-160;
                motors.MoveOmnidirectionalBase(setpointGoal,0.7, 0);
            }else{
                motors.MoveOmnidirectionalBase(ballAngle*kBallFollowOffset, 0.5, 0);
                double speed_w = pid.Calculate(setpointGoal, yaw);
                if (speed_w > 0.1 || speed_w < -0.1) {
                    motors.StopAllMotors();
                    motors.MoveOmnidirectionalBase(0, 0, speed_w);
                }
            }
        }
        }
    }

        
    /*double speed_w = pid.Calculate(setpoint, yaw);
    motors.MoveOmnidirectionalBase(ballAngle*kBallFollowOffset, 0.5, 0);
    if (speed_w > 0.1 || speed_w < -0.1) {
        motors.StopAllMotors();
        motors.MoveOmnidirectionalBase(0, 0, speed_w);
    }
    if ( abs(ballAngle) > 10 ) {
        // motors.MoveOmnidirectionalBase(angle, 0.5, 0);
        Serial.println("moving robot with the ball");
        motors.MoveOmnidirectionalBase(ballAngle, 0.5, 0);
    } else {
        Serial.println("atack function");
        static unsigned long lastMoveTime=0;
        pixy.updateData();
        int numberObjects=pixy.numBlocks();
        
        int bestBlock=-1;
        int maxWidth=0;
        int bestHeight=0;
    
        for(int i=0;i<numberObjects;i++){
            int height=pixy.getHeight(i);
            int width= pixy.getWidth(i);
    
            if (height> HeightGoalMax){
                if(width>maxWidth){
                    maxWidth=width;
                    bestBlock=i;
                    bestHeight=height;
                }
            }
        }
        float x=pixy.getX(bestBlock);
        int setpoint=pixy.angleGoal(x);
        
        if (bestHeight>= HeightGoalMax){
            motors.StopAllMotors();
            delay(500);
            motors.MoveOmnidirectionalBase(180,255,0);
            delay(1000);
            motors.StopAllMotors();
            return;
        }
        
        motors.MoveOmnidirectionalBase(setpoint,0.7, 0);
    }    

    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("\tradio: ");
    Serial.println(strength);
    delay(50);*/    

    }
}
