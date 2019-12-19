/*!
  * @file     LQ_CTIME.c
  *
  * @brief    CTIME�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     LPC54606��5��32λ��CTIME
  *
  * @version  V1.1 
  *           �޸ļ�¼   2019/11/13  CTIMER0 PWMͨ��1 P0_3 �ܽŸ��ù���Ӧ����FUN2
  *           			 2019/12/11  �Ż�ע�� Doxygen
                         2019/12/11  �Ż�IO��ʼ������
  *
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "fsl_iocon.h"
#include "fsl_ctimer.h"
#include "LQ_CTIME.h"
#include "LQ_GPIO.h"



/*!
  * @brief    ��ʼ��CTIMERΪPWM�������
  *
  * @param    matchChannel   ��    CTIMERͨ��  LQ_CTIMER.h��ö����
  * @param    duty           ��    ռ�ձ� * CMTER_PWM_MAX
  * @param    pwmFreq_Hz     ��    Ƶ��
  *
  * @return   ��
  *
  * @note     һ��CTIMERģ��ֻ���������������PWM�����һ��
  * @note     һ��CTIMERģ�����ֻ�����3·PWMƵ����ͬ��PWM��
  *
  * @see      CTIMER_InitPwmConfig(CT0Output0_P0_0, 5000, 100);//��ʼ��P0_0 ��ΪCTIMER0��ͨ��0 ��PWM����� Ƶ��100Hz ռ�ձ� �ٷ�֮(5000/CMTER_PWM_MAX)*100
  *
  * @date     2019/5/7 ���ڶ�
  */
void CTIMER_InitPwmConfig(CTIMER_OutputChannel_t matchChannel, uint32_t duty, uint32_t pwmFreq_Hz)
{
	static uint8_t flag[5];
	uint8_t index = matchChannel >> 12;
    uint8_t channel_temp = (matchChannel&0x0F00)>>8;
	CTIMER_Type     * TIMERN[] = CTIMER_BASE_PTRS;
	CTIMER_Type     * base = TIMERN[index];
	
	assert(pwmFreq_Hz > 0);
	uint32_t reg;   
	ctimer_config_t cconfig;  
	if (index >= 3)      
	{  
		// Ctimer3��4ʹ��12 MHzʱ��
		CLOCK_AttachClk(kFRO12M_to_ASYNC_APB);
		
		pwmFreq_Hz = (CLOCK_GetFreq(kCLOCK_AsyncApbClk) / pwmFreq_Hz) - 1; 
	}     
	else   
	{
		pwmFreq_Hz = (CLOCK_GetFreq(kCLOCK_BusClk) / pwmFreq_Hz) - 1;//BUSCLK=180Mʱ�� 
	}
	
	if (channel_temp == kCTIMER_Match_3)
	{
		return ;
	}
	/* ��ֹ�ظ���ʼ�� */
	if(flag[index] < 1)
	{
		flag[index]++;
		/* ��ʼ�� CTIMER */
		CTIMER_GetDefaultConfig(&cconfig);
		CTIMER_Init(base, &cconfig); 
	}

	/* ��ʼ����Ӧ�ܽ� */
	CTIME_PWMPinInit(matchChannel);
	
	/* ʹ��PWMģʽ */
	base->PWMC |= (1U << (channel_temp));
	
	/* �����־λ */
	reg = base->MCR;
	reg &= ~((CTIMER_MCR_MR0R_MASK | CTIMER_MCR_MR0S_MASK | CTIMER_MCR_MR0I_MASK) << ((channel_temp) * 3));
	
	/* ��������ͨ��  */
	reg |= CTIMER_MCR_MR3R_MASK;
	
	base->MCR = reg;  
	
	/* ����PWMƵ�� */
	base->MR[kCTIMER_Match_3] = pwmFreq_Hz;
	
	/* ����ռ�ձ� */
	base->MR[channel_temp] = (uint32_t)(pwmFreq_Hz * ((float)(CMTER_PWM_MAX - duty)/CMTER_PWM_MAX)); 
	
	/* �����־λ */
	CTIMER_ClearStatusFlags(base, CTIMER_IR_MR0INT_MASK << channel_temp);
	
	CTIMER_StartTimer(base);
	return;
}



/*!
  * @brief    CTIMER ����PWMռ�ձ�
  *
  * @param    matchChannel   ��    CTIMERͨ��
  * @param    duty           ��    ռ�ձ� * CMTER_PWM_MAX
  *
  * @return   ��
  *
  * @note     ʹ��ǰ���ȳ�ʼ����Ӧͨ��
  *
  * @see      CTIMER_SetDuty(CT0Output0_P0_0, 4000); //����P0_0 ͨ�� PWMռ�ձ� �ٷ�֮ �ٷ�֮(4000/CMTER_PWM_MAX)*100 
  *
  * @date     2019/5/7 ���ڶ�
  */
void CTIMER_SetDuty(CTIMER_OutputChannel_t matchChannel, uint32_t duty)
{ 
    CTIMER_Type     * TIMERN[] = CTIMER_BASE_PTRS;
    CTIMER_Type     * base = TIMERN[matchChannel >> 12];
    
    uint32_t pulsePeriod = 0, period;

    /* ��ȡ���� */
    period = base->MR[kCTIMER_Match_3];

    if (duty == 0)
    {
        pulsePeriod = period + 1;
    }
    else
    {
        pulsePeriod = (uint32_t)(period * ((float)(CMTER_PWM_MAX - duty)/CMTER_PWM_MAX));
    }

    /* ����ռ�ձ� */
    base->MR[((matchChannel&0x0F00)>>8)] = pulsePeriod;
}

/*!
  * @brief    ��ʼ��CTIMER ��Ϊ�����������
  *
  * @param    base     �� CTIMER0 - CTIMER4
  * @param    channel  �� �����������ͨ��
  *
  * @return   ��
  *
  * @note     LPCֻ���ô����������  
  *
  * @see      CTIMER_InitCapConfig(CTIMER0, CT0Input0_P0_1);//��ʼ��CTIMER0 Ϊ���岶���� ʹ��P0_1�ܽŲ�������
  *
  * @date     2019/10/21 ����һ
  */
void CTIMER_InitCapConfig(CTIMER_Type *base, CTIMER_InputChannel_t channel)
{
  
    CTIMER_CAPPinInit(channel);
    
    ctimer_config_t CTimerConfigStruct;
    
    // ����CTimerΪ���벶׽ģʽ��������ģʽ���½��ز�׽ 
    CTimerConfigStruct.mode = kCTIMER_IncreaseOnFallEdge;
    CTimerConfigStruct.input= (ctimer_capture_channel_t)((channel>>8)&0x000f);  
    CTimerConfigStruct.prescale = 0U; // ���÷�Ƶ���� 

    CTIMER_Init(base, &CTimerConfigStruct);
    CTIMER_StartTimer(base);
}


/*!
  * @brief    CTIMER �õ�����ֵ
  *
  * @param    base        �� CTIMER0 - CTIMER4
  * @param    pin         �� ����ܽ� DIR
  *
  * @return   �������ֵ
  *
  * @note     ʹ��ǰ��Ҫ��CTMIE��ʼ�� ����ܽ�Ҳ��Ҫ��ʼ��
  *
  * @see      CTIMER_GetCounter(CTIMER0, P1_11); //��ȡCTIMER0�������ֵ P1_11�ӱ���������ܽţ�DIR��
  *
  * @date     2019/5/7 ���ڶ�
  */
int16_t CTIMER_GetCounter(CTIMER_Type *base, GPIO_Name_t pin)
{          
    /* ��ȡ�������ֵ */
    int16_t temp = CTIMER_GetTimerCountValue(base);
    
    /* �����Ӧ������ */
    CTIMER_Reset(base);
    
    if(PIN_Read(pin) == 0)
        return -temp;
    else
        return temp;
    
}






/*!
  * @brief    CTIMER PWM����ܽų�ʼ��
  *
  * @param    CTn_CHn  : PWMͨ��
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      CTIME_PWMPinInit(CT0Output0_P0_0); //��ʼ��P0_0 ΪCTIMER0 ��ͨ��0
  *
  * @date     2019/10/21 ����һ
  */
void CTIME_PWMPinInit(CTIMER_OutputChannel_t CTn_CHn)
{    
    uint32_t PIOFun2_config = FUNC2|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun3_config = FUNC3|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun4_config = FUNC4|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    
    /* ���� ʱ�� */
    CLOCK_EnableClock(kCLOCK_Iocon);
    
    switch(CTn_CHn)
    {
      case  CT0Output0_P0_0:       
        IOCON_PinMuxSet(IOCON, 0, 0, PIOFun3_config);
        break;
     
      case  CT0Output0_P0_30:       
        IOCON_PinMuxSet(IOCON, 0,30, PIOFun4_config);          
        break;     
        
      case CT0Output1_P0_3:        
        IOCON_PinMuxSet(IOCON, 0, 3, PIOFun2_config);
        break;
        
      case CT0Output1_P0_31:
        IOCON_PinMuxSet(IOCON, 0,31, PIOFun4_config);
        break;     
        
      case  CT0Output2_P0_19:        
        IOCON_PinMuxSet(IOCON, 0,19, PIOFun3_config);
        break;
        
      case CT0Output2_P1_31:
        IOCON_PinMuxSet(IOCON, 1,31, PIOFun4_config);
        break; 
        
      case CT1Output0_P0_18:       
        IOCON_PinMuxSet(IOCON, 0, 18, PIOFun3_config);
        break;
        
      case CT1Output0_P1_10:
        IOCON_PinMuxSet(IOCON, 1,10, PIOFun3_config);
        break;    
        
      case CT1Output1_P0_20:        
        IOCON_PinMuxSet(IOCON, 0, 20, PIOFun2_config);
        break;
        
      case CT1Output1_P1_12:
        IOCON_PinMuxSet(IOCON, 1,12, PIOFun3_config);
        break; 
        
      case CT1Output2_P0_23: 
        IOCON_PinMuxSet(IOCON, 0,23, PIOFun2_config);
        break;
        
      case CT1Output2_P1_14:
        IOCON_PinMuxSet(IOCON, 1,14, PIOFun3_config);  
        break;      
        
      case CT2Output0_P0_10: 
        IOCON_PinMuxSet(IOCON, 0,10, PIOFun3_config);
        break;
        
      case CT2Output0_P1_5:
        IOCON_PinMuxSet(IOCON, 1, 5, PIOFun3_config);    
        break;     
        
      case CT2Output1_P1_4: 
        IOCON_PinMuxSet(IOCON, 1, 4, PIOFun3_config);
        break;
        
      case CT2Output1_P1_6:
        IOCON_PinMuxSet(IOCON, 1, 6, PIOFun3_config);  
        break;      
        
      case CT2Output2_P0_11: 
        IOCON_PinMuxSet(IOCON, 0,11, PIOFun2_config);
        break;
        
      case CT2Output2_P1_7:
        IOCON_PinMuxSet(IOCON, 1,7, PIOFun3_config);
        break;      
        
      case CT3Output0_P0_5: 
        IOCON_PinMuxSet(IOCON, 0, 5, PIOFun3_config);
        break;      
        
      case CT3Output1_P1_19: 
        IOCON_PinMuxSet(IOCON, 1, 19, PIOFun3_config); 
        break;      
        
      case CT3Output2_P0_27: 
        IOCON_PinMuxSet(IOCON, 0,27, PIOFun3_config);
        break;
        
      case CT3Output2_P1_21:
        IOCON_PinMuxSet(IOCON, 1,21, PIOFun3_config);
        break;   
        
      case CT4Output0_P0_6: 
        IOCON_PinMuxSet(IOCON, 0, 6, PIOFun3_config);
        break;      

      default:
        break;
    }           
}

/*!
  * @brief    CTIMER ��������ܽų�ʼ��
  *
  * @param    channel  �� ���岶��ͨ��
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      CTIMER_CAPPinInit(CT0Input0_P0_1); //��ʼ��P0_1 �ܽŸ���ΪCTIMER����ܽ�
  * 
  * @date     2019/10/21 ����һ
  */
void CTIMER_CAPPinInit(CTIMER_InputChannel_t channel)
{
    uint32_t PIOFun2_config = FUNC2|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun3_config = FUNC3|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    
    /* ���� ʱ�� */
    CLOCK_EnableClock(kCLOCK_Iocon);
    
    switch(channel)
    {
      case  CT0Input0_P0_1:        
        IOCON_PinMuxSet(IOCON, 0, 1, PIOFun3_config);     
        break;     
      case  CT0Input0_P0_13:       
        IOCON_PinMuxSet(IOCON, 0,13, PIOFun3_config);
        break;  
	  case  CT0Input1_P0_14:       
        IOCON_PinMuxSet(IOCON, 0,14, PIOFun3_config);
        break;
	  case  CT0Input1_P0_2:       
        IOCON_PinMuxSet(IOCON, 0, 2, PIOFun2_config);
        break;
	  case  CT0Input2_P1_0:       
        IOCON_PinMuxSet(IOCON, 1, 0, PIOFun3_config);
        break;  
	  case  CT0Input2_P1_28:       
        IOCON_PinMuxSet(IOCON, 1,28, PIOFun3_config);
        break;
	  case  CT0Input3_P1_1:       
        IOCON_PinMuxSet(IOCON, 1,1,  PIOFun3_config);
        break;
	  case  CT0Input3_P1_26:       
        IOCON_PinMuxSet(IOCON, 1,26, PIOFun3_config);
        break;
	  
      case  CT1Input0_P1_9:       
        IOCON_PinMuxSet(IOCON, 1, 9, PIOFun3_config);
        break;      
      case  CT1Input0_P0_16:       
        IOCON_PinMuxSet(IOCON, 0,16, PIOFun3_config);
        break; 
	  case  CT1Input1_P1_11:       
        IOCON_PinMuxSet(IOCON, 1,11, PIOFun3_config);
        break;	  
      case  CT1Input2_P1_13:       
        IOCON_PinMuxSet(IOCON, 1,13, PIOFun3_config);
        break;      
      case  CT1Input3_P1_15:       
        IOCON_PinMuxSet(IOCON, 1,15, PIOFun3_config);
        break; 
	  
	  case  CT2Input0_P0_24:       
        IOCON_PinMuxSet(IOCON, 0,24, PIOFun3_config);
        break;
	  case  CT2Input1_P0_25:       
        IOCON_PinMuxSet(IOCON, 0,25, PIOFun3_config);
        break;
	  case  CT2Input2_P0_10:       
        IOCON_PinMuxSet(IOCON, 0,10, PIOFun2_config);
        break;
	  case  CT2Input3_P0_28:       
        IOCON_PinMuxSet(IOCON, 0,28, PIOFun3_config);
        break; 
	  
	  case  CT3Input0_P0_4:       
        IOCON_PinMuxSet(IOCON, 0, 4, PIOFun3_config);
        break;	
      case  CT3Input1_P0_6:       
        IOCON_PinMuxSet(IOCON, 0, 6, PIOFun2_config);
        break;	  
      case  CT3Input2_P1_20:       
        IOCON_PinMuxSet(IOCON, 1,20, PIOFun3_config);
        break;     
      case  CT3Input2_P0_26:       
        IOCON_PinMuxSet(IOCON, 0,26, PIOFun3_config);
        break;  
      case  CT3Input3_P0_20:       
        IOCON_PinMuxSet(IOCON, 0,20, PIOFun3_config);
        break; 
      case  CT3Input3_P0_22:       
        IOCON_PinMuxSet(IOCON, 0,22, PIOFun3_config);
        break;        
	  
      case  CT4Input0_P0_15:       
        IOCON_PinMuxSet(IOCON, 0,15, PIOFun3_config);
        break;
   
      default:
        break;
    }   

}

