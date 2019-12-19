/*!
  * @file     LQ_SCTIME.c
  *
  * @brief    SCT驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1 
  *           修改记录   2019/11/13  SCTIMER0 函数入口参数结构体
  *           			 2019/12/11  优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "fsl_iocon.h"
#include "fsl_sctimer.h"
#include "fsl_clock.h"
#include "fsl_inputmux.h"
#include "LQ_SCTIME.h"


/*!
  * @brief    SCT 输出PWM初始化
  *
  * @param    channel    ： SCT通道  LQ_SCTIME.h 中可的枚举体
  * @param    frequency  ： 频率  注意SCT输出的PWM频率必须一样
  * @param    duty       ： 占空比百分之 duty/SCT_PWM_MAX *100  
  *
  * @return   无
  *
  * @note     SCT最多10个事件，其中一个事件用于PWM周期，其他九个事件可以产生9路频率相同的PWM
  * @note     但是摄像头也需要用到SCT的事件，如果使用神眼带与非门的转接座（白色），需要一个输入事件接摄像头像素同步信号触发DMA，最多就只能输出8路PWM
  * @note     如果使用神眼老板转接座或者OV7725，就需要更多的输入事件 不可以驱动8路PWM了。
  *
  * @see      SCT_InitPwmConfig(SctOutPut0_P0_2, 18000, 500); //设置通道0 P0_2输出频率 18000 占空比百分之 500/SCT_PWM_MAX *100
  *
  * @date     2019/10/21 星期一
  */
void SCT_InitPwmConfig(SCT0_OutChnannel_t channel, uint32_t frequency, uint32_t duty)
{
    /* 管脚初始化 */
    SCT_PwmPinInit(channel);
    
	channel = (SCT0_OutChnannel_t)((uint32_t)channel >> 8);
    /* 设置分频系数 */
    uint32_t core_clock = CLOCK_GetFreq(kCLOCK_BusClk);
                           
    uint32_t div = core_clock/(frequency * 0xffff);
    
    if(div > 255)
    {
        assert("输入频率过低");
    }
    
    /* 初始化的结构体 */
    sctimer_config_t config = {
        .enableCounterUnify = false,                   /* SCT是两个16位定时器 可以级联为32位定时器 */
        .clockMode = kSCTIMER_System_ClockMode,         /* SCT使用内核时钟 */
        .clockSelect = kSCTIMER_Clock_On_Rise_Input_0,  /* 在内核时钟上升沿计数 */
        .enableBidirection_l = false,                   /* SCT 低16位计数器 向上计数 */
        .enableBidirection_h = false,                   /* SCT 高16位计数器 向上计数 */
        .prescale_l = div,                               /* SCT 低16位计数器 分频系数 */
        .prescale_h = div,                               /* SCT 高16位计数器 分频系数 */
        .outInitState = 0U,                              /* SCT 输出管脚初始状态 */
        .inputsync = 0                                   /* SCT 输入管脚初始状态 */
    };

    /* 开启时钟 */
    CLOCK_EnableClock(kCLOCK_Sct0);
    
    /* 按照上面初始化结构体配置寄存器 */
    SCT0->CONFIG = SCT_CONFIG_CKSEL(config.clockSelect) | SCT_CONFIG_CLKMODE(config.clockMode) |
                   SCT_CONFIG_UNIFY(config.enableCounterUnify) | SCT_CONFIG_INSYNC(config.inputsync);
    SCT0->CTRL = SCT_CTRL_BIDIR_L(config.enableBidirection_l) | SCT_CTRL_PRE_L(config.prescale_l) |
                 SCT_CTRL_CLRCTR_L_MASK | SCT_CTRL_HALT_L_MASK;
    if (!(config.enableCounterUnify))
    {
        SCT0->CTRL |= SCT_CTRL_BIDIR_H(config.enableBidirection_h) | SCT_CTRL_PRE_H(config.prescale_h) |
                      SCT_CTRL_CLRCTR_H_MASK | SCT_CTRL_HALT_H_MASK;
    }
    
    
    //暂停SCT 以便修改某些必须要在停止状态下才能修改的寄存器
    SCT0->CTRL |= (SCT_CTRL_HALT_H_MASK | SCT_CTRL_HALT_L_MASK);                  
     
    //PWM初始化 使用匹配模式
    SCT0->REGMODE = 0;                                                            

    /* 周期通道 SCT一共有十个事件， 一个事件用于PWM周期，不能产生PWM
       SCT有16个状态 每个状态下都可以指定一些事件可以发生，一些不可以发生 */
    /* 任何状态下 都可以发生周期事件 */
    SCT0->EVENT[PWM_SCT_EVENT_PERIOD].STATE = 0xffff;            
    
    uint32_t period = core_clock/(frequency * (div + 1));                           //周期计数次数
    uint32_t match_val = (uint32_t)(duty * (double)((double)period / (double)SCT_PWM_MAX));   //计算占空比匹配数
    
    /* 设置周期事件*/
    SCT0->SCTMATCH[PWM_SCT_EVENT_PERIOD] = period<<SCT_SCTMATCH_MATCHn_H_SHIFT;     //为 高16位定时器设置 匹配值 
    SCT0->SCTMATCHREL[PWM_SCT_EVENT_PERIOD] = period<<SCT_SCTMATCH_MATCHn_H_SHIFT;  //为 高16位定时器设置 自动装载值
    SCT0->EVENT[PWM_SCT_EVENT_PERIOD].CTRL =      SCT_EVENT_CTRL_MATCHSEL(PWM_SCT_EVENT_PERIOD) /* 选择与此事件关联的匹配寄存器 */
                                                | SCT_EVENT_CTRL_HEVENT(1)   /* 仅使用State_H状态机 */
                                                | SCT_EVENT_CTRL_OUTSEL(1)   /* 设置为输出 */
                                                | SCT_EVENT_CTRL_IOSEL(PWM_SCT_EVENT_PERIOD) /* 选择输出的通道 */
                                                | SCT_EVENT_CTRL_IOCOND(0)   /* 无效配置*/
                                                | SCT_EVENT_CTRL_COMBMODE(1) /* 仅使用指定的匹配项，而不考虑定时器系统的触发条件 */
                                                | SCT_EVENT_CTRL_STATELD(0)  /* 操作状态机的方式：直接载入新值 */
                                                | SCT_EVENT_CTRL_STATEV(0)   /* 事件发生后载入新的状态值 */
                                                | SCT_EVENT_CTRL_MATCHMEM(0) /* 此配置无效 */
                                                | SCT_EVENT_CTRL_DIRECTION(0)/* 此配置无效 */
                                                ;
    //将 PWM_SCT_EVENT_PERIOD 配置到限制寄存器中，当计数器计数到PWM_SCT_EVENT_PERIOD的匹配值时，计数器清零
    SCT0->LIMIT |= SCT_LIMIT_LIMMSK_H(1U << PWM_SCT_EVENT_PERIOD); 
    
    
    /* 任何状态下 都可以发生PWM事件 */
    SCT0->EVENT[channel].STATE = 0xffff;                                 
    
    /* 设置PWM匹配事件 */
    SCT0->SCTMATCH[channel] = match_val<<SCT_SCTMATCH_MATCHn_H_SHIFT;                 //channel 通道 高电平时间
    SCT0->SCTMATCHREL[channel] = match_val<<SCT_SCTMATCH_MATCHn_H_SHIFT;              //channel 通道 重装载值
    SCT0->EVENT[channel].CTRL =      SCT_EVENT_CTRL_MATCHSEL(channel) /* 选择与此事件关联的匹配寄存器 */
                                    | SCT_EVENT_CTRL_HEVENT(1)        /* 仅使用State_H状态机 */
                                    | SCT_EVENT_CTRL_OUTSEL(1)        /* 设置为输出 */
                                    | SCT_EVENT_CTRL_IOSEL(channel)   /* 选择输出的通道 */
                                    | SCT_EVENT_CTRL_IOCOND(0)        /* 无效配置*/
                                    | SCT_EVENT_CTRL_COMBMODE(1)      /* 仅使用指定的匹配项，而不考虑定时器系统的触发条件 */
                                    | SCT_EVENT_CTRL_STATELD(0)       /* 操作状态机的方式：直接载入新值 */
                                    | SCT_EVENT_CTRL_STATEV(0)        /* 事件发生后载入新的状态值 */
                                    | SCT_EVENT_CTRL_MATCHMEM(0)      /* 此配置无效 */
                                    | SCT_EVENT_CTRL_DIRECTION(0)     /* 此配置无效 */
                                    ;
    //计数器到达设定值后 设置清零 
    SCT0->OUT[channel].CLR = 1<<channel;                                  
   
    SCT0->RES &= ~((uint32_t)SCT_RES_O0RES_MASK<<(2*channel));                        //清除 通道SCT0_Chn对应的 conflict resolution register
    if(0 == match_val)                                                                 
    {
        SCT0->RES |= 0x2U<<(2*channel);                                               //清除输出 PWM周期事件发生会令输出置1，PWM匹配事件发生会令输出清零 同时发生应该清零
        SCT0->OUT[channel].SET = 1<<channel;                                          //设置输出 
    }
    else
    {
        SCT0->RES |= 0x1U<<(2*channel);                                               //设置输出 //如果多个事件(甚至同一个事件)要求同时设置和清除给定的输出，则应该采取设置输出操作
        SCT0->OUT[channel].SET = 1<<PWM_SCT_EVENT_PERIOD;                             //设置输出
    }

    SCT0->CTRL &= ~(SCT_CTRL_HALT_L_MASK | SCT_CTRL_HALT_H_MASK);      /* 启动状态机 */

}



/**
  * @brief    SCT 设置PWM占空比
  *
  * @param    channel    ： SCT通道  LQ_SCTIME.h 中的枚举体
  * @param    duty       ： 占空比百分之 duty/SCT_PWM_MAX *100
  *
  * @return   无
  *
  * @note     使用前需要初始化
  *
  * @example  SCT_PwmSetDuty(SctOutPut0_P0_2, 500);  //设置通道0 P0_2输出占空比百分之 500/SCT_PWM_MAX *100
  *
  * @date     2019/5/8 星期三
  */
void SCT_PwmSetDuty(SCT0_OutChnannel_t channel, uint32_t duty)
{
    assert(duty<=SCT_PWM_MAX); 
    uint32_t period;                              //周期计数次数
    uint32_t match_val;                           //匹配值
    channel = (SCT0_OutChnannel_t)((uint32_t)channel >> 8); 
    period = SCT0->SCTMATCHREL[PWM_SCT_EVENT_PERIOD]>>SCT_SCTMATCHREL_RELOADn_H_SHIFT;  //取出周期计数次数 初始化时设置过
    match_val = duty * period / SCT_PWM_MAX;                                            //计算占空比匹配数
                    
    SCT0->RES &= ~((uint32_t)SCT_RES_O0RES_MASK<<(2*channel));           //清除 通道SCT0_Chn对应的 conflict resolution register
    if(0 == match_val)
    {
        SCT0->RES |= 0x2U<<(2*channel);                                  //清除输出 PWM周期事件发生会令输出置1，PWM匹配事件发生会令输出清零 同时发生应该清零
        SCT0->OUT[channel].SET = 1<<channel;                             //设置输出 
    }                                                                                   
    else                                                                                
    {                                                                                   
        SCT0->RES |= 0x1U<<(2*channel);                                  //设置输出//如果多个事件(甚至同一个事件)要求同时设置和清除给定的输出，则应该采取设置输出操作
        SCT0->OUT[channel].SET = 1<<PWM_SCT_EVENT_PERIOD;                //设置输出
    }

    SCT0->SCTMATCHREL[channel] = match_val<<SCT_SCTMATCH_MATCHn_H_SHIFT; //更新匹配值
}

/*!
  * @brief    SCT 输入管脚触发DMA初始化
  *
  * @param    channel  :  SCT输入通道  LQ_SCTIME.h 中的枚举体
  *
  * @return   无
  *
  * @note     SCT最多10个事件，其中一个事件用于PWM周期，其他九个事件可以产生9路频率相同的PWM
  * @note     但是摄像头也需要用到SCT的事件，如果使用神眼带与非门的转接座，需要一个输入事件接摄像头像素同步信号触发DMA，最多就只能输出8路PWM
  * @note     如果使用神眼老板转接座或者OV7725，就不可以驱动8路PWM了。   
  *
  * @see      SCT_InitCameraConfig(SctInput0_P0_0);  //设置输入通道0 P0_0作为摄像头pclk接口
  *
  * @date     2019/10/22 星期二
  */
void SCT_InitCameraConfig(SCT0_InputChannel_t channel)
{

    SCT_CapPinInit(channel);

	channel = (SCT0_InputChannel_t)((uint32_t)channel >> 8);
    /* 多路复用器初始化 */
    INPUTMUX_Init(INPUTMUX);
    
    /* 将管脚连接到对应的SCT通道上 */
    INPUTMUX->SCT0_INMUX[channel] = INPUTMUX_SCT0_INMUX_INP_N(channel);      
    
    /* 初始化的结构体 */
    sctimer_config_t config = {
        .enableCounterUnify = false,                   /* SCT是两个16位定时器 可以级联为32位定时器 */
        .clockMode = kSCTIMER_System_ClockMode,         /* SCT使用内核时钟 */
        .clockSelect = kSCTIMER_Clock_On_Rise_Input_0,  /* 在内核时钟上升沿计数 */
        .enableBidirection_l = false,                   /* SCT 低16位计数器 向上计数 */
        .enableBidirection_h = false,                   /* SCT 高16位计数器 向上计数 */
        .prescale_l = 0,                                /* SCT 低16位计数器 分频系数 */
        .prescale_h = 0,                                /* SCT 高16位计数器 分频系数 */
        .outInitState = 0U,                              /* SCT 输出管脚初始状态 */
        .inputsync = (1U << channel)                     /* SCT 输入管脚初始状态 */
    };
    
    /* 开启时钟 */
    CLOCK_EnableClock(kCLOCK_Sct0);
    
    /* 按照上面初始化结构体配置寄存器 */
    SCT0->CONFIG = SCT_CONFIG_CKSEL(config.clockSelect) | SCT_CONFIG_CLKMODE(config.clockMode) |
                   SCT_CONFIG_UNIFY(config.enableCounterUnify) | SCT_CONFIG_INSYNC(config.inputsync);

    //暂停SCT 以便修改某些必须要在停止状态下才能修改的寄存器
    SCT0->CTRL |= (SCT_CTRL_HALT_H_MASK | SCT_CTRL_HALT_L_MASK);  
    
    //状态清零
    SCT0->STATE = (SCT0->STATE & SCT_STATE_STATE_H_MASK) | SCT_STATE_STATE_L(0U);   
    
    /* 任何状态下 都可以发生PCLK事件 */
    SCT0->EVENT[CAMERA_SCT_EVENT_PCLK].STATE = 0xffff;                    
    SCT0->EVENT[CAMERA_SCT_EVENT_PCLK].CTRL = ( 0 
                                    | SCT_EVENT_CTRL_HEVENT(0)                      /* 仅使用State_L状态机 */
                                    | SCT_EVENT_CTRL_OUTSEL(0)                      /* 接受输入引脚的触发 */
                                    | SCT_EVENT_CTRL_IOSEL(channel)                 /* 接受PCLK输入引脚的触发 */
                                    | SCT_EVENT_CTRL_IOCOND(1)                      /* 触发时机为输入上升沿 1：上升沿    2：下降沿 */  
                                    | SCT_EVENT_CTRL_COMBMODE(2)                    /* 仅使用IO引脚产生的触发信号，而不考虑定时器系统的触发条件 */
                                    | SCT_EVENT_CTRL_STATELD(1)                     /* 操作状态机的方式：直接载入新值 */
                                    | SCT_EVENT_CTRL_STATEV(1)                      /* 事件发生后载入新的状态值 */   
                                    | SCT_EVENT_CTRL_MATCHMEM(0)                    /* 此配置无效 */
                                    | SCT_EVENT_CTRL_DIRECTION(0)                   /* 此配置无效 */

                                    );
    SCT0->DMA0REQUEST = SCT_DMA0REQUEST_DEV_0(1U<<CAMERA_SCT_EVENT_PCLK);            //使能PCLK事件触发DMA
                      
    SCT0->CTRL &= ~(SCT_CTRL_HALT_L_MASK | SCT_CTRL_HALT_H_MASK);                    /* 启动状态机 */
    
}



/*!
  * @brief    SCT 输入引脚配置
  *
  * @param    channel  : SCT输入通道
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      SCT_CapPinInit(SctInput0_P1_5);  //初始化P1_5 功能复用为SCT输入
  *
  * @date     2019/5/8 星期三
  */
void SCT_CapPinInit(SCT0_InputChannel_t channel)
{
    uint32_t PIOFun3_config = FUNC3|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun4_config = FUNC4|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    switch(channel)
    {
      case SctInput0_P0_24:
        PIN_MuxSet(P0_24, PIOFun4_config);
        break;
      case SctInput0_P0_13:
        PIN_MuxSet(P0_13, PIOFun4_config);
        break;
      case SctInput0_P1_5:
        PIN_MuxSet(P1_5,  PIOFun4_config);
        break;  
      case SctInput0_P0_0:
        PIN_MuxSet(P0_0,  PIOFun4_config);
        break;  
      case SctInput1_P0_1:
        PIN_MuxSet(P0_1,  PIOFun4_config);
        break; 
      case SctInput1_P0_25:
        PIN_MuxSet(P0_25, PIOFun4_config);
        break;
      case SctInput2_P0_20:
        PIN_MuxSet(P0_20, PIOFun4_config);
        break;  
      case SctInput2_P0_2:
        PIN_MuxSet(P0_2,  PIOFun4_config);
        break;  
      case SctInput3_P1_6:
        PIN_MuxSet(P1_6,  PIOFun4_config);
        break;
      case SctInput3_P0_21:
        PIN_MuxSet(P0_21, PIOFun4_config);
        break;
      case SctInput3_P0_3:
        PIN_MuxSet(P0_3,  PIOFun4_config);
        break;  
      case SctInput4_P1_7:
        PIN_MuxSet(P1_7,  PIOFun4_config);
        break;
      case SctInput4_P1_0:
        PIN_MuxSet(P1_0,  PIOFun4_config);
        break;
      case SctInput4_P0_4:
        PIN_MuxSet(P0_4,  PIOFun4_config);
        break;
      case SctInput5_P0_5:
        PIN_MuxSet(P0_5,  PIOFun4_config);
        break;
      case SctInput5_P1_22:
        PIN_MuxSet(P1_22, PIOFun4_config);
        break;
      case SctInput5_P1_1:
        PIN_MuxSet(P1_1,  PIOFun4_config);
        break;
      case SctInput6_P1_2:
        PIN_MuxSet(P1_2,  PIOFun4_config);
        break;
      case SctInput6_P1_29:
        PIN_MuxSet(P1_29, PIOFun3_config);
        break;
      case SctInput6_P0_6:
        PIN_MuxSet(P0_6,  PIOFun4_config);
        break;
      case SctInput7_P1_19:
        PIN_MuxSet(P1_19, PIOFun4_config);
        break;
      case SctInput7_P1_30:
        PIN_MuxSet(P1_30, PIOFun3_config);
        break;
      case SctInput7_P0_12:
        PIN_MuxSet(P0_12, PIOFun4_config);
        break;
      case SctInput7_P0_17:
        PIN_MuxSet(P0_17, PIOFun3_config);
        break;
      default:
        break;
    }
}


/*!
  * @brief    SCT PWM输出引脚配置
  *
  * @param    SCT0_Chn  : PWM输出通道
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      SCT_PwmPinInit(SctOutPut0_P0_2); //初始化 P0_2 功能复用为SCT输出
  *
  * @date     2019/5/8 星期三
  */
void SCT_PwmPinInit(SCT0_OutChnannel_t SCT0_Chn)
{   
    uint32_t PIOFun2_config = FUNC2|MODE_Down|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun3_config = FUNC3|MODE_Down|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun4_config = FUNC4|MODE_Down|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    
    /* 开启 时钟 */
    CLOCK_EnableClock(kCLOCK_Iocon);
    
    switch(SCT0_Chn)
    {
      case SctOutPut0_P0_2:
        IOCON_PinMuxSet(IOCON, 0, 2, PIOFun3_config);
        break;
      case SctOutPut0_P0_17:
        IOCON_PinMuxSet(IOCON, 0,17, PIOFun4_config);
        break;
      case SctOutPut0_P1_4:
        IOCON_PinMuxSet(IOCON, 1, 4, PIOFun4_config);
        break;
      case SctOutPut0_P1_23:
        IOCON_PinMuxSet(IOCON, 1, 23, PIOFun2_config);
        break;
      case SctOutPut1_P0_3:
        IOCON_PinMuxSet(IOCON, 0, 3, PIOFun3_config);
        break;
      case SctOutPut1_P0_18:
        IOCON_PinMuxSet(IOCON, 0,18, PIOFun4_config);
        break;
      case SctOutPut1_P1_8:
        IOCON_PinMuxSet(IOCON, 1, 8, PIOFun4_config);
        break;
      case SctOutPut1_P1_24:
        IOCON_PinMuxSet(IOCON, 1,24, PIOFun2_config);
        break;
      case SctOutPut2_P0_15:
        IOCON_PinMuxSet(IOCON, 0, 15, PIOFun4_config);
        break;
      case SctOutPut2_P0_19:
        IOCON_PinMuxSet(IOCON, 0, 19, PIOFun4_config);
        break;
      case SctOutPut2_P1_9:
        IOCON_PinMuxSet(IOCON, 1, 9, PIOFun4_config);
        break;
      case SctOutPut2_P1_25:
        IOCON_PinMuxSet(IOCON, 1, 25, PIOFun2_config);
        break;
      case SctOutPut3_P0_22:
        IOCON_PinMuxSet(IOCON, 0, 22, PIOFun4_config);
        break;
      case SctOutPut3_P0_31:
        IOCON_PinMuxSet(IOCON, 0, 31, PIOFun4_config);
        break;
      case SctOutPut3_P1_10:
        IOCON_PinMuxSet(IOCON, 1, 10, PIOFun4_config);
        break;
      case SctOutPut3_P1_26:
        IOCON_PinMuxSet(IOCON, 1, 26, PIOFun2_config);
        break;
      case SctOutPut4_P0_23:
        IOCON_PinMuxSet(IOCON, 0, 23, PIOFun4_config);
        break;
      case SctOutPut4_P1_3:
        IOCON_PinMuxSet(IOCON, 1, 3, PIOFun4_config);
        break;
      case SctOutPut4_P1_17:
        IOCON_PinMuxSet(IOCON, 1, 17, PIOFun4_config);
        break;
      case SctOutPut5_P0_26:
        IOCON_PinMuxSet(IOCON, 0, 26, PIOFun4_config);
        break;
      case SctOutPut5_P1_18:
        IOCON_PinMuxSet(IOCON, 1, 18, PIOFun4_config);
        break;
      case SctOutPut6_P0_27:
        IOCON_PinMuxSet(IOCON, 0, 27, PIOFun4_config);
        break;
      case SctOutPut6_P1_31:
        IOCON_PinMuxSet(IOCON, 1, 31, PIOFun4_config);
        break;
      case SctOutPut7_P0_28:
        IOCON_PinMuxSet(IOCON, 0, 28, PIOFun4_config);
        break;
      case SctOutPut7_P1_19:
        IOCON_PinMuxSet(IOCON, 1, 19, PIOFun2_config);
        break;
      case SctOutPut8_P0_29:
        IOCON_PinMuxSet(IOCON, 0, 29, PIOFun4_config);  
        break;
      case SctOutPut9_P0_30:
        IOCON_PinMuxSet(IOCON, 0, 30, PIOFun4_config);      
        break;
    }
}


