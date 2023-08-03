/*************************************
使用串口3接收LD14雷达数据，使用串口1输出接收成功的次数
接线说明：
LD14雷达接口      单片机接口
-----------------------------------
   P5V----------------5V	
   GND----------------GND
   TX-----------------B11
   PWM----------------不接(不控速)
***************************************/

#include "sys.h"

u16 receive_cnt;//计算成功接收数据帧次数
LiDARFrameTypeDef Pack_Data;
PointDataProcessDef AvoidData[100];


int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组，即优先级分级个数
	                                                //NVIC_PriorityGroup_2，代表抢占优先级位数位2，可以分[0, 1, 2, 3]四级优先级
	                                                //                          响应优先级位数位2，可以分[0, 1, 2, 3]四级优先级
	delay_init();//延时初始化
	
	uart_init(115200);//串口1初始化，用于输出接收数据帧成功的次数
	
	uart3_init(115200);//雷达串口接收
	
	while(1)
	{
		//printf("成功接受%d\r\n",receive_cnt);
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

