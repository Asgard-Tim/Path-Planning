/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��V1.0
�޸�ʱ�䣺2023-03-02

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update��2023-03-02

All rights reserved
***********************************************/
  
#include "bsp_led.h"



/**************************************************************************
Function: LED_Flash
Input   : Indicates the count of frequencies
Output  : none
�������ܣ�LED��˸Ƶ��
��ڲ���: ָʾƵ�ʵļ��� 
����  ֵ����
**************************************************************************/	 	
//���жϺ�������
void LED_Flash(u16 count)
{
	static int count_time;
	if(0 == count)
	{
		LED1_OFF();
	}
	else if(++count_time >= count)
	{
		LED1_TOGGLE();
		count_time = 0;	
	}
}

/*********************************************END OF FILE**********************/
