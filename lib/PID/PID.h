

#ifndef ARDUINO_PID_H
#define ARDUINO_PID_H
#include <Arduino.h>

class PID {
    public:
        PID(double kp, double ki, double kd, double max_error);
        double Calculate(double setpoint, double input);
        void SetR(bool r);
        bool getR();
        void setKp(double P);
        double getKp();
        void setMinToMove(int min);
        int getMinToMove();
        void setAngle(double angle);


    private:
        double kp_;
        double ki_;
        double kd_;
        double max_error_;
        double last_error_;
        double last_time_;
        bool r=false;
        int minToMove=60;
        double angle=100;
        
};

#endif
