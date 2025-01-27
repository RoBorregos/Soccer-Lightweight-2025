#include "Motors.h"  
#include "Arduino.h"
#include "constants.h"

Motors::Motors(int speed1, int in1_1, int in2_1, int speed2, uint8_t in1_2, int in2_2, uint8_t speed3, uint8_t in1_3, uint8_t in2_3, uint8_t speed4, uint8_t in1_4, uint8_t in2_4) 
: motor1(speed1, in1_1, in2_1),
  motor2(speed2, in1_2, in2_2),
  motor3(speed3, in1_3, in2_3),
  motor4(speed4, in1_4, in2_4)
{};
