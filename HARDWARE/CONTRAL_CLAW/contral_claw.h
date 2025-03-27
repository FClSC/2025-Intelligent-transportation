#ifndef _CONTRAL_CLAW_H
#define _CONTRAL_CLAW_H

#include "system_init.h"

#define claw_most_up    195     //            升到最高的位置            
#define camera_position  20       //               扫码的位置
#define claw_block_get   28       //      地上抓物块的高度  25

#define put_block_down   28       //      地上放物块的高度26

#define claw_block_get1  90    //     从物料转盘上抓物块的高度

#define claw_block_put   158 //        车上放物块的位置

#define get_block_down    150   //       从车上抓取要把物块放下去的位置

#define put_block_down2   111   //     把物块叠放在二层的高度

#define circle_capture1  80   //          一层放置靶心识别的高度

#define circle_capture3  180   //     二层码垛靶心识别的高度

#define circle_capture2  102    //物料盘颜色识别位置，要高于等会抓取物块的高度



typedef struct {
	int16_t position_now;             //当前值
	int16_t position_target;           //目标值
	int16_t position_temp;             //临时值（中间差值）
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
