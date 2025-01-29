#include "stm32f10x.h"                  // Device header
#include "config.h"


int main(void)
{	
	Variate_Init();
	OLED_Init();
	AD_Init();
	EXTI_MPU_Init();
	TIM2_Init();			//定时计算输出PWM
	Usart1_Init(9600);
	
	
	
	NVIC_Config();
	OLED_ShowString(1,1,"D0:");
	OLED_ShowString(2,1,"D1:");
	OLED_ShowString(3,1,"D2:");
	OLED_ShowString(2,9,"D3:");
	OLED_ShowString(1,9,"D4:");
	OLED_ShowString(4,1,"Er:");
	OLED_ShowString(4,11,"B:");
	
	TIM1_PWM_Init(7199,0);					//PWM频率10kHz
	Motor_Init();
	
	
	while(1)
	{	


		
		OLED_ShowNum(1,4,ADC.orignalData[0],4);
		OLED_ShowNum(2,4,ADC.orignalData[1],4);
		OLED_ShowNum(3,4,ADC.orignalData[2],4);
		OLED_ShowNum(2,13,ADC.orignalData[3],4);
		OLED_ShowNum(1,13,ADC.orignalData[4],4);
		OLED_ShowSignedNum(4,4,PID.Err,4);
		OLED_ShowNum(4,14,Flag.B,2);
	
		

	}
}







