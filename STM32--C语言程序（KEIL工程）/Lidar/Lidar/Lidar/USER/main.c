/*************************************
ʹ�ô���3����LD14�״����ݣ�ʹ�ô���1������ճɹ��Ĵ���
����˵����
LD14�״�ӿ�      ��Ƭ���ӿ�
-----------------------------------
   P5V----------------5V	
   GND----------------GND
   TX-----------------B11
   PWM----------------����(������)
***************************************/

#include "sys.h"

u16 receive_cnt;//����ɹ���������֡����
LiDARFrameTypeDef Pack_Data;
PointDataProcessDef AvoidData[100];


int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ����飬�����ȼ��ּ�����
	                                                //NVIC_PriorityGroup_2��������ռ���ȼ�λ��λ2�����Է�[0, 1, 2, 3]�ļ����ȼ�
	                                                //                          ��Ӧ���ȼ�λ��λ2�����Է�[0, 1, 2, 3]�ļ����ȼ�
	delay_init();//��ʱ��ʼ��
	
	uart_init(115200);//����1��ʼ�������������������֡�ɹ��Ĵ���
	
	uart3_init(115200);//�״ﴮ�ڽ���
	
	while(1)
	{
		//printf("�ɹ�����%d\r\n",receive_cnt);
		//delay_ms(5);
		//printf("%d\n",Pack_Data);
		int i = 0;
		for(i=0;i<100;i++)
		{
				printf("%.2f ",AvoidData[i].angle);
				printf("%d\r\n ",AvoidData[i].distance);
		}
		delay_ms(500);
	}
}

