#!/usr/bin/env python
# encoding: utf-8


import RPi.GPIO as GPIO

import time


DI = 3	#out
DO = 5	#
CS = 7
PS2_CLK = 10

t=0.000005  # (read clk >2KHz)

Handkey =0 
Comd=[0x01,0x42]
Data=[0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00]



PSB_SELECT      =1
PSB_L3          =2
PSB_R3          =3
PSB_START       =4
PSB_PAD_UP      =5
PSB_PAD_RIGHT   =6
PSB_PAD_DOWN    =7
PSB_PAD_LEFT    =8
PSB_L2         =9
PSB_R2          =10
PSB_L1          =11
PSB_R1          =12
PSB_GREEN       =13
PSB_RED         =14
PSB_BLUE        =15
PSB_PINK        =16
PSB_TRIANGLE    =13
PSB_CIRCLE      =14
PSB_CROSS       =15
PSB_SQUARE      =26




PSS_RX =5              
PSS_RY =6
PSS_LX =7
PSS_LY =8


class pstwo():
	def __init__(self):
		GPIO.setwarnings(False)
		GPIO.setmode(GPIO.BOARD)

		GPIO.setup(DI,GPIO.IN)
		GPIO.setup(DO,GPIO.OUT,initial=GPIO.LOW)
		GPIO.setup(CS,GPIO.OUT,initial=GPIO.HIGH)
		GPIO.setup(PS2_CLK,GPIO.OUT,initial=GPIO.HIGH)


	def __del__(self):
		GPIO.cleanup(DI,DO ,CS ,PS2_CLK)

	def PS2_Cmd(self,CMD):
		ref=0x01
		Data[1] = 0
		for ref in range(1,9):
			if (1<<(ref-1))&CMD:
				GPIO.output(DO,GPIO.HIGH)
			else:
				GPIO.output(DO,GPIO.LOW)

			GPIO.output(PS2_CLK,GPIO.HIGH)
			time.sleep(t)
			GPIO.output(PS2_CLK,GPIO.LOW)
			time.sleep(t)

			if GPIO.input(DI):
				Data[1]=(1<<(ref-1))|Data[1]
			#	print ref,"ref --->  high" 

			time.sleep(t)
		#	print "ref--->",ref,"ps2_cmd--->Data[1]   ref|data",Data[1],ref|Data[1]
		GPIO.output(PS2_CLK,GPIO.HIGH)
		time.sleep(t)


	def PS2_RedLight(self):
		GPIO.output(CS,GPIO.LOW)
		time.sleep(t)
		self.PS2_Cmd(Comd[0])
		print "comnd[0]--->",Comd[0]
		self.PS2_Cmd(Comd[1])
		print "comnd[1]--->",Comd[1]
		GPIO.output(CS,GPIO.HIGH)
		time.sleep(t)
		print "DATA[1]--->",hex(Data[1])

		if Data[1]==0x73:
			return 0
		else:
			return 1


	def PS2_ReadData(self):
		byte = 0
		ref=0x01
		GPIO.output(CS,GPIO.LOW)
		self.PS2_Cmd(Comd[0])
		self.PS2_Cmd(Comd[1])

		for byte in range(2,9):
		#	print "byte-->",byte
			for ref in range(1,9):
				GPIO.output(PS2_CLK,GPIO.HIGH)
				time.sleep(t)
				GPIO.output(PS2_CLK,GPIO.LOW)
				time.sleep(t)
			#	print "ref-------->",ref
				if GPIO.input(DI):
					Data[byte] = (1<<(ref-1))|Data[byte]
				time.sleep(t)

			time.sleep(t)
			GPIO.output(PS2_CLK,GPIO.HIGH)


		print "sp2 readdata data1--->",hex(Data[1])

		GPIO.output(CS,GPIO.HIGH)
		time.sleep(t)



if __name__ == '__main__':
	print "hello world"

	sp2 = pstwo()
	print "init off"
	#sp2.PS2_RedLight()

	sp2.PS2_ReadData()
	print "end"
































	
