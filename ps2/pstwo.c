#include "pstwo.h"
#include "stm8s.h"
#include "stm8s_gpio.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：PS2驱动程序
Author：pinggai    Version:1.0     Data:2015/05/16
Description: PS2驱动程序
**********************************************************/	 
u16 Handkey;
u8 Comd[2]={0x01,0x42};	//开始命令。请求数据
u8 Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //数据存储数组
u16 MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	//按键值与按键明

//手柄接口初始化    输入  DI->PB12 
//                  输出  DO->PB13    CS->PB14  CLK->PB15
void PS2_Init(void)
{
	GPIO_Init(PS_PORT, (GPIO_Pin_TypeDef)DI, GPIO_MODE_IN_FL_NO_IT  );
	GPIO_Init(PS_PORT, (GPIO_Pin_TypeDef)DO, GPIO_MODE_OUT_PP_LOW_FAST );
	GPIO_Init(PS_PORT, (GPIO_Pin_TypeDef)CS, GPIO_MODE_OUT_PP_HIGH_FAST  );
	GPIO_Init(PS_PORT, (GPIO_Pin_TypeDef)PS2_CLK, GPIO_MODE_OUT_PP_HIGH_FAST  );
	/*
    //输入  DI->PB12
	RCC->APB2ENR|=1<<3;     //使能PORTB时钟
	GPIOB->CRH&=0XFFF0FFFF;//PB12设置成输入	默认下拉  
	GPIOB->CRH|=0X00080000;   

    //  DO->PB13    CS->PB14  CLK->PB15
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟  	   	  	 
	GPIOB->CRH&=0X000FFFFF; 
	GPIOB->CRH|=0X33300000;//PB13、PB14、PB15 推挽输出   	 											  
*/
	}


	
	
//向手柄发送命令
void PS2_Cmd(u8 CMD)
{
	volatile u16 ref=0x01;
	Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;                   //输出以为控制位
		}
		else DO_L;

		CLK_H;                        //时钟拉高
		Delay(10);
		CLK_L;
		Delay(10);
		//CLK_H;
		if(DI_IN)
			Data[1] = ref|Data[1];
        Delay(10);
		

	}
        CLK_H;
        Delay(10);
}
//判断是否为红灯模式
//返回值；0，红灯模式
//		  其他，其他模式


extern void UART1_SendStr(uint8_t *str);
extern void Send(uint8_t dat);
u8 PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据
	CS_H;
 
 //       uint8_t str_r[7];
 //       str_r[0] = (Data[1]/100)+'0';
 //       str_r[1] = (Data[1]/10)%10+'0';
 //       str_r[2] = (Data[1]%10)+'0';
 //       str_r[3] = '\0';
 //       UART1_SendStr(str_r);    
	if( Data[1] == 0x73)
          return 0 ;
	else
          return 1;

}
//读取手柄数据
void PS2_ReadData(void)
{
	volatile u8 byte=0;
	volatile u16 ref=0x01;

	CS_L;

	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据

	for(byte=2;byte<9;byte++)          //开始接受数据
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
            CLK_H;
            Delay(10);
            CLK_L;
            Delay(10);
			//CLK_H;
		  if(DI_IN)
            {
                Data[byte] = ref|Data[byte];  
            }
            Delay(10);
		      
		}   
        Delay(10);
        CLK_H;
	}
	CS_H;	
        
  
		

		
}

//对读出来的PS2的数据进行处理      只处理了按键部分         默认数据是红灯模式  只有一个按键按下时
//按下为0， 未按下为1
u8 PS2_DataKey()
{
	u8 index;

	PS2_ClearData();
	PS2_ReadData();

	Handkey=(Data[4]<<8)|Data[3];     //这是16个按键  按下为0， 未按下为1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;
	}
	return 0;          //没有任何按键按下
}

//得到一个摇杆的模拟量	 范围0~256
u8 PS2_AnologData(u8 button)
{
	return Data[button];
}

//清除数据缓冲区
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}




