#include "PID.h"
#include "Arduino.h"
#include "constants.h"

PID::PID(double kp, double ki, double kd, double max_error)
    : kp_(kp), ki_(ki), kd_(kd), max_error_(max_error), last_error_(0), last_time_(millis()) {
        // Local variables
        delta_error = 0;
        error = 0;
        sum_error = 0;
    }

// Note that the sampling time for our PID controller is 20ms
double PID::Calculate(double setpoint, double input)
{
    unsigned long time = millis();

    // time difference since last calculation
    double delta_time = (time - last_time_) / 50.0;

    error = setpoint - input;
    sum_error += error * delta_time;
    delta_error = (error - last_error_) / delta_time;

    double proportional = kp_ * error;
    double integral = ki_ * sum_error;
    double derivative = kd_ * delta_error;
    // calculate the control signal using PID
    double control = (proportional) + (integral) + (derivative);

    // Serial.print("Error: ");
    // Serial.print(error);
    // Serial.print(" Kp: ");
    // Serial.print(proportional);
    // Serial.print(" Ki: ");
    // Serial.print(integral);
    // Serial.print(" Kd: ");
    // Serial.print(derivative);
    // Serial.print(" Output: ");
    // Serial.println(control);

    // update previous error and time
    last_error_ = error;
    last_time_ = time;

    return control;
}
