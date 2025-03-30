#include "contral.h"
#include <stdio.h>
#include <math.h>
#include "delay.h"

speedRampData srd;
speedRampData srd1;
speedRampData srd2;

uint8_t servo_angle1;
uint8_t servo_angle2;
uint16_t servo_angle3;

extern float Angle_Err;  //角度相比较于初始的累计误差


int stepPosition = 0;
int stepPosition1 = 0;
int stepPosition2 = 0;

int distance=0;
uint16_t angle_temp=0;

int distance1=0;

// 定时器3
/*******************************************
函数功能 : 控制小车底盘的初始化
输入参数 : 无
输出参数 ：无
********************************************/
void contral_motor_Init(void)
{
	MOTOR3_Init();
	MOTOR4_Init();
	MOTOR7_Init();
	MOTOR8_Init();
}
// 定时器2
/*******************************************
函数功能 : 控制爪子抓取的初始化
输入参数 : 无
输出参数 ：无
********************************************/
void claw_Init(void)
{
	MOTOR1_Init();//升降
	MOTOR5_Init();//转盘
	Servo2_Init();
	Servo3_Init();
	claw_turn0();	
	claw_open();
	claw.position_now=0;  
	claw.position_target=0;
	claw.position_temp=0;
}
/*************************
定时器3 的控制
控制对象 小车底盘
小车功能 ： 控制小车底盘运动
输入参数 ： 步数 加速度 减速度 速度
输出参数 ： 无
**************************/
void MSD_Move(signed int step, unsigned int accel, unsigned int decel, unsigned int speed)
{
    uint16_t max_s_lim;
    uint16_t accel_lim; 
    if(step > 0)//逆时针
    {
        srd.dir = CCW;
    }
    if(step == 1)
    {
        srd.accel_count = -1;
        srd.run_state = DECEL;
        srd.step_delay = 1000;
        TIM_SetAutoreload(TIM3,Pulse_width);
        TIM_SetCompare1(TIM3,Pulse_width_comper); 
		TIM_SetCompare2(TIM3,Pulse_width_comper); 					
        TIM_SetCompare3(TIM3,Pulse_width_comper); 
		TIM_SetCompare4(TIM3,Pulse_width_comper); 
        TIM_Cmd(TIM3, ENABLE); 
     }
    else if(step != 0)
    {
			accel = accel*100; 
			decel = decel*100;
			speed = speed*100;
			srd.min_delay = A_T_x100 / speed;
			srd.step_delay = (T1_FREQ_148 * sqrt(A_SQ / accel))/100;
			// 计算多少步之后达到最大速度的限制
			max_s_lim = (long)speed*speed/(long)(((long)A_x20000*accel)/100);
			// 如果达到最大速度小于0.5步，我们将四舍五入为0
			// 但实际我们必须移动至少一步才能达到想要的速度
			if(max_s_lim == 0)
			{
					max_s_lim = 1;
			}
			// 计算多少步之后我们必须开始减速
			accel_lim = ((long)step*decel) / (accel+decel);
			// 我们必须加速至少1步才能才能开始减速.
			if(accel_lim == 0)
			{
					accel_lim = 1;
			}
			// 使用限制条件我们可以计算出第一次开始减速的位置
			if(accel_lim <= max_s_lim)
			{
					srd.decel_val = accel_lim - step;
			}
			else
			{
					srd.decel_val = -(long)(max_s_lim*accel/decel);
			}
			// 当只剩下一步我们必须减速
			if(srd.decel_val == 0)
			{
					srd.decel_val = -1;
			}
			// 计算开始减速时的步数
			srd.decel_start = step + srd.decel_val;
			// 如果最大速度很慢，我们就不需要进行加速运动
			if(srd.step_delay <= srd.min_delay)
			{
					srd.step_delay = srd.min_delay;
					srd.run_state = RUN;
			}
			else
		  {
					srd.run_state = ACCEL;
			} 
			// 复位加速度计数值
			srd.accel_count = 0;
			//设置定时器重装值	
			TIM_SetAutoreload(TIM3,Pulse_width);
			TIM_SetCompare1(TIM3,Pulse_width_comper); 
			TIM_SetCompare2(TIM3,Pulse_width_comper); 					
			TIM_SetCompare3(TIM3,Pulse_width_comper); 
			TIM_SetCompare4(TIM3,Pulse_width_comper); 		
			//使能定时器	      
			TIM_Cmd(TIM3, ENABLE); 
    }
}
/*************************
定时器2 的控制
控制对象 抓取机构
功能 ： 控制抓取机构的上升与下降
输入参数 ： 步数 加速度 减速度 速度
输出参数 ： 无
**************************/
void MSD_Move1(signed int step, unsigned int accel, unsigned int decel, unsigned int speed)
{
    uint16_t max_s_lim;
    uint16_t accel_lim; 
    if(step > 0)//逆时针
    {
        srd1.dir = CCW;
    }
    if(step == 1)
    {
        srd1.accel_count = -1;
        srd1.run_state = DECEL;
        srd1.step_delay = 1000;
        TIM_SetAutoreload(TIM2,Pulse_width);
        TIM_SetCompare3(TIM2,Pulse_width_comper); 
				TIM_SetCompare4(TIM2,Pulse_width_comper); 
        TIM_Cmd(TIM2, ENABLE); 
     }
    else if(step != 0)
    {
				accel = accel*100; 
				decel = decel*100;
				speed = speed*100;
			srd1.min_delay = A_T_x100 / speed;
			srd1.step_delay = (T1_FREQ_148 * sqrt(A_SQ / accel))/100;
			// 计算多少步之后达到最大速度的限制
			max_s_lim = (long)speed*speed/(long)(((long)A_x20000*accel)/100);
			// 如果达到最大速度小于0.5步，我们将四舍五入为0
			// 但实际我们必须移动至少一步才能达到想要的速度
			if(max_s_lim == 0)
			{
					max_s_lim = 1;
			}
			// 计算多少步之后我们必须开始减速
			accel_lim = ((long)step*decel) / (accel+decel);
			// 我们必须加速至少1步才能才能开始减速.
			if(accel_lim == 0)
			{
					accel_lim = 1;
			}
			// 使用限制条件我们可以计算出第一次开始减速的位置
			if(accel_lim <= max_s_lim)
			{
					srd1.decel_val = accel_lim - step;
			}
			else
			{
					srd1.decel_val = -(long)(max_s_lim*accel/decel);
			}
			// 当只剩下一步我们必须减速
			if(srd1.decel_val == 0)
			{
					srd1.decel_val = -1;
			}
			// 计算开始减速时的步数
			srd1.decel_start = step + srd1.decel_val;
			// 如果最大速度很慢，我们就不需要进行加速运动
			if(srd1.step_delay <= srd1.min_delay)
			{
					srd1.step_delay = srd1.min_delay;
					srd1.run_state = RUN;
			}
			else
		  {
					srd1.run_state = ACCEL;
			} 
			// 复位加速度计数值
			srd1.accel_count = 0;
			//设置定时器重装值	
			TIM_SetAutoreload(TIM2,Pulse_width);
			//设置占空比为50%	
			TIM_SetCompare3(TIM2,Pulse_width_comper);
			TIM_SetCompare4(TIM2,Pulse_width_comper);			
			//使能定时器	      
			TIM_Cmd(TIM2, ENABLE); 
    }
}
/*************************
定时器4 的控制
控制对象 转盘机构
功能 ： 控制转盘的旋转
输入参数 ： 步数 加速度 减速度 速度
输出参数 ： 无
**************************/
void MSD_Move2(signed int step, unsigned int accel, unsigned int decel, unsigned int speed)
{
    uint16_t max_s_lim;
    uint16_t accel_lim; 
    if(step > 0)//逆时针
    {
        srd2.dir = CCW;
    }
    if(step == 1)
    {
        srd2.accel_count = -1;
        srd2.run_state = DECEL;
        srd2.step_delay = 1000;
        TIM_SetAutoreload(TIM4,Pulse_width);
        TIM_SetCompare3(TIM4,Pulse_width_comper); 
		TIM_SetCompare4(TIM4,Pulse_width_comper); //这一步没必要,2024/12/10
        TIM_Cmd(TIM4, ENABLE); 
     }
    else if(step != 0)
    {
				accel = accel*100; 
				decel = decel*100;
				speed = speed*100;
			srd2.min_delay = A_T_x100 / speed;
			srd2.step_delay = (T1_FREQ_148 * sqrt(A_SQ / accel))/100;
			// 计算多少步之后达到最大速度的限制
			max_s_lim = (long)speed*speed/(long)(((long)A_x20000*accel)/100);
			// 如果达到最大速度小于0.5步，我们将四舍五入为0
			// 但实际我们必须移动至少一步才能达到想要的速度
			if(max_s_lim == 0)
			{
					max_s_lim = 1;
			}
			// 计算多少步之后我们必须开始减速
			accel_lim = ((long)step*decel) / (accel+decel);
			// 我们必须加速至少1步才能才能开始减速.
			if(accel_lim == 0)
			{
					accel_lim = 1;
			}
			// 使用限制条件我们可以计算出第一次开始减速的位置
			if(accel_lim <= max_s_lim)
			{
					srd2.decel_val = accel_lim - step;
			}
			else
			{
					srd2.decel_val = -(long)(max_s_lim*accel/decel);
			}
			// 当只剩下一步我们必须减速
			if(srd2.decel_val == 0)
			{
					srd2.decel_val = -1;
			}
			// 计算开始减速时的步数
			srd2.decel_start = step + srd2.decel_val;
			// 如果最大速度很慢，我们就不需要进行加速运动
			if(srd2.step_delay <= srd2.min_delay)
			{
					srd2.step_delay = srd2.min_delay;
					srd2.run_state = RUN;
			}
			else
		  {
					srd2.run_state = ACCEL;
			} 
			// 复位加速度计数值
			srd2.accel_count = 0;
			//设置定时器重装值	
			TIM_SetAutoreload(TIM4,Pulse_width);
			//设置占空比为50%	
			TIM_SetCompare3(TIM4,Pulse_width_comper);
			TIM_SetCompare4(TIM4,Pulse_width_comper);			
			//使能定时器	      
			TIM_Cmd(TIM4, ENABLE); 
    }
}

/*************************
定时器3 的控制
控制对象 小车底盘
功能 ： 累计底盘的脉冲数
输入参数 ： 步数
输出参数 ： 无
**************************/
void MSD_StepCounter(signed char inc)
{
  //根据方向判断电机位置
  if(inc == CCW)
  {
    stepPosition++;
  }
  else
  {
    stepPosition--;
  }
}
/*************************
定时器2 的控制
控制对象 抓取机构
功能 ： 控制抓取机构的步数
输入参数 ： 步数
输出参数 ： 无
**************************/
void MSD_StepCounter1(signed char inc)
{
  //根据方向判断电机位置
  if(inc == CCW)
  {
    stepPosition1++;
  }
  else
  {
    stepPosition1--;
  }
}
/*************************
定时器4 的控制
控制对象 转盘机构
功能 ： 控制转盘的步数
输入参数 ： 步数
输出参数 ： 无
**************************/
void MSD_StepCounter2(signed char inc)
{
  //根据方向判断电机位置
  if(inc == CCW)
  {
    stepPosition2++;
  }
  else
  {
    stepPosition2--;
  }
}



/*************************
定时器2 的控制
功能 ： 控制电机1的方向
输入参数 ： 方向
输出参数 ： 无
**************************/
void Motor1_DIR(uint8_t a)
{
	if(a == CW)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
}
/*******************************************
函数功能 : 处理小车底盘的移动方向
输入参数 : 方向
输出参数 ：无
********************************************/
// PG7    dir3
void DIR1(uint8_t a)
{
	if(a == CW)
	{
		GPIO_SetBits(GPIOG,GPIO_Pin_7);
	}
	else
	{
		GPIO_ResetBits(GPIOG,GPIO_Pin_7);
	}
}
//PG8    dir4
void DIR2(uint8_t a)
{
	if(a == CW)
	{
		GPIO_ResetBits(GPIOG,GPIO_Pin_8);
	}
	else
	{
		GPIO_SetBits(GPIOG,GPIO_Pin_8);
	}
}
// PA8    dir7
void DIR3(uint8_t a)
{
	if(a == CW)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	}
}
// PC1    dir8
void DIR4(uint8_t a)
{
	if(a == CW)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	}
}
/********************
函数功能 : 处理小车移动方向的函数
输入参数 : x的位移，y的位移
输出参数 ：无
**********************/
void MOTOR_Direction(int16_t x,int16_t y)
{
	// x有值
	if(x<0) {DIR1(0); DIR2(0);DIR3(0); DIR4(0);}
	else if(x>0)  {DIR1(1); DIR2(1);DIR3(1); DIR4(1);}
	// y有值	
	if(y>0) {DIR1(0); DIR2(1);DIR3(0); DIR4(1);}
	else if(y<0) {DIR1(1); DIR2(0);DIR3(1); DIR4(0);}
}
/********************
函数功能 : 绝对值函数
输入参数 : 整数值
输出参数 ：无
**********************/
uint16_t abs_int(int16_t x)
{
	if(x>0) return x;
	else return -x;
}

/********************
函数功能 : 绝对值函数
输入参数 : 浮点值
输出参数 ：整型
**********************/
int16_t abs_float(float x,int8_t y)
{
    int16_t z;
	if(x>y)
	{
		z=round(x-y);
		return z;
	}
	else
	{
		z=round(y-x);
		return z;
	}
}

/********************
函数功能 : 得到x与y方向的最大位移的函数
输入参数 : x的位移，y的位移
输出参数 ：无
**********************/
uint16_t max_Return(int16_t x,int16_t y)
{
	uint16_t x1,y1;
	x1 = abs_int(x);
	y1 = abs_int(y);
	if(x1>y1) return x1;
	if(y1>x1) return y1;
	return 0;
}
/********************
函数功能 : 处理小车旋转方向的函数
输入参数 : 旋转角度
输出参数 ：无
**********************/
void MOTOR_TURN(int16_t angle)
{
	if(angle>0)  {DIR1(0); DIR2(1);DIR3(1); DIR4(0);}
	else if(angle<0) {DIR1(1); DIR2(0);DIR3(0); DIR4(1);}
}
/********************
函数功能 : 处理小车位移函数
输入参数 : x方向的cm与y方向的cm距离
输出参数 ：无
**********************/
void MOTOR_Displacement(int16_t x_cm,int16_t y_cm)
{
	int temp=0;
	// 先判断方向
	MOTOR_Direction(x_cm,y_cm);
	// 运动控制
	temp=max_Return(x_cm,y_cm);
	//     3200        x/a = 78/3200     
	distance=temp*130;  //输入的是cm 
	MSD_Move(distance,20,20,40);  //17 17 40 
}


/********************
函数功能 : 处理小车旋转角度（微调）
输入参数 : 微调的角度
输出参数 ：无
**********************/
float adjust_float(float x, int8_t y)
{
    float z;
	z=y-x;
	return z;
}



/********************
函数功能 : 处理小车角度函数
输入参数 : 逆时针旋转的角度
输出参数 ：无
**********************/
void MOTOR_Angle(int8_t angle)
{
	MOTOR_TURN(angle);
	angle_temp = abs_int(angle*50);
	MSD_Move(angle_temp,15,15,30);   //张瑞哲 14 14 25
}

/********************
函数功能 : 处理小车微调角度函数
输入参数 : 逆时针旋转的角度
输出参数 ：无
**********************/
void MOTOR_Angle_micro(float angle1)
{
	int16_t angle2;
	angle2=angle1*10;

	MOTOR_TURN(angle2);  //旋转方向的处理
	angle_temp = abs_int(angle2*5);   //注意这个地方是*5，角度变得更精细，张瑞哲的是*4
	MSD_Move(angle_temp,10,10,20);   //张瑞哲： 8 8 24
}


/********************
函数功能 : 在初步旋转后进行两次校准
输入参数 : 初步旋转的角度
输出参数 ：无
**********************/
void MOTOR_TurnRight(int angle)  
{

	OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	OLED_Update();
	//delay_ms(5000);
	if(determicro(angle,global_angle)==1)
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
	}
	//delay_ms(3000);
	OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	OLED_Update();
	if(determicro(angle,global_angle)==1)
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
	}
	OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	OLED_Update();
	//delay_ms(2000);

	Angle_Err+=(global_angle-angle);//每次清零Z轴,将误差累积起来
	ResetAng_Z(); //重置Z轴陀螺仪，多次重置，防止未重置
	delay_ms(100);
	ResetAng_Z(); //重置Z轴陀螺仪
	delay_ms(100);
	OLED_ShowFloatNum(0,0,global_angle,3,3,OLED_8X16);
	OLED_Update();

}


/********************
函数功能 : 靶心识别时候进行姿态矫正(对应陀螺仪上一次清零与0度的差值)
输入参数 : 无
输出参数 ：不进行陀螺仪清零,可以在这里利用angle_err消除累计误差
**********************/
void MOTOR_Align(void)
{
    
	if(determicro(0,global_angle)==1)
	{

		stepPosition=0;
		MOTOR_Angle_micro(adjust_float(global_angle,0));
		while(1)
		{
			if(stepPosition == angle_temp)
			{
				break;
			}
		}
	}
	OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	OLED_Update();

	if(determicro(0,global_angle)==1)
	{

		stepPosition=0;
		MOTOR_Angle_micro(adjust_float(global_angle,0));
		while(1)
		{
			if(stepPosition == angle_temp)
			{
				break;
			}
		}
	}
	OLED_ShowFloatNum(0,0,global_angle,3,1,OLED_8X16);
	OLED_Update();

}
/********************
函数功能 : 处理小车位移函数
输入参数 : x方向的mm与y方向的mm距离
输出参数 ：无
**********************/
void MOTOR_Displacement_mm(int16_t x_mm,int16_t y_mm)
{
	int temp=0;
	distance=0;
	// 先判断方向
	MOTOR_Direction(x_mm,y_mm);
	// 运动控制
	temp=max_Return(x_mm,y_mm);
	//     3200        x/a = 78/3200 
	distance=temp*13;  //输入的是mm 
	MSD_Move(distance,12,12,20); //改成和国赛一样的速度
}
/********************
函数功能 : 处理上位机发送的消息
输入参数 : 无
输出参数 ：无
**********************/
void uart_handle(void)
{
	uint8_t mode=0x00;
	mode = Serial_RXPacket[0];   //接受模式
	uint8_t x_dis1 = 0;  //将距离拆分成两位进行传递,x_dis1和x_dis2
	uint8_t x_dis2 = 0;
	uint16_t temp_dis = 0; //转化中间变量
	uint8_t y_dis1 = 0;	
	uint8_t y_dis2 = 0;
    int16_t x_dis  = 0;
	int16_t y_dis  = 0;
	int8_t x_mdis = 0;
	int8_t y_mdis = 0;
	int8_t angle = 0;		
	int16_t code1 =0; 
	int16_t code2 =0; 	
	uint8_t position_camera = 0;
	uint8_t claw_mode=0;
	int8_t move_mode=0;

	
/*收到树莓派发送的数据包的格式：
0xFF 
0[模式] 
1[x或y位移的高八位]  2[x或y位移的低八位]     
3[旋转角度] 4[二维码前三位高八位] 5[二维码前三位低八位]
6[二维码后三位高八位] 7[二维码后三位低八位]
0xFE
                                                     */
	switch(mode)
	{
		case 0x01:  //x位移
		{
			x_dis1 = Serial_RXPacket[1];
			x_dis2 = Serial_RXPacket[2];
			temp_dis =  (x_dis1 << 8) | x_dis2 ;
			x_dis  = (int16_t)temp_dis;
			stepPosition=0;
			MOTOR_Displacement(x_dis,0);
			while(1)
			{
				if(stepPosition == distance)
				{
					break;
				}
			}
			break;
		}
		case 0x02:  //y位移
		{
            y_dis1 = Serial_RXPacket[1];
			y_dis2 = Serial_RXPacket[2];
			temp_dis =  (y_dis1 << 8) | y_dis2 ;
			y_dis  = (int16_t)temp_dis;
			stepPosition=0;			
			MOTOR_Displacement(0,y_dis);
			while(1)
			{
				if(stepPosition == distance)
				{
					break;
				}
			}
			break;
		}		
		case 0x03:  //角度
		{
			angle = Serial_RXPacket[3];
			stepPosition=0;			
			MOTOR_Angle(angle);
			while(1)
			{
				if(stepPosition == angle_temp)
				{
					break;
				}
			}	
			// // 陀螺仪微调操作
		    //MOTOR_TurnRight(angle);
			ResetAng_Z(); //重置Z轴陀螺仪
			  
			break;
		}			
		case 0x04:  //让单片机扫码
		{
			UART5_Start_Scan();//发送扫码指令
			while(1)//如果没有接收到数据就一直等待
			{
				if(Serial5_GetRxFlag() == 1)//接收到了数据就处理
				{
					delay_ms(300);//等待数据接收完全
					UART5_ParseCode(UART5_RX_BUF,&code1,&code2);//解析出二维码数据，此时UART5_BUX中依然存放的是二维码数据	
					u2_printf("tt3.txt=\"%d+%d\"",code1,code2);//多次发送给串口屏
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


			break;
		}	
		case 0x05:  //靶心识别x方向
		{
			x_mdis = Serial_RXPacket[1];
			stepPosition=0;
			MOTOR_Displacement_mm(x_mdis,0);
			while(1)
			{
				if(stepPosition == distance)
				{
					break;
				}
			}
			break;
		}		
		case 0x06:  //靶心识别y方向
		{
			y_mdis = Serial_RXPacket[2];
			stepPosition=0;
			MOTOR_Displacement_mm(0,y_mdis);
			while(1)
			{
				if(stepPosition == distance)
				{
					break;
				}
			}
			break;
		}	
		//0x07-0x09  从物料台获得物块放车上
		case 0x07:     //物块从物料转盘搬到车上
		{
            claw_get_block1(); 
			break;
		}

        case 0x08:     //物块从地上放到车上
		{
            claw_get_block();
			break;
		}

		case 0x09:     //物块从车上放地上
		{
            claw_put_block();   
			break;
		}
        case 0x0A:
		{
          claw_put_blockF2(); //物块从车上放二层
		  break;
		}
		

		case 0x0B: // 到达指定位置
		{
			position_camera=Serial_RXPacket[1];
			switch (position_camera)
			{
				case 0x01:
				{
					arrive_camera();   //到达二维码，最低
					  break;
				}
				case 0x02:
				{
					arrive_color_reco();   //到达转盘读取颜色
					  break;					
				}
				case 0x03:
				{
					arrive_circle_capture();   //识别放地上的高度
					  break;					
				}	
				case 0x04:
				{
					arrive_circle_capture2();   //识别二层码垛的高度
					break;
				}
				default :
				{
                    break ;
				}
			}
			break;
		}

		case 0X0D:
		{
			claw_mode=Serial_RXPacket[1];   //爪子模式
			move_mode=Serial_RXPacket[2];   //移动距离
			
			switch(claw_mode)
			{
				case 0x01:  //到达二维码，现在不需要这个东西，换扫码模块了
				{	
					stepPosition=0;   //跑
					stepPosition1=0;  //抓
					MOTOR_Displacement(move_mode,0);
					claw_turn0();
					delay_ms(200);  //先执行跑的在执行升降的
					arrive_camera();//应该是最低
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
						{
							break;
						}
					}	
					break;
				}
				case 0x02:     //到达物料台
				{
					stepPosition=0;   //跑
					stepPosition1=0;  //抓
					MOTOR_Displacement(move_mode,0);
					delay_ms(200);  //先执行跑的在执行升降的
					arrive_color_reco();  //这个是颜色识别高度
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
						{
							break;
						}
					}						
					break;
				}

				case 0x03:  // 到达靶心识别1，应该是快要到把心识别的地方用这个，边跑，边降低到这个高度
				{
					stepPosition=0;   //跑
					stepPosition1=0;  //抓
					MOTOR_Displacement(move_mode,0);
					delay_ms(200);  //先执行跑的在执行升降的
					arrive_circle_capture();
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
						{
							break;
						}
					}
					break;
				}

				case 0x04:  // 到达码垛高度
				{
					stepPosition=0;   //跑
					stepPosition1=0;  //抓
					MOTOR_Displacement(move_mode,0);
					delay_ms(200);  //先执行跑的在执行升降的
					arrive_circle_capture2();
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
						{
							break;
						}
					}
					break;
				}
				case 0x05:  // 转，升降，走，下降到达物料台识别高度
				{
					stepPosition=0;   //跑
					stepPosition1=0;  //抓
					MOTOR_Displacement(move_mode,0);
					claw_turn0();
					delay_ms(200);  //先执行跑的在执行升降的
					arrive_color_reco();
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
						{
							break;
						}
					}	
					break;
				}				
				case 0x06:  // 边走边转到到靶心识别1的高度
				{
					stepPosition=0;   //跑
					stepPosition1=0;  //抓
					MOTOR_Displacement(move_mode,0);
					claw_turn0();
					delay_ms(200);  //先执行跑的在执行升降的
					arrive_circle_capture();
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //两个都完成
						{
							break;
						}
					}	
					break;
				}	


				default:
				{
					break;
				}
			}
			break;
		}

		case 0x11:    //物料台旋转120度           
		{
           support_turn120();
			
			break;
		}
		case 0x12:
		{
           MOTOR_Align();  //靶心识别时候进行姿态矫正
			break;
		}
		case 0x13:
		{
            ResetAng_Z(); //重置Z轴陀螺仪
			break;
		}	
		case 0x14://把物块放到转盘上面
		{
			claw_put_block2();
			break;
		}	
		case 0x21:  //物料盘抓物块2放车上
		{
			claw_get2_block1(); 
			break;
		}
		case 0x22:  //地面抓物块2放车上
		{
            claw_get2_block();
			break;
		}
		case 0x23:  //从车上抓物块2放地上
		{
            claw_put2_block();
			break;
		}
		case 0x24:  //从车上抓物块2放二层
		{
			claw_put2_blockF2();
			 break;
		}
		case 0x25:  //从车上抓物块2放转盘
		{
            claw_put2_block2();
			 break;
		}
		case 0x26: 
		{

			break;
		}

		case 0x30 :
		{
		arrive_most_up();
			break;
		}
		case 0x31 :
		{
		arrive_block_get();
				break;
		}
		case 0x32 :
		{
		claw_turn0();
				break;
		}

		case 0x36 ://54
		{
			UART1_SendString(UART5_RX_BUF);  //给树莓派发送二维码信息
						
			u2_printf("tt3.txt=\"%d+%d\"",code1,code2);//多次发送给串口屏
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
		case 0x34 :
		{

			break;
		}
		case 0x33 :
		{
		    claw_home();
			break;
		}
				
		
		
		default:
			break;
	}
}
	

/********************
函数功能 : 爪子的初始上升
输入参数 : 无
输出参数 ：无
**********************/
void claw_up_start(void)
{
	Motor1_DIR(1);
	distance1=9800;
	stepPosition1=0;
	MSD_Move1(9800,12,12,16);
	while(1)
	{
		if(stepPosition1 == distance1)
		{
			break;
		}
	}
}



/********************
函数功能 : 爪子的上升
输入参数 : 无
输出参数 ：无
**********************/
void claw_up(void)
{
	Motor1_DIR(1);
	distance1=9600;
	stepPosition1=0;
	MSD_Move1(9600,12,12,16);
	while(1)
	{
		if(stepPosition1 == distance1)
		{
			break;
		}
	}
}
/********************
函数功能 : 爪子的下降
输入参数 : 无
输出参数 ：无
**********************/
void claw_down(void)
{
	Motor1_DIR(0);
	distance1=9600+1500;
	stepPosition1=0;
	MSD_Move1(11100,12,12,16);  // 9600+1500            3600+1500= 5100
	while(1)
	{
		if(stepPosition1 == distance1)
		{
			break;
		}
	}
}
void claw_down2(void)
{
	Motor1_DIR(0);
	distance1=1500;
	stepPosition1=0;
	MSD_Move1(1500,12,12,16);
	while(1)
	{
		if(stepPosition1 == distance1)
		{
			break;
		}
	}
}
///********************
//函数功能 : 爪子的向下  放第二层（1）
//输入参数 : 无
//输出参数 ：无
//**********************/
//void claw_down3(void)
//{
//	Motor1_DIR(0);
//	distance1=6000;
//	stepPosition1=0;
//	MSD_Move1(6000,12,12,16);
//	while(1)
//	{
//		if(stepPosition1 == distance1)
//		{
//			break;
//		}
//	}
//}
///********************
//函数功能 : 爪子的向下  放第二层（2）
//输入参数 : 无
//输出参数 ：无
//**********************/
//void claw_down4(void)
//{
//	Motor1_DIR(0);
//	distance1=5100;
//	stepPosition1=0;
//	MSD_Move1(5100,12,12,16);
//	while(1)
//	{
//		if(stepPosition1 == distance1)
//		{
//			break;
//		}
//	}
//}

//void claw_up2(void)
//{
//	Motor1_DIR(1);
//	distance1=3000;
//	stepPosition1=0;
//	MSD_Move1(3000,12,12,16);
//	while(1)
//	{
//		if(stepPosition1 == distance1)
//		{
//			break;
//		}
//	}
//}
/********************
函数功能 : 爪子的张开，大角度
输入参数 : 无
输出参数 ：无
**********************/

void claw_open(void)
{
		servo_angle2=0;
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);	
}

/********************
函数功能 : 爪子的关闭，对于经典物块
输入参数 : 无
输出参数 ：无
**********************/
void claw_close(void)
{
		servo_angle2=73;
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);	
}

/********************
函数功能 : 爪子的关闭，对于决赛物块
输入参数 : 无
输出参数 ：无
**********************/
void claw_close2(void)
{
		servo_angle2=73;
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);	
}


/********************
函数功能 : 爪子的小角度张开，防止放物块打到
输入参数 : 无
输出参数 ：无
**********************/
void claw_open1(void)
{
		servo_angle2=49;
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);	
}
// 转到前面
/********************
函数功能 : 爪子旋转到0度
输入参数 : 无
输出参数 ：无
**********************/
void claw_turn0(void)
{
		servo_angle3=10;					//56
		SERVO3_CONTRAL(servo_angle3);      //56
}

// 转到后面
/********************
函数功能 : 爪子旋转到129 = (90 + 38.97)度
输入参数 : 无
输出参数 ：无
**********************/
void claw_turn129(void)
{
		servo_angle3=70;
		SERVO3_CONTRAL(servo_angle3);			//230
}

/********************
函数功能 : 爪子旋转到转盘正上方
输入参数 : 无
输出参数 ：无
**********************/
void claw_turn1(void)
{
		servo_angle3 = 162;
		SERVO3_CONTRAL(servo_angle3);
}
/********************
函数功能 : 爪子旋转到位置二
输入参数 : 无
输出参数 ：无
**********************/
void claw_turn2(void)
{
		servo_angle3 = 152;
		SERVO3_CONTRAL(servo_angle3);
}
/********************
函数功能 : 爪子旋转到位置三
输入参数 : 无
输出参数 ：无
**********************/
void claw_turn3(void)
{
		servo_angle3=188;
		SERVO3_CONTRAL(servo_angle3);
}
/********************
函数功能 : 爪子旋转到位置四
输入参数 : 无
输出参数 ：无
**********************/
void claw_turn4(void)
{
		servo_angle3=215;
		SERVO3_CONTRAL(215);
}
/********************
函数功能 : 爪子旋转到位置五
输入参数 : 无
输出参数 ：无
**********************/
void claw_turn5(void)
{
		servo_angle3=250;
		SERVO3_CONTRAL(250);
}


/********************
函数功能 : 载物台的旋转
输入参数 : 无
输出参数 ：无
**********************/
void support_turn120(void)
{
	MSD_Move2(1067,7,7,14);
}
void support_turn35(void)
{
	MSD_Move2(700,1,1,2);
}
void support_turn67(void)
{
	MSD_Move2(400,1,1,2);
}
///********************
//函数功能 : 爪子吧物块放到载物台
//输入参数 : 无
//输出参数 ：无
//**********************/
//void claw_in(void)
//{
//	claw_close();
//	claw_up();          // 9600
//	claw_turn129();
//	delay_ms(1200);
//	delay_ms(1200);
//	claw_down2();       // -1500
//	claw_open();
//	claw_up2();         //  3000
//	claw_turn0();
//	support_turn120();
//	delay_ms(1200);
//	delay_ms(1200);
//	claw_turn0();
//	claw_down();        // -11100
//	delay_ms(1200);	
//	delay_ms(1200);
//}
///********************
//函数功能 : 爪子吧物块拿出载物台 放到第一层
//输入参数 : 无
//输出参数 ：无
//**********************/
//void claw_out(void)
//{
//	claw_open();
//	claw_up();          //   9600
//	claw_turn129();
//	delay_ms(1200);
//	delay_ms(1200);
//	claw_down2();       //  -1500
//	claw_close();
//	claw_up2();         //   3000
//	claw_turn0();
//	support_turn120();
//	delay_ms(1200);
//	delay_ms(1200);
//	claw_turn0();
//	claw_down();       //   -11100
//	delay_ms(1200);	
//	delay_ms(1200);
//	claw_open();
//}
///********************
//函数功能 : 爪子吧物块拿出载物台 放到第二层
//输入参数 : 无
//输出参数 ：无
// //    高度5100
//**********************/
//void claw_out2(void)
//{
//	claw_open();
//	claw_up();         //    9600
//	claw_turn129();
//	delay_ms(1200);
//	delay_ms(1200);
//	claw_down2();     //    -1500
//	claw_close();
//	claw_up2();       //     3000   
//	claw_turn0();
//	support_turn120();
//	delay_ms(1200);
//	delay_ms(1200);
//	claw_turn0();
//	claw_down3();     //    -6000
//	delay_ms(1200);
//	delay_ms(1200);	
//	claw_open();
////  12600-1500-6000 = 5100
//}

///***********************
//摄像头位置
//**********************/
//void task1()
//{
//	
//	
//}
