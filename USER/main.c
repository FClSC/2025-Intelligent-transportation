#include "system_init.h"


/*********************************************


FClSc 2025/1
*********************************************/

// volatile float global_angle = 0.0;  //ƫ����
// // volatile float angular_velocity_y = 0.0; //y������ٶ�
// // volatile float angular_velocity_z = 0.0; //z������ٶ�
// volatile uint8_t new_data_received = 0;  //�����ݽ��ձ�־λ
// uint8_t received_data_packet[11] = {0};   //���յ������ݰ�



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





	while(1)              //������
	{


	//   if(new_data_received)//���յ����µ�����
	//   {
		  
        
    //    OLED_ShowFloatNum(0,16,global_angle,3,4,OLED_8X16);
	//    OLED_Update();
    //    delay_s(6);
	//    ResetAng_Z();
	// 	  new_data_received=0;				
	//   }
	  
  


      if(Serial2_GetRxFlag() == 1)//�����������յ��������ĵ㰴ָʾ����������ָ��
			{
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);
				
			}

		if(Serial1_GetRxFlag() == 1)//������ݮ����Ϣ
		{
			uart_handle();
			UART_SendPacket2UP(0x01);
		}
		
	}	 
	
} 


void test(void) //���Գ���
{
     



}
