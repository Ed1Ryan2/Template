#ifndef __BSP_H__
#define __BSP_H__

#include "ti_msp_dl_config.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"

#include "led.h"
#include "key.h"
#include "tim.h"
#include "uart.h"
#include "adc.h"

#include "wit_c_sdk.h"
#include "REG.h"
#include "IMU.h"
#include "Encoder.h"

void delay_ms(unsigned int ms);

#endif
