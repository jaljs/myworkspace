/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"


/*
 * ��������GPIO_ALL_Config
 * ����  �����й������ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  ����ʼ���е���
 */
void GPIO_ALL_Config(void)     //���й������ų�ʼ��
{  
      MOTOR_GPIO_Config();      //������ų�ʼ��
      LED_GPIO_Config();        //��ʼ��LED1��LED2��ˮ��
}

/*
 * ��������LED_GPIO_Config
 * ����  ����ˮ�����ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
 */
void LED_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ
      GPIO_Init(GPIOB, &GPIO_InitStructure);
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOD, &GPIO_InitStructure);
      LED1_Low;
      LED2_Low;
}



/*
 * ��������Infrared_GPIO_Config
 * ����  ��������ų�ʼ��
 * ����  ����
 * ���  ����
 * ����  �����ܺ����е���
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



