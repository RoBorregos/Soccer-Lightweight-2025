#ifndef PHOTO_H
#define PHOTO_H
#include "Arduino.h"
#include "motors.h"
#include "constants.h"
#include "MUX.h"
#include <utility> // For std::pair

enum class Side {
    Left,
    Right,
    Front
};

class Photo {
public:
    // Photo();
    MUX left_mux_;
    MUX right_mux_;
    MUX front_mux_;
    Photo(uint8_t signal_pin1, uint8_t mux_pin1_1, uint8_t mux_pin2_1, uint8_t mux_pin3_1,
        uint8_t signal_pin2, uint8_t mux_pin1_2, uint8_t mux_pin2_2, uint8_t mux_pin3_2,
        uint8_t signal_pin3, uint8_t mux_pin1_3, uint8_t mux_pin2_3, uint8_t mux_pin3_3);
    int ReadPhotoLeft();
    int ReadPhotoRight();
    int ReadPhotoFront();
    bool CheckPhotoLeft();
    bool CheckPhotoRight();
    bool CheckPhotoFront();
    uint16_t ReadPhoto(Side side);
    bool CheckPhoto(Side side);
    std::pair<uint16_t, bool> GetPhotoData(Side side);

private:
    // Photo Left
    uint16_t photo_left[kPhotoLeftElements];
    uint16_t average_photo_left;
    // Photo Right
    uint16_t photo_right[kPhotoRightElements];
    uint16_t average_photo_right;
    // Photo Front
    uint16_t photo_front[kPhotoFrontElements];
    uint16_t average_photo_front;
};

#endif // PHOTO_H