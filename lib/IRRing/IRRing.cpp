#include "IRRing.h"  
#include <Arduino.h>
#include <SingleEMAFilterLib.h>

SingleEMAFilter<double> filterAngle(0.6);
SingleEMAFilter<double> filterStr(0.6);

IRRing::IRRing():
angle(0),
strength(0),
offset(0),
current_time(nullptr),
last_time(0)
{

}
void IRRing::init(unsigned long*current_time)
{
    this->current_time=current_time;
    Serial1.begin(115200);
    Serial1.setTimeout(100);
}

void IRRing::UpdateData() {
    if (Serial1.available()) {
        String data = Serial1.readStringUntil('\n');
        data.trim();  
        
        // Data is expected to be received in the format: 
        // “a 0.1” for angle or “r 10” for force.
        
        if (data.length() > 2) {  
            char type = data[0];
            String valueStr = data.substring(2);  
            if (valueStr.length() > 0) {  
                double value = valueStr.toFloat();  
                if (type == 'a') {
                    angle = value + offset;
                    filterAngle.AddValue(angle);
                } else if (type == 'r') {
                    strength = value;
                    filterStr.AddValue(strength);
                }
            }
        }
    }
    last_time = *current_time;
}

void IRRing::SetOffset(double offset){
    this->offset=offset;
}
double IRRing::GetRowAngle(){
    return angle;
}
double IRRing::GetStrength(){
    return filterStr.GetLowPass();
}
double IRRing::GetAngle(double rowAngle){
    if(rowAngle>180){
        rowAngle-=360;
    }
    return rowAngle;
    
}
