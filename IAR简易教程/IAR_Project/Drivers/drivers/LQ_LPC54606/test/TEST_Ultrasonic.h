/*!
  * @file     TEST_ULTRASONIC.h
  *
  * @brief    超声波测试
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 星期六
  */ 
#ifndef __TEST_ULTRASONIC_H
#define __TEST_ULTRASONIC_H
#include "LQ_GPIO.h"

/*! 超声波管脚 */
#define HCSR04_TRIG   P0_7
#define HCSR04_ECHO   P1_13

/**  hc_starttime 记录超声波测距ECHO 高电平开始时间  hc_time 记录ECHO高电平持续时间 */
extern volatile uint32_t hc_starttime; 
extern volatile uint16_t hc_time;

/*!
  * @brief    测试超声波模块
  *
  * @param    
  *
  * @return   
  *
  * @note     中断方式 超声波HCSR04_TRIG管脚置高电平15us左右，
  *           超声波模块会发射超声波 同时HCSR04_ECHO管脚置为高电平 
  *           当收到超声波反射信号时HCSR04_ECHO管脚变成低电平 
  *           记录HCSR04_ECHO管脚高电平时间 通过声速就可以计算出距离
  *
  * @example  Test_HCSR04(); //普通等待方式  测距会花费比较长的时间
  *
  * @date     2019/10/9 星期三
  */
void Test_HCSR04(void);



/*!
  * @brief    测试超声波模块
  *
  * @param    
  *
  * @return   
  *
  * @note     中断方式 超声波HCSR04_TRIG管脚置高电平15us左右，
  *           超声波模块会发射超声波 同时HCSR04_ECHO管脚置为高电平 
  *           当收到超声波反射信号时HCSR04_ECHO管脚变成低电平 
  *           记录HCSR04_ECHO管脚高电平时间 通过声速就可以计算出距离
  *
  * @example  Test_HCSR(); //在irq.c中断中记录时间
  *
  * @date     2019/10/9 星期三
  */
void Test_HCSR(void);

#endif
