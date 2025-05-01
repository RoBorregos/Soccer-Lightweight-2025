#include "MUX.h"

MUX::MUX(uint8_t signalPin, uint8_t s0, uint8_t s1, uint8_t s2)
    : signal_pin_(signalPin), s0_(s0), s1_(s1), s2_(s2)  {}

void MUX::InitializeMUX() {
    pinMode(s0_, OUTPUT);
    pinMode(s1_, OUTPUT);
    pinMode(s2_, OUTPUT);
    pinMode(signal_pin_, INPUT);
}

float MUX::readChannel(uint8_t channel) {
    // configurar los pines de selección para escojer el canal que se va a leeer
    digitalWrite(s0_, bitRead(channel, 0));
    digitalWrite(s1_, bitRead(channel, 1));
    digitalWrite(s2_, bitRead(channel, 2));
    // delayMicroseconds(10); // Allow signals to settle
    // leer el canal seleccionado
    return analogRead(signal_pin_);
}