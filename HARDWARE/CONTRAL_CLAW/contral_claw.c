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


/********************
函数功能 : 到达摄像头的位置
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
函数功能 : 到达摄像头的位置
输入参数 : 无
输出参数 ：无
是否结束由外部控制
**********************/
void arrive_camera2(void)
{
	claw.position_target = camera_position;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position2(claw.position_temp);
}
/********************
函数功能 : 到达抓物料块的位置 从物料台抓物块的高度
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
函数功能 : 到达抓物料块的位置
输入参数 : 无
输出参数 ：无
**********************/
void arrive_block_get(void)
{
	claw.position_target = claw_block_get;//地面高度
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达把物块叠起来第二层的高度
输入参数 : 无
输出参数 ：无
**********************/
void arrive_block_putF2(void)
{
	claw.position_target = claw_block_get2;  //物块第二层
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}
/********************
函数功能 : 到达抓物料块的位置 第二层
输入参数 : 无
输出参数 ：无
**********************/
void arrive_block_get3(void)
{
	claw.position_target = claw_block_get3;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}
/********************
函数功能 : 到达放物料块的位置
输入参数 : 无
输出参数 ：无
**********************/
void arrive_block_put(void)
{
	claw.position_target = get_block_down;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);
}

/********************
函数功能 : 到达放物料块的位置  放第二层
输入参数 : 无
输出参数 ：无
**********************/
//void arrive_block_put2(void)
//{
//	claw.position_target = claw_block_put2;
//	claw.position_temp = claw.position_target - claw.position_now;
//	claw_position(claw.position_temp);
//}
///********************
//函数功能 : 到达放物料块的位置  放第二层
//输入参数 : 无
//输出参数 ：无
//**********************/
//void arrive_block_put3(void)
//{
//	claw.position_target = claw_block_put3;
//	claw.position_temp = claw.position_target - claw.position_now;
//	claw_position(claw.position_temp);
//}
/********************
函数功能 : 到达最顶端
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
函数功能 : 从转盘拿物料块放到车上的位置
输入参数 : 无
输出参数 ：无
**********************/
void arrive_block_down(void)
{
	claw.position_target = get_block_down;
	claw.position_temp = claw.position_target - claw.position_now;
	claw_position(claw.position_temp);	
}

/********************
函数功能 : 到靶心识别的位置
输入参数 : 无
输出参数 ：无
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
函数功能 : 到物料盘靶心识别的位置2
输入参数 : 无
输出参数 ：无
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
//函数功能 : 到达转盘识别黑色块的高度
//输入参数 : 无
//输出参数 ：无
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
//函数功能 : 爪子把物块放到载物台   从转盘抓
//输入参数 : 无
//输出参数 ：无
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
//函数功能 : 爪子把物块放到载物台   从地面抓
//输入参数 : 无
//输出参数 ：无
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
//函数功能 : 爪子吧物块拿出载物台 放到第一层
//输入参数 : 无
//输出参数 ：无
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
//函数功能 : 爪子吧物块拿出载物台 放到第二层
//输入参数 : 无
//输出参数 ：无
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
//函数功能 : 爪子吧物块拿出载物台 放到第二层平台上
//输入参数 : 无
//输出参数 ：无
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
//函数功能 : 归位
//输入参数 : 无
//输出参数 ：无
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
函数功能 : 爪子把物块放到载物台   
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把物块放到载物台   
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把物块放到载物台
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把物块放到载物台 
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把物块放到载物台 
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把物块放到载物台 
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把物块放到载物台  
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把物块放到载物台   
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子吧物块拿出载物台 放到1
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子吧物块拿出载物台 放到2
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子吧物块拿出载物台 放到3
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把车上1号位置的物块码放到物块二层
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把车上2号位置的物块码放到物块二层
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子把车上3号位置的物块码放到物块二层
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子吧物块拿出载物台 放到4
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子吧物块拿出载物台 放到5
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子吧物块拿出载物台 放到第一层
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子吧物块拿出载物台 放到第二层
输入参数 : 无
输出参数 ：无
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
函数功能 : 爪子吧物块拿出载物台 放到5
输入参数 : 无
输出参数 ：无
**********************/
void claw_home(void)
{
	arrive_most_up();
	delay_ms(300);  
	claw_turn3();
}
///********************
//函数功能 : 爪子吧物块拿出载物台 放到4
//输入参数 : 无
//输出参数 ：无
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
//函数功能 : 爪子吧物块拿出载物台 放到5
//输入参数 : 无
//输出参数 ：无
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
