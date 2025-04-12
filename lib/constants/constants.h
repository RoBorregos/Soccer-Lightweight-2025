#ifndef constants_h
#define constants_h
#include <stdint.h>

const uint8_t kMotor3In1 = 53; // Back center motor
const uint8_t kMotor3In2 = 52;
const uint8_t kMotor3Pwm = 5; 

const uint8_t kMotor2In1 = 51; // Derecha
const uint8_t kMotor2In2 = 50;
const uint8_t kMotor2Pwm = 6; 

const uint8_t kMotor1In1 = 49; // Izquierda
const uint8_t kMotor1In2 = 48;
const uint8_t kMotor1Pwm = 7;

const double kMaxPWM = 255.0; // We set a max PWM to limit the motors movement for better performance and control
const double kMinPWM = 40.0; // We set the minimum PWM that the robot needs to move

// Photo Left
const uint8_t kPhotoLeftElements = 5;
const uint8_t kPhotoLeftPins[kPhotoLeftElements] = {A0, A1,A2,A3,A4}; // These are the pins abailable on robot where test was done

// Photo Right
const uint8_t kPhotoRightElements = 5;
const uint8_t kPhotoRightPins[kPhotoRightElements] = {A5,A6,A7,A8,A9}; // These are the pins abailable on robot where test was done

// Photo Front
const uint8_t kPhotoFrontElements = 2;
const uint8_t kPhotoFrontPins[kPhotoFrontElements] = {A10, A11};

// Photo Treshold
const int kPhotoTresholdLeft = 53;
const int kPhotoTresholdRight = 387;
const int kPhotoTresholdFront = 77;


// Receive signals
const uint8_t kReceiveBno = 's';
const uint8_t kReceiveBallAngle = 'c';
const uint8_t kReceiveBallDistance = 'd';
const uint8_t kReceiveGoalAngle = 'g';
const uint8_t kReceiveGoalDistance = 'k';
const uint8_t kReceiveLineAngle = 'r';

#endif  