#ifndef __UART_H__
#define __UART_H__

#include "bsp.h"

void UART_Init(void);

int fputc(int _c, FILE *_fp);
int fputs(const char *restrict s, FILE *restrict stream);
int puts(const char *_ptr);

#endif