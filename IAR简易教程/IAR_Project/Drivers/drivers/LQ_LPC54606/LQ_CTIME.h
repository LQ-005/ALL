/*!
  * @file     LQ_CTIME.h
  *
  * @brief    CTIME驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  修改记录   2019/12/11  优化CTIME通道结构体
  *           2019/12/11 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#ifndef __LQ_CTIME_H
#define __LQ_CTIME_H

#include "stdint.h"
#include "LQ_GPIO.h"

/*!  CTIMER 最大占空比 可自行修改 */
#define  CMTER_PWM_MAX    10000


/** 
  * @brief CTIMER模块 PWM输出通道 一个CT最多输出3路周期相同的PWM，四个通道中通道3用作周期通道
  * @note  CTIMER 用做PWM输出通道 一个CTIMER模块只能用作脉冲计数和PWM输出中的一种
  */ 
typedef enum  
{
    //CTIMER PWM通道 ，一行最多选一个（一个CT最多输出3路周期相同的PWM，四个通道中通道3用作周期通道）     
    CT0Output0_P0_0 = 1 + 0x0000, CT0Output0_P0_30 = 2 + 0x0000,  /*!< CTIME0 PWM输出通道0管脚  */    
    CT0Output1_P0_3 = 1 + 0x0100, CT0Output1_P0_31 = 2 + 0x0100,  /*!< CTIME0 PWM输出通道1管脚  */       
    CT0Output2_P0_19= 1 + 0x0200, CT0Output2_P1_31 = 2 + 0x0200,  /*!< CTIME0 PWM输出通道2管脚  */       
 
    CT1Output0_P0_18= 1 + 0x1000, CT1Output0_P1_10 = 2 + 0x1000,  /*!< CTIME1 PWM输出通道0管脚  */   
    CT1Output1_P0_20= 1 + 0x1100, CT1Output1_P1_12 = 2 + 0x1100,  /*!< CTIME1 PWM输出通道1管脚  */   
    CT1Output2_P0_23= 1 + 0x1200, CT1Output2_P1_14 = 2 + 0x1200,  /*!< CTIME1 PWM输出通道2管脚  */   

    CT2Output0_P0_10= 1 + 0x2000, CT2Output0_P1_5  = 2 + 0x2000,  /*!< CTIME2 PWM输出通道0管脚  */  
    CT2Output1_P1_6 = 1 + 0x2100, CT2Output1_P1_4  = 2 + 0x2100,  /*!< CTIME2 PWM输出通道1管脚  */  
    CT2Output2_P1_7 = 1 + 0x2200, CT2Output2_P0_11 = 2 + 0x2200,  /*!< CTIME2 PWM输出通道2管脚 P0_11（下载口）   */
    
    CT3Output0_P0_5 = 1 + 0x3000,                                 /*!< CTIME3 PWM输出通道0管脚  */
    CT3Output1_P1_19= 1 + 0x3100,                                 /*!< CTIME3 PWM输出通道1管脚  */
    CT3Output2_P0_27= 1 + 0x3200, CT3Output2_P1_21 = 2 + 0x3200,  /*!< CTIME3 PWM输出通道2管脚  */
    
    CT4Output0_P0_6= 1 + 0x4000,                                  /*!< CTIME4 PWM输出通道0管脚  */  
} CTIMER_OutputChannel_t;


/** 
  * @brief CTIMER模块 脉冲计数通道
  * @note  一个CTIMER 只能有一个通道用作脉冲计数 一个CTIMER模块只能用作脉冲计数和PWM输出中的一种
  */ 
typedef enum
{
    CT0Input0_P0_1  = 0x0000 + 1,  CT0Input0_P0_13 = 0x0000 + 2,     /*!< CTIMER0 输入通道0管脚  */  
    CT0Input1_P0_14 = 0x0100 + 1,  CT0Input1_P0_2  = 0x0100 + 2,     /*!< CTIMER0 输入通道1管脚  */  
    CT0Input2_P1_0  = 0x0200 + 1,  CT0Input2_P1_28 = 0x0200 + 2,     /*!< CTIMER0 输入通道2管脚  */  
    CT0Input3_P1_1  = 0x0300 + 1,  CT0Input3_P1_26 = 0x0300 + 2,     /*!< CTIMER0 输入通道3管脚  */  
	
    CT1Input0_P1_9  = 0x0400 + 1,  CT1Input0_P0_16 = 0x0400 + 2,     /*!< CTIMER1 输入通道0管脚  */  
    CT1Input1_P1_11 = 0x0500 + 1,                                    /*!< CTIMER1 输入通道1管脚  */  
    CT1Input2_P1_13 = 0x0600 + 1,                                    /*!< CTIMER1 输入通道2管脚  */  
    CT1Input3_P1_15 = 0x0700 + 1,                                    /*!< CTIMER1 输入通道3管脚  */  
	
    CT2Input0_P0_24 = 0x0800 + 1,                                    /*!< CTIMER2 输入通道0管脚  */  
    CT2Input1_P0_25 = 0x0900 + 1,                                    /*!< CTIMER2 输入通道1管脚  */  
    CT2Input2_P0_10 = 0x0A00 + 1,                                    /*!< CTIMER2 输入通道2管脚  */  
    CT2Input3_P0_28 = 0x0B00 + 1,                                    /*!< CTIMER2 输入通道3管脚  */
	                                                                    
    CT3Input0_P0_4 = 0x0C00 + 1,                                     /*!< CTIMER3 输入通道0管脚  */  
    CT3Input1_P0_6 = 0x0D00 + 1,                                     /*!< CTIMER3 输入通道1管脚  */  
    CT3Input2_P1_20= 0x0E00 + 1,  CT3Input2_P0_26= 0x0E00 + 2,       /*!< CTIMER3 输入通道2管脚  */  
    CT3Input3_P0_20= 0x0F00 + 1,  CT3Input3_P0_22= 0x0F00 + 2,       /*!< CTIMER4 输入通道3管脚  */ 
	
    CT4Input0_P0_15= 0x1000 + 1,                                     /*!< CTIMER4 输入通道0管脚  */  
    
} CTIMER_InputChannel_t;

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
void CTIMER_InitPwmConfig(CTIMER_OutputChannel_t matchChannel, uint32_t duty, uint32_t pwmFreq_Hz);



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
void CTIMER_SetDuty(CTIMER_OutputChannel_t matchChannel, uint32_t duty);



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
void CTIMER_InitCapConfig(CTIMER_Type *base, CTIMER_InputChannel_t channel);



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
int16_t CTIMER_GetCounter(CTIMER_Type *base, GPIO_Name_t pin);





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
void CTIME_PWMPinInit(CTIMER_OutputChannel_t CTn_CHn);



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
void CTIMER_CAPPinInit(CTIMER_InputChannel_t channel);




#endif
