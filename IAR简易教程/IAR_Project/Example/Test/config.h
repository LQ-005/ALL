/*!
  * @file     config.h
  *
  * @brief    这是一个配置文件 存放一些全局宏定义
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.0
  *
  * @Software IAR8.22 or MDK5.25
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/28 星期一
  */ 

#ifndef __CONFIG_H
#define __CONFIG_H

/* 中断开关宏定义 */
#define EnableInterrupts  __asm(" CPSIE i");//开总中断
#define DisableInterrupts __asm(" CPSID i");//关总中断


/* 这里主要存放一些全局宏定义 */

/* 显示屏幕 */
//#define OLED
//#define TFT1_8

/* 使用摄像头 */
//#define LQMT9V034    //使用神眼


/* MPU6050   只能使用 硬件IIC 和软件IIC */
/* ICM20602  能使用 硬件IIC 和软件IIC  硬件SPI 和软件SPI */
/* 龙邱九轴  只能使用 硬件IIC 和软件IIC */
/* 宏定义 使用不同的接线方式 */
#define USE_HAL_SPI  0    /* 硬件SPI */
#define USE_SOFT_SPI 1    /* 模拟SPI */
#define USE_SOFT_IIC 2    /* 模拟IIC */
#define USE_HAL_IIC  3    /* 硬件IIC */

/* MPU6050/ICM20602/龙邱九轴 选择使用?IIC */
//#define IMU_USE_SELECT  USE_HAL_IIC

/* VL53 使用？IIC */
//#define VL53_USE_SELECT USE_SOFT_IIC

/* ICM20602 选择使用 SPI */
//#define ICM_USE_SELECT  USE_SOFT_SPI

/* 是否使用DMA方式发送数据给匿名上位机 */
//#define ANO_DT_USE_DMA  1



#endif
