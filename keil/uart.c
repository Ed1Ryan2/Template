#include "uart.h"


unsigned char rxpoint;
unsigned char Rx[100];
unsigned char RxData;
bool uart_flag;


void UART_Init()
{
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
	
	NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
}

void UART_0_INST_IRQHandler(void)
{
	
	RxData = DL_UART_Main_receiveData(UART_0_INST);
	Rx[rxpoint++]=RxData;
	uart_flag=1;
}

void UART_1_INST_IRQHandler(void)
{
	RxData = DL_UART_Main_receiveData(UART_1_INST);
	WitSerialDataIn(RxData);
}

//printf重定向
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

void uart_proc()//不定长字符串处理函数
{
	if(uart_flag==0)return;
	else if(rxpoint>0)
	{
		unsigned char len = strlen(Rx);
		printf("%s len:%d\r\n",Rx,len);
		
		rxpoint = 0;
		uart_flag = 0;
		memset(Rx,0,sizeof(Rx));
	}
}

