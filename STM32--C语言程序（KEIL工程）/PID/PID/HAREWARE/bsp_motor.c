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

#include "bsp_motor.h"  


/**************************************************************************
Function: Drive_Motor
Input   : motor_a,motor_b:Indicates the left/right motor PWM duty cycle
Output  : none
�������ܣ��������
��ڲ���: motor_a��motor_b��ֵָʾ���ҵ��PWMռ�ձȣ�ֵԽ���ٶ�Խ��
����  ֵ����
**************************************************************************/	 	
void Set_Pwm(int motor_a,int motor_b)
{
	
	if(Car_Num==Akm_Car)//����������Ҫ���ƶ��
		SERVO_TIM_SetCompareX_FUN(&htim1,TIM_CHANNEL_1,Servo_PWM);
	if(motor_a<0)		PWMA_IN1=7200,PWMA_IN2=7200+motor_a;
	else 	            PWMA_IN2=7200,PWMA_IN1=7200-motor_a;

	if(motor_b<0)		PWMB_IN1=7200,PWMB_IN2=7200+motor_b;
	else 	            PWMB_IN2=7200,PWMB_IN1=7200-motor_b;
}


