/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"


/*
 * 函数名：GPIO_ALL_Config
 * 描述  ：所有功能引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：初始化中调用
 */
void GPIO_ALL_Config(void)     //所有功能引脚初始化
{  
      MOTOR_GPIO_Config();      //电机引脚初始化
      LED_GPIO_Config();        //初始化LED1、LED2流水灯
}

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：流水灯引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void LED_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出模式
      GPIO_Init(GPIOB, &GPIO_InitStructure);
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOD, &GPIO_InitStructure);
      LED1_Low;
      LED2_Low;
}



/*
 * 函数名：Infrared_GPIO_Config
 * 描述  ：电机引脚初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void MOTOR_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |GPIO_Pin_9;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);
      GPIO_ResetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |GPIO_Pin_9);	
}



