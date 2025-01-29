#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include <stdio.h>
#include <stdarg.h>
#include "config.h"

int RxData;

uint8_t RxFlag;

void Usart1_Init(u32 bound)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Pin= stm32_Usart2_TX ;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_IN_FLOATING;
	GPIO_Initstructure.GPIO_Pin= stm32_Usart2_RX;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;			//奇偶校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init( USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);	

	USART_Cmd(USART1,ENABLE);




}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus( USART1, USART_FLAG_TXE) == RESET);
}


void  Serial_SendArray(uint8_t*Array,uint16_t Length)
{
	for(uint16_t i = 0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
		
	}
	
}

void  Serial_SendString(char* string)
{
	for(uint8_t i = 0;string[i] != '\0';i++)
	{
		Serial_SendByte(string[i]);
	
	}
	
}

uint32_t Serial_pow(uint32_t X,uint32_t Y){

	uint32_t temp = 1;
	for(uint8_t i = 0;i<Y;i++)
	{
		temp *= X;
	
	}
	return temp;
	
}
	

void Serial_SendNumber(uint32_t Number,uint8_t Length)
{

	uint8_t wei = 0,i;
	for(i = 1;i<=Length;i++)
	{
	wei = Number/(10*(Length-i))%10 + '0';
	}
	Serial_SendByte(wei);
	
}


int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;

}

void Serial_Printf(char *format,...)
{

	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);

}

uint8_t Serial_GetRxFlag(void)
{

	if(RxFlag == 1)
	{
		RxFlag = 0;
		return 1;
	} else
	{
		return 0;
	}
}

uint8_t Serial_GetRxData(void)
{
	return RxData;
	
}
int b2f(uint8_t  m0, uint8_t m1, uint8_t m2, uint8_t m3)
{	
	int temp;
	
	temp = ((int)m0)<<24 | ((int)m1)<<16 |((int)m2)<<8 |(int)m3;
	return temp;
}

void change(void)
{	
	int temporary[8] = {0};
	uint8_t i,j = 0;
	for( i = 0;i<25;i+=4)
	{
		temporary[j++] = b2f(Change_Data[i+3],Change_Data[i+2],Change_Data[i+1],Change_Data[i]);
	
	}
	if(temporary[0] != 0)
		PID.k = temporary[0];
	if(temporary[1] != 0)
		PID.b = temporary[1]; 
	if(temporary[2] != 0)
		PID.I = temporary[2]; 
	if(temporary[3] != 0)
		PID.D = temporary[3]; 
	if(temporary[4] != 0)
		Poor.A = temporary[4]; 
	if(temporary[5] != 0)
		Poor.B = temporary[5]; 
	if(temporary[6] != 0)
		Poor.C = temporary[6]; 
	if(temporary[7] != 0)
		Poor.P = temporary[7]; 
	
	
	
}

int Change_Data[9];

void USART1_IRQHandler(void){
	static uint8_t RxState = 0,i = 0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		RxData = USART_ReceiveData(USART1);
		if(RxData == 16 || RxData == 17)
		{
			sign =  RxData;
		}


		if(sign == 17)
		{
			if(RxData==0x05)Fore=0,Back=0,Left=0,Right=0;//刹
			else if(RxData==0x02)Fore=1,Back=0,Left=0,Right=0;//前
			else if(RxData==0x08)Fore=0,Back=1,Left=0,Right=0;//后
			else if(RxData==0x06)Fore=0,Back=0,Left=0,Right=1;//右
			else if(RxData==0x04)Fore=0,Back=0,Left=1,Right=0;//左
			else	Fore=0,Back=0,Left=0,Right=0;//刹										
		} else if(sign == 16)
		{
			if(RxData == 0xA5)
			{
				RxState = 1;
				i = 0;
			}
			 else if(RxState == 1)
			{
				Change_Data[i++] = RxData;
				if(i == 31)
				{
					RxState = 2;
				}
			} else if(RxState == 2)
			{
				Change_Data[i] = RxData;
				RxState = 3;
			} else if(RxState == 3)
			{
				if(RxData == 0x5A)
				{
					RxState = 0;
					RxFlag = 1;
				}
			}	
			change();
		
		}

	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	
}








