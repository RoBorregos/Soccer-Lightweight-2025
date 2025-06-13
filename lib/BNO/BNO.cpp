
# include "BNO.h"


Bno::Bno()
{
  yaw = 0;
}

void Bno::InitializeBNO()
{
Serial.println("Orientation Sensor Test"); Serial.println("");
  if(!bno.begin(OPERATION_MODE_IMUPLUS))
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

double Bno::GetBNOData()
{
imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
yaw = euler.x();

// Convert yaw to -180 to 180
if (yaw > 180)
{
  yaw = -1*(360 - yaw);
}
yaw = -yaw; // Change sign to match the robot motion function
return yaw;
}
