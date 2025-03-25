

#ifndef ARDUINO_PID_H
#define ARDUINO_PID_H
#include <Arduino.h>

class PID {
    public:
        PID() {};
        PID(double kp, double ki, double kd, double max_error);
        double Calculate(double setpoint, double input);
        void SetR(bool r);
        bool getR();
        void setKp(double P);
        double getKp();
        void setMinToMove(int min);
        int getMinToMove();
        void setAngle(double angle);
        void setki(double ki){ki_=ki;};
        void setkd(double kd){kd_=kd;};
        void setkp(double kp){kp_=kp;};
        void setMaxError(double max_error){max_error_=max_error;};
        double getki(){return ki_;};
        double getkd(){return kd_;};
        double getkp(){return kp_;};
        double getMaxError(){return max_error_;};


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
