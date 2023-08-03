
#include "bsp_usart.h"

/**************************************************************************
Function: fputc
Input   : none
Output  : none
�������ܣ��ض���c�⺯��printf������
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
//�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
	if(!Flag_Show)			//��������������ʹ��printf���������1
	{
		/* �ȴ�������� */
		while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET);///<�ȴ��������		

		/* ����һ���ֽ����ݵ����� */
		HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
		
		return ch;
	}
	else					//ʹ��printf���������3
	{
		
		while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET);///<�ȴ��������

		HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
	
		return ch;
	}
	
}


///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
	 uint8_t ch = 0;
		while (__HAL_UART_GET_FLAG (&huart1,UART_FLAG_TC) == RESET);

		return (int)HAL_UART_Receive(&huart1,&ch, 1, 0xffff);;
}

