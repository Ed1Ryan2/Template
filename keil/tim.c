#include "tim.h"

void TIM_Init()
{
	//ʹ�ܶ�ʱ���ж�
	NVIC_EnableIRQ(TIMER_1ms_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_1s_INST_INT_IRQN);
	
	//ʹ��PWM
	DL_TimerA_startCounter(PWM_0_INST);
}


//��ʱ���ж�
void TIMER_1ms_INST_IRQHandler()
{
	key_proc();
}

void TIMER_1s_INST_IRQHandler()
{
//	DL_GPIO_togglePins(LED_PORT,LED_D1_PIN);
	
}

//PWM��������
//����һ��PWM���ĸ�ͨ����Ƶ��
void setFrq(unsigned int frq)
{
	static unsigned int arr;
	static unsigned int ccr;
	
	arr = (unsigned int)(PWM_0_INST_CLK_FREQ/frq);
	ccr = (unsigned int)(arr/2);
	
	DL_TimerA_setLoadValue(PWM_0_INST,arr);
	DL_TimerG_setCaptureCompareValue(PWM_0_INST,ccr,GPIO_PWM_0_C0_IDX);
	
}
