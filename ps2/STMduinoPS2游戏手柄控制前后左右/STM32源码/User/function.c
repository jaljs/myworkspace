/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"




/*
 * 函数名：Communication_Decode
 * 描述  ：解析串口数据功能函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：在Interrupt.c串口中断1函数中调用
 */

 void Communication_Decode(void)  
{
    if(buffer[0]==0x00)//手动控制
    {
         GPIOB->ODR ^= GPIO_Pin_5;                     //电机指示灯翻转
         switch(buffer[1])
          {
            case 0x01:MOTOR_GO_FORWARD;return;        //前进
            case 0x02:MOTOR_GO_BACK;return;           //后退
            case 0x03:MOTOR_GO_LEFT;return;           //左转
            case 0x04:MOTOR_GO_RIGHT;return;          //右转
            default:MOTOR_GO_STOP;                    //停止
          }
    }
    
  
    else if(buffer[0]==0x02)
    {
        if(buffer[2]>100)return;     
        if(buffer[1]==0x01)//等于01表示左侧调速
        {
            speed_left=(buffer[2]*8+200);//buffer[2]为档位值最小0最大100
            //将档位值换算左侧速度
            Set_Left_Speed(speed_left);//左边速度
            //I2C_EEPROM_WriteByte(buffer[2],0x09);//把右侧档位存储到EEPROM
        }
        if(buffer[1]==0x02)//等于02表示右侧调速
        {
            speed_right=(buffer[2]*8+200);//buffer[2]为档位值最小0最大100
            //将档位值换算右侧速度
            Set_Right_Speed(speed_right);//右边速度
            //I2C_EEPROM_WriteByte(buffer[2],0x0a);//把右侧档位存储到EEPROM
        }
    }

    else if(buffer[0]==0x40)//电机校准标志，校准功能模式的电机转向方向
    {
        adjust=buffer[1];
        I2C_EEPROM_WriteByte(adjust,0x10);//存储标志	
    }
 
}

