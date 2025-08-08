#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "PixyCam.h" 
#include "Photo.h"
#include "Ultrasonic.h"

uint8_t j = 1;

bool isCorrecting = false;
int setpoint = 0;
float kBallFollowOffsetBack = 1.2;
float kBallFollowOffsetSide = 1.0;
float kBallFollowOffsetFront = 1.0;
uint8_t targetSignature = 2;
const uint32_t kCommunicationMode = SPI_MODE0; //This mode is used because we are using the SPI communication
int kLineCorrectionTime = 375;
unsigned long currentTime = millis();

Photo photo(
    kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
    kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
    kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);
Bno bno;
PixyCam pixy;
IRRing irring;
Ultrasonic ultrasonic(kTrigPin, kEchoPin);
PID pid_w(0.75/kMaxPWM, 0/kMaxPWM, 0.005/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In2, kMotor2In1,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

uint8_t switchPin = 42;

unsigned long lastUltrasonicReadTime = 0; // Last ultrasonic read time
const unsigned long ultrasonicReadInterval = 50; // Reading interval in milliseconds
float distanceY = 0; // Last Y distance reading
float distanceX = 0; // Last X distance reading
TargetGoalData targetGoalData = {0, 0, 0, 0, 0, 0}; // Structure to store target data

int X;

uint8_t kGoalkeeperCorrectionTime = 50;
float correctionStartTime = 0;

void setup() {
    Serial.begin(9600);
    pixy.Init(kCommunicationMode);
    motors.InitializeMotors(switchPin);
    bno.InitializeBNO();
    irring.init(&currentTime);
    irring.SetOffset(0.0);
}

void loop() {
    int motors_start_time;
    motors.StartStopMotors(switchPin); // Switch to digital pin 
    if (j == 1){
        motors_start_time = millis();
        j = 2;
    }
    pixy.updateData();
    irring.UpdateData();
    uint8_t numberObjects = pixy.numBlocks();
    float yaw = bno.GetBNOData();
    float ballAngle = irring.GetAngle(kBallFollowOffsetBack, kBallFollowOffsetSide, kBallFollowOffsetFront);
    float speed_w = pid_w.Calculate(setpoint, yaw);

    bool hasPosesion = abs(ballAngle) > 10;

    if (hasPosesion) {
        // Adjust speed based on angle
        motors.MoveOmnidirectionalBase(ballAngle, 0.45, speed_w);
    } else if (!hasPosesion) {
        TargetGoalData targetGoalData = pixy.getTargetGoalData(numberObjects, targetSignature);
        if(targetGoalData.signature == targetSignature) {
            motors.MoveOmnidirectionalBase(targetGoalData.cameraAngle, 0.4, speed_w);
        }
    }
    Serial.print(hasPosesion);


    PhotoData photoDataLeft = photo.CheckPhotosOnField(Side::Left);
    PhotoData photoDataRight = photo.CheckPhotosOnField(Side::Right);
    PhotoData photoDataFront = photo.CheckPhotosOnField(Side::Front);

    if (millis() - motors_start_time >= 1500){
        if (photoDataLeft.is_on_line) {
            motors.MoveOmnidirectionalBase(photoDataLeft.correction_degree, 1, 0);
            delay (kLineCorrectionTime);
            motors.StopAllMotors();
            return;
        } else if (photoDataRight.is_on_line) {
            motors.MoveOmnidirectionalBase(photoDataRight.correction_degree, 1, 0);
            delay (kLineCorrectionTime);
            motors.StopAllMotors();
            return;
        } else if (photoDataFront.is_on_line) {
            motors.MoveOmnidirectionalBase(photoDataFront.correction_degree, 1, 0);
            delay (kLineCorrectionTime);
            motors.StopAllMotors();
            return;
        }
    }
}
