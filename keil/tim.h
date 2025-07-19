#ifndef __TIM_H__
#define __TIM_H__

#include "bsp.h"

void TIM_Init(void);


void TIMER_1ms_INST_IRQHandler(void);
void TIMER_1s_INST_IRQHandler(void);

void setFrq(unsigned int frq);

#endif
