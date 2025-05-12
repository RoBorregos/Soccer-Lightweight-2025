#ifndef constants_h
#define constants_h
#include <stdint.h>


//--------------------Pines for arduino mega--------------------
const uint8_t kMotor1In1 = 23; // Izquierda
const uint8_t kMotor1In2 = 22;
const uint8_t kMotor1Pwm = 6;

const uint8_t kMotor2In1 = 24; // centro
const uint8_t kMotor2In2 = 25; 
const uint8_t kMotor2Pwm = 5;

const uint8_t kMotor3In1 = 27; // derecha
const uint8_t kMotor3In2 = 26;
const uint8_t kMotor3Pwm = 4;

const double kMaxPWM = 255.0; // We set a max PWM to limit the motors movement for better performance and control
const double kMinPWM = 40.0; // We set the minimum PWM that the robot needs to move

//--------------------Pins for multiplexer and phototransistors--------------------

const uint8_t kSignalPin1 = A6; 
const uint8_t kMUXPin1_1 = 14; 
const uint8_t kMUXPin2_1 = 15;
const uint8_t kMUXPin3_1 = 16;

const uint8_t kSignalPin2 = A8;
const uint8_t kMUXPin1_2 = 17;
const uint8_t kMUXPin2_2 = 28;
const uint8_t kMUXPin3_2 = 29;

const uint8_t kSignalPin3 = A7;
const uint8_t kMUXPin1_3 = 43;
const uint8_t kMUXPin2_3 = 44;
const uint8_t kMUXPin3_3 = 45;

// Phototransistors
const uint8_t kPhotoLeftElements = 8;
const uint8_t kPhotoRightElements = 8;
const uint8_t kPhotoFrontElements = 8;

// Photo Treshold
const int kPhotoTresholdLeft = 260;
const int kPhotoTresholdRight = 290;
const int kPhotoTresholdFront = 315; // 81

// Ultrasonic sensor
const uint8_t kTrigPin = 33;
const uint8_t kEchoPin = 32;

const uint8_t kMinGoalKeeperTresholdY = 35; // Minimum distance to the goal in cm
const uint8_t kMaxGoalKeeperTresholdY = 65; // Maximum distance to the goal in cm
const int kLeftGoalKeeperTresholdX = 116; // Minimum distance to the goal in cm
const int kRightGoalKeeperTresholdX = 275; // Maximum distance to the goal in cm
const uint8_t kGoalKeeperTresholdX = 15;

#endif  