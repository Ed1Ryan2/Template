#include "tim.h"

void TIM_Init()
{
	//使能定时器中断
	NVIC_EnableIRQ(TIMER_1ms_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_1s_INST_INT_IRQN);
	
	//使能PWM
	DL_TimerA_startCounter(PWM_0_INST);
	
}


//PWM操作函数
//操作一个PWM的四个通道的频率
void setFrq(unsigned int frq)
{
	static unsigned int arr;
	static unsigned int ccr;
	
	arr = (unsigned int)(PWM_0_INST_CLK_FREQ/frq);
	ccr = (unsigned int)(arr/2);
	
	DL_TimerA_setLoadValue(PWM_0_INST,arr);
	DL_TimerG_setCaptureCompareValue(PWM_0_INST,ccr,GPIO_PWM_0_C0_IDX);
	
}
