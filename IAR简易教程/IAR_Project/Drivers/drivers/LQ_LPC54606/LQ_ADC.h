/*!
  * @file     LQ_ADC.h
  *
  * @brief    ADC驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#ifndef __LQ_ADC_H
#define __LQ_ADC_H
#include "stdint.h"



/** 
  * @brief ADC通道
  */ 
typedef enum  //ADC模块
{
    //ADC通道 管脚关系        LQ_546XXP100SYS       
    ADC0CH0_P0_10=0,     /*!< P0_10    可用                  */              
    ADC0CH1_P0_11=1,     /*!< P0_11    可用（SWD下载器口）   */
    ADC0CH2_P0_12=2,     /*!< P0_12    可用（SWD下载器口）   */
    ADC0CH3_P0_15=3,     /*!< P0_15    可用                  */
    ADC0CH4_P0_16=4,     /*!< P0_16    可用                  */
    ADC0CH5_P0_31=5,     /*!< P0_31    可用                  */
    ADC0CH6_P1_0=6,      /*!< P1_0     可用                  */     
    ADC0CH11_P0_23=11,   /*!< P0_23    可用                  */ 
} ADCn_Ch;


/** 
  * @brief ADC精度
  */
typedef enum ADC_nbit
{
    ADC_8bit   = 0x01,    /*!< 分辨率 8位                  */       
    ADC_10bit  = 0x02,    /*!< 分辨率 10位                 */     
    ADC_12bit  = 0x03,    /*!< 分辨率 16位                 */     
} ADC_nbit;

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
void ADC_InitConfig(ADCn_Ch channel, ADC_nbit bit);


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
uint16_t ADC_Read(ADCn_Ch channel);


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
uint16_t ADC_ReadMean(ADCn_Ch channel, uint8_t count);



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
void ADC_PinInit(ADCn_Ch channel);

#endif


