#ifndef _MOTOR_H
#define _MOTOR_H

#include "system_init.h"
/******************定时器初始化*********************/
#define TIM2_ARR 100-1
#define TIM2_PSC 72-1
#define TIM2_CCR 50-1

#define TIM3_ARR 100-1
#define TIM3_PSC 72-1
#define TIM3_CCR 50-1

#define TIM4_ARR 100-1
#define TIM4_PSC 72-1
#define TIM4_CCR 50-1

#define TIM5_ARR 100-1
#define TIM5_PSC 72-1
#define TIM5_CCR 50-1


/******************脉冲控制引脚*********************/
#define MOTOR_STEP1 PBout(10)
#define MOTOR_STEP2 PBout(11)
#define MOTOR_STEP3 PCout(6)
#define MOTOR_STEP4 PCout(7)
#define MOTOR_STEP5 PBout(8)
#define MOTOR_STEP6 PBout(9)
#define MOTOR_STEP7 PCout(8)
#define MOTOR_STEP8 PCout(9)
/******************步进电机方向控制引脚*********************/
#define MOTOR_DIR1 PAout(4)
#define MOTOR_DIR2 PAout(5)
#define MOTOR_DIR3 PGout(7)
#define MOTOR_DIR4 PGout(8)
#define MOTOR_DIR5 PGout(13)
#define MOTOR_DIR6 PEout(6)
#define MOTOR_DIR7 PAout(8)
#define MOTOR_DIR8 PCout(1)



void MOTOR1_Init(void);
void MOTOR2_Init(void);
void MOTOR3_Init(void);
void MOTOR4_Init(void);
void MOTOR5_Init(void);
void MOTOR6_Init(void);
void MOTOR7_Init(void);
void MOTOR8_Init(void);



void TIM3_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
#endif


