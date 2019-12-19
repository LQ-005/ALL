/*!
  * @file     LQ_SYSTICK.c
  *
  * @brief    systick驱动文件
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
#include "fsl_common.h"
#include "LQ_SYSTICK.h"

#define EACH_PER_MS    25   /*!<每隔 25 ms 中断一次  systick 定时器是24位向下计数的定时器  最大装载值16777215 */ 

/** 
  * @brief 一个时间结构体
  * @note  内部调用
  */
struct time{
	
    uint32_t fac_us;                  /*!<us分频系数         */
	uint32_t fac_ms;                  /*!<ms分频系数         */
	volatile uint32_t millisecond;    /*!<当前ms值           */
	uint8_t ms_per_tick;              /*!<每隔多少ms中断一次 */
	
}timer;



/*!
  * @brief    systime 初始化
  *
  * @param    无
  *
  * @return   无
  *
  * @note     默认优先级最低 可以修改
  *
  * @see      systime.init();  //初始化  
  *
  * @date     2019/6/10 星期一
  */
void systime_init(void)
{
	timer.fac_us = SystemCoreClock / 1000000;
	timer.fac_ms = SystemCoreClock / 1000;
	timer.ms_per_tick = EACH_PER_MS;
    timer.millisecond = 100;
	SysTick_Config((SystemCoreClock / 1000) * timer.ms_per_tick );   //开启systick中断
    
//    //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
//    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
}



/*!
  * @brief    systime 中断服务函数
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @see      无
  *
  * @date     2019/6/10 星期一
  */
void SysTick_Handler(void)
{
	timer.millisecond += timer.ms_per_tick;
}



/*!
  * @brief    获取当前时间
  *
  * @param    无
  *
  * @return   当前ms值
  *
  * @note     无
  *
  * @see      system.get_time_ms();  //获取当前ms值  
  *
  * @date     2019/6/10 星期一
  */
static inline uint32_t systime_get_current_time_ms(void)
{
    register uint32_t val, ms;
    do
    {
        ms  = timer.millisecond;
        val = SysTick->VAL; 
    }while(ms != timer.millisecond);
    
	return ms  -  val/timer.fac_ms;
}



/*!
  * @brief    获取当前时间
  *
  * @param    无
  *
  * @return   当前us值
  *
  * @note     无
  *
  * @see      system.get_time_us();  //获取当前ms值  
  *
  * @date     2019/6/10 星期一
  */
static inline uint32_t systime_get_current_time_us(void)
{
    register uint32_t val, ms;
    do
    {
        ms  = timer.millisecond;
        val = SysTick->VAL;
    }while(ms != timer.millisecond);
	return (uint32_t)((uint32_t)(ms * 1000) -  val / timer.fac_us);
}




/*!
  * @brief    systime 延时函数
  *
  * @param    us    ：延时时间
  *
  * @return   无
  *
  * @note     最大延时不要超过 4292s
  *
  * @see      system.delay_us(1000);  //延时1ms
  *
  * @date     2019/6/10 星期一
  */
void systime_delay_us(uint32_t us)     
{
    uint32_t now = systime.get_time_us();
	uint32_t end_time = now + us - 3;
	while( systime.get_time_us() <= end_time)
    {
        ;
    }
}



/*!
  * @brief    延时函数
  *
  * @param    ms :  延时时间
  *
  * @return   无
  *
  * @note     无 
  *
  * @see      system.delay_ms(1000);  //延时1s  
  *
  * @date     2019/6/10 星期一
  */
void systime_delay_ms(uint32_t ms) 
{
    while(ms--)
    {
        systime.delay_us(1000);
    }
	
}

/** 创建一个systck实例 */
systime_t  systime = 
{
	systime_init,
	systime_get_current_time_us,
	systime_get_current_time_ms,
	systime_delay_us,
	systime_delay_ms
};



