#include "Photo.h"
#include "constants.h"
#include "motors.h"
#include <Arduino.h>


Photo::Photo() {}


void Photo::ReadPhotoLeft() {
    photo_left1 = analogRead(kPhotoLeft1);
    photo_left2 = analogRead(kPhotoLeft2);
    photo_left3 = analogRead(kPhotoLeft3);
    photo_left4 = analogRead(kPhotoLeft4);
    photo_left5 = analogRead(kPhotoLeft5);
    photo_left6 = analogRead(kPhotoLeft6);
    photo_left7 = analogRead(kPhotoLeft7);
    photo_left8 = analogRead(kPhotoLeft8);
    average_photo_left = (photo_left1 + photo_left2 + photo_left3 + photo_left4 + photo_left5 + photo_left6 + photo_left7 + photo_left8) / 8;
}

void Photo::ReadPhotoRight() {
    photo_right1 = analogRead(kPhotoRight1);
    photo_right2 = analogRead(kPhotoRight2);
    photo_right3 = analogRead(kPhotoRight3);
    photo_right4 = analogRead(kPhotoRight4);
    photo_right5 = analogRead(kPhotoRight5);
    photo_right6 = analogRead(kPhotoRight6);
    photo_right7 = analogRead(kPhotoRight7);
    photo_right8 = analogRead(kPhotoRight8);
    average_photo_right = (photo_right1 + photo_right2 + photo_right3 + photo_right4 + photo_right5 + photo_right6 + photo_right7 + photo_right8) / 8;
}

void Photo::ReadPhotoFront() {
    /*
    photo_front1 = analogRead(kPhotoFront1);
    photo_front2 = analogRead(kPhotoFront2);
    photo_front3 = analogRead(kPhotoFront3);
    photo_front4 = analogRead(kPhotoFront4);
    photo_front5 = analogRead(kPhotoFront5);
    photo_front6 = analogRead(kPhotoFront6);
    photo_front7 = analogRead(kPhotoFront7);
    photo_front8 = analogRead(kPhotoFront8);
    int average_photo_front = (photo_front1 + photo_front2 + photo_front3 + photo_front4 + photo_front5 + photo_front6 + photo_front7 + photo_front8) / 8;
*/
}

int Photo::GetPhotoValueLeft() {
    return average_photo_left;
}

int Photo::GetPhotoValueRight() {
    return average_photo_right;
}

int Photo::GetPhotoValueFront() {
    return average_photo_front;
}

void Photo::LineCorrectionLeft() {
    double current_millis = millis();
    double motor_start_millis = 0;
    double motor_photo_correction = 90;
    
    motors.MoveMotorsImu(90,255,0);
    motor_start_millis = current_millis;
    if (current_millis - motor_start_millis >= motor_photo_correction)
    {
    motors.StopMotors();
    }
}

void Photo::LineCorrectionRight() {
    double current_millis = millis();
    double motor_start_millis = 0;
    double motor_photo_correction = 90;
    
    motors.MoveMotorsImu(270,255,0);
    motor_start_millis = current_millis;
    if (current_millis - motor_start_millis >= motor_photo_correction)
    {
    motors.StopMotors();
    }
}

void Photo::LineCorrectionFront() {
    double current_millis = millis();
    double motor_start_millis = 0;
    double motor_photo_correction = 90;
    
    motors.MoveMotorsImu(180,255,0);
    motor_start_millis = current_millis;
    if (current_millis - motor_start_millis >= motor_photo_correction)
    {
    motors.StopMotors();
    }
}

