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
	
	/*全局标志位*/
	Flag.A = 0;				//环岛
	Flag.B = 0;             //十字
	Flag.C = 0;             //Y形
	Flag.D = 0;             //捕获sign
	Flag.G = 1;             //干簧管	
	
    /*PID参数*/                  
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
	
	//赛道特征判断值
	Judge.jm1 = 3800;		//环岛
	Judge.jm2 = 500 ;       //环岛
	Judge.jm3 = 2000;       //十字
	Judge.jm4 = 500;        //十字
	Judge.jm5 = 2000;        //十字
	Judge.jm6 = 10;         //Y形
	Judge.jm7 = 100;        //Y形
	Judge.jm8 = 2000;       //捕获
	
	//函数开关
	Switch.F1 = 0;			//环岛
	Switch.F2 = 1;           //十字
	Switch.F3 = 0;           //Y形
	Switch.F4 = 0;           //标志值捕获
	Switch.F5 = 0;           //滤波     
	
	//PWM设置
	PWM.basepwmvalue = 2000;
	PWM.P = 1;
	PWM.pwmSwitch = 0; 	//PWM输出开关
	
	PWM.pwmTemp = 0;
	

	Motor[0].pwmrate = 0;
	Motor[1].pwmrate = 0;
	
	//归一化算法参数
	Poor.A = 190;
	Poor.B = 675;
	Poor.C = 965;
	Poor.P = 0.75;
	
	sign = 16;
	
	
}








