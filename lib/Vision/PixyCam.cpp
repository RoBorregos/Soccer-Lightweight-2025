#include "PixyCam.h"  

PixyCam::PixyCam() {}

void PixyCam::Init() {
  Wire.begin();
  pixy_.init();
}
std::vector<GoalData> PixyCam::DetectGoals() {
  pixy_.ccc.getBlocks();
  std::vector<GoalData> detectedgoals;

  if (pixy_.ccc.numBlocks > 0) {
    for (int i = 0; i < pixy_.ccc.numBlocks; i++) {
      GoalData goal;
      goal.signature=pixy_.ccc.blocks[i].m_signature;
      goal.x=pixy_.ccc.blocks[i].m_x;
      goal.y=pixy_.ccc.blocks[i].m_y;
      goal.width=pixy_.ccc.blocks[i].m_width;
      goal.height=pixy_.ccc.blocks[i].m_height;

      goal.angle=angleGoal(goal.x);
      detectedgoals.push_back(goal);
      }
    }
    return detectedgoals;
 }
 float PixyCam::angleGoal(float x){
    const float FOV = 60.0;   
   const int x_center = 158; 
    const int x_max = 158;    

    float angle = ((x - x_center) / (float)x_max) * (FOV / 2);
    return angle;
 }
