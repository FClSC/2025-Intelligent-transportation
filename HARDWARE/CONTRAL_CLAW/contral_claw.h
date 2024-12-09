#ifndef _CONTRAL_CLAW_H
#define _CONTRAL_CLAW_H

#include "system_init.h"

#define claw_most_up    180   // 280mm      64*170 = 10880脉冲         升到最高的位置            

#define camera_position 0  // 140mm      64*140 = 8960脉冲          扫码的位置

#define claw_block_get  0     // 153mm      64*153 = 9792脉冲          地上 抓放物块的位置
#define claw_block_get1  90  //80mm   应当低于颜色识别的高度
#define claw_block_get2  82  //18mm
#define claw_block_get3  46  //36mm

//#define claw_block_put   195 // 153mm       64*153 = 9792脉冲         车上 放物块的位置


#define get_block_down    86   // 127mm       64*127 = 8128脉冲         车上抓取的位置

#define circle_capture1  80   // 127mm       64*127 = 8128脉冲         靶心识别的位置

//#define recognaze_height 80   // 127mm       64*127 = 8128脉冲         物块颜色识别的位置

#define circle_capture2  102    //物料盘颜色识别位置，要高于等会抓取物块的高度

//#define claw_block_get2  18  

//#define claw_block_get3  36  

typedef struct {
	int16_t position_now;             //当前值
	int16_t position_target;           //目标值
	int16_t position_temp;             //临时值（中间差值）
}CLAW_POSITION;

extern CLAW_POSITION claw;





void claw_position(int16_t position);


void arrive_camera(void);
void arrive_camera2(void);
void arrive_block_get(void);
void arrive_block_get1(void);
void arrive_block_putF2(void);
void arrive_block_get3(void);
void arrive_block_put(void);
void arrive_most_up(void);
void arrive_block_down(void);
void arrive_circle_capture(void);
void arrive_circle_capture2(void);


void claw_get_block1(void);
void claw_get_block2(void);
void claw_get_block3(void);
void claw_get_block4(void);
void claw_get_block5(void);
void claw_get_block6(void);
void claw_put_1blockF2(void);
void claw_put_2blockF2(void);
void claw_put_3blockF2(void);
void claw_turn0(void);
void claw_turn1(void);
void claw_turn2(void);
void claw_turn3(void);

void claw_put_block1(void);
void claw_put_block2(void);
void claw_put_block3(void);
void claw_put_block4(void);
void claw_put_block5(void);
void claw_put_block6(void);
void claw_put_block7(void);
void claw_home(void);



#endif
