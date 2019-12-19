/*!
  * @file     LQ_GPIO.c
  *
  * @brief    GPIO驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/11 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "fsl_clock.h"
#include "fsl_inputmux.h"
#include "fsl_pint.h"
#include "LQ_GPIO.h"


/*!
  * @brief    设置IO复用功能
  *
  * @param    pin      ： 管脚标号    LQ_GPIO.h中定义
  * @param    mode     ： GPIO 模式   LQ_GPIO.h中的宏定义中选择   
  *
  * @return   无
  *
  * @note     每个IO最多8种复用 复用功能具体可以查看RM手册 第九章IOCON最后部分
  *
  * @see      PIN_MuxSet(P0_0, PIN_MODE_OUTPUT); //P0_0管脚设置为GPIO推挽输出功能
  *
  * @date     2019/10/18 星期五
  */
void PIN_MuxSet(GPIO_Name_t pin, uint32_t mode)
{
    /* 开启 时钟 */
    CLOCK_EnableClock(kCLOCK_Iocon);
    
    /* 设置 功能 */
    IOCON_PinMuxSet(IOCON, PTx(pin), PTn(pin), mode);
}




/*!
  * @brief    GPIO初始化
  *
  * @param    pin      ： 管脚标号  LQ_GPIO.h中定义
  * @param    mode     ： GPIO 模式   LQ_GPIO.h中的宏定义中选择
  * @param    output   ： 输出模式时，输出电平 1：高电平  0：低电平   
  *
  * @return   无
  *
  * @note     无
  *
  * @see      PIN_InitConfig(P0_0, PIN_MODE_OUTPUT, 1);  //P0_0初始化推挽输出 高电平
  *
  * @date     2019/10/18 星期五
  */
void PIN_InitConfig(GPIO_Name_t pin, uint32_t mode, uint8_t output)
{
    /* 设置复用功能 */
    PIN_MuxSet(pin, mode);
    
    gpio_pin_config_t pin_config_t;
    
    /* IO方向 */
    pin_config_t.pinDirection = (gpio_pin_direction_t)((mode & 0x8000000)>>27);
    
    /* 输出电平 */
    pin_config_t.outputLogic = output;
   
    /* 打开GPIO时钟 */
    if(0 == PTx(pin))
    {
        CLOCK_EnableClock(kCLOCK_Gpio0);
    }
    else if(1 == PTx(pin))
    {
        CLOCK_EnableClock(kCLOCK_Gpio1);
    }

    /* 初始化GPIO */
    GPIO_PinInit(GPIO, PTx(pin), PTn(pin), &pin_config_t);
}

/*!
  * @brief    GPIO初始化
  *
  * @param    pin      ： 管脚标号  LQ_GPIO.h中定义  
  *
  * @return   读取的电平  1：高电平  0：低电平   
  *
  * @note     使用前先初始化IO
  *
  * @see      PIN_Read(P0_0, PIN_MODE_OUTPUT, 1);  //P0_0初始化推挽输出 高电平
  *
  * @date     2019/10/18 星期五
  */
uint8_t PIN_Read(GPIO_Name_t pin)
{
    return GPIO->B[PTx(pin)][PTn(pin)];
}

/*!
  * @brief    设置GPIO输出状态
  *
  * @param    pin      ： 管脚标号 LQ_GPIO_Cfg.h中定义
  * @param    output   ： 1:高电平  0：低电平
  *
  * @return   无
  *
  * @note     使用前先初始化IO
  *
  * @example  PIN_Write(P0_0, 1);//P0_0置为高电平
  *
  * @date     2019/8/19 星期一
  */
void PIN_Write(GPIO_Name_t pin, uint8_t output)
{
    uint8_t ptx = PTx(pin);
    uint8_t ptn = PTn(pin);
    GPIO->B[ptx][ptn] = output;
}


/*!
  * @brief    设置GPIO输入输出
  *
  * @param    pin      ： 管脚标号 LQ_GPIO_Cfg.h中定义
  * @param    mode     ： 1:输出  0：输入
  *
  * @return   无
  *
  * @note     使用前请先初始化
  *
  * @example  PIN_Dir(P0_0, 1);//P0_0设置为输出
  *
  * @date     2019/8/19 星期一
  */
void PIN_Dir(GPIO_Name_t pin, uint8_t mode)
{ 
    if(0 == mode)
    {
        GPIO->DIR[PTx(pin)] &= ~((uint32_t)(1<<PTn(pin)));
    }
    else
    {
        GPIO->DIR[PTx(pin)] |= 1<<PTn(pin);
    }
}

/*!
  * @brief    GPIO翻转函数
  *
  * @param    pin      ： 管脚标号 LQ_GPIO_Cfg.h中定义
  *
  * @return   无
  *
  * @note     使用前请先初始化
  *
  * @see      PIN_Reverse(P0_0); //翻转P0_0管脚
  *
  * @date     2019/10/18 星期五
  */
void PIN_Reverse(GPIO_Name_t pin)
{
    GPIO->NOT[PTx(pin)]  = 1<<PTn(pin);
}


/*!
  * @brief    GPIO外部中断初始化
  *
  * @param    pin      ： 管脚标号 LQ_GPIO_Cfg.h中定义
  * @param    mode     ： GPIO 中断模式   LQ_GPIO.h中的宏定义中选择
  * @param    Channel  ： 使用的外部中断通道 0-7
  *
  * @return   无
  *
  * @note     LPC54606一共有8个外部中断，所有管脚都可以连接到这8个外部中断上 
  *
  * @example  PIN_Exti(P0_0, 0, PIN_IRQ_MODE_FALLING);//配置P0_0 下降沿触发中断
  * @example  优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级可打断别的中断
  * @example  NVIC_SetPriority(PIN_INT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
  * @example  EnableIRQ(PIN_INT0_IRQn);			          //使能外部中断通道 0   
  *
  * @date     2019/8/19 星期一
  */
void PIN_Exti(GPIO_Name_t pin, uint8_t Channel, uint8_t mode)
{
    assert(Channel < 8);
    uint32_t temp = 0;
    
    if(mode == PIN_IRQ_MODE_RISING || mode == PIN_IRQ_MODE_HIGH_LEVEL)
    {
        temp = PIN_MODE_INPUT_PULLDOWN;
    }
    else if(mode == PIN_IRQ_MODE_FALLING || mode == PIN_IRQ_MODE_LOW_LEVEL)
    {
        temp = PIN_MODE_INPUT_PULLUP;
    }
    else
    {
        temp = PIN_MODE_INPUT;
    }
    /* 初始化 IO状态 */
    PIN_MuxSet(pin, temp);

    static uint8_t count = 0;
    if(0 == count)
    {
        count ++;
        
        // 初始化PINT 
        PINT_Init(PINT);
        
        /* 中断复用器初始化 */
        INPUTMUX_Init(INPUTMUX);
    }

    /* 将管脚连接到对应的中断通道上 */
    INPUTMUX_AttachSignal(INPUTMUX, (pint_pin_int_t)Channel, (inputmux_connection_t)(pin + (PINTSEL_PMUX_ID << PMUX_SHIFT)));   

    // 设置管脚触发方式 和 中断函数 
    PINT_PinInterruptConfig(PINT, (pint_pin_int_t)Channel, (pint_pin_enable_t)mode, NULL);

    // 清除标志位
    PINT_PinInterruptClrStatusAll(PINT);
}

