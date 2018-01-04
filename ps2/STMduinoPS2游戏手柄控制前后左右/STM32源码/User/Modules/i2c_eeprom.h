/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/
#ifndef __I2C_EEPROM_H
#define __I2C_EEPROM_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
/* Exported macro ------------------------------------------------------------*/
#define ADDR_24CXX        0xA0
#define SCLH         GPIOB->BSRR = GPIO_Pin_6
#define SCLL         GPIOB->BRR  = GPIO_Pin_6 
   
#define SDAH         GPIOB->BSRR = GPIO_Pin_7
#define SDAL         GPIOB->BRR  = GPIO_Pin_7
#define SCLread      GPIOB->IDR  & GPIO_Pin_6
#define SDAread      GPIOB->IDR  & GPIO_Pin_7
 
/* Exported functions ------------------------------------------------------- */
void I2C_EEPROM_Init(void);
void DelayMs(uint16_t ms);
u8 I2C_EEPROM_BufferWrite(u8 *psrc_data,u8 adr,u8 nbyte);
u8 I2C_EEPROM_BufferRead(u8*pdin_data,u8 adr,u8 nbyte);
u8 I2C_EEPROM_WriteByte(u8 SendByte, u8 WriteAddress);
u8 I2C_EEPROM_ReadByte( u8 ReadAddress);

#endif /* __I2C_EEPROM_H */

