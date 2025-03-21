#include "uart.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdarg.h"    
#include "string.h" 
#include "delay.h"
#include "math.h"


uint8_t Serial_Flag;
uint8_t Serial_Flag2;
uint8_t Serial_Flag5=0;
char UART5_RX_BUF[100];
uint8_t Serial_TXPacket[3];
uint8_t Serial_RXPacket[8];
uint8_t USART2_TX_BUF[100];


volatile float global_angle;
volatile uint8_t new_data_received;
volatile float angular_velocity_y;
volatile float angular_velocity_z;
uint8_t received_data_packet[11];








// PA9    TX
// PA10   RX
/********************************
函数功能 : 串口1的初始化
输入参数 : 无
输出参数 ；无
*********************************/
void UART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART1, &USART_InitStructure); 
	
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
  USART_Cmd(USART1, ENABLE);
}
/********************************
函数功能 : 串口1 发送一个字节
输入参数 : 一个字节
输出参数 ；无
*********************************/
void USART1_SendBits(uint8_t data)
{
	USART1->DR = data;
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}
/********************************
函数功能 : 串口1 发送一个数组
输入参数 : 一个数组
输出参数 ；无
*********************************/
void UART1_SendArray(uint8_t *array,uint8_t length)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		USART1_SendBits(array[i]);
	}
}
/********************************
函数功能 : 串口1 发送一个字符串
输入参数 : 一个字符串
输出参数 ；无
*********************************/
void UART1_SendString(uint8_t *String1)
{
	uint8_t i;
	for(i=0;String1[i]!='\0';i++)
	{
		USART1_SendBits(String1[i]);		
	}
}
/********************************
函数功能 : 串口1 发送一个数字
输入参数 : 一个数字
输出参数 ；无
*********************************/
void UART1_SendNum(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		USART1_SendBits(Number/Serial_Pow(10,Length-i-1)%10 + '0');
	}
}
/********************************
函数功能 : x的y次方
输入参数 : x与y
输出参数 ；无
*********************************/
uint32_t Serial_Pow(uint32_t x,uint32_t y)
{
	uint32_t Result=1;
	while(y--)
	{
		Result *= x;
	}
	return Result;
}
/********************************
函数功能 : 发送一个数据包 针头0xff 针尾0xfe
输入参数 : 数据包
输出参数 ；无
*********************************/
void UART_SendPacket(uint8_t *Serial_TXPacket)
{
	USART1_SendBits(0xFF); //包头
	UART1_SendArray(Serial_TXPacket,6); //数据
	USART1_SendBits(0xFE); //包尾
}
/********************************
函数功能 : 发送一个数据包 针头0xff 针尾0xfe
输入参数 : 一个字节
输出参数 ；无
*********************************/
void UART_SendPacket2UP(uint8_t data)
{
	USART1_SendBits(0xFF); //包头
	USART1_SendBits(data);
	USART1_SendBits(0xFE); //包尾
}
/********************************
函数功能 : 串口1的中断处理函数
输入参数 : 无
输出参数 ；无
*********************************/
void USART1_IRQHandler(void)
{
	static uint8_t RX1State=0;
	static uint8_t pRx1Packet=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		uint8_t Rx1Data = USART_ReceiveData(USART1);
		if(RX1State == 0)
		{
			if(Rx1Data == 0xFF)
			{
					RX1State =1;
					pRx1Packet=0;
			}
		}
		else if(RX1State == 1)
		{
				Serial_RXPacket[pRx1Packet] = Rx1Data;
				pRx1Packet++;
				if(pRx1Packet>7)
				{
					RX1State=2;
				}
		}
		else if(RX1State == 2)
		{
			if(Rx1Data == 0xFE)
			{
					RX1State = 0;
					Serial_Flag = 1;
			}
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
/********************************
函数功能 : 串口1的获取接收数据完成的标志位
输入参数 : 无
输出参数 ；1 接收完成  0 接收未完成
*********************************/
uint8_t Serial1_GetRxFlag(void)
{
	if(Serial_Flag == 1)
	{
		Serial_Flag=0;
		return 1;
	}
	return 0;
}

/******************************************************************************
PD5  TX2
PD6  RX2
******************************************************************************/
/********************************
函数功能 : 串口2的初始化
映射
输入参数 : 无
输出参数 ；无
*********************************/
void UART2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART2, &USART_InitStructure); 
	
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
  USART_Cmd(USART2, ENABLE);
	
}
/********************************
函数功能 : 串口2 发送一个字节
输入参数 : 一个字节
输出参数 ；无
*********************************/
void USART2_SendBits(uint8_t data)
{
	USART2->DR = data;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
}

void UART2_SendArray(uint8_t *array,uint8_t length)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		USART2_SendBits(array[i]);
	}
}

void USART2_SendString(uint8_t *String1)
{
	uint8_t i;
	for(i=0;String1[i]!='\0';i++)
	{
		USART2_SendBits(String1[i]);		
	}
}

int fputc(int ch, FILE *f)
{
	USART2_SendBits(ch);
	
	return ch;
}
void USART2_IRQHandler(void)
{
//	static uint8_t RX2State=0;
//	static uint8_t pRx2Packet=0;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{
		uint8_t Rx2Data = USART_ReceiveData(USART2);
		// if(RX2State == 0)
		// {
		// 	if(Rx2Data == 0xFF)
		// 	{
		// 			RX2State =1;
		// 			pRx2Packet=0;
		// 	}
		// }
		// else if(RX2State == 1)
		// {
		// 		Serial_RXPacket[pRx2Packet] = Rx2Data;
		// 		pRx2Packet++;
		// 		if(pRx2Packet>7)
		// 		{
		// 			RX2State=2;
		// 		}
		// }
		// else if(RX2State == 2)
		// {
		// 	if(Rx2Data == 0xFE)
		// 	{
		// 			RX2State = 0;
		// 			Serial_Flag2 = 1;
		// 	}
		// }
		if(Rx2Data == 0x02) //一键启动按下按钮会给单片机发送多个0x02，只要收到一个，就会把标志位置1
		Serial_Flag2 = 1;
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

/********************************
函数功能 : 串口2的获取接收数据完成的标志位
输入参数 : 无
输出参数 ；1 接收完成  0 接收未完成
*********************************/
uint8_t Serial2_GetRxFlag(void)
{
	if(Serial_Flag2 == 1)
	{
		Serial_Flag2=0;
		return 1;
	}
	return 0;
}



	void u2_printf(char* fmt,...)  
	{  
	 u16 i,j;
	 va_list ap;
	 va_start(ap,fmt);
	 vsprintf((char*)USART2_TX_BUF,fmt,ap);
	 va_end(ap);
	 i=strlen((const char*)USART2_TX_BUF);//此次发送数据的长度
	 for(j=0;j<i;j++)//循环发送数据
	 { 
	  USART_SendData(USART2,(uint8_t)USART2_TX_BUF[j]);   //发送数据到串口2
	   while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);  //等待上次传输完成 
	 } 
	 USART_SendData(USART2,(uint8_t)0xff);  //这个函数改为你的单片机的串口发送单字节函数
	 while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); 
	 USART_SendData(USART2,(uint8_t)0xff);  //这个函数改为你的单片机的串口发送单字节函数
	 while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); 
	 USART_SendData(USART2,(uint8_t)0xff);  //这个函数改为你的单片机的串口发送单字节函数
	 while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); 
	}
	

//串口四：陀螺仪模块
// 0xFF, 0xAA, 0x76, 0x00, 0x00     Z轴角度归零
// 0xFF, 0xAA, 0x03, 0x08, 0x00}    设置输出速率50HZ
///////////////////////////////
void UART4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//优先级不要过高，占用树莓派
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(UART4, &USART_InitStructure); 
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(UART4, ENABLE);
	
// 	//发送配置命令
// 	Uart4_SendArray(unlock_register,sizeof(unlock_register));
// 	//Uart4_SendArray(reset_z_axis, sizeof(reset_z_axis));
//    Uart4_SendArray(set_output_200Hz, sizeof(set_output_200Hz));
//    Uart4_SendArray(set_baudrate_115200, sizeof(set_baudrate_115200));
//    Uart4_SendArray(save_settings, sizeof(save_settings));


}

void Uart4_SendByte(uint8_t byte)
{
	UART4->DR = byte;
	while(USART_GetFlagStatus(UART4,USART_FLAG_TXE) == RESET);
}

void Uart4_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		Uart4_SendByte(Array[i]);	
	}
    // Uart4_SendByte(0x0D);//发送换行符
	// Uart4_SendByte(0x0A);//发送换行符
	delay_ms(200);        //延时处理
	
}

void Uart4_SendString(char* String)
{
	uint8_t i;
	for(i=0;String[i]!='\0';i++)
	{
		Uart4_SendByte(String[i]);	
	}
}
uint32_t Uart4_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result=1;
	while(Y--)
	{
		Result*=X;
	}
	return Result;
}

void Uart4_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Uart4_SendByte(Number /Uart4_Pow(10,Length-i-1) % 10 + '0');
	}
	
}

// void Uart4_Printf(char* format,...)
// {
// 	char String[100];
// 	va_list arg;
// 	va_start(arg,format);
// 	vsprintf(String,format,arg);
// 	va_end(arg);
// 	Uart4_SendString(String);
	
// }


void UART4_IRQHandler(void)
{
	static uint8_t Rx_Buffer[11];
	static uint8_t Rx_Index=0;
	static uint8_t state = 0; //状态机： 0：寻找包头 1：接收数据
	
	if (USART_GetITStatus(UART4, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(UART4);
		
		if(state==0)//寻找包头
		{
			if(RxData==0x55)
			{
				Rx_Buffer[0]=RxData;
				Rx_Index=1;
                state=1;				
			}			
		}
		
		else if (state==1)//接受数据
		{
			Rx_Buffer[Rx_Index++]=RxData;
			if(Rx_Index==2&&Rx_Buffer[1]!=0x53&&Rx_Buffer[1]!=0x52)
				//如果第二个字节不是0x53或者0x52，寻找下一个0x55
			{
				if(Rx_Buffer[1]==0x55)Rx_Index=1;
				else 
				{
					state=0;
					Rx_Index=0;
					
				}			
			}
			
			else if(Rx_Index==11)//接收到了完整数据包
			{
        
               ParseData(Rx_Buffer,11);//解析数据
				Rx_Index=0;
				state=0;    //重新寻找包头
			}					
		}
		

    USART_ClearITPendingBit(UART4, USART_IT_RXNE);			
		
	
}

}
void ParseData(uint8_t *data, uint16_t length)
{
   if (length == 11) 
		{
       uint8_t checksum = CalculateChecksum(data, length - 1, data[1]);
       if (checksum != data[length - 1]) 
		{
           //Uart4_Printf("Checksum error\r\n");
           return;
       }

       if (data[0] == 0x55 && data[1] == 0x53)//角度的解析
		{
           // 数据部分从索引6开始，低字节在前，高字节在后
           uint8_t yaw_l = data[6];
           uint8_t yaw_h = data[7];
           int16_t yaw = (int16_t)((yaw_h << 8) | yaw_l);

           // 将解析后的整数值转换为角度
           float angle = ((float)yaw / 32768.0) * 180.0;   //只需要这个即可
           global_angle = angle;
           new_data_received = 1;
       }
        else if (data[0] == 0x55 && data[1] == 0x52) 
		{
           //解析角速度数据
           uint8_t wy_l = data[4];
           uint8_t wy_h = data[5];
           int16_t wy = (int16_t)((wy_h << 8) | wy_l);
           angular_velocity_y = ((float)wy / 32768.0) * 2000.0;

           uint8_t wz_l = data[6];
           uint8_t wz_h = data[7];
           int16_t wz = (int16_t)((wz_h << 8) | wz_l);
           angular_velocity_z = ((float)wz / 32768.0) * 2000.0;

           new_data_received = 1;
       }
				
   }
}


uint8_t CalculateChecksum(uint8_t *data, uint16_t length, uint8_t type) 
{
   uint8_t checksum = 0;
   for (uint16_t i = 0; i < length; i++) 
	{
       checksum += data[i];
   }
   return checksum;
}

void ResetAng_Z(void)
{
	Uart4_SendByte(0xFF);
	Uart4_SendByte(0xAA);
	Uart4_SendByte(0x76);
	Uart4_SendByte(0x00);
	Uart4_SendByte(0x00);
	delay_ms(200);
	
}

int16_t determicro(int target,float real)  //决定是否微调
{
	//如果旋转后的角度在85-95度之间或者-85到-95之间，返回1，进行微调
     if((fabs(target-real)<20)||(fabs(target-real))>0.1)
     {
		 return 1;
	 }
	 else
	 {
		 return 0;
	 }

}

















//获得UART5_RX_BUF的0-6位是所需要的  ：  123+321
//串口五    扫码模块   采用USART5 
//单片机   PC12 TX    PD2 RX   
void UART5_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);//启用UART5的APB1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	//PC12   TX 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//PD2   RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(UART5, &USART_InitStructure);
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);


	
	USART_Cmd(UART5, ENABLE);
}

/********************************
函数功能 : 串口5 发送一个字节
输入参数 : 一个字节
输出参数 ；无
*********************************/
void USART5_SendBits(uint8_t data)
{
	UART5->DR = data;
	while(USART_GetFlagStatus(UART5,USART_FLAG_TXE) == RESET);
}
/********************************
函数功能 : 串口5 发送一个数组
输入参数 : 一个数组
输出参数 ；无
*********************************/
void UART5_SendArray(uint8_t *array,uint8_t length)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		USART5_SendBits(array[i]);
	}
}
/********************************
函数功能 : 串口5 发送一个字符串
输入参数 : 一个字符串
输出参数 ；无
*********************************/
void UART5_SendString(uint8_t *String1)
{
	uint8_t i;
	for(i=0;String1[i]!='\0';i++)
	{
		USART5_SendBits(String1[i]);		
	}
}


//串口5获得标志位
uint8_t Serial5_GetRxFlag(void)
{
	if(Serial_Flag5 == 1)
	{
		Serial_Flag5=0;
		return 1;
	}
	return 0;
}

//  @123+321#$  @123+321#$

void UART5_IRQHandler(void)
{
	static uint8_t RxState = 0;
	static uint8_t pRxPacket = 0;	
    if (USART_GetITStatus(UART5, USART_IT_RXNE) == SET)
	{
        uint8_t RxData = USART_ReceiveData(UART5);
        if(RxState==0)
		{
			if(RxData=='@'&&Serial_Flag5==0)
			{
				RxState=1;
				pRxPacket=0;		
			}			
		}
		else if (RxState==1)
		{
			if(RxData=='#')
			{
				RxState=2;
			}
			else
			{
				UART5_RX_BUF[pRxPacket]=RxData;
				pRxPacket++;
			}
		}
		else if(RxState==2)
		{
			if(RxData=='$')
			{
				RxState=0;
				UART5_RX_BUF[pRxPacket]='\0';
				Serial_Flag5=1;				
			}
			
			
		}
        USART_ClearITPendingBit(UART5, USART_IT_RXNE);
  }
}


void UART5_Start_Scan(void)//发送扫码指令,因该设置成一直扫码直到扫到停止
{

   uint8_t Order[9]={0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0xAB,0xCD};

   UART5_SendArray(Order,9);


}


void UART5_ParseCode(const char *Buf, int16_t *code1, int16_t *code2)
{
    // 直接解析第一个三位数
    *code1 = (Buf[0] - '0') * 100 + 
            (Buf[1] - '0') * 10 + 
            (Buf[2] - '0');

    // 跳过 '+' 号解析第二个三位数
    *code2 = (Buf[4] - '0') * 100 + 
            (Buf[5] - '0') * 10 + 
            (Buf[6] - '0');
	
}
//把解析后的数据发给树莓派，有可能会带一个换行符号







