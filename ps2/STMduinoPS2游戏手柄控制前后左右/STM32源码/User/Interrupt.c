/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"


void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void) 
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**系统滴答中断服务函数********
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{  
  TimingDelay_Decrement();
}




/**********************串口1中断服务函数************************************/


void USART1_IRQHandler(void)                	//串口1中断服务程序
{
  static u8 i;
  if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==1)
  {
    USART_ClearFlag(USART1,USART_FLAG_RXNE);
    if(rec_flag==0)
    {
      if(USART_ReceiveData(USART1)==0xff)
      {
        rec_flag=1;	
        i=0;
      }			
    }
    else
    {
      if(USART_ReceiveData(USART1)==0xff)
      {
        rec_flag=0;	
        if(i==3)
        {
          Communication_Decode();		
        }
        i=0;
      }
      else
      {
        buffer[i]=USART_ReceiveData(USART1);
        i++;
      }
    }		
  }
  else
  {
    USART_ClearFlag(USART1,USART_FLAG_LBD);
  }	
} 





