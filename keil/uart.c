#include "bsp.h"

unsigned char rxpoint;
unsigned char RxData[100];

void UART_Init()
{
	DL_DMA_setSrcAddr(DMA,DMA_CH0_CHAN_ID,(unsigned int)(&UART_0_INST->RXDATA));
	DL_DMA_setDestAddr(DMA,DMA_CH0_CHAN_ID,(unsigned int)&RxData);
	DL_DMA_setTransferSize(DMA,DMA_CH0_CHAN_ID,1);
	DL_DMA_enableChannel(DMA,DMA_CH0_CHAN_ID);
	
	
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
	
	
	
}

void UART_0_INST_IRQHandler(void)  
{
	switch(DL_UART_Main_getPendingInterrupt(UART_0_INST))
    {
		case DL_UART_MAIN_IIDX_DMA_DONE_RX:
			//串口接收数据
			RxData[rxpoint++] = DL_UART_Main_receiveData(UART_0_INST);

			while( DL_UART_isBusy(UART_0_INST) == true );

			printf("Hello\r\n");

			break;

		default:

			break;
    }
}



int fputc(int _c, FILE *_fp)
{
  DL_UART_Main_transmitDataBlocking(UART_0_INST, _c);
  return _c;
}

int fputs(const char *restrict s, FILE *restrict stream)
{
  uint16_t i, len;
  len = strlen(s);
  for (i = 0; i < len; i++) {
    DL_UART_Main_transmitDataBlocking(UART_0_INST, s[i]);
  }
  return len;
}

int puts(const char *_ptr)
{
  int cnt = fputs(_ptr, stdout);
  cnt += fputs("\n", stdout);
  return cnt;
}
