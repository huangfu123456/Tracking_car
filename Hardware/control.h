#ifndef __CONTROL_H
#define __CONTROL_H


float CycleIn(float value);	
float Cross(float value);	
float Yshape(float value);	
void Error_run(void);
double  PID_Core(float error);
void PID_control(void);













#endif 
