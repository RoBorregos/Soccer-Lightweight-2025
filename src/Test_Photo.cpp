#include "Photo.h"
#include "Arduino.h"
#include "motors.h"
#include "constants.h"
#include "BNO.h"
#include "PID.h"

int PhotoLeft;
int PhotoRight;
int PhotoFront;
bool PhotoLeftOnLine;
bool PhotoRightOnLine;
bool PhotoFrontOnLine;
int currentTime;
unsigned long motor_start_millis = 0;
unsigned long motor_photo_correction = 90;

Photo photo;
Motors motors(
    kMotor1Pwm, kMotor1In1, kMotor1In2,
    kMotor2Pwm, kMotor2In1, kMotor2In2,
    kMotor3Pwm, kMotor3In1, kMotor3In2);


void setup() {
    Serial.begin(9600);
    currentTime = millis();
}

void loop() {
    Serial.println("Reading photos");
    PhotoLeft = photo.ReadPhotoLeft();
    PhotoRight = photo.ReadPhotoRight();
    Serial.print("Photo Left: ");
    Serial.print(PhotoLeft);
    Serial.print("   Photo Right: ");
    Serial.println(PhotoRight);
    delay(1000);

    Serial.println("Checking photos");
    PhotoLeftOnLine = photo.CheckPhotoLeft();
    PhotoRightOnLine = photo.CheckPhotoRight();
    Serial.print("Photo Left on line: ");
    Serial.print(PhotoLeftOnLine);
    Serial.print("   Photo Right on line: ");
    Serial.println(PhotoRightOnLine);
    delay(1000);

    if (PhotoLeftOnLine) {
        Serial.println("Photo Left on line");
        motor_start_millis = currentTime;
        if (currentTime - motor_start_millis >= motor_photo_correction)
        {
        motors.StopAllMotors();
        }
    }

    if (PhotoRightOnLine) {
        Serial.println("Photo Right on line");
        motor_start_millis = currentTime;
        if (currentTime - motor_start_millis >= motor_photo_correction)
        {
        motors.StopAllMotors();
        }
    }

    if (PhotoFrontOnLine) {
        Serial.println("Photo Front on line");
        motor_start_millis = currentTime;
        if (currentTime - motor_start_millis >= motor_photo_correction)
        {
        motors.StopAllMotors();
        }
    }
}