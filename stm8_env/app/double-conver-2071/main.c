/**
  n
/******************************************************************************
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
//#include "main.h"
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
#define SPI_CLOCK(a)  a(GPIOC, GPIO_Pin_2);

#define SPI_DATA(a)   a(GPIOC, GPIO_Pin_1);

#define SPI_READ_DATA ((GPIO_ReadInputData(GPIOC) >> 1) & 1)


#define SPI_EN_1C        GPIO_WriteLow(GPIOC, GPIO_Pin_3);
#define SPI_DIS_1C       GPIO_WriteHigh(GPIOC, GPIO_Pin_3);



#define SPI_EN_2C        GPIO_WriteLow(GPIOC, GPIO_Pin_0);
#define SPI_DIS_2C       GPIO_WriteHigh(GPIOC, GPIO_Pin_0);


#define SPI_READ      GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_1, GPIO_Mode_In_FL_No_IT);
#define SPI_WRITE     GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);

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
// 1 Conver spi programming
uint16_t rffc2071a_spi_read_1C(uint8_t addr)
{
    uint16_t data =0;
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN_1C; 
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
    SPI_DIS_1C; 
    SPI_WRITE;
    clock_cycle();
    return data;
}

void rffc2071a_spi_write_1C(uint8_t addr, uint16_t data)
{
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN_1C; 
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
    SPI_DIS_1C; 
    clock_cycle();
}
//----------------------------------------------------//


// 2 Conver spi programming
uint16_t rffc2071a_spi_read_2C(uint8_t addr)
{
    uint16_t data =0;
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN_2C; 
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
    SPI_DIS_2C; 
    SPI_WRITE;
    clock_cycle();
    return data;
}

void rffc2071a_spi_write_2C(uint8_t addr, uint16_t data)
{
    int i = 0;
    void (*pGPIO)(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins) = 0;
    SPI_WRITE;
    SPI_CLOCK(GPIO_WriteLow);
    SPI_DATA(GPIO_WriteLow);
    clock_cycle();
    SPI_EN_2C; 
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
    SPI_DIS_2C; 
    clock_cycle();
}
//----------------------------------------------------//





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
 
 int n=0; 
  SYNC_GPIO_Init();

#if 1 
 for (n = 0;n<5;n++)
{
Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
}
#else
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
  Delay(0x1000);
#endif



  SPI_DIS_1C; 
  SPI_DIS_2C; 

//---------------start set 1 conver--------------------//  
  rb = rffc2071a_spi_read_1C(0x0f); //not use  do the spi bug
  rffc2071a_spi_write_1C(0xf, rb|0x00);
//  rffc2071a_spi_write(0x00,0xbef9);
  
  rffc2071a_spi_write_1C(8, 0xff00|(127 << 8));

  rffc2071a_spi_write_1C(4, 0xacbf|(12 << 8));
  rffc2071a_spi_write_1C(5, 0xacbf|(12 << 8));
  rffc2071a_spi_write_1C(0x1e, 5|4);// TESTrgbyp = 1



  rffc2071a_spi_write_1C(0x16, 1);// set led lock
 

//------LO 450  -----------//
//P1 LO   p1:     0x0c  0x1238
//p2 LO   p2: 	  0x0f  0x123a
//-----------------------//


//------LO 1081.25  -----------//
//P1 LO   p1:      0x0c  0x15a8
//P1 LO   p1:      0x0d  0x4000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x15aa
//P1 LO   p1:      0x10  0x4000
//P1 LO   p1:      0x11  0x0000
//-----------------------//

//------LO 525  -----------//
//P1 LO   p1:      0x0c  0x1538
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x153a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//

//------LO 630  -----------//
//P1 LO   p1:      0x0c  0x1938
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x193a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 900  -----------//
//P1 LO   p1:      0x0c  0x1228
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x122a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 950  -----------//
//P1 LO   p1:      0x0c  0x1328
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x132a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//
//   lo 
  rffc2071a_spi_write_1C(0xc,0x15a8);
  rffc2071a_spi_write_1C(0xd, 0x0000);
  rffc2071a_spi_write_1C(0xe, 0x0000);
  //P2 test  
  rffc2071a_spi_write_1C(0xf, 0x15aa);
  rffc2071a_spi_write_1C(0x10, 0x0000);
  rffc2071a_spi_write_1C(0x11, 0x0000);


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
  rffc2071a_spi_write_1C(0x0b, 0x7e00);//tx rx mode
 //low phase noise test
  rffc2071a_spi_write_1C(0x00, 0xfff9);//
  rffc2071a_spi_write_1C(0x09,0x8228 );//pll relock
//-----------end 1 conver -------------------------//


//---------------start set 2 conver--------------------//  
	rb = rffc2071a_spi_read_2C(0x0f); //not use  do the spi bug
 	rffc2071a_spi_write_2C(0xf, rb|0x00);
//  rffc2071a_spi_write(0x00,0xbef9);
  
  rffc2071a_spi_write_2C(8, 0xff00|(127 << 8));

  rffc2071a_spi_write_2C(4, 0xacbf|(12 << 8));
  rffc2071a_spi_write_2C(5, 0xacbf|(12 << 8));
  rffc2071a_spi_write_2C(0x1e, 5|4);// TESTrgbyp = 1



  rffc2071a_spi_write_2C(0x16, 1);// set led lock
 

//------LO 450  -----------//
//P1 LO   p1:     0x0c  0x1238
//p2 LO   p2: 	  0x0f  0x123a
//-----------------------//


//------LO 1081.25  -----------//
//P1 LO   p1:      0x0c  0x15a8
//P1 LO   p1:      0x0d  0x4000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x15aa
//P1 LO   p1:      0x10  0x4000
//P1 LO   p1:      0x11  0x0000
//-----------------------//

//------LO 525  -----------//
//P1 LO   p1:      0x0c  0x1538
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x153a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//

//------LO 630  -----------//
//P1 LO   p1:      0x0c  0x1938
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x193a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 900  -----------//
//P1 LO   p1:      0x0c  0x1228
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x122a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//


//------LO 950  -----------//
//P1 LO   p1:      0x0c  0x1328
//P1 LO   p1:      0x0d  0x0000
//P1 LO   p1:      0x0e  0x0000
//P1 LO   p1:      0x0f  0x132a
//P1 LO   p1:      0x10  0x0000
//P1 LO   p1:      0x11  0x0000
//-----------------------//
//   lo 
  rffc2071a_spi_write_2C(0xc,0x15a8);
  rffc2071a_spi_write_2C(0xd, 0x0000);
  rffc2071a_spi_write_2C(0xe, 0x0000);
  //P2 test 
  rffc2071a_spi_write_2C(0xf, 0x15aa);
  rffc2071a_spi_write_2C(0x10, 0x0000);
  rffc2071a_spi_write_2C(0x11, 0x0000);


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
  rffc2071a_spi_write_2C(0x0b, 0x7e00);//tx rx mode
 //low phase noise test
  rffc2071a_spi_write_2C(0x00, 0xfff9);//
  rffc2071a_spi_write_2C(0x09,0x8228 );//pll relock


//-----------end 2 conver -------------------------//







  while(1) {
  __asm__("nop\n");
  }
}

static void SYNC_GPIO_Init()
{

   GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast);

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


