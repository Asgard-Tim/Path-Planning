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
#ifndef __KEY_H
#define	__KEY_H



#include "Header.h"


#define KEY2_STATE  		 PCin(13)

//  ���Ŷ���
#define    KEY1_GPIO_PORT    GPIOA			   
#define    KEY1_GPIO_PIN	   GPIO_PIN_0

#define    KEY2_GPIO_PORT    GPIOC		   
#define    KEY2_GPIO_PIN     GPIO_PIN_13

 /** �������±��ú�
	*  ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
	*  ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	*/
#define KEY_ON	1
#define KEY_OFF	0


//�û���������ֵ״̬
#define No_Action 					0
#define Click 						1
#define Long_Press 					2
#define Double_Click				3


uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
uint8_t User_Key_Scan(void);
void Get_KeyVal(void);


#endif /* __KEY_H */

