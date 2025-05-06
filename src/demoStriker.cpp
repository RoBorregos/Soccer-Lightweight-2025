#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "PixyCam.h" 
#include "Photo.h"

int setpoint = 0;
float kBallFollowOffsetBack = 1.0;
float kBallFollowOffsetSide = 1.0;
float kBallFollowOffsetFront = 1.0;
unsigned long currentTime = millis();
float lastKnownGoalX = 0;
float lastKnownGoalY = 0;
int targetSignature = 2;
bool goalDetected = false;
bool ballControlled = false;
const uint32_t kCommunicationMode = SPI_MODE0; //This mode is used because we are using the SPI communication
int kLineCorrectionTime = 275;
double kCorrectionDegreeOffset = 5;
Photo photo(
    kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
    kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
    kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);
Bno bno;
PixyCam pixy;
IRRing irring;
PID pid(0.45/kMaxPWM, 0.01/kMaxPWM, 0.00075/kMaxPWM, 100);//0.30  0.01 0.01
Motors motors( // motor pins for striker jamaica0
    kMotor1Pwm, kMotor1In2, kMotor1In1,
    kMotor3Pwm, kMotor3In2, kMotor3In1,
    kMotor2Pwm, kMotor2In2, kMotor2In1);

uint8_t switchPin = 42; // Pin for the switch to start/stop the motors
TargetGoalData targetGoalData = {0, 0, 0, 0, 0, 0};
void setup() {
    Serial.begin(9600);
    pixy.Init(kCommunicationMode);
    motors.InitializeMotors(switchPin);
    bno.InitializeBNO();
    irring.init(&currentTime);
    irring.SetOffset(0.0);

}
void loop() {
    motors.StartStopMotors(switchPin);
    //--------------------------- Update data from sensors ---------------------------
    // currentTime = millis();
    irring.UpdateData();
    double rawAngle = irring.GetRawAngle();
    double ballAngle = irring.GetAngle(kBallFollowOffsetBack, kBallFollowOffsetSide, kBallFollowOffsetFront);
    double yaw = bno.GetBNOData();
    double speed_w = pid.Calculate(setpoint, yaw);
    pixy.updateData();
    uint8_t numberObjects = pixy.numBlocks();
    // pixy.updateData();
    // int numberObjects = pixy.numBlocks();
    
    Serial.print("  Raw angle: ");
    Serial.print(rawAngle);
    Serial.print("  Ball angle: ");
    Serial.println(ballAngle);

    // Serial.print("Number of objects: ");
    // Serial.print(numberObjects);
    float speed;
    if (ballAngle>10 || ballAngle<-10){
        speed = 0.35;
    } else if (ballAngle <=10 || ballAngle >= -10){
        speed = 0.55;
    }
    motors.MoveOmnidirectionalBase(ballAngle, speed, speed_w, kCorrectionDegreeOffset);
    // targetGoalData = pixy.getTargetGoalData(numberObjects, targetSignature);
    // double angleGoal= targetGoalData.cameraAngle ;
    // // if (ballAngle<=10|| ballAngle>=-10){
    //  motors.MoveOmnidirectionalBase(angleGoal, speed, speed_w, kCorrectionDegreeOffset);
    // // }

    // if(targetGoalData.signature==targetSignature){
    //     int height=targetGoalData.height;
    //     if (height > 4){
    //         motors.MoveOmnidirectionalBase(180,0.35,speed_w, kCorrectionDegreeOffset);
    //         motors.StopAllMotors();
    //     }
    // }
    // PhotoData photoDataFront = photo.CheckPhotosOnField(Side::Front);
    // if (photoDataFront.is_on_line) {
    //     motors.MoveOmnidirectionalBase(photoDataFront.correction_degree, 1, speed_w, kCorrectionDegreeOffset);
    //     delay (kLineCorrectionTime);
    //     motors.StopAllMotors();
    // }


}

// #include "motors.h"
// #include "BNO.h"
// #include <Arduino.h>
// #include "IRRing.h"
// #include "PID.h"
// #include "constants.h"
// #include "PixyCam.h" 
// #include "Photo.h"

// int setpoint = 0;
// float kBallFollowOffsetBack = 1.0;
// float kBallFollowOffsetSide = 1.0;
// float kBallFollowOffsetFront = 1.0;
// unsigned long currentTime = millis();
// float lastKnownGoalX = 0;
// float lastKnownGoalY = 0;
// int targetSignature = 1;
// bool goalDetected = false;
// bool ballControlled = false;
// const uint32_t kCommunicationMode = SPI_MODE0; //This mode is used because we are using the SPI communication
// int kLineCorrectionTime = 100;
// double kCorrectionDegreeOffset = 16;
// Photo photo(
//     kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
//     kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
//     kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);
// Bno bno;
// PixyCam pixy;
// IRRing irring;
// PID pid(0.9375/kMaxPWM, 0/kMaxPWM, 0/kMaxPWM, 100);
// Motors motors(
//     kMotor1Pwm, kMotor1In1, kMotor1In2,
//     kMotor2Pwm, kMotor2In1, kMotor2In2,
//     kMotor3Pwm, kMotor3In1, kMotor3In2);

// void setup() {
//     Serial.begin(9600);
//     pixy.Init(kCommunicationMode);
//     motors.InitializeMotors();
//     bno.InitializeBNO();
//     irring.init(&currentTime);
//     irring.SetOffset(0.0);

// }
// void loop() {
//     //--------------------------- Update data from sensors ---------------------------
//     // currentTime = millis();
//     irring.UpdateData();
//     double ballAngle = irring.GetAngle(kBallFollowOffsetBack, kBallFollowOffsetSide, kBallFollowOffsetFront);
//     double yaw = bno.GetBNOData();
//     double speed_w = pid.Calculate(setpoint, yaw);
//     // pixy.updateData();
//     // int numberObjects = pixy.numBlocks();
    
//     Serial.print("  Ball angle: ");
//     Serial.println(ballAngle);
//     // Serial.print("Number of objects: ");
//     // Serial.print(numberObjects);

   // motors.MoveOmnidirectionalBase(ballAngle, 0.45, speed_w, kCorrectionDegreeOffset);
    //--------------------------- Phototransistors reading and correction ---------------------------

//     // PhotoData photoDataLeft = photo.CheckPhotosOnField(Side::Left);
//     // PhotoData photoDataRight = photo.CheckPhotosOnField(Side::Right);
//     // PhotoData photoDataFront = photo.CheckPhotosOnField(Side::Front);

//     // if (photoDataLeft.is_on_line) {
//     //     motors.MoveOmnidirectionalBase(photoDataLeft.correction_degree, 1, 0);
//     //     delay (kLineCorrectionTime);
//     //     motors.StopAllMotors();
//     // } else if (photoDataRight.is_on_line) {
//     //     motors.MoveOmnidirectionalBase(photoDataRight.correction_degree, 1, 0);
//     //     delay (kLineCorrectionTime);
//     //     motors.StopAllMotors();
//     // if (photoDataFront.is_on_line) {
//     //     motors.MoveOmnidirectionalBase(photoDataFront.correction_degree, 1, speed_w, kCorrectionDegreeOffset);
//     //     delay (kLineCorrectionTime);
//     //     motors.StopAllMotors();
//     // }

//     //--------------------------- Pixy with motion ---------------------------
//     // for (int i = 0; i < numberObjects; i++){
//     //     int signature = pixy.getSignature();
//     //     Serial.print("  signature: ");
//     //     Serial.print(signature);
//     //     if (signature == targetSignature){
//     //         int x = pixy.getX(i);
//     //         // Serial.println("x");
//     //         // Serial.println(x);
//     //         int y = pixy.getY(i);
//     //         // Serial.println("y");
//     //         // Serial.println(y);
//     //         float goalAngle = (x-158)*(60.0/316.0)*-1;
//     //         Serial.print("  angleX: ");
//     //         Serial.println(goalAngle);

//     //         if (abs(ballAngle) < 5){
//     //             motors.MoveOmnidirectionalBase(goalAngle, 0.5, 0);
//     //         }
//     //     }
//     // }
// }