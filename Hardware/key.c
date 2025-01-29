#include "stm32f10x.h"                  // Device heade
#include "delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=  GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin= GPIO_Pin_11 | GPIO_Pin_1;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
		
}




uint8_t Key_GetNum(void ){
	uint8_t Keynum = 0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0){
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
		delay_ms(20);
		Keynum = 1;
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0){
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
		delay_ms(20);
		Keynum= 2;
	}
	return Keynum ;
}















