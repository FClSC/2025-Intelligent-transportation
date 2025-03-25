#include "system_init.h"


/*********************************************


FClSc 2025/3/15



ؽ����������:
1. PCBС����ض��ģ��,�������ϵ���

2. һ����������,LED�����,OLED������Ҫ������������Ӧ�³�,�Լ���Щ�������³�����ĳ���׶��еĵ��ô���

3. Ϊ�˷�������߶�,��Ҫ���߶ȵ���������,��Ӧ�����ʵ���ʵ�߶�

4. �������ڰ���ʶ���ʱ��У׼��̬:��Ҫ�������һ��ģʽ������ 0x0X

5.��������⣬��Ҫ����һЩ����������ѳ��ϵ����ŵ�ת�̣����������ɫ�Ǻ죬Ԥ����һ������������ɫ������ȥ

Ŀǰ������������ת90�������0.1-0.4��֮��,����ת���ٶȱ�������


�ɲ���һ�׵�ͨ�˲��������������ݽ��д���,�Լ�С���
// ʾ����һ�׵�ͨ�˲�




// ȫ�ֱ���
float filtered_angle = 0.0;
float alpha = 0.1; // �˲�ϵ����0.1~0.3��

// ��UART4_IRQHandler�����ݽ���������
void ParseData(uint8_t *data, uint16_t length) {
    // ... ԭʼ�����߼� ...
    float raw_angle = ((float)yaw) / 32768.0 * 180.0; // ԭʼ�Ƕ�
    filtered_angle = alpha * raw_angle + (1 - alpha) * filtered_angle; // һ�׵�ͨ�˲�
    global_angle = filtered_angle; // ����ȫ�ֽǶ�
}



*********************************************/

// volatile float global_angle = 0.0;  //ƫ����
// // volatile float angular_velocity_y = 0.0; //y������ٶ�
// // volatile float angular_velocity_z = 0.0; //z������ٶ�
// volatile uint8_t new_data_received = 0;  //�����ݽ��ձ�־λ
// uint8_t received_data_packet[11] = {0};   //���յ������ݰ�

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
	// ResetAng_Z(); //����Z��������
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





	while(1)              //������
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
	  
		if(Key_Get() == 1)//һ��������������£�����ݮ�ɷ�������ָ��
		{
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);
			UART_SendPacket2UP(0x02);

			
		}  
     

    //   if(Serial2_GetRxFlag() == 1)//�����������յ��������ĵ㰴ָʾ����������ָ��
	// 		{
	// 			UART_SendPacket2UP(0x02);
	// 			UART_SendPacket2UP(0x02);
	// 			UART_SendPacket2UP(0x02);
	// 			UART_SendPacket2UP(0x02);
				
	// 		}

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
