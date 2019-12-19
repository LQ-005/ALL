/*!
  * @file     LQ_CTIME.c
  *
  * @brief    CTIME驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     LPC54606有5个32位的CTIME
  *
  * @version  V1.1 
  *           修改记录   2019/11/13  CTIMER0 PWM通道1 P0_3 管脚复用功能应该是FUN2
  *           			 2019/12/11  优化注释 Doxygen
                         2019/12/11  优化IO初始化函数
  *
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "fsl_iocon.h"
#include "fsl_ctimer.h"
#include "LQ_CTIME.h"
#include "LQ_GPIO.h"



/*!
  * @brief    初始化CTIMER为PWM输出功能
  *
  * @param    matchChannel   ：    CTIMER通道  LQ_CTIMER.h中枚举体
  * @param    duty           ：    占空比 * CMTER_PWM_MAX
  * @param    pwmFreq_Hz     ：    频率
  *
  * @return   无
  *
  * @note     一个CTIMER模块只能用作脉冲计数和PWM输出的一种
  * @note     一个CTIMER模块最多只能输出3路PWM频率相同的PWM波
  *
  * @see      CTIMER_InitPwmConfig(CT0Output0_P0_0, 5000, 100);//初始化P0_0 作为CTIMER0的通道0 的PWM输出口 频率100Hz 占空比 百分之(5000/CMTER_PWM_MAX)*100
  *
  * @date     2019/5/7 星期二
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
		// Ctimer3、4使用12 MHz时钟
		CLOCK_AttachClk(kFRO12M_to_ASYNC_APB);
		
		pwmFreq_Hz = (CLOCK_GetFreq(kCLOCK_AsyncApbClk) / pwmFreq_Hz) - 1; 
	}     
	else   
	{
		pwmFreq_Hz = (CLOCK_GetFreq(kCLOCK_BusClk) / pwmFreq_Hz) - 1;//BUSCLK=180M时钟 
	}
	
	if (channel_temp == kCTIMER_Match_3)
	{
		return ;
	}
	/* 防止重复初始化 */
	if(flag[index] < 1)
	{
		flag[index]++;
		/* 初始化 CTIMER */
		CTIMER_GetDefaultConfig(&cconfig);
		CTIMER_Init(base, &cconfig); 
	}

	/* 初始化对应管脚 */
	CTIME_PWMPinInit(matchChannel);
	
	/* 使能PWM模式 */
	base->PWMC |= (1U << (channel_temp));
	
	/* 清除标志位 */
	reg = base->MCR;
	reg &= ~((CTIMER_MCR_MR0R_MASK | CTIMER_MCR_MR0S_MASK | CTIMER_MCR_MR0I_MASK) << ((channel_temp) * 3));
	
	/* 设置周期通道  */
	reg |= CTIMER_MCR_MR3R_MASK;
	
	base->MCR = reg;  
	
	/* 配置PWM频率 */
	base->MR[kCTIMER_Match_3] = pwmFreq_Hz;
	
	/* 配置占空比 */
	base->MR[channel_temp] = (uint32_t)(pwmFreq_Hz * ((float)(CMTER_PWM_MAX - duty)/CMTER_PWM_MAX)); 
	
	/* 清除标志位 */
	CTIMER_ClearStatusFlags(base, CTIMER_IR_MR0INT_MASK << channel_temp);
	
	CTIMER_StartTimer(base);
	return;
}



/*!
  * @brief    CTIMER 更新PWM占空比
  *
  * @param    matchChannel   ：    CTIMER通道
  * @param    duty           ：    占空比 * CMTER_PWM_MAX
  *
  * @return   无
  *
  * @note     使用前请先初始化对应通道
  *
  * @see      CTIMER_SetDuty(CT0Output0_P0_0, 4000); //设置P0_0 通道 PWM占空比 百分之 百分之(4000/CMTER_PWM_MAX)*100 
  *
  * @date     2019/5/7 星期二
  */
void CTIMER_SetDuty(CTIMER_OutputChannel_t matchChannel, uint32_t duty)
{ 
    CTIMER_Type     * TIMERN[] = CTIMER_BASE_PTRS;
    CTIMER_Type     * base = TIMERN[matchChannel >> 12];
    
    uint32_t pulsePeriod = 0, period;

    /* 获取周期 */
    period = base->MR[kCTIMER_Match_3];

    if (duty == 0)
    {
        pulsePeriod = period + 1;
    }
    else
    {
        pulsePeriod = (uint32_t)(period * ((float)(CMTER_PWM_MAX - duty)/CMTER_PWM_MAX));
    }

    /* 更新占空比 */
    base->MR[((matchChannel&0x0F00)>>8)] = pulsePeriod;
}

/*!
  * @brief    初始化CTIMER 作为脉冲计数功能
  *
  * @param    base     ： CTIMER0 - CTIMER4
  * @param    channel  ： 输入脉冲计数通道
  *
  * @return   无
  *
  * @note     LPC只能用带方向编码器  
  *
  * @see      CTIMER_InitCapConfig(CTIMER0, CT0Input0_P0_1);//初始化CTIMER0 为脉冲捕获功能 使用P0_1管脚捕获脉冲
  *
  * @date     2019/10/21 星期一
  */
void CTIMER_InitCapConfig(CTIMER_Type *base, CTIMER_InputChannel_t channel)
{
  
    CTIMER_CAPPinInit(channel);
    
    ctimer_config_t CTimerConfigStruct;
    
    // 配置CTimer为输入捕捉模式、计数器模式，下降沿捕捉 
    CTimerConfigStruct.mode = kCTIMER_IncreaseOnFallEdge;
    CTimerConfigStruct.input= (ctimer_capture_channel_t)((channel>>8)&0x000f);  
    CTimerConfigStruct.prescale = 0U; // 设置分频因子 

    CTIMER_Init(base, &CTimerConfigStruct);
    CTIMER_StartTimer(base);
}


/*!
  * @brief    CTIMER 得到计数值
  *
  * @param    base        ： CTIMER0 - CTIMER4
  * @param    pin         ： 方向管脚 DIR
  *
  * @return   脉冲计数值
  *
  * @note     使用前需要对CTMIE初始化 方向管脚也需要初始化
  *
  * @see      CTIMER_GetCounter(CTIMER0, P1_11); //获取CTIMER0脉冲计数值 P1_11接编码器方向管脚（DIR）
  *
  * @date     2019/5/7 星期二
  */
int16_t CTIMER_GetCounter(CTIMER_Type *base, GPIO_Name_t pin)
{          
    /* 获取脉冲计数值 */
    int16_t temp = CTIMER_GetTimerCountValue(base);
    
    /* 清除对应计数器 */
    CTIMER_Reset(base);
    
    if(PIN_Read(pin) == 0)
        return -temp;
    else
        return temp;
    
}






/*!
  * @brief    CTIMER PWM输出管脚初始化
  *
  * @param    CTn_CHn  : PWM通道
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      CTIME_PWMPinInit(CT0Output0_P0_0); //初始化P0_0 为CTIMER0 的通道0
  *
  * @date     2019/10/21 星期一
  */
void CTIME_PWMPinInit(CTIMER_OutputChannel_t CTn_CHn)
{    
    uint32_t PIOFun2_config = FUNC2|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun3_config = FUNC3|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun4_config = FUNC4|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    
    /* 开启 时钟 */
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
  * @brief    CTIMER 脉冲计数管脚初始化
  *
  * @param    channel  ： 脉冲捕获通道
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      CTIMER_CAPPinInit(CT0Input0_P0_1); //初始化P0_1 管脚复用为CTIMER输入管教
  * 
  * @date     2019/10/21 星期一
  */
void CTIMER_CAPPinInit(CTIMER_InputChannel_t channel)
{
    uint32_t PIOFun2_config = FUNC2|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun3_config = FUNC3|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    
    /* 开启 时钟 */
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

