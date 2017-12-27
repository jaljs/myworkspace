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



GPIO.output(INT1,GPIO.HIGH)
GPIO.output(INT2,GPIO.LOW)
GPIO.output(INT3,GPIO.HIGH)
GPIO.output(INT4,GPIO.LOW)
time.sleep(0.1)
GPIO.cleanup()





