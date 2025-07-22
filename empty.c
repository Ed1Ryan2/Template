/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"

#include "bsp.h"

unsigned int uartTick;
unsigned int imuTick;
unsigned int delay_times = 0;

unsigned int second = 0;

int main(void)
{
    SYSCFG_DL_init();
	
	
	
	TIM_Init();
	
//	ADC_Init();
	
	IMU_Init();
	
	UART_Init();
	
	Encoder_Init();
	
    while (1)
	{
		key_proc();//执行按键处理
    }
}

//SysTick，1ms执行一次
void SysTick_Handler(void)
{
	
	if( delay_times != 0 )
    {
        delay_times--;
    }
}

//定时器中断
void TIMER_1ms_INST_IRQHandler()
{
	uartTick++;
	imuTick++;
	if(uartTick>100)
	{
		uart_proc();//执行串口处理
		uartTick=0;
	}
	
	if(imuTick>500)
	{
//		imu_proc();
		imuTick=0;
	}
	
}

void TIMER_1s_INST_IRQHandler()
{
	DL_WWDT_restart(WWDT0_INST);
	DL_GPIO_togglePins(LED_PORT,LED_D1_PIN);
	second++;
//	printf("%d second passed \r\n",second);
}

void delay_ms(unsigned int ms)
{
    delay_times = ms;
    while( delay_times != 0 );
}
