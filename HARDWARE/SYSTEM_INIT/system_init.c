#include "system_init.h"

/*******************************************
函数功能 : 中断优先级，LED，按键，OLED与串口通信的初始化
输入参数 : 无
输出参数 ：无
********************************************/
void system_Init(void)
{
    //delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LED_Init();
	KEY_Init();
    OLED_Init();
	UART1_Init();
	UART2_Init();
	UART4_Init();
	UART5_Init();
	TIM6_COUNT_Init();
	delay_ms(50);
	WS2812_Init();
}

