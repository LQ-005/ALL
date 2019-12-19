/*!
  * @file     LQ_SCTIME.h
  *
  * @brief    SCT驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1 
  *           修改记录   2019/11/13  SCTIMER0 函数入口参数结构体
  *           			 2019/12/11  优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#ifndef __LQ_SCTIME_H
#define __LQ_SCTIME_H

#include "LQ_GPIO.h"


/** 
  * @brief SCT0模块 输入7通道 
  */ 
typedef enum
{
    SctInput0_P0_0 = 0x0000 + 1,  SctInput0_P1_5 = 0x0000 + 2, SctInput0_P0_24= 0x0000 + 3, SctInput0_P0_13= 0x0000 + 4,
    SctInput1_P0_1 = 0x0100 + 1,  SctInput1_P0_14= 0x0100 + 2, SctInput1_P0_25= 0x0100 + 3,
    SctInput2_P0_2 = 0x0200 + 1,  SctInput2_P0_20= 0x0200 + 2,
    SctInput3_P0_3 = 0x0300 + 1,  SctInput3_P0_21= 0x0300 + 2, SctInput3_P1_6 = 0x0300 + 3,
    SctInput4_P0_4 = 0x0400 + 1,  SctInput4_P1_0 = 0x0400 + 2, SctInput4_P1_7 = 0x0400 + 3,
    SctInput5_P0_5 = 0x0500 + 1,  SctInput5_P1_1 = 0x0500 + 2, SctInput5_P1_22= 0x0500 + 3,
    SctInput6_P0_6 = 0x0600 + 1,  SctInput6_P1_29= 0x0600 + 2, SctInput6_P1_2 = 0x0600 + 3,
    SctInput7_P0_17= 0x0700 + 1,  SctInput7_P0_12= 0x0700 + 2, SctInput7_P1_19= 0x0700 + 3, SctInput7_P1_30= 0x0700 + 4,   
}SCT0_InputChannel_t;


 
/** 
  * @brief SCT0模块 输出通道 
  */
typedef enum  
{
    //SCT0通道     管脚  可选管脚 完整2019      
    SctOutPut0_P0_2 = 0x0000 + 1, SctOutPut0_P0_17= 0x0000 + 2, SctOutPut0_P1_4 = 0x0000 + 3, SctOutPut0_P1_23= 0x0000 + 4, 
    SctOutPut1_P0_3 = 0x0100 + 1, SctOutPut1_P0_18= 0x0100 + 2, SctOutPut1_P1_8 = 0x0100 + 3, SctOutPut1_P1_24= 0x0100 + 4, 
    SctOutPut2_P0_15= 0x0200 + 1, SctOutPut2_P0_19= 0x0200 + 2, SctOutPut2_P1_9 = 0x0200 + 3, SctOutPut2_P1_25= 0x0200 + 4, 
    SctOutPut3_P0_22= 0x0300 + 1, SctOutPut3_P0_31= 0x0300 + 2, SctOutPut3_P1_10= 0x0300 + 3, SctOutPut3_P1_26= 0x0300 + 4, 
    SctOutPut4_P0_23= 0x0400 + 1, SctOutPut4_P1_3 = 0x0400 + 2, SctOutPut4_P1_17= 0x0400 + 3, 
    SctOutPut5_P0_26= 0x0500 + 1, SctOutPut5_P1_18= 0x0500 + 2, 
    SctOutPut6_P0_27= 0x0600 + 1, SctOutPut6_P1_31= 0x0600 + 2,
    SctOutPut7_P0_28= 0x0700 + 1, SctOutPut7_P1_19= 0x0700 + 2,
    SctOutPut8_P0_29= 0x0800 + 1, 
    SctOutPut9_P0_30= 0x0900 + 1, 
} SCT0_OutChnannel_t;



#define SCT_PWM_MAX                  10000     /*!< PWM占空比输出最大值 */
#define PWM_SCT_EVENT_PERIOD         9         /*!< 定义周期事件（一共10个事件0-9）,用于确定输出PWM的周期值。*/
#define CAMERA_SCT_EVENT_PCLK        8         /*!< 摄像头PCLK能触发DMA的事件（一共10个事件0-9） */


/*!
  * @brief    SCT 输出PWM初始化
  *
  * @param    channel    ： SCT通道  LQ_SCTIME.h 中可的枚举体
  * @param    frequency  ： 频率  注意SCT输出的PWM频率必须一样
  * @param    duty       ： 占空比百分之 duty/SCT_PWM_MAX *100  
  *
  * @return   无
  *
  * @note     SCT最多10个事件，其中一个事件用于PWM周期，其他九个事件可以产生9路频率相同的PWM
  * @note     但是摄像头也需要用到SCT的事件，如果使用神眼带与非门的转接座（白色），需要一个输入事件接摄像头像素同步信号触发DMA，最多就只能输出8路PWM
  * @note     如果使用神眼老板转接座或者OV7725，就需要更多的输入事件 不可以驱动8路PWM了。
  *
  * @see      SCT_InitPwmConfig(SctOutPut0_P0_2, 18000, 500); //设置通道0 P0_2输出频率 18000 占空比百分之 500/SCT_PWM_MAX *100
  *
  * @date     2019/10/21 星期一
  */
void SCT_InitPwmConfig(SCT0_OutChnannel_t channel, uint32_t frequency, uint32_t duty);



/**
  * @brief    SCT 设置PWM占空比
  *
  * @param    channel    ： SCT通道  LQ_SCTIME.h 中的枚举体
  * @param    duty       ： 占空比百分之 duty/SCT_PWM_MAX *100
  *
  * @return   无
  *
  * @note     使用前需要初始化
  *
  * @example  SCT_PwmSetDuty(SctOutPut0_P0_2, 500);  //设置通道0 P0_2输出占空比百分之 500/SCT_PWM_MAX *100
  *
  * @date     2019/5/8 星期三
  */
void SCT_PwmSetDuty(SCT0_OutChnannel_t channel, uint32_t duty);




/*!
  * @brief    SCT 输入管脚触发DMA初始化
  *
  * @param    channel  :  SCT输入通道  LQ_SCTIME.h 中的枚举体
  *
  * @return   无
  *
  * @note     SCT最多10个事件，其中一个事件用于PWM周期，其他九个事件可以产生9路频率相同的PWM
  * @note     但是摄像头也需要用到SCT的事件，如果使用神眼带与非门的转接座，需要一个输入事件接摄像头像素同步信号触发DMA，最多就只能输出8路PWM
  * @note     如果使用神眼老板转接座或者OV7725，就不可以驱动8路PWM了。   
  *
  * @see      SCT_InitCameraConfig(SctInput0_P0_0);  //设置输入通道0 P0_0作为摄像头pclk接口
  *
  * @date     2019/10/22 星期二
  */
void SCT_InitCameraConfig(SCT0_InputChannel_t channel);


/*!
  * @brief    SCT 输入引脚配置
  *
  * @param    channel  : SCT输入通道
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      SCT_CapPinInit(SctInput0_P1_5);  //初始化P1_5 功能复用为SCT输入
  *
  * @date     2019/5/8 星期三
  */
void SCT_CapPinInit(SCT0_InputChannel_t channel);


/*!
  * @brief    SCT PWM输出引脚配置
  *
  * @param    SCT0_Chn  : PWM输出通道
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      SCT_PwmPinInit(SctOutPut0_P0_2); //初始化 P0_2 功能复用为SCT输出
  *
  * @date     2019/5/8 星期三
  */
void SCT_PwmPinInit(SCT0_OutChnannel_t SCT0_Chn);

#endif
