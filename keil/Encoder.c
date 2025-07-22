#include "Encoder.h"

int ENCVal = 0;

void Encoder_Init()
{
	NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOA_INT_IRQN);
}

void GROUP1_IRQHandler(void)
{
	if (DL_GPIO_getPendingInterrupt(EncoderA_PORT) == EncoderA_PIN_A_IIDX)
	{
        if (DL_GPIO_readPins(EncoderB_PORT, EncoderB_PIN_B_PIN)>0 && DL_GPIO_readPins(EncoderA_PORT, EncoderA_PIN_A_PIN)>0)
		{
            ENCVal--;
        }
        else
		{
            ENCVal++;
        }
    }
	if (DL_GPIO_getPendingInterrupt(EncoderB_PORT) == EncoderB_PIN_B_IIDX)
	{
        if (DL_GPIO_readPins(EncoderB_PORT, EncoderB_PIN_B_PIN)>0 && DL_GPIO_readPins(EncoderA_PORT, EncoderA_PIN_A_PIN)>0)
		{
            ENCVal++;
        }
        else
		{
            ENCVal--;
        }
    }
}
