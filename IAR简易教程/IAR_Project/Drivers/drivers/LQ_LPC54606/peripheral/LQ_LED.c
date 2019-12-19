/*!
  * @file     LQ_LED.c
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
#include "LQ_GPIO.h"
#include "LQ_LED.h"


/** 声明外部延时函数 */
extern void delayms(uint16_t ms);




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
void LED_Init(void)
{
    PIN_InitConfig(LED_R_PIN,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(LED_G_PIN,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(LED_B_PIN,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(LED_D0_PIN, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(LED_D1_PIN, PIN_MODE_OUTPUT, 0);
    
}



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
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            PIN_Write(LED_G_PIN,  0U);//LED亮; 
            PIN_Write(LED_R_PIN,  0U);//LED亮; 
            PIN_Write(LED_B_PIN,  0U);//LED亮; 
            break;
        case black:
            PIN_Write(LED_G_PIN,  1U);//LED灭; 
            PIN_Write(LED_R_PIN,  1U);//LED灭; 
            PIN_Write(LED_B_PIN,  1U);//LED灭; 
            break;
        case red:
            PIN_Write(LED_G_PIN,  1U);//LED灭; 
            PIN_Write(LED_R_PIN,  0U);//LED亮; 
            PIN_Write(LED_B_PIN,  1U);//LED灭; 
            break;
        case green:
            PIN_Write(LED_G_PIN,  0U);//LED亮; 
            PIN_Write(LED_R_PIN,  1U);//LED灭; 
            PIN_Write(LED_B_PIN,  1U);//LED灭; 
            break;
        case blue:
            PIN_Write(LED_G_PIN,  1U);//LED灭; 
            PIN_Write(LED_R_PIN,  1U);//LED灭; 
            PIN_Write(LED_B_PIN,  0U);//LED亮; 
            break;
        case yellow:
            PIN_Write(LED_G_PIN,  0U);//LED亮; 
            PIN_Write(LED_R_PIN,  0U);//LED亮; 
            PIN_Write(LED_B_PIN,  1U);//LED灭; 
            break;
        case violet:
            PIN_Write(LED_G_PIN,  1U);//LED灭; 
            PIN_Write(LED_R_PIN,  0U);//LED亮; 
            PIN_Write(LED_B_PIN,  0U);//LED亮; 
            break;
        case cyan:
            PIN_Write(LED_G_PIN,  0U);//LED亮; 
            PIN_Write(LED_R_PIN,  1U);//LED灭; 
            PIN_Write(LED_B_PIN,  0U);//LED亮; 
            break;      
    }
}




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
void LED_ColorReverse(LED_t color)
{
    static uint8_t count = 0;
    if(count++ % 2)
    {
        LED_Color(color);   //亮指定颜色的灯
    }
    else
    {
        LED_Color(black);   //灭
    }
    
}


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
void Test_LED(void)
{
  LED_Init();   
  while (1)
  {          
        LED_Color(red);     //红灯
        delayms(500);
        LED_Color(green);   //绿灯
        delayms(500);
        LED_Color(blue);    //蓝灯
        delayms(500);
        LED_Color(violet);  //紫灯
        delayms(500);
        LED_Color(yellow);  //黄灯
        delayms(500);
        LED_Color(cyan);    //青灯
        delayms(500);
        LED_Color(white);   //白灯
        delayms(500);
        LED_Color(black);   //关灯
        delayms(500);
        
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(red);     //红灯闪烁
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(green);   //绿灯闪烁
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(blue);    //蓝灯闪烁
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(violet);  //紫灯闪烁
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(yellow);  //黄灯闪烁
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(cyan);    //青灯闪烁
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(white);   //白灯闪烁
            delayms(100);
        }
        
        for(int i = 0; i < 20; i++)
        {
            PIN_Write(LED_D0_PIN,  1U);//LED亮;
            PIN_Write(LED_D1_PIN,  1U);//LED亮;
            delayms(100);
            PIN_Write(LED_D0_PIN,  0U);//LED亮;
            PIN_Write(LED_D1_PIN,  0U);//LED亮;
            delayms(100);
        }

  }
}

