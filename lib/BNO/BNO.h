
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
    void InitializeBNO();
    void GetBNOData();
    double GetYaw();
    void setOffset(double off);
    bool GetisRight();
  
  private:
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
    double yaw;
    double target_yaw;
    double current_yaw;
    double offset;
    bool isRightFlag;


};

# endif
