#ifndef PHOTO_H
#define PHOTO_H
#include "Arduino.h"
#include "motors.h"
#include "constants.h"
#include "MUX.h"

class Photo {
public:
    // Photo();
    MUX left_MUX;
    MUX right_MUX;
    MUX front_MUX;
    Photo(uint8_t SignalPin1, uint8_t MUXPin1_1, uint8_t MUXPin2_1, uint8_t MUXPin3_1,
        uint8_t SignalPin2, uint8_t MUXPin1_2, uint8_t MUXPin2_2, uint8_t MUXPin3_2,
        uint8_t SignalPin3, uint8_t MUXPin1_3, uint8_t MUXPin2_3, uint8_t MUXPin3_3);
    int ReadPhotoLeft();
    int ReadPhotoRight();
    int ReadPhotoFront();
    bool CheckPhotoLeft();
    bool CheckPhotoRight();
    bool CheckPhotoFront();

private:
    // Photo Left
    uint16_t photo_left[kPhotoLeftElements];
    int average_photo_left;
    // Photo Right
    uint16_t photo_right[kPhotoRightElements];
    int average_photo_right;
    // Photo Front
    uint16_t photo_front[kPhotoFrontElements];
    int average_photo_front;
};

#endif // PHOTO_H