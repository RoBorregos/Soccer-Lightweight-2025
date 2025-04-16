import sensor #Controls OpenMV
import time  #Manage time and clock
import math #Mathematic calculations like angles
import pyb # Special library for pins, UARTs and LEDs in OpenMV
from pyb import UART
uart = UART(3, 115200, timeout_char=0)

## Define color ranges
THRESHOLD_YELLOW_GOAL=(42, 99, -33, 40, 10, 72)
THRESHOLD_BLUE_GOAL=(13, 80, 47, -36, -78, -14)
# Define OpenMV camera integrated LEDs
blue_led=pyb.LED(3)
red_led=pyb.LED(1)

sensor.reset() # Reset the camera
sensor.set_pixformat(sensor.RGB565)# Select the RGB color image format.
sensor.set_framesize(sensor.QVGA)# Image size 320x240
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

clock=time.clock()

def detect_goal(color,tag):
    max_area=0 # Stores the largest area encountered
    max_blob=None
    # Look for objects that match the given color.
    for blob in img.find_blobs([color],pixels_threshold=200, area_threshold=300, merge=True):
        #img.draw_rectangle(blob.rect(),color=(255,255,0))
        #img.draw_cross(blob.cx(),blob.cy(),color=(255,255,0))
        #img.draw_keypoints([(blob.cx(),blob.cy(),int(math.degrees(blob.rotation())))],size=20)
        red_led.on() #enciende led rojo si detecta objeto

        if blob.area()>max_area:
            max_area=blob.area()
            max_blob=blob
    if max_blob is not None:
        img.draw_rectangle(blob.rect(),color=(255,255,0))
        img.draw_cross(blob.cx(),blob.cy(),color=(255,255,0))
        img.draw_keypoints([(blob.cx(),blob.cy(),int(math.degrees(blob.rotation())))],size=20)
        center_x=max_blob.cx() #coordenada en x
        center_y=max_blob.cy() #coorden23ada en y
        width=max_blob.w() #ancho
        height=max_blob.h() #alto
        angle_from_center = (center_x - 160) * (60.0 / 320.0) * -1

        #Centro
        print(f"Centro: ({center_x},{center_y},Ancho:{width}, Alto:{height}, Ángulo:{angle_from_center}°)")
        #Manda los datos al microcontrolador
        uart.write(f"{tag},{center_x},{center_y},{width},{height},{angle_from_center}\n")
while True:
    clock.tick()
    img=sensor.snapshot()
    detect_goal(THRESHOLD_YELLOW_GOAL, 'y')#Detecta objetos amarillos
    detect_goal(THRESHOLD_BLUE_GOAL,'b')#Detecta objetos azules

