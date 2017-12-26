#include "main.h"
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_tuner.h"
#include "stm8s_it.h"
#include "string.h"
#include "pstwo.h"


void Send(uint8_t dat)
{
	while(( UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET));
	
	UART1_SendData8(dat);
	while((UART1_GetFlagStatus(UART1_FLAG_TC)==RESET));//等待传输完成
	
}

void UART1_SendStr(uint8_t *str)
{
    while(*str != '\0')
    {
        Send(*str++); /* 循环调用发送一个字符函数 */
        
    }  
    Send('\r');
    Send('\n');
}

void Delay(uint16_t nCount);
/* set gpio port statue */
void Delay1m(uint16_t n)//   delay= 1ms*n
{
  uint16_t i;
  
  
  for(i=1;i<=n;i++)
  {
    Delay(0x016c);
  }
}


void Init_UART1(void)
{
	UART1_DeInit();
	UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
	
UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);

//	UART1_Cmd(ENABLE);
}







/*******************************************************************************
* 名称: UART1_SendStr
* 功能: UART1发送len个字符
* 形参: data -> 指向要发送的字符串
*       len -> 要发送的字节数
* 返回: 无
* 说明: 无 
******************************************************************************/



void main(void)
{
    Init_UART1();
	enableInterrupts(); 
	
	UART1_SendStr("hello uart1");

	Delay(72);	     //延时初始化


	PS2_Init();
	u8 DK=0;

        

	
	

	while(1)
	{
		if( PS2_RedLight()!=0) //判断手柄是否为红灯模式，是，指示灯LED点亮
		{
            for(int j=0;j<50;j++)
                Delay(10000);
            UART1_SendStr("红灯 ");
//			DK = PS2_DataKey();

		}
		else	//判断手柄不是红灯模式，指示灯LED熄灭
		{
            for(int j=0;j<5;j++)
                Delay(10000);
			
            
			DK = PS2_DataKey();
			


			if(DK!=0)
			{

               // UART1_SendStr("绿灯 ");
				uint8_t str_r[7];
				str_r[0] = (DK/100)+'0';
				str_r[1] = (DK/10)%10+'0';
				str_r[2] = (DK%10)+'0';
        
				str_r[3] = '\0';
				UART1_SendStr(str_r);

			}
			
			

		}

                

	}	

}



/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
void Delay(uint16_t nCount)//   Delay(0x016c)  1 ms
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}

