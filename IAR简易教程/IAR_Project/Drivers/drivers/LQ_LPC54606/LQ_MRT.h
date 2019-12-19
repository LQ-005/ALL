/*!
  * @file     LQ_MRT.h
  *
  * @brief    MRT定时器驱动
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     MRT最大计数 0XFFFFFF
  *
  * @version  V1.1  2019/12/11 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#ifndef __LQ_MRT_H
#define __LQ_MRT_H


#include "fsl_mrt.h"

/**
  * @brief    MRT定时中断初始化
  *
  * @param    channel ： MRT通道 kMRT_Channel_0 - kMRT_Channel_3
  * @param    us      ： 定时中断时间
  *
  * @return   无
  *
  * @note     MRT最大 0XFFFFFF  最大计时90ms   
  *
  * @see      MRT_InitConfig(kMRT_Channel_0, 5000); //5ms触发一次MRT中断
  * @see      优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级高的可打断抢占优先级低的中断
  * @see      NVIC_SetPriority(MRT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
  * @see      EnableIRQ(MRT0_IRQn);  //使能中断
  *
  * @date     2019/5/6 星期一
  */
void MRT_InitConfig(mrt_chnl_t channel, uint32_t us);




#endif
