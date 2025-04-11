#include "Photo.h"
//---------------Transition from individual pins to MUX------------------ 
// On the ReadPhoto methods there is a line commented because the MUX is not integrated to the hardware yet
// The commented line is for the individual reading of the photoresistors


Photo::Photo(uint8_t mux_signal_pin1, uint8_t mux_pin1, uint8_t mux_pin2, uint8_t mux_pin3, uint8_t mux_signal_pin2, uint8_t mux_pin1_2, uint8_t mux_pin2_2, uint8_t mux_pin3_2, uint8_t mux_signal_pin3, uint8_t mux_pin1_3, uint8_t mux_pin2_3, uint8_t mux_pin3_3):
    left_mux_(mux_signal_pin1, mux_pin1, mux_pin2, mux_pin3),
    right_mux_(mux_signal_pin2, mux_pin1_2, mux_pin2_2, mux_pin3_2),
    front_mux_(mux_signal_pin3, mux_pin1_3, mux_pin2_3, mux_pin3_3)
        {}

int Photo::ReadPhotoLeft() {
    int sum = 0;
    for (int i = 0; i < kPhotoLeftElements; i++) {
        // photo_left[i] = analogRead(kPhotoLeftPins[i]);
        photo_left[i] = left_MUX.readChannel(i);
        sum += photo_left[i];
    }
    average_photo_left = sum / kPhotoLeftElements;
    return average_photo_left;
}

int Photo::ReadPhotoRight() {
    int sum = 0;
    for (int i = 0; i < kPhotoRightElements; i++) {
        // photo_right[i] = analogRead(kPhotoRightPins[i]);
        photo_right[i] = right_MUX.readChannel(i);
        sum += photo_right[i];
    }
    average_photo_right = sum / kPhotoRightElements;
    return average_photo_right;
}

int Photo::ReadPhotoFront() {
    int sum = 0;
    for (int i = 0; i < kPhotoFrontElements; i++) {
        // photo_front[i] = analogRead(kPhotoFrontPins[i]);
        photo_front[i] = front_MUX.readChannel(i);
        sum += photo_front[i];
    }
    average_photo_front = sum / kPhotoFrontElements;
    return average_photo_front;
}

bool Photo::CheckPhotoFront() {
    int front = ReadPhotoFront();
    return front > kPhotoTresholdFront;
}

bool Photo::CheckPhotoLeft() {
    int left = ReadPhotoLeft();
    return left > kPhotoTresholdLeft;
}

bool Photo::CheckPhotoRight() {
    int right = ReadPhotoRight();
    return right > kPhotoTresholdRight;
}

uint16_t Photo::ReadPhoto(Side side) {
    int sum = 0;
    int* photo_array;
    int elements;
    MUX* mux;

    switch (side) {
        case Side::Left:
            photo_array = photo_left;
            elements = kPhotoLeftElements;
            this->mux = mux = &left_mux_;
            break;
        case Side::Right:
            photo_array = photo_right;
            elements = kPhotoRightElements;
            this->mux = mux = &right_mux_;
            break;
        case Side::Front:
            photo_array = photo_front;
            elements = kPhotoFrontElements;
            this->mux = mux = &front_mux_;
            break;
        default:
            return 0; // Invalid side
    }

    for (int i = 0; i < elements; i++) {
        photo_array[i] = mux->readChannel(i);
        sum += photo_array[i];
    }

    return sum / elements;
}

bool Photo::CheckPhoto(Side side) {
    int average = ReadPhoto(side);
    switch (side) {
        case Side::Left:
            return average > kPhotoTresholdLeft;
        case Side::Right:
            return average > kPhotoTresholdRight;
        case Side::Front:
            return average > kPhotoTresholdFront;
        default:
            return false; // Invalid side
    }
}



std::pair<uint16_t, bool> Photo::GetPhotoData(Side side) {
    uint8_t sum = 0;
    int* photo_array;
    uint8_t elements;
    MUX* mux;
    uint16_t threshold;

    switch (side) {
        case Side::Left:
            photo_array = photo_left;
            elements = kPhotoLeftElements;
            this->mux = mux = &left_mux_;
            threshold = kPhotoTresholdLeft;
            break;
        case Side::Right:
            photo_array = photo_right;
            elements = kPhotoRightElements;
            this->mux = mux = &right_mux_;
            threshold = kPhotoTresholdRight;
            break;
        case Side::Front:
            photo_array = photo_front;
            elements = kPhotoFrontElements;
            this->mux = mux = &front_mux_;
            threshold = kPhotoTresholdFront;
            break;
        default:
            return {0, false}; // Invalid side
    }

    for (int i = 0; i < elements; i++) {
        photo_array[i] = mux->readChannel(i);
        sum += photo_array[i];
    }

    uint16_t average = sum / elements;
    bool exceeds_threshold = average > threshold;

    return {average, exceeds_threshold};
}


