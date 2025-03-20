#include "PixyCam.h"  

PixyCam::PixyCam() {}

void PixyCam::init() {
  Wire.begin();
  pixy.init();
}
void PixyCam::detectGoals() {
  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks > 0) {
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      Serial.print("Signature: ");
      Serial.print(pixy.ccc.blocks[i].m_signature);
      Serial.print("x");
      Serial.print(pixy.ccc.blocks[i].m_x);
      Serial.print(" y");
      Serial.print(pixy.ccc.blocks[i].m_y);
      Serial.print(" width");
      Serial.print(pixy.ccc.blocks[i].m_width);
      Serial.print(" height");
      Serial.printl(pixy.ccc.blocks[i].m_height);

      if (pixy.ccc.blocks[i].m_signature == 1) {
        Serial.println(" - Goal 1 Yellow");
      } else if (pixy.ccc.blocks[i].m_signature == 2) {
        Serial.println(" - Goal 2 Blue");
      }
    }

  }
}