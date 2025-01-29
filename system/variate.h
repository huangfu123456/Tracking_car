#ifndef __VARIATE_H
#define __VARIATE_H

#define MOTOR_MIN		0
#define MOTOR_MAX		5000
#define ADC_Data_Min   250




 struct ADC_Data{						//ADC变量
	
	__IO	uint16_t		orignalData[5];
	__IO	float			filterData[5];
	__IO	float			L;
	__IO	float			R;
	__IO	float			M;
	__IO	float			LM;
	__IO	float			RM;
	__IO	float			Error;

	
} ;

 struct PoorCmpAnd{										//归一化算法参数*100
	
	uint8_t	flag;			
	int A;
	int B;
	int C;
	float P;

	
} ;

 struct PID_V{											//PID参数*100
	
	double 	P;
	int 	I;
	int 	D;
	float   Err;
	float	ErrLastValue[3];
	float	ErrLastSum;
	float	Integral_Max;								//积分限幅值
	int 	k;
	int 	b;
	
} ;

 struct Flag_Q{											//全局标志位
	uint16_t 	A;			//环岛
	uint16_t 	B;			//环形
	uint16_t	C;			//Y形
	uint16_t	D;			//捕获sign
	uint16_t	G;			//干簧管
	uint16_t	S;			//出库与入库
	uint16_t	T;			//出库
	uint16_t	K;			//Y形消抖
	uint16_t	W;			//入库消抖
} ;					
	
struct JudgeValue{										//赛道特征判断值
	
	uint16_t	jm1;		//环岛
	uint16_t	jm2;		//环岛
	uint16_t	jm3;		//十字
	uint16_t	jm4;		//十字
	uint16_t	jm5;		//十字
	uint16_t	jm6;		//Y形
	uint16_t	jm7;		//Y形
	uint16_t	jm8;		//捕获
};					

struct Switch_A{										//函数开关
	
	_Bool F1;				//环岛
	_Bool F2;				//十字
	_Bool F3;				//Y形
	_Bool F4;				//标志值捕获
	uint8_t F5;				//滤波
	
	
	
};

	
struct PWM_Set{
	
	_Bool		pwmSwitch;	//PWM输出开关
	uint16_t	basepwmvalue;	//PWM输出基础值
	float 		P;		//增幅系数
	double		pwmTemp;//PWM临时值
	
	
	
};

struct MotorDriver{											//电机控制
	
	
	float				pwmrate;						//电机输出
	
};











extern struct ADC_Data ADC;
extern struct PoorCmpAnd Poor;
extern struct PID_V PID;
extern struct Flag_Q Flag;
extern struct JudgeValue Judge;
extern struct Switch_A Switch;
extern struct MotorDriver  Moter;
extern struct PWM_Set  PWM;
extern struct MotorDriver Motor[2];
extern int RxData;
extern int Change_Data[9];
void Variate_Init(void);
extern u8 Fore,Back,Left,Right;
extern int sign;

#endif 
