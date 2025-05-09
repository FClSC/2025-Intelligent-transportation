#ifndef _CONTRAL_CLAW_H
#define _CONTRAL_CLAW_H

#include "system_init.h"

//通用高度
/*对于物料转盘抓取时候的80-100mm
转盘  物块5.5cm处爪子高度
80mm  13.5cm 99

85mm 14.0cm 105

90mm 14.5cm  111

95mm 15.0cm 117

100mm 15.5cm 123

计算公式为：爪子脉冲高度=99+(转盘实际高度-80)/20*24

*/
#define claw_most_up    175     //            升到最高的位置            
#define camera_position  0       //               扫码的位置（最低）
#define circle_capture1  0   //          一层放置靶心识别的高度
#define circle_capture3  25   //     二层码垛靶心识别的高度   160
#define circle_capture2  114    //物料盘颜色识别位置，要高于等会抓取物块的高度

//普通经典物块
#define claw_block_get    6      //      地上抓物块的高度  4

#define put_block_down   6       //      地上放物块的高度  4

extern int16_t claw_block_get1 ;    //     从物料转盘上抓物块的高度    需要进行更改的，设为变量，可以软件进行修改

#define claw_block_put   135 //        车上放物块的位置

#define get_block_down    132   //       从车上抓取要把物块放下去的位置

#define put_block_down2   87   //     把物块叠放在二层的高度

#define claw_block_putF2  165    //车上把物块放到转盘二层的高度

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
void arrive_block_putF2(void);

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
