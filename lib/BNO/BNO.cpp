
# include "Bno.h"


Bno::Bno()
{
  yaw = 0;
  target_yaw = 0;
  current_yaw = 0;
}

void Bno::bno_begin()
{
Serial.println("Orientation Sensor Test"); Serial.println("");
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

void Bno::getEuler()
{
imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
yaw = euler.x();
current_yaw = yaw;

// Convert yaw to -180 to 180
if (yaw > 180)
{
yaw = -1*(360 - yaw);
}
Serial.print("X: ");
Serial.print(yaw);
Serial.println("");
}

double Bno::getYaw()
{
return yaw;
}
