#include "Photo.h"
#include "Arduino.h"
#include "motors.h"
#include "constants.h"
#include "PID.h"

int currentTime;
int setpoint = 0;

Motor upper_left_motor(kMotor1Pwm, kMotor1In1, kMotor1In2);
Motor lower_center_motor(kMotor2Pwm, kMotor2In1, kMotor2In2);
Motor upper_right_motor(kMotor3Pwm, kMotor3In1, kMotor3In2);
Photo photo(
    kSignalPin1, kMUXPin1_1, kMUXPin2_1, kMUXPin3_1,
    kSignalPin2, kMUXPin1_2, kMUXPin2_2, kMUXPin3_2,
    kSignalPin3, kMUXPin1_3, kMUXPin2_3, kMUXPin3_3);
PID pid(1.2/kMaxPWM, 0/kMaxPWM, 1.3/kMaxPWM, 100);
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);

void setup() {
    Serial.begin(9600);
    motors.InitializeMotors();
}

void loop() {
    currentTime = millis();
    // motors.SetAllSpeeds(120);
    // upper_left_motor.MovePositive();
    // upper_right_motor.MovePositive();
    // lower_center_motor.MovePositive();
    uint16_t kPhotoTresholdLeft = photo.PhotoCalibrationOnLine(Side::Left);
    uint16_t kPhotoTresholdRight = photo.PhotoCalibrationOnLine(Side::Right);
    uint16_t kPhotoTresholdFront = photo.PhotoCalibrationOnLine(Side::Front);
    Serial.println("Calibration photos");
    Serial.print("Calibration Left: ");
    Serial.print(kPhotoTresholdLeft);
    Serial.print("   Calibration Right: ");
    Serial.print(kPhotoTresholdRight);
    Serial.print("   Calibration Front: ");
    Serial.println(kPhotoTresholdFront);
}
