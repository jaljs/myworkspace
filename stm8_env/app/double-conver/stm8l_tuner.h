#ifndef __STM8L_TUNER_H
#define __STM8L_TUNER_H


#include "stm8l15x.h"
#include "stm8l15x_gpio.h"

#define TUNER_SPI_PORT  (GPIOC)
//#define BUTTON (GPIOC)


#define CtrlData  (GPIO_Pin_1)
#define CtrlClk  (GPIO_Pin_2)
#define CtrlEn  (GPIO_Pin_3)
#define ButtonBit (GPIO_Pin_4)
#define CtrlEn2 (GPIO_Pin_0)



#define SET_CE_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlEn, GPIO_Mode_Out_PP_Low_Fast );}//Output push-pull, low level, 10MHz 

#define SET_CE_OUT_2()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlEn2, GPIO_Mode_Out_PP_Low_Fast );}//Output push-pull, low level, 10MHz    TUNER 2 

#define SET_SCL_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlClk, GPIO_Mode_Out_PP_Low_Fast );}

#define SET_SDA_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlData, GPIO_Mode_Out_PP_Low_Fast );}

void InitTunerSpi();
void Write_Tuner2400_Reg(uint16_t,uint16_t);
void Write_Tuner700_Reg(uint16_t,uint16_t);
void SET_PIN_HIGH(GPIO_Pin_TypeDef);
void SET_PIN_LOW(GPIO_Pin_TypeDef);




#endif





