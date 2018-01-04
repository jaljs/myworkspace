#include "led.h"

/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：LED驱动代码
Author：pinggai    Version:1.0     Data:2015/05/06
Description: Balance-STM32 LED驱动代码
**********************************************************/	   

//初始化PD2为输出口.并使端口时钟		    
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<5;    //使能PORTD时钟	 
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2推挽输出
	GPIOD->ODR|=1<<2;      //PD.2输出高 
}




