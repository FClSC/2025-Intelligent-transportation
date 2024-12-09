#include "system_init.h"


/*********************************************
摄像头位置

抓取的位置


1 3 4 7 8 5

*********************************************/


int main(void)
{		
	system_Init();
	contral_motor_Init();


    

	//claw_Init();
   	// delay_ms(1000);	
	// arrive_most_up();
	// delay_ms(1000);	
	// claw_turn3();
	// delay_ms(1000);	
	// claw_open();
	// delay_ms(1000);	

	//UART5_Start_Scan();
	//uint8_t Order[9]={0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0xAB,0xCD};
   // UART2_SendArray(Order,9);



	//UART2_SendArray(Order,9);
	//UART5_Start_Scan();
	//UART2_SendArray(Order,9);
	//delay_ms(3000);
	//UART2_SendArray(Order,9);


		delay_ms(3000);
		
		OLED_Clear();
		UART5_Start_Scan();
		delay_ms(1000);
		if(Serial5_GetRxFlag() == 1)
		{
           OLED_ShowString(0,0,UART5_RX_BUF,6);
			OLED_Update();
		}







	


    






	
//	while(1)                   //调试代码
//	{
////		if(click0() == 1)
////		if(clickKEY2()==1)
////		{
////			claw_open();                //爪子张开
////			claw_close();                //爪子闭合
////			arrive_most_up();                //升到最高位置
////			arrive_camera();                //升到摄像头位置
////			arrive_block_get();              //升到抓取物块的位置
////			arrive_block_wait();              //升到等待物块的位置
////			arrive_block_put();              //升到最低第一层放置物块的位置
////			arrive_block_put2();              //升到最低 2                     2   555eee2eeeeeee eee第二层放置物块的位置
////			arrive_block_down();              //升到载物台放置物块的位置
////			arrive2_circle_capture();              //升到靶心识别第一层的位置
////			arrive2_circle_capture2();              //升到靶心识别第一层的位置
////			claw_put_block3();                      //精加工区第二层木板放置
////		  arrive_circle_capture2();               //精加工区第二层靶心识别
////		
////			break;
////		}
//		
////		claw_turn0();
//		
//	}


	 	// 等待上位机初始化完成，小灯亮
//	while(1)
//	{
//		if(Serial1_GetRxFlag() == 1)
//		{
//			if(Serial_RXPacket[0]==0xFD)
//			{
//				ws2812_AllOpen(255,255,255);//点亮所有灯
//				delay_ms(200);
//				break;
//			}
//		}
//	}


//	// 等待用户按下按键，上位机启动
//	while(1)                
//	{
//		if(click0() == 1)               //先用32板子上的按键进行调，比较方便
//		{
//			delay_ms(20);
//			UART_SendPacket2UP(0x01);
//			break;
//		}
//////		if(clickKEY1() == 1)          //把这个取消注释就是pcb板子上的按键
//////		{
//////			delay_ms(20);
//////			UART_SendPacket2UP(0x01);
//////			break;
//////		}
//	}
//	while(1)              //主代码
//		{
//			if(Serial2_GetRxFlag() == 1)
//			{
//				UART_SendPacket2UP(0x02);
//				UART_SendPacket2UP(0x02);
//				UART_SendPacket2UP(0x02);
//				UART_SendPacket2UP(0x02);
//				break;
//			}
//		}
//  while(1)                
//	{
//		if(Serial2_GetRxFlag() == 1)               //先用32板子上的按键进行调，比较方便
//		{
//			delay_ms(20);
//			UART_SendPacket2UP(0x02);
//			UART_SendPacket2UP(0x02);
//			UART_SendPacket2UP(0x02);
//			break;
//		}
//	}
	while(1)              //主代码
	{
     

        if(Serial2_GetRxFlag() == 1)//串口屏
			{
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);

			
				//MSD_Move2(100,1,1,2);
			}

		if(Serial1_GetRxFlag() == 1)//接收树莓派消息
		{
			uart_handle();
			UART_SendPacket2UP(0x01);
		}
	}	 
} 

void test(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	
	
	// dir
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	// stp
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
	// enm
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);		
	
	GPIO_ResetBits(GPIOG,GPIO_Pin_7);
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_5);	
	
	while(1)
	{
		MOTOR_STEP3=1;
		delay_us(400);
		MOTOR_STEP3=0;
		delay_us(400);
	}
}
