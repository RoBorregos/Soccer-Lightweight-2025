#include "IRSOS.h"
#include <Arduino.h>

IRSOS::IRSOS(int pin) : irPin(pin) {}

void IRSOS::begin() {
    pinMode(irPin, INPUT);
}

int IRSOS::readSignal() {
    return digitalRead(irPin);
}