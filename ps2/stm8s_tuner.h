#ifndef __STM8S_TUNER_H
#define __STM8S_TUNER_H


#include "stm8s.h"
#include "stm8s_gpio.h"

#define TUNER_SPI_PORT  (GPIOB)
#define BUTTON (GPIOC)


#define CtrlData  (GPIO_PIN_2)
#define CtrlClk  (GPIO_PIN_1)
#define CtrlEn  (GPIO_PIN_0)
#define ButtonBit (GPIO_PIN_4)
#define CtrlEn2 (GPIO_PIN_3)



#define SET_CE_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlEn, GPIO_MODE_OUT_PP_LOW_FAST );}//Output push-pull, low level, 10MHz 

#define SET_CE_OUT_2()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlEn2, GPIO_MODE_OUT_PP_LOW_FAST );}//Output push-pull, low level, 10MHz    TUNER 2 

#define SET_SCL_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlClk, GPIO_MODE_OUT_PP_LOW_FAST );}

#define SET_SDA_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlData, GPIO_MODE_OUT_PP_LOW_FAST );}

extern void InitTunerSpi();
extern void Write_Tuner2400_Reg(uint16_t,uint16_t);
extern void Write_Tuner700_Reg(uint16_t,uint16_t);


extern void SET_PIN_HIGH(GPIO_Pin_TypeDef);
extern void SET_PIN_LOW(GPIO_Pin_TypeDef);




#endif





