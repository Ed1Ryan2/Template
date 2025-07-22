#ifndef __UART_H__
#define __UART_H__

#include "bsp.h"

extern unsigned char rxpoint;
extern unsigned char Rx[100];
extern unsigned char RxData;

void UART_Init(void);

int fputc(int _c, FILE *_fp);
int fputs(const char *restrict s, FILE *restrict stream);
int puts(const char *_ptr);

void uart_proc(void);

#endif