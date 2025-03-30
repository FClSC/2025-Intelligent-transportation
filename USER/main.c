#include "system_init.h"


/*********************************************


FClSc 2025/3/30



ؽ����������:
1.Ŀǰ�ĳ���צ���ŵ�����Ų��ˣ�Ϊ�˷�ֹ�򵽣���Ҫ��װ���

2.�������Ż���Ŀǰ���յ���ά����һ��0+0������123+321������Ҫ������Ĵ�

3. Ϊ�˷�������߶�,��Ҫ���߶ȵ���������,��Ӧ�����ʵ���ʵ�߶ȣ�������ת��80-100mm�Ķ���

4.��������⣬��Ҫ����һЩ����������Ҫ���µ���飬��Ҫ������Ƹ߶���צ���ſ��رյĽǶȣ�3/30������ɣ�δ����λ����������

5.��ɨ��ģ������ã��ĳɴ�һ��ʼ�Ϳ�ʼ���߱��б�ģ��Լ�С��������ɨ��ģ������

6.׼��������Ҫ�������Ͷ���

7.�������������и���Ż���������Ҫ������3.30����

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

float Angle_Err=0;

int main(void)
{		
	system_Init();
	contral_motor_Init();
	claw_Init();
	delay_ms(1000);
	arrive_most_up();
	delay_ms(1000);
	claw_turn1();

    // claw_get_block();
	// delay_ms(1000);
	// claw_get_block();
	// delay_ms(1000);
	// claw_put_block();
	// delay_ms(1000);
	// claw_put_block();
	// delay_ms(1000);
	// claw_put_blockF2();
	// delay_ms(1000);
	// claw_put_blockF2();
	// delay_ms(1000);
	// arrive_color_reco();
	// delay_ms(5000);

	// claw_get_block1();
	// delay_ms(1000);
	// claw_get_block1();
	// delay_ms(1000);
	// delay_ms(5000);
	// claw_put_block2();
	// delay_ms(1000);
	// claw_put_block2();
	// delay_ms(1000);


	




	while(1)              //������
	{

		OLED_Printf(0,32,OLED_8X16,"Angle==%.3f",global_angle);
		OLED_ShowString(0,48,"Yess",OLED_8X16);
    	OLED_ShowFloatNum(0,16,Angle_Err,3,1,OLED_8X16);
		OLED_Update();




	  
		if(Key_Get() == 1)//һ��������������£�����ݮ�ɷ�������ָ��
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
