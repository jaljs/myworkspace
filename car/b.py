#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BOARD)

INT1 = 18
INT2 = 16
INT3 = 13 
INT4 = 15


GPIO.setup(INT1,GPIO.OUT)
GPIO.setup(INT2,GPIO.OUT)
GPIO.setup(INT3,GPIO.OUT)
GPIO.setup(INT4,GPIO.OUT)



GPIO.output(INT1,0)
GPIO.output(INT2,1)
GPIO.output(INT3,0)
GPIO.output(INT4,1)
time.sleep(0.1)
GPIO.cleanup()





