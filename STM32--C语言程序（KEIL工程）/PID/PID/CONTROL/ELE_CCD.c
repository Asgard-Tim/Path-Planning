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


#include "ELE_CCD.h"

int Sensor_Left,Sensor_Middle,Sensor_Right,Sensor;
u16  CCD_ADV[128]={0};
u8 CCD_Median,CCD_Threshold;                 //����CCD���



/**************************************************************************
Function: ELE_ADC_Mode_Config
Input   : none
Output  : none
�������ܣ���ʼ�����Ѳ��ADC
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	

static void ELE_ADC_Mode_Config(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ELE_ADC_L_CHANNEL;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	
	sConfig.Channel = ELE_ADC_M_CHANNEL;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
	
	sConfig.Channel = ELE_ADC_R_CHANNEL;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  HAL_ADC_Start(&hadc1);
  HAL_ADCEx_Calibration_Start(&hadc1); //����adcУ׼
}



/**************************************************************************
Function: CCD_ADC_Mode_Config
Input   : none
Output  : none
�������ܣ���ʼ��CCDѲ��ADC
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
static void CCD_ADC_Mode_Config(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = CCD_ADC_CHANNEL;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  HAL_ADC_Start(&hadc1);
  HAL_ADCEx_Calibration_Start(&hadc1); //����adcУ׼

}

/**************************************************************************
Function: CCD_GPIO_Config
Input   : none
Output  : none
�������ܣ���ʼ��CCDѲ��GPIO
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
static void CCD_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// ��CCD�˿�ʱ��
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	// CLK,SI����Ϊ���	
	GPIO_InitStruct.Pin = TSL_SI_PIN;				//PA4
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(TSL_SI_PORT, &GPIO_InitStruct);	


	GPIO_InitStruct.Pin = TSL_CLK_PIN;				//PA5
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(TSL_CLK_PORT, &GPIO_InitStruct);				
	
}


/**************************************************************************
Function: ELE_ADC_Init
Input   : none
Output  : none
�������ܣ���ʼ�����Ѳ��ADC
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
//���Ѳ�߳�ʼ��
void ELE_ADC_Init(void)
{
	//ELE_ADC_GPIO_Config();
	ELE_ADC_Mode_Config();

}


/**************************************************************************
Function: CCD_Init
Input   : none
Output  : none
�������ܣ���ʼ��CCDѲ��
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
void CCD_Init(void)
{
	CCD_GPIO_Config();
	CCD_ADC_Mode_Config();

}

/**************************************************************************
Function: ELE_Mode
Input   : none
Output  : none
�������ܣ����Ѳ��ģʽ����
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
void ELE_Mode(void)
{
	int Sum = 0;
	Sensor_Left = Get_Adc(ELE_ADC_L_CHANNEL);
	Sensor_Middle = Get_Adc(ELE_ADC_M_CHANNEL);
	Sensor_Right = Get_Adc(ELE_ADC_R_CHANNEL);
	Sum = Sensor_Left*1+Sensor_Middle*100+Sensor_Right*199;			
	Sensor = Sum/(Sensor_Left+Sensor_Middle+Sensor_Right);
	if(Detect_Barrier() == No_Barrier)		//��⵽���ϰ���
	{
		Move_X = ELE_Move_X;				//Ѳ�ߵ�ʱ���ٶ�,Ĭ����0.25m
		if(Car_Num == Diff_Car|| Car_Num == Akm_Car)
			Move_Z = ELE_PID(Sensor,92);		//Ŀ��ֵ92
		else
			Move_Z = ELE_PID(Sensor,100);		//Ŀ��ֵ100
		Buzzer_Alarm(0);
    }											
	else									//���ϰ���
	{
		if(!Flag_Stop)
			Buzzer_Alarm(100);				//�����ʹ�ܵ�ʱ�����ϰ��������������
		else 
			Buzzer_Alarm(0);
		Move_X = 0;
		Move_Z = 0;
	}
}

/**************************************************************************
Function: Detect_Barrier
Input   : none
Output  : 1or0(Barrier_Detected or No_Barrier)
�������ܣ����Ѳ��ģʽ�״����ϰ���
��ڲ���: ��
����  ֵ��1��0(��⵽�ϰ�������ϰ���)
**************************************************************************/	 	
//����ϰ���
u8 Detect_Barrier(void)
{
	int i;
	u8 point_count = 0;
	if(Lidar_Detect == Lidar_Detect_ON)
	{
		for(i=0;i<390;i++)	//����Ƿ����ϰ���
		{
			if((Dataprocess[i].angle>300)||(Dataprocess[i].angle<60))
			{
				if(0<Dataprocess[i].distance&&Dataprocess[i].distance<700)//700mm���Ƿ����ϰ���
					point_count++;
		  }
		}
		if(point_count > 3)//���ϰ���
			return Barrier_Detected;
		else
			return No_Barrier;
	}
	else
		return No_Barrier;
}
/**************************************************************************
�������ܣ������ʱ
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void Dly_us(void)
{
   int ii;    
   for(ii=0;ii<10;ii++);      
}

/**************************************************************************
Function: Read_TSL
Input   : none
Output  : none
�������ܣ���ȡCCDģ�������
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
//��ȡCCDģ�������
void RD_TSL(void) 
{
	u8 i=0,tslp=0;
	
	TSL_CLK_HIGH;
	TSL_SI_LOW;
	Dly_us();
	Dly_us();

	TSL_CLK_LOW;
	TSL_SI_LOW;
	Dly_us();
	Dly_us();

	TSL_CLK_LOW;
	TSL_SI_HIGH;
	Dly_us();
	Dly_us();

	TSL_CLK_HIGH;
	TSL_SI_HIGH;
	Dly_us();
	Dly_us();

	TSL_CLK_HIGH;
	TSL_SI_LOW;
	Dly_us();
	Dly_us();
	
	for(i=0;i<128;i++)
	{ 
		TSL_CLK_LOW; 
		Dly_us();  //�����ع�ʱ��
		Dly_us();
		CCD_ADV[tslp]=(Get_Adc(CCD_ADC_CHANNEL))>>4;		
		++tslp;
		TSL_CLK_HIGH;
		Dly_us();  
	}
}


/**************************************************************************
�������ܣ�����CCDȡ��ֵ
��ڲ�������
����  ֵ����
**************************************************************************/
void  Find_CCD_Median(void)
{ 
	static u8 i,j,Left,Right,Last_CCD_Median;
	static u16 value1_max,value1_min;

	value1_max=CCD_ADV[0];  //��̬��ֵ�㷨����ȡ������Сֵ
	for(i=15;i<123;i++)   //���߸�ȥ��15����
	{
		if(value1_max<=CCD_ADV[i])
		value1_max=CCD_ADV[i];
	}
	value1_min=CCD_ADV[0];  //��Сֵ
	for(i=15;i<123;i++) 
	{
		if(value1_min>=CCD_ADV[i])
		value1_min=CCD_ADV[i];
	}
	CCD_Threshold=(value1_max+value1_min)/2;	  //���������������ȡ����ֵ
	for(i = 15;i<118; i++)   //Ѱ�����������
	{
		if(CCD_ADV[i]>CCD_Threshold&&CCD_ADV[i+1]>CCD_Threshold&&CCD_ADV[i+2]>CCD_Threshold&&CCD_ADV[i+3]<CCD_Threshold&&CCD_ADV[i+4]<CCD_Threshold&&CCD_ADV[i+5]<CCD_Threshold)
		{	
			Left=i;
			break;	
		}
	}
	for(j = 118;j>15; j--)//Ѱ���ұ�������
	{
		if(CCD_ADV[j]<CCD_Threshold&&CCD_ADV[j+1]<CCD_Threshold&&CCD_ADV[j+2]<CCD_Threshold&&CCD_ADV[j+3]>CCD_Threshold&&CCD_ADV[j+4]>CCD_Threshold&&CCD_ADV[j+5]>CCD_Threshold)
		{	
			Right=j;
			break;	
		}
	}
	CCD_Median=(Right+Left)/2;//��������λ��
	if(myabs(CCD_Median-Last_CCD_Median)>90)   //�������ߵ�ƫ����̫��
		CCD_Median=Last_CCD_Median;    //��ȡ��һ�ε�ֵ
	Last_CCD_Median=CCD_Median;  //������һ�ε�ƫ��

}	
/**************************************************************************
Function: CCD_Mode
Input   : none
Output  : none
�������ܣ�CCDѲ��ģʽ����
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
void CCD_Mode(void)
{
	RD_TSL();			//��ȡCCDģ������
	Find_CCD_Median();	//����ֵ
	
	Move_X = CCD_Move_X;			//CCDѲ���ٶȣ�Ĭ��0.3m
	Move_Z = CCD_PID(CCD_Median,64);//PID���ڣ�Ŀ��ֵ64
}	


