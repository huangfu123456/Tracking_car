#include "stm32f10x.h"                  // Device header
#include "config.h"



void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AIN  ;
	GPIO_Initstructure.GPIO_Pin = ADC_IN0 | ADC_IN1 | ADC_IN2 | ADC_IN3 | ADC_IN4 ;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_Initstructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,5,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//单次转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 5;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描模式
	ADC_Init(ADC1,&ADC_InitStructure);
	
	DMA_InitTypeDef DMA_Initstructure;
	DMA_Initstructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Initstructure.DMA_MemoryBaseAddr = (uint32_t)ADC.orignalData;
	DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_Initstructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;//方向
	DMA_Initstructure.DMA_BufferSize = 5;
	DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;//硬件触发
	DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;//是自动重装
	DMA_Initstructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMA_Initstructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);//使能ADC——DMA
	ADC_Cmd(ADC1,ENABLE);//开启ADC
	
	
	
	ADC_ResetCalibration(ADC1);//校准ADC1
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	

}

void Get_ADC_Value(void)
{
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter( DMA1_Channel1, 5); 
	DMA_Cmd(DMA1_Channel1,ENABLE);

	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
		
		
	
}














