/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "Include.h"


/*
 * ��������forward
 * ����  ��У׼���ǰ������
 * ����  ��adjust
 * ���  ����
 * ����  �����ܺ����е���
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
 * ��������back
 * ����  ��У׼��ĺ��˷���
 * ����  ��adjust
 * ���  ����
 * ����  �����ܺ����е���
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
 * ��������left
 * ����  ��У׼�����ת����
 * ����  ��adjust
 * ���  ����
 * ����  �����ܺ����е���
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
 * ��������right
 * ����  ��У׼�����ת����
 * ����  ��adjust
 * ���  ����
 * ����  �����ܺ����е���
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







