#include "time_count.h"

void TIM6_COUNT_Init(void)  // 1s¶¨Ê±Æ÷ÖÐ¶Ï
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	// 72 000 000/ (7200)
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=7200-1;
	TIM_TimeBaseStructure.TIM_Prescaler=10000-1;
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	
	TIM_Cmd(TIM6,ENABLE);
}

void TIM6_IRQHandler(void)
{
	static uint8_t flag = 0;
	if(TIM_GetITStatus(TIM6,TIM_IT_Update))
	{
		flag=!flag;
//		LED0=flag;
		SERVO2_CONTRAL(servo_angle2);
		SERVO3_CONTRAL(servo_angle3);
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
}
