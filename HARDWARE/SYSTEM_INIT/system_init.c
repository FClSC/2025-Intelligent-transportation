#include "system_init.h"

/*******************************************
�������� : �ж����ȼ���LED��������OLED�봮��ͨ�ŵĳ�ʼ��
������� : ��
������� ����
********************************************/
void system_Init(void)
{
	//delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	KEY_Init();
  OLED_Init();
	//delay_init();
	UART1_Init();
	UART2_Init();
	UART5_Init();
	TIM6_COUNT_Init();
	delay_ms(50);
	ws2812_Init();
}
