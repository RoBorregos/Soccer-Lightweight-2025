#include "PixyCam.h"  

PixyCam::PixyCam() {}

void PixyCam::Init(uint32_t communicationMode) {
  //Wire.begin();
  pixy_.init(communicationMode);
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

float PixyCam::getGoalAngle(int x){
  float angle = (x-160)*(60.0/320.0)*-1;
  angle_values[angle_index] = angle;
  angle_index = (angle_index + 1) % kMovingAverageSize; // Incrementar el índice circularmente

  // Calcular el promedio móvil
  float sum = 0;
  for (int i = 0; i < kMovingAverageSize; i++) {
      sum += angle_values[i];
  }
  return sum / kMovingAverageSize;
}