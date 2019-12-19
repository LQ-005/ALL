/*!
  * @file     LQ_SYSTICK.c
  *
  * @brief    systick�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "fsl_common.h"
#include "LQ_SYSTICK.h"

#define EACH_PER_MS    25   /*!<ÿ�� 25 ms �ж�һ��  systick ��ʱ����24λ���¼����Ķ�ʱ��  ���װ��ֵ16777215 */ 

/** 
  * @brief һ��ʱ��ṹ��
  * @note  �ڲ�����
  */
struct time{
	
    uint32_t fac_us;                  /*!<us��Ƶϵ��         */
	uint32_t fac_ms;                  /*!<ms��Ƶϵ��         */
	volatile uint32_t millisecond;    /*!<��ǰmsֵ           */
	uint8_t ms_per_tick;              /*!<ÿ������ms�ж�һ�� */
	
}timer;



/*!
  * @brief    systime ��ʼ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     Ĭ�����ȼ���� �����޸�
  *
  * @see      systime.init();  //��ʼ��  
  *
  * @date     2019/6/10 ����һ
  */
void systime_init(void)
{
	timer.fac_us = SystemCoreClock / 1000000;
	timer.fac_ms = SystemCoreClock / 1000;
	timer.ms_per_tick = EACH_PER_MS;
    timer.millisecond = 100;
	SysTick_Config((SystemCoreClock / 1000) * timer.ms_per_tick );   //����systick�ж�
    
//    //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
//    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
}



/*!
  * @brief    systime �жϷ�����
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      ��
  *
  * @date     2019/6/10 ����һ
  */
void SysTick_Handler(void)
{
	timer.millisecond += timer.ms_per_tick;
}



/*!
  * @brief    ��ȡ��ǰʱ��
  *
  * @param    ��
  *
  * @return   ��ǰmsֵ
  *
  * @note     ��
  *
  * @see      system.get_time_ms();  //��ȡ��ǰmsֵ  
  *
  * @date     2019/6/10 ����һ
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
  * @brief    ��ȡ��ǰʱ��
  *
  * @param    ��
  *
  * @return   ��ǰusֵ
  *
  * @note     ��
  *
  * @see      system.get_time_us();  //��ȡ��ǰmsֵ  
  *
  * @date     2019/6/10 ����һ
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
  * @brief    systime ��ʱ����
  *
  * @param    us    ����ʱʱ��
  *
  * @return   ��
  *
  * @note     �����ʱ��Ҫ���� 4292s
  *
  * @see      system.delay_us(1000);  //��ʱ1ms
  *
  * @date     2019/6/10 ����һ
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
  * @brief    ��ʱ����
  *
  * @param    ms :  ��ʱʱ��
  *
  * @return   ��
  *
  * @note     �� 
  *
  * @see      system.delay_ms(1000);  //��ʱ1s  
  *
  * @date     2019/6/10 ����һ
  */
void systime_delay_ms(uint32_t ms) 
{
    while(ms--)
    {
        systime.delay_us(1000);
    }
	
}

/** ����һ��systckʵ�� */
systime_t  systime = 
{
	systime_init,
	systime_get_current_time_us,
	systime_get_current_time_ms,
	systime_delay_us,
	systime_delay_ms
};



