/*!
  * @file     LQ_ADC.c
  *
  * @brief    ADC�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_power.h"
#include "LQ_GPIO.h"
#include "LQ_ADC.h"


/** �ڲ����� ����ADC��ʼ�� */
static adc_conv_seq_config_t adcConvSeqConfigStruct;  



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
void ADC_InitConfig(ADCn_Ch channel, ADC_nbit bit)
{
    /* ADC��ʼ�����ýṹ�� */
    adc_config_t adcConfigStruct;

    /* �ر�ģ���Դ */
    POWER_DisablePD(kPDRUNCFG_PD_VDDA);    /* Power on VDDA. */
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);    /* Power on the ADC converter. */
    POWER_DisablePD(kPDRUNCFG_PD_VD2_ANA); /* Power on the analog power supply. */
    POWER_DisablePD(kPDRUNCFG_PD_VREFP);   /* Power on the reference voltage source. */
    
    /* ʹ��ADC ʱ�� */
    CLOCK_EnableClock(kCLOCK_Adc0); 
    
    /* ��ʼ�� IO */
    ADC_PinInit(channel);
    
    /* ADCУ׼ */
    if (!ADC_DoSelfCalibration(ADC0))
    {
        assert("У׼ʧ��!");
    }
    
    /* ѡ��ADCʱ��Դ */
    adcConfigStruct.clockMode = kADC_ClockSynchronousMode; /* Using sync clock source. */
    
    /* ����ADC����ϵ�� ADCʱ�Ӳ�Ҫ����80M*/
    adcConfigStruct.clockDividerNumber = 3;                /* The divider for sync clock is ?. */
    
    /* ����ADC�ֱ��� */
    adcConfigStruct.resolution =(adc_resolution_t)bit;
    adcConfigStruct.enableBypassCalibration = false;
    
    /* �������� */
    adcConfigStruct.sampleTimeNumber = 0U;
    
    /* ��ʼ��ADCģ�� */
    ADC_Init(ADC0, &adcConfigStruct);
    
    /* ʹ��ADCͨ��. */
    adcConvSeqConfigStruct.channelMask |= (1U << channel); 
    
    /* �������� */
    adcConvSeqConfigStruct.triggerMask = 0U;
    adcConvSeqConfigStruct.triggerPolarity = kADC_TriggerPolarityNegativeEdge;
    adcConvSeqConfigStruct.enableSingleStep = false;
    adcConvSeqConfigStruct.enableSyncBypass = false;
    adcConvSeqConfigStruct.interruptMode = kADC_InterruptForEachSequence;
    
    /* �������� A */
    ADC_SetConvSeqAConfig(ADC0, &adcConvSeqConfigStruct);
    
    /* ʹ������A */
    ADC_EnableConvSeqA(ADC0, true); 
    
    /* ����ת�� */
    ADC_DoSoftwareTriggerConvSeqA(ADC0);  
}


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
uint16_t ADC_Read(ADCn_Ch channel)
{
    adc_result_info_t adcResultInfoStruct;  
    
    /* ����ת�� */
    ADC_DoSoftwareTriggerConvSeqA(ADC0);  
    
    /* �ȴ�ת����� */
    while(!ADC_GetChannelConversionResult(ADC0, channel, &adcResultInfoStruct));
    
    return (adcResultInfoStruct.result);
}


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
uint16_t ADC_ReadMean(ADCn_Ch channel, uint8_t count)
{
    assert(count);
    
    uint32_t sum = 0;
    for(int i = 0; i < count; i++)
    {
        sum += ADC_Read(channel);
    }
    return sum/count;
}



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
void ADC_PinInit(ADCn_Ch channel)
{
    uint32_t temp = FUNC0|MODE_Diaable|MODE_GPIO|INVERT_Disable|DIGIMODE_Analog|FILTER_Disable;
    switch(channel)
    {
      case ADC0CH0_P0_10:
        PIN_MuxSet(P0_10, temp);
        break;
      case ADC0CH1_P0_11:
        PIN_MuxSet(P0_11, temp);
        break;
      case ADC0CH2_P0_12:
        PIN_MuxSet(P0_12, temp);
        break;
      case ADC0CH3_P0_15:
        PIN_MuxSet(P0_15, temp);
        break;
      case ADC0CH4_P0_16:
        PIN_MuxSet(P0_16, temp);
        break;
      case ADC0CH5_P0_31:
        PIN_MuxSet(P0_31, temp);
        break;
      case ADC0CH6_P1_0:
        PIN_MuxSet(P1_0, temp);
        break;
      case ADC0CH11_P0_23:
        PIN_MuxSet(P0_23, temp);
        break;
      default:
        assert(0);   //ADC�ܽ�ѡ������
    }
}
