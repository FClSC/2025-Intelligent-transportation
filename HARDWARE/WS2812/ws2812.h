#ifndef _WS2812_H
#define _WS2812_H

#include "system_init.h"

#define WS2812_LED_NUM 	14

// 11111000  SIG_1   5/8 = 62.5%
// 11100000  SIG_0   3/8 = 37.5%

#define 		SIG_1 		0XF8
#define 		SIG_0  		0XE0


//       ÑÕÉ«     GRB
#define	C_Red		0x00FF00
#define	C_Green		0xFF0000
#define	C_Blue		0x0000FF
#define	C_Yellow   	0xFFFF00
#define	C_Purple	0x00FFFF
#define	C_Orange	0x7DFF00
#define	C_indigo	0xFF00FF
#define	C_white 	0xFFFFFF




typedef struct RGB_Color{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char l;
}RGB_Color;

typedef struct HSV_Color{
	float H;
	float S;
	float V;
}HSV_Color;


enum Color
{
	Red,
	Green,
	Blue,
	Yellow,
	Purple,
	Orange,
	Indigo,
	White,
};



void ws2812_GPIO_Init(void);
void ws2812_SPI_Init(void);
void ws2812_DMA_Init(void);
void ws2812_AllShutOff(void);
void ws2812_Send_Data(void);
void ws2812_Init(void);
void ws2812_AllOpen(uint8_t red ,uint8_t green ,uint8_t blue);
uint32_t ws281x_color(uint8_t red, uint8_t green, uint8_t blue);

void ws281x_setPixelRGB(uint16_t n ,uint8_t red, uint8_t green, uint8_t blue);
void set_pixel_rgb(uint16_t n,u8 color);
void ws2812_Set_one_LED_Color(uint16_t LED_index ,uint32_t GRB_color);
uint32_t ws2812_LED_Gray2GRB(uint8_t LED_gray);
void ws2812_Roll_on_Color_Ring(uint16_t interval_time);
void ws2812_All_LED_one_Color_breath(uint16_t interval_time, uint32_t GRB_color);
void horse_race_lamp(uint16_t interval_time);
void Running_water_lamp( uint8_t green ,uint8_t red ,uint8_t blue, uint16_t interval_time );
void srand_lamp(uint16_t interval_time);
float __getMaxValue(float a, float b);
float __getMinValue(float a, float b);
void __RGB_2_HSV(RGB_Color RGB, HSV_Color *HSV);
void __HSV_2_RGB(HSV_Color HSV, RGB_Color *RGB);
void __brightnessAdjust(float percent, RGB_Color RGB);

#endif
