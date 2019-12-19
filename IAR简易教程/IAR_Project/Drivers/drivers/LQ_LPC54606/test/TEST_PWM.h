/*!
  * @file     TEST_PWM.h
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
#ifndef __TEST_PWM_H
#define __TEST_PWM_H
#include "stdint.h"

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
void PWM_SetServoDuty(uint16_t duty);


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
void TEST_Servo(void);


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
void PWM_SetMotorDuty(uint8_t num, short duty);



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
void TEST_MOTOR(void);



#endif
