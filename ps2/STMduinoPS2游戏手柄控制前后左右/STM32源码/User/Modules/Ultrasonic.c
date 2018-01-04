/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/
#include "Include.h"


/*
 * ��������Get_distance
 * ����  ����ó���������
 * ����  ����
 * ���  ��distance(���׼�)
 * ����  ���ⲿ����
 */
float Get_distance(void)
{
  float distance=0,sum_distance=0;
  u16 TIM=0;
  u8 i=0;
  /*��5�����ݼ���һ��ƽ��ֵ*/
  while(i!=5)
  {
      GPIO_SetBits(GPIOC,GPIO_Pin_4);//�����źţ���Ϊ�����ź�
      Delay_us(12);//�ߵ�ƽ�źų���10us
      GPIO_ResetBits(GPIOC,GPIO_Pin_4);//�����ź�
      
      TIM_Cmd(TIM4, ENABLE);
      /*�ȴ������ź�*/
      while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) && overcount==0);
      TIM4->CNT=0;
      while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) && overcount==0);
      TIM_Cmd(TIM4, DISABLE);
      i++;
      if(overcount!=0)//��ʱ���ж����
      {
            overcount=0;//����
            return 0.0;
      }
      TIM=TIM_GetCounter(TIM4);//��ȡ��TIM4���Ĵ����еļ���ֵ
      distance=(float)sqrt((TIM/10.0*17)*(TIM/10.0*17)-module_interval*module_interval/4.0)+12.0; //12.0Ϊ����//���ݼ���ֵ������β�����
      sum_distance=sum_distance+distance;//�ۼ�5��
  }
  distance=sum_distance/5;//��5��ƽ��ֵ
  return distance;//���ؾ���ֵ
}



/*
 * ��������Send_Distance
 * ����  ������λ�����ͳ���������
 * ����  ����
 * ���  ��distance(���׼�)
 * ����  ���ⲿ����
 */
void Send_Distance(void)
{
    USART_SendData(USART1, 0xFF);
    Delay_ms(5);
    USART_SendData(USART1, 0x03);
    Delay_ms(5);
    USART_SendData(USART1, 0x00);
    Delay_ms(5);
    USART_SendData(USART1, (u16)Get_distance()/10);
    Delay_ms(5);
    USART_SendData(USART1, 0xFF);
    Delay_ms(1000);   
}