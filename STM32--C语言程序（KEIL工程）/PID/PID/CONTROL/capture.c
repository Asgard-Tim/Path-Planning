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

//���ģ��Ĭ�ϲ�ʹ��
//4·������ģ��
//�� 4·��ģң��
#include "capture.h"
TIM_HandleTypeDef htim2;
u16 Distance1,Distance2,Distance3,Distance4;	//4�����������������

// ��ʱ�����벶���û��Զ�������ṹ�嶨��
TIM_ICUserValueTypeDef Distance_TIM2_CH2_ICUserValueStructure = {0,0,0,0};//������ģ��1������Ӧ�ı���
TIM_ICUserValueTypeDef Distance_TIM2_CH3_ICUserValueStructure = {0,0,0,0};//������ģ��2������Ӧ�ı���
TIM_ICUserValueTypeDef Distance_TIM2_CH4_ICUserValueStructure = {0,0,0,0};//������ģ��3������Ӧ�ı���
TIM_ICUserValueTypeDef Distance_TIM1_CH4_ICUserValueStructure = {0,0,0,0};//������ģ��4������Ӧ�ı���


TIM_ICUserValueTypeDef PWM_TIM2_CH4_ICUserValueStructure = {0,0,0,0};//��ģң�ص�һ·
TIM_ICUserValueTypeDef PWM_TIM2_CH3_ICUserValueStructure = {0,0,0,0};//��ģң�صڶ�·
TIM_ICUserValueTypeDef PWM_TIM1_CH4_ICUserValueStructure = {0,0,0,0};//��ģң�ص���·
TIM_ICUserValueTypeDef PWM_TIM1_CH1_ICUserValueStructure = {0,0,0,0};//��ģң�ص���·

/* TIM2 init function */
void MX_TIM2_Init(u16 arr,u16 psc) //��������ʼ��
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = arr;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = psc;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
   HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_2);  //������ʱ��ͨ��2��3��4���벶���ж�
	 HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_4);
  /* USER CODE END TIM2_Init 2 */

}


void TIM1_Init(u16 arr,u16 psc) //��������ʼ��ͨ����
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = arr;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = psc;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */
    HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_4);//������ʱ��1ͨ��4�����벶���ж�

   __HAL_TIM_ENABLE_IT(&htim1,TIM_IT_UPDATE);//�����ж������������
  /* USER CODE END TIM1_Init 2 */

}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef* tim_icHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_icHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PA1     ------> TIM2_CH2
    PA2     ------> TIM2_CH3
    PA3     ------> TIM2_CH4
		PA11    ------> TIM1_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
	else if(tim_icHandle->Instance==TIM1)
	{
	/* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM1 GPIO Configuration
		PA11    ------> TIM1_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
	}
	
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
}

void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef* tim_icHandle)
{

  if(tim_icHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /**TIM2 GPIO Configuration
    PA1     ------> TIM2_CH2
    PA2     ------> TIM2_CH3
    PA3     ------> TIM2_CH4
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
}
/**************************************************************************
Function: Distance_Cap_Init
Input   : TIM_Period,TIM_Prescaler
Output  : none
�������ܣ���������ʼ��
��ڲ���: Ԥװ��ֵ��Ԥ��Ƶ�� 
����  ֵ����
**************************************************************************/	 	
void Distance_Cap_Init(u16 arr,u16 psc)
{
	MX_TIM2_Init(arr,psc);
	TIM1_Init(arr,psc);
}

/**************************************************************************
Function: PWM_Capture_Mode_Config
Input   : TIM_Period,TIM_Prescaler
Output  : none
�������ܣ���ģң�ز���PWM�ߵ�ƽ��ʼ��
��ڲ���: Ԥװ��ֵ��Ԥ��Ƶ�� 
����  ֵ����
**************************************************************************/	 	
void PWM_Cap_Init(u16 arr,u16 psc) //��ģ�ĺͳ�������һ�£�ֻ�Ǻ�ģ����Ҫ������ţ�������gpioһ����ʼ���ˣ�����Ҫ���
{
	MX_TIM2_Init(arr,psc);
	TIM1_Init(arr,psc);
}


/**************************************************************************
Function: Read_Distane
Input   : none
Output  : none
�������ܣ���ȡ������������
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
//��5ms��ʱ�ж��е���
void Read_Distane(void)        
{   
	
	static u16 cnt = 0;	 //������������������Ҫ̫Ƶ������Ծ���Ļ�ȡ��һ����Ӱ��
	u32 temp_distance;
	cnt++;
	if(cnt == 20)		 //���ڴ������ٶ�
	{
		TRIG_HIGH1;      //������ģ��1����   
		delay_us(15);  
		TRIG_LOW1;	
		
		TRIG_HIGH2;      //������ģ��2����   
		delay_us(15);  
		TRIG_LOW2;	

	}
	if(cnt == 40)
	{
		cnt =0;
		TRIG_HIGH3;      //������ģ��3����   
		delay_us(15);  
		TRIG_LOW3;	
		
		TRIG_HIGH4;      //������ģ��4����   
		delay_us(15);  
		TRIG_LOW4;	
	}

	//������ģ��1
	if(Distance_TIM2_CH2_ICUserValueStructure.Capture_FinishFlag)//�ɹ�������һ�θߵ�ƽ
	{
		temp_distance=Distance_TIM2_CH2_ICUserValueStructure.Capture_CcrValue+Distance_TIM2_CH2_ICUserValueStructure.Capture_Period*65536; //һ���������ٴ�
		Distance1=temp_distance*Light_Speed/2/1000;  						//ʱ��*����/2�����أ� һ������0.001ms
		Distance_TIM2_CH2_ICUserValueStructure.Capture_FinishFlag = 0;			//������һ�β���
	}
	//������ģ��2
	if(Distance_TIM2_CH3_ICUserValueStructure.Capture_FinishFlag)//�ɹ�������һ�θߵ�ƽ
	{
		temp_distance=Distance_TIM2_CH3_ICUserValueStructure.Capture_CcrValue+Distance_TIM2_CH3_ICUserValueStructure.Capture_Period*65536; //һ���������ٴ�
		Distance2=temp_distance*Light_Speed/2/1000;  						//ʱ��*����/2�����أ� һ������0.001ms
		Distance_TIM2_CH3_ICUserValueStructure.Capture_FinishFlag = 0;			//������һ�β���
	}
	//������ģ��3
	if(Distance_TIM2_CH4_ICUserValueStructure.Capture_FinishFlag)//�ɹ�������һ�θߵ�ƽ
	{
		temp_distance=Distance_TIM2_CH4_ICUserValueStructure.Capture_CcrValue+Distance_TIM2_CH4_ICUserValueStructure.Capture_Period*65536; //һ���������ٴ�
		Distance3=temp_distance*Light_Speed/2/1000;  						//ʱ��*����/2�����أ� һ������0.001ms
		Distance_TIM2_CH4_ICUserValueStructure.Capture_FinishFlag = 0;			//������һ�β���
	}
	//������ģ��4
	if(Distance_TIM1_CH4_ICUserValueStructure.Capture_FinishFlag)//�ɹ�������һ�θߵ�ƽ
	{
		temp_distance=Distance_TIM1_CH4_ICUserValueStructure.Capture_CcrValue+Distance_TIM1_CH4_ICUserValueStructure.Capture_Period*65536; //һ���������ٴ�
		Distance4=temp_distance*Light_Speed/2/1000;  						//ʱ��*����/2�����أ� һ������0.001ms
		Distance_TIM1_CH4_ICUserValueStructure.Capture_FinishFlag = 0;			//������һ�β���
	}

}


//ʹ�ó�����
#ifdef Distance_Capture


/**************************************************************************
Function: HAL_TIM_IC_CaptureCallback
Input   : none
Output  : none
�������ܣ��ߵ�ƽ�����жϻص�����
��ڲ���: ��
����  ֵ����
**************************************************************************/	 	
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{ 	
	// ��Ҫ��������źŵ����ڴ��ڶ�ʱ�������ʱʱ����ʱ���ͻ���������������ж�
	// ���ʱ��������Ҫ�������Ķ�ʱ���ڼӵ������źŵ�ʱ������ȥ
	if(htim == &htim2)
	{
	/*************************************ͨ��2*******************************************/
	  if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if(Distance_TIM2_CH2_ICUserValueStructure.Capture_FinishFlag == 0)//û�����һ�ε�ʱ�򲶻���ܽ�ȥ����ֹ�����������
	    {
				Distance_TIM2_CH2_ICUserValueStructure.Capture_Period ++;
					if( Distance_TIM2_CH2_ICUserValueStructure.Capture_StartFlag == 0)// ��һ�β���
				{
					Distance_TIM2_CH2_ICUserValueStructure.Capture_CcrValue = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);//��һ�β���ʱ���Ѳ���ֵ��������
					Distance_TIM2_CH2_ICUserValueStructure.Capture_Period =0;// �Զ���װ�ؼĴ������±�־��0
					__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
									// ��ʼ�����־λ��1			
					Distance_TIM2_CH2_ICUserValueStructure.Capture_StartFlag = 1;	
				}
				else// �½��ز����ж�,�ڶ��β���
				{
					// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
					Distance_TIM2_CH2_ICUserValueStructure.Capture_CcrValue = 
					HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2)-Distance_TIM2_CH2_ICUserValueStructure.Capture_CcrValue;
					// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
					__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);
					// ��ʼ�����־��0		
					Distance_TIM2_CH2_ICUserValueStructure.Capture_StartFlag = 0;
				}
			}
		}
	/*************************************ͨ��3*******************************************/
	 if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3)
		{
			if(Distance_TIM2_CH3_ICUserValueStructure.Capture_FinishFlag == 0)//û�����һ�ε�ʱ�򲶻���ܽ�ȥ����ֹ�����������
	    {
				 Distance_TIM2_CH3_ICUserValueStructure.Capture_Period ++;
					if(Distance_TIM2_CH3_ICUserValueStructure.Capture_StartFlag==0)// ��һ�β���
				{
					Distance_TIM2_CH3_ICUserValueStructure.Capture_CcrValue = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_3);//��һ�β���ʱ���Ѳ���ֵ��������
					Distance_TIM2_CH3_ICUserValueStructure.Capture_Period =0;
					__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
					Distance_TIM2_CH3_ICUserValueStructure.Capture_StartFlag = 1; // ��ʼ�����־λ��1		
				}
				else
				{
					// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
					Distance_TIM2_CH3_ICUserValueStructure.Capture_CcrValue=
					HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_3)-Distance_TIM2_CH3_ICUserValueStructure.Capture_CcrValue;
					__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
					Distance_TIM2_CH3_ICUserValueStructure.Capture_StartFlag = 0;// ��ʼ�����־��0		
				}
			}
		}
	/*************************************ͨ��4*******************************************/
   if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)
	 {
		 if(Distance_TIM2_CH4_ICUserValueStructure.Capture_FinishFlag == 0)//û�����һ�ε�ʱ�򲶻���ܽ�ȥ����ֹ�����������
	   {
			  Distance_TIM2_CH4_ICUserValueStructure.Capture_Period ++;
				if(Distance_TIM2_CH4_ICUserValueStructure.Capture_StartFlag==0)// ��һ�β���
				{
					Distance_TIM2_CH4_ICUserValueStructure.Capture_CcrValue = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_4);//��һ�β���ʱ���Ѳ���ֵ��������
					Distance_TIM2_CH4_ICUserValueStructure.Capture_Period=0;
					__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
					Distance_TIM2_CH4_ICUserValueStructure.Capture_StartFlag = 1; // ��ʼ�����־λ��1		
				}
				else
				{
					// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
					Distance_TIM2_CH4_ICUserValueStructure.Capture_CcrValue=
					HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_4)-Distance_TIM2_CH4_ICUserValueStructure.Capture_CcrValue;
					__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
					Distance_TIM2_CH4_ICUserValueStructure.Capture_StartFlag = 0;// ��ʼ�����־��0		
				}
			}
		
	 }
  }
	else if(htim==&htim1)
	{
		 if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)
	 {
		 if(Distance_TIM1_CH4_ICUserValueStructure.Capture_FinishFlag == 0)//û�����һ�ε�ʱ�򲶻���ܽ�ȥ����ֹ�����������
	   {
			 if(Distance_TIM1_CH4_ICUserValueStructure.Capture_StartFlag==0)// ��һ�β���
			{
        Distance_TIM1_CH4_ICUserValueStructure.Capture_CcrValue = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_4);//��һ�β���ʱ���Ѳ���ֵ��������
				Distance_TIM1_CH4_ICUserValueStructure.Capture_Period =0;
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
				Distance_TIM1_CH4_ICUserValueStructure.Capture_StartFlag = 1; // ��ʼ�����־λ��1		
			}
			else
			{
				// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
				Distance_TIM1_CH4_ICUserValueStructure.Capture_CcrValue=
				HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_4)-Distance_TIM1_CH4_ICUserValueStructure.Capture_CcrValue;
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
				Distance_TIM1_CH4_ICUserValueStructure.Capture_StartFlag = 0;// ��ʼ�����־��0		
			}
		 }
		 
	 }
	}
}
#endif


//ʹ�ú�ģң��
#ifdef PWM_Capture
/**************************************************************************
Function: HAL_TIM_IC_CaptureCallback
Input   : none
Output  : none
�������ܣ��ߵ�ƽ�����жϻص�����
��ڲ���: ��
����  ֵ����
**************************************************************************/	
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{ 	
	// ��Ҫ��������źŵ����ڴ��ڶ�ʱ�������ʱʱ����ʱ���ͻ���������������ж�
	// ���ʱ��������Ҫ�������Ķ�ʱ���ڼӵ������źŵ�ʱ������ȥ
	if(htim == &htim2)
	{
	/*************************************ͨ��2*******************************************/
	  if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if( Distance_TIM2_CH2_ICUserValueStructure.Capture_StartFlag == 0)// ��һ�β���
			{
			  Distance_TIM2_CH2_ICUserValueStructure.Capture_CcrValue = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);//��һ�β���ʱ���Ѳ���ֵ��������
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
								// ��ʼ�����־λ��1			
				Distance_TIM2_CH2_ICUserValueStructure.Capture_StartFlag = 1;	
			}
			else// �½��ز����ж�,�ڶ��β���
			{
				// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
				Distance_TIM2_CH2_ICUserValueStructure.Capture_CcrValue = 
				HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2)-Distance_TIM2_CH2_ICUserValueStructure.Capture_CcrValue;
			  // ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING);
				// ��ʼ�����־��0		
				Distance_TIM2_CH2_ICUserValueStructure.Capture_StartFlag = 0;
			}
		}
	/*************************************ͨ��3*******************************************/
	 if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_3)
		{
			if(Distance_TIM2_CH3_ICUserValueStructure.Capture_StartFlag==0)// ��һ�β���
			{
        Distance_TIM2_CH3_ICUserValueStructure.Capture_CcrValue = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_3);//��һ�β���ʱ���Ѳ���ֵ��������
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
				Distance_TIM2_CH3_ICUserValueStructure.Capture_StartFlag = 1; // ��ʼ�����־λ��1		
			}
			else
			{
				// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
				Distance_TIM2_CH3_ICUserValueStructure.Capture_CcrValue=
				HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_3)-Distance_TIM2_CH3_ICUserValueStructure.Capture_CcrValue;
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
				Distance_TIM2_CH3_ICUserValueStructure.Capture_StartFlag = 0;// ��ʼ�����־��0		
			}
		}
	/*************************************ͨ��4*******************************************/
   if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)
	 {
		 if(Distance_TIM2_CH4_ICUserValueStructure.Capture_StartFlag==0)// ��һ�β���
			{
        Distance_TIM2_CH4_ICUserValueStructure.Capture_CcrValue = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_4);//��һ�β���ʱ���Ѳ���ֵ��������
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
				Distance_TIM2_CH4_ICUserValueStructure.Capture_StartFlag = 1; // ��ʼ�����־λ��1		
			}
			else
			{
				// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
				Distance_TIM2_CH4_ICUserValueStructure.Capture_CcrValue=
				HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_4)-Distance_TIM2_CH4_ICUserValueStructure.Capture_CcrValue;
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
				Distance_TIM2_CH4_ICUserValueStructure.Capture_StartFlag = 0;// ��ʼ�����־��0		
			}
	 }
  }
	else if(htim==&htim1)
	{
		 if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_4)
	 {
		 if(Distance_TIM1_CH4_ICUserValueStructure.Capture_StartFlag==0)// ��һ�β���
			{
        Distance_TIM1_CH4_ICUserValueStructure.Capture_CcrValue = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_4);//��һ�β���ʱ���Ѳ���ֵ��������
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);// ����һ�β���������֮�󣬾ͰѲ����������Ϊ�½���
				Distance_TIM1_CH4_ICUserValueStructure.Capture_StartFlag = 1; // ��ʼ�����־λ��1		
			}
			else
			{
				// ��ȡ����ȽϼĴ�����ֵ�����ֵ���ǲ��񵽵ĸߵ�ƽ��ʱ���ֵ
				Distance_TIM1_CH4_ICUserValueStructure.Capture_CcrValue=
				HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_4)-Distance_TIM1_CH4_ICUserValueStructure.Capture_CcrValue;
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);// ���ڶ��β����½���֮�󣬾ͰѲ����������Ϊ�����أ��ÿ����µ�һ�ֲ���
				Distance_TIM1_CH4_ICUserValueStructure.Capture_StartFlag = 0;// ��ʼ�����־��0		
			}
	 }
	}
}

#endif




