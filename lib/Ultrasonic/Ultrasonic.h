#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <Arduino.h>

class Ultrasonic {
public:
    Ultrasonic(uint8_t triggerPin, uint8_t echoPin);
    void UltrasonicInit();
    float getDistanceY(); // Returns distance in centimeters
    float getDistanceX(float cameraAngle, float distanceY); // Returns distance in centimeters
    void updateMovingAverage(float newMeasurement);
    float getMovingAverage(); // Returns the moving average of the last 10 measurements

private:
    uint8_t triggerPin;
    uint8_t echoPin;

    static const int kMovingAverageSize = 5; // Tamaño del array circular
    float distance_x_values[kMovingAverageSize] = {0}; // Array circular para el lado izquierdo
    uint16_t distance_y_values[kMovingAverageSize] = {0}; // Array circular para el lado derecho
    int x_index = 0; // Índice actual
    int y_index = 0; // Índice actual
};

#endif 