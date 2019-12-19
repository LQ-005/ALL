/*!
  * @file     TEST_PWM.c
  *
  * @brief    PWM测试
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.0   2019/11/27  修改硬件SPI初始化函数
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "config.h"
#include "TEST_PWM.h"
#include "LQ_CTIME.h"
#include "LQ_SCTIME.h"
#include "LQ_KEY.h"
#include "LQ_LED.h"
#include "LQ_SGP18T.h"
#include "LQ_12864.h"
#include "LQ_UART.h"
#include "stdio.h"
#include "fsl_debug_console.h"
/* 声明外部延时函数 */
extern void delayms(uint16_t ms);


/**
  * @brief    设置舵机占空比
  *
  * @param    duty          ：占空比*SCT_PWM_MAX   
  *
  * @return   
  *
  * @note      舵机中值 1.5ms高电平的PWM波    限幅在 1.3 - 1.7ms之间
  *
  * @example  PWM_SetServoDuty(700);  //设置占空比百分之  700/SCT_PWM_MAX * 100
  *
  * @date     2019/5/23 星期四
  */
void PWM_SetServoDuty(uint16_t duty)    
{
    if(duty > 850) duty = 850;    //限幅，可自行修改
    if(duty < 650) duty = 650;
    CTIMER_SetDuty(CT1Output0_P1_10, duty);
}

/*!
  * @brief    测试舵机PWM
  *
  * @param    
  *
  * @return   
  *
  * @note     初次使用此函数时，舵机不要装舵盘，防止舵机卡死，设置中值后再装车，可以自行设置中值
  *
  * @example      
  *
  * @date     2019/10/21 星期一
  */
void TEST_Servo(void)
{
    /* 舵机PWM 初始化 */
    CTIMER_InitPwmConfig(CT1Output0_P1_10, 0, 50);
    
    LED_Init();
    KEY_Init();
    UART_InitConfig(USART0, 115200);
#ifdef TFT1_8
    TFTSPI_Init(1);                //TFT1.8初始化  
    TFTSPI_CLS(u16BLUE);           //清屏
    TFTSPI_P8X16Str(3,0,"LQ Motor PWM",u16RED,u16BLUE);
#else
    LCD_Init();
    LCD_CLS();                     //LCD清屏  
    LCD_P8x16Str(13,0,"LQ Servo PWM");
#endif

    char txt[16];
    int servopwm = 750; 
    float time = 0;
    
    while (1)
    {      
        switch(KEY_Read(1))  //检测按键 mode:0单按，mode:1连按
        {
            case 0:
            break;
            case 1:
                servopwm -= 10;   
				if(servopwm < 650) servopwm = 650;     //限幅，可自行修改
                PWM_SetServoDuty(servopwm);//刷新servopwm频率
                break;           
            case 2:           
                servopwm = 750;
                PWM_SetServoDuty(servopwm);//刷新servopwm频率
                break;
            case 3:           
                servopwm += 10;
				if(servopwm > 850) servopwm = 850; 
                PWM_SetServoDuty(servopwm);//刷新servopwm频率
                break;
        }
        time=(servopwm)*20.0/10000;
        sprintf(txt,"Time:%4.3fms",time);
#ifdef TFT1_8        
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);
#else        
        LCD_P8x16Str(2,3,txt);
#endif  
        printf(txt); 
        
        //LED闪烁
        LED_ColorReverse(red);      
        delayms(50);
    }
    
}


/*!
  * @brief    电机控制函数
  *
  * @param    num： 1：电机1： 使用 P0_26  P1_17   
                    2：电机2： 使用 P0_28  P0_27  
                    3：电机3： 使用 P0_19  P0_22   
                    4：电机4： 使用 P0_18  P0_17
  * @param    duty: 占空比  范围：-SCT_PWM_MAX  ---  SCT_PWM_MAX   
  *
  * @return   
  *
  * @note     电机不分正负
  *
  * @see      PWM_SetMotorDuty(1, -2000);  //电机1 反转 设置占空比百分之 2000/SCT_PWM_MAX * 100
  *
  * @date     2019/10/31 星期四
  */
void PWM_SetMotorDuty(uint8_t num, short duty)
{
    /* 防止PWM越界 */
    assert(abs(duty) < SCT_PWM_MAX);
    switch(num)
    {
      case 1:
        {
            if(duty > 0)
            {
                SCT_PwmSetDuty(SctOutPut5_P0_26, 0);
                SCT_PwmSetDuty(SctOutPut4_P1_17, duty);
            }
            else
            {
                SCT_PwmSetDuty(SctOutPut5_P0_26, -duty);
                SCT_PwmSetDuty(SctOutPut4_P1_17, 0);
            }
        }
        break;
        
        case 2:
        {
            if(duty > 0)
            {
                SCT_PwmSetDuty(SctOutPut7_P0_28, 0);
                SCT_PwmSetDuty(SctOutPut6_P0_27, duty);
            }
            else
            {
                SCT_PwmSetDuty(SctOutPut7_P0_28, -duty);
                SCT_PwmSetDuty(SctOutPut6_P0_27, 0);
            }
        }
        break;
        
        case 3:
        {
            if(duty > 0)
            {
                SCT_PwmSetDuty(SctOutPut2_P0_19, 0);
                SCT_PwmSetDuty(SctOutPut3_P0_22, duty);
            }
            else
            {
                SCT_PwmSetDuty(SctOutPut2_P0_19, -duty);
                SCT_PwmSetDuty(SctOutPut3_P0_22, 0);
            }
        }
        break;
        
        case 4:
        {
            if(duty > 0)
            {
                SCT_PwmSetDuty(SctOutPut1_P0_18, 0);
                SCT_PwmSetDuty(SctOutPut0_P0_17, duty);
            }
            else
            {
                SCT_PwmSetDuty(SctOutPut1_P0_18, -duty);
                SCT_PwmSetDuty(SctOutPut0_P0_17, 0);
            }
        }
        break;
    }

}

/*!
  * @brief    测试电机
  *
  * @param    
  *
  * @return   
  *
  * @note      1：电机1： 使用 P0_26  P1_17   
               2：电机2： 使用 P0_28  P0_27  
               3：电机3： 使用 P0_19  P0_22   
               4：电机4： 使用 P0_18  P0_17   
  *
  * @example   按键 K1按下 电机停止  K0、K2按下，电机加减速
  *
  * @date     2019/10/31 星期四
  */
void TEST_MOTOR(void)
{
    /* 初始化PWM */
    SCT_InitPwmConfig(SctOutPut0_P0_17, 18000, 0);
    SCT_InitPwmConfig(SctOutPut1_P0_18, 18000, 0);
    SCT_InitPwmConfig(SctOutPut2_P0_19, 18000, 0);
    SCT_InitPwmConfig(SctOutPut3_P0_22, 18000, 0);
    SCT_InitPwmConfig(SctOutPut4_P1_17, 18000, 0);
    SCT_InitPwmConfig(SctOutPut5_P0_26, 18000, 0);
    SCT_InitPwmConfig(SctOutPut6_P0_27, 18000, 0);
    SCT_InitPwmConfig(SctOutPut7_P0_28, 18000, 0);
    
    LED_Init();
    KEY_Init();
    UART_InitConfig(USART0, 115200);
#ifdef TFT1_8
    TFTSPI_Init(1);                //TFT1.8初始化  
    TFTSPI_CLS(u16BLUE);           //清屏
    TFTSPI_P8X16Str(3,0,"LQ Motor PWM",u16RED,u16BLUE);
#else
    LCD_Init();
    LCD_CLS();                     //LCD清屏  
    LCD_P8x16Str(13,0,"LQ Servo PWM");
#endif
    char txt[16];
    short motorpwm=0;   
    
    while (1)
    {        
        switch(KEY_Read(1))  //检测按键
        {
            case 0:
                break;
            case 1:
                motorpwm -= 100;
                if(motorpwm < -10000) motorpwm = -10000;
                PWM_SetMotorDuty(1, motorpwm);
                PWM_SetMotorDuty(2, motorpwm);
                PWM_SetMotorDuty(3, motorpwm);
                PWM_SetMotorDuty(4, motorpwm);
                break;           
            case 3:           
                motorpwm += 100;
                if(motorpwm > 10000) motorpwm = 10000;
                PWM_SetMotorDuty(1, motorpwm);
                PWM_SetMotorDuty(2, motorpwm);
                PWM_SetMotorDuty(3, motorpwm);
                PWM_SetMotorDuty(4, motorpwm);
                break;
            case 2:
                motorpwm = 0;
                PWM_SetMotorDuty(1, motorpwm);
                PWM_SetMotorDuty(2, motorpwm);
                PWM_SetMotorDuty(3, motorpwm);
                PWM_SetMotorDuty(4, motorpwm);
            break;
        }
        
        sprintf(txt,"PWM: %4.2f %%",motorpwm/100.0f);
#ifdef TFT1_8        
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);
#else        
        LCD_P8x16Str(2,3,txt);
#endif       
        printf(txt); 
        
        //LED闪烁
        LED_ColorReverse(red);     
        delayms(50);
    }
}
