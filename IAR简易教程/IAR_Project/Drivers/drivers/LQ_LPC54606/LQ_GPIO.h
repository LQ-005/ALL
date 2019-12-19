/*!
  * @file     LQ_GPIO.h
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
#ifndef __LQ_GPIO_H
#define __LQ_GPIO_H

#include "fsl_gpio.h"

/** 
  * @brief GPIO 枚举端口编号
  */
typedef enum // 
{
    P0_0=0,  P0_1,  P0_2,  P0_3,  P0_4,  P0_5,  P0_6,  P0_7,
    P0_8,    P0_9,  P0_10, P0_11, P0_12, P0_13, P0_14, P0_15,
    P0_16,   P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23,
    P0_24,   P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31,
                                                         
    P1_0,    P1_1,  P1_2,  P1_3,  P1_4,  P1_5,  P1_6,  P1_7,
    P1_8,    P1_9,  P1_10, P1_11, P1_12, P1_13, P1_14, P1_15,
    P1_16,   P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23,
    P1_24,   P1_25, P1_26, P1_27, P1_28, P1_29, P1_30, P1_31,

}GPIO_Name_t;


/** 
  * @brief GPIO配置枚举体
  */
typedef enum
{
    /*!< GPIO复用功能 每种复用功能具体可以查看RM手册 第九章IOCON最后部分 */
    FUNC0          = IOCON_PIO_FUNC(0),
    FUNC1          = IOCON_PIO_FUNC(1),
    FUNC2          = IOCON_PIO_FUNC(2),
    FUNC3          = IOCON_PIO_FUNC(3),
    FUNC4          = IOCON_PIO_FUNC(4),
    FUNC5          = IOCON_PIO_FUNC(5),
    FUNC6          = IOCON_PIO_FUNC(6),
    FUNC7          = IOCON_PIO_FUNC(7),
    
    /*!< 上下拉电阻配置  注意 PT013, PT014 不可以设置上下拉电阻 */
    MODE_Diaable   =   IOCON_PIO_MODE(0),   /*!< 不使用上下拉电阻 */
    MODE_Down      =   IOCON_PIO_MODE(1),   /*!< 使用下拉电阻 */
    MODE_Up        =   IOCON_PIO_MODE(2),   /*!< 使用上拉电阻 */
    MODE_Repeater  =   IOCON_PIO_MODE(3),   /*!< 使用Repeater mode */

    /*!< IIC模式和GPIO模式  PT013, PT014才可以设置 个人理解：这个主要是为了高速IIC设计的，
         一般情况下，外设模块的IIC速率最大400K，不需要怎么关心IIC总线上的RC值，但是高速IIC就需要注意这些了*/
    MODE_IIC       =   IOCON_PIO_I2CSLEW(0), /*!< IIC模式 */
    MODE_GPIO      =   IOCON_PIO_I2CSLEW(1), /*!< GPIO模式 */
    
    /*!< 信号倒置  */
    INVERT_Disable =   IOCON_PIO_INVERT(0),  /*!< 不使用信号倒置功能 */
    INVERT_Enable  =   IOCON_PIO_INVERT(1),  /*!< 使用信号倒置功能 */
    
    /*!< 模拟数字模式  */
    DIGIMODE_Analog=   IOCON_PIO_DIGIMODE(0),/*!< 模拟 ADC模式 */
    DIGIMODE_Digital=  IOCON_PIO_DIGIMODE(1),/*!< 数字 信号模式 */
    
    /*!< 滤波功能  */
    FILTER_Enable  =   IOCON_PIO_FILTEROFF(0),/*!< 开启 */
    FILTER_Disable =   IOCON_PIO_FILTEROFF(1),/*!< 关闭 */
    
/*----------------------------------------------------------------*/
    /*!< 转换速率  PT010-PT016，PT023、PT031、PT10不可用 */
    SLEW_Standard  =   IOCON_PIO_SLEW(0),     /*!< 标准模式 */
    SLEW_Fast      =   IOCON_PIO_SLEW(1),     /*!< 快速模式 */
    
    /*!< IIC驱动能力  仅PT013, PT014可用 这个和转换速率其实是一个位，只是在IIC模式和GPIO模式下释意不同 */
    I2CDRIVE_Low   =   IOCON_PIO_I2CDRIVE(0), /*!< 一般模式 4mA*/
    I2CDRIVE_High  =   IOCON_PIO_I2CDRIVE(1), /*!< 超高速模式 20mA*/
/*----------------------------------------------------------------*/
    
    /*!< 开漏模式  PT013, PT014不可用 */
    OD_Disable     =   IOCON_PIO_OD(0),       /*!< 关闭开漏*/
    OD_Enable      =   IOCON_PIO_OD(1),       /*!< 使能开漏*/
    
    /*!< IIC 50ns毛刺滤波器  仅PT013, PT014可用 */
    I2CFILTER_Disable = IOCON_PIO_I2CFILTER(0),/*!< 关闭*/
    I2CFILTER_Enable  = IOCON_PIO_I2CFILTER(1),/*!< 开启*/
    
    
    /* 输入 输出(为方便使用自己添加的，寄存器并没有这个) */
    OUTPUT               = 0x8000000,    /*!< 输出 */
    INPUT                = 0,            /*!< 输入 */
    
}PinConfig_t;




/* GPIO常用配置 */
#define PIN_MODE_OUTPUT         OUTPUT|FUNC0|MODE_Diaable|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Disable   /*!< 推挽输出  */
#define PIN_MODE_INPUT          INPUT|FUNC0|MODE_Diaable|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Enable     /*!< 浮空输入  */
#define PIN_MODE_INPUT_PULLUP   INPUT|FUNC0|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Disable         /*!< 上拉输入  */
#define PIN_MODE_INPUT_PULLDOWN INPUT|FUNC0|MODE_Down|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Disable       /*!< 下拉输入  */
#define PIN_MODE_OUTPUT_OD      OUTPUT|FUNC0|MODE_Diaable|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Enable    /*!< 开漏输出  */

/* GPIO 中断触发模式 */
#define PIN_IRQ_MODE_RISING             0x01 /*!< 上升沿（下拉）触发中断 */  
#define PIN_IRQ_MODE_FALLING            0x02 /*!< 下降沿（上拉）触发中断 */
#define PIN_IRQ_MODE_RISING_FALLING     0x03 /*!< 双边沿（开漏）触发中断 */
#define PIN_IRQ_MODE_LOW_LEVEL          0x04 /*!< 低电平（上拉）触发中断 */
#define PIN_IRQ_MODE_HIGH_LEVEL         0x05 /*!< 高电平（下拉）触发中断 */


/* 获取端口和标号 */
#define PTx(PTX_n)  (PTX_n>>5)  /*!< 获取模块号 PTX_n/32 */
#define PTn(PTX_n)  (PTX_n&0x1f)/*!< 获取引脚号 PTX_n%32 */

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
void PIN_MuxSet(GPIO_Name_t pin, uint32_t mode);


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
void PIN_InitConfig(GPIO_Name_t pin, uint32_t mode, uint8_t output);



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
uint8_t PIN_Read(GPIO_Name_t pin);



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
void PIN_Write(GPIO_Name_t pin, uint8_t output);



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
void PIN_Dir(GPIO_Name_t pin, uint8_t mode);



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
void PIN_Reverse(GPIO_Name_t pin);



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
void PIN_Exti(GPIO_Name_t pin, uint8_t Channel, uint8_t mode);



/*!
  * @brief    类似51风格的操作 和STM32中的IO微操作类似
  *
  * @param    x ：端口号
  *
  * @return   无
  *
  * @note     使用前要初始化IO
  *
  * @see      PT0(2) = !PT0(2);  //翻转PT0_2 管脚的输出状态
  *
  * @date     2019/10/18 星期五
  */
#define PT0(x)    GPIO->B[0][x]
#define PT1(x)    GPIO->B[1][x]

/*! 定义PT0_的端口  类似51风格的操作 */
#define PT0_0     GPIO->B[0][0]
#define PT0_1     GPIO->B[0][1]
#define PT0_2     GPIO->B[0][2]
#define PT0_3     GPIO->B[0][3]
#define PT0_4     GPIO->B[0][4]
#define PT0_5     GPIO->B[0][5]
#define PT0_6     GPIO->B[0][6]
#define PT0_7     GPIO->B[0][7]
#define PT0_8     GPIO->B[0][8]
#define PT0_9     GPIO->B[0][9]
#define PT0_10    GPIO->B[0][10]
#define PT0_11    GPIO->B[0][11]
#define PT0_12    GPIO->B[0][12]
#define PT0_13    GPIO->B[0][13]
#define PT0_14    GPIO->B[0][14]
#define PT0_15    GPIO->B[0][15]
#define PT0_16    GPIO->B[0][16]
#define PT0_17    GPIO->B[0][17]
#define PT0_18    GPIO->B[0][18]
#define PT0_19    GPIO->B[0][19]
#define PT0_20    GPIO->B[0][20]
#define PT0_21    GPIO->B[0][21]
#define PT0_22    GPIO->B[0][22]
#define PT0_23    GPIO->B[0][23]
#define PT0_24    GPIO->B[0][24]
#define PT0_25    GPIO->B[0][25]
#define PT0_26    GPIO->B[0][26]
#define PT0_27    GPIO->B[0][27]
#define PT0_28    GPIO->B[0][28]
#define PT0_29    GPIO->B[0][29]
#define PT0_30    GPIO->B[0][30]
#define PT0_31    GPIO->B[0][31]

/*! 定义PT1_的端口  */
#define PT1_0     GPIO->B[1][0]
#define PT1_1     GPIO->B[1][1]
#define PT1_2     GPIO->B[1][2]
#define PT1_3     GPIO->B[1][3]
#define PT1_4     GPIO->B[1][4]
#define PT1_5     GPIO->B[1][5]
#define PT1_6     GPIO->B[1][6]
#define PT1_7     GPIO->B[1][7]
#define PT1_8     GPIO->B[1][8]
#define PT1_9     GPIO->B[1][9]
#define PT1_10    GPIO->B[1][10]
#define PT1_11    GPIO->B[1][11]
#define PT1_12    GPIO->B[1][12]
#define PT1_13    GPIO->B[1][13]
#define PT1_14    GPIO->B[1][14]
#define PT1_15    GPIO->B[1][15]
#define PT1_16    GPIO->B[1][16]
#define PT1_17    GPIO->B[1][17]
#define PT1_18    GPIO->B[1][18]
#define PT1_19    GPIO->B[1][19]
#define PT1_20    GPIO->B[1][20]
#define PT1_21    GPIO->B[1][21]
#define PT1_22    GPIO->B[1][22]
#define PT1_23    GPIO->B[1][23]
#define PT1_24    GPIO->B[1][24]
#define PT1_25    GPIO->B[1][25]
#define PT1_26    GPIO->B[1][26]
#define PT1_27    GPIO->B[1][27]
#define PT1_28    GPIO->B[1][28]
#define PT1_29    GPIO->B[1][29]
#define PT1_30    GPIO->B[1][30]
#define PT1_31    GPIO->B[1][31]



/*! 定义PT0_的8位端口  */
#define PT0__BYTE0   GPIO->PINs[0].Byte0
#define PT0__BYTE1   GPIO->PINs[0].Byte1
#define PT0__BYTE2   GPIO->PINs[0].Byte2
#define PT0__BYTE3   GPIO->PINs[0].Byte3

#define PT1__BYTE0   GPIO->PINs[1].Byte0
#define PT1__BYTE1   GPIO->PINs[1].Byte1
#define PT1__BYTE2   GPIO->PINs[1].Byte2
#define PT1__BYTE3   GPIO->PINs[1].Byte3

/*! 定义PT0_的输出输入方向  */
#define PT0_0_DIR     GPIO->DIRs[0].BIT0
#define PT0_1_DIR     GPIO->DIRs[0].BIT1
#define PT0_2_DIR     GPIO->DIRs[0].BIT2
#define PT0_3_DIR     GPIO->DIRs[0].BIT3
#define PT0_4_DIR     GPIO->DIRs[0].BIT4
#define PT0_5_DIR     GPIO->DIRs[0].BIT5
#define PT0_6_DIR     GPIO->DIRs[0].BIT6
#define PT0_7_DIR     GPIO->DIRs[0].BIT7
#define PT0_8_DIR     GPIO->DIRs[0].BIT8
#define PT0_9_DIR     GPIO->DIRs[0].BIT9
#define PT0_10_DIR    GPIO->DIRs[0].BIT10
#define PT0_11_DIR    GPIO->DIRs[0].BIT11
#define PT0_12_DIR    GPIO->DIRs[0].BIT12
#define PT0_13_DIR    GPIO->DIRs[0].BIT13
#define PT0_14_DIR    GPIO->DIRs[0].BIT14
#define PT0_15_DIR    GPIO->DIRs[0].BIT15
#define PT0_16_DIR    GPIO->DIRs[0].BIT16
#define PT0_17_DIR    GPIO->DIRs[0].BIT17
#define PT0_18_DIR    GPIO->DIRs[0].BIT18
#define PT0_19_DIR    GPIO->DIRs[0].BIT19
#define PT0_20_DIR    GPIO->DIRs[0].BIT20
#define PT0_21_DIR    GPIO->DIRs[0].BIT21
#define PT0_22_DIR    GPIO->DIRs[0].BIT22
#define PT0_23_DIR    GPIO->DIRs[0].BIT23
#define PT0_24_DIR    GPIO->DIRs[0].BIT24
#define PT0_25_DIR    GPIO->DIRs[0].BIT25
#define PT0_26_DIR    GPIO->DIRs[0].BIT26
#define PT0_27_DIR    GPIO->DIRs[0].BIT27
#define PT0_28_DIR    GPIO->DIRs[0].BIT28
#define PT0_29_DIR    GPIO->DIRs[0].BIT29
#define PT0_30_DIR    GPIO->DIRs[0].BIT30
#define PT0_31_DIR    GPIO->DIRs[0].BIT31

/*! 定义PT1_的输出输入方向   */
#define PT1_0_DIR     GPIO->DIRs[1].BIT0
#define PT1_1_DIR     GPIO->DIRs[1].BIT1
#define PT1_2_DIR     GPIO->DIRs[1].BIT2
#define PT1_3_DIR     GPIO->DIRs[1].BIT3
#define PT1_4_DIR     GPIO->DIRs[1].BIT4
#define PT1_5_DIR     GPIO->DIRs[1].BIT5
#define PT1_6_DIR     GPIO->DIRs[1].BIT6
#define PT1_7_DIR     GPIO->DIRs[1].BIT7
#define PT1_8_DIR     GPIO->DIRs[1].BIT8
#define PT1_9_DIR     GPIO->DIRs[1].BIT9
#define PT1_10_DIR    GPIO->DIRs[1].BIT10
#define PT1_11_DIR    GPIO->DIRs[1].BIT11
#define PT1_12_DIR    GPIO->DIRs[1].BIT12
#define PT1_13_DIR    GPIO->DIRs[1].BIT13
#define PT1_14_DIR    GPIO->DIRs[1].BIT14
#define PT1_15_DIR    GPIO->DIRs[1].BIT15
#define PT1_16_DIR    GPIO->DIRs[1].BIT16
#define PT1_17_DIR    GPIO->DIRs[1].BIT17
#define PT1_18_DIR    GPIO->DIRs[1].BIT18
#define PT1_19_DIR    GPIO->DIRs[1].BIT19
#define PT1_20_DIR    GPIO->DIRs[1].BIT20
#define PT1_21_DIR    GPIO->DIRs[1].BIT21
#define PT1_22_DIR    GPIO->DIRs[1].BIT22
#define PT1_23_DIR    GPIO->DIRs[1].BIT23
#define PT1_24_DIR    GPIO->DIRs[1].BIT24
#define PT1_25_DIR    GPIO->DIRs[1].BIT25
#define PT1_26_DIR    GPIO->DIRs[1].BIT26
#define PT1_27_DIR    GPIO->DIRs[1].BIT27
#define PT1_28_DIR    GPIO->DIRs[1].BIT28
#define PT1_29_DIR    GPIO->DIRs[1].BIT29
#define PT1_30_DIR    GPIO->DIRs[1].BIT30
#define PT1_31_DIR    GPIO->DIRs[1].BIT31

#endif



