#include "stm32f10x.h"

#include "delay.h"
#include "gpio.h"
#include "moto.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "encoder.h"

 /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/



 

int main(void)
 {	
   int a;
   SystemInit(); //����ϵͳʱ��Ϊ72M   
   delay_init();    //��ʱ������ʼ��
   uart_init(9600);		//���ڳ�ʼ��
	 
   PWM_Int(7199,0);      //��ʼ��pwm��� 72000 000 /7199+1=10000 
   delay_ms(5);	 
	 a=1;
  while(a==1)
{
	moto(0);               
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
	moto(0);               
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
	moto(2);               
		delay_ms(600);
	moto(0);               
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(100);
	moto(1);               
		delay_ms(600);
	moto(0);               
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
	moto(1);               
		delay_ms(600);
	moto(0);               
		delay_ms(500);
	moto(2);               
		delay_ms(600);
	moto(0);               
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
			moto(0);               
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
		delay_ms(500);
	moto(3);               
		delay_ms(600);
		delay_ms(5000000000000000000);
	}
	
 }

