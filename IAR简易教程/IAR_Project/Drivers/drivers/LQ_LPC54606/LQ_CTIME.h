/*!
  * @file     LQ_CTIME.h
  *
  * @brief    CTIME�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  �޸ļ�¼   2019/12/11  �Ż�CTIMEͨ���ṹ��
  *           2019/12/11 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __LQ_CTIME_H
#define __LQ_CTIME_H

#include "stdint.h"
#include "LQ_GPIO.h"

/*!  CTIMER ���ռ�ձ� �������޸� */
#define  CMTER_PWM_MAX    10000


/** 
  * @brief CTIMERģ�� PWM���ͨ�� һ��CT������3·������ͬ��PWM���ĸ�ͨ����ͨ��3��������ͨ��
  * @note  CTIMER ����PWM���ͨ�� һ��CTIMERģ��ֻ���������������PWM����е�һ��
  */ 
typedef enum  
{
    //CTIMER PWMͨ�� ��һ�����ѡһ����һ��CT������3·������ͬ��PWM���ĸ�ͨ����ͨ��3��������ͨ����     
    CT0Output0_P0_0 = 1 + 0x0000, CT0Output0_P0_30 = 2 + 0x0000,  /*!< CTIME0 PWM���ͨ��0�ܽ�  */    
    CT0Output1_P0_3 = 1 + 0x0100, CT0Output1_P0_31 = 2 + 0x0100,  /*!< CTIME0 PWM���ͨ��1�ܽ�  */       
    CT0Output2_P0_19= 1 + 0x0200, CT0Output2_P1_31 = 2 + 0x0200,  /*!< CTIME0 PWM���ͨ��2�ܽ�  */       
 
    CT1Output0_P0_18= 1 + 0x1000, CT1Output0_P1_10 = 2 + 0x1000,  /*!< CTIME1 PWM���ͨ��0�ܽ�  */   
    CT1Output1_P0_20= 1 + 0x1100, CT1Output1_P1_12 = 2 + 0x1100,  /*!< CTIME1 PWM���ͨ��1�ܽ�  */   
    CT1Output2_P0_23= 1 + 0x1200, CT1Output2_P1_14 = 2 + 0x1200,  /*!< CTIME1 PWM���ͨ��2�ܽ�  */   

    CT2Output0_P0_10= 1 + 0x2000, CT2Output0_P1_5  = 2 + 0x2000,  /*!< CTIME2 PWM���ͨ��0�ܽ�  */  
    CT2Output1_P1_6 = 1 + 0x2100, CT2Output1_P1_4  = 2 + 0x2100,  /*!< CTIME2 PWM���ͨ��1�ܽ�  */  
    CT2Output2_P1_7 = 1 + 0x2200, CT2Output2_P0_11 = 2 + 0x2200,  /*!< CTIME2 PWM���ͨ��2�ܽ� P0_11�����ؿڣ�   */
    
    CT3Output0_P0_5 = 1 + 0x3000,                                 /*!< CTIME3 PWM���ͨ��0�ܽ�  */
    CT3Output1_P1_19= 1 + 0x3100,                                 /*!< CTIME3 PWM���ͨ��1�ܽ�  */
    CT3Output2_P0_27= 1 + 0x3200, CT3Output2_P1_21 = 2 + 0x3200,  /*!< CTIME3 PWM���ͨ��2�ܽ�  */
    
    CT4Output0_P0_6= 1 + 0x4000,                                  /*!< CTIME4 PWM���ͨ��0�ܽ�  */  
} CTIMER_OutputChannel_t;


/** 
  * @brief CTIMERģ�� �������ͨ��
  * @note  һ��CTIMER ֻ����һ��ͨ������������� һ��CTIMERģ��ֻ���������������PWM����е�һ��
  */ 
typedef enum
{
    CT0Input0_P0_1  = 0x0000 + 1,  CT0Input0_P0_13 = 0x0000 + 2,     /*!< CTIMER0 ����ͨ��0�ܽ�  */  
    CT0Input1_P0_14 = 0x0100 + 1,  CT0Input1_P0_2  = 0x0100 + 2,     /*!< CTIMER0 ����ͨ��1�ܽ�  */  
    CT0Input2_P1_0  = 0x0200 + 1,  CT0Input2_P1_28 = 0x0200 + 2,     /*!< CTIMER0 ����ͨ��2�ܽ�  */  
    CT0Input3_P1_1  = 0x0300 + 1,  CT0Input3_P1_26 = 0x0300 + 2,     /*!< CTIMER0 ����ͨ��3�ܽ�  */  
	
    CT1Input0_P1_9  = 0x0400 + 1,  CT1Input0_P0_16 = 0x0400 + 2,     /*!< CTIMER1 ����ͨ��0�ܽ�  */  
    CT1Input1_P1_11 = 0x0500 + 1,                                    /*!< CTIMER1 ����ͨ��1�ܽ�  */  
    CT1Input2_P1_13 = 0x0600 + 1,                                    /*!< CTIMER1 ����ͨ��2�ܽ�  */  
    CT1Input3_P1_15 = 0x0700 + 1,                                    /*!< CTIMER1 ����ͨ��3�ܽ�  */  
	
    CT2Input0_P0_24 = 0x0800 + 1,                                    /*!< CTIMER2 ����ͨ��0�ܽ�  */  
    CT2Input1_P0_25 = 0x0900 + 1,                                    /*!< CTIMER2 ����ͨ��1�ܽ�  */  
    CT2Input2_P0_10 = 0x0A00 + 1,                                    /*!< CTIMER2 ����ͨ��2�ܽ�  */  
    CT2Input3_P0_28 = 0x0B00 + 1,                                    /*!< CTIMER2 ����ͨ��3�ܽ�  */
	                                                                    
    CT3Input0_P0_4 = 0x0C00 + 1,                                     /*!< CTIMER3 ����ͨ��0�ܽ�  */  
    CT3Input1_P0_6 = 0x0D00 + 1,                                     /*!< CTIMER3 ����ͨ��1�ܽ�  */  
    CT3Input2_P1_20= 0x0E00 + 1,  CT3Input2_P0_26= 0x0E00 + 2,       /*!< CTIMER3 ����ͨ��2�ܽ�  */  
    CT3Input3_P0_20= 0x0F00 + 1,  CT3Input3_P0_22= 0x0F00 + 2,       /*!< CTIMER4 ����ͨ��3�ܽ�  */ 
	
    CT4Input0_P0_15= 0x1000 + 1,                                     /*!< CTIMER4 ����ͨ��0�ܽ�  */  
    
} CTIMER_InputChannel_t;

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
void CTIMER_InitPwmConfig(CTIMER_OutputChannel_t matchChannel, uint32_t duty, uint32_t pwmFreq_Hz);



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
void CTIMER_SetDuty(CTIMER_OutputChannel_t matchChannel, uint32_t duty);



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
void CTIMER_InitCapConfig(CTIMER_Type *base, CTIMER_InputChannel_t channel);



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
int16_t CTIMER_GetCounter(CTIMER_Type *base, GPIO_Name_t pin);





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
void CTIME_PWMPinInit(CTIMER_OutputChannel_t CTn_CHn);



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
void CTIMER_CAPPinInit(CTIMER_InputChannel_t channel);




#endif
