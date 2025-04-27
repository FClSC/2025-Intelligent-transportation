#include "system_init.h"


/*********************************************


FClSc 2025/4/26



即将进行创新实践环节：

注意扫码,把扫码换成摄像头扫码




亟待进行事项:

---爪子小角度张开度数小了？


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
+float filtered_angle = 0.0;
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
//也就是相对于初始Z轴0度的偏角
int16_t base_angle = 0; //基准角度,根据上位机要求角度跟随用，比如上位机调用转90度，基准角度会加90度，反方向会减去90度

//获得扫码信息，全局变量
int16_t code1 =0; 
int16_t code2 =0; 	


int main(void)
{		
	system_Init();
	contral_motor_Init();
	claw_Init();
	delay_ms(500);
	arrive_most_up();
	delay_ms(1000);
	claw_turn1();
	claw_close();

	//claw_open();

	//test();

	

	while(1)              //主代码
	{

		OLED_Printf(0,0,OLED_8X16,"Angle=%.3f",global_angle);
		OLED_Printf(0,16,OLED_8X16,"BaseAngle=");
		OLED_ShowSignedNum(64,16,base_angle,3,OLED_8X16);
		OLED_Printf(0,32,OLED_8X16,"Err_Angle=%.3f",global_angle-base_angle);
		OLED_Printf(0,48,OLED_8X16,"Code=");
        OLED_Printf(64,48,OLED_8X16,UART5_RX_BUF);
		OLED_Update();
	

		if(Key_Get() == 1)//一键启动，如果按下，给工控机发送启动指令，同时令目标角度和串口屏显示为0
		{
			base_angle = 0;
			// arrive_camera();//最低高度
			// delay_ms(2000);
			// arrive_color_reco();//物料颜色识别高度
			// delay_ms(2000);
			// arrive_block_get1();//物料转盘上抓物块的高度
			// delay_ms(2000);
            
			OLED_Clear();
			OLED_ShowNum(0,0,claw_block_get1,3,OLED_8X16);
			OLED_Update();
			delay_ms(1000);
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
	// claw_get_block1();//转盘放车上
	// delay_ms(1000);
	// claw_get_block1();
	// delay_ms(1000);
	// claw_get_block1();
	// delay_ms(1000);

	// claw_get_block();//地上放车上，混动    1111
	// delay_ms(1000);
	// claw_get_block();
	// delay_ms(1000);
	// claw_get_block();
	// delay_ms(1000);

/////////////////////////////////////
	// claw_turn0();
	// claw_open();
	// arrive_block_get();
	// delay_ms(400);
	// claw_close();
	// delay_ms(400);
	// arrive_most_up();//从地面抓起来物块并升到最高

	// stepPosition=0;   //跑
	// stepPosition1=0;  //抓
	// MOTOR_Displacement(10,0);//移动到下一个需要从地上抓取物块的地方
	// claw_turn1();
	// delay_ms(600);
	// arrive_car_put();
	// while(1)
	// {
	// 	if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
	// 	{
	// 		break;
	// 	}
		
	// }

	// claw_open1();
	// delay_ms(300);
	// arrive_most_up();
	// claw_open();
	// support_turn120();

	// delay_ms(1000);

	// claw_turn0();
	// claw_open();
	// arrive_block_get();
	// delay_ms(400);
	// claw_close();
	// delay_ms(400);
	// arrive_most_up();//从地面抓起来物块并升到最高

	// stepPosition=0;   //跑
	// stepPosition1=0;  //抓
	// MOTOR_Displacement(10,0);//移动到下一个需要从地上抓取物块的地方
	// claw_turn1();
	// delay_ms(600);
	// arrive_car_put();
	// while(1)
	// {
	// 	if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
	// 	{
	// 		break;
	// 	}
		
	// }

	// claw_open1();
	// delay_ms(300);
	// arrive_most_up();
	// claw_open();
	// support_turn120();

	// delay_ms(1000);

	// claw_turn0();
	// claw_open();
	// arrive_block_get();
	// delay_ms(400);
	// claw_close();
	// delay_ms(400);
	// arrive_most_up();//从地面抓起来物块并升到最高

	// stepPosition=0;   //跑
	// stepPosition1=0;  //抓
	// MOTOR_Displacement(10,0);//移动到下一个需要从地上抓取物块的地方
	// claw_turn1();
	// delay_ms(600);
	// arrive_car_put();
	// while(1)
	// {
	// 	if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
	// 	{
	// 		break;
	// 	}
		
	// }

	// claw_open1();
	// delay_ms(300);
	// arrive_most_up();
	// claw_open();
	// support_turn120();
////////////////////////////////////

	// claw_put_block();//车上放地上  222222
	// delay_ms(1000);
	// claw_put_block();
	// delay_ms(1000);
	// claw_put_block();
	// delay_ms(1000);

	// claw_put_blockF2();//车上放二层
	// delay_ms(1000);
	// claw_put_blockF2();
	// delay_ms(1000);
	// claw_put_blockF2();
	// delay_ms(1000);

	claw_put_block2();//车上放转盘
	delay_ms(1000);
	claw_put_block2();
	delay_ms(1000);
	claw_put_block2();
	delay_ms(1000);


///车上码二层


	arrive_most_up();
	claw_open1();       
	claw_turn1();
	delay_ms(600);
	arrive_car_get();
	claw_close();
	delay_ms(300);	
	arrive_most_up(); 
	delay_ms(200);
	claw_turn0();
	delay_ms(300);
	arrive_block_putF2();//和抓物料的高度一样先
	delay_ms(500);	
	claw_open();
	delay_ms(300);
	arrive_most_up();
	support_turn120();

	arrive_most_up();
	claw_open1();       
	claw_turn1();
	delay_ms(600);
	arrive_car_get();
	claw_close();
	delay_ms(300);	
	arrive_most_up(); 
	delay_ms(200);
	claw_turn0();
	delay_ms(300);
	arrive_block_putF2();//和抓物料的高度一样先
	delay_ms(500);	
	claw_open();
	delay_ms(300);
	arrive_most_up();
	support_turn120();

	arrive_most_up();
	claw_open1();       
	claw_turn1();
	delay_ms(600);
	arrive_car_get();
	claw_close();
	delay_ms(300);	
	arrive_most_up(); 
	delay_ms(200);
	claw_turn0();
	delay_ms(300);
	arrive_block_putF2();//和抓物料的高度一样先
	delay_ms(500);	
	claw_open();
	delay_ms(300);
	arrive_most_up();
	support_turn120();





}
