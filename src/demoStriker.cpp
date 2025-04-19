#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "PixyCam.h" 
#include "Photo.h"

int setpoint = 0;
float kBallFollowOffsetBack = 1.12;
float kBallFollowOffsetSide = 1.09;
float kBallFollowOffsetFront = 0.9;
unsigned long currentTime = millis();
float lastKnownGoalX = 0;
float lastKnownGoalY = 0;
int targetSignature = 1;
bool goalDetected = false;
bool ballControlled = false;
const uint32_t kCommunicationMode = SPI_MODE0; //This mode is used because we are using the SPI communication
int kLineCorrectionTime = 200;

Photo photo;
Bno bno;
PixyCam pixy;
IRRing irring;
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

void setup() {
    Serial.begin(115200);
    pixy.Init(kCommunicationMode);
    motors.InitializeMotors();
    bno.InitializeBNO();
    irring.init(&currentTime);
    irring.SetOffset(0.0);

}
void loop() {
    //--------------------------- Update data from sensors ---------------------------
    currentTime = millis();
    irring.UpdateData();
    double ballAngle = irring.GetAngle(kBallFollowOffsetBack, kBallFollowOffsetSide, kBallFollowOffsetFront);
    double yaw = bno.GetBNOData();
    double speed_w = pid.Calculate(setpoint, yaw);
    pixy.updateData();
    int numberObjects = pixy.numBlocks();
    // Serial.print("Number of objects: ");
    // Serial.print(numberObjects);

    // if (abs(ballAngle) > 5){
    motors.MoveOmnidirectionalBase(ballAngle, 0.5, 0);
    // }

    Serial.print("  Ball angle: ");
    Serial.println(ballAngle);
    //--------------------------- Phototransistors reading and correction ---------------------------

    // PhotoData photoDataLeft = photo.CheckPhotosOnField(Side::Left);
    // PhotoData photoDataRight = photo.CheckPhotosOnField(Side::Right);
    // PhotoData photoDataFront = photo.CheckPhotosOnField(Side::Front);

    // if (photoDataLeft.is_on_line) {
    //     motors.MoveOmnidirectionalBase(photoDataLeft.correction_degree, 1, 0);
    //     delay (kLineCorrectionTime);
    //     motors.StopAllMotors();
    // } else if (photoDataRight.is_on_line) {
    //     motors.MoveOmnidirectionalBase(photoDataRight.correction_degree, 1, 0);
    //     delay (kLineCorrectionTime);
    //     motors.StopAllMotors();
    // } else if (photoDataFront.is_on_line) {
    //     motors.MoveOmnidirectionalBase(photoDataFront.correction_degree, 1, 0);
    //     delay (kLineCorrectionTime);
    //     motors.StopAllMotors();
    // }

    //--------------------------- PID Correction ---------------------------
    if (speed_w > 0.1 || speed_w < -0.1) {
        motors.StopAllMotors();
        motors.MoveOmnidirectionalBase(0, 0, speed_w);
    }

    //--------------------------- Pixy with motion ---------------------------
    // for (int i = 0; i < numberObjects; i++){
    //     int signature = pixy.getSignature();
    //     Serial.print("  signature: ");
    //     Serial.print(signature);
    //     if (signature == targetSignature){
    //         int x = pixy.getX(i);
    //         // Serial.println("x");
    //         // Serial.println(x);
    //         int y = pixy.getY(i);
    //         // Serial.println("y");
    //         // Serial.println(y);
    //         float goalAngle = (x-158)*(60.0/316.0)*-1;
    //         Serial.print("  angleX: ");
    //         Serial.println(goalAngle);

    //         if (abs(ballAngle) < 5){
    //             motors.MoveOmnidirectionalBase(goalAngle, 0.5, 0);
    //         }
    //     }
    // }
}