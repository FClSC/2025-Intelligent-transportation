#include "system_init.h"


/*********************************************
����ͷλ��

ץȡ��λ��


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







	


    






	
//	while(1)                   //���Դ���
//	{
////		if(click0() == 1)
////		if(clickKEY2()==1)
////		{
////			claw_open();                //צ���ſ�
////			claw_close();                //צ�ӱպ�
////			arrive_most_up();                //�������λ��
////			arrive_camera();                //��������ͷλ��
////			arrive_block_get();              //����ץȡ����λ��
////			arrive_block_wait();              //�����ȴ�����λ��
////			arrive_block_put();              //������͵�һ���������λ��
////			arrive_block_put2();              //������� 2                     2   555eee2eeeeeee eee�ڶ����������λ��
////			arrive_block_down();              //��������̨��������λ��
////			arrive2_circle_capture();              //��������ʶ���һ���λ��
////			arrive2_circle_capture2();              //��������ʶ���һ���λ��
////			claw_put_block3();                      //���ӹ����ڶ���ľ�����
////		  arrive_circle_capture2();               //���ӹ����ڶ������ʶ��
////		
////			break;
////		}
//		
////		claw_turn0();
//		
//	}


	 	// �ȴ���λ����ʼ����ɣ�С����
//	while(1)
//	{
//		if(Serial1_GetRxFlag() == 1)
//		{
//			if(Serial_RXPacket[0]==0xFD)
//			{
//				ws2812_AllOpen(255,255,255);//�������е�
//				delay_ms(200);
//				break;
//			}
//		}
//	}


//	// �ȴ��û����°�������λ������
//	while(1)                
//	{
//		if(click0() == 1)               //����32�����ϵİ������е����ȽϷ���
//		{
//			delay_ms(20);
//			UART_SendPacket2UP(0x01);
//			break;
//		}
//////		if(clickKEY1() == 1)          //�����ȡ��ע�;���pcb�����ϵİ���
//////		{
//////			delay_ms(20);
//////			UART_SendPacket2UP(0x01);
//////			break;
//////		}
//	}
//	while(1)              //������
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
//		if(Serial2_GetRxFlag() == 1)               //����32�����ϵİ������е����ȽϷ���
//		{
//			delay_ms(20);
//			UART_SendPacket2UP(0x02);
//			UART_SendPacket2UP(0x02);
//			UART_SendPacket2UP(0x02);
//			break;
//		}
//	}
	while(1)              //������
	{
     

        if(Serial2_GetRxFlag() == 1)//������
			{
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);
				UART_SendPacket2UP(0x02);

			
				//MSD_Move2(100,1,1,2);
			}

		if(Serial1_GetRxFlag() == 1)//������ݮ����Ϣ
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
