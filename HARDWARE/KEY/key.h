#ifndef _KEY_H
#define _KEY_H

#include "sys.h"

#define KEY0 		PEin(4) 
#define WAKE_UP PAin(0) 
#define KEY1 PDin(0) 
#define KEY2 PDin(3) 

void KEY_Init(void);
u8 click0(void);
u8 click1(void);
u8 clickKEY1(void);
u8 clickKEY2(void);

#endif
