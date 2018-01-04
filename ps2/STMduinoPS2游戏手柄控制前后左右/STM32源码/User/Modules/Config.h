/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#ifndef __CONFIG_H
#define	__CONFIG_H

#define MOTOR_A_EN_High              GPIO_SetBits(GPIOA,GPIO_Pin_0);     //���ʹ�ܶ�A����Ϊ�� PA0
#define MOTOR_A_EN_Low               GPIO_ResetBits(GPIOA,GPIO_Pin_0);   //���ʹ�ܶ�A����Ϊ�� PA0
#define MOTOR_B_EN_High              GPIO_SetBits(GPIOA,GPIO_Pin_1);     //���ʹ�ܶ�B����Ϊ�� PA1
#define MOTOR_B_EN_Low               GPIO_ResetBits(GPIOA,GPIO_Pin_1);   //���ʹ�ܶ�B����Ϊ�� PA1

#define MOTOR_A_CON1_HIGH            GPIO_SetBits(GPIOC,GPIO_Pin_6);     //����ӿ�1-A����Ϊ�ߵ�ƽ PC6
#define MOTOR_A_CON1_LOW             GPIO_ResetBits(GPIOC,GPIO_Pin_6);   //����ӿ�1-A����Ϊ�͵�ƽ PC6
#define MOTOR_A_CON2_HIGH            GPIO_SetBits(GPIOC,GPIO_Pin_7);     //����ӿ�2-A����Ϊ�ߵ�ƽ PC7
#define MOTOR_A_CON2_LOW             GPIO_ResetBits(GPIOC,GPIO_Pin_7);   //����ӿ�2-A����Ϊ�͵�ƽ PC7
#define MOTOR_B_CON1_HIGH            GPIO_SetBits(GPIOC,GPIO_Pin_8);     //����ӿ�1-B����Ϊ�ߵ�ƽ PC8
#define MOTOR_B_CON1_LOW             GPIO_ResetBits(GPIOC,GPIO_Pin_8);   //����ӿ�1-B����Ϊ�͵�ƽ PC8
#define MOTOR_B_CON2_HIGH            GPIO_SetBits(GPIOC,GPIO_Pin_9);     //����ӿ�2-B����Ϊ�ߵ�ƽ PC9
#define MOTOR_B_CON2_LOW             GPIO_ResetBits(GPIOC,GPIO_Pin_9);   //����ӿ�2-B����Ϊ�͵�ƽ PC9

#define Servo1_High                  GPIO_SetBits(GPIOA,GPIO_Pin_6);     //���1��������Ϊ�� PA6
#define Servo2_High                  GPIO_SetBits(GPIOB,GPIO_Pin_1);     //���2��������Ϊ�� PB1
#define Servo3_High                  GPIO_SetBits(GPIOB,GPIO_Pin_0);     //���3��������Ϊ�� PB0
#define Servo4_High                  GPIO_SetBits(GPIOA,GPIO_Pin_7);     //���4��������Ϊ�� PA7
#define Servo5_High                  GPIO_SetBits(GPIOA,GPIO_Pin_4);     //���5��������Ϊ�� PA4
#define Servo6_High                  GPIO_SetBits(GPIOA,GPIO_Pin_5);     //���6��������Ϊ�� PA5
#define Servo7_High                  GPIO_SetBits(GPIOA,GPIO_Pin_2);     //���7��������Ϊ�� PA2
#define Servo8_High                  GPIO_SetBits(GPIOA,GPIO_Pin_3);     //���8��������Ϊ�� PA3


#define Servo1_Low                   GPIO_ResetBits(GPIOA,GPIO_Pin_6);   //���1��������Ϊ�� PA6
#define Servo2_Low                   GPIO_ResetBits(GPIOB,GPIO_Pin_1);   //���2��������Ϊ�� PB1
#define Servo3_Low                   GPIO_ResetBits(GPIOB,GPIO_Pin_0);   //���3��������Ϊ�� PB0
#define Servo4_Low                   GPIO_ResetBits(GPIOA,GPIO_Pin_7);   //���4��������Ϊ�� PA7
#define Servo5_Low                   GPIO_ResetBits(GPIOA,GPIO_Pin_4);   //���5��������Ϊ�� PA4
#define Servo6_Low                   GPIO_ResetBits(GPIOA,GPIO_Pin_5);   //���6��������Ϊ�� PA5
#define Servo7_Low                   GPIO_ResetBits(GPIOA,GPIO_Pin_2);   //���7��������Ϊ�� PA2
#define Servo8_Low                   GPIO_ResetBits(GPIOA,GPIO_Pin_3);   //���8��������Ϊ�� PA3
  

#define Open_Light                   GPIO_SetBits(GPIOC,GPIO_Pin_0);     //���ƴ� PC0
#define Closs_Light                  GPIO_ResetBits(GPIOC,GPIO_Pin_0);   //���ƹر� PC0

#define LED1_High                    GPIO_SetBits(GPIOB,GPIO_Pin_5);     //LED1��
#define LED1_Low                     GPIO_ResetBits(GPIOB,GPIO_Pin_5);   //LED1��
#define LED2_High                    GPIO_SetBits(GPIOD,GPIO_Pin_2);     //LED2��
#define LED2_Low                     GPIO_ResetBits(GPIOD,GPIO_Pin_2);   //LED2��

#define IR                           GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)    //�м����
#define TR_L                         GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)   //ѭ��������
#define TR_R                         GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)   //ѭ��������
#define FR_L                         GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)    //���������
#define FR_R                         GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)    //���������

void GPIO_ALL_Config(void);
void MOTOR_GPIO_Config(void);
void Wave_GPIO_Config(void);
void Infrared_GPIO_Config(void);
void Fllow_GPIO_Config(void);
void Light_Config(void);
void TIM2_Servo_GPIO_Config(void);
void LED_GPIO_Config(void);
void Key_Configuration(void);
#endif /* __CONFIG_H */