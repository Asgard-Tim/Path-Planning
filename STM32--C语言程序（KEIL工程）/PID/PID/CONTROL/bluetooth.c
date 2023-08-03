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

#include "bluetooth.h"
#include "Lidar.h"
SEND_DATA Send_Data;
RECEIVE_DATA Receive_Data;
int Time_count;
static const u8 CrcTable[256] =
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

u8 Usart1_Receive_buf[1];          //����1�����ж����ݴ�ŵĻ�����
u8 Usart3_Receive_buf[1];          //����3�����ж����ݴ�ŵĻ�����
u8 Uart5_Receive_buf[1];          //����5�����ж����ݴ�ŵĻ�����
u8 PID_Send;			//�����ֻ�app��ȡ��������ı���
u8 Flag_Direction;		//�����ֻ�app�ķ��������˳ʱ��һȦ��8��������ֵ��1--8,ֹͣʱ��ֵΪ0
/**************************************************************************
Function: BLUETOOTH_USART_IRQHandler
Input   : none
Output  : none
�������ܣ����������жϺ��������������ֻ�������
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
//���������жϣ�����3
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*huart) //���ջص�����
{
	if(huart == &huart1)
	{
			static u8 Count=0;
	  u8 Usart_Receive;

		Usart_Receive = Usart3_Receive_buf[0];//Read the data //��ȡ����
		ROS_ON_Flag = RC_ON;//ros����ʱ����С��ģʽ��ΪROSģʽ
		APP_ON_Flag = RC_OFF;		
		PS2_ON_Flag = RC_OFF;
//		if(Time_count<CONTROL_DELAY)
//			// Data is not processed until 10 seconds after startup
//		  //����10��ǰ����������
//		  return 0;	
		
		//Fill the array with serial data
		//����������������
        Receive_Data.buffer[Count]=Usart_Receive;
		
		// Ensure that the first data in the array is FRAME_HEADER
		//ȷ�������һ������ΪFRAME_HEADER
		if(Usart_Receive == FRAME_HEADER||Count>0) 
			Count++; 
		else			
			Count=0;
		
		if (Count == 11) //Verify the length of the packet //��֤���ݰ��ĳ���
		{   
				Count=0; //Prepare for the serial port data to be refill into the array //Ϊ����������������������׼��
				if(Receive_Data.buffer[10] == FRAME_TAIL) //Verify the frame tail of the packet //��֤���ݰ���֡β
				{
					//Data exclusionary or bit check calculation, mode 0 is sent data check
					//�������λУ����㣬ģʽ0�Ƿ�������У��
					if(Receive_Data.buffer[9] ==Check_Sum(9,0))	 
				  {	
						float Vz;						
						//All modes flag position 0, USART3 control mode
            //����ģʽ��־λ��0��ΪUsart3����ģʽ						
//						PS2_ON_Flag=0;
//						Remote_ON_Flag=0;
//						APP_ON_Flag=0;
//						CAN_ON_Flag=0;
//						Usart1_ON_Flag=0;
//						Usart5_ON_Flag=0;
						//Calculate the target speed of three axis from serial data, unit m/s
						//�Ӵ�������������Ŀ���ٶȣ� ��λm/s
						Move_X=XYZ_Target_Speed_transition(Receive_Data.buffer[3],Receive_Data.buffer[4]);
//						Move_Y=XYZ_Target_Speed_transition(Receive_Data.buffer[5],Receive_Data.buffer[6]);
						Vz    =XYZ_Target_Speed_transition(Receive_Data.buffer[7],Receive_Data.buffer[8]);
						if(Car_Num==Akm_Car)
						{
							Move_Z=Vz_to_Akm_Angle(Move_X, Vz);
						}
						else
						{
							Move_Z=XYZ_Target_Speed_transition(Receive_Data.buffer[7],Receive_Data.buffer[8]);
						}			
					}
			}
		}
       HAL_UART_Receive_IT(&huart1,Usart1_Receive_buf,sizeof(Usart1_Receive_buf));//����3�ص�����ִ�����֮����Ҫ�ٴο��������жϵȴ���һ�ν����жϵķ���			
	}
	if(huart == &huart3)
	{
		static int temp_count = 0;				//���ڼ�¼ǰ����ָ��Ĵ�������һ������������ʱ����Ҫ�õ�
	  static	int bluetooth_receive=0;		//����������ر���
	  static u8 Flag_PID,i,j,Receive[50];
	  static float Data;						//app������ղ����õ��ı���	  
		  bluetooth_receive=Usart3_Receive_buf[0]; 
		  if(APP_ON_Flag == RC_OFF)						//δ�����������ƣ�ֻ�������ݽ��м򵥵ķ���
	  	{
			  if(bluetooth_receive == 0x41)
			  {
				  if((++temp_count) == 5)					//��Ҫ��������5��ǰ����ָ�����ת��һ��ʱ��ɿ�ʼapp����
				  {
					  temp_count = 0;
					  APP_ON_Flag = RC_ON;		
					  PS2_ON_Flag = RC_OFF;
					  RC_Velocity = Default_Velocity;		//��ʱ�ٶȻָ�Ĭ���ٶ�
					  if(Car_Num == Akm_Car)				//����������ת��Ϊ�Ƕȣ���������ʱת��Ƕ�Ĭ�ϲ���
						  RC_Turn_Velocity = Bluetooth_Turn_Angle;
					  else								//�������������ֲ���
						  RC_Turn_Velocity = Default_Turn_Bias;
				  }
			  }
			  else 
				  temp_count = 0;
		  }
		  else 
		  {
			  if(bluetooth_receive>=0x41&&bluetooth_receive<=0x48) 	//Ĭ��ʹ�ã�8�������ֻ����͵���ֵ��0x41--0x48
				  Flag_Direction=bluetooth_receive-0x40;
			
			  else if(bluetooth_receive==0X5A)  						//ֹͣʱ����0x5a
				  Flag_Direction=0;

			  else if(bluetooth_receive<=10)  //����app
				  Flag_Direction=bluetooth_receive;	
			
			  else if(bluetooth_receive==0x59) 						//���ٰ���
			  {
				  if((RC_Velocity -= X_Step)<MINI_RC_Velocity)
					  RC_Velocity = MINI_RC_Velocity;
				  if(Car_Num != Akm_Car)								//�ǰ�������ת���ٶȿɸ���
				  {
				 	  if((RC_Turn_Velocity -= Z_Step)<MINI_RC_Turn_Velocity)
					  RC_Turn_Velocity = MINI_RC_Turn_Velocity;
				  }
			  }			 
			  else if(bluetooth_receive==0x58)						//����
			  {
				  if((RC_Velocity += X_Step)>MAX_RC_Velocity)
					  RC_Velocity = MAX_RC_Velocity;
				  if(Car_Num != Akm_Car)
				  {
					  if((RC_Turn_Velocity += Z_Step)>MAX_RC_Turn_Bias)
					  	RC_Turn_Velocity = MAX_RC_Turn_Bias;
				  }
			  }			
			  else if(bluetooth_receive==0x7B) Flag_PID=1;   			//APP����ָ����ʼλ
			  else if(bluetooth_receive==0x7D) Flag_PID=2;   			//APP����ָ��ֹͣλ

			  if(Flag_PID==1)  //�ɼ�����
			  {
				  Receive[i]=bluetooth_receive;
				  i++;
			  }
			  if(Flag_PID==2)  //��������
			  {
				  if(Receive[3]==0x50) 	 PID_Send=1;
				  else if(Receive[1]!=0x23) 
				  {								
					  for(j=i;j>=4;j--)
					  {
					  	Data+=(Receive[j-1]-48)*pow(10,i-j);
					  }
					  switch(Receive[1])//���ν���
					  {
						
						 case 0x30:  RC_Velocity=Data;break;
						 case 0x31:   CCD_Move_X=Data/1000;break;
						 case 0x32:   break;
						 case 0x33:   break; //Ԥ��
						  case 0x34:  break; //Ԥ�� 
						  case 0x35:  break; //Ԥ��
						  case 0x36:  break; //Ԥ��
						  case 0x37:  break; //Ԥ��
						  case 0x38:  break; //Ԥ��
						  default:break;
 
					  }
				  }				 
				  Flag_PID=0;
				  i=0;
				  j=0;
				  Data=0;
				  memset(Receive, 0, sizeof(u8)*50);//��������
			} 
		}
   HAL_UART_Receive_IT(&huart3,Usart3_Receive_buf,sizeof(Usart3_Receive_buf));//����3�ص�����ִ�����֮����Ҫ�ٴο��������жϵȴ���һ�ν����жϵķ���		
	}
	else if(huart == &huart5)
	{
		static u8 state = 0;//״̬λ	��ָʾ��ǰ����֡��λ��
	  static u8 crc = 0;	//У���
	  static u8 cnt = 0;	//����һ֡12����ļ���
	  u8 temp_data; 
		temp_data=Uart5_Receive_buf[0]; 
#ifdef LD14	
			if (state > 5)	
			{
				if(state < 42)
				{
					if(state%3 == 0)		//һ֡�����е����Ϊ6,9.....39�����ݣ�����ֵ��8λ
					{
						Pack_Data.point[cnt].distance = (u16)temp_data;
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
					}
					else if(state%3 == 1)	//һ֡�����е����Ϊ7,10.....40�����ݣ�����ֵ��8λ
					{
						Pack_Data.point[cnt].distance = ((u16)temp_data<<8)+Pack_Data.point[cnt].distance;
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
					}
					else					//һ֡�����е����Ϊ8,11.....41�����ݣ����Ŷ�
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
							Pack_Data.end_angle = (u16)temp_data;						//�����Ƕȵ�8λ
							state++;
							crc = CrcTable[(crc^temp_data) & 0xff];
							break;
						case 43:
							Pack_Data.end_angle = ((u16)temp_data<<8)+Pack_Data.end_angle;//�����Ƕȸ�8λ
							state++;
							crc = CrcTable[(crc^temp_data) & 0xff];
							break;
						case 44:
							Pack_Data.timestamp = (u16)temp_data;						//ʱ�����8λ
							state++;
							crc = CrcTable[(crc^temp_data) & 0xff];
							break;
						case 45:
							Pack_Data.timestamp = ((u16)temp_data<<8)+Pack_Data.timestamp;//ʱ�����8λ
							state++;
							crc = CrcTable[(crc^temp_data) & 0xff];
							break;
						case 46:
							Pack_Data.crc8 = temp_data;		//�״ﴫ����У���
							if(Pack_Data.crc8 == crc)		//У����ȷ
							{
								data_process();				//���յ�һ֡��У����ȷ���Խ������ݴ���
							}
							else
							{
								memset(&Pack_Data, 0, sizeof(LiDARFrameTypeDef));//����
							}
							crc = 0;
							state = 0;
							cnt = 0;//��λ
							break;
						default: break;
					}
				}
			}
			else 
			{
				switch(state)
				{
					case 0:
						if(temp_data == HEADER)									//ͷ�̶�
						{
							Pack_Data.header = temp_data;
							state++;
							crc = CrcTable[(crc^temp_data) & 0xff];				//��ʼ����У��
						} else state = 0,crc = 0;
						break;
					case 1:
						if(temp_data == LENGTH)									//�����ĵ�����Ŀǰ�̶�
						{
							Pack_Data.ver_len = temp_data;
							state++;
							crc = CrcTable[(crc^temp_data) & 0xff];
						} else state = 0,crc = 0;
						break;
					case 2:
						Pack_Data.speed = (u16)temp_data;						//�״��ת�ٵ�8λ����λ��ÿ��
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
						break;
					case 3:
						Pack_Data.speed = ((u16)temp_data<<8)+Pack_Data.speed;	//�״��ת�ٸ�8λ
						state++;
						crc = CrcTable[(crc^temp_data) & 0xff];
						break;
					case 4:
						Pack_Data.start_angle = (u16)temp_data;					//��ʼ�Ƕȵ�8λ���Ŵ���100��
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
#endif
	HAL_UART_Receive_IT(&huart5,Uart5_Receive_buf,sizeof(Uart5_Receive_buf));//����5�ص�����ִ�����֮����Ҫ�ٴο��������жϵȴ���һ�ν����жϵķ���	
	}
}


/**************************************************************************
Function: The data sent by the serial port is assigned
Input   : none
Output  : none
�������ܣ����ڷ��͵����ݽ��и�ֵ
��ڲ�������
����  ֵ����
**************************************************************************/
void data_transition(void)
{
	Send_Data.Sensor_Str.Frame_Header = FRAME_HEADER; //Frame_header //֡ͷ
	Send_Data.Sensor_Str.Frame_Tail = FRAME_TAIL;     //Frame_tail //֡β
	
	//According to different vehicle types, different kinematics algorithms were selected to carry out the forward kinematics solution, 
	//and the three-axis velocity was obtained from each wheel velocity
	//���ݲ�ͬ����ѡ��ͬ�˶�ѧ�㷨�����˶�ѧ���⣬�Ӹ������ٶ���������ٶ�
	switch(Car_Num)
	{	
		case Akm_Car:  
			Send_Data.Sensor_Str.X_speed = ((MotorA.Current_Encoder+MotorB.Current_Encoder)/2)*1000; 
			Send_Data.Sensor_Str.Y_speed = 0;
			Send_Data.Sensor_Str.Z_speed = ((MotorB.Current_Encoder-MotorA.Current_Encoder)/Akm_wheelspacing)*1000;
		  break; 
		
		case Diff_Car: 
			Send_Data.Sensor_Str.X_speed = ((MotorA.Current_Encoder+MotorB.Current_Encoder)/2)*1000; 
			Send_Data.Sensor_Str.Y_speed = 0;
			Send_Data.Sensor_Str.Z_speed = ((MotorB.Current_Encoder-MotorA.Current_Encoder)/Diff_wheelspacing)*1000;
			break; 
		
		case Small_Tank_Car: 
			Send_Data.Sensor_Str.X_speed = ((MotorA.Current_Encoder+MotorB.Current_Encoder)/2)*1000; 
			Send_Data.Sensor_Str.Y_speed = 0;
			Send_Data.Sensor_Str.Z_speed = ((MotorB.Current_Encoder-MotorA.Current_Encoder)/Small_Tank_wheelspacing)*1000;
			break; 
		
		case Big_Tank_Car: 
			Send_Data.Sensor_Str.X_speed = ((MotorA.Current_Encoder+MotorB.Current_Encoder)/2)*1000; 
			Send_Data.Sensor_Str.Y_speed = 0;
			Send_Data.Sensor_Str.Z_speed = ((MotorB.Current_Encoder-MotorA.Current_Encoder)/Big_Tank_wheelspacing)*1000;
			break; 
	}
	
	//The acceleration of the triaxial acceleration //���ٶȼ�������ٶ�
	Send_Data.Sensor_Str.Accelerometer.X_data= accel[1]; //The accelerometer Y-axis is converted to the ros coordinate X axis //���ٶȼ�Y��ת����ROS����X��
	Send_Data.Sensor_Str.Accelerometer.Y_data=-accel[0]; //The accelerometer X-axis is converted to the ros coordinate y axis //���ٶȼ�X��ת����ROS����Y��
	Send_Data.Sensor_Str.Accelerometer.Z_data= accel[2]; //The accelerometer Z-axis is converted to the ros coordinate Z axis //���ٶȼ�Z��ת����ROS����Z��
	
	//The Angle velocity of the triaxial velocity //���ٶȼ�������ٶ�
	Send_Data.Sensor_Str.Gyroscope.X_data= gyro[1]; //The Y-axis is converted to the ros coordinate X axis //���ٶȼ�Y��ת����ROS����X��
	Send_Data.Sensor_Str.Gyroscope.Y_data=-gyro[0]; //The X-axis is converted to the ros coordinate y axis //���ٶȼ�X��ת����ROS����Y��
	if(Flag_Stop==0) 
		//If the motor control bit makes energy state, the z-axis velocity is sent normall
	  //����������λʹ��״̬����ô��������Z����ٶ�
		Send_Data.Sensor_Str.Gyroscope.Z_data=gyro[2];  
	else  
		//If the robot is static (motor control dislocation), the z-axis is 0
    //����������Ǿ�ֹ�ģ��������λʧ�ܣ�����ô���͵�Z����ٶ�Ϊ0		
		Send_Data.Sensor_Str.Gyroscope.Z_data=0;        
	
	//Battery voltage (this is a thousand times larger floating point number, which will be reduced by a thousand times as well as receiving the data).
	//��ص�ѹ(���ｫ�������Ŵ�һǧ�����䣬��Ӧ���ڽ��ն��ڽ��յ����ݺ�Ҳ����Сһǧ��)
	Send_Data.Sensor_Str.Power_Voltage = Voltage*1000; 
	
	Send_Data.buffer[0]=Send_Data.Sensor_Str.Frame_Header; //Frame_heade //֡ͷ
  Send_Data.buffer[1]=Flag_Stop; //Car software loss marker //С�����ʧ�ܱ�־λ
	
	//The three-axis speed of / / car is split into two eight digit Numbers
	//С�������ٶ�,���ᶼ���Ϊ����8λ�����ٷ���
	Send_Data.buffer[2]=Send_Data.Sensor_Str.X_speed >>8; 
	Send_Data.buffer[3]=Send_Data.Sensor_Str.X_speed ;    
	Send_Data.buffer[4]=Send_Data.Sensor_Str.Y_speed>>8;  
	Send_Data.buffer[5]=Send_Data.Sensor_Str.Y_speed;     
	Send_Data.buffer[6]=Send_Data.Sensor_Str.Z_speed >>8; 
	Send_Data.buffer[7]=Send_Data.Sensor_Str.Z_speed ;    
	
	//The acceleration of the triaxial axis of / / imu accelerometer is divided into two eight digit reams
	//IMU���ٶȼ�������ٶ�,���ᶼ���Ϊ����8λ�����ٷ���
	Send_Data.buffer[8]=Send_Data.Sensor_Str.Accelerometer.X_data>>8; 
	Send_Data.buffer[9]=Send_Data.Sensor_Str.Accelerometer.X_data;   
	Send_Data.buffer[10]=Send_Data.Sensor_Str.Accelerometer.Y_data>>8;
	Send_Data.buffer[11]=Send_Data.Sensor_Str.Accelerometer.Y_data;
	Send_Data.buffer[12]=Send_Data.Sensor_Str.Accelerometer.Z_data>>8;
	Send_Data.buffer[13]=Send_Data.Sensor_Str.Accelerometer.Z_data;
	
	//The axis of the triaxial velocity of the / /imu is divided into two eight digits
	//IMU���ٶȼ�������ٶ�,���ᶼ���Ϊ����8λ�����ٷ���
	Send_Data.buffer[14]=Send_Data.Sensor_Str.Gyroscope.X_data>>8;
	Send_Data.buffer[15]=Send_Data.Sensor_Str.Gyroscope.X_data;
	Send_Data.buffer[16]=Send_Data.Sensor_Str.Gyroscope.Y_data>>8;
	Send_Data.buffer[17]=Send_Data.Sensor_Str.Gyroscope.Y_data;
	Send_Data.buffer[18]=Send_Data.Sensor_Str.Gyroscope.Z_data>>8;
	Send_Data.buffer[19]=Send_Data.Sensor_Str.Gyroscope.Z_data;
	
	//Battery voltage, split into two 8 digit Numbers
	//��ص�ѹ,���Ϊ����8λ���ݷ���
	Send_Data.buffer[20]=Send_Data.Sensor_Str.Power_Voltage >>8; 
	Send_Data.buffer[21]=Send_Data.Sensor_Str.Power_Voltage; 

  //Data check digit calculation, Pattern 1 is a data check
  //����У��λ���㣬ģʽ1�Ƿ�������У��
	Send_Data.buffer[22]=Check_Sum(22,1); 
	
	Send_Data.buffer[23]=Send_Data.Sensor_Str.Frame_Tail; //Frame_tail //֡β
}

/**************************************************************************
Function: After the top 8 and low 8 figures are integrated into a short type data, the unit reduction is converted
Input   : 8 bits high, 8 bits low
Output  : The target velocity of the robot on the X/Y/Z axis
�������ܣ�����λ��������Ŀ��ǰ���ٶ�Vx��Ŀ����ٶ�Vz��ת��Ϊ������С������ǰ��ת��
��ڲ�����Ŀ��ǰ���ٶ�Vx��Ŀ����ٶ�Vz����λ��m/s��rad/s
����  ֵ��������С������ǰ��ת�ǣ���λ��rad
**************************************************************************/
float Vz_to_Akm_Angle(float Vx, float Vz)
{
	float R, AngleR, Min_Turn_Radius;
	//float AngleL;
	
	//Ackermann car needs to set minimum turning radius
	//If the target speed requires a turn radius less than the minimum turn radius,
	//This will greatly improve the friction force of the car, which will seriously affect the control effect
	//������С����Ҫ������Сת��뾶
	//���Ŀ���ٶ�Ҫ���ת��뾶С����Сת��뾶��
	//�ᵼ��С���˶�Ħ���������ߣ�����Ӱ�����Ч��
	Min_Turn_Radius=MINI_AKM_MIN_TURN_RADIUS;
	
	if(Vz!=0 && Vx!=0)
	{
		//If the target speed requires a turn radius less than the minimum turn radius
		//���Ŀ���ٶ�Ҫ���ת��뾶С����Сת��뾶
		if(float_abs(Vx/Vz)<=Min_Turn_Radius)
		{
			//Reduce the target angular velocity and increase the turning radius to the minimum turning radius in conjunction with the forward speed
			//����Ŀ����ٶȣ����ǰ���ٶȣ����ת��뾶����Сת��뾶
			if(Vz>0)
				Vz= float_abs(Vx)/(Min_Turn_Radius);
			else	
				Vz=-float_abs(Vx)/(Min_Turn_Radius);	
		}		
		R=Vx/Vz;
		//AngleL=atan(Axle_spacing/(R-0.5*Wheel_spacing));
		AngleR=atan(Akm_axlespacing/(R+0.5f*Akm_wheelspacing));
	}
	else
	{
		AngleR=0;
	}
	
	return AngleR;
}
/**************************************************************************
Function: After the top 8 and low 8 figures are integrated into a short type data, the unit reduction is converted
Input   : 8 bits high, 8 bits low
Output  : The target velocity of the robot on the X/Y/Z axis
�������ܣ�����λ���������ĸ�8λ�͵�8λ�������ϳ�һ��short�����ݺ�������λ��ԭ����
��ڲ�������8λ����8λ
����  ֵ��������X/Y/Z���Ŀ���ٶ�
**************************************************************************/
float XYZ_Target_Speed_transition(u8 High,u8 Low)
{
	//Data conversion intermediate variable
	//����ת�����м����
	short transition; 
	
	//����8λ�͵�8λ���ϳ�һ��16λ��short������
	//The high 8 and low 8 bits are integrated into a 16-bit short data
	transition=((High<<8)+Low)/1000; 
	return transition; 					
}

/**************************************************************************
Function: Serial port 1 sends data
Input   : none
Output  : none
�������ܣ�����1��������
��ڲ�������
����  ֵ����
**************************************************************************/
void USART1_SEND(void)
{
     u8 i = 0;	
	for(i=0; i<24; i++)
	{
		usart1_send(Send_Data.buffer[i]);
	}	 
}

/**************************************************************************
Function: Serial port 1 sends data
Input   : The data to send
Output  : none
�������ܣ�����1��������
��ڲ�����Ҫ���͵�����
����  ֵ����
**************************************************************************/
void usart1_send(u8 data)
{
	USART1->DR = data;
	while((USART1->SR&0x40)==0);	
}

/**************************************************************************
Function: Calculates the check bits of data to be sent/received
Input   : Count_Number: The first few digits of a check; Mode: 0-Verify the received data, 1-Validate the sent data
Output  : Check result
�������ܣ�����Ҫ����/���յ�����У����
��ڲ�����Count_Number��У���ǰ��λ����Mode��0-�Խ������ݽ���У�飬1-�Է������ݽ���У��
����  ֵ��У����
**************************************************************************/
u8 Check_Sum(unsigned char Count_Number,unsigned char Mode)
{
	unsigned char check_sum=0,k;
	
	//Validate the data to be sent
	//��Ҫ���͵����ݽ���У��
	if(Mode==1)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Send_Data.buffer[k];
	}
	
	//Verify the data received
	//�Խ��յ������ݽ���У��
	if(Mode==0)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Receive_Data.buffer[k];
	}
	return check_sum;
}


/**************************************************************************
Function: Floating-point data calculates the absolute value
Input   : float
Output  : The absolute value of the input number
�������ܣ����������ݼ������ֵ
��ڲ�����������
����  ֵ���������ľ���ֵ
**************************************************************************/
float float_abs(float insert)
{
	if(insert>=0) return insert;
	else return -insert;
}
