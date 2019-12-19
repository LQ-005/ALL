/*!
  * @file     LQ_WDOG.h
  *
  * @brief    看门狗驱动文件
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
#ifndef __LQ_WDOG_H
#define __LQ_WDOG_H

#include "stdint.h"

/*!
  * @brief    看门狗初始化
  *
  * @param    min_s    ：窗口下限时间 单位 s
  * @param    max_s    ：窗口上限时间 单位 s
  *
  * @return   无
  *
  * @note     无
  *
  * @see      WDOG_InitConfig(2, 5); //设置看门狗 在2-5S内喂狗
  * @see      优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级高的可打断抢占优先级低的中断
  * @see      NVIC_SetPriority(WDT_BOD_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
  * @see      EnableIRQ(WDT_BOD_IRQn);  //使能中断
  *
  * @date     2019/10/19 星期六
  */
void WDOG_InitConfig(uint8_t min_s, uint8_t max_s);





#endif
