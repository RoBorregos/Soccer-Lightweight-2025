#include "PixyCam.h"  

PixyCam::PixyCam() {}

void PixyCam::Init() {
  Wire.begin();
  pixy_.init();
}
 void PixyCam::updateData(){
  pixy_.ccc.getBlocks();
 }
 float PixyCam::angleGoal(float x){
  if (getSignature() == 1){
    const float FOV = 60.0;   
    const int x_center = 158; 
    const int x_max = 158;    

    float angle = ((x - x_center) / (float)x_max) * (FOV / 2);
    return angle;
  }
 }
 int PixyCam::numBlocks(){
   return pixy_.ccc.numBlocks;
 }
 int PixyCam::getSignature(){
   return pixy_.ccc.blocks[block].m_signature;
  }
  int PixyCam::getX(uint8_t block){
  return pixy_.ccc.blocks[block].m_x;
  }
  int PixyCam::getY(uint8_t block){
  return pixy_.ccc.blocks[block].m_y;

}
  int PixyCam::getWidth(uint8_t block){
  return pixy_.ccc.blocks[block].m_width;
  }

  int PixyCam::getHeight(uint8_t block){
  return pixy_.ccc.blocks[block].m_height;
  }
