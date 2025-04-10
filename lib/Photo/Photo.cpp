#include "Photo.h"


Photo::Photo() {}
// Photo::Photo(uint8_t MUXSignalPin1, uint8_t MUXPin1, uint8_t MUXPin2, uint8_t MUXPin3, uint8_t MUXSignalPin2, uint8_t MUXPin1_2, uint8_t MUXPin2_2, uint8_t MUXPin3_2, uint8_t MUXSignalPin3, uint8_t MUXPin1_3, uint8_t MUXPin2_3, uint8_t MUXPin3_3):
//         left_MUX(MUXSignalPin1, MUXPin1, MUXPin2, MUXPin3),
//         right_MUX(MUXSignalPin2, MUXPin1, MUXPin2, MUXPin3),
//         front_MUX(MUXSignalPin3, MUXPin1, MUXPin2, MUXPin3) 
//         {}

int Photo::ReadPhotoLeft() {
    int sum = 0;
    for (int i = 0; i < kPhotoLeftElements; i++) {
        photo_left[i] = analogRead(kPhotoLeftPins[i]);
        //photo_left[i] = left_MUX.readChannel(i);
        sum += photo_left[i];
    }
    average_photo_left = sum / kPhotoLeftElements;
    return average_photo_left;
}

int Photo::ReadPhotoRight() {
    int sum = 0;
    for (int i = 0; i < kPhotoRightElements; i++) {
        photo_right[i] = analogRead(kPhotoRightPins[i]);
        // photo_right[i] = right_MUX.readChannel(i);
        sum += photo_right[i];
    }
    average_photo_right = sum / kPhotoRightElements;
    return average_photo_right;
}

int Photo::ReadPhotoFront() {
    int sum = 0;
    for (int i = 0; i < kPhotoFrontElements; i++) {
        photo_front[i] = analogRead(kPhotoFrontPins[i]);
        // photo_front[i] = front_MUX.readChannel(i);
        sum += photo_front[i];
    }
    average_photo_front = sum / kPhotoFrontElements;
    return average_photo_front;
}

bool Photo::CheckPhotoLeft() {
    int left = ReadPhotoLeft();
    return left > kPhotoTresholdLeft;
}

bool Photo::CheckPhotoRight() {
    int right = ReadPhotoRight();
    return right > kPhotoTresholdRight;
}

bool Photo::CheckPhotoFront() {
    int front = ReadPhotoFront();
    return front > kPhotoTresholdFront;
}


