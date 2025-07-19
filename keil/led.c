#include "led.h"

unsigned char led = 0;//LED状态变量

//LED灯D1：PB14
void Led_Disp(unsigned char i)
{
	if(i)DL_GPIO_setPins(LED_PORT,LED_D1_PIN);
	else DL_GPIO_clearPins(LED_PORT,LED_D1_PIN);
}



//测试函数
void Toggle_Task_1ms()//LED翻转任务，1ms一次
{
	static unsigned int ledTick;
	ledTick++;
	
	if(ledTick>=100)
	{
		ledTick=0;
		DL_GPIO_togglePins(LED_PORT,LED_D1_PIN);
	}
}
