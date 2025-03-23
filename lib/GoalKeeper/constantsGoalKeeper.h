#ifndef CONSTANTS_GOALKEEPER_H
#define CONSTANTS_GOALKEEPER_H
#include <Arduino.h>

// Goalkeeper constants
static const uint8_t GOALKEEPER_MAX_SPEED = 150; // Maximum speed of the goalkeeper in m/s
static const uint8_t GOALKEEPER_MIN_SPEED = 0; // Minimum speed of the goalkeeper in m/s



enum GoalkeeperState {
    limits,
    moveWithoutBall,
    moveWithBall,
};

#endif // CONSTANTS_GOALKEEPER_H