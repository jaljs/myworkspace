/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"


/*
 * 函数名：Init_LED
 * 描述  ：流水灯
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
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
 * 函数名：Init_Steer
 * 描述  ：初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Init_Steer()
{
    u8 l,r;
    I2C_EEPROM_Init();

    adjust=I2C_EEPROM_ReadByte(0x10);//存储电机校准标志
    if(adjust==0xff)adjust=1;//从未保存过则赋1
    l=I2C_EEPROM_ReadByte(0x09);//从eeprom读取左侧档位数值
    r=I2C_EEPROM_ReadByte(0x0a);//从eeprom读取右侧档位数值
    if((l>100)||(r>100))//判断档位数值是否合理
    {
      l=100;
      r=100;
    }
    speed_left=l*8+200;//档位值换算成速度值
    speed_right=r*8+200;//档位值换算成速度值
    
}


