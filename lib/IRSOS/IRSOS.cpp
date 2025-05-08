#include "IRSOS.h"
#include <Arduino.h>

void IRSOS::IRInit() {
    pinMode(LeftIRPin, INPUT);
    pinMode(RightIRPin, INPUT);
    pinMode(FrontIRPin, INPUT);
}

int IRSOS::getLeftIRSignal() {
    return digitalRead(LeftIRPin);
}
int IRSOS::getRightIRSignal() {
    return digitalRead(RightIRPin);
}
int IRSOS::getFrontIRSignal() {
    return digitalRead(FrontIRPin);
}