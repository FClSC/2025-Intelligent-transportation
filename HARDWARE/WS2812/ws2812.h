#ifndef _WS2812_H
#define _WS2812_H
#include "system_init.h"
#include "stm32f10x.h"
#define WS2812_NUM_LEDS 12
#define WS2812_BUFFER_SIZE (WS2812_NUM_LEDS * 24) // ??LED 24bit
#define WS2812_0 29      // 0??????0.4us (72MHz?????)
#define WS2812_1 58      // 1??????0.8us


void WS2812_Init(void);
void WS2812_SetColor(uint8_t led_num, uint32_t grb_color);
void WS2812_Update(void);
void ws2812_ON(void);






#endif
