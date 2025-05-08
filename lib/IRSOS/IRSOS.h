#ifndef IRSOS_H
#define IRSOS_H

#include <Arduino.h>
// #include <IRremote.h>

class IRSOS {
private:

    uint8_t LeftIRPin; // Pin for the IR receiver
    uint8_t RightIRPin; // Variable to store the received IR signal
    uint8_t FrontIRPin; // Variable to store the received IR signal
    // IRrecv irrecv; // IR receiver object
    // decode_results results; // To store the decoded IR signal

public:
    // Constructor: Initialize the IR receiver with the specified pin
    IRSOS(uint8_t LeftIRPin, uint8_t RightIRPin, uint8_t FrontIRPin) {}

    // Initialize the IR receiver
    void IRInit(); 
    void readSignal();
    
};

#endif // IRSOS_H