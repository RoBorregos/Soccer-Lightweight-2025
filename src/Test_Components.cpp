#include "motors.h"
#include "BNO.h"
#include "PID.h"
#include "constants.h"
#include "IRRing.h"
#include "Photo.h"
#include "PixyCam.h"
#include "Ultrasonic.h"
#include <Arduino.h>

unsigned long start_millis;
unsigned long current_millis;
double yaw;
double speed_w;
int setpoint = 0;
double kCorrectionDegreeOffset = 0;
const uint32_t kCommunicationMode = SPI_MODE0;

Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

Bno bno;
PixyCam pixy;
IRRing irring;
Ultrasonic ultrasonic(kTrigPin, kEchoPin);
Photo photo(
    kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
    kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
    kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);
PID pid(0.125/kMaxPWM, 0.1/kMaxPWM, 0.0125/kMaxPWM, 100);
// 1.125
uint8_t switchPin = 42;

void setup() {
    Serial.begin(9600);
    bno.InitializeBNO();
    ultrasonic.UltrasonicInit();
    irring.init(&start_millis);
    irring.SetOffset(0.0);
    pixy.Init(kCommunicationMode);

    start_millis = millis();
}

void loop() {
    motors.StartStopMotors(switchPin);
   
// // BNO   
//     yaw = bno.GetBNOData();
//     Serial.print("Yaw: ");
//     Serial.println(yaw);
// // PID    
//     speed_w = pid.Calculate(setpoint, yaw);
//     Serial.print("  Speed_w: ");
//     Serial.println(speed_w);
// // // IRRing
//     irring.UpdateData();
//     double ballAngle = irring.GetAngle(1.0, 1.0, 1.0);
//     Serial.print("  Ball angle: ");
//     Serial.println(ballAngle);
// // Phototransistors
//     int LeftValue = photo.ReadPhotoWithMUX(Side::Left);
//     int RightVale = photo.ReadPhotoWithMUX(Side::Right);
//     int FrontValue = photo.ReadPhotoWithMUX(Side::Front);
//     PhotoData photoDataLeft = photo.CheckPhotosOnField(Side::Left);
//     PhotoData photoDataRight = photo.CheckPhotosOnField(Side::Right);
//     PhotoData photoDataFront = photo.CheckPhotosOnField(Side::Front);
//     Serial.print("  Left value: ");
//     Serial.print(LeftValue);
//     Serial.print("  Right value: ");
//     Serial.print(RightVale);
//     Serial.print("  Front value: ");
//     Serial.print(FrontValue);
//     Serial.print("  Left on line: ");
//     Serial.print(photoDataLeft.is_on_line);
//     Serial.print("  Right on line: ");
//     Serial.print(photoDataRight.is_on_line);
//     Serial.print("  Front on line: ");
//     Serial.println(photoDataFront.is_on_line);
// Pixy
    int targerSignature = 2;
    pixy.updateData();
    int numberObjects = pixy.numBlocks();
    TargetGoalData targetGoalData = pixy.getTargetGoalData(numberObjects, targerSignature);
    Serial.print("numberObjects: ");
    Serial.print(numberObjects);
    Serial.print("  signature: ");
    Serial.print(targetGoalData.signature);
    Serial.print("  x: ");
    Serial.print(targetGoalData.x);
    Serial.print("  y: ");
    Serial.print(targetGoalData.y);
    Serial.print("  width: ");
    Serial.print(targetGoalData.width);
    Serial.print("  height: ");
    Serial.print(targetGoalData.height);
    Serial.print("  cameraAngle: ");
    Serial.println(targetGoalData.cameraAngle);
// // Ultrasonic
//     float distanceY = ultrasonic.getDistanceY();
//     float distanceX = ultrasonic.getDistanceX(targetGoalData.cameraAngle, distanceY);
//     Serial.print("  Distance Y: ");
//     Serial.print(distanceY);
//     Serial.print("  Distance X: ");
//     Serial.println(distanceX);
}