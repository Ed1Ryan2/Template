#include "key.h"


//key函数轮询执行--->按键按下(低电平) k1 = 0 --->按键抬起(高电平) k1 = 1
//k1_last 为按键上一状态
// (k1_last & !k1)==1 即为按键下降沿
// (!k1_last & k1)==1 即为按键上升沿

//按键边沿检测实现
unsigned char k1 = 0;//按键当前状态
unsigned char k1_last = 0;//按键上一状态


//按键S2 PB21
void key_proc()
{
	if(DL_GPIO_readPins(KEY_PORT,KEY_S2_PIN)>0)k1=1;
	else k1 = 0;
	
	if(k1_last & !k1)//检测到下降沿
	{
		
		
	}
	
	k1_last = k1;
}