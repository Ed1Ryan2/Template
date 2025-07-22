#include "IMU.h"

float fAcc[3], fGyro[3], fAngle[3];
int i;
float fAngle_tmp = 0;

void IMU_Init()
{
	WitInit(WIT_PROTOCOL_NORMAL, 0x50);
    WitSerialWriteRegister(SensorUartSend);
    WitRegisterCallBack(SensorDataUpdata);
    WitDelayMsRegister(Delayms);
}

void imu_proc()
{
	CmdProcess();
	if(s_cDataUpdate)
    {
        for(i = 0; i < 3; i++)
        {
            fAcc[i] = sReg[AX+i] / 32768.0f * 16.0f;
            fGyro[i] = sReg[GX+i] / 32768.0f * 2000.0f;
        }
        if(sReg[TEMP] - sReg[Roll] > 10 | sReg[Roll] - sReg[TEMP] > 10)
        {
            fAngle[0] = sReg[Roll] / 32768.0f * 180.0f;
            fAngle_tmp = fAngle[0];
        }
        else   fAngle[0] = fAngle_tmp;

        for(i = 1; i<3;i++)
        {
            fAngle[i] = sReg[Roll+i] / 32768.0f * 180.0f;
        }
//        if(s_cDataUpdate & ACC_UPDATE)
//        {
//            printf("acc:%.3f %.3f %.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);
//            s_cDataUpdate &= ~ACC_UPDATE;
//        }
//        if(s_cDataUpdate & GYRO_UPDATE)
//        {
//            printf("gyro:%.3f %.3f %.3f\r\n", fGyro[0], fGyro[1], fGyro[2]);
//            s_cDataUpdate &= ~GYRO_UPDATE;
//        }
//        if(s_cDataUpdate & ANGLE_UPDATE)
//        {
//            printf("angle:%.3f %.3f %.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);
//            s_cDataUpdate &= ~ANGLE_UPDATE;
//        }
//        if(s_cDataUpdate & MAG_UPDATE)
//        {
//            printf("mag:%d %d %d\r\n", sReg[HX], sReg[HY], sReg[HZ]);
//            s_cDataUpdate &= ~MAG_UPDATE;
//        }
		
		if(s_cDataUpdate & ANGLE_UPDATE)
        {
            printf("Angle:	X:%.3f Y:%.3f Z:%.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);
            s_cDataUpdate &= ~ANGLE_UPDATE;
        }
		if(s_cDataUpdate & ACC_UPDATE)
        {
            printf("ACC:	X:%.3f Y:%.3f Z:%.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);
            s_cDataUpdate &= ~ACC_UPDATE;
        }
    }
}

void show_data()
{
	printf("Angle:	X:%.3f Y:%.3f Z:%.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);
	s_cDataUpdate &= ~ANGLE_UPDATE;
	printf("ACC:	X:%.3f Y:%.3f Z:%.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);
	s_cDataUpdate &= ~ACC_UPDATE;
}


static void SensorUartSend(uint8_t* p_data, uint32_t uiSize)
{
    uint32_t i;
    for(i = 0; i < uiSize; i++) {
        // 发送单个字节
        DL_UART_transmitData(UART_1_INST, p_data[i]);
    }
}

static void Delayms(uint16_t ucMs)
{
	delay_ms(ucMs);
}

static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
	int i;
    for(i = 0; i < uiRegNum; i++)
    {
        switch(uiReg)
        {
//            case AX:
//            case AY:
            case AZ:
				s_cDataUpdate |= ACC_UPDATE;
            break;
//            case GX:
//            case GY:
            case GZ:
				s_cDataUpdate |= GYRO_UPDATE;
            break;
//            case HX:
//            case HY:
            case HZ:
				s_cDataUpdate |= MAG_UPDATE;
            break;
//            case Roll:
//            case Pitch:
            case Yaw:
				s_cDataUpdate |= ANGLE_UPDATE;
            break;
            default:
				s_cDataUpdate |= READ_UPDATE;
			break;
        }
		uiReg++;
    }
}

static void CmdProcess(void)
{
	switch(s_cCmd)
	{
		case 'a':	
			if(WitStartAccCali() != WIT_HAL_OK) 
				printf("\r\nSet AccCali Error\r\n");
			break;
		case 'm':	
			if(WitStartMagCali() != WIT_HAL_OK) 
				printf("\r\nSet MagCali Error\r\n");
			break;
		case 'e':	
			if(WitStopMagCali() != WIT_HAL_OK)
				printf("\r\nSet MagCali Error\r\n");
			break;
		case 'u':	
			if(WitSetBandwidth(BANDWIDTH_5HZ) != WIT_HAL_OK) 
				printf("\r\nSet Bandwidth Error\r\n");
			break;
		case 'U':	
			if(WitSetBandwidth(BANDWIDTH_256HZ) != WIT_HAL_OK) 
				printf("\r\nSet Bandwidth Error\r\n");
			break;
		case 'R':	
			if(WitSetOutputRate(RRATE_10HZ) != WIT_HAL_OK) 
				printf("\r\nSet Rate Error\r\n");
			break;
		case 'r':	
			if(WitSetOutputRate(RRATE_1HZ) != WIT_HAL_OK) 
				printf("\r\nSet Rate Error\r\n");
			break;
		case 'C':	
			if(WitSetContent(RSW_ACC|RSW_GYRO|RSW_ANGLE|RSW_MAG) != WIT_HAL_OK) 
				printf("\r\nSet RSW Error\r\n");
			break;
		case 'c':	
			if(WitSetContent(RSW_ACC) != WIT_HAL_OK) 
				printf("\r\nSet RSW Error\r\n");
			break;
	}
	s_cCmd = 0xff;
}
