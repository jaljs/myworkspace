#include "stm8s_tuner.h"


//tx_pad1_gain   B4B3  11: 12.5dB       10: 9.1dB       01: 8.5dB
//Tx_rfvga_gain  B2B1  10: 11.5dB       01: 8.5dB       00: 5.7dB


void SET_PIN_HIGH(GPIO_Pin_TypeDef GPIO_PIN)
{
	GPIO_WriteHigh    ( TUNER_SPI_PORT,GPIO_PIN );
}

void SET_PIN_LOW(GPIO_Pin_TypeDef GPIO_PIN)
{
	GPIO_WriteLow    ( TUNER_SPI_PORT,GPIO_PIN );
}

void InitTunerSpi()
{
	SET_CE_OUT();
	SET_SCL_OUT();
	SET_SDA_OUT();
	SET_CE_OUT_2();

}



void Write_Tuner2400_Reg(uint16_t REG_ADD,uint16_t REG_DATA)
{
	uint16_t i;
	
	uint16_t BafferData=(uint16_t)0x0000;
	uint16_t BafferSetData=(uint16_t)0x0000;//SDA data 
	
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


void Write_Tuner700_Reg(uint16_t REG_ADD,uint16_t REG_DATA)
{
	uint16_t i;
	
	uint16_t BafferData=(uint16_t)0x0000;
	uint16_t BafferSetData=(uint16_t)0x0000;//SDA data 
	
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
	
	SET_PIN_HIGH(CtrlEn2);//SET en high
	
	
	
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
			SET_PIN_LOW(CtrlEn2);//SET en LOW
	}
	
	
}
