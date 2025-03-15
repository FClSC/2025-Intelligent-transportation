#include "key.h"

/********************************
函数功能 : 按键的控制，一键启动
输入参数 : 无
输出参数 ；无
*********************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//下拉输入，正常处于低电平，按下可读取高电平
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	GPIO_ResetBits(GPIOD,GPIO_Pin_0);

	
}
/********************************
函数功能 : 按键KEY的读取
输入参数 : 无
输出参数 ；按下返回1，没有按下返回0
*********************************/
uint8_t Key_Get(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) == 1)
	{
		delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) == 1);
		delay_ms(20);
		KeyNum = 1;
	}
	
	return KeyNum;
}
