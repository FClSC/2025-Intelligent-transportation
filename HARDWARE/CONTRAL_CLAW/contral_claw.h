#ifndef _CONTRAL_CLAW_H
#define _CONTRAL_CLAW_H

#include "system_init.h"

#define claw_most_up    175     //            ������ߵ�λ��            
#define camera_position  0       //               ɨ���λ��
#define claw_block_get    4      //      ����ץ���ĸ߶�  28

#define put_block_down   4       //      ���Ϸ����ĸ߶�28

#define claw_block_get1  103    //     ������ת����ץ���ĸ߶�

#define claw_block_put   135 //        ���Ϸ�����λ��

#define get_block_down    132   //       �ӳ���ץȡҪ��������ȥ��λ��

#define put_block_down2   87   //     ���������ڶ���ĸ߶�

#define circle_capture1  0   //          һ����ð���ʶ��ĸ߶�

#define circle_capture3  160   //     ����������ʶ��ĸ߶�

#define circle_capture2  114    //��������ɫʶ��λ�ã�Ҫ���ڵȻ�ץȡ���ĸ߶�



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
void claw_put_block2(void);


void claw_home(void);



#endif
