#include "PixyCam.h"  

PixyCam::PixyCam() {}

void PixyCam::Init(uint32_t communicationMode) {
  //Wire.begin();
  pixy_.init(communicationMode);
}

void PixyCam::updateData(){
  pixy_.ccc.getBlocks();
}

uint8_t PixyCam::numBlocks(){
   return pixy_.ccc.numBlocks;
}

uint8_t PixyCam::getSignature(){
   return pixy_.ccc.blocks[block].m_signature;
}

int PixyCam::getX(uint8_t block){
  return pixy_.ccc.blocks[block].m_x;
}

int PixyCam::getY(uint8_t block){
  return pixy_.ccc.blocks[block].m_y;
}

int PixyCam::getWidth(uint8_t block){
  width_values[width_index] = pixy_.ccc.blocks[block].m_width;
  width_index = (width_index + 1) % kMovingAverageSize; // Incrementar el índice circularmente

  float sum = 0;
  for (int i = 0; i < kMovingAverageSize; i++) {
      sum += width_values[i];
  }
  return sum / kMovingAverageSize;
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

TargetGoalData PixyCam::getTargetGoalData(uint8_t numberObjects, uint8_t targetSignature){
  for (int i = 0; i < numberObjects; i++){
    uint8_t signature = getSignature();
    if (signature == targetSignature){
      int x = getX(i);
      int y = getY(i);
      int width = getWidth(i);
      int height = getHeight(i);
      float cameraAngle = getGoalAngle(x);
      return {signature, x, y, width, height, cameraAngle};
    }
  }
}