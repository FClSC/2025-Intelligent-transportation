#ifndef _LED_H
#define _LED_H

#include "sys.h"

#define LED0 PBout(5) 
#define LED1 PEout(5) 


void LED_Init(void);
void LED_Turn(void);

#endif
