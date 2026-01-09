#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"

extern float Target, Actual, Out;
extern float Kp, Ki, Kd;
extern float Error0, Error1, Error2;

extern uint8_t KeyNum;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
	static uint16_t Count=0;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		if(KeyNum == 0)
		{
			Count ++;
			if (Count >= 1)
			{
				Count = 0;
				
				Actual = Encoder_Get_1();
				
				Error2 = Error1;
				Error1 = Error0;
				Error0 = Target - Actual;
				
				Out += Kp * (Error0 - Error1) + Ki * Error0 
						+ Kd * (Error0 - 2 * Error1 + Error2);
				
				if (Out > 100) {Out = 100;}
				if (Out < -100) {Out = -100;}
				
				Motor_SetPWM_1(Out); 
				
			}
		}
		else if(KeyNum == 1)
		{
			Count ++;
			if (Count >= 10)
			{
				Count = 0;
				
				Target += Encoder_Get_2();
				
				Actual += Encoder_Get_1();
				
				Error2 = Error1;
				Error1 = Error0;
				Error0 = Target - Actual;
				
				Out += Kp * (Error0 - Error1) + Ki * Error0
					   + Kd * (Error0 - 2 * Error1 + Error2);
				
				if (Out > 100)
				{
					Out = 100;
				}
				if (Out < -100)
				{
					Out = -100;
				}			
			}
		}
		
		Key_Tick();
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
