#include "contral_claw.h"

CLAW_POSITION claw;
/********************
函数功能 : 爪子位置函数  单位mm

输入参数 : 无
输出参数 ：无
直径 16mm 
转一圈  8*2*3.14=50.24 
x/mm = 3200/50.24
x = 64*mm   1mm需要64个脉冲
**********************/
void claw_position(int16_t position)
{
	uint32_t pulse=0;
	claw.position_now = claw.position_now + position; // 更新当前位置
	
	if(claw.position_now<0 || claw.position_now>265)
	{
		claw.position_now=claw.position_now - position;
	}
	else
	{
		// 方向
		if(position>0)
		{
				Motor1_DIR(1);   // 向上
		}
		else
		{
				position=-position;
				Motor1_DIR(0);   // 向下
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
函数功能 : 爪子位置函数  单位mm
输入参数 : 无
输出参数 ：无
是否结束由外部控制
*********/
void claw_position2(int16_t position)
{
	uint32_t pulse=0;
	claw.position_now = claw.position_now + position; // 更新当前位置
	if(claw.position_now<0 || claw.position_now>265)
	{
		claw.position_now=claw.position_now - position;
	}
	else
	{
		// 方向
		if(position>0)
		{
				Motor1_DIR(1);   // 向上
		}
		else
		{
				position=-position;
				Motor1_DIR(0);   // 向下
		}
		pulse=(64*position);
		distance1=pulse;
		stepPosition1=0;
		MSD_Move1(pulse,36,36,45);
	}
}

////////////////////////////////////////////////////////////爪子高度
/********************
函数功能 : 到达摄像头扫码的位置
输入参数 : 无
输出参数 ：无
**********************/
void arrive_camera(void)
{
	claw.position_target = camera_position;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达最高处
输入参数 : 无
输出参数 ：无
**********************/
void arrive_most_up(void)
{
	claw.position_target = claw_most_up;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达地面抓物块的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_block_get(void)
{
	claw.position_target = claw_block_get;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达地面放物块的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_block_put(void)
{
	claw.position_target = put_block_down;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达从物料盘抓物块的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_block_get1(void)
{
	claw.position_target = claw_block_get1;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}


/********************
函数功能 : 到达在车上放物块的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_car_put(void)
{
	claw.position_target = claw_block_put;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}


/********************
函数功能 : 到达车上抓物块的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_car_get(void)
{
	claw.position_target = get_block_down;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达物块放在第二层高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_put_down2(void)
{
	claw.position_target = put_block_down2;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达靶心识别的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_circle_capture(void)
{
	claw.position_target = circle_capture1;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达二层靶心识别的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_circle_capture2(void)
{
	claw.position_target = circle_capture3;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达物料盘识别颜色的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_color_reco(void)
{
	claw.position_target = circle_capture2;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}



////////////////////////////////////////////////////爪子具体动作

/********************
函数功能 : 爪子从地面把物块放车上 
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子从物料盘把物块放车上 
输入参数 : 无
输出参数 ：无
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
	arrive_color_reco();//再次回到识别物料颜色的高度
	support_turn120();
	
}


/********************
函数功能 : 爪子从车上把物块放地上
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把物块从车上放到二层
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子归位
输入参数 : 无
输出参数 ：无
**********************/
void claw_home(void)
{
	arrive_most_up();
	delay_ms(300);  
	claw_turn1();
}

