#ifndef __IMU_H__
#define __IMU_H__

#include "bsp.h"

#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80

void IMU_Init(void);
void imu_proc(void);

void show_data(void);


static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
static void Delayms(uint16_t ucMs);
static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);

static void CmdProcess(void);

#endif
