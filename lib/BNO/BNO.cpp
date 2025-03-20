
# include "Bno.h"


Bno::Bno()
{
  yaw = 0;
  target_yaw = 0;
  current_yaw = 0;
  isRightFlag=false;
}

void Bno::InitializeBNO()
{
Serial.println("Orientation Sensor Test"); Serial.println("");
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

void Bno::GetBNOData()
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

double Bno::GetYaw()
{
return yaw;
}
void Bno::setOffset(double off){
  offset=off;
}
bool Bno::GetisRight() {
  return isRightFlag;
}