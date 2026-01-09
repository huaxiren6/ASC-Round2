#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Timer.h"
#include "Key.h"
#include "OLED.h"
#include "Encoder.h"
#include "Motor.h"
#include "pwm.h"
#include "Serial.h"
#include "string.h"

float Target, Actual, Out;
float Kp, Ki, Kd;
float Error0, Error1, Error2;

uint8_t KeyNum = 0;
int8_t Press_flag=0;

char SerialData[100];

int main(void)
{	
	Timer_Init();
	Key_Init();
	OLED_Init();
	Encoder_Init();
	Motor_Init();
	PWM_Init();
	Serial_Init();
	
	while (1)
	{
		OLED_Printf(0, 16, OLED_8X16, "Kp:%4.2f", Kp);
		OLED_Printf(0, 32, OLED_8X16, "Ki:%4.2f", Ki*10);
		OLED_Printf(0, 48, OLED_8X16, "Kd:%4.2f", Kd);
		
		OLED_Printf(64, 16, OLED_8X16, "Tar:%+04.0f", Target);
		OLED_Printf(64, 32, OLED_8X16, "Act:%+04.0f", Actual);
		OLED_Printf(64, 48, OLED_8X16, "Out:%+04.0f", Out);
		
		OLED_Update();

		Serial_Printf("%f,%f,%f\r\n", Target, Actual, Out);
		
		if(KeyNum == 0)
		{
			if(Press_flag == 1)
			{
				OLED_Clear();
				Press_flag=0;
			}
			
			OLED_ShowString(0,0,"Mode_1:Speed",OLED_8X16);
		
			OLED_Update();
			
			if (Serial_RxFlag == 1)
			{
				Target = 0;
				
				strcpy(SerialData,Serial_RxPacket);
				char *percentPos = strchr(SerialData, '%');
				
                if (percentPos != NULL)
                {
                    Target = atoi(percentPos + 1);
					
                    if (Target > 100)
					{
						Target = 100;
					}
                    if (Target < -100)
					{
						Target = -100;
					}
				}
				Serial_RxFlag = 0;
			}
		}
		else if(KeyNum == 1)
		{
			if(Press_flag == 1)
			{
				OLED_Clear();
				Press_flag = 0;
			}
			
			OLED_ShowString(0,0,"Mode_2:Location",OLED_8X16);
			
			OLED_Update();
			
		}
	}
}
