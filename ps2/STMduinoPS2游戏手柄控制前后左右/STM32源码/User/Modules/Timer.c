/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/


#include "Include.h"

                                         
/**************************************TIM5��ʱ������************************************************/
										
/*
 * ��������TIM5_GPIO_Config
 * ����  ������TIM5�����PWM�źŵ�ͨ��
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */

static void TIM5_GPIO_Config(void) 
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
      /*****************************��� ENA  PA0     ENB   PA1*************************/
      GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * ��������TIM5_Mode_Config
 * ����  ������TIM5�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */

static void TIM5_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;	 
  TIM_TimeBaseStructure.TIM_Period = (1000-1);       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = (72-1);	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ36MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = (speed_left-1);	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = (speed_right-1);	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);	  //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
  TIM_Cmd(TIM5, ENABLE);                   //ʹ�ܶ�ʱ��5	
}

/*
 * ��������TIM5_PWM_Init
 * ����  ��TIM5 ��ʼ��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
 void TIM5_PWM_Init(void)
{
	TIM5_GPIO_Config();
	TIM5_Mode_Config();
}


                                            
/*****************************************�������**************************************************/
											
/*
 * ��������PWM_MOTOR_LEFT,PWM_MOTOR_RIGHT
 * ����  ������ٶȵ���
 * ����  ��PWM_1,PWM_2
 * ���  ����
 * ����  ���ⲿ����
 */
 
/****************���ʹ��A pwm����*********************/
void Set_Left_Speed(u16 Speed_Left)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Speed_Left-1;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
}

/****************���ʹ��B pwm����*********************/
void Set_Right_Speed(u16 Speed_Right)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Speed_Right-1;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
}