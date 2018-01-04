#ifndef __PS2_H
#define __PS2_H

#include "stm32f10x.h"

#define uchar unsigned char
#define uint unsigned int
#define GPIOA_ODR_A  (GPIOA_BASE+0x0C)
#define GPIOA_IDR_A  (GPIOA_BASE+0x08)
#define GPIOB_ODR_A  (GPIOB_BASE+0x0C)
#define GPIOB_IDR_A  (GPIOB_BASE+0x08)
#define GPIOC_ODR_A  (GPIOC_BASE+0x0C)
#define GPIOC_IDR_A  (GPIOC_BASE+0x08)
#define GPIOD_ODR_A  (GPIOD_BASE+0x0C)
#define GPIOD_IDR_A  (GPIOD_BASE+0x08)
#define GPIOE_ODR_A  (GPIOE_BASE+0x0C)
#define GPIOE_IDR_A  (GPIOE_BASE+0x08)
#define BitBand(Addr,BitNum)    *((volatile unsigned long *)((Addr&0xF0000000)+0x2000000+((Addr&0xfffff)<<5)+(BitNum<<2)))

#define PAout(n)   BitBand(GPIOA_ODR_A,n)
#define PAin(n)    BitBand(GPIOA_IDR_A,n)
#define PBout(n)   BitBand(GPIOB_ODR_A,n)
#define PBin(n)    BitBand(GPIOB_IDR_A,n)
#define PCout(n)   BitBand(GPIOC_ODR_A,n)
#define PCin(n)    BitBand(GPIOC_IDR_A,n)
#define PDout(n)   BitBand(GPIOD_ODR_A,n)
#define PDin(n)    BitBand(GPIOD_IDR_A,n)
#define PEout(n)   BitBand(GPIOE_ODR_A,n)
#define PEin(n)    BitBand(GPIOE_IDR_A,n)

#define DI   PAin(8)           // DI输入

#define DO_H PAout(11)=1        //命令位高
#define DO_L PAout(11)=0        //命令位低

#define CS_H PBout(10)=1       //CS拉高
#define CS_L PBout(10)=0       //CS拉低

#define CLK_H PBout(11)=1      //时钟拉高
#define CLK_L PBout(11)=0      //时钟拉低


//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
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
#define PSS_RX 5                //右摇杆X轴数据
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8



extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;

void PS2_Init(void);
u8 PS2_RedLight(void);//判断是否为红灯模式
void PS2_ReadData(void);
void PS2_Cmd(u8 CMD);		  //
u8 PS2_DataKey(void);		  //键值读取
u8 PS2_AnologData(u8 button); //得到一个摇杆的模拟量
void PS2_ClearData(void);	  //清除数据缓冲区

#endif





