#ifndef _CONTRAL_CLAW_H
#define _CONTRAL_CLAW_H

#include "system_init.h"

#define claw_most_up    195     //            ������ߵ�λ��            
#define camera_position  20       //               ɨ���λ��
#define claw_block_get   28       //      ����ץ���ĸ߶�  25

#define put_block_down   28       //      ���Ϸ����ĸ߶�26

#define claw_block_get1  90    //     ������ת����ץ���ĸ߶�

#define claw_block_put   158 //        ���Ϸ�����λ��

#define get_block_down    150   //       �ӳ���ץȡҪ��������ȥ��λ��

#define put_block_down2   111   //     ���������ڶ���ĸ߶�

#define circle_capture1  80   //          һ����ð���ʶ��ĸ߶�

#define circle_capture3  180   //     ����������ʶ��ĸ߶�

#define circle_capture2  102    //��������ɫʶ��λ�ã�Ҫ���ڵȻ�ץȡ���ĸ߶�



typedef struct {
	int16_t position_now;             //��ǰֵ
	int16_t position_target;           //Ŀ��ֵ
	int16_t position_temp;             //��ʱֵ���м��ֵ��
}CLAW_POSITION;

extern CLAW_POSITION claw;





void claw_position(int16_t position);
void claw_position2(int16_t position);

void arrive_camera(void);
void arrive_most_up(void);
void arrive_block_get(void);
void arrive_block_put(void);
void arrive_block_get1(void);
void arrive_car_put(void);
void arrive_car_get(void);
void arrive_put_down2(void);
void arrive_circle_capture(void);
void arrive_circle_capture2(void);
void arrive_color_reco(void);
void claw_get_block(void);
void claw_get_block1(void);
void claw_put_block(void);
void claw_put_blockF2(void);


void claw_home(void);



#endif
