#ifndef __PSTWO_H
#define __PSTWO_H

#include "stm8s.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File��PS2��������
Author��pinggai    Version:1.0     Data:2015/05/16
Description: PS2��������
**********************************************************/	 
/*
pin18-->pc1-->DI
pin19-->pc2-->DO
pin20-->pc3-->CS
pin21-->pc4-->CLK



*/


#define DI (GPIO_PIN_1)
#define DO (GPIO_PIN_2)
#define CS (GPIO_PIN_3)
#define PS2_CLK (GPIO_PIN_4)
#define PS_PORT (GPIOC)


#define DI_IN GPIO_ReadInputPin(PS_PORT,DI)

#define DO_H GPIO_WriteHigh( PS_PORT,DO )        //����λ��
#define DO_L GPIO_WriteLow( PS_PORT,DO )        //����λ��

#define CS_H GPIO_WriteHigh( PS_PORT,CS )       //CS����
#define CS_L GPIO_WriteLow( PS_PORT,CS )       //CS����

#define CLK_H GPIO_WriteHigh( PS_PORT,PS2_CLK )      //ʱ������
#define CLK_L GPIO_WriteLow( PS_PORT,PS2_CLK )      //ʱ������









//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2         9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      26

//#define WHAMMY_BAR		8

//These are stick values
#define PSS_RX 5                //��ҡ��X������
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8





extern void Delay(uint16_t nCount);


extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;

void PS2_Init(void);
u8 PS2_RedLight(void);//�ж��Ƿ�Ϊ���ģʽ
void PS2_ReadData(void);
void PS2_Cmd(u8 CMD);		  //
u8 PS2_DataKey(void);		  //��ֵ��ȡ
u8 PS2_AnologData(u8 button); //�õ�һ��ҡ�˵�ģ����
void PS2_ClearData(void);	  //������ݻ�����


#endif





