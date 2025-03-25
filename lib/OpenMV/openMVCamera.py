
import sensor
import time
import math
import time
import utime
import image
import sensor
import pyb
from pyb import UART
uart = UART(3, 115200, timeout_char=0)
treshold_yellowgoal=(42, 99, -33, 40, 10, 72)
treshold_bluegoal=(13, 80, 47, -36, -78, -14)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

clock=time.clock()
detected_goals=[]

def Init();
    pass
def updateData():
    global detected_goals
    detected_goals=[]
    img=sensor.snapshot()
    for color, tag in [(treshold_yellowgoal, 1), (treshold_bluegoal, 2)]:
        for blob in img.find_blobs([color], pixels_threshold=200, area_threshold=300, merge=True):
            goal = {
                'signature': tag,
                'x': blob.cx(),
                'y': blob.cy(),
                'width': blob.w(),
                'height': blob.h(),
                'angle': angleGoal(blob.cx()) 
            }
            detected_goals.append(goal)
            img.draw_rectangle(blob.rect(), color=(255, 255, 0))
            img.draw_cross(blob.cx(), blob.cy(), color=(255, 255, 0))

def angleGoal(x):
    FOV = 70.8  
    x_center = sensor.width() // 2  
    x_max = sensor.width() // 2  

    return ((x - x_center) / x_max) * (FOV / 2)

def numBlocks():
    return len(detected_goals)

def getSignature(block=0):
    if block < numBlocks():
        return detected_goals[block]['signature']
    return -1

def getX(block=0):
    if block < numBlocks():
        return detected_goals[block]['x']
    return -1

def getY(block=0):
    if block < numBlocks():
        return detected_goals[block]['y']
    return -1

def getWidth(block=0):
    if block < numBlocks():
        return detected_goals[block]['width']
    return -1

def getHeight(block=0):
    if block < numBlocks():
        return detected_goals[block]['height']
    return -1
