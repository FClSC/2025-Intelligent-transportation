#include "system_init.h"


/*********************************************


FClSc 2025/1
*********************************************/

// volatile float global_angle = 0.0;  //偏航角
// // volatile float angular_velocity_y = 0.0; //y方向角速度
// // volatile float angular_velocity_z = 0.0; //z方向角速度
// volatile uint8_t new_data_received = 0;  //新数据接收标志位
// uint8_t received_data_packet[11] = {0};   //接收到的数据包



int main(void)
{		
	system_Init();
	contral_motor_Init();
	claw_Init();
	claw_turn0();
	claw_open();
 	arrive_most_up();
	claw_turn1();
	delay_ms(1000);

	



	
	//test


    
        //  claw_get_block();
		//  delay_ms(1000);
		//  claw_put_block();
		//  delay_ms(1000);
		//  claw_put_blockF2();





	while(1)              //主代码
	{


	//   if(new_data_received)//接收到了新的数据
	//   {
		  
        
    //    OLED_ShowFloatNum(0,16,global_angle,3,4,OLED_8X16);
	//    OLED_Update();
    //    delay_s(6);
	//    ResetAng_Z();
	// 	  new_data_received=0;				
	//   }
	  
  


      if(Serial2_GetRxFlag() == 1)//串口屏，接收到串口屏的点按指示，发送启动指令
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
