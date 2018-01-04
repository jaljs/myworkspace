/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/


#include "Include.h"

                                         
/**************************************TIM5定时器配置************************************************/
										
/*
 * 函数名：TIM5_GPIO_Config
 * 描述  ：配置TIM5输出的PWM信号的通道
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */

static void TIM5_GPIO_Config(void) 
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
      /*****************************电机 ENA  PA0     ENB   PA1*************************/
      GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * 函数名：TIM5_Mode_Config
 * 描述  ：配置TIM5输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */

static void TIM5_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;	 
  TIM_TimeBaseStructure.TIM_Period = (1000-1);       //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = (72-1);	    //设置预分频：不预分频，即为36MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = (speed_left-1);	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = (speed_right-1);	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);	  //使能通道2
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
  TIM_Cmd(TIM5, ENABLE);                   //使能定时器5	
}

/*
 * 函数名：TIM5_PWM_Init
 * 描述  ：TIM5 初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
 void TIM5_PWM_Init(void)
{
	TIM5_GPIO_Config();
	TIM5_Mode_Config();
}


                                            
/*****************************************电机部分**************************************************/
											
/*
 * 函数名：PWM_MOTOR_LEFT,PWM_MOTOR_RIGHT
 * 描述  ：电机速度调节
 * 输入  ：PWM_1,PWM_2
 * 输出  ：无
 * 调用  ：外部调用
 */
 
/****************电机使能A pwm设置*********************/
void Set_Left_Speed(u16 Speed_Left)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Speed_Left-1;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
}

/****************电机使能B pwm设置*********************/
void Set_Right_Speed(u16 Speed_Right)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Speed_Right-1;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
}