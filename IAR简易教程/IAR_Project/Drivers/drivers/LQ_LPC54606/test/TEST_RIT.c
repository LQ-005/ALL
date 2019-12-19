/*!
  * @file     TEST_RIT.c
  *
  * @brief    RIT测试文件
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
#include "LQ_RIT.h"
#include "LQ_LED.h"
#include "TEST_RIT.h"

/*!
  * @brief    RIT定时器测试
  *
  * @param    无
  *
  * @return   无
  *
  * @note     示波器观察 P0_26   500Hz
  *
  * @example  Test_RIT();
  *
  * @date     2019/10/31 星期四
  */
void Test_RIT(void)
{
    /* 初始化 LED */
    LED_Init();
    
    /* 初始化 IO 在中断服务函数中反转 方便观察是否进入中断 */
    PIN_InitConfig(P0_26, PIN_MODE_OUTPUT, 0);
    
    /* 设置RIT定时器 1000us 触发一次中断 */
    RIT_InitConfig(1000);
    
    //优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级高的可打断抢占优先级低的中断
    NVIC_SetPriority(RIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(RIT_IRQn);  //使能中断
    
    /* 在irq.c中 编写中断服务函数*/
    while(1);

}
