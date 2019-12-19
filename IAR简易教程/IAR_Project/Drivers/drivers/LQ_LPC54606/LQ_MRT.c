/*!
  * @file     LQ_MRT.c
  *
  * @brief    MRT定时器
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
#include "fsl_clock.h"
#include "LQ_MRT.h"


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
void MRT_InitConfig(mrt_chnl_t channel, uint32_t us)
{
    /* 校准值 */
//    us += (us/500)+1;
    
    uint32_t mrt_clock;
    
    /* MRT初始化结构体 */
    mrt_config_t mrtConfig;    
    
    /* 获取MRT时钟频率 */
    mrt_clock =CLOCK_GetFreq(kCLOCK_BusClk);
    
    /* 获取MRT初始化默认参数 */
    MRT_GetDefaultConfig(&mrtConfig);

    static uint8_t count = 0;
    
    /* 防止多次初始化 */
    if(count == 0)
    {
        count++;
        /* Init mrt module */
        MRT_Init(MRT0, &mrtConfig);
    }
    
    
    /* 设置通道模式 */
    MRT_SetupChannelMode(MRT0, channel, kMRT_RepeatMode);

    /* 使能中断 */
    MRT_EnableInterrupts(MRT0, channel, kMRT_TimerInterruptEnable);
    
    //微秒，ticksINTVAL最大值为0xFFFFFFU  
    MRT_StartTimer(MRT0, channel, USEC_TO_COUNT(us, mrt_clock));
    //毫秒
    //MRT_StartTimer(MRT0, channel, MSEC_TO_COUNT(250000U, mrt_clock));   
}

