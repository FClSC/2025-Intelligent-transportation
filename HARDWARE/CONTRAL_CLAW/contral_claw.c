#include "contral_claw.h"

CLAW_POSITION claw;
/********************
�������� : צ��λ�ú���  ��λmm

������� : ��
������� ����
ֱ�� 16mm 
תһȦ  8*2*3.14=50.24 
x/mm = 3200/50.24
x = 64*mm   1mm��Ҫ64������
**********************/
void claw_position(int16_t position)
{
	uint32_t pulse=0;
	claw.position_now = claw.position_now + position; // ���µ�ǰλ��
	
	if(claw.position_now<0 || claw.position_now>265)
	{
		claw.position_now=claw.position_now - position;
	}
	else
	{
		// ����
		if(position>0)
		{
				Motor1_DIR(1);   // ����
		}
		else
		{
				position=-position;
				Motor1_DIR(0);   // ����
		}
		pulse=(64*position);
		distance1=pulse;
		stepPosition1=0;
		MSD_Move1(pulse,50,50,100);
		while(1)
		{
			if(stepPosition1 == distance1)
			{
				break;
			}
		}
	}
}
/********************
�������� : צ��λ�ú���  ��λmm
������� : ��
������� ����
�Ƿ�������ⲿ����
*********/
void claw_position2(int16_t position)
{
	uint32_t pulse=0;
	claw.position_now = claw.position_now + position; // ���µ�ǰλ��
	if(claw.position_now<0 || claw.position_now>265)
	{
		claw.position_now=claw.position_now - position;
	}
	else
	{
		// ����
		if(position>0)
		{
				Motor1_DIR(1);   // ����
		}
		else
		{
				position=-position;
				Motor1_DIR(0);   // ����
		}
		pulse=(64*position);
		distance1=pulse;
		stepPosition1=0;
		MSD_Move1(pulse,36,36,45);
	}
}


/********************
�������� : ��������ͷ��λ��
������� : ��
������� ����
**********************/
void arrive_camera(void)
{
	claw.position_target = camera_position;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}
/********************
�������� : ��������ͷ��λ��
������� : ��
������� ����
�Ƿ�������ⲿ����
**********************/
void arrive_camera2(void)
{
	claw.position_target = camera_position;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position2(claw.position_temp);
}
/********************
�������� : ����ץ���Ͽ��λ�� ������̨ץ���ĸ߶�
������� : ��
������� ����
**********************/
void arrive_block_get1(void)
{
	claw.position_target = claw_block_get1;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : ����ץ���Ͽ��λ��
������� : ��
������� ����
**********************/
void arrive_block_get(void)
{
	claw.position_target = claw_block_get;//����߶�
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : ��������������ڶ���ĸ߶�
������� : ��
������� ����
**********************/
void arrive_block_putF2(void)
{
	claw.position_target = claw_block_get2;  //���ڶ���
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}
/********************
�������� : ����ץ���Ͽ��λ�� �ڶ���
������� : ��
������� ����
**********************/
void arrive_block_get3(void)
{
	claw.position_target = claw_block_get3;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}
/********************
�������� : ��������Ͽ��λ��
������� : ��
������� ����
**********************/
void arrive_block_put(void)
{
	claw.position_target = get_block_down;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : ��������Ͽ��λ��  �ŵڶ���
������� : ��
������� ����
**********************/
//void arrive_block_put2(void)
//{
//	claw.position_target = claw_block_put2;
//	claw.position_temp = claw.position_target - claw.position_now;
//	claw_position(claw.position_temp);
//}
///********************
//�������� : ��������Ͽ��λ��  �ŵڶ���
//������� : ��
//������� ����
//**********************/
//void arrive_block_put3(void)
//{
//	claw.position_target = claw_block_put3;
//	claw.position_temp = claw.position_target - claw.position_now;
//	claw_position(claw.position_temp);
//}
/********************
�������� : �������
������� : ��
������� ����
**********************/
void arrive_most_up(void)
{
	claw.position_target = claw_most_up;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}
/********************
�������� : ��ת�������Ͽ�ŵ����ϵ�λ��
������� : ��
������� ����
**********************/
void arrive_block_down(void)
{
	claw.position_target = get_block_down;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);	
}

/********************
�������� : ������ʶ���λ��
������� : ��
������� ����
**********************/
void arrive_circle_capture(void)
{
	claw.position_target = circle_capture1;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);	
}
//void arrive2_circle_capture(void)
//{
//	claw.position_target = circle_capture1;
//	claw.position_temp = claw.position_target - claw.position_now;
//	claw_position2(claw.position_temp);	
//}
/********************
�������� : �������̰���ʶ���λ��2
������� : ��
������� ����
**********************/
void arrive_circle_capture2(void)
{
	claw.position_target = circle_capture2;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);	
}
//void arrive2_circle_capture2(void)
//{
//	claw.position_target = circle_capture2;
//	claw.position_temp = claw.position_target - claw.position_now;
//	claw_position2(claw.position_temp);	
//}


///********************
//�������� : ����ת��ʶ���ɫ��ĸ߶�
//������� : ��
//������� ����
//**********************/
//void arrive_circle_capture3(void)
//{
//	claw.position_target = circle_capture3;
//	claw.position_temp = claw.position_target - claw.position_now;
//	claw_position(claw.position_temp);	
//}
//void arrive2_circle_capture3(void)
//{
//	claw.position_target = circle_capture3;
//	claw.position_temp = claw.position_target - claw.position_now;
//	claw_position2(claw.position_temp);	
////}
///********************
//�������� : צ�Ӱ����ŵ�����̨   ��ת��ץ
//������� : ��
//������� ����
//**********************/
//void claw_get_block(void)
//{
////	arrive_block_get();  //160
////	delay_ms(200);
//	claw_close(); 
//	delay_ms(500);
//	arrive_most_up();    //195 
//	claw_turn129(); 
//	delay_ms(200);
//	delay_ms(500); 
//	arrive_block_down(); //130 
//	claw_open();
//	delay_ms(500); 
//	arrive_most_up();    //173 
//	claw_turn0();
//	delay_ms(200);
//	delay_ms(500);
//	support_turn120();
//	delay_ms(100);
//	arrive_block_get(); 
//}

///********************
//�������� : צ�Ӱ����ŵ�����̨   �ӵ���ץ
//������� : ��
//������� ����
//**********************/
//void claw_get_block2(void)
//{
//	//claw_turn0();
//	arrive_block_put();   //0
//	claw_close();
//	delay_ms(200);
//	arrive_most_up();     //173
//	delay_ms(200);
//	claw_turn129();
//	delay_ms(400);
//	arrive_block_down();  //130
//	claw_open();
//	arrive_most_up();     //173
//	claw_turn0();
//	delay_ms(200);
//	support_turn120();	
//	delay_ms(100);
//	
//}

///*****************
//�������� : צ�Ӱ�����ó�����̨ �ŵ���һ��
//������� : ��
//������� ����
//**********************/
//void claw_put_block(void)
//{
//	arrive_most_up();       
//	claw_turn129();
//	delay_ms(300);
//	arrive_block_down();
//	claw_close();
//	delay_ms(300);	
//	arrive_most_up(); 
//	delay_ms(500);
//	claw_turn0();
//	delay_ms(300);
//	support_turn120();
//	arrive_block_put(); 
//	delay_ms(300);	
//	claw_open();
//	delay_ms(300);
//}

///********************
//�������� : צ�Ӱ�����ó�����̨ �ŵ��ڶ���
//������� : ��
//������� ����
//**********************/
//void claw_put_block2(void)
//{
//	//claw_open();
//	arrive_most_up();       
//	claw_turn129();
//	delay_ms(200);
//	arrive_block_down();
//	claw_close();
//	delay_ms(300);
//	arrive_most_up();   
//	claw_turn0();
//	delay_ms(300);
//	support_turn120();
//	arrive_block_put2(); 
//	delay_ms(300);	
//	claw_open();
//	delay_ms(300);
//}
///********************
//�������� : צ�Ӱ�����ó�����̨ �ŵ��ڶ���ƽ̨��
//������� : ��
//������� ����
//**********************/
//void claw_put_block3(void)
//{
//	claw_open();
//	arrive_most_up();       
//	claw_turn129();
//	delay_ms(200);
//	arrive_block_down();
//	claw_close();
//	delay_ms(300);
//	arrive_most_up();   
//	claw_turn0();
//	delay_ms(300);
//	support_turn120();
//	arrive_block_put3(); 
//	delay_ms(300);	
//	claw_open();
//	delay_ms(300);
//}
///********************
//�������� : ��λ
//������� : ��
//������� ����
//**********************/
//void claw_back(void)
//{   
//	arrive_most_up();
//	delay_ms(200);
//	claw_turn129();
//	delay_ms(200);
//  support_turn67();
//}
/********************
�������� : צ�Ӱ����ŵ�����̨   
������� : ��
������� ����
**********************/
void claw_get_block1(void)
{
	arrive_block_get();
	claw_close();
	delay_ms(200);
	arrive_most_up();
	delay_ms(200);
	claw_turn1();
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	arrive_block_put();
	delay_ms(300);
	claw_open();
	 arrive_most_up();
	claw_turn0();
	claw_open();
	delay_ms(200);
}
/********************
�������� : צ�Ӱ����ŵ�����̨   
������� : ��
������� ����
**********************/
void claw_get_block2(void)
{
	arrive_block_get();
	claw_close();
	delay_ms(200);
	arrive_most_up();
	delay_ms(200);
	claw_turn2();
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	arrive_block_put();
	delay_ms(300);
	claw_open();
	 arrive_most_up();
	claw_turn0();
	claw_open();
	delay_ms(200);

}
/********************
�������� : צ�Ӱ����ŵ�����̨
������� : ��
������� ����
**********************/
void claw_get_block3(void)
{
	arrive_block_get();
	claw_close();
	delay_ms(200);
	arrive_most_up();
	delay_ms(200);
	claw_turn3();
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	arrive_block_put();
	delay_ms(300);
	claw_open();
	arrive_most_up();
	claw_turn0();
	claw_open();
	delay_ms(200);
}
/********************
�������� : צ�Ӱ����ŵ�����̨ 
������� : ��
������� ����
**********************/
void claw_get_block4(void)
{
	claw_turn0();
	delay_ms(200);
	arrive_block_get1();
	claw_close();
	delay_ms(200);
	arrive_most_up();
	delay_ms(200);
	claw_turn1();
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	arrive_block_put();
	delay_ms(300);
	claw_open();
	arrive_most_up();
	delay_ms(300);
	claw_turn0();
	delay_ms(300);
	arrive_circle_capture2();
	claw_open();
	delay_ms(200);
}
/********************
�������� : צ�Ӱ����ŵ�����̨ 
������� : ��
������� ����
**********************/
void claw_get_block5(void)
{
	claw_turn0();
	delay_ms(200);
	arrive_block_get1();
	claw_close();
	delay_ms(200);
	arrive_most_up();
	delay_ms(200);
	claw_turn2();
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	arrive_block_put();
	delay_ms(300);
	claw_open();
	arrive_most_up();
	delay_ms(300);
	claw_turn0();
	delay_ms(300);
	arrive_circle_capture2();
	claw_open();
	delay_ms(200);
}
/********************
�������� : צ�Ӱ����ŵ�����̨ 
������� : ��
������� ����
**********************/
void claw_get_block6(void)
{
	claw_turn0();
	delay_ms(200);
	arrive_block_get1();
	claw_close();
	delay_ms(200);
	arrive_most_up();
	delay_ms(200);
	claw_turn3();
	delay_ms(200);
	delay_ms(200);
	delay_ms(200);
	arrive_block_put();
	delay_ms(300);
	claw_open();
	arrive_most_up();
	delay_ms(300);
	claw_turn0();
	delay_ms(300);
	arrive_circle_capture2();
	claw_open();
	delay_ms(200);
}
/********************
�������� : צ�Ӱ����ŵ�����̨  
������� : ��
������� ����
**********************/
// void claw_get_block4(void)
// {
// 	arrive_block_get();
// 	claw_close();
// 	delay_ms(200);
// 	arrive_most_up();
// 	delay_ms(200);
// 	claw_turn4();
// 	delay_ms(200);
// 	delay_ms(200);
// 	delay_ms(200);
// 	arrive_block_put();
// 	claw_open1();
// 	arrive_most_up();
// 	claw_turn0();
// 	claw_open();
// 	delay_ms(200);
// }
/********************
�������� : צ�Ӱ����ŵ�����̨   
������� : ��
������� ����
**********************/
// void claw_get_block5(void)
// {
// 	arrive_block_get();
// 	claw_close();
// 	delay_ms(200);
// 	arrive_most_up();
// 	delay_ms(200);
// 	claw_turn5();
// 	delay_ms(200);
// 	delay_ms(200);
// 	delay_ms(200);
// 	arrive_block_put();
// 	claw_open1();
// 	arrive_most_up();
// 	claw_turn0();
// 	claw_open();
// 	delay_ms(200);
// }
/********************
�������� : צ�Ӱ�����ó�����̨ �ŵ�1
������� : ��
������� ����
**********************/
void claw_put_block1(void)
{

	arrive_most_up();       
	claw_turn1();
	delay_ms(300);
	arrive_block_down();
	claw_close();
	delay_ms(300);	
	arrive_most_up(); 
  delay_ms(300);
  delay_ms(300);  
	claw_turn0();
	delay_ms(300);
	arrive_block_get();
	delay_ms(300);	
	claw_open();
	delay_ms(300);
	arrive_most_up();
	delay_ms(300);
}
/********************
�������� : צ�Ӱ�����ó�����̨ �ŵ�2
������� : ��
������� ����
**********************/
void claw_put_block2(void)
{
	
	arrive_most_up();   	
	claw_turn2();
	delay_ms(200);
	arrive_block_down();
	claw_close();
	delay_ms(300);
	arrive_most_up();
  delay_ms(300);	
	delay_ms(300);
	claw_turn0();
	delay_ms(300);
	arrive_block_get();
	delay_ms(300);	
	claw_open();
	delay_ms(300);
	arrive_most_up();
	delay_ms(300);
}
/********************
�������� : צ�Ӱ�����ó�����̨ �ŵ�3
������� : ��
������� ����
**********************/
void claw_put_block3(void)
{
	
	arrive_most_up();       
	claw_turn3();
	delay_ms(200);
	arrive_block_down();
	claw_close();
	delay_ms(300);
	arrive_most_up();  
  delay_ms(300);
  delay_ms(300);  
	claw_turn0();
	delay_ms(300);
	arrive_block_get();
	delay_ms(300);	
	claw_open();
	delay_ms(300);
	arrive_most_up();
	delay_ms(300);
}

/********************
�������� : צ�Ӱѳ���1��λ�õ������ŵ�������
������� : ��
������� ����
**********************/
void claw_put_1blockF2(void)
{
	
    arrive_most_up();
	claw_turn1();
	delay_ms(200);
	arrive_block_down();
	claw_close();
	delay_ms(300);
	arrive_most_up();
	delay_ms(300);
    delay_ms(300); 
	claw_turn0();
	delay_ms(300);
	arrive_block_putF2();
	delay_ms(300);
	claw_open();
	delay_ms(300);
		arrive_most_up();
	delay_ms(300);
}
/********************
�������� : צ�Ӱѳ���2��λ�õ������ŵ�������
������� : ��
������� ����
**********************/
void claw_put_2blockF2(void)
{

    arrive_most_up();
	claw_turn2();
	delay_ms(200);
	arrive_block_down();
	claw_close();
	delay_ms(300);
	arrive_most_up();
	delay_ms(300);
    delay_ms(300); 
	claw_turn0();
	delay_ms(300);
	arrive_block_putF2();
	delay_ms(300);
	claw_open();
	delay_ms(300);	
		arrive_most_up();
	delay_ms(300);
}
/********************
�������� : צ�Ӱѳ���3��λ�õ������ŵ�������
������� : ��
������� ����
**********************/
void claw_put_3blockF2(void)
{

    arrive_most_up();
	claw_turn3();
	delay_ms(200);
	arrive_block_down();
	claw_close();
	delay_ms(300);
	arrive_most_up();
	delay_ms(300);
    delay_ms(300); 
	claw_turn0();
	delay_ms(300);
	arrive_block_putF2();
	delay_ms(300);
	claw_open();
	delay_ms(300);
	arrive_most_up();
	delay_ms(300);
}
/********************
�������� : צ�Ӱ�����ó�����̨ �ŵ�4
������� : ��
������� ����
**********************/
// void claw_put_block4(void)
// {
// 	claw_open1();
// 	arrive_most_up();       
// 	claw_turn4();
// 	delay_ms(200);
// 	arrive_block_down();
// 	claw_close();
// 	delay_ms(300);
// 	arrive_most_up(); 
// 	delay_ms(300);
//   delay_ms(300);	
// 	claw_turn0();
// 	delay_ms(300);
// 	arrive_block_get(); 
// 	delay_ms(300);	
// 	claw_open();
// 	delay_ms(300);
// }
/********************
�������� : צ�Ӱ�����ó�����̨ �ŵ�5
������� : ��
������� ����
**********************/
// void claw_put_block5(void)
// {
// 	claw_open1();
// 	arrive_most_up();  
// 	claw_turn5();
// 	delay_ms(300);
// 	delay_ms(300);
// 	arrive_block_down();
// 	claw_close();
// 	delay_ms(300);
// 	arrive_most_up(); 
//   delay_ms(300);
// 	delay_ms(300);
// 	claw_turn0();
// 	delay_ms(300);	
// 	arrive_block_get(); 
// 	delay_ms(300);
// 	claw_open();
// 	delay_ms(300);
// }
/********************
�������� : צ�Ӱ�����ó�����̨ �ŵ���һ��
������� : ��
������� ����
**********************/
// void claw_put_block6(void)
// {
// 	claw_open1();
// 	arrive_most_up();       
// 	claw_turn2();//
// 	delay_ms(200);
// 	arrive_block_down();
// 	claw_close();
// 	delay_ms(300);
// 	arrive_most_up(); 
// 	delay_ms(300);
//   delay_ms(300);	
// 	claw_turn0();
// 	delay_ms(300);
// 	arrive_block_get2(); 
// 	delay_ms(300);	
// 	claw_open();
// 	delay_ms(300);
// }
/********************
�������� : צ�Ӱ�����ó�����̨ �ŵ��ڶ���
������� : ��
������� ����
**********************/
// void claw_put_block7(void)
// {
// 	claw_open1();
// 	arrive_most_up();  
// 	claw_turn3();//
// 	delay_ms(300);
// 	delay_ms(300);
// 	arrive_block_down();
// 	claw_close();
// 	delay_ms(300);
// 	arrive_most_up(); 
//   delay_ms(300);
// 	delay_ms(300);
// 	claw_turn0();
// 	delay_ms(300);	
// 	arrive_block_get3(); 
// 	delay_ms(300);
// 	claw_open();
// 	delay_ms(300);
// }

/********************
�������� : צ�Ӱ�����ó�����̨ �ŵ�5
������� : ��
������� ����
**********************/
void claw_home(void)
{
	arrive_most_up();
	delay_ms(300);  
	claw_turn3();
}
///********************
//�������� : צ�Ӱ�����ó�����̨ �ŵ�4
//������� : ��
//������� ����
//**********************/
//void claw_put_block6(void)
//{
//	claw_open1();
//	arrive_most_up();       
//	claw_turn4();
//	delay_ms(200);
//	arrive_block_down();
//	claw_close();
//	delay_ms(300);
//	arrive_most_up(); 
//	delay_ms(300);
//  delay_ms(300);	
//	claw_turn0();
//	delay_ms(300);
//	arrive_block_get2(); 
//	delay_ms(300);	
//	claw_open();
//	delay_ms(300);
//}
///********************
//�������� : צ�Ӱ�����ó�����̨ �ŵ�5
//������� : ��
//������� ����
//**********************/
//void claw_put_block7(void)
//{
//	claw_open1();
//	arrive_most_up();  
//	claw_turn5();
//	delay_ms(300);
//	delay_ms(300);
//	arrive_block_down();
//	claw_close();
//	delay_ms(300);
//	arrive_most_up(); 
//  delay_ms(300);
//	delay_ms(300);
//	claw_turn0();
//	delay_ms(300);	
//	arrive_block_get3(); 
//	delay_ms(300);
//	claw_open();
//	delay_ms(300);
//}
