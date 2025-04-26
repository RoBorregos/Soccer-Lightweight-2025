#ifndef constants_h
#define constants_h
#include <stdint.h>

//--------------------Pines for arduino mega--------------------
const uint8_t kMotor1In1 = 22; // Izquierda
const uint8_t kMotor1In2 = 23;
const uint8_t kMotor1Pwm = 6;

const uint8_t kMotor2In1 = 25; // derecha
const uint8_t kMotor2In2 = 24; 
const uint8_t kMotor2Pwm = 5; 

const uint8_t kMotor3In1 = 26; // atrás
const uint8_t kMotor3In2 = 27;
const uint8_t kMotor3Pwm = 4; 

// --------------------Pines for esp32--------------------

// const uint8_t kMotor2In1 = 26; 
// const uint8_t kMotor2In2 = 25;
// const uint8_t kMotor2Pwm = 13; 

// const uint8_t kMotor3In1 = 33; 
// const uint8_t kMotor3In2 = 32;
// const uint8_t kMotor3Pwm = 27; 

// const uint8_t kMotor1In1 = 19; 
// const uint8_t kMotor1In2 = 18;
// const uint8_t kMotor1Pwm = 15;

const double kMaxPWM = 255.0; // We set a max PWM to limit the motors movement for better performance and control
const double kMinPWM = 40.0; // We set the minimum PWM that the robot needs to move

//--------------------Pins for multiplexer and phototransistors--------------------

const uint8_t kSignalPin1 = A0; 
const uint8_t kMUXPin1_1 = 7; 
const uint8_t kMUXPin2_1 = 8;
const uint8_t kMUXPin3_1 = 9;

const uint8_t kSignalPin2 = A1;
const uint8_t kMUXPin1_2 = 10;
const uint8_t kMUXPin2_2 = 11;
const uint8_t kMUXPin3_2 = 12;

const uint8_t kSignalPin3 = A2;
const uint8_t kMUXPin1_3 = 13;
const uint8_t kMUXPin2_3 = 14;
const uint8_t kMUXPin3_3 = 15;

// Photo Left
const uint8_t kPhotoLeftElements = 8;
const uint8_t kPhotoLeftPins[kPhotoLeftElements] = {A0,A1,A2,A3,A4}; // These are the pins abailable on robot where test was done

// Photo Right
const uint8_t kPhotoRightElements = 8;
const uint8_t kPhotoRightPins[kPhotoRightElements] = {A5,A6,A7,A8,A9}; // These are the pins abailable on robot where test was done

// Photo Front
const uint8_t kPhotoFrontElements = 6;
const uint8_t kPhotoFrontPins[kPhotoFrontElements] = {A10, A11};

// Photo Treshold
const int kPhotoTresholdLeft = 110;
const int kPhotoTresholdRight = 661;
const int kPhotoTresholdFront = 62;

// Receive signals
// const uint8_t kReceiveBno = 's';
// const uint8_t kReceiveBallAngle = 'c';
// const uint8_t kReceiveBallDistance = 'd';
// const uint8_t kReceiveGoalAngle = 'g';
// const uint8_t kReceiveGoalDistance = 'k';
// const uint8_t kReceiveLineAngle = 'r';

#endif  