#include "system_init.h"


/*********************************************


FClSc 2025/3/31



亟待进行事项:


1.面对新赛题，需要增加一些动作，最主要是新的物块，需要独立设计高度与爪子张开关闭的角度，3/30基本完成，未在上位机建立动作

2.新扫码模块的配置，改成从一开始就开始或者变成斜的，以及小板子上新扫码模块的添加

3.准备比赛需要的器件和东西

4.陀螺仪在流程中搞得优化，近期需要保持在3.30左右

可采用一阶低通滤波器对陀螺仪数据进行处理,以减小误差
// 示例：一阶低通滤波
// 全局变量
float filtered_angle = 0.0;
float alpha = 0.1; // 滤波系数（0.1~0.3）

// 在UART4_IRQHandler或数据解析函数中
void ParseData(uint8_t *data, uint16_t length) {
    // ... 原始解析逻辑 ...
    float raw_angle = ((float)yaw) / 32768.0 * 180.0; // 原始角度
    filtered_angle = alpha * raw_angle + (1 - alpha) * filtered_angle; // 一阶低通滤波
    global_angle = filtered_angle; // 更新全局角度
}


*********************************************/

float Angle_Err=0;

int main(void)
{		
	system_Init();
	contral_motor_Init();
	claw_Init();
	delay_ms(500);
	arrive_most_up();
	delay_ms(1000);
	claw_turn1();

	
	while(1)              //主代码
	{

		OLED_Printf(0,16,OLED_8X16,"Angle=%.3f",global_angle);
		OLED_Printf(0,32,OLED_8X16,"Angle_Err=%.3f",Angle_Err);
		OLED_Printf(0,48,OLED_8X16,"Code=");
        OLED_Printf(64,48,OLED_8X16,UART5_RX_BUF);
		OLED_Update();


		if(Key_Get() == 1)//一键启动，如果按下，给工控机发送启动指令
		{
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);		
		}  
     

		if(Serial1_GetRxFlag() == 1)//接收树莓派消息
		{
			uart_handle();
			UART_SendPacket2UP(0x01);
		}
		
	}	 
	

} 


void test(void) //测试程序
{
     



}
