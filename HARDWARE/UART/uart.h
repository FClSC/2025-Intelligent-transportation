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

extern volatile float global_angle;
extern volatile uint8_t new_data_received;
extern volatile float angular_velocity_y;
extern volatile float angular_velocity_z;
extern uint8_t received_data_packet[11];



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


void UART2_Init(void);
void USART2_SendBits(uint8_t data);
void USART2_SendString(uint8_t *String1);
void UART2_SendArray(uint8_t *array,uint8_t length);
int fputc(int ch, FILE *f);
void USART2_IRQHandler(void);
uint8_t Serial2_GetRxFlag(void);
void u2_printf(char* fmt,...) ;

void UART4_Init(void);
void Uart4_SendByte(uint8_t byte);
void Uart4_SendArray(uint8_t *Array,uint16_t Length);
void Uart4_SendString(char* String);
uint32_t Uart4_Pow(uint32_t X,uint32_t Y);
void Uart4_SendNumber(uint32_t Number,uint8_t Length);
void Uart4_Printf(char* format,...);
void UART4_IRQHandler(void);
void ParseData(uint8_t *data, uint16_t length);
uint8_t CalculateChecksum(uint8_t *data, uint16_t length, uint8_t type) ;
void ResetAng_Z(void);
int16_t determicro(int target,float real);

void UART5_Init(void);
void USART5_SendBits(uint8_t data);
void UART5_SendArray(uint8_t *array,uint8_t length);
void UART5_SendString(uint8_t *String1);
uint8_t Serial5_GetRxFlag(void);
void  UART5_IRQHandler(void);
void UART5_Start_Scan(void);
void UART5_ParseCode(const char *Buf, int16_t *code1, int16_t *code2);

#endif
