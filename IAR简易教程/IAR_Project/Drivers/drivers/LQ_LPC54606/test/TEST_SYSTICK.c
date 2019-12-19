/*!
  * @file     TEST_SYSTICK.c
  *
  * @brief    systick测试文件
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
#include "LQ_LED.h"
#include "LQ_SYSTICK.h"
#include "TEST_SYSTICK.h"

/**
  * @brief    测试systime 计时器
  *
  * @param    
  *
  * @return   
  *
  * @note     示波器 LED_R_PIN   500Hz翻转
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void Test_Systick(void)
{
    LED_Init();                          //LED初始化
    systime.init();                      //开启systick定时器
    uint32_t nowtime = 0;
    nowtime = systime.get_time_us();
    while(1)
    {
        
        if(systime.get_time_us() - nowtime >= 1000)
        {
            nowtime = systime.get_time_us();
            
            LED_ColorReverse(red);     //翻转红灯 用于指示程序运行
            
        }
    }
    
}


/**
  * @brief    测试systime 延时
  *
  * @param    
  *
  * @return   
  *
  * @note     示波器 LED_R_PIN   500Hz翻转
  *
  * @example  
  *
  * @date     2019/6/10 星期一
  */
void Test_SystickDelay(void)
{
    LED_Init();                          //LED初始化
    systime.init();                      //开启systick定时器
    while(1)
    {
        systime.delay_ms(1);
        LED_ColorReverse(red);           //翻转红灯 用于指示程序运行
        
    }
    
}



