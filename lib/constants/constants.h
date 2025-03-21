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

const uint8_t kMotor3In1 = 34; 
const uint8_t kMotor3In2 = 33;
const uint8_t kMotor3Pwm = 4; 

const uint8_t kMotor4In1 = 30;
const uint8_t kMotor4In2 = 31;
const uint8_t kMotor4Pwm = 3; 

const uint8_t kMotor2In1 = 36;
const uint8_t kMotor2In2 = 35;
const uint8_t kMotor2Pwm = 5; 

const uint8_t kMotor1In1 = 29;
const uint8_t kMotor1In2 = 28;
const uint8_t kMotor1Pwm = 2;

// Photo Left
const uint8_t kPhotoLeftElements = 2;
const uint8_t kPhotoLeftPins[kPhotoLeftElements] = {A2, A7}; // These are the pins abailable on robot where test was done

// Photo Right
const uint8_t kPhotoRightElements = 1;
const uint8_t kPhotoRightPins[kPhotoRightElements] = {A3}; // These are the pins abailable on robot where test was done

// No photo front abailable on test
// Photo Front
const uint8_t kPhotoFrontElements = 3;
const uint8_t kPhotoFrontPins[kPhotoFrontElements] = {A14, A15, A16};



// Photo Treshold
const int kPhotoTreshold = 2500;

// Receive signals
const uint8_t kReceiveBno = 's';
const uint8_t kReceiveBallAngle = 'c';
const uint8_t kReceiveBallDistance = 'd';
const uint8_t kReceiveGoalAngle = 'g';
const uint8_t kReceiveGoalDistance = 'k';
const uint8_t kReceiveLineAngle = 'r';

#endif  

