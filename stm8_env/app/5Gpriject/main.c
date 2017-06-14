#include "stm8l15x.h"
#include "stm8l15x_gpio.h"

#define TUNER_SPI_PORT  (GPIOC)
#define CtrlEn  (GPIO_Pin_2)
#define CtrlClk  (GPIO_Pin_1)
#define CtrlData  (GPIO_Pin_0)



#define SET_CE_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlEn, GPIO_Mode_Out_PP_Low_Fast );}//Output push-pull, low level, 10MHz 

#define SET_SCL_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlClk, GPIO_Mode_Out_OD_Low_Fast );}

#define SET_SDA_OUT()	{GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlData, GPIO_Mode_Out_OD_Low_Fast );}


void Delay(uint16_t nCount);
/* set gpio port statue */



void SET_PIN_HIGH(GPIO_Pin_TypeDef G)
{
	GPIO_WriteBit(TUNER_SPI_PORT,G,SET);
}


void SET_PIN_LOW(GPIO_Pin_TypeDef G)
{
	GPIO_WriteBit(TUNER_SPI_PORT,G,RESET);
}


void InIt_GPIO()
{
	SET_CE_OUT();
	SET_SCL_OUT();
	SET_SDA_OUT();

	SET_PIN_LOW(CtrlClk);
	SET_PIN_LOW(CtrlData);
	SET_PIN_LOW(CtrlEn);

}



void Write_Tuner_Reg(uint16_t REG_ADD,uint16_t REG_DATA)
{
	uint16_t i;
	uint16_t delay_i;
	uint16_t BafferData=(uint16_t)0x0000;
	uint16_t BafferSetData=(uint16_t)0x0000;//SDA data 
	uint16_t testbuffer=0x5555;
	
	BafferData=(uint16_t)REG_ADD|(uint16_t)0x0000;
	BafferData=BafferData<<11;
	BafferSetData=BafferSetData|BafferData;
	
	BafferData=(uint16_t)REG_DATA|(uint16_t)0x0000;
	BafferData=BafferData<<3;
	BafferSetData=BafferSetData|BafferData;//bit15~bit3 is the spi sda 
	

	
	
	
	SET_PIN_HIGH(CtrlClk);		  
		Delay(0x00FF);
		Delay(0x00FF);
		SET_PIN_LOW(CtrlClk);
	
	SET_PIN_HIGH(CtrlEn);//SET en high
	
	
	
	for( i=1;i<=15;i++)
	{
		//DATA CONTROL
		Delay(0x00FF);
		
		if(((uint16_t)BafferSetData&(uint16_t)0x8000)==(uint16_t)0x0000)
		{
			SET_PIN_LOW(CtrlData);
		}
		else
		{
			SET_PIN_HIGH(CtrlData);
		}
		Delay(0x00FF);
		
		
		//CLOCK CONTROL
	
		SET_PIN_HIGH(CtrlClk);		  
		Delay(0x00FF);
		Delay(0x00FF);
		SET_PIN_LOW(CtrlClk);
		BafferSetData=BafferSetData<<1;
		if(i==13)
			SET_PIN_LOW(CtrlEn);//SET en LOW
	}
	
	
}


void main(void)
{

Delay(0xFFFF);
Delay(0xFFFF);
Delay(0xFFFF);
Delay(0xFFFF);

InIt_GPIO();
Delay(0xFFFF);




Write_Tuner_Reg((uint16_t)0x0000,(uint16_t)0x00fc);

Delay(0x0FFF);

Write_Tuner_Reg((uint16_t)0x0001,(uint16_t)0x0059);

Delay(0x0FFF);






Delay(0xFFFF);
Delay(0xFFFF);
Delay(0xFFFF);
Delay(0xFFFF);
while(1)
{
	Delay(0xFFFF);
}

/*

while(1)
{
	SET_PIN_HIGH(CtrlClk);
	Delay(0x0FFF);
	SET_PIN_LOW(CtrlClk);
	Delay(0x0FFF);


	SET_PIN_HIGH(CtrlEn);
	Delay(0x0FFF);
	SET_PIN_LOW(CtrlEn);
	Delay(0x0FFF);


	SET_PIN_HIGH(CtrlData);
	Delay(0x0FFF);
	SET_PIN_LOW(CtrlData);
	Delay(0x0FFF);






}
*/


//Write_Tuner_Reg((uint16_t)0x0002,(uint16_t)0x0094);


}

/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}
