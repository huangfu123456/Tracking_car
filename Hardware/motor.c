#include "stm32f10x.h"                  // Device header
#include "motor.h"
#include "config.h"
void tb6612_AIN1_Set(uint8_t bitvalue)
{

	GPIO_WriteBit(GPIOB, tb6612_AIN1, (BitAction) bitvalue);
}

void tb6612_AIN2_Set(uint8_t bitvalue)
{

	GPIO_WriteBit(GPIOB, tb6612_AIN2, (BitAction) bitvalue);
}

void tb6612_BIN1_Set(uint8_t bitvalue)
{

	GPIO_WriteBit(GPIOB, tb6612_BIN1, (BitAction) bitvalue);
}

void tb6612_BIN2_Set(uint8_t bitvalue)
{

	GPIO_WriteBit(GPIOB, tb6612_BIN2, (BitAction) bitvalue);
}

/*绝对值函数*/
int GFP_abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}



void Motor_Init(void)
{
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_Initstructure.GPIO_Pin = tb6612_AIN1 | tb6612_AIN2 | tb6612_BIN1 |tb6612_BIN2;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOB, &GPIO_Initstructure);
	tb6612_AIN1_Set(1);
	tb6612_AIN2_Set(0);
	tb6612_BIN1_Set(1);
	tb6612_BIN2_Set(0);
	
	TIM_SetCompare1(TIM1,PWM.basepwmvalue);	//控制左轮
	TIM_SetCompare4(TIM1,PWM.basepwmvalue);	//控制右轮
	
	
}

float  Motor_Limit(float value)								/* 限幅 */
{
	float temp = value;
	
	if(temp < MOTOR_MIN)
		temp = MOTOR_MIN;
	else if (temp > MOTOR_MAX)
		temp = MOTOR_MAX;
	
	return temp ;

}

void Motor_PwmSet(int pwmTemp)
{	
	int8_t K = 0;

	
	Motor[0].pwmrate = PWM.basepwmvalue -  (PWM.P * pwmTemp) ;
	Motor[1].pwmrate = PWM.basepwmvalue +  (PWM.P * pwmTemp);
		
	Motor[0].pwmrate = Motor_Limit(Motor[0].pwmrate);
	Motor[1].pwmrate = Motor_Limit(Motor[1].pwmrate);
	
	
	
	/* 环岛判断 */
	if (Flag.A == 1)
	{
		
		
		Motor[0].pwmrate = Motor_Limit(Motor[0].pwmrate);
		Motor[1].pwmrate = Motor_Limit(Motor[1].pwmrate);
		Flag.A = 0;
		
	}
	/* 十字判断 */
	if (Flag.B == 1)
	{
		Motor[0].pwmrate  = 3000;
		Motor[1].pwmrate  = 3000;
		Motor[0].pwmrate = Motor_Limit(Motor[0].pwmrate);
		Motor[1].pwmrate = Motor_Limit(Motor[1].pwmrate);
//		Flag.B = 0;
	}
	
	/* Y形判断 */
	if (Flag.C == 1)
	{

		Motor[0].pwmrate = Motor_Limit(Motor[0].pwmrate);
		Motor[1].pwmrate = Motor_Limit(Motor[1].pwmrate);
		Flag.C = 0;
	}
	
	
	
	
	//最终输出
	TIM_SetCompare1(TIM1,(uint16_t)Motor[0].pwmrate);	//控制右轮
	TIM_SetCompare4(TIM1,(uint16_t)Motor[1].pwmrate);	//控制左轮
	
	

}





