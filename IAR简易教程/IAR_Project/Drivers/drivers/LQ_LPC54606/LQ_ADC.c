/*!
  * @file     LQ_ADC.c
  *
  * @brief    ADC驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_power.h"
#include "LQ_GPIO.h"
#include "LQ_ADC.h"


/** 内部调用 用于ADC初始化 */
static adc_conv_seq_config_t adcConvSeqConfigStruct;  



/*!
  * @brief    ADC通道初始化
  *
  * @param    channel   ：  ADC通道 LQ_ADC.h中的一个枚举体  
  * @param    bit       ：  ADC通道精度 LQ_ADC.h中的一个枚举体  
  *
  * @return   无
  *
  * @note     读取ADC之前一定要调用该函数对ADC通道进行初始化
  *
  * @see      ADC_InitConfig(ADC0CH0_P0_10, ADC_12bit);  //初始化ADC通道0 P0_10
  *
  * @date     2019/10/21 星期一
  */
void ADC_InitConfig(ADCn_Ch channel, ADC_nbit bit)
{
    /* ADC初始化配置结构体 */
    adc_config_t adcConfigStruct;

    /* 关闭模块电源 */
    POWER_DisablePD(kPDRUNCFG_PD_VDDA);    /* Power on VDDA. */
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);    /* Power on the ADC converter. */
    POWER_DisablePD(kPDRUNCFG_PD_VD2_ANA); /* Power on the analog power supply. */
    POWER_DisablePD(kPDRUNCFG_PD_VREFP);   /* Power on the reference voltage source. */
    
    /* 使能ADC 时钟 */
    CLOCK_EnableClock(kCLOCK_Adc0); 
    
    /* 初始化 IO */
    ADC_PinInit(channel);
    
    /* ADC校准 */
    if (!ADC_DoSelfCalibration(ADC0))
    {
        assert("校准失败!");
    }
    
    /* 选择ADC时钟源 */
    adcConfigStruct.clockMode = kADC_ClockSynchronousMode; /* Using sync clock source. */
    
    /* 配置ADC分配系数 ADC时钟不要超过80M*/
    adcConfigStruct.clockDividerNumber = 3;                /* The divider for sync clock is ?. */
    
    /* 设置ADC分辨率 */
    adcConfigStruct.resolution =(adc_resolution_t)bit;
    adcConfigStruct.enableBypassCalibration = false;
    
    /* 采样周期 */
    adcConfigStruct.sampleTimeNumber = 0U;
    
    /* 初始化ADC模块 */
    ADC_Init(ADC0, &adcConfigStruct);
    
    /* 使能ADC通道. */
    adcConvSeqConfigStruct.channelMask |= (1U << channel); 
    
    /* 触发配置 */
    adcConvSeqConfigStruct.triggerMask = 0U;
    adcConvSeqConfigStruct.triggerPolarity = kADC_TriggerPolarityNegativeEdge;
    adcConvSeqConfigStruct.enableSingleStep = false;
    adcConvSeqConfigStruct.enableSyncBypass = false;
    adcConvSeqConfigStruct.interruptMode = kADC_InterruptForEachSequence;
    
    /* 配置序列 A */
    ADC_SetConvSeqAConfig(ADC0, &adcConvSeqConfigStruct);
    
    /* 使能序列A */
    ADC_EnableConvSeqA(ADC0, true); 
    
    /* 启动转换 */
    ADC_DoSoftwareTriggerConvSeqA(ADC0);  
}


/**
  * @brief    获取ADC的测量值
  *
  * @param    channel ：adc通道
  *
  * @return   测量值
  *
  * @note     使用前需要初始化ADC通道
  *
  * @see      ADC_Read(ADC0CH0_P0_10); //读取一次ADC值
  *
  * @date     2019/5/7 星期二
  */
uint16_t ADC_Read(ADCn_Ch channel)
{
    adc_result_info_t adcResultInfoStruct;  
    
    /* 启动转换 */
    ADC_DoSoftwareTriggerConvSeqA(ADC0);  
    
    /* 等待转换完成 */
    while(!ADC_GetChannelConversionResult(ADC0, channel, &adcResultInfoStruct));
    
    return (adcResultInfoStruct.result);
}


/*!
  * @brief    ADC读取多次 返回平均值
  *
  * @param    channel ：adc通道
  * @param    count   ：ADC读取次数
  *
  * @return   多次读取的平均值
  *
  * @note     使用前需要初始化ADC通道
  *
  * @see      ADC_ReadMean(ADC0CH0_P0_10, 10);  //读取P0_10 十次返回平均值
  *
  * @date     2019/9/30 星期一
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
  * @brief    IO复用为ADC
  *
  * @param    channel   ：  ADC通道 LQ_ADC.h中的一个枚举体
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      ADC_PinInit(ADC0CH0_P0_10);  //将ADC管脚配置为ADC模式
  *
  * @date     2019/10/21 星期一
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
        assert(0);   //ADC管脚选择有误
    }
}
