/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
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

extern u16 speed_left;//����ٶȳ�ֵ
extern u16 speed_right;//�Ҳ��ٶȳ�ֵ

#endif /* __INCLUDE_H */