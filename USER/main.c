#include "system_init.h"


/*********************************************


FClSc 2025/4/15

һЩ���⣺
������һ�죨�ǳ�����һ�죩�������ֳ�����
1.�ܷ�����ʽ�����ĳ����Ͻ��е��ԣ��ܷ�����䳡���϶�ά���λ�û���ת�̸߶ȣ�
2.�ڻ�Уǰ�Ƿ�Ҫ�ѳ��Ͻ��ҷ�棿
3.�Ƿ��Ǽ�¼�꼴�⳵�Ͻ���


�����ڶ��죨�����봴��ʵ�����ڣ���
1.�Ƿ�ֻ���ڱ�����ʼǰ�����õ��Լ��ĳ���
2.�Ƿ�ֻ�б���ʱ�򷢳�ǰ��4�����ǵ���ʱ�䣿���ʱ�����������ԣ�
3.�Ƿ��ڳ���������Ͳ��ý������ȴ����봴��ʵ�����ڣ�����������
4.����ʵ�������Ƿ��ϸ����ƻ��������ӣ�������ʹ���Լ����ֻ���ֻ�ܵ����������������磿
5.���ڽ�������15���ӵ���ʱ�䣨ȥ����������ʹ��֮����������棬�ȵ��ڶ���ֱ�ӽ��о���������

���������죨��������




ؽ����������:


1.��������⣬��Ҫ����һЩ����������Ҫ���µ���飬��Ҫ������Ƹ߶���צ���ſ��رյĽǶȣ�3/30������ɣ�δ����λ����������

2.��ɨ��ģ������ã��ĳɴ�һ��ʼ�Ϳ�ʼ���߱��б�ģ��Լ�С��������ɨ��ģ�����ӣ�������ɣ���Ŀǰż������ִ�����λ��û���������
�������Ԥ���������λ��û��Ҫ������ֱ������˳��
�����Ϊ��λ������ɨ�����������Ҫ����ǰ�ķ�ʽ����ı����

3.׼��������Ҫ�������Ͷ���

4.������λ��צ�����������Ķ���

5.�����ƶ���׼���޸ļ���

6.С���ӵĹ��ں�ɫ�������ǵİ�װ�Լ�ws2812�İ�װ����

8.��ά��λ�ú�ת��λ�ò�ȷ��

11.����ת��ץ�����һ�����֮��������

9.�߶ȸ�Ϊ����޸�

7.�������esp8266���͵������룬ֱ�ӵȴ����ڼ��ɣ�Ŀǰ�����UDPЭ�飬TCP�ȴ����
��Ϊ
			while(1)//���û�н��յ����ݾ�һֱ�ȴ�
			{
				if(Serial5_GetRxFlag() == 1)//���յ������ݾʹ���
				{
					int16_t code1 =0; 
					int16_t code2 =0; 	
					delay_ms(300);//�ȴ����ݽ�����ȫ
					UART5_ParseCode(UART5_RX_BUF,&code1,&code2);//��������ά�����ݣ���ʱUART5_BUX����Ȼ��ŵ��Ƕ�ά������	
					u2_printf("tt3.txt=\"%d+%d\"",code1,code2);//��η��͸�������
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


�ɲ���һ�׵�ͨ�˲��������������ݽ��д���,�Լ�С���
// ʾ����һ�׵�ͨ�˲�
// ȫ�ֱ���
+float filtered_angle = 0.0;
float alpha = 0.1; // �˲�ϵ����0.1~0.3��

// ��UART4_IRQHandler�����ݽ���������
void ParseData(uint8_t *data, uint16_t length) {
    // ... ԭʼ�����߼� ...
    float raw_angle = ((float)yaw) / 32768.0 * 180.0; // ԭʼ�Ƕ�
    filtered_angle = alpha * raw_angle + (1 - alpha) * filtered_angle; // һ�׵�ͨ�˲�
    global_angle = filtered_angle; // ����ȫ�ֽǶ�
}


*********************************************/

void test(void); //���Ժ���

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

	// claw_get_block();//���Ϸų���
	// delay_ms(1000);
	// claw_get_block();
	// delay_ms(1000);
	// claw_get_block();
	// delay_ms(1000);

	// claw_put_block();//���Ϸŵ���
	// delay_ms(1000);
	// claw_put_block();
	// delay_ms(1000);
	// claw_put_block();
	// delay_ms(1000);

	// claw_put_blockF2();//���ϷŶ���
	// delay_ms(1000);
	// claw_put_blockF2();
	// delay_ms(1000);
	// claw_put_blockF2();
	// delay_ms(1000);

    
	


// //Բ��ץ��
// 		claw_turn0();
// 		arrive_block_get1();
// 		delay_ms(200);
// 		claw_close();
// 		delay_ms(200);

// 		stepPosition=0;   //��
// 		stepPosition1=0;  //ץ
// 		arrive_most_up();  //�������
// 		MOTOR_Displacement(30,0);  //�����׼�����ƶ�
// 		claw_turn1();   //�ջ�צ��
// 		delay_ms(400);
// 		arrive_car_put();
// 		claw_open1();
// 		delay_ms(200);
// 		arrive_most_up();
// 		support_turn120();
// 		while(1)
// 		{
// 			if((stepPosition == distance)&&(stepPosition1 == distance1))   //���������
// 			{
// 				break;
// 			}
// 		}

// //��⣬����
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
// 		//�����������
// 		//�뿪���ջ�צ��
// 		MOTOR_Displacement(50,0);  //�����׼�����ƶ�
// 		delay_ms(200);  //��ִ���ܵ���ִ��������
// 		claw_turn1();   //�ջ�צ��
// 		support_turn120();
// 		while(1)
// 		{
// 			if((stepPosition == distance)&&(stepPosition1 == distance1))   //���������
// 			{
// 				break;
// 			}
// 		}

// 		delay_ms(2000); //�ȴ�2���ӣ�����λ����������

// //����ת��תצ��
// 			stepPosition=0;   //ת
// 			stepPosition1=0;  //����
// 			MOTOR_Angle(81);
// 			delay_ms(200);  //
// 			claw_turn0();
// 			delay_ms(200);  //��ִ���ܵ���ִ��������
// 			arrive_circle_capture();  //����ǰ���ʶ��߶�
// 			while(1)
// 			{
// 				if((stepPosition == angle_temp)&&(stepPosition1 == distance1))   //���������
// 				{
// 					break;
// 				}
// 			}
	

	while(1)              //������
	{

		OLED_Printf(0,0,OLED_8X16,"Angle=%.3f",global_angle);
		OLED_Printf(0,16,OLED_8X16,"BaseAngle=");
		OLED_ShowSignedNum(64,16,base_angle,3,OLED_8X16);
		OLED_Printf(0,32,OLED_8X16,"Err_Angle=%.3f",global_angle-base_angle);
		OLED_Printf(0,48,OLED_8X16,"Code=");
        OLED_Printf(64,48,OLED_8X16,UART5_RX_BUF);
		OLED_Update();


		if(Key_Get() == 1)//һ��������������£������ػ���������ָ�ͬʱ��Ŀ��Ƕ�Ϊ0
		{
			base_angle = 0;
			// arrive_camera();//��͸߶�
			// delay_ms(2000);
			// arrive_color_reco();//������ɫʶ��߶�
			// delay_ms(2000);
			// arrive_block_get1();//����ת����ץ���ĸ߶�
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
     
		if(Serial1_GetRxFlag() == 1)//������ݮ����Ϣ
		{
			uart_handle();
			UART_SendPacket2UP(0x01);
		}

		if(Serial5_GetRxFlag() == 1)//������յ���ɨ�뷢�������ݾʹ���
		{
			int16_t code1 =0; 
			int16_t code2 =0; 	
			delay_ms(300);//�ȴ����ݽ�����ȫ
			UART5_ParseCode(UART5_RX_BUF,&code1,&code2);//��������ά�����ݣ���ʱUART5_BUX����Ȼ��ŵ��Ƕ�ά������	
			u2_printf("tt3.txt=\"%d+%d\"",code1,code2);//��η��͸�������
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


void test(void) //���Գ���
{
	claw_get_block1();//ת�̷ų���
	delay_ms(1000);
	claw_get_block1();
	delay_ms(1000);
	claw_get_block1();
	delay_ms(1000);

	claw_get_block();//���Ϸų���
	delay_ms(1000);
	claw_get_block();
	delay_ms(1000);
	claw_get_block();
	delay_ms(1000);

	claw_put_block();//���Ϸŵ���
	delay_ms(1000);
	claw_put_block();
	delay_ms(1000);
	claw_put_block();
	delay_ms(1000);

	claw_put_blockF2();//���ϷŶ���
	delay_ms(1000);
	claw_put_blockF2();
	delay_ms(1000);
	claw_put_blockF2();
	delay_ms(1000);

	claw_put_block2();//���Ϸ�ת��
	delay_ms(1000);
	claw_put_block2();
	delay_ms(1000);
	claw_put_block2();
	delay_ms(1000);



}
