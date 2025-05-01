#include <Arduino.h>
#include "PixyCam.h"
#include "motors.h"
#include "BNO.h"
#include "PID.h"

const uint32_t kCommunicationMode= SPI_MODE0;
const int KSignatureGoal = 2;

PID pid(0.85/kMaxPWM, 0/kMaxPWM, 0.85/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
Bno bno;
PixyCam pixy;

void setup() {
    Serial.begin(9600);
    pixy.Init(kCommunicationMode);
    motors.InitializeMotors();
    bno.InitializeBNO();


    pixy.updateData();
    int numberObjects = pixy.numBlocks();
    for (int i = 0; i < numberObjects; i++){
        int signature = pixy.getSignature();
        if (signature == KSignatureGoal){
            int setpoint = 180
            ;
            double yaw = bno.GetBNOData();
            double speed_w = pid.Calculate(setpoint, yaw);
            double error = abs(setpoint - yaw);
            while (error >50){
                yaw= bno.GetBNOData();
                double speed_w = pid.Calculate(setpoint, yaw);
                Serial.print("Speed_w: ");
                Serial.println(speed_w);
                motors.MoveOmnidirectionalBase(0, 0, speed_w);
                error = abs(setpoint - yaw);
            }
            motors.StopAllMotors();
            bno.InitializeBNO();
            break;
        }
    
    }
}
void loop() {

    
}