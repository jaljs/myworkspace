/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm8l15x.h"
#include "stm8l15x_usart.h"
#include "stm8l15x_gpio.h"
#include "stm8l15x_clk.h"
#include "stm8l15x_tim1.h"
#include "stm8l15x_exti.h"
#include "stm8l15x_syscfg.h"




/* Private defines -----------------------------------------------------------*/
static void Delay(uint32_t nCount);
static void SYNC_GPIO_Init();
static void UART1_Send(uint8_t dat);
static void Init_UART1();
static void Delay_t();

/* SPI GPIO define */
#define SPI_CLOCK(a)  a(GPIOC, GPIO_Pin_1);

#define SPI_DATA(a)   a(GPIOC, GPIO_Pin_0);

#define SPI_READ_DATA ((GPIO_ReadInputData(GPIOC) >> 0) & 1)

#define SPI_EN        GPIO_WriteLow(GPIOC, GPIO_Pin_2);
#define SPI_DIS       GPIO_WriteHigh(GPIOC, GPIO_Pin_2);

#define SPI_READ      GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_0, GPIO_Mode_In_FL_No_IT);
#define SPI_WRITE     GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast);

void clock_cycle()
{
    SPI_CLOCK(GPIO_WriteLow);
    Delay(1);
    SPI_CLOCK(GPIO_WriteHigh);
    Delay(1);
    SPI_CLOCK(GPIO_WriteLow);
    Delay(1);
}



void rffc2071a_hw_rst()
{

}

uint16_t rffc2071a_spi_read(uint8_t addr)
{
    uint16_t data =0;
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN; 
    clock_cycle();
    SPI_DATA(GPIO_WriteHigh);
    clock_cycle();
    for(i= 0; i< 7;i++)
    {
        pGPIO = (addr & (1 << (6-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    SPI_READ;
    clock_cycle();
    for(i = 0; i < 16;i++)
    {
        clock_cycle();
        data = data << 1;
        data |= SPI_READ_DATA;
    }
    SPI_DIS; 
    SPI_WRITE;
    clock_cycle();
    return data;
}
void rffc2071a_spi_write(uint8_t addr, uint16_t data)
{

#if 1

    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN; 
    clock_cycle();
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    for(i= 0; i< 7;i++)
    {
        pGPIO = (addr & (1 << (6-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    for(i = 0; i < 16;i++)
    {
        pGPIO = (data & (1 << (15-i))) == 0?GPIO_WriteLow:GPIO_WriteHigh;
        SPI_DATA(pGPIO);
        clock_cycle();
    }
    SPI_DIS; 
    clock_cycle();
#else
  uint16_t i;
  
  uint32_t BafferData=(uint32_t)0x0000;
  uint32_t BafferSetData=(uint32_t)0x0000;//SDA data 
  
  BafferData=(uint32_t)0x01|(uint32_t)0x0000;
  BafferData=BafferData<<22;
  BafferSetData=BafferSetData|BafferData;



  BafferData=(uint32_t)addr|(uint32_t)0x0000;
  BafferData=BafferData<<21;
  BafferSetData=BafferSetData|BafferData;
  
  BafferData=(uint32_t)data|(uint32_t)0x0000;
  BafferData=BafferData<<15;
  BafferSetData=BafferSetData|BafferData;//bit15~bit3 is the spi sda 
  

  SPI_WRITE;
  SPI_CLOCK(GPIO_WriteLow);
  SPI_DATA(GPIO_WriteLow);
  Delay_t();
  clock_cycle();

  SPI_EN; 

  clock_cycle();  //  x   data write  


  SPI_DATA(GPIO_WriteLow);  //write comm
  clock_cycle();

  for( i=1;i<=22;i++)
  {
    //DATA CONTROL
    Delay(0x00FF);
    
    if(((uint32_t)BafferSetData&(uint32_t)0x200000)==(uint32_t)0x0000)
    {
      SPI_DATA(GPIO_WriteLow);
    }
    else
    {
      SPI_DATA(GPIO_WriteHigh);
    }
    Delay_t();

    clock_cycle();  //  x   data write  
    
   
    BafferSetData=BafferSetData<<1;

  }
  






  SPI_DIS; 
  clock_cycle();




  

  
  

#endif


}
void Uart_print(uint16_t data)
{
    int i ;
    uint8_t send_data;
    for (i = 0; i< 4;i++){
        if(((data >>i)&0xf) > 9)
        {send_data = 'a'+((data >>i)&0xf)-10; }
        else
        {send_data = '0'+((data >>i)&0xf);}
        UART1_Send(send_data);
    }
}
void main(void)
{
  uint16_t pllset = 0;
  uint16_t vcoset = 0;
  uint16_t rb = 0; 
  SYNC_GPIO_Init();
  //Init_UART1();
  Delay(10000);
  
  GPIO_WriteLow(GPIOC, GPIO_Pin_4);
	
  GPIO_WriteHigh(GPIOD, GPIO_Pin_1);//set enbl high
  Delay(0x1000);
// hw reset device  
  GPIO_WriteLow(GPIOD, GPIO_Pin_0);
  Delay(0x1000);
  GPIO_WriteHigh(GPIOD, GPIO_Pin_0);
//------------------------------------  
  Delay(0x1000);
  SPI_DIS; 

#if 1
// set up device 
  
  rb = rffc2071a_spi_read(0x0f); //not use  do the spi bug
  rffc2071a_spi_write(0xf, rb|0x00);
//  rffc2071a_spi_write(0x00,0xbef9);
  
  rffc2071a_spi_write(8, 0xff00|(127 << 8));

  rffc2071a_spi_write(4, 0xacbf|(12 << 8));
  rffc2071a_spi_write(5, 0xacbf|(12 << 8));
  rffc2071a_spi_write(0x1e, 5|4);// TESTrgbyp = 1



  rffc2071a_spi_write(0x16, 1);// set led lock
  //P1 test 
  rffc2071a_spi_write(0xc,0x15a8);
  rffc2071a_spi_write(0xd, 0x4000);
  rffc2071a_spi_write(0xe, 0x0000);
  //P2 test
  rffc2071a_spi_write(0xf, 0x15aa);
  rffc2071a_spi_write(0x10, 0x4000);
  rffc2071a_spi_write(0x11, 0x0000);

  //loop filter
//  rffc2071a_spi_write(6, 0x0000);
//  rffc2071a_spi_write(7, 0x0000);

  //P1 low noise 314
 // rffc2071a_spi_write(0xc, ((96<<7)|  (16<<4)| (2<<2))|0x1a94);
//  rffc2071a_spi_write(0xd, 0xaa15);
//  rffc2071a_spi_write(0xe, 0x6a << 8);
  //P2 low noise 314
//  rffc2071a_spi_write(0xf, ((96<<7)|  (16<<4)| (2<<2))|0x1e84);
//  rffc2071a_spi_write(0x10, 0xaa15);
//  rffc2071a_spi_write(0x11, 0x6a << 8);

  rffc2071a_spi_write(0x0b, 0x7e00);//tx rx mode
 //low phase noise test
  rffc2071a_spi_write(0x00, 0xfff9);//
  

  rffc2071a_spi_write(0x09,0x8228 );//pll relock



#else
  rffc2071a_spi_read(0x00);
  
  rffc2071a_spi_write(0x00, 0xfffa);
  rffc2071a_spi_write(0x00, 0xfff0);
  if(rffc2071a_spi_read(0x00)==0xfffa)
  	GPIO_WriteHigh(GPIOC, GPIO_Pin_4);
  
  rffc2071a_spi_write(0x01, 0x4064);
  rffc2071a_spi_write(0x02, 0x9055);
  rffc2071a_spi_write(0x03, 0x2d02);
  rffc2071a_spi_write(0x04, 0xacdf);
  rffc2071a_spi_write(0x05, 0xacbf);
  rffc2071a_spi_write(0x06, 0x0028);
  rffc2071a_spi_write(0x07, 0x0028);
  rffc2071a_spi_write(0x08, 0xff00);
  rffc2071a_spi_write(0x09, 0x8220);
  rffc2071a_spi_write(0x0a, 0x0202);
  rffc2071a_spi_write(0x0b, 0xc800);//tx rx mode
//  rffc2071a_spi_write(0x0b, 0x4800);//full mode 
  rffc2071a_spi_write(0x0c, 0x2024);
  rffc2071a_spi_write(0x0d, 0x0000);
  rffc2071a_spi_write(0x0e, 0x0000);
 //LO set ---------------------------
  rffc2071a_spi_write(0x0f, 0x15a8);
  rffc2071a_spi_write(0x10, 0x4000);
  rffc2071a_spi_write(0x11, 0x0000);
  rffc2071a_spi_write(0x12, 0x15aa);
  rffc2071a_spi_write(0x13, 0x4000);
  rffc2071a_spi_write(0x14, 0x0000);
//-------------------------------------- 
  rffc2071a_spi_write(0x15, 0x0000);
  rffc2071a_spi_write(0x16, 0x0001);//set lock 
  rffc2071a_spi_write(0x17, 0x4900);
  rffc2071a_spi_write(0x18, 0x0281);
  rffc2071a_spi_write(0x19, 0xf00f);
  rffc2071a_spi_write(0x1a, 0x0000);
  rffc2071a_spi_write(0x1b, 0x0005);

  rffc2071a_spi_write(0x09,0x82a8 );//set pllst
  rffc2071a_spi_write(0x09,0x8228 );//pll relock




//  Delay(1000);
  
 // GPIO_WriteLow(GPIOD, GPIO_Pin_1);



#endif
  while(1) {
  __asm__("nop\n");
  }
}

static void SYNC_GPIO_Init()
{

   GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast   );
   GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast   );
   GPIO_Init(GPIOD, (GPIO_Pin_TypeDef)GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast   );
}


static void Delay(uint32_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }

}

static void Delay_t()
{
  Delay(1000);
}




static void Init_UART1(void)
{
#ifdef CREDO_NEW
        SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA, ENABLE);
        SYSCFG_REMAPPinConfig(REMAP_Pin_USART1Clk, ENABLE); 
        GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast); //tx
        GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_Pin_3, GPIO_Mode_In_FL_No_IT);   //rx
#else
        GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Fast);
        GPIO_Init(GPIOA, (GPIO_Pin_TypeDef)GPIO_Pin_2, GPIO_Mode_In_FL_No_IT);   
#endif
  USART_DeInit(USART1);
  USART_Init(USART1,(u32)9600, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, USART_Mode_Rx | USART_Mode_Tx);
  //USART_Cmd(USART1,ENABLE);
}
static void UART1_Send(uint8_t dat)
{
  while(( USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET));
  USART_SendData8(USART1, dat);
  
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
//void assert_failed(uint8_t* file, uint32_t line)
//{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
 // while (1)
 // {
 // }
//}
#endif


