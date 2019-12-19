/*!
  * @file     LQ_RIT.c
  *
  * @brief    RIT定时器驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/11 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "fsl_rit.h"
#include "LQ_RIT.h"


/*!
  * @brief    RIT定时器中断初始化
  *
  * @param    us  ： 定时时间
  *
  * @return   无
  *
  * @note     48位的定时器  最大计数 0xFFFFFFFFFFFF
  *
  * @see      RIT_InitConfig(5000); //5ms触发一次RIT中断
  * @see      优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级高的可打断抢占优先级低的中断
  * @see      NVIC_SetPriority(RIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
  * @see      EnableIRQ(RIT_IRQn);  //使能中断
  *
  * @date     2019/10/19 星期六
  */
void RIT_InitConfig(uint32_t us)
{
    /* 校准值  */
//    us += (us/500)+1;
    
    rit_config_t ritConfig;  
    
    RIT_GetDefaultConfig(&ritConfig); 
    
    RIT_Init(RIT, &ritConfig);        //RIT初始化
    RIT_SetTimerCompare(RIT, USEC_TO_COUNT(us, CLOCK_GetFreq(kCLOCK_CoreSysClk)));
    RIT_SetCountAutoClear(RIT, true); //周期计数
    RIT_ClearCounter(RIT, true);      //清零    
    RIT_StartTimer(RIT);               //使能  
    
}
