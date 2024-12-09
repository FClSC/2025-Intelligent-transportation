#ifndef _SERVO_H
#define _SERVO_H

#include "system_init.h"



void Servo1_Init(void);
void Servo2_Init(void);
void Servo3_Init(void);

void SERVO1_CONTRAL(uint8_t angle);
void SERVO2_CONTRAL(uint8_t angle);
void SERVO3_CONTRAL(uint8_t angle);

#endif
