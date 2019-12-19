/*!
  * @file     TEST_WDOG.c
  *
  * @brief    看门狗测试
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
#include "fsl_wwdt.h"
#include "LQ_WDOG.h"
#include "LQ_LED.h"
#include "TEST_WDog.h"
/*!
  * @brief    测试看门狗
  *
  * @param    
  *
  * @return   
  *
  * @note     看门狗是一种防止程序跑飞的外设 需要定时喂狗 如果不喂狗则会导致单片机复位
  *
  * @example      
  *
  * @date     2019/10/31 星期四
  */
 void Test_WDOG(void)
 {
     LED_Init();
     WDOG_InitConfig(1, 2);
     
     // 优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级高的可打断抢占优先级低的中断
     NVIC_SetPriority(WDT_BOD_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
     EnableIRQ(WDT_BOD_IRQn);  //使能中断
     
     /* 喂狗 */
     WWDT_Refresh(WWDT);
     
     /* */
     while(1);
     
 }
