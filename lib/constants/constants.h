#ifndef constants_h
#define constants_h
#include <stdint.h>

// Motor 4
/*const uint8_t MOTOR3_IN1 = 23;
const uint8_t MOTOR3_IN2 = 22;
const uint8_t MOTOR3_PWM = 15;*/

// Motor 3
/*const uint8_t MOTOR2_IN1 = 25;
const uint8_t MOTOR2_IN2 = 6;
const uint8_t MOTOR2_PWM = 20;*/

// Motor 1
/*const uint8_t MOTOR4_IN1 = 9;
const uint8_t MOTOR4_IN2 = 8;
const uint8_t MOTOR4_PWM = 10;*/

// Motor 2
/*const uint8_t MOTOR1_IN1 = 14;
const uint8_t MOTOR1_IN2 = 11;
const uint8_t MOTOR1_PWM = 21;*/

const uint8_t kMotor1Pwm = 4;
const uint8_t kMotor1In1 = 22;
const uint8_t kMotor1In2 = 23;

const uint8_t kMotor3Pwm = 6; 
const uint8_t kMotor3In1 = 26; 
const uint8_t kMotor3In2 = 27;


const uint8_t kMotor2Pwm = 5; 
const uint8_t kMotor2In1 = 24;
const uint8_t kMotor2In2 = 25;


// Photo Left
const uint8_t kPhotoLeftElements = 5;
const uint8_t kPhotoLeftPins[kPhotoLeftElements] = {A0, A1,A2,A3,A4}; // These are the pins abailable on robot where test was done

// Photo Right
const uint8_t kPhotoRightElements = 5;
const uint8_t kPhotoRightPins[kPhotoRightElements] = {A5,A6,A7,A8,A9}; // These are the pins abailable on robot where test was done

// No photo front abailable on test
// Photo Front
const uint8_t kPhotoFrontElements = 2;
const uint8_t kPhotoFrontPins[kPhotoFrontElements] = {A10, A11};


// Photo Treshold
const int kPhotoTresholdLeft = 113;
const int kPhotoTresholdRight=387;
const int kPhotoTresholdFront=77;

// Receive signals
const uint8_t kReceiveBno = 's';
const uint8_t kReceiveBallAngle = 'c';
const uint8_t kReceiveBallDistance = 'd';
const uint8_t kReceiveGoalAngle = 'g';
const uint8_t kReceiveGoalDistance = 'k';
const uint8_t kReceiveLineAngle = 'r';

#endif  

