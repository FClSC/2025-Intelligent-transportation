#include "system_init.h"


/*********************************************


FClSc 2025/3/15



亟待进行事项:
1. PCB小板承载多个模块,进行联合调试

2. 一键启动按键,LED补光灯,OLED代码需要更改引脚以适应新车,以及这些东西在新车运行某个阶段中的调用代码

3. 为了方便调整高度,需要将高度调整的数字,对应到合适的真实高度

4. 陀螺仪在靶心识别的时候校准姿态:需要额外添加一个模式来调用 0x0X

5.面对新赛题，需要增加一些动作，例如把车上的物块放到转盘，比如这个颜色是红，预判下一个是蓝或者绿色，放上去

目前代码陀螺仪旋转90度误差在0.1-0.4度之间,且旋转的速度被增加了


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

// volatile float global_angle = 0.0;  //偏航角
// // volatile float angular_velocity_y = 0.0; //y方向角速度
// // volatile float angular_velocity_z = 0.0; //z方向角速度
// volatile uint8_t new_data_received = 0;  //新数据接收标志位
// uint8_t received_data_packet[11] = {0};   //接收到的数据包

float Angle_Err=0;

int main(void)
{		
	system_Init();
	contral_motor_Init();
	claw_Init();
	// claw_turn0();
	//  claw_open();
	// arrive_most_up();
    //  OLED_Printf(0,16,OLED_8X16,"adjust=%1.f",adjust_float(111.5,90));
	//  OLED_ShowFloatNum(0,48,adjust_float(111.5,90),3,1,OLED_8X16);
	//  OLED_Update();
	//  delay_ms(5000);
	//  stepPosition=0;
    // MOTOR_Angle_micro(90);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }
	// OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	// OLED_Update();
	// delay_ms(5000);
	// ResetAng_Z(); //重置Z轴陀螺仪
	// OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	// OLED_Update();
	// //delay_ms(5000);

//	
	//test
	// int angle =-90;
	// stepPosition=0;			
	// MOTOR_Angle(angle);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }	

    // MOTOR_TurnRight(angle);
    // delay_ms(5000);

	// angle =90;
	// stepPosition=0;			
	// MOTOR_Angle(angle);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }	

	// MOTOR_TurnRight(angle);
	// delay_ms(5000);

	// angle =90;
	// stepPosition=0;			
	// MOTOR_Angle(angle);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }	

	// MOTOR_TurnRight(angle);
	// delay_ms(5000);

	// angle =-90;
	// stepPosition=0;			
	// MOTOR_Angle(angle);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }	

	// MOTOR_TurnRight(angle);

    // //delay_ms(5000);
    // delay_ms(5000);
	// MOTOR_Align();
        //  claw_get_block();
		//  delay_ms(1000);
		//  claw_put_block();
		//  delay_ms(1000);
		//  claw_put_blockF2();





	while(1)              //主代码
	{

		

		OLED_Printf(0,32,OLED_8X16,"Angle==%.3f",global_angle);
		OLED_ShowString(0,48,"Yess",OLED_8X16);
        OLED_ShowFloatNum(0,16,Angle_Err,3,1,OLED_8X16);
		OLED_Update();

		
    //    static int num=0;
	//    OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	//    OLED_Update();
	//    if(Key_Get()==1)
	//    {
		
	// 	num++;
    //     ResetAng_Z();//按键按下清零Z轴陀螺仪
		
	// 	OLED_ShowNum(16,16,num,3,OLED_8X16);
	// 	OLED_Update();
		
	//    }
	   //按键启动
	//   if(new_data_received)//接收到了新的数据
	//   {
		  
        
    //    OLED_ShowFloatNum(0,16,global_angle,3,4,OLED_8X16);
	//    OLED_Update();
    //    delay_s(6);
	//    ResetAng_Z();
	// 	  new_data_received=0;				
	//   }
	  
		if(Key_Get() == 1)//一键启动，如果按下，给树莓派发送启动指令
		{
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);

			
		}  
     

    //   if(Serial2_GetRxFlag() == 1)//串口屏，接收到串口屏的点按指示，发送启动指令
	// 		{
	// 			UART_SendPacket2UP(0x02);
	// 			UART_SendPacket2UP(0x02);
	// 			UART_SendPacket2UP(0x02);
	// 			UART_SendPacket2UP(0x02);
				
	// 		}

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
