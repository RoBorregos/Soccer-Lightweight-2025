#include "motors.h"
#include "BNO.h"
#include <Arduino.h>
#include "IRRing.h"
#include "PID.h"
#include "constants.h"
#include "PixyCam.h" 
#include "Photo.h"
#include "Ultrasonic.h"

bool isCorrecting = false;
int setpoint = 0;
float kBallFollowOffsetBack = 1.0;
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
PID pid_w(0.9375/kMaxPWM, 0.01/kMaxPWM, 0.01/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

uint8_t switchPin = 42;

unsigned long lastUltrasonicReadTime = 0; // Last ultrasonic read time
const unsigned long ultrasonicReadInterval = 50; // Reading interval in milliseconds
float distanceY = 0; // Last Y distance reading
float distanceX = 0; // Last X distance reading
TargetGoalData targetGoalData = {0}; // Structure to store target data

int X;

uint8_t kGoalkeeperCorrectionTime = 50;
float correctionStartTime = 0;

void setup() {
    Serial.begin(9600);
    pixy.Init(kCommunicationMode);
    motors.InitializeMotors(switchPin);
    bno.InitializeBNO();
    ultrasonic.UltrasonicInit();
    irring.init(&currentTime);
    irring.SetOffset(0.0);
}

void loop() {
    motors.StartStopMotors(switchPin); // Switch to digital pin
    pixy.updateData();
    irring.UpdateData();
    uint8_t numberObjects = pixy.numBlocks();
    float yaw = bno.GetBNOData();
    float ballAngle = irring.GetAngle(kBallFollowOffsetBack, kBallFollowOffsetSide, kBallFollowOffsetFront);
    float speed_w = pid_w.Calculate(setpoint, yaw);

    // Update ultrasonic readings every certain time
    if (millis() >= 450){ // Wait to allow the sensor to start reading
        if ((millis() - lastUltrasonicReadTime >= ultrasonicReadInterval)) {
            lastUltrasonicReadTime = millis(); // Update the last read time
            targetGoalData = pixy.getTargetGoalData(numberObjects, targetSignature);
            distanceY = ultrasonic.getDistanceY();
            distanceX = ultrasonic.getDistanceX(targetGoalData.cameraAngle, distanceY);
            X = targetGoalData.x;
        }
    }


    // Verify if the robot has possession of the ball
    bool dentroDelRectangulo = (distanceY >= kMinGoalKeeperTresholdY && distanceY <= kMaxGoalKeeperTresholdY && (X <= kRightGoalKeeperTresholdX && X >= kLeftGoalKeeperTresholdX) || (distanceX >= -kGoalKeeperTresholdX && distanceX <= kGoalKeeperTresholdX)); 

    // Serial.print("Signature: ");
    // Serial.print(targetGoalData.signature);
    // Serial.print("  Angle: ");
    // Serial.print(targetGoalData.cameraAngle);
    // Serial.print("  Distance Y: ");
    // Serial.print(distanceY);
    // Serial.print("  Distance X: ");
    // Serial.print(distanceX);
    // Serial.print("  X: ");
    // Serial.print(targetGoalData.x);
    // Serial.print("  Yaw: ");
    // Serial.print(yaw);
    // Serial.print("  Ball angle: ");
    // Serial.println(ballAngle);
    // Serial.print("  Dentro del rectangulo: ");
    // Serial.println(dentroDelRectangulo);
    
//---------------------------Goalkeeper correction------------------
if (!dentroDelRectangulo){
    // Front center
    if (distanceY >= kMaxGoalKeeperTresholdY && (X >= kLeftGoalKeeperTresholdX && X <= kRightGoalKeeperTresholdX)){ // || (distanceX >= -kGoalKeeperTresholdX && distanceX <= kGoalKeeperTresholdX))
        motors.MoveOmnidirectionalBase(180, 0.37, speed_w);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
    // Back center
    } else if (distanceY <= kMinGoalKeeperTresholdY && (X >= kLeftGoalKeeperTresholdX && X <= kRightGoalKeeperTresholdX)){ // || (distanceX >= -kGoalKeeperTresholdX && distanceX <= kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(0, 0.37, speed_w);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
    // Front Left
    } else if (distanceY >= kMaxGoalKeeperTresholdY && X <= kLeftGoalKeeperTresholdX){ // || distanceX >= kGoalKeeperTresholdX
        motors.MoveOmnidirectionalBase(-135, 0.37, speed_w);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
    // Front Right
    } else if (distanceY >= kMaxGoalKeeperTresholdY && X >= kRightGoalKeeperTresholdX){ // || distanceX <= -kGoalKeeperTresholdX
        motors.MoveOmnidirectionalBase(135, 0.37, speed_w);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
    // Back Left
    } else if (distanceY <= kMinGoalKeeperTresholdY && X <= kLeftGoalKeeperTresholdX){ //  || distanceX >= kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(-45, 0.37, speed_w);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
    // Back Right
    } else if (distanceY <= kMinGoalKeeperTresholdY && X >= kRightGoalKeeperTresholdX){ // || distanceX <= -kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(45, 0.37, speed_w);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
    // Left
    } else if ((distanceY >= kMinGoalKeeperTresholdY && distanceY <= kMaxGoalKeeperTresholdY) && X <= kLeftGoalKeeperTresholdX){ // || distanceX >= kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(-90, 0.37, speed_w);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors(); 
     // Right
    } else if ((distanceY >= kMinGoalKeeperTresholdY && distanceY <= kMaxGoalKeeperTresholdY) && X >= kRightGoalKeeperTresholdX){ // || distanceX <= -kGoalKeeperTresholdX)
        motors.MoveOmnidirectionalBase(90, 0.37, speed_w);
        delay(kGoalkeeperCorrectionTime);
        motors.StopAllMotors();
    }
} if (dentroDelRectangulo) {
    motors.MoveOmnidirectionalBase(ballAngle, 0.35, speed_w);
} 
}