#include "adc.h"

unsigned int result1,result2;
float voltage1,voltage2;
bool checkADC = false; 
void ADC_Init()
{
	NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
	DL_ADC12_startConversion(ADC12_0_INST);
}

void ADC12_0_INST_IRQHandler(void)
{
	switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST))
	{
		case DL_ADC12_IIDX_MEM1_RESULT_LOADED: //∂‘”¶MEM±‡∫≈
			checkADC = true;
		break;
			default:
		break;
	}
}

void adc_proc()
{
	if(checkADC)
	{
		result1 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_0);
		result2 = DL_ADC12_getMemResult(ADC12_0_INST, DL_ADC12_MEM_IDX_1);
		voltage1 = result1*3.3/4095;
		voltage2 = result2*3.3/4095;
		printf("res1 = %3.2lfV res2 = %3.2lfV\r\n", voltage1,voltage2);
		checkADC = false;
	}
}