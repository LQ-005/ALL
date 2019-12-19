/*!
  * @file     LQ_ADC.h
  *
  * @brief    ADC�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __LQ_ADC_H
#define __LQ_ADC_H
#include "stdint.h"



/** 
  * @brief ADCͨ��
  */ 
typedef enum  //ADCģ��
{
    //ADCͨ�� �ܽŹ�ϵ        LQ_546XXP100SYS       
    ADC0CH0_P0_10=0,     /*!< P0_10    ����                  */              
    ADC0CH1_P0_11=1,     /*!< P0_11    ���ã�SWD�������ڣ�   */
    ADC0CH2_P0_12=2,     /*!< P0_12    ���ã�SWD�������ڣ�   */
    ADC0CH3_P0_15=3,     /*!< P0_15    ����                  */
    ADC0CH4_P0_16=4,     /*!< P0_16    ����                  */
    ADC0CH5_P0_31=5,     /*!< P0_31    ����                  */
    ADC0CH6_P1_0=6,      /*!< P1_0     ����                  */     
    ADC0CH11_P0_23=11,   /*!< P0_23    ����                  */ 
} ADCn_Ch;


/** 
  * @brief ADC����
  */
typedef enum ADC_nbit
{
    ADC_8bit   = 0x01,    /*!< �ֱ��� 8λ                  */       
    ADC_10bit  = 0x02,    /*!< �ֱ��� 10λ                 */     
    ADC_12bit  = 0x03,    /*!< �ֱ��� 16λ                 */     
} ADC_nbit;

/*!
  * @brief    ADCͨ����ʼ��
  *
  * @param    channel   ��  ADCͨ�� LQ_ADC.h�е�һ��ö����  
  * @param    bit       ��  ADCͨ������ LQ_ADC.h�е�һ��ö����  
  *
  * @return   ��
  *
  * @note     ��ȡADC֮ǰһ��Ҫ���øú�����ADCͨ�����г�ʼ��
  *
  * @see      ADC_InitConfig(ADC0CH0_P0_10, ADC_12bit);  //��ʼ��ADCͨ��0 P0_10
  *
  * @date     2019/10/21 ����һ
  */
void ADC_InitConfig(ADCn_Ch channel, ADC_nbit bit);


/**
  * @brief    ��ȡADC�Ĳ���ֵ
  *
  * @param    channel ��adcͨ��
  *
  * @return   ����ֵ
  *
  * @note     ʹ��ǰ��Ҫ��ʼ��ADCͨ��
  *
  * @see      ADC_Read(ADC0CH0_P0_10); //��ȡһ��ADCֵ
  *
  * @date     2019/5/7 ���ڶ�
  */
uint16_t ADC_Read(ADCn_Ch channel);


/*!
  * @brief    ADC��ȡ��� ����ƽ��ֵ
  *
  * @param    channel ��adcͨ��
  * @param    count   ��ADC��ȡ����
  *
  * @return   ��ζ�ȡ��ƽ��ֵ
  *
  * @note     ʹ��ǰ��Ҫ��ʼ��ADCͨ��
  *
  * @see      ADC_ReadMean(ADC0CH0_P0_10, 10);  //��ȡP0_10 ʮ�η���ƽ��ֵ
  *
  * @date     2019/9/30 ����һ
  */
uint16_t ADC_ReadMean(ADCn_Ch channel, uint8_t count);



/*!
  * @brief    IO����ΪADC
  *
  * @param    channel   ��  ADCͨ�� LQ_ADC.h�е�һ��ö����
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      ADC_PinInit(ADC0CH0_P0_10);  //��ADC�ܽ�����ΪADCģʽ
  *
  * @date     2019/10/21 ����һ
  */
void ADC_PinInit(ADCn_Ch channel);

#endif


