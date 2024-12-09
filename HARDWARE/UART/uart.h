#ifndef _UART_H
#define _UART_H

#include "sys.h"
#include <stdio.h>

extern uint8_t Serial_TXPacket[3];
extern uint8_t Serial_RXPacket[8];
extern uint8_t USART2_TX_BUF[100];
extern uint8_t Serial_Flag2;
extern char UART5_RX_BUF[100];
extern uint8_t Serial_Flag5;


/********************����1************************/
void UART1_Init(void);
void USART1_SendBits(uint8_t data);
void UART1_SendArray(uint8_t *array,uint8_t length);
void UART1_SendString(uint8_t *String1);
void UART3_SendNum(uint32_t Number,uint8_t Length);
uint32_t Serial_Pow(uint32_t x,uint32_t y);


void UART_SendPacket(uint8_t *Serial_TXPacket);
uint8_t Serial1_GetRxFlag(void);
void USART1_IRQHandler(void);
void UART_SendPacket2UP(uint8_t data);

/********************����2************************/
void UART2_Init(void);
void USART2_SendBits(uint8_t data);
void USART2_SendString(uint8_t *String1);
void UART2_SendArray(uint8_t *array,uint8_t length);
int fputc(int ch, FILE *f);
void USART2_IRQHandler(void);
uint8_t Serial2_GetRxFlag(void);

void u2_printf(char* fmt,...);



void UART5_Init(void);
void USART5_SendBits(uint8_t data);
void UART5_SendArray(uint8_t *array,uint8_t length);
void UART5_SendString(uint8_t *String1);
uint8_t Serial5_GetRxFlag(void);

void  UART5_IRQHandler(void);
void UART5_Start_Scan(void);
void UART5_PraseCode(const char *Buf, uint16_t *code1, uint16_t *code2) ;

#endif
