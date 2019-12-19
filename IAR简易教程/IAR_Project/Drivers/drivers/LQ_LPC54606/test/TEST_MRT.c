/*!
  * @file     TEST_MRT.c
  *
  * @brief    MRT定时器测试
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
#include "LQ_MRT.h"
#include "LQ_LED.h"
#include "TEST_MRT.h"


/*!
  * @brief    测试MRT定时器
  *
  * @param    无
  *
  * @return   无
  *
  * @note     示波器测试 P0_26 P1_17 P0_28 P0_27 频率分别500Hz 100Hz 50Hz 10Hz
  *
  * @example      
  *
  * @date     2019/10/31 星期四
  */
void Test_MRT(void)
{
    /* 初始化 LED */
    LED_Init();
    
    /* 初始化 IO 在中断服务函数中反转 方便观察是否进入中断 */
    PIN_InitConfig(P0_26, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P1_17, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P0_28, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P0_27, PIN_MODE_OUTPUT, 0);
    
    /* 设置MRT定时器通道0 1000us触发一次中断 */
    MRT_InitConfig(kMRT_Channel_0, 1000);
    
    /* 设置MRT定时器通道0 5000us触发一次中断 */
    MRT_InitConfig(kMRT_Channel_1, 5000);
    
    /* 设置MRT定时器通道0 10000us触发一次中断 */
    MRT_InitConfig(kMRT_Channel_2, 10000);
    
    /* 设置MRT定时器通道0 50000us触发一次中断 */
    MRT_InitConfig(kMRT_Channel_3, 50000);
    
    //优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级高的可打断抢占优先级低的中断
    NVIC_SetPriority(MRT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(MRT0_IRQn);  //使能中断
    
    /* 在irq.c中 编写中断服务函数*/
    while(1);

}

