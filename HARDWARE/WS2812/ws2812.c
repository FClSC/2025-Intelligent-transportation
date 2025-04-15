#include "ws2812.h"
/*
WS2812

PWM+DMA

PWM: TIM1_CH4  PA11

时钟周期72 MHz=7200 0000 HZ
分频系数 1
分频后频率 = 7200 0000/1=7200 0000 HZ
分频后一次计数的时间 1 / 7200 0000 s
计90个数是 1.25us
故 PSC=1 ARR=90

0码
高电平+低电平=0.125us
设置CCR=25
高电平时间0.347us
低电平时间0.903us



1码时间
高电平+低电平=0.125us
设置CCR=55
高电平时间0.76us
低电平时间0.49us


*/


uint16_t ws2812_buffer[WS2812_BUFFER_SIZE]; // DMA传输缓冲区

// 初始化函数（保持原样，正确配置TIM1和DMA）
void WS2812_Init(void) 
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = 89;        // 800kHz (72MHz/(89+1))
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable);

    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&TIM1->CCR4;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ws2812_buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = WS2812_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);

    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_DMACmd(TIM1, TIM_DMA_CC4, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    GPIO_ResetBits(GPIOA, GPIO_Pin_11);
    delay_us(100);
}

// 设置单个LED颜色（GRB格式）
void WS2812_SetColor(uint8_t led_num, uint32_t grb_color) 
{
    uint16_t *p = &ws2812_buffer[led_num * 24];
    for (int i = 0; i < 24; i++) {
        p[i] = (grb_color & (1 << (23 - i))) ? WS2812_1 : WS2812_0;
    }
}

// 启动DMA传输并生成复位信号
void WS2812_Update(void)
{
    TIM_Cmd(TIM1, DISABLE);
    DMA_Cmd(DMA1_Channel4, DISABLE);

    DMA_SetCurrDataCounter(DMA1_Channel4, WS2812_BUFFER_SIZE);
    DMA_Cmd(DMA1_Channel4, ENABLE);
    TIM_Cmd(TIM1, ENABLE);

    // 等待DMA传输完成
    while (!DMA_GetFlagStatus(DMA1_FLAG_TC4));
    DMA_ClearFlag(DMA1_FLAG_TC4);

    // 关键修复：彻底关闭 PWM 和 DMA，再拉低 GPIO
    TIM_Cmd(TIM1, DISABLE);
    DMA_Cmd(DMA1_Channel4, DISABLE);
    GPIO_ResetBits(GPIOA, GPIO_Pin_11); // 强制拉低数据线
    delay_us(100);  // 延长复位时间至 100μs（确保可靠）
}

//0xFFFFFF 全白
// 0xFF0000 红色
// 0x00FF00 绿色
// 0x0000FF 蓝色
// 0x7F7F7F 半白
// 示例：点亮所有LED为白色
void ws2812_ON(void) 
{
    for (int i = 0; i < WS2812_NUM_LEDS; i++) {
        WS2812_SetColor(i, 0x7F7F7F); // GRB格式（白色）
    }
    WS2812_Update();
    delay_ms(10);
}
// 关闭所有 LED（灭灯）
void ws2812_OFF(void) 
{
    for (int i = 0; i < WS2812_NUM_LEDS; i++) {
        WS2812_SetColor(i, 0x000000); // GRB 全 0，关闭 LED
    }
    WS2812_Update(); // 发送数据到灯带
    delay_ms(10);    // 可选，确保数据发送完成
}


// DMA传输完成中断服务函数（可选）
void DMA1_Channel4_IRQHandler(void) 
{
    if (DMA_GetITStatus(DMA1_IT_TC4)) {
        DMA_ClearITPendingBit(DMA1_IT_TC4);
        // 可在此添加复位信号处理
    }
}
