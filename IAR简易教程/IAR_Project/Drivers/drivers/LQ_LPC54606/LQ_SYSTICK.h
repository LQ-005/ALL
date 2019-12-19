/*!
  * @file     LQ_SYSTICK.h
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
#ifndef __LQ_SYSTICK_H
#define __LQ_SYSTICK_H
#include "fsl_common.h"

/** 
  * @brief 一个系统时间结构体
  */
typedef struct
{	
	void (* init) (void);  
	uint32_t (* get_time_us) (void);
	uint32_t (* get_time_ms) (void);
	void (* delay_us)(uint32_t);
	void (* delay_ms)(uint32_t);
}systime_t;

/** 声明 systime */
extern systime_t  systime;



#endif //__LQ_SYSTICK_H




