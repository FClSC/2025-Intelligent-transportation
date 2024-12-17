#include "contral.h"
#include <stdio.h>
#include <math.h>

speedRampData srd;
speedRampData srd1;
speedRampData srd2;

uint8_t servo_angle1;
uint8_t servo_angle2;
uint8_t servo_angle3;


int stepPosition = 0;
int stepPosition1 = 0;
int stepPosition2 = 0;

int distance=0;
uint16_t angle_temp=0;

int distance1=0;

// ��ʱ��3
/*******************************************
�������� : ����С�����̵ĳ�ʼ��
������� : ��
������� ����
********************************************/
void contral_motor_Init(void)
{
	MOTOR3_Init();
	MOTOR4_Init();
	MOTOR7_Init();
	MOTOR8_Init();
}
// ��ʱ��2
/*******************************************
�������� : ����צ��ץȡ�ĳ�ʼ��
������� : ��
������� ����
********************************************/
void claw_Init(void)
{
	MOTOR1_Init();//����
	MOTOR5_Init();//ת��
	Servo2_Init();
	Servo3_Init();
	claw_turn0();
	
	claw_open();
	claw.position_now=0;  
	claw.position_target=0;
	claw.position_temp=0;
}
/*************************
��ʱ��3 �Ŀ���
���ƶ��� С������
С������ �� ����С�������˶�
������� �� ���� ���ٶ� ���ٶ� �ٶ�
������� �� ��
**************************/
void MSD_Move(signed int step, unsigned int accel, unsigned int decel, unsigned int speed)
{
    uint16_t max_s_lim;
    uint16_t accel_lim; 
    if(step > 0)//��ʱ��
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
			// ������ٲ�֮��ﵽ����ٶȵ�����
			max_s_lim = (long)speed*speed/(long)(((long)A_x20000*accel)/100);
			// ����ﵽ����ٶ�С��0.5�������ǽ���������Ϊ0
			// ��ʵ�����Ǳ����ƶ�����һ�����ܴﵽ��Ҫ���ٶ�
			if(max_s_lim == 0)
			{
					max_s_lim = 1;
			}
			// ������ٲ�֮�����Ǳ��뿪ʼ����
			accel_lim = ((long)step*decel) / (accel+decel);
			// ���Ǳ����������1�����ܲ��ܿ�ʼ����.
			if(accel_lim == 0)
			{
					accel_lim = 1;
			}
			// ʹ�������������ǿ��Լ������һ�ο�ʼ���ٵ�λ��
			if(accel_lim <= max_s_lim)
			{
					srd.decel_val = accel_lim - step;
			}
			else
			{
					srd.decel_val = -(long)(max_s_lim*accel/decel);
			}
			// ��ֻʣ��һ�����Ǳ������
			if(srd.decel_val == 0)
			{
					srd.decel_val = -1;
			}
			// ���㿪ʼ����ʱ�Ĳ���
			srd.decel_start = step + srd.decel_val;
			// �������ٶȺ��������ǾͲ���Ҫ���м����˶�
			if(srd.step_delay <= srd.min_delay)
			{
					srd.step_delay = srd.min_delay;
					srd.run_state = RUN;
			}
			else
		  {
					srd.run_state = ACCEL;
			} 
			// ��λ���ٶȼ���ֵ
			srd.accel_count = 0;
			//���ö�ʱ����װֵ	
			TIM_SetAutoreload(TIM3,Pulse_width);
			TIM_SetCompare1(TIM3,Pulse_width_comper); 
			TIM_SetCompare2(TIM3,Pulse_width_comper); 					
			TIM_SetCompare3(TIM3,Pulse_width_comper); 
			TIM_SetCompare4(TIM3,Pulse_width_comper); 		
			//ʹ�ܶ�ʱ��	      
			TIM_Cmd(TIM3, ENABLE); 
    }
}
/*************************
��ʱ��2 �Ŀ���
���ƶ��� ץȡ����
���� �� ����ץȡ�������������½�
������� �� ���� ���ٶ� ���ٶ� �ٶ�
������� �� ��
**************************/
void MSD_Move1(signed int step, unsigned int accel, unsigned int decel, unsigned int speed)
{
    uint16_t max_s_lim;
    uint16_t accel_lim; 
    if(step > 0)//��ʱ��
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
		TIM_SetCompare4(TIM2,Pulse_width_comper); //��һ��û��Ҫ
        TIM_Cmd(TIM2, ENABLE); 
     }
    else if(step != 0)
    {
				accel = accel*100; 
				decel = decel*100;
				speed = speed*100;
			srd1.min_delay = A_T_x100 / speed;
			srd1.step_delay = (T1_FREQ_148 * sqrt(A_SQ / accel))/100;
			// ������ٲ�֮��ﵽ����ٶȵ�����
			max_s_lim = (long)speed*speed/(long)(((long)A_x20000*accel)/100);
			// ����ﵽ����ٶ�С��0.5�������ǽ���������Ϊ0
			// ��ʵ�����Ǳ����ƶ�����һ�����ܴﵽ��Ҫ���ٶ�
			if(max_s_lim == 0)
			{
					max_s_lim = 1;
			}
			// ������ٲ�֮�����Ǳ��뿪ʼ����
			accel_lim = ((long)step*decel) / (accel+decel);
			// ���Ǳ����������1�����ܲ��ܿ�ʼ����.
			if(accel_lim == 0)
			{
					accel_lim = 1;
			}
			// ʹ�������������ǿ��Լ������һ�ο�ʼ���ٵ�λ��
			if(accel_lim <= max_s_lim)
			{
					srd1.decel_val = accel_lim - step;
			}
			else
			{
					srd1.decel_val = -(long)(max_s_lim*accel/decel);
			}
			// ��ֻʣ��һ�����Ǳ������
			if(srd1.decel_val == 0)
			{
					srd1.decel_val = -1;
			}
			// ���㿪ʼ����ʱ�Ĳ���
			srd1.decel_start = step + srd1.decel_val;
			// �������ٶȺ��������ǾͲ���Ҫ���м����˶�
			if(srd1.step_delay <= srd1.min_delay)
			{
					srd1.step_delay = srd1.min_delay;
					srd1.run_state = RUN;
			}
			else
		  {
					srd1.run_state = ACCEL;
			} 
			// ��λ���ٶȼ���ֵ
			srd1.accel_count = 0;
			//���ö�ʱ����װֵ	
			TIM_SetAutoreload(TIM2,Pulse_width);
			//����ռ�ձ�Ϊ50%	
			TIM_SetCompare3(TIM2,Pulse_width_comper);
			TIM_SetCompare4(TIM2,Pulse_width_comper);			
			//ʹ�ܶ�ʱ��	      
			TIM_Cmd(TIM2, ENABLE); 
    }
}
/*************************
��ʱ��4 �Ŀ���
���ƶ��� ת�̻���
���� �� ����ת�̵���ת
������� �� ���� ���ٶ� ���ٶ� �ٶ�
������� �� ��
**************************/
void MSD_Move2(signed int step, unsigned int accel, unsigned int decel, unsigned int speed)
{
    uint16_t max_s_lim;
    uint16_t accel_lim; 
    if(step > 0)//��ʱ��
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
		TIM_SetCompare4(TIM4,Pulse_width_comper); //��һ��û��Ҫ,2024/12/10
        TIM_Cmd(TIM4, ENABLE); 
     }
    else if(step != 0)
    {
				accel = accel*100; 
				decel = decel*100;
				speed = speed*100;
			srd2.min_delay = A_T_x100 / speed;
			srd2.step_delay = (T1_FREQ_148 * sqrt(A_SQ / accel))/100;
			// ������ٲ�֮��ﵽ����ٶȵ�����
			max_s_lim = (long)speed*speed/(long)(((long)A_x20000*accel)/100);
			// ����ﵽ����ٶ�С��0.5�������ǽ���������Ϊ0
			// ��ʵ�����Ǳ����ƶ�����һ�����ܴﵽ��Ҫ���ٶ�
			if(max_s_lim == 0)
			{
					max_s_lim = 1;
			}
			// ������ٲ�֮�����Ǳ��뿪ʼ����
			accel_lim = ((long)step*decel) / (accel+decel);
			// ���Ǳ����������1�����ܲ��ܿ�ʼ����.
			if(accel_lim == 0)
			{
					accel_lim = 1;
			}
			// ʹ�������������ǿ��Լ������һ�ο�ʼ���ٵ�λ��
			if(accel_lim <= max_s_lim)
			{
					srd2.decel_val = accel_lim - step;
			}
			else
			{
					srd2.decel_val = -(long)(max_s_lim*accel/decel);
			}
			// ��ֻʣ��һ�����Ǳ������
			if(srd2.decel_val == 0)
			{
					srd2.decel_val = -1;
			}
			// ���㿪ʼ����ʱ�Ĳ���
			srd2.decel_start = step + srd2.decel_val;
			// �������ٶȺ��������ǾͲ���Ҫ���м����˶�
			if(srd2.step_delay <= srd2.min_delay)
			{
					srd2.step_delay = srd2.min_delay;
					srd2.run_state = RUN;
			}
			else
		  {
					srd2.run_state = ACCEL;
			} 
			// ��λ���ٶȼ���ֵ
			srd2.accel_count = 0;
			//���ö�ʱ����װֵ	
			TIM_SetAutoreload(TIM4,Pulse_width);
			//����ռ�ձ�Ϊ50%	
			TIM_SetCompare3(TIM4,Pulse_width_comper);
			TIM_SetCompare4(TIM4,Pulse_width_comper);			
			//ʹ�ܶ�ʱ��	      
			TIM_Cmd(TIM4, ENABLE); 
    }
}

/*************************
��ʱ��3 �Ŀ���
���ƶ��� С������
���� �� �ۼƵ��̵�������
������� �� ����
������� �� ��
**************************/
void MSD_StepCounter(signed char inc)
{
  //���ݷ����жϵ��λ��
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
��ʱ��2 �Ŀ���
���ƶ��� ץȡ����
���� �� ����ץȡ�����Ĳ���
������� �� ����
������� �� ��
**************************/
void MSD_StepCounter1(signed char inc)
{
  //���ݷ����жϵ��λ��
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
��ʱ��4 �Ŀ���
���ƶ��� ת�̻���
���� �� ����ת�̵Ĳ���
������� �� ����
������� �� ��
**************************/
void MSD_StepCounter2(signed char inc)
{
  //���ݷ����жϵ��λ��
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
��ʱ��2 �Ŀ���
���� �� ���Ƶ��1�ķ���
������� �� ����
������� �� ��
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
�������� : ����С�����̵��ƶ�����
������� : ����
������� ����
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
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
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
�������� : ����С���ƶ�����ĺ���
������� : x��λ�ƣ�y��λ��
������� ����
**********************/
void MOTOR_Direction(int16_t x,int16_t y)
{
	// x��ֵ
	if(x<0) {DIR1(0); DIR2(0);DIR3(0); DIR4(0);}
	else if(x>0)  {DIR1(1); DIR2(1);DIR3(1); DIR4(1);}
	// y��ֵ	
	if(y>0) {DIR1(0); DIR2(1);DIR3(0); DIR4(1);}
	else if(y<0) {DIR1(1); DIR2(0);DIR3(1); DIR4(0);}
}
/********************
�������� : ����ֵ����
������� : ����ֵ
������� ����
**********************/
uint16_t abs_int(int16_t x)
{
	if(x>0) return x;
	else return -x;
}
/********************
�������� : �õ�x��y��������λ�Ƶĺ���
������� : x��λ�ƣ�y��λ��
������� ����
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
�������� : ����С����ת����ĺ���
������� : ��ת�Ƕ�
������� ����
**********************/
void MOTOR_TURN(int16_t angle)
{
	if(angle>0)  {DIR1(0); DIR2(1);DIR3(1); DIR4(0);}
	else if(angle<0) {DIR1(1); DIR2(0);DIR3(0); DIR4(1);}
}
/********************
�������� : ����С��λ�ƺ���
������� : x�����cm��y�����cm����
������� ����
**********************/
void MOTOR_Displacement(int16_t x_cm,int16_t y_cm)
{
	int temp=0;
	// ���жϷ���
	MOTOR_Direction(x_cm,y_cm);
	// �˶�����
	temp=max_Return(x_cm,y_cm);
	//     3200        x/a = 78/3200     
	distance=temp*130;  //�������cm 
	MSD_Move(distance,18,18,24);
}
/********************
�������� : ����С���ǶȺ���
������� : ��ʱ����ת�ĽǶ�
������� ����
**********************/
void MOTOR_Angle(int8_t angle)
{
	MOTOR_TURN(angle);
	angle_temp = abs_int(angle*50);
	MSD_Move(angle_temp,6,6,12);
}
/********************
�������� : ����С��λ�ƺ���
������� : x�����mm��y�����mm����
������� ����
**********************/
void MOTOR_Displacement_mm(int16_t x_mm,int16_t y_mm)
{
	int temp=0;
	distance=0;
	// ���жϷ���
	MOTOR_Direction(x_mm,y_mm);
	// �˶�����
	temp=max_Return(x_mm,y_mm);
	//     3200        x/a = 78/3200 
	distance=temp*13;  //�������mm 
	MSD_Move(distance,4,4,10);//
}
/********************
�������� : ������λ�����͵���Ϣ
������� : ��
������� ����
**********************/
void uart_handle(void)
{
	uint8_t mode=0x00;
	mode = Serial_RXPacket[0];   //����ģʽ
	int8_t x_dis = 0;
	int8_t y_dis = 0;	
	int8_t angle = 0;		
	uint16_t code1 =0; 
	uint16_t code2 =0; 	
	uint8_t position_camera = 0;
//	uint16_t dis_claw = 0;
	uint8_t claw_mode=0;
	int8_t move_mode=0;
//	uint8_t mode_get=0;
//	uint8_t mode_put=0;
	
	switch(mode)
	{
		case 0x01:  //xλ��
		{
			x_dis = Serial_RXPacket[1];
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
		case 0x02:  //yλ��
		{
			y_dis = Serial_RXPacket[2];
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
		case 0x03:  //�Ƕ�
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
			break;
		}			
		case 0x04:  //�õ�Ƭ��ɨ��
		{
			UART5_Start_Scan();
			break;
		}	
		case 0x05:  //����ʶ��x����
		{
			x_dis = Serial_RXPacket[1];
			stepPosition=0;
			MOTOR_Displacement_mm(x_dis,0);
			while(1)
			{
				if(stepPosition == distance)
				{
					break;
				}
			}
			break;
		}		
		case 0x06:  //����ʶ��y����
		{
			y_dis = Serial_RXPacket[2];
			stepPosition=0;
			MOTOR_Displacement_mm(0,y_dis);
			while(1)
			{
				if(stepPosition == distance)
				{
					break;
				}
			}
			break;
		}	
		//0x7-0x9  ������̨������ų���
		case 0x07:     //��������ת�̰ᵽ����
		{
            claw_get_block1();
			break;
		}

        case 0x08:     //��������ת�̰ᵽ����2��λ
		{

			break;
		}

		case 0x09:     //��������ת�̰ᵽ����3��λ
		{

			break;
		}

		case 0x0B: // ����ָ��λ��
		{
			position_camera=Serial_RXPacket[1];
			switch (position_camera)
			{
				case 0x01:
				{
						claw_turn0();
						arrive_camera();   //�����ά��
					  break;
				}
				case 0x02:
				{
						arrive_color_reco();   //����ת�̶�ȡ��ɫ
					  break;					
				}
				case 0x03:
				{
						arrive_circle_capture();   //�������ʶ��1
					  break;					
				}	
				case 0x04:
				{
					    arrive_put_down2();   //ʶ��������ĸ߶ȣ��д��ı�
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
			claw_mode=Serial_RXPacket[1];   //צ��ģʽ
			move_mode=Serial_RXPacket[2];   //�ƶ�����
			
			switch(claw_mode)
			{
				case 0x01:  //�����ά��
				{	
					stepPosition=0;   //��
					stepPosition1=0;  //ץ
					MOTOR_Displacement(move_mode,0);
					claw_turn0();
					delay_ms(100);  //��ִ���ܵ���ִ��������
					arrive_camera();
					
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //���������
						{
							break;
						}
					}	
					break;
				}
				case 0x02:     //��������̨
				{
					stepPosition=0;   //��
					stepPosition1=0;  //ץ
					MOTOR_Displacement(move_mode,0);
					delay_ms(200);  //��ִ���ܵ���ִ��������
					arrive_color_reco();  //�������ɫʶ��߶ȣ�
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //���������
						{
							break;
						}
					}						
					break;
				}
				case 0x03:  // �������ʶ��1
				{
					stepPosition=0;   //��
					stepPosition1=0;  //ץ
					MOTOR_Displacement(move_mode,0);
					delay_ms(200);  //��ִ���ܵ���ִ��������
					arrive_circle_capture();
					while(1)
					{
						if((stepPosition == distance)&&(stepPosition1 == distance1))   //���������
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

		//0x11-0x13  �ӵ��������ų���
		case 0x11:                     //���Ͽ��ȡ�����ӵ��ϼ�ȡ֮����õ���Ӧλ��Ȼ��צ���ֻ�ص�ʶ���λ��
		{

			claw_get_block();
			break;
		}
		case 0x12:
		{

			break;
		}
		case 0x13:
		{

			break;
		}		
		case 0x21:  //���ŵ���
		{
			claw_put_block();   
			break;
		}
		case 0x22:
		{

			break;
		}
		case 0x23:
		{

			break;
		}
		case 0x24:   //�ӳ��ϵ�1��λ�뵽�ڶ���
		{
             claw_put_blockF2();
			 break;
		}
		case 0x25:  
		{

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

		case 0x36 ://53
		{
			UART5_PraseCode(UART5_RX_BUF,&code1,&code2);//��������ά������
			u2_printf("t3.txt=\"%d+%d\"",code1,code2);//��η��͸�������
			delay_ms(10);
			u2_printf("t3.txt=\"%d+%d\"",code1,code2);
			delay_ms(10);
			u2_printf("t3.txt=\"%d+%d\"",code1,code2);
			delay_ms(10);
			u2_printf("t3.txt=\"%d+%d\"",code1,code2);
			delay_ms(10);
			u2_printf("t3.txt=\"%d+%d\"",code1,code2);
			delay_ms(100);
            UART1_SendString(UART5_RX_BUF);  //����ݮ�ɷ��Ͷ�ά����Ϣ
			break;
		}
		case 0x34 ://52
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
�������� : צ�ӵĳ�ʼ����
������� : ��
������� ����
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
�������� : צ�ӵ�����
������� : ��
������� ����
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
�������� : צ�ӵ��½�
������� : ��
������� ����
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
//�������� : צ�ӵ�����  �ŵڶ��㣨1��
//������� : ��
//������� ����
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
//�������� : צ�ӵ�����  �ŵڶ��㣨2��
//������� : ��
//������� ����
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
�������� : צ�ӵ��ſ�
������� : ��
������� ����
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
�������� : צ�ӵĹر�
������� : ��
������� ����
**********************/
void claw_close(void)
{
		servo_angle2=60;
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);	
}

/********************
�������� : צ�ӵ��ſ�
������� : ��
������� ����
**********************/
void claw_open1(void)
{
		servo_angle2=60;
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);
		SERVO2_CONTRAL(servo_angle2);
		delay_ms(25);	
}
// ת��ǰ��
/********************
�������� : צ����ת��0��
������� : ��
������� ����
**********************/
void claw_turn0(void)
{
		servo_angle3=0;					//56
		SERVO3_CONTRAL(servo_angle3);      //56
}

// ת������
/********************
�������� : צ����ת��129 = (90 + 38.97)��
������� : ��
������� ����
**********************/
void claw_turn129(void)
{
		servo_angle3=70;					//230
		SERVO3_CONTRAL(servo_angle3);			//230
}

/********************
�������� : צ����ת��ת�����Ϸ�
������� : ��
������� ����
**********************/
void claw_turn1(void)
{
		servo_angle3 = 147;
		SERVO3_CONTRAL(servo_angle3);
}
/********************
�������� : צ����ת��λ�ö�
������� : ��
������� ����
**********************/
void claw_turn2(void)
{
		servo_angle3 = 152;
		SERVO3_CONTRAL(servo_angle3);
}
/********************
�������� : צ����ת��λ����
������� : ��
������� ����
**********************/
void claw_turn3(void)
{
		servo_angle3=188;
		SERVO3_CONTRAL(servo_angle3);
}
/********************
�������� : צ����ת��λ����
������� : ��
������� ����
**********************/
void claw_turn4(void)
{
		servo_angle3=215;
		SERVO3_CONTRAL(215);
}
/********************
�������� : צ����ת��λ����
������� : ��
������� ����
**********************/
void claw_turn5(void)
{
		servo_angle3=250;
		SERVO3_CONTRAL(250);
}


/********************
�������� : ����̨����ת
������� : ��
������� ����
**********************/
void support_turn120(void)
{
	MSD_Move2(1067,1,1,2);
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
//�������� : צ�Ӱ����ŵ�����̨
//������� : ��
//������� ����
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
//�������� : צ�Ӱ�����ó�����̨ �ŵ���һ��
//������� : ��
//������� ����
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
//�������� : צ�Ӱ�����ó�����̨ �ŵ��ڶ���
//������� : ��
//������� ����
// //    �߶�5100
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
//����ͷλ��
//**********************/
//void task1()
//{
//	
//	
//}
