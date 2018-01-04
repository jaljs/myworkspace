/*
版权声明：
深圳市小二极客科技（小R科技）旗下：WIFI机器人网·机器人创意工作室版权所有www.wifi-robots.com
您可以任意修改本程序，并应用于自行研发的智能小车机器人及其他电子产品上，但是禁止用于商业牟利。
小R科技保留付诸法律起诉侵权的权利！2016-4-1
BY WIFI机器人网·机器人创意工作室
*/

#include "Include.h"


/*
 * 函数名：forward
 * 描述  ：校准后的前进方向
 * 输入  ：adjust
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void forward(int adjust)
{
        Set_Left_Speed(speed_left);
        Set_Right_Speed(speed_right);
	switch(adjust)
	{
            case 1:MOTOR_GO_FORWARD;return;
            case 2:MOTOR_GO_FORWARD;return;
            case 3:MOTOR_GO_BACK;return;
            case 4:MOTOR_GO_BACK;return;
            case 5:MOTOR_GO_LEFT;return;
            case 6:MOTOR_GO_LEFT;return;
            case 7:MOTOR_GO_RIGHT;return;
            case 8:MOTOR_GO_RIGHT;return;
            default:return;		
	}
}

/*
 * 函数名：back
 * 描述  ：校准后的后退方向
 * 输入  ：adjust
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void back(int adjust)
{
        Set_Left_Speed(speed_left);
        Set_Right_Speed(speed_right);
	switch(adjust)
	{
            case 1:MOTOR_GO_BACK;return;
            case 2:MOTOR_GO_BACK;return;
            case 3:MOTOR_GO_FORWARD;return;
            case 4:MOTOR_GO_FORWARD;return;
            case 5:MOTOR_GO_RIGHT;return;
            case 6:MOTOR_GO_RIGHT;return;
            case 7:MOTOR_GO_LEFT;return;
            case 8:MOTOR_GO_LEFT;return;
            default:return;		
	}
}

/*
 * 函数名：left
 * 描述  ：校准后的左转方向
 * 输入  ：adjust
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void left(int adjust)
{
        Set_Left_Speed(speed_left);
        Set_Right_Speed(speed_right);
	switch(adjust)
	{
            case 1:MOTOR_GO_LEFT;return;
            case 2:MOTOR_GO_RIGHT;return;
            case 3:MOTOR_GO_LEFT;return;
            case 4:MOTOR_GO_RIGHT;return;
            case 5:MOTOR_GO_FORWARD;return;
            case 6:MOTOR_GO_BACK;return;
            case 7:MOTOR_GO_FORWARD;return;
            case 8:MOTOR_GO_BACK;return;
            default:return;	
        }
}

/*
 * 函数名：right
 * 描述  ：校准后的右转方向
 * 输入  ：adjust
 * 输出  ：无
 * 调用  ：功能函数中调用
 */
void right(int adjust)
{
        Set_Left_Speed(speed_left);
        Set_Right_Speed(speed_right);
	switch(adjust)
	{
            case 1:MOTOR_GO_RIGHT;return;
            case 2:MOTOR_GO_LEFT;return;
            case 3:MOTOR_GO_RIGHT;return;
            case 4:MOTOR_GO_LEFT;return;
            case 5:MOTOR_GO_BACK;return;
            case 6:MOTOR_GO_FORWARD;return;
            case 7:MOTOR_GO_BACK;return;
            case 8:MOTOR_GO_FORWARD;return;	
            default:return;
	}
}







