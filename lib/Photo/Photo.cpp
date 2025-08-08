#include "Photo.h"

// Photo::Photo() // Used for functions without MUX
Photo::Photo(uint8_t signal_pin1, uint8_t mux_pin1_1, uint8_t mux_pin2_1, uint8_t mux_pin3_1,
            uint8_t signal_pin2, uint8_t mux_pin1_2, uint8_t mux_pin2_2, uint8_t mux_pin3_2,
            uint8_t signal_pin3, uint8_t mux_pin1_3, uint8_t mux_pin2_3, uint8_t mux_pin3_3) :
    left_mux_(signal_pin1, mux_pin1_1, mux_pin2_1, mux_pin3_1),
    right_mux_(signal_pin2, mux_pin1_2, mux_pin2_2, mux_pin3_2),
    front_mux_(signal_pin3, mux_pin1_3, mux_pin2_3, mux_pin3_3) 
        {}

// uint16_t Photo::ReadPhoto(Side side) { // This function is to read the values of the phototransistors without MUX
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

uint16_t Photo::PhotoCalibrationOnLine(Side side) {
    unsigned long start_time = millis(); // Register the start time
    unsigned long duration = 10000; // Duration of 10 seconds in milliseconds
    uint32_t sum = 0; // Accumulated sum of the read values
    uint16_t count = 0; // Readings counter

    while (millis() - start_time < duration) {
        // Read the value from the specified side
        uint16_t value = ReadPhotoWithMUX(side);
        sum += value;
        count++;
        Serial.println(count);
        delay(30); // Wait a bit between readings
    }

    return sum / count;
}

PhotoData Photo::CheckPhotosOnField(Side side) {
    uint16_t value = ReadPhotoWithMUX(side); // Read the current value from the specified side
    uint16_t* values_array;
    int* index;
    uint16_t calibration_line;
    int correctionDegree;

    // Select the array and the corresponding index for the side
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

    // Update the circular array
    values_array[*index] = value;
    *index = (*index + 1) % kMovingAverageSize; // Increment the index circularly

    // Calculate the moving average
    uint32_t sum = 0;
    for (int i = 0; i < kMovingAverageSize; i++) {
        sum += values_array[i];
    }
    uint16_t moving_average = sum / kMovingAverageSize;
    bool is_on_line = value > ((moving_average + calibration_line) / 2);  
    // Serial.print("  ");
    // Serial.print("Moving average: ");
    // Serial.print(moving_average);
    // Serial.print("  Value: ");
    // Serial.print(value);
    // Serial.print("  Calculation: ");
    // Serial.print(calibration_line * 0.8);
    // Serial.print("  Is on line: ");
    // Serial.println(is_on_line);

    return {is_on_line, correctionDegree};
}