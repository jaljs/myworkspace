002D:EW3C1B.tmp:00:1:14=518E3A15:16=47d21313:002D:EW3C1C.tmp:00:1:14=518E3A15:16=47d21313:002F:EW3C1C.tmp.c:00:1:14=518E3A15:16=47d21313:002D:EWA0A1.tmp:00:1:14=518E3A15:16=47d21313:002D:EWA0A2.tmp:00:1:14=518E3A15:16=47d21313:002F:EWA0A2.tmp.c:00:1:14=518E3A15:16=47d21313:002D:EWFA1C.tmp:00:1:14=518E3A15:16=47d21313:002D:EWFA1D.tmp:00:1:14=518E3A15:16=47d21313:002F:EWFA1D.tmp.c:00:1:14=518E3A15:16=47d21313:0030:function.c:011B8:1:14=56016A5C:16=47d21313:#include "function.h"
#include "pwm_output.h"
#include "Time_test.h"
#include "SysTick.h"
extern u8 buffer[3];
extern u8 rec_flag;
extern u16 left_camera;
extern u16 right_camera;
extern u16 up_camera;
extern u16 down_camera;
u16 speed_left=800;
u16 speed_right=800;


 void Communication_Decode(void)  
{
    if(buffer[0]==0x00)
    {
         switch(buffer[1])
          {
          case 0x01:motor_go_forward();return;
          case 0x02:motor_go_back();return;
          case 0x03:motor_go_left();return;
          case 0x04:motor_go_right();return;
          default:motor_stop();
          }
    }
   else if(buffer[0]==0x01)
    {
            if(buffer[2]>160)
                    return;
                    
            switch(buffer[1])
            {
                    u16 temp;
  