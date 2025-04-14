#ifndef PHOTO_H
#define PHOTO_H
#include "Arduino.h"
#include "motors.h"
#include "constants.h"
#include "MUX.h"
// #include <utility> // For std::pair

enum class Side {
    Left,
    Right,
    Front
};

struct PhotoData {
    bool is_on_line;          // Indicador de si se detectó una línea
    int correction_degree;    // Grado de corrección
};

class Photo {
public:
    Photo();
    // MUX left_mux_;
    // MUX right_mux_;
    // MUX front_mux_;
    // Photo(uint8_t signal_pin1, uint8_t mux_pin1_1, uint8_t mux_pin2_1, uint8_t mux_pin3_1,
    //     uint8_t signal_pin2, uint8_t mux_pin1_2, uint8_t mux_pin2_2, uint8_t mux_pin3_2,
    //     uint8_t signal_pin3, uint8_t mux_pin1_3, uint8_t mux_pin2_3, uint8_t mux_pin3_3);
    uint16_t ReadPhoto(Side side);
    uint16_t ReadPhotoWithMUX(Side side);
    bool CheckPhoto(Side side);
    PhotoData CheckPhotosOnField(Side side);
    uint16_t PhotoCalibrationOnLine(Side side);
    // std::pair<uint16_t, bool> GetPhotoData(Side side);

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

    static const int kMovingAverageSize = 10; // Tamaño del array circular
    uint16_t left_values[kMovingAverageSize] = {0}; // Array circular para el lado izquierdo
    uint16_t right_values[kMovingAverageSize] = {0}; // Array circular para el lado derecho
    uint16_t front_values[kMovingAverageSize] = {0}; // Array circular para el lado frontal
    int left_index = 0; // Índice actual para el lado izquierdo
    int right_index = 0; // Índice actual para el lado derecho
    int front_index = 0; // Índice actual para el lado frontal
    uint16_t calibration_line_left = 74; // Valor calibrado sobre la línea (izquierda)
    uint16_t calibration_line_right = 338; // Valor calibrado sobre la línea (derecha)
    uint16_t calibration_line_front = 51; // Valor calibrado sobre la línea (frontal)
};

#endif // PHOTO_H