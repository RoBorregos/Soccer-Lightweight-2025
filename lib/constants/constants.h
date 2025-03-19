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

const int kMotor3In1 = 34; 
const int kMotor3In2 = 33;
const int kMotor3Pwm = 4; 

const int kMotor4In1 = 30;
const int kMotor4In2 = 31;
const int kMotor4Pwm = 3; 

const int kMotor2In1 = 36;
const int kMotor2In2 = 35;
const int kMotor2Pwm = 5; 

const int kMotor1In1 = 29;
const int kMotor1In2 = 28;
const int kMotor1Pwm = 2;

// Photo Left
const int kPhotoLeft1 = A0;
const int kPhotoLeft2 = A1;
const int kPhotoLeft3 = A2;
const int kPhotoLeft4 = A3;
const int kPhotoLeft5 = A4;
const int kPhotoLeft6 = A5;
const int kPhotoLeft7 = A6;
const int kPhotoLeft8 = A7;

// Photo Right
const int kPhotoRight1 = A8;
const int kPhotoRight2 = A9;
const int kPhotoRight3 = A10;
const int kPhotoRight4 = A11;
const int kPhotoRight5 = A12;
const int kPhotoRight6 = A13;
const int kPhotoRight7 = A14;
const int kPhotoRight8 = A15;
const int kPhotoFront1 = A16;
const int kPhotoFront2 = A17;

/*
// Photo Front
const int kPhotoFront3 = A18;
const int kPhotoFront4 = A19;
const int kPhotoFront5 = A20;
const int kPhotoFront6 = A21;
const int kPhotoFront7 = A22;
const int kPhotoFront8 = A23;
*/

// Receive signals
const uint8_t kReceiveBno = 's';
const uint8_t kReceiveBallAngle = 'c';
const uint8_t kReceiveBallDistance = 'd';
const uint8_t kReceiveGoalAngle = 'g';
const uint8_t kReceiveGoalDistance = 'k';
const uint8_t kReceiveLineAngle = 'r';

#endif  

