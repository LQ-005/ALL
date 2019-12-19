/*!
  * @file     main.c
  *
  * @brief    
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.0
  *
  * @Software IAR8.22 or MDK5.25
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 星期六
  */ 
#include "include.h"

/* 中断优先级组 */
#define NVIC_Group0   0x07
#define NVIC_Group1   0x06
#define NVIC_Group2   0x05
#define NVIC_Group3   0x04


/**
  * @brief    不精确延时
  *
  * @param    无
  *
  * @return   无
  *
  * @note     LPC54606 有32KB的I&D SRAM  相比普通的SRAM速度快很多 
  * @note     在分散加载文件里 默认将32K的I&D SRAM分成16K的栈区和16K的RamFunction
  * @note     可以使用RAMFUNCTION_SECTION_CODE()将关键部分代码放到I&D SRAM里面加速
  * @note     这里只是做一个示例用的 
  *
  * @example  delayms(100);
  *
  * @date     2019/4/22 星期一
*/
RAMFUNCTION_SECTION_CODE(void delayms(uint16_t ms))
{
	volatile uint32_t i = 0;
	while(ms--)
	{
		for (i = 0; i < 15000; ++i)
		{
			__asm("NOP"); /* delay */
		}
	}	
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* 初始化板子时钟 180M */
    BOARD_BootClockPLL180M();
    
    /* 初始化串口0 可以使用 PRINTF函数 */
    BOARD_InitDebugConsole();

    
    /*设置中断优先级组  0: 0个抢占优先级 8个子优先级 
     *                  1: 2个抢占优先级 4个子优先级 
	 *		            2: 4个抢占优先级 2个子优先级 
     *                  3: 8个抢占优先级 0个子优先级 
     */
	/* 配置优先级分组 3: 8个抢占优先级 0-7  0优先级最高 */
    NVIC_SetPriorityGrouping(NVIC_Group3);
    
    /*!
      * @brief   一个例子工程  用户可以基于这个工程修改
      *
      *          
      *          
      * @note    在config.h中 选择显示的屏幕   
      */ 
    Test_LED();
    while(1)
    {

    }
}
