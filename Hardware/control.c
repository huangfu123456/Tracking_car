#include "stm32f10x.h"                  // Device header
#include "config.h"




		
		
	
float CycleIn(float value)						//环岛判断
{
	float result = value;
	
	if (Switch.F1 == 1)
	{
		if((ADC.LM + ADC.RM) > 5000 && ADC.M > 3000)
		{
					Flag.A = 1;
		}
	}
	if((ADC.LM-ADC.RM)>200 )
	{
		Motor[0].pwmrate -= ADC.M/15;
		Motor[1].pwmrate += ADC.M/15;
	
	
	} else if((ADC.LM-ADC.RM)<-200)
	{
		Motor[0].pwmrate += ADC.M/15;
		Motor[1].pwmrate -= ADC.M/15;
	
	
	
	}
	
	
	
	
		return result;
}




			
		
	
float Cross(float value)						//十字判断
{	
	float result = value;
	
	if (Switch.F2 == 1)
	{
		
		if (ADC.filterData[2] <100 || ADC.filterData[2]>2300)
		{
			
					Flag.B =1;
				
		}
	}

	
		
	
	return result;
}




float Yshape(float value)						//Y字判断
{
	float result = value;
	
	if (Switch.F3 == 1)
	{
		if (ADC.M < 10)
		{
//			if (ADC.Ex < 120 && ADC.M < 120 && Judge.Tim3 == 100)
//			{				
//					Flag.C++;
//					Flag.K = 1;			
//			}
		}
	}
	
	if(Flag.C == 1)
	{
		result -= 120;
	}
	if(Flag.C == 3)
	{
		result += 170;
	}
	return result;
}


void Error_run(void)
{
	
	if(ADC.L <ADC_Data_Min    &&    ADC.LM <ADC_Data_Min    &&    ADC.M <ADC_Data_Min   
          &&   ADC.RM <ADC_Data_Min    &&    ADC.R <ADC_Data_Min)
	{
		
		
		tb6612_AIN1_Set(0);
		tb6612_AIN2_Set(0);
		
		tb6612_BIN1_Set(0);
		tb6612_BIN2_Set(0);
		
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare1(TIM1,0);
	
	
	
	}//else 
//	{
//		tb6612_AIN1_Set(1);
//		tb6612_AIN2_Set(0);
//		
//		tb6612_BIN1_Set(1);
//		tb6612_BIN2_Set(0);
//		
//	
//	
//	}


}

                    

double PID_Core(float error)
{
	PID.Err = error;
	float PWM;		
	static double pwm = 0;	
	PID.ErrLastValue[2] = PID.ErrLastValue[1];
	PID.ErrLastValue[1] = PID.ErrLastValue[0];
	PID.ErrLastValue[0] = error;
	
	
	if (
			((PID.ErrLastSum + error) < PID.Integral_Max) 
				&&((PID.ErrLastSum + error) > -PID.Integral_Max)	)			/* 积分限幅 */ 
	{
		
		PID.ErrLastSum += error;												/* err值累加 */
	}
	else if (PID.ErrLastSum > 0)		
	{
		
		PID.ErrLastSum = PID.Integral_Max;										/* 正向限幅 */
	}
	else if (PID.ErrLastSum < 0)		
	{
	
		PID.ErrLastSum = -PID.Integral_Max;										/* 反向限幅 */
	}
	
//	PID.P = (PID.k*1.0/100) * fabs(ADC.Error)+ (PID.b*1.0/100);
//	
	PWM = (PID.P*1.0/100) * (error) + (PID.I*1.0/100) * PID.ErrLastSum + 
						(PID.D*1.0/100) * ((PID.ErrLastValue[0] - PID.ErrLastValue[1]) -
					(	PID.ErrLastValue[1] - PID.ErrLastValue[2]));
	
	return PWM;
}

//double	PID_Core(float error)
//{
//	PID.Err = error;
//	static double pwm = 0;	
//	
//	PID.ErrLastValue[2] = PID.ErrLastValue[1];
//	PID.ErrLastValue[1] = PID.ErrLastValue[0];
//	PID.ErrLastValue[0] = error;
//	
//	
//	PID.P = (PID.k*1.0/100) * fabs(ADC.Error)+ (PID.b*1.0/100);
//	
//	pwm += PID.P * (PID.ErrLastValue[0]-PID.ErrLastValue[1]) + (PID.I*1.0/100) * PID.ErrLastValue[0] + 
//						(PID.D*1.0/100) * (PID.ErrLastValue[0] - 2 * PID.ErrLastValue[1] + PID.ErrLastValue[2]);
//	
//	return pwm;
//}




void PID_control(void)
{

	AD_Value_Filter();
//	Cross(0);
	ADC.Error = ADCValue_PoorCmpAnd();	
	PWM.pwmTemp  = PID_Core( ADC.Error);
	Motor_PwmSet( (int)PWM.pwmTemp);
	Error_run();


}

u8 Fore,Back,Left,Right;
uint8_t biaozhi  = 0;
extern uint8_t biaozhi;
void Blue_control_move(void)
{	
	
	if((Fore==0)&&(Back==0)&&(Left==0)&&(Right==0))
		{
				TIM_SetCompare1(TIM1,0);	//控制右轮
				TIM_SetCompare4(TIM1,0);	//控制左轮;//未接受到前进后退指令-->速度清零，稳在原地
		}
			if(Fore==1)
			{	
				
				tb6612_AIN1_Set(1);
				tb6612_AIN2_Set(0);
				tb6612_BIN1_Set(1);
				tb6612_BIN2_Set(0);	
				
				TIM_SetCompare1(TIM1,2000);	//控制右轮
				TIM_SetCompare4(TIM1,2000);	//控制左轮;
				
				
			}
			if(Back==1)
			{	
				
				tb6612_AIN1_Set(0);
				tb6612_AIN2_Set(1);
				tb6612_BIN1_Set(0);
				tb6612_BIN2_Set(1);		
				TIM_SetCompare1(TIM1,2000);	//控制右轮
				TIM_SetCompare4(TIM1,2000);	//控制左轮;
				
			}
		
			if(Left==1)
			{
				TIM_SetCompare1(TIM1,100);	//控制右轮
				TIM_SetCompare4(TIM1,1500);	//控制左轮
			}
			if(Right==1)
			{	
				TIM_SetCompare1(TIM1,1500);	//控制右轮
				TIM_SetCompare4(TIM1,100);	//控制左轮
			}
			

}

int sign;










void EXTI1_IRQHandler(void)
{	

	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{

		Flag.G = 0;
		
		tb6612_AIN1_Set(0);
		tb6612_AIN2_Set(0);
		
		tb6612_BIN1_Set(0);
		tb6612_BIN2_Set(0);
		
		TIM_SetCompare1(TIM1,0);
		TIM_SetCompare4(TIM1,0);
	
		
		
		
	}
	
	EXTI_ClearITPendingBit(EXTI_Line1);
	
	
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		
		
		Get_ADC_Value();
		if(sign == 16)
		{
			PID_control();	//寻迹模式
		}else if(sign == 17)
		{
			Blue_control_move();			//	蓝牙模式
			
		}
		
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}









