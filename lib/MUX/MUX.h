#ifndef MUX_H
#define MUX_H

#include <Arduino.h>

class MUX {
public:
    MUX(uint8_t signalPin, uint8_t s0, uint8_t s1, uint8_t s2);
    void InitializeMUX();
    float readChannel(uint8_t channel);

private:
    uint8_t signal_pin_;
    uint8_t s0_, s1_, s2_;

};

#endif // MUX_H