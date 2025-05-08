#include "Photo.h"
#include "Arduino.h"
#include "motors.h"
#include "constants.h"
#include "BNO.h"
#include "PID.h"
#include "IRRing.h"

int currentTime;
int setpoint = 0;
int kLineCorrectionTime = 100; // Tiempo de corrección en milisegundos

Photo photo(
    kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
    kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
    kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);
IRRing irring;
Bno bno;
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In2, kMotor2In1,
    kMotor3Pwm, kMotor3In1, kMotor3In2);


void setup() {
    Serial.begin(19200);
    motors.InitializeMotors(42);
}

void loop() {
    currentTime = millis();
    motors.StartStopMotors(42);
    motors.MoveOmnidirectionalBase(0, 0.4, 0, 0);
    PhotoData photoDataLeft = photo.CheckPhotosOnField(Side::Left);
    PhotoData photoDataRight = photo.CheckPhotosOnField(Side::Right);
    PhotoData photoDataFront = photo.CheckPhotosOnField(Side::Front);
    //motors.MoveOmnidirectionalBase(0, 0.4, 0, 0);
    // Serial.print("Left on line");
    // Serial.print(photoDataLeft.is_on_line);
    // Serial.print("  Right on line");
    // Serial.print(photoDataRight.is_on_line);
    // Serial.print("  Front on line");
    // Serial.println(photoDataFront.is_on_line);

    // if (photoDataLeft.is_on_line) {
    //     motors.MoveOmnidirectionalBase(photoDataLeft.correction_degree, 1, 0, 0);
    //     delay (kLineCorrectionTime);
    //     motors.StopAllMotors();
    // } else if (photoDataRight.is_on_line) {
    //     motors.MoveOmnidirectionalBase(photoDataRight.correction_degree, 1, 0,0 );
    //     delay (kLineCorrectionTime);
    //     motors.StopAllMotors();
    // } else if (photoDataFront.is_on_line) {
    //     motors.MoveOmnidirectionalBase(photoDataFront.correction_degree, 1, 0, 0);
    //     delay (kLineCorrectionTime);
    //     motors.StopAllMotors();
    // }

    uint16_t valueleft = photo.ReadPhotoWithMUX(Side::Left);
    uint16_t valueright = photo.ReadPhotoWithMUX(Side::Right);
    uint16_t valuefront = photo.ReadPhotoWithMUX(Side::Front);
    Serial.print("Left photo value: ");
    Serial.print(valueleft);
    Serial.print("  Right photo value: ");
    Serial.print(valueright);
    Serial.print("  Front photo value: ");
    Serial.println(valuefront);
}