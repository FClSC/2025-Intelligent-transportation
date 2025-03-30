#include "system_init.h"


/*********************************************


FClSc 2025/3/30



亟待进行事项:
1.目前的车：爪子张到最开，张不了，为了防止打到，需要重装舵机

2.串口屏优化，目前接收到二维码是一个0+0，不是123+321，且需要把字体改大

3. 为了方便调整高度,需要将高度调整的数字,对应到合适的真实高度，尤其是转盘80-100mm的东西

4.面对新赛题，需要增加一些动作，最主要是新的物块，需要独立设计高度与爪子张开关闭的角度，3/30基本完成，未在上位机建立动作

5.新扫码模块的配置，改成从一开始就开始或者变成斜的，以及小板子上新扫码模块的添加

6.准备比赛需要的器件和东西

7.陀螺仪在流程中搞得优化，近期需要保持在3.30左右

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
	delay_ms(1000);
	arrive_most_up();
	delay_ms(1000);
	claw_turn1();

    // claw_get_block();
	// delay_ms(1000);
	// claw_get_block();
	// delay_ms(1000);
	// claw_put_block();
	// delay_ms(1000);
	// claw_put_block();
	// delay_ms(1000);
	// claw_put_blockF2();
	// delay_ms(1000);
	// claw_put_blockF2();
	// delay_ms(1000);
	// arrive_color_reco();
	// delay_ms(5000);

	// claw_get_block1();
	// delay_ms(1000);
	// claw_get_block1();
	// delay_ms(1000);
	// delay_ms(5000);
	// claw_put_block2();
	// delay_ms(1000);
	// claw_put_block2();
	// delay_ms(1000);


	




	while(1)              //主代码
	{

		OLED_Printf(0,32,OLED_8X16,"Angle==%.3f",global_angle);
		OLED_ShowString(0,48,"Yess",OLED_8X16);
    	OLED_ShowFloatNum(0,16,Angle_Err,3,1,OLED_8X16);
		OLED_Update();




	  
		if(Key_Get() == 1)//一键启动，如果按下，给树莓派发送启动指令
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
