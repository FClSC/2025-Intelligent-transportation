#include "system_init.h"


/*********************************************


FClSc 2025/3/15

������һ�����������Լ���LED�����

�������ջ�δ����������δ����

ؽ�����������PCBС����ض��ģ��

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
	int angle =90;
	stepPosition=0;			
	MOTOR_Angle(angle);
	while(1)
	{
		if(stepPosition == angle_temp)
		{
			break;
		}
	}	

	// ������΢������
	delay_ms(100);
	OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	OLED_Update();
	if(determicro()==1)
	{

		stepPosition=0;
		MOTOR_Angle_micro(adjust_float(global_angle,angle));
		while(1)
		{
			if(stepPosition == angle_temp)
			{
				break;
			}
		}
		OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
		OLED_Update();

	}
	delay_ms(100);

	if(determicro()==1)
	{

		stepPosition=0;
		MOTOR_Angle_micro(adjust_float(global_angle,angle));
		while(1)
		{
			if(stepPosition == angle_temp)
			{
				break;
			}
		}
		OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
		OLED_Update();

	}
	delay_ms(100);
	ResetAng_Z(); //����Z��������
	OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	OLED_Update();

    
        //  claw_get_block();
		//  delay_ms(1000);
		//  claw_put_block();
		//  delay_ms(1000);
		//  claw_put_blockF2();





	while(1)              //������
	{

    //    static int num=0;
	//    OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	//    OLED_Update();
	//    if(Key_Get()==1)
	//    {
		
	// 	num++;
    //     ResetAng_Z();//������������Z��������
		
	// 	OLED_ShowNum(16,16,num,3,OLED_8X16);
	// 	OLED_Update();
		
	//    }
	   //��������
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
