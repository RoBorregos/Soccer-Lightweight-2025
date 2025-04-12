#include "Photo.h"
//---------------Transition from individual pins to MUX------------------ 
// On the ReadPhoto methods there is a line commented because the MUX is not integrated to the hardware yet
// The commented line is for the individual reading of the photoresistors

Photo::Photo()
// Photo::Photo(uint8_t mux_signal_pin1, uint8_t mux_pin1, uint8_t mux_pin2, uint8_t mux_pin3, uint8_t mux_signal_pin2, uint8_t mux_pin1_2, uint8_t mux_pin2_2, uint8_t mux_pin3_2, uint8_t mux_signal_pin3, uint8_t mux_pin1_3, uint8_t mux_pin2_3, uint8_t mux_pin3_3):
//     left_mux_(mux_signal_pin1, mux_pin1, mux_pin2, mux_pin3),
//     right_mux_(mux_signal_pin2, mux_pin1_2, mux_pin2_2, mux_pin3_2),
//     front_mux_(mux_signal_pin3, mux_pin1_3, mux_pin2_3, mux_pin3_3)
        {}

int Photo::ReadPhotoLeft() {
    int sum = 0;
    for (int i = 0; i < kPhotoLeftElements; i++) {
        photo_left[i] = analogRead(kPhotoLeftPins[i]);
        // photo_left[i] = left_MUX.readChannel(i);
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

int Photo::ReadPhoto(Side side) {
    int sum = 0;
    int* photo_array;
    int elements;

    switch (side) {
        case Side::Left:
            photo_array = photo_left;
            elements = kPhotoLeftElements;
            break;
        case Side::Right:
            photo_array = photo_right;
            elements = kPhotoRightElements;
            break;
        case Side::Front:
            photo_array = photo_front;
            elements = kPhotoFrontElements;
            break;
        default:
            return 0; // Invalid side
    }

    for (int i = 0; i < elements; i++) {
        photo_array[i] = analogRead(kPhotoPins[side][i]);
        sum += photo_array[i];
    }

    return sum / elements;
}

// uint16_t Photo::ReadPhotoWithMUX(Side side) {
//     int sum = 0;
//     int* photo_array;
//     int elements;
//     MUX* mux;

//     switch (side) {
//         case Side::Left:
//             photo_array = photo_left;
//             elements = kPhotoLeftElements;
//             this->mux = mux = &left_mux_;
//             break;
//         case Side::Right:
//             photo_array = photo_right;
//             elements = kPhotoRightElements;
//             this->mux = mux = &right_mux_;
//             break;
//         case Side::Front:
//             photo_array = photo_front;
//             elements = kPhotoFrontElements;
//             this->mux = mux = &front_mux_;
//             break;
//         default:
//             return 0; // Invalid side
//     }

//     for (int i = 0; i < elements; i++) {
//         photo_array[i] = analogRead(kPhotoPins[side][i]);
//         photo_array[i] = mux->readChannel(i);
//         sum += photo_array[i];
//     }

//     return sum / elements;
// }

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

// std is not avalable for arduino uno or mega boards.
// This implementation could be used when we add esp32 to our robot. 

// std::pair<uint16_t, bool> Photo::GetPhotoData(Side side) {
//     uint8_t sum = 0;
//     int* photo_array;
//     uint8_t elements;
//     MUX* mux;
//     uint16_t threshold;

//     switch (side) {
//         case Side::Left:
//             photo_array = photo_left;
//             elements = kPhotoLeftElements;
//             this->mux = mux = &left_mux_;
//             threshold = kPhotoTresholdLeft;
//             break;
//         case Side::Right:
//             photo_array = photo_right;
//             elements = kPhotoRightElements;
//             this->mux = mux = &right_mux_;
//             threshold = kPhotoTresholdRight;
//             break;
//         case Side::Front:
//             photo_array = photo_front;
//             elements = kPhotoFrontElements;
//             this->mux = mux = &front_mux_;
//             threshold = kPhotoTresholdFront;
//             break;
//         default:
//             return {0, false}; // Invalid side
//     }

//     for (int i = 0; i < elements; i++) {
//         photo_array[i] = mux->readChannel(i);
//         sum += photo_array[i];
//     }

//     uint16_t average = sum / elements;
//     bool exceeds_threshold = average > threshold;

//     return {average, exceeds_threshold};
// }

int Photo::PhotoCalibrationOnLine(Side side) {
    unsigned long start_time = millis(); // Registrar el tiempo de inicio
    unsigned long duration = 10000; // Duración de 10 segundos en milisegundos
    uint32_t sum = 0; // Suma acumulada de los valores leídos
    uint16_t count = 0; // Contador de lecturas

    while (millis() - start_time < duration) {
        // Leer el valor promedio del lado especificado
        uint16_t value = ReadPhoto(side);
        sum += value;
        count++;
        delay(30); // Esperar un poco entre lecturas
    }

    return sum / count;
}

bool Photo::CalibratePhotosOnField(Side side) {
    uint16_t value = ReadPhoto(side); // Leer el valor actual del lado especificado
    uint16_t* values_array;
    int* index;
    uint16_t calibration_line;

    // Seleccionar el array y el índice correspondiente al lado
    switch (side) {
        case Side::Left:
            values_array = left_values;
            index = &left_index;
            calibration_line = calibration_line_left;
            break;
        case Side::Right:
            values_array = right_values;
            index = &right_index;
            calibration_line = calibration_line_right;
            break;
        case Side::Front:
            values_array = front_values;
            index = &front_index;
            calibration_line = calibration_line_front;
            break;
        default:
            return false; // Lado inválido
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

    // Comparar el último valor con el promedio calibrado
    return value > (moving_average + calibration_line) / 2;
}