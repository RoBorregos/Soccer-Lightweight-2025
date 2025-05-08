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
    Serial.begin(115200);
    Serial.setTimeout(100);
}

void IRRing::UpdateData() {
    if (Serial.available()) {
        String data = Serial.readStringUntil('\n');
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
double IRRing::GetRawAngle(){
    if(angle > 180){
        angle -= 360;
    }
    return angle;
}
double IRRing::GetStrength(){
    return filterStr.GetLowPass();
}

// We adjust the angle using different offsets based on how far the ball is from the front.
// Larger angles (ball behind) get a smaller correction using ballFollowOffsetBack,
// medium angles (ball to the side) use ballFollowOffsetSide,
// and smaller angles (ball in front) use ballFollowOffsetFront.
// This allows more precise control depending on the ball’s position.

double IRRing::GetAngle(float ballFollowOffsetBack, float ballFollowOffsetSide, float ballFollowOffsetFront){
    
    if(angle > 180){
        angle -= 360;
    }
    
    if (abs(angle) > 52){
        angle = angle * ballFollowOffsetBack;
    }
    else if (abs(angle) < 52 && abs(angle) > 25){
        angle = angle * ballFollowOffsetSide;
    }
    else if (abs(angle) < 25){
        angle = angle * ballFollowOffsetFront;
    }
    else {
        angle = angle;
    }

    if (angle > 180){
        angle = 180;
    }
    else if (angle < -180){
        angle = -180;
    }

    // Filtrar Valores
    if (angle > 0.05 || angle <= -0.05){
        lastBallAngle = angle; // 
    } else if (angle <= 0.05 || angle >= -0.05) {
        angle = lastBallAngle; // 
    }  
    return angle * -1;
    
}
//Para implementar el offset usando el PID, no sería necesario tener condicionales porque el PID se encarga de corregir el offset según el ángulo
// double IRRing::GetAngle(){
//     if (angle > 180){
//         angle -= 360;
//     }
//     return angle*-1;
// }
// double IRRing::GetAnglewithOffset(float offset){
//     angle = angle * ballFollowOffset;
    
//     return angle;
// }
//Se me ocurre tener dos funciones diferentes, porque para calcular el PID necesitamos el ángulo que ya está corregido para que este en valores de -180 a 180