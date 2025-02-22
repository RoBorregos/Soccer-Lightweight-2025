
# ifndef Bno_h
# define Bno_h

# include <Arduino.h>
# include <Wire.h>
# include <Adafruit_Sensor.h>
# include <Adafruit_BNO055.h>

class Bno
{
  public:
    Bno();
    void bno_begin();
    void getEuler();
    double getYaw();
  
  private:
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
    double yaw;
    double target_yaw;
    double current_yaw;

};

# endif
