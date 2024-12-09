#include "key.h"

/********************************
函数功能 : 按键的控制
输入参数 : 无
输出参数 ；无
*********************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
	
}
/********************************
函数功能 : 按键KEY0的读取
输入参数 : 无
输出参数 ；按下返回1，没有按下返回0
*********************************/
u8 click0(void)
{
			static u8 flag_key=1;//按键按松开标志
			if(flag_key&&WAKE_UP==1)
			{
			flag_key=0;
			return 1;	// 按键按下
			}
			else if(0==WAKE_UP)			flag_key=1;
			return 0;//无按键按下
}
/********************************
函数功能 : 按键KEY1的读取
输入参数 : 无
输出参数 ；按下返回1，没有按下返回0
*********************************/
u8 click1(void)
{
			static u8 flag_key=1;//按键按松开标志
			if(flag_key&&KEY0==1)
			{
			flag_key=0;
			return 1;	// 按键按下
			}
			else if(0==KEY0)			flag_key=1;
			return 0;//无按键按下
}
/********************************
函数功能 : PCB板子上按键KEY1的读取
输入参数 : 无
输出参数 ；按下返回1，没有按下返回0
*********************************/
u8 clickKEY1(void)
{
			static u8 flag_key=1;//按键按松开标志
			if(flag_key&&KEY1==1)
			{
			flag_key=0;
			return 1;	// 按键按下
			}
			else if(0==KEY1)			flag_key=1;
			return 0;//无按键按下
}
/********************************
函数功能 : PCB板子上按键KEY2的读取
输入参数 : 无
输出参数 ；按下返回1，没有按下返回0
*********************************/
u8 clickKEY2(void)
{
			static u8 flag_key=1;//按键按松开标志
			if(flag_key&&KEY2==1)
			{
			flag_key=0;
			return 1;	// 按键按下
			}
			else if(0==KEY2)			flag_key=1;
			return 0;//无按键按下
}
