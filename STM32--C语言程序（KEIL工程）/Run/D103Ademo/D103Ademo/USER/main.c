#include "stm32f10x.h"

#include "delay.h"
#include "gpio.h"
#include "moto.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "encoder.h"

 /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/



 

int main(void)
 {	
   int a;
   SystemInit(); //配置系统时钟为72M   
   delay_init();    //延时函数初始化
   uart_init(9600);		//串口初始化
	 
   PWM_Int(7199,0);      //初始化pwm输出 72000 000 /7199+1=10000 
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

