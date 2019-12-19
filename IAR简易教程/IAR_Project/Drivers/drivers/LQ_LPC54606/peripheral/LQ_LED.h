/*!
  * @file     LQ_LED.h
  *
  * @brief    LED驱动文件
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
#ifndef __LQ_LED_H
#define __LQ_LED_H

#include "LQ_GPIO.h"

/** 
  * @brief RGB LED颜色枚举体
  */ 
typedef enum
{
  white = 0,  /*!<白色 */
  black = 1,  /*!<黑色 */
  red   = 2,  /*!<红   */
  green = 3,  /*!<绿   */
  blue  = 4,  /*!<蓝色 */
  yellow= 5,  /*!<黄色 */
  violet= 6,  /*!<紫色 */
  cyan  = 7,  /*!<青色 */
}LED_t;


/* LED管脚定义 */
#define LED_R_PIN       P0_8            /*!<  @brief    核心板RGB灯 R灯的Pin  */
                                        
#define LED_G_PIN       P0_9            /*!<  @brief    核心板RGB灯 G灯的Pin  */
                                        
#define LED_B_PIN       P1_12           /*!<  @brief    核心板RGB灯 B灯的Pin  */
                                        
#define LED_D0_PIN      P1_15           /*!<  @brief    母板灯 D0灯的Pin  */
                                        
#define LED_D1_PIN      P1_4            /*!<  @brief    母板灯 D1灯的Pin  */

/**
  * @brief    RGB灯引脚初始化
  *
  * @param    无
  *
  * @return   无
  *
  * @note     LED使用IO在LQ_LED.h中通过宏定义选择
  *
  * @see      LED_Init();  
  *
  * @date     2019/6/4 星期二
  */
void LED_Init(void);


/**
  * @brief    指定颜色的灯亮
  *
  * @param    color  ： 枚举LED_t中的颜色
  *
  * @return   无
  *
  * @note     使用前请先初始化
  *
  * @see      LED_Color(red);   //红灯亮
  *
  * @date     2019/6/4 星期二
  */
void LED_Color(LED_t color);




/**
  * @brief    指定颜色闪烁
  *
  * @param    color  ： 枚举LED_t中的颜色
  *
  * @return   无
  *
  * @note     无
  *
  * @see      LED_ColorReverse(red);
  *
  * @date     2019/6/4 星期二
  */
void LED_ColorReverse(LED_t color);


/**
  * @brief    测试LED灯
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  * 
  * @see  
  *
  * @date     2019/6/4 星期二
  */
void Test_LED(void);


#endif
