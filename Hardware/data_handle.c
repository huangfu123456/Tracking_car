#include "stm32f10x.h"                  // Device header
#include "config.h"



void  AD_Value_Filter(void)//数据滤波
{
	float result;
	
	for(uint8_t i = 0;i<5;i++)
	{
		result = 0.80 * ADC.orignalData[i] + (1 - 0.80) * ADC.orignalData[i];
		ADC.filterData[i] = result;
		
	}
	ADC.L = ADC.filterData[4];
	ADC.LM = ADC.filterData[3];
	ADC.M = ADC.filterData[2];
	ADC.RM = ADC.filterData[1];
	ADC.R = ADC.filterData[0];

}


float ADCValue_PoorCmpAnd(void)				//差比和差加权 
{
	float Err;
			
									
	
//		Err = (
//						(	(Poor.A*1.0/100) * (ADC.L - ADC.R) +
//							(Poor.B*1.0/100) * (ADC.LM - ADC.RM)) /
//						(
//							(	(Poor.A*1.0/100) * (ADC.L + ADC.R)) +
//							(	(Poor.C*1.0/100) * (fabs((ADC.LM - ADC.RM))))
//						)
//					) * (Poor.P*1.0/100);

	
	Err =  (Poor.P)*(ADC.LM-ADC.RM);
	
	return Err;
}













