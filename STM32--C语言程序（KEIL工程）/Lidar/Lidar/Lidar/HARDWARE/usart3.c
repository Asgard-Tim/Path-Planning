#include "usart3.h"
#include <string.h>
/**************************************************************************
Function: Usart3 initialization
Input   : bound:Baud rate
Output  : none
�������ܣ�����3��ʼ��
��ڲ�����bound:������
����  ֵ����
**************************************************************************/

extern LiDARFrameTypeDef Pack_Data;//�״���յ����ݴ������������֮��
extern PointDataProcessDef AvoidData[100];
extern u16 receive_cnt;

static const uint8_t CrcTable[256] =
{
 0x00, 0x4d, 0x9a, 0xd7, 0x79, 0x34, 0xe3,
 0xae, 0xf2, 0xbf, 0x68, 0x25, 0x8b, 0xc6, 0x11, 0x5c, 0xa9, 0xe4, 0x33,
 0x7e, 0xd0, 0x9d, 0x4a, 0x07, 0x5b, 0x16, 0xc1, 0x8c, 0x22, 0x6f, 0xb8,
 0xf5, 0x1f, 0x52, 0x85, 0xc8, 0x66, 0x2b, 0xfc, 0xb1, 0xed, 0xa0, 0x77,
 0x3a, 0x94, 0xd9, 0x0e, 0x43, 0xb6, 0xfb, 0x2c, 0x61, 0xcf, 0x82, 0x55,
 0x18, 0x44, 0x09, 0xde, 0x93, 0x3d, 0x70, 0xa7, 0xea, 0x3e, 0x73, 0xa4,
 0xe9, 0x47, 0x0a, 0xdd, 0x90, 0xcc, 0x81, 0x56, 0x1b, 0xb5, 0xf8, 0x2f,
 0x62, 0x97, 0xda, 0x0d, 0x40, 0xee, 0xa3, 0x74, 0x39, 0x65, 0x28, 0xff,
 0xb2, 0x1c, 0x51, 0x86, 0xcb, 0x21, 0x6c, 0xbb, 0xf6, 0x58, 0x15, 0xc2,
 0x8f, 0xd3, 0x9e, 0x49, 0x04, 0xaa, 0xe7, 0x30, 0x7d, 0x88, 0xc5, 0x12,
 0x5f, 0xf1, 0xbc, 0x6b, 0x26, 0x7a, 0x37, 0xe0, 0xad, 0x03, 0x4e, 0x99,
 0xd4, 0x7c, 0x31, 0xe6, 0xab, 0x05, 0x48, 0x9f, 0xd2, 0x8e, 0xc3, 0x14,
 0x59, 0xf7, 0xba, 0x6d, 0x20, 0xd5, 0x98, 0x4f, 0x02, 0xac, 0xe1, 0x36,
 0x7b, 0x27, 0x6a, 0xbd, 0xf0, 0x5e, 0x13, 0xc4, 0x89, 0x63, 0x2e, 0xf9,
 0xb4, 0x1a, 0x57, 0x80, 0xcd, 0x91, 0xdc, 0x0b, 0x46, 0xe8, 0xa5, 0x72,
 0x3f, 0xca, 0x87, 0x50, 0x1d, 0xb3, 0xfe, 0x29, 0x64, 0x38, 0x75, 0xa2,
 0xef, 0x41, 0x0c, 0xdb, 0x96, 0x42, 0x0f, 0xd8, 0x95, 0x3b, 0x76, 0xa1,
 0xec, 0xb0, 0xfd, 0x2a, 0x67, 0xc9, 0x84, 0x53, 0x1e, 0xeb, 0xa6, 0x71,
 0x3c, 0x92, 0xdf, 0x08, 0x45, 0x19, 0x54, 0x83, 0xce, 0x60, 0x2d, 0xfa,
 0xb7, 0x5d, 0x10, 0xc7, 0x8a, 0x24, 0x69, 0xbe, 0xf3, 0xaf, 0xe2, 0x35,
 0x78, 0xd6, 0x9b, 0x4c, 0x01, 0xf4, 0xb9, 0x6e, 0x23, 0x8d, 0xc0, 0x17,
 0x5a, 0x06, 0x4b, 0x9c, 0xd1, 0x7f, 0x32, 0xe5, 0xa8
};//����crcУ�������

void uart3_init(u32 bound)
{  	 
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��UGPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3ʱ��
	//USART3_TX  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//USART3_RX	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Usart3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure);     //��ʼ������3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 

}

/**************************************************************************
Function: Receive interrupt function
Input   : none
Output  : none
�������ܣ�����3�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART3_IRQHandler(void)//����ld14�״����ݣ�һ֡47���ֽ�
{	
	static u8 state = 0;//״̬λ	
	static u8 crc = 0;//У���
	static u8 cnt = 0;//����һ֡12����ļ���
	u8 temp_data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //���յ�����
	{	  
		temp_data=USART_ReceiveData(USART3); 
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		if (state > 5)
		{
			if(state < 42)
			{
				if(state%3 == 0)//һ֡�����е����Ϊ6,9.....39�����ݣ�����ֵ��8λ
				{
					Pack_Data.point[cnt].distance = (u16)temp_data;
					state++;
					crc = CrcTable[(crc^temp_data) & 0xff];
				}
				else if(state%3 == 1)//һ֡�����е����Ϊ7,10.....40�����ݣ�����ֵ��8λ
				{
					Pack_Data.point[cnt].distance = ((u16)temp_data<<8)+Pack_Data.point[cnt].distance;
					state++;
					crc = CrcTable[(crc^temp_data) & 0xff];
				}
				else//һ֡�����е����Ϊ8,11.....41�����ݣ����Ŷ�
				{
					Pack_Data.point[cnt].confidence = temp_data;
					cnt++;	
					state++;
					crc = CrcTable[(crc^temp_data) & 0xff];
				}
			}
			else 
			{
				switch(state)
				{
					case 42:
						Pack_Data.end_angle = (u16)temp_data;//�����Ƕȵ�8λ
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
						break;
					case 43:
						Pack_Data.end_angle = ((u16)temp_data<<8)+Pack_Data.end_angle;//�����Ƕȸ�8λ
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
						break;
					case 44:
						Pack_Data.timestamp = (u16)temp_data;//ʱ�����8λ
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
						break;
					case 45:
						Pack_Data.timestamp = ((u16)temp_data<<8)+Pack_Data.timestamp;//ʱ�����8λ
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
						break;
					case 46:
						Pack_Data.crc8 = temp_data;//�״ﴫ����У���
						if(Pack_Data.crc8 == crc)//У����ȷ
						{
							receive_cnt++;//������յ���ȷ���ݵĴ���
							data_process();//���յ�һ֡��У����ȷ���Խ������ݴ���

							//printf("666\n");
						}
						else
							memset(&Pack_Data,0,sizeof(Pack_Data));//����
						crc = 0;
						state = 0;
						cnt = 0;//��λ
					default: break;
				}
			}
		}
		else 
		{
			switch(state)
			{
				case 0:
					if(temp_data == HEADER)//ͷ�̶�
					{
						Pack_Data.header = temp_data;
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];//��ʼ����У��
					} else state = 0,crc = 0;
					break;
				case 1:
					if(temp_data == LENGTH)//�����ĵ�����Ŀǰ�̶�
					{
						Pack_Data.ver_len = temp_data;
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
					} else state = 0,crc = 0;
					break;
				case 2:
					Pack_Data.speed = (u16)temp_data;//�״��ת�ٵ�8λ����λ��ÿ��
					state++;
					crc = CrcTable[(crc^temp_data) & 0xff];
					break;
				case 3:
					Pack_Data.speed = ((u16)temp_data<<8)+Pack_Data.speed;//�״��ת�ٸ�8λ
					state++;
					crc = CrcTable[(crc^temp_data) & 0xff];
					break;
				case 4:
					Pack_Data.start_angle = (u16)temp_data;
					state++;
					crc = CrcTable[(crc^temp_data) & 0xff];
					break;
				case 5:
					Pack_Data.start_angle = ((u16)temp_data<<8)+Pack_Data.start_angle;
					state++;
					crc = CrcTable[(crc^temp_data) & 0xff];
					break;
				default: break;

			}
		}
	}		
} 


void data_process(void)
{
	/*for(int i=0;i<12;i=i+1){
		printf("%u ",Pack_Data.point[i].distance);
		
	}
	printf("\n");*/
	float average_angel;	
	static uint8_t data_cnt_avoid = 0;		//����ģʽ�����������
	uint8_t i = 0;
	float start_angle = Pack_Data.start_angle/100.0;//��ʼ�Ƕ�
	float end_angel = Pack_Data.end_angle/100.0;	//�����Ƕ�
	if(start_angle>=360)
		start_angle -= 360;
	if(end_angel>=360)
		end_angel -= 360;
				
	if((start_angle -= 180)<0)
		start_angle += 360;
	if((end_angel -= 180)<0)
		end_angel += 360;
	if(start_angle>end_angel) end_angel +=360;
	average_angel = (end_angel - start_angle)/11;
//	if((start_angle>250||end_angel<150))
//	{
//		for(i=0;i<12;i++)
//		{
//			AvoidData[data_cnt_avoid].angle = start_angle + i*average_angel;
//			if(AvoidData[data_cnt_avoid].angle>=360)
//				AvoidData[data_cnt_avoid].angle -= 360;
//			AvoidData[data_cnt_avoid].distance = Pack_Data.point[i].distance;
//			if(++data_cnt_avoid == 100)
//				data_cnt_avoid = 0;
//		}
//	}
	if(1)
	{
		for(i=0;i<12;i++)
		{
			AvoidData[data_cnt_avoid].angle = start_angle + i*average_angel;
			if(AvoidData[data_cnt_avoid].angle>=360)
				AvoidData[data_cnt_avoid].angle -= 360;
			AvoidData[data_cnt_avoid].distance = Pack_Data.point[i].distance;
			if(++data_cnt_avoid == 100)
				data_cnt_avoid = 0;
		}
	}

}




