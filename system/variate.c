#include "stm32f10x.h"                  // Device header
#include "variate.h"

struct ADC_Data ADC;
struct PoorCmpAnd Poor;
struct PID_V PID;
struct Flag_Q Flag;
struct JudgeValue Judge;
struct Switch_A  Switch;
struct PWM_Set  PWM;
struct MotorDriver Motor[2];




void Variate_Init(void)
{ 
	
	/*ȫ�ֱ�־λ*/
	Flag.A = 0;				//����
	Flag.B = 0;             //ʮ��
	Flag.C = 0;             //Y��
	Flag.D = 0;             //����sign
	Flag.G = 1;             //�ɻɹ�	
	
    /*PID����*/                  
	PID.P = 50;
	PID.I = 50;
	PID.D = 180;
	PID.Integral_Max = 1000;
	PID.b = 100;
	PID.k = 50;
	PID.ErrLastSum = 0;
	PID.ErrLastValue[0] = 0.0;
	PID.ErrLastValue[1] = 0.0;
	PID.ErrLastValue[2] = 0.0;
	
	//���������ж�ֵ
	Judge.jm1 = 3800;		//����
	Judge.jm2 = 500 ;       //����
	Judge.jm3 = 2000;       //ʮ��
	Judge.jm4 = 500;        //ʮ��
	Judge.jm5 = 2000;        //ʮ��
	Judge.jm6 = 10;         //Y��
	Judge.jm7 = 100;        //Y��
	Judge.jm8 = 2000;       //����
	
	//��������
	Switch.F1 = 0;			//����
	Switch.F2 = 1;           //ʮ��
	Switch.F3 = 0;           //Y��
	Switch.F4 = 0;           //��־ֵ����
	Switch.F5 = 0;           //�˲�     
	
	//PWM����
	PWM.basepwmvalue = 2000;
	PWM.P = 1;
	PWM.pwmSwitch = 0; 	//PWM�������
	
	PWM.pwmTemp = 0;
	

	Motor[0].pwmrate = 0;
	Motor[1].pwmrate = 0;
	
	//��һ���㷨����
	Poor.A = 190;
	Poor.B = 675;
	Poor.C = 965;
	Poor.P = 0.75;
	
	sign = 16;
	
	
}








