
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

blue_led=pyb.LED(3)
red_led=pyb.LED(1)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

clock=time.clock()
uart=UART(3,9600,timeout_char=0)

def detect_goal(color,tag):
    max_area=0
    max_blob=None
    
    for blob in img.find_blobs([color],pixels_threshold=200, area_threshold=300, merge=True):
        img.draw_rectangle(blob.rect(),color=(255,255,0))
        img.draw_cross(blob.cx(),blob.cy(),color=(255,255,0))
        img.draw_keypoints([(blob.cx(),blob.cy(),int(math.degrees(blob.rotation())))],size=20)
        red_led.on() #enciende led rojo si detecta objeto
        
        if blob.area()>max_area:
            max_area=blob.area()
            max_blob=blob
    if max_blob is not None:
        center_x=max_blob.cx()
        center_y=max_blob.cy()
        width=max_blob.w()
        height=max_blob.h()
        angle=math.degrees(max_blob.rotation())
        #Centro 
        print(f"Centro: ({center_x},{center_y},Ancho:{width}, Alto:{height}, Ángulo:{angle}°")
        
        uart.write(f"{tag},{center_x},{center_y},{width},{height},{angle}\n")
    while True:
        clock.tick()
        img=sensor.snapshot()
        detect_goal(treshold_yellowgoal, 'y')#Detecta objetos amarillos
        detect_goal(treshold_bluegoal,'b')#Detecta objetos azules

