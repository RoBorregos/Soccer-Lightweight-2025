#ifndef PHOTO_H
#define PHOTO_H
#include "Arduino.h"
#include "motors.h"
#include "constants.h"

class Photo {
public:
    Photo();
    int ReadPhotoLeft();
    int ReadPhotoRight();
    int ReadPhotoFront();
    bool CheckPhotoLeft();
    bool CheckPhotoRight();
    bool CheckPhotoFront();

private:
    int Line_Treshold;
    // Photo Left
    int photo_left1;
    int photo_left2;
    int photo_left3;
    int photo_left4;
    int photo_left5;
    int photo_left6;
    int photo_left7;
    int photo_left8;
    int average_photo_left;
    // Photo Right
    int photo_right1;
    int photo_right2;
    int photo_right3;
    int photo_right4;
    int photo_right5;
    int photo_right6;
    int photo_right7;
    int photo_right8;
    int average_photo_right;
    // Photo Front
    int photo_front1;
    int photo_front2;
    int photo_front3;
    int photo_front4;
    int photo_front5;
    int photo_front6;
    int photo_front7;
    int photo_front8;
    int average_photo_front;
};

#endif // PHOTO_H