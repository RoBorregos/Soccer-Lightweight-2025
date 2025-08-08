#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(uint8_t triggerPin, uint8_t echoPin) 
    : triggerPin(triggerPin), echoPin(echoPin) {
}

void Ultrasonic::UltrasonicInit() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float Ultrasonic::getDistanceY() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(1);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10); // Send a 10 microsecond HIGH pulse
    digitalWrite(triggerPin, LOW);

    // Read the echo time
    float signal = pulseIn(echoPin, HIGH, 30000); // Wait up to 30 ms (for 5 meters)
    float distanceY = signal * 0.0343 / 2; // Convert time to distance in cm

    distance_y_values[y_index] = distanceY;
    y_index = (y_index + 1) % kMovingAverageSize; // Increase the index circularly

    // Calculate the moving average
    float sum = 0;
    for (int i = 0; i < kMovingAverageSize; i++) {
        sum += distance_y_values[i];
    }
    return sum / kMovingAverageSize;
}

float Ultrasonic::getDistanceX(float cameraAngle, float distanceY) {
    float distanceX = distanceY * tan(cameraAngle * (PI / 180.0));
    distance_x_values[x_index] = distanceX;
    x_index = (x_index + 1) % kMovingAverageSize; // Increase the index circularly

    // Calculate the moving average
    float sum = 0;
    for (int i = 0; i < kMovingAverageSize; i++) {
        sum += distance_x_values[i];
    }
    return sum / kMovingAverageSize;
}

  