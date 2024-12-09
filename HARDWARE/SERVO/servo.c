#include "servo.h"

//TIM5_CH2    PA1    servo1  Y

/********************************
函数功能 : 舵机1的初始化
输入参数 : 无
输出参数 ；无
*********************************/
void Servo1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	// 72 000 000/7200             50             100us        200
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=200-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC2Init(TIM5,&TIM_OCInitStructure);
	
	TIM_OC2PreloadConfig(TIM5,ENABLE);
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	
	TIM_Cmd(TIM5,ENABLE);
}
//TIM5_CH3    PA2    servo2  Y
/********************************
函数功能 : 舵机2的初始化
输入参数 : 无
输出参数 ；无
*********************************/
void Servo2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=2000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC3Init(TIM5,&TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM5,ENABLE);
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	
	TIM_Cmd(TIM5,ENABLE);
}
//TIM5_CH4    PA3    servo3  Y
/********************************
函数功能 : 舵机3的初始化
输入参数 : 无
输出参数 ；无
*********************************/
void Servo3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=2000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC4Init(TIM5,&TIM_OCInitStructure);
	
	TIM_OC4PreloadConfig(TIM5,ENABLE);
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	
	TIM_Cmd(TIM5,ENABLE);
}
/*************************
	 x = K*angle + 0.5
	 0---0.5/20           
   1.5/90 = 2.5/180
	 90--1.5/20


100us    10

0.5ms   0
1ms     45

10 = 45* +5

200
*************************/
/********************************
函数功能 : 舵机1的控制函数
输入参数 : 角度
输出参数 ；无
*********************************/
void SERVO1_CONTRAL(uint8_t angle)
{
	float temp ;
	temp = 0.074*angle + 5;
	TIM_SetCompare2(TIM5,(uint16_t)temp);
}
/********************************
函数功能 : 舵机2的控制函数
输入参数 : 角度
输出参数 ；无
*********************************/
void SERVO2_CONTRAL(uint8_t angle)
{
	float temp ;
	temp = 0.74*angle + 50;
	TIM_SetCompare3(TIM5,(uint16_t)temp);
}
/********************************
函数功能 : 舵机3的控制函数
输入参数 : 角度
输出参数 ；无
*********************************/
void SERVO3_CONTRAL(uint8_t angle)
{
	float temp ;
	temp = 0.74*angle + 50;
	TIM_SetCompare4(TIM5,(uint16_t)temp);
}


