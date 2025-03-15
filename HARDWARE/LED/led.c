#include "led.h"


/********************************
LED1    PE5 
LED0    PB5
**********************************/
/********************************
函数功能 : led的控制
输入参数 : 无
输出参数 ；无
*********************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);	

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);	
	
	GPIO_SetBits(GPIOB,GPIO_Pin_5);//红灯
	GPIO_SetBits(GPIOE,GPIO_Pin_5);//绿灯
	GPIO_SetBits(GPIOD,GPIO_Pin_3);//LED补光灯
}

void LED_Turn(void)  //调用对LED补光灯进行开关操作
{
	if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_3)==1)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_3);
	}
	else
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_3);
	}
}
