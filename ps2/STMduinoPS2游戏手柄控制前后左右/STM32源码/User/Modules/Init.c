/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"


/*
 * ��������Init_LED
 * ����  ����ˮ��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Init_LED()
{
  for(int i=0;i<50;i++)
  {
    GPIOB->ODR ^= GPIO_Pin_5;
    Delay_ms(200);
    GPIOD->ODR ^= GPIO_Pin_2;
    Delay_ms(200);
  }
  for(int i=0;i<2;i++)
  {
    GPIOB->ODR ^= GPIO_Pin_5;
    Delay_ms(50);
    GPIOD->ODR ^= GPIO_Pin_2;
    Delay_ms(50);
  }
  LED1_Low;
  LED2_Low;
}




/*
 * ��������Init_Steer
 * ����  ����ʼ��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void Init_Steer()
{
    u8 l,r;
    I2C_EEPROM_Init();

    adjust=I2C_EEPROM_ReadByte(0x10);//�洢���У׼��־
    if(adjust==0xff)adjust=1;//��δ�������1
    l=I2C_EEPROM_ReadByte(0x09);//��eeprom��ȡ��൵λ��ֵ
    r=I2C_EEPROM_ReadByte(0x0a);//��eeprom��ȡ�Ҳ൵λ��ֵ
    if((l>100)||(r>100))//�жϵ�λ��ֵ�Ƿ����
    {
      l=100;
      r=100;
    }
    speed_left=l*8+200;//��λֵ������ٶ�ֵ
    speed_right=r*8+200;//��λֵ������ٶ�ֵ
    
}


