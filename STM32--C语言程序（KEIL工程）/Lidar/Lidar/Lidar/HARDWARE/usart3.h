/***********************************************
��˾����ݸ��΢�����ܿƼ����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��
�޸�ʱ�䣺2021-04-29

Company: WeiHong Co.Ltd
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:
Update��2021-04-29

All rights reserved
***********************************************/
#ifndef __USRAT3_H
#define __USRAT3_H 
#include "sys.h"	  	


#define ANGLE_PER_FRAME 12
#define HEADER 0x54
#define POINT_PER_PACK 12
#define LENGTH  0x2C 	//����λ��һ֡���ݽ��յ��ĵ�����Ŀǰ�̶���12������λԤ��

typedef struct __attribute__((packed)) Point_Data
{
	u16 distance;//����
	u8 confidence;//���Ŷ�
	
}LidarPointStructDef;

typedef struct __attribute__((packed)) Pack_Data
{
	uint8_t header;
	uint8_t ver_len;
	uint16_t speed;
	uint16_t start_angle;
	LidarPointStructDef point[POINT_PER_PACK];
	uint16_t end_angle;
	uint16_t timestamp;
	uint8_t crc8;
}LiDARFrameTypeDef;

typedef struct __attribute__((packed)) PointDataProcess_
{
	uint16_t distance;//����
	float angle;//�Ƕ�
}PointDataProcessDef;//��������������

void uart3_init(u32 bound);
void USART3_IRQHandler(void);
void data_process(void);

#endif

