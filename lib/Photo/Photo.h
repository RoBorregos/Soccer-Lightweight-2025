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