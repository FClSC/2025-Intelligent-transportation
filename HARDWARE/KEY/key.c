#include "key.h"

/********************************
�������� : �����Ŀ���
������� : ��
������� ����
*********************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);	
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
	
}
/********************************
�������� : ����KEY0�Ķ�ȡ
������� : ��
������� �����·���1��û�а��·���0
*********************************/
u8 click0(void)
{
			static u8 flag_key=1;//�������ɿ���־
			if(flag_key&&WAKE_UP==1)
			{
			flag_key=0;
			return 1;	// ��������
			}
			else if(0==WAKE_UP)			flag_key=1;
			return 0;//�ް�������
}
/********************************
�������� : ����KEY1�Ķ�ȡ
������� : ��
������� �����·���1��û�а��·���0
*********************************/
u8 click1(void)
{
			static u8 flag_key=1;//�������ɿ���־
			if(flag_key&&KEY0==1)
			{
			flag_key=0;
			return 1;	// ��������
			}
			else if(0==KEY0)			flag_key=1;
			return 0;//�ް�������
}
/********************************
�������� : PCB�����ϰ���KEY1�Ķ�ȡ
������� : ��
������� �����·���1��û�а��·���0
*********************************/
u8 clickKEY1(void)
{
			static u8 flag_key=1;//�������ɿ���־
			if(flag_key&&KEY1==1)
			{
			flag_key=0;
			return 1;	// ��������
			}
			else if(0==KEY1)			flag_key=1;
			return 0;//�ް�������
}
/********************************
�������� : PCB�����ϰ���KEY2�Ķ�ȡ
������� : ��
������� �����·���1��û�а��·���0
*********************************/
u8 clickKEY2(void)
{
			static u8 flag_key=1;//�������ɿ���־
			if(flag_key&&KEY2==1)
			{
			flag_key=0;
			return 1;	// ��������
			}
			else if(0==KEY2)			flag_key=1;
			return 0;//�ް�������
}
