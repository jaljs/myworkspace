/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤���� V3.2�汾
*/

/**************************** WiFi �����˴��⹤���� *******************************
��оƬ��STM32F105RCT6
 ����     ����              I/O             TIMER         ����

�����    ena              PA0             TIMER5/CH1
          enb              PA1             TIMER5/CH2
          IN1              PC6
          IN2              PC7
          IN3              PC8
          IN4              PC9
�����    SER1             PA2             TIMER2
          SER2             PA3             TIMER2

���ڣ�    TXD              PA9
          RXD              PA10

PWM��    ���1/  11~       PA6             TIMER2
         ���2/  2         PA7             TIMER2
         ���3/  4         PB0             TIMER2
         ���4/  3~        PB1             TIMER2

I/O��    A15  /  A5        PC5             ADC12-IN15       Echo
         A14  /  A4        PC4             ADC12-IN14       Trig
         A13  /  A3        PC3             ADC12-IN13       �����
         A12  /  A2        PC2             ADC12-IN12       �Һ���
         A11  /  A1        PC1             ADC12-IN11       �к���
         A10  /  A0        PC0             ADC12-IN10       ����
		             
         A11  /  A1        PC1             ADC12-IN11       �������ǰ         
                           PC10                             ���������                                                                      
                           PC11                             ���������

**********************************************************************************/

#include "Include.h"
/*
 * ��������main
 * ����  ��������ں���
 * ����  ����
 * ���  ����
 * ����  ����
 */
            
int cnt = 0;
int flag = 0;
void main(void)
{
  /* ����ϵͳʱ��Ϊ72M */
  SystemInit();
  
  SysTick_Configuration();  //SysTick�ж����ã���Ҫ������ʱ
  
  GPIO_ALL_Config(); //GPIO��ʼ��
  
  //Init_LED();   //��ˮ��
   
  Init_Steer();
    
  TIM5_PWM_Init(); //��ʱ��5(����ٶ�PWM��ʼ��)
  
  USART1_Config();  //���ڳ�ʼ��

  PS2_Init();
  
  Set_Left_Speed(1000);//����ٶ�
  Set_Right_Speed(1000);//�ұ��ٶ�
  while (1)
  {
     PS2_Key=PS2_DataKey();
     Delay_ms(10);
     cnt++;

     if(PS2_Key!=0)
     {
       //printf("PS2_Key:%d\n",PS2_Key);
        cnt = 0;
        flag = 1;
        GPIOB->ODR ^= GPIO_Pin_5;                     //���ָʾ�Ʒ�ת
        if(PS2_Key==PSB_PAD_UP)
        {
          forward(adjust);
        }
        else if(PS2_Key==PSB_PAD_DOWN)
        {
          back(adjust);
        }
        else if(PS2_Key==PSB_PAD_LEFT)
        {
          left(adjust);
        }
        else if(PS2_Key==PSB_PAD_RIGHT)
        {
          right(adjust);
        }
     }

     if(cnt>10)
     {
       cnt = 0;
       if(flag==1)
       {
        flag = 0;
        MOTOR_GO_STOP;
       }  
     }

  }
}		

