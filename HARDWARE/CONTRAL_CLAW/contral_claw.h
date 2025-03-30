#ifndef _CONTRAL_CLAW_H
#define _CONTRAL_CLAW_H

#include "system_init.h"

//通用高度
#define claw_most_up    175     //            升到最高的位置            
#define camera_position  0       //               扫码的位置（最低）
#define circle_capture1  0   //          一层放置靶心识别的高度
#define circle_capture3  160   //     二层码垛靶心识别的高度
#define circle_capture2  114    //物料盘颜色识别位置，要高于等会抓取物块的高度

//普通经典物块
#define claw_block_get    4      //      地上抓物块的高度  28

#define put_block_down   4       //      地上放物块的高度28

#define claw_block_get1  103    //     从物料转盘上抓物块的高度

#define claw_block_put   135 //        车上放物块的位置

#define get_block_down    132   //       从车上抓取要把物块放下去的位置

#define put_block_down2   87   //     把物块叠放在二层的高度

//决赛物块
#define claw_block2_get    4      //      地上抓物块2的高度  28

#define put_block2_down   4       //      地上放物块2的高度28

#define claw_block2_get1  103    //     从物料转盘上抓物块2的高度

#define claw_block2_put   135 //        车上放物块2的位置

#define get_block2_down    132   //       从车上抓取要把物块2放下去的位置

#define put_block2_down2   87   //     把物块2叠放在二层的高度


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
void arrive_circle_capture(void);
void arrive_circle_capture2(void);
void arrive_color_reco(void);

void arrive_block_get(void);
void arrive_block_put(void);
void arrive_block_get1(void);
void arrive_car_put(void);
void arrive_car_get(void);
void arrive_put_down2(void);

void arrive_block2_get(void);
void arrive_block2_put(void);
void arrive_block2_get1(void);
void arrive_car2_put(void);
void arrive_car2_get(void);
void arrive_put2_down2(void);


void claw_get_block(void);
void claw_get_block1(void);
void claw_put_block(void);
void claw_put_blockF2(void);
void claw_put_block2(void);


void claw_get2_block(void);
void claw_get2_block1(void);
void claw_put2_block(void);
void claw_put2_blockF2(void);
void claw_put2_block2(void);

void claw_home(void);



#endif
