/*!
  * @file     LQ_KEY.c
  *
  * @brief    按键驱动文件
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
#include "LQ_LED.h"
#include "LQ_KEY.h"
#include "LQ_GPIO.h"
/** 声明外部延时函数 */
extern void delayms(uint16_t ms);




/**
  * @brief    初始化龙邱母板上的按键
  *
  * @param    无
  *
  * @return   无
  *
  * @note     按键IO在LQ_KEY.h中通过宏定义选择
  *
  * @see      KEY_Init();
  *
  * @date     2019/6/4 星期二
  */
void KEY_Init(void)
{  
    /* 设置上拉输入 */
    PIN_InitConfig(KEY0_PIN,  PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(KEY1_PIN,  PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(KEY2_PIN,  PIN_MODE_INPUT_PULLUP, 1);  
}


/**
  * @brief    读取按键状态
  *
  * @param    mode： 0：不支持连续按;   1：支持连续按;
  *
  * @return   0：无按键按下  1：KEY0按下  2:KEY1按下  3:KEY2按下
  *
  * @note     使用前请先初始化按键
  *
  * @see      uint8_t key_flag = KEY_Read(0);
  *
  * @date     2019/6/4 星期二
  */
uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //按键松开标志
    if(mode==1) 
    {
        key_up=1;      //支持连按
    }
    if(key_up && (PIN_Read(KEY0_PIN)==0 || PIN_Read(KEY1_PIN)==0 || PIN_Read(KEY2_PIN)==0))
    {
        delayms(10);   //消抖
        key_up=0;
        if(PIN_Read(KEY0_PIN)==0)      
        {
            return 1;
        }
        
        else if(PIN_Read(KEY1_PIN)==0) 
        {
            return 2;    
        }
        
        else if(PIN_Read(KEY2_PIN)==0) 
        {
            return 3;    
        }
        
    }
    if(PIN_Read(KEY0_PIN)==1 && PIN_Read(KEY1_PIN)==1 && PIN_Read(KEY2_PIN)==1) 
    {
        key_up=1;   
    }
    return 0;   //无按键按下
    
}



/*!
  * @brief    测试GPIIO外部中断
  *
  * @param    无
  *
  * @return   无
  *
  * @note     按下母板上不同的按键 不同颜色的灯闪烁
  *
  * @see      Test_ExtiKEY();
  *
  * @date     2019/8/19 星期一
  */
void Test_ExtiKEY(void)
{
    LED_Init();
    
    /* 配置下降沿触发中断 */
    PIN_Exti(KEY0_PIN, 0, PIN_IRQ_MODE_FALLING);
    PIN_Exti(KEY1_PIN, 1, PIN_IRQ_MODE_FALLING);
    PIN_Exti(KEY2_PIN, 2, PIN_IRQ_MODE_FALLING);
  
    //优先级配置 抢占优先级4  子优先级0   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(PIN_INT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4,0));
    
	EnableIRQ(PIN_INT0_IRQn);			          //使能PIN_INT0_IRQn的中断  
    
    //优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(PIN_INT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    
	EnableIRQ(PIN_INT1_IRQn);			          //使能PIN_INT1_IRQn的中断 

    //优先级配置 抢占优先级6  子优先级0   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(PIN_INT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),6,0));
    
	EnableIRQ(PIN_INT2_IRQn);			          //使能PIN_INT2_IRQn的中断 
    /* 在irq.c 中 处理中断 */
    while(1);



}


/**
  * @brief    测试按键
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @see      Test_KEY();
  *
  * @date     2019/6/4 星期二
  */
void Test_KEY(void)
{ 
    LED_Init();
    KEY_Init(); 
    while (1)
    {  
        switch(KEY_Read(1))  
        {
            case 1:
                LED_Color(red);     
                break;           
            case 2:      
                LED_Color(green);   
                break;
            case 3:      
                LED_Color(blue);    
                break;
            default:
                LED_Color(white);   
                break;
        }

        delayms(50);
    }
}


