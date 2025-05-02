#include <Arduino.h>
#include "Photo.h"
#include "motors.h"
#include "IRRing.h"
#include "BNO.h"
#include "PID.h"

int setpoint = 0;
int currentTime;
Bno bno;
int kLineCorrectionTime = 300;
IRRing irring;
PID pid(0.8/kMaxPWM, 0/kMaxPWM, 0.85/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);
Photo photo(
    kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
    kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
    kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);

void setup() {
    Serial.begin(115200);
    unsigned long currentTime = millis();
    bno.InitializeBNO();
    motors.InitializeMotors();
    irring.init(&currentTime);
    irring.SetOffset(0.0);
    motors.InitializeMotors();
    }
void loop() {
    irring.UpdateData();
    currentTime = millis();
    double ballAngle = irring.GetAngle(1.1, 0.96, 0.95);
    double yaw = bno.GetBNOData();
    double speed_w = pid.Calculate(setpoint, yaw);
    motors.MoveOmnidirectionalBase(ballAngle, 0.5, 0);
    uint16_t valuefront = photo.ReadPhotoWithMUX(Side::Front);
    // if(valuefront>0){
    //     motors.StopAllMotors();
    //     delay(kLineCorrectionTime);
    //     motors.MoveOmnidirectionalBase(0,0,speed_w);
    // }else{
        motors.MoveOmnidirectionalBase(ballAngle, 0.5, 0);
    
        if (speed_w > 0.1 || speed_w < -0.1) {
            motors.StopAllMotors();
            motors.MoveOmnidirectionalBase(0, 0, speed_w);
        }
    //}
    
}
    