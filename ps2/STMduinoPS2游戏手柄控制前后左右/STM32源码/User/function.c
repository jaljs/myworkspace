/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"




/*
 * ��������Communication_Decode
 * ����  �������������ݹ��ܺ���
 * ����  ����
 * ���  ����
 * ����  ����Interrupt.c�����ж�1�����е���
 */

 void Communication_Decode(void)  
{
    if(buffer[0]==0x00)//�ֶ�����
    {
         GPIOB->ODR ^= GPIO_Pin_5;                     //���ָʾ�Ʒ�ת
         switch(buffer[1])
          {
            case 0x01:MOTOR_GO_FORWARD;return;        //ǰ��
            case 0x02:MOTOR_GO_BACK;return;           //����
            case 0x03:MOTOR_GO_LEFT;return;           //��ת
            case 0x04:MOTOR_GO_RIGHT;return;          //��ת
            default:MOTOR_GO_STOP;                    //ֹͣ
          }
    }
    
  
    else if(buffer[0]==0x02)
    {
        if(buffer[2]>100)return;     
        if(buffer[1]==0x01)//����01��ʾ������
        {
            speed_left=(buffer[2]*8+200);//buffer[2]Ϊ��λֵ��С0���100
            //����λֵ��������ٶ�
            Set_Left_Speed(speed_left);//����ٶ�
            //I2C_EEPROM_WriteByte(buffer[2],0x09);//���Ҳ൵λ�洢��EEPROM
        }
        if(buffer[1]==0x02)//����02��ʾ�Ҳ����
        {
            speed_right=(buffer[2]*8+200);//buffer[2]Ϊ��λֵ��С0���100
            //����λֵ�����Ҳ��ٶ�
            Set_Right_Speed(speed_right);//�ұ��ٶ�
            //I2C_EEPROM_WriteByte(buffer[2],0x0a);//���Ҳ൵λ�洢��EEPROM
        }
    }

    else if(buffer[0]==0x40)//���У׼��־��У׼����ģʽ�ĵ��ת����
    {
        adjust=buffer[1];
        I2C_EEPROM_WriteByte(adjust,0x10);//�洢��־	
    }
 
}

