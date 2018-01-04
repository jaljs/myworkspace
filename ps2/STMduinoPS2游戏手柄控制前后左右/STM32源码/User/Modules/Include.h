/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/
#ifndef __INCLUDE_H
#define __INCLUDE_H

#include "stm32f10x.h"
#include "Interrupt.h"
#include "SysTick.h"
#include "usart1.h"
#include "Timer.h"
#include "function.h"
#include "i2c_eeprom.h"
#include "Config.h"
#include "Motor.h"
#include "Ultrasonic.h"
#include "Init.h"
#include "PS2.h"
#include <stdarg.h>
#include <math.h>
#include <stdio.h>


extern u8 adjust;
extern u8 buffer[3];
extern u8 rec_flag;
extern u8 PS2_Key;

extern u16 speed_left;//左侧速度初值
extern u16 speed_right;//右侧速度初值

#endif /* __INCLUDE_H */