#include "system_init.h"


/*********************************************


FClSc 2025/4/15



亟待进行事项:


1.面对新赛题，需要增加一些动作，最主要是新的物块，需要独立设计高度与爪子张开关闭的角度，3/30基本完成，未在上位机建立动作

2.新扫码模块的配置，改成从一开始就开始或者变成斜的，以及小板子上新扫码模块的添加（基本完成），目前偶尔会出现传给上位机没东西的情况，
或许改为上位机调用扫码后立即问我要（以前的方式）会改变更好

3.准备比赛需要的器件和东西

4.长距离位移爪子收起来动的动作

5.脉冲移动不准，修改计算

6.小板子的关于黑色大陀螺仪的安装以及ws2812的安装测试

7.如果接收esp8266发送的任务码，直接等待串口即可，目前完成了UDP协议，TCP等待完成
即为
			while(1)//如果没有接收到数据就一直等待
			{
				if(Serial5_GetRxFlag() == 1)//接收到了数据就处理
				{
					int16_t code1 =0; 
					int16_t code2 =0; 	
					delay_ms(300);//等待数据接收完全
					UART5_ParseCode(UART5_RX_BUF,&code1,&code2);//解析出二维码数据，此时UART5_BUX中依然存放的是二维码数据	
					u2_printf("tt3.txt=\"%d+%d\"",code1,code2);//多次发送给串口屏
					delay_ms(10);
					u2_printf("tt3.txt=\"%d+%d\"",code1,code2);
					delay_ms(10);
					u2_printf("t3.txt=\"%d+%d\"",code1,code2);
					delay_ms(10);
					u2_printf("t3.txt=\"%d+%d\"",code1,code2);
					delay_ms(10);
					u2_printf("tt3.txt=\"%d+%d\"",code1,code2);
					delay_ms(10);			
					break;
				}
			}


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

void test(void); //测试函数

int16_t base_angle = 0; //基准角度,根据上位机要求角度跟随用，比如上位机调用转90度，基准角度会加90度，反方向会减去90度
//也就是相对于初始Z轴0度的偏角


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

		OLED_Printf(0,0,OLED_8X16,"Angle=%.3f",global_angle);
		OLED_Printf(0,16,OLED_8X16,"BaseAngle=");
		OLED_ShowSignedNum(64,16,base_angle,3,OLED_8X16);
		OLED_Printf(0,32,OLED_8X16,"Err_Angle=%.3f",global_angle-base_angle);
		OLED_Printf(0,48,OLED_8X16,"Code=");
        OLED_Printf(64,48,OLED_8X16,UART5_RX_BUF);
		OLED_Update();


		if(Key_Get() == 1)//一键启动，如果按下，给工控机发送启动指令，同时令目标角度为0
		{
			base_angle = 0;
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

		if(Serial5_GetRxFlag() == 1)//如果接收到了扫码发来的数据就处理
		{
			int16_t code1 =0; 
			int16_t code2 =0; 	
			delay_ms(300);//等待数据接收完全
			UART5_ParseCode(UART5_RX_BUF,&code1,&code2);//解析出二维码数据，此时UART5_BUX中依然存放的是二维码数据	
			u2_printf("tt3.txt=\"%d+%d\"",code1,code2);//多次发送给串口屏
			delay_ms(10);
			u2_printf("tt3.txt=\"%d+%d\"",code1,code2);
			delay_ms(10);
			u2_printf("t3.txt=\"%d+%d\"",code1,code2);
			delay_ms(10);
			u2_printf("t3.txt=\"%d+%d\"",code1,code2);
			delay_ms(10);
			u2_printf("tt3.txt=\"%d+%d\"",code1,code2);
			delay_ms(10);			

		}
		
	}	 
	

} 


void test(void) //测试程序
{
	claw_get_block1();//转盘放车上
	delay_ms(1000);
	claw_get_block1();
	delay_ms(1000);
	claw_get_block1();
	delay_ms(1000);

	claw_get_block();//地上放车上
	delay_ms(1000);
	claw_get_block();
	delay_ms(1000);
	claw_get_block();
	delay_ms(1000);

	claw_put_block();//车上放地上
	delay_ms(1000);
	claw_put_block();
	delay_ms(1000);
	claw_put_block();
	delay_ms(1000);

	claw_put_blockF2();//车上放二层
	delay_ms(1000);
	claw_put_blockF2();
	delay_ms(1000);
	claw_put_blockF2();
	delay_ms(1000);

	claw_put_block2();//车上放转盘
	delay_ms(1000);
	claw_put_block2();
	delay_ms(1000);
	claw_put_block2();
	delay_ms(1000);



}
