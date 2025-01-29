#ifndef __VARIATE_H
#define __VARIATE_H

#define MOTOR_MIN		0
#define MOTOR_MAX		5000
#define ADC_Data_Min   250




 struct ADC_Data{						//ADC����
	
	__IO	uint16_t		orignalData[5];
	__IO	float			filterData[5];
	__IO	float			L;
	__IO	float			R;
	__IO	float			M;
	__IO	float			LM;
	__IO	float			RM;
	__IO	float			Error;

	
} ;

 struct PoorCmpAnd{										//��һ���㷨����*100
	
	uint8_t	flag;			
	int A;
	int B;
	int C;
	float P;

	
} ;

 struct PID_V{											//PID����*100
	
	double 	P;
	int 	I;
	int 	D;
	float   Err;
	float	ErrLastValue[3];
	float	ErrLastSum;
	float	Integral_Max;								//�����޷�ֵ
	int 	k;
	int 	b;
	
} ;

 struct Flag_Q{											//ȫ�ֱ�־λ
	uint16_t 	A;			//����
	uint16_t 	B;			//����
	uint16_t	C;			//Y��
	uint16_t	D;			//����sign
	uint16_t	G;			//�ɻɹ�
	uint16_t	S;			//���������
	uint16_t	T;			//����
	uint16_t	K;			//Y������
	uint16_t	W;			//�������
} ;					
	
struct JudgeValue{										//���������ж�ֵ
	
	uint16_t	jm1;		//����
	uint16_t	jm2;		//����
	uint16_t	jm3;		//ʮ��
	uint16_t	jm4;		//ʮ��
	uint16_t	jm5;		//ʮ��
	uint16_t	jm6;		//Y��
	uint16_t	jm7;		//Y��
	uint16_t	jm8;		//����
};					

struct Switch_A{										//��������
	
	_Bool F1;				//����
	_Bool F2;				//ʮ��
	_Bool F3;				//Y��
	_Bool F4;				//��־ֵ����
	uint8_t F5;				//�˲�
	
	
	
};

	
struct PWM_Set{
	
	_Bool		pwmSwitch;	//PWM�������
	uint16_t	basepwmvalue;	//PWM�������ֵ
	float 		P;		//����ϵ��
	double		pwmTemp;//PWM��ʱֵ
	
	
	
};

struct MotorDriver{											//�������
	
	
	float				pwmrate;						//������
	
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
