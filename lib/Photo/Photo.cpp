#include "Photo.h"


Photo::Photo() {}


int Photo::ReadPhotoLeft() {
    int sum = 0;
    for (int i = 0; i < kPhotoLeftElements; i++) {
        photo_left[i] = analogRead(kPhotoLeftPins[i]);
        sum += photo_left[i];
    }
    average_photo_left = sum / kPhotoLeftElements;
    return average_photo_left;
}

int Photo::ReadPhotoRight() {
    int sum = 0;
    for (int i = 0; i < kPhotoRightElements; i++) {
        photo_right[i] = analogRead(kPhotoRightPins[i]);
        sum += photo_right[i];
    }
    average_photo_right = sum / kPhotoRightElements;
    return average_photo_right;
}

int Photo::ReadPhotoFront() {
    int sum = 0;
    for (int i = 0; i < kPhotoFrontElements; i++) {
        photo_front[i] = analogRead(kPhotoFrontPins[i]);
        sum += photo_front[i];
    }
    average_photo_front = sum / kPhotoFrontElements;
    return average_photo_front;
}

bool Photo::CheckPhotoFront() {
    int front = ReadPhotoFront();
    return front < kPhotoTresholdFront;
}

bool Photo::CheckPhotoLeft() {
    int left = ReadPhotoLeft();
    return left < kPhotoTresholdLeft;
}

bool Photo::CheckPhotoRight() {
    int right = ReadPhotoRight();
    return right < kPhotoTresholdRight;
}



