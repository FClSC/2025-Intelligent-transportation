#include "system_init.h"


/*********************************************


FClSc 2025/4/15

一些问题：
比赛第一天（非初赛的一天）：到达现场报道
1.能否在正式比赛的场地上进行调试？能否测量其场地上二维码的位置或者转盘高度？
2.在回校前是否要把车上交且封存？
3.是否是检录完即封车上交？


比赛第二天（初赛与创新实践环节）：
1.是否只有在比赛开始前才能拿到自己的车？
2.是否只有比赛时候发车前的4分钟是调试时间？别的时候均不允许调试？
3.是否在初赛结束后就不用交车，等待进入创新实践环节，进入社区？
4.创新实践环节是否严格限制互联网连接？不允许使用自己的手机？只能电脑连接社区的网络？
5.环节结束后，在15分钟调试时间（去年是这样）使用之后立马交车封存，等到第二天直接进行决赛，对吗？

比赛第三天（决赛）：




亟待进行事项:


1.面对新赛题，需要增加一些动作，最主要是新的物块，需要独立设计高度与爪子张开关闭的角度，3/30基本完成，未在上位机建立动作

2.新扫码模块的配置，改成从一开始就开始或者变成斜的，以及小板子上新扫码模块的添加（基本完成），目前偶尔会出现传给上位机没东西的情况
建议添加预案：如果上位机没有要到东西直接内置顺序
或许改为上位机调用扫码后立即问我要（以前的方式）会改变更好

3.准备比赛需要的器件和东西

4.长距离位移爪子收起来动的动作

5.脉冲移动不准，修改计算

6.小板子的关于黑色大陀螺仪的安装以及ws2812的安装测试

8.二维码位置和转盘位置不确定

11.物流转盘抓完最后一个物块之后立马走

9.高度改为软件修改

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

	// claw_get_block();//地上放车上
	// delay_ms(1000);
	// claw_get_block();
	// delay_ms(1000);
	// claw_get_block();
	// delay_ms(1000);

	// claw_put_block();//车上放地上
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

    
	


// //圆盘抓跑
// 		claw_turn0();
// 		arrive_block_get1();
// 		delay_ms(200);
// 		claw_close();
// 		delay_ms(200);

// 		stepPosition=0;   //跑
// 		stepPosition1=0;  //抓
// 		arrive_most_up();  //升到最高
// 		MOTOR_Displacement(30,0);  //先厘米级别的移动
// 		claw_turn1();   //收回爪子
// 		delay_ms(400);
// 		arrive_car_put();
// 		claw_open1();
// 		delay_ms(200);
// 		arrive_most_up();
// 		support_turn120();
// 		while(1)
// 		{
// 			if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
// 			{
// 				break;
// 			}
// 		}

// //码垛，收跑
// 		arrive_most_up();
// 		claw_open1();       
// 		claw_turn1();
// 		delay_ms(600);
// 		arrive_car_get();
// 		claw_close();
// 		delay_ms(300);	
// 		arrive_most_up(); 
// 		delay_ms(200);
// 		claw_turn0();
// 		delay_ms(300);
// 		arrive_put_down2();
// 		delay_ms(200);	
// 		claw_open();
// 		delay_ms(300);
// 		arrive_most_up();
// 		//放置物块流程
// 		//离开并收回爪子
// 		MOTOR_Displacement(50,0);  //先厘米级别的移动
// 		delay_ms(200);  //先执行跑的在执行升降的
// 		claw_turn1();   //收回爪子
// 		support_turn120();
// 		while(1)
// 		{
// 			if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
// 			{
// 				break;
// 			}
// 		}

// 		delay_ms(2000); //等待2秒钟，给上位机发送数据

// //边旋转边转爪子
// 			stepPosition=0;   //转
// 			stepPosition1=0;  //升降
// 			MOTOR_Angle(81);
// 			delay_ms(200);  //
// 			claw_turn0();
// 			delay_ms(200);  //先执行跑的在执行升降的
// 			arrive_circle_capture();  //这个是靶心识别高度
// 			while(1)
// 			{
// 				if((stepPosition == angle_temp)&&(stepPosition1 == distance1))   //两个都完成
// 				{
// 					break;
// 				}
// 			}
	

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
