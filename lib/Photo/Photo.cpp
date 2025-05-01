#include "Photo.h"
//---------------Transition from individual pins to MUX------------------ 
// On the ReadPhoto methods there is a line commented because the MUX is not integrated to the hardware yet
// The commented line is for the individual reading of the photoresistors

// Photo::Photo()
Photo::Photo(uint8_t signal_pin1, uint8_t mux_pin1_1, uint8_t mux_pin2_1, uint8_t mux_pin3_1,
            uint8_t signal_pin2, uint8_t mux_pin1_2, uint8_t mux_pin2_2, uint8_t mux_pin3_2,
            uint8_t signal_pin3, uint8_t mux_pin1_3, uint8_t mux_pin2_3, uint8_t mux_pin3_3) :
    left_mux_(signal_pin1, mux_pin1_1, mux_pin2_1, mux_pin3_1),
    right_mux_(signal_pin2, mux_pin1_2, mux_pin2_2, mux_pin3_2),
    front_mux_(signal_pin3, mux_pin1_3, mux_pin2_3, mux_pin3_3) 
        {}

// uint16_t Photo::ReadPhoto(Side side) { // Este método devuelve el promedio de los valores leídos
//     int sum = 0;
//     uint16_t* photo_array;
//     int elements;
//     const uint8_t* pins;

//     switch (side) {
//         case Side::Left:
//             photo_array = photo_left;
//             elements = kPhotoLeftElements;
//             pins = kPhotoLeftPins;
//             break;
//         case Side::Right:
//             photo_array = photo_right;
//             elements = kPhotoRightElements;
//             pins = kPhotoRightPins;
//             break;
//         case Side::Front:
//             photo_array = photo_front;
//             elements = kPhotoFrontElements;
//             pins = kPhotoFrontPins;
//             break;
//         default:
//             return 0; // Invalid side
//     }

//     for (int i = 0; i < elements; i++) {
//         photo_array[i] = analogRead(pins[i]);
//         sum += photo_array[i];
//     }

//     return sum / elements;
// }

uint16_t Photo::ReadPhotoWithMUX(Side side) {
    int sum = 0;
    uint16_t* photo_array;
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
    // int average = ReadPhotoWithMUX(side);
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

uint16_t Photo::PhotoCalibrationOnLine(Side side) {
    unsigned long start_time = millis(); // Registrar el tiempo de inicio
    unsigned long duration = 10000; // Duración de 10 segundos en milisegundos
    uint32_t sum = 0; // Suma acumulada de los valores leídos
    uint16_t count = 0; // Contador de lecturas

    while (millis() - start_time < duration) {
        // Leer el valor promedio del lado especificado
        uint16_t value = ReadPhotoWithMUX(side);
        sum += value;
        count++;
        Serial.println(count);
        delay(30); // Esperar un poco entre lecturas
    }

    return sum / count;
}

PhotoData Photo::CheckPhotosOnField(Side side) {
    uint16_t value = ReadPhotoWithMUX(side); // Leer el valor actual del lado especificado
    uint16_t* values_array;
    int* index;
    uint16_t calibration_line;
    int correctionDegree;

    // Seleccionar el array y el índice correspondiente al lado
    switch (side) {
        case Side::Left:
            values_array = left_values;
            index = &left_index;
            calibration_line = kPhotoTresholdLeft;
            correctionDegree = -90;
            break;
        case Side::Right:
            values_array = right_values;
            index = &right_index;
            calibration_line = kPhotoTresholdRight;
            correctionDegree = 90;
            break;
        case Side::Front:
            values_array = front_values;
            index = &front_index;
            calibration_line = kPhotoTresholdFront;
            correctionDegree = 180;
            break;
    }

    // Actualizar el array circular
    values_array[*index] = value;
    *index = (*index + 1) % kMovingAverageSize; // Incrementar el índice circularmente

    // Calcular el promedio móvil
    uint32_t sum = 0;
    for (int i = 0; i < kMovingAverageSize; i++) {
        sum += values_array[i];
    }
    uint16_t moving_average = sum / kMovingAverageSize;
    bool is_on_line = value > (moving_average + calibration_line) / 2;
    return {is_on_line, correctionDegree};
}