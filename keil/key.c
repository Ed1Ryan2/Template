#include "key.h"


//key������ѯִ��--->��������(�͵�ƽ) k1 = 0 --->����̧��(�ߵ�ƽ) k1 = 1
//k1_last Ϊ������һ״̬
// (k1_last & !k1)==1 ��Ϊ�����½���
// (!k1_last & k1)==1 ��Ϊ����������

//�������ؼ��ʵ��
unsigned char k1 = 0;//������ǰ״̬
unsigned char k1_last = 0;//������һ״̬


//����S2 PB21
void key_proc()
{
	if(DL_GPIO_readPins(KEY_PORT,KEY_S2_PIN)>0)k1=1;
	else k1 = 0;
	
	if(k1_last & !k1)//��⵽�½���
	{
		
		
	}
	
	k1_last = k1;
}