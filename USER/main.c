#include "system_init.h"


/*********************************************


FClSc 2025/4/7



ؽ����������:


1.��������⣬��Ҫ����һЩ����������Ҫ���µ���飬��Ҫ������Ƹ߶���צ���ſ��رյĽǶȣ�3/30������ɣ�δ����λ����������

2.��ɨ��ģ������ã��ĳɴ�һ��ʼ�Ϳ�ʼ���߱��б�ģ��Լ�С��������ɨ��ģ�����ӣ�������ɣ�����Ҫ�Ĵ�ӡ����������������

3.׼��������Ҫ�������Ͷ���

4.�������������и���Ż��������ǲ���������ɣ�ؽ���������ȫ��

5.�����ƶ���׼���޸ļ���

6.С���ӵĹ��ں�ɫ�������ǵİ�װ�Լ�ws2812�İ�װ����

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

int16_t base_angle = 0; //��׼�Ƕ�,������λ��Ҫ��Ƕȸ����ã�������λ������ת90�ȣ���׼�ǶȻ��90�ȣ���������ȥ90��
//Ҳ��������ڳ�ʼZ��0�ȵ�ƫ��


int main(void)
{		
	system_Init();
	contral_motor_Init();
	claw_Init();
	delay_ms(500);
	arrive_most_up();
	delay_ms(1000);
	claw_turn1();

	// delay_ms(5000);

	// base_angle +=90;
	// stepPosition=0;		
	// MOTOR_Angle(81);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }	
	// delay_ms(100);
	// MOTOR_Align(); //��̬����������������

	// base_angle -=90;
	// stepPosition=0;		
	// MOTOR_Angle(-81);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }	
	// delay_ms(100);

	// MOTOR_Align(); //��̬����������������

	// base_angle -=90;
	// stepPosition=0;		
	// MOTOR_Angle(-81);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }	
	// delay_ms(100);

	// MOTOR_Align(); //��̬����������������


	// base_angle +=90;
	// stepPosition=0;		
	// MOTOR_Angle(81);
	// while(1)
	// {
	// 	if(stepPosition == angle_temp)
	// 	{
	// 		break;
	// 	}
	// }	
	// delay_ms(100);
	// MOTOR_Align(); //��̬����������������




	
	while(1)              //������
	{

		OLED_Printf(0,0,OLED_8X16,"Angle=%.3f",global_angle);
		OLED_Printf(0,16,OLED_8X16,"BaseAngle=");
		OLED_ShowSignedNum(64,16,base_angle,3,OLED_8X16);
		OLED_Printf(0,32,OLED_8X16,"Err_Angle=%.3f",global_angle-base_angle);
		OLED_Printf(0,48,OLED_8X16,"Code=");
        OLED_Printf(64,48,OLED_8X16,UART5_RX_BUF);
		OLED_Update();


		if(Key_Get() == 1)//һ��������������£������ػ���������ָ��
		{
			base_angle = 0;
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
