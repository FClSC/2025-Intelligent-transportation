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
		MSD_Move1(pulse,120,120,150);
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

////////////////////////////////////////////////////////////צ�Ӹ߶�
/********************
�������� : ��������ͷɨ���λ��
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
�������� : ������ߴ�
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
�������� : �������ץ���ĸ߶�
������� : ��
������� ����
**********************/
void arrive_block_get(void)
{
	claw.position_target = claw_block_get;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : �����������ĸ߶�
������� : ��
������� ����
**********************/
void arrive_block_put(void)
{
	claw.position_target = put_block_down;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : �����������ץ���ĸ߶�
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
�������� : �����ڳ��Ϸ����ĸ߶�
������� : ��
������� ����
**********************/
void arrive_car_put(void)
{
	claw.position_target = claw_block_put;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}


/********************
�������� : ���ﳵ��ץ���ĸ߶�
������� : ��
������� ����
**********************/
void arrive_car_get(void)
{
	claw.position_target = get_block_down;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : ���������ڵڶ���߶�
������� : ��
������� ����
**********************/
void arrive_put_down2(void)
{
	claw.position_target = put_block_down2;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : �������ʶ��ĸ߶�
������� : ��
������� ����
**********************/
void arrive_circle_capture(void)
{
	claw.position_target = circle_capture1;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : ����������ʶ��ĸ߶�
������� : ��
������� ����
**********************/
void arrive_circle_capture2(void)
{
	claw.position_target = circle_capture3;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
�������� : ����������ʶ����ɫ�ĸ߶�
������� : ��
������� ����
**********************/
void arrive_color_reco(void)
{
	claw.position_target = circle_capture2;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}



////////////////////////////////////////////////////צ�Ӿ��嶯��

/********************
�������� : צ�Ӵӵ�������ų��� 
������� : ��
������� ����
**********************/
void claw_get_block(void)
{
	claw_turn0();
	claw_open();
	arrive_block_get();
	delay_ms(200);
	claw_close();
	delay_ms(300);
	arrive_most_up();
	claw_turn1();
	delay_ms(800);
	arrive_car_put();
	claw_open1();
	delay_ms(200);
	arrive_most_up();	
	support_turn120();
	claw_open();

	// claw_turn0();
	// arrive_block_get();
	// delay_ms(200);
	// claw_close();
	// delay_ms(300);
	// arrive_most_up();
	// claw_turn1();
	// delay_ms(800);
	// arrive_car_put();
	// claw_open();
	// delay_ms(200);
	// arrive_most_up();
	// claw_turn0();
	// claw_open();
	// support_turn120();

    

}

/********************
�������� : צ�Ӵ������̰����ų��� 
������� : ��
������� ����
**********************/
void claw_get_block1(void)
{
	claw_turn0();
	arrive_block_get1();
	delay_ms(200);
	claw_close();
	delay_ms(200);
	arrive_most_up();
	claw_turn1();
	delay_ms(800);
	arrive_car_put();
	claw_open1();
	delay_ms(200);
	arrive_most_up();
	claw_turn0();
	claw_open();
	delay_ms(200);
	arrive_color_reco();//�ٴλص�ʶ��������ɫ�ĸ߶�
	support_turn120();
	
}


/********************
�������� : צ�Ӵӳ��ϰ����ŵ���
������� : ��
������� ����
**********************/
void claw_put_block(void)
{
    
	arrive_most_up(); 
	claw_open1();   
	claw_turn1();
	delay_ms(800);
	arrive_car_get();
	delay_ms(300);
	claw_close();
	delay_ms(300);
	arrive_most_up(); 
    delay_ms(200);
	claw_turn0();
    delay_ms(300);
	arrive_block_put();
	delay_ms(300);	
	claw_open();
	arrive_most_up();
	support_turn120();
	
}

/********************
�������� : צ�Ӱ����ӳ��Ϸŵ�����
������� : ��
������� ����
**********************/
void claw_put_blockF2(void)
{

	arrive_most_up();
	claw_open1();       
	claw_turn1();
	delay_ms(800);
	arrive_car_get();
	claw_close();
	delay_ms(300);	
	arrive_most_up(); 
    delay_ms(200);
	claw_turn0();
	delay_ms(300);
	arrive_put_down2();
	delay_ms(500);	
	claw_open();
	delay_ms(300);
	arrive_most_up();
	support_turn120();

}


/********************
�������� : צ�ӹ�λ
������� : ��
������� ����
**********************/
void claw_home(void)
{
	arrive_most_up();
	delay_ms(300);  
	claw_turn1();
}

