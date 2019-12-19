/*!
  * @file     include.h
  *
  * @brief    包涵头文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     可以直接包涵这个头文件
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
#ifndef __INCLUDE__H
#define __INCLUDE__H

/* 常用头文件 */
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"

/* fsl 官方底层驱动库 */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_ctimer.h"
#include "fsl_dma.h"
#include "fsl_eeprom.h"
#include "fsl_flashiap.h"
#include "fsl_flexcomm.h"
#include "fsl_gint.h"
#include "fsl_gpio.h"
#include "fsl_i2c.h"
#include "fsl_inputmux.h"
#include "fsl_iocon.h"
#include "fsl_mrt.h"
#include "fsl_otp.h"
#include "fsl_pint.h"
#include "fsl_power.h"
#include "fsl_reset.h"
#include "fsl_rit.h"
#include "fsl_sctimer.h"
#include "fsl_spi.h"
#include "fsl_usart.h"
#include "fsl_usart_dma.h"
#include "fsl_wwdt.h"


/* 龙邱基于fsl库封装的智能车上层函数 */
#include "LQ_ADC.h"         /* 测量电压 */
#include "LQ_CTIME.h"       /* 输出PWM  脉冲计数 */
#include "LQ_DMA.h"         /* DMA */
#include "LQ_EEPROM.h"      /* 掉电保存数据 */
#include "LQ_GPIO.h"        /* GPIO */
#include "LQ_IIC.h"         /* 硬件IIC */
#include "LQ_MRT.h"         /* 周期中断计时器 */
#include "LQ_RIT.h"         /* 计时器 */
#include "LQ_SCTIME.h"      /* 灵活计时器 可以输出PWM */
#include "LQ_SOFTIIC.h"     /* 模拟IIC */
#include "LQ_SOFTSPI.h"     /* 模拟SPI */
#include "LQ_SPI.h"         /* 硬件SPI */
#include "LQ_SYSTICK.h"     /* systick 系统计时器 */
#include "LQ_UART.h"        /* 串口 */
#include "LQ_UART_DMA.h"    /* DMA串口 */
#include "LQ_WDOG.h"        /* 看门狗 */


///* 龙邱 外设库 */
#include "ANO_DT.h"         /* 匿名上位机通信协议 */
#include "LQ_12864.h"       /* OLED驱动 */
#include "LQ_9AX.h"         /* 九轴驱动 */
#include "LQ_CAMERA.h"      /* 摄像头驱动 */
#include "LQ_ICM20602.h"    /* ICM20602驱动 */
#include "LQ_KEY.h"         /* 按键驱动 */
#include "LQ_LED.h"         /* LED驱动 */
#include "LQ_MPU6050.h"     /* MPU6050驱动 */
#include "LQ_SGP18T.h"      /* TFT18驱动 */
#include "LQ_MT9V034.h"     /* 神眼驱动 */
#include "LQ_PROTOCOL.h"    /* 上位机通信协议 */


///* 龙邱 测试文件 */
#include "config.h"         /* 配置文件 */
#include "TEST_9AX.h"       /* 测试龙邱九轴 */
#include "TEST_ADC.h"       /* 测试ADC电压读取 */
#include "TEST_CAMERA.h"    /* 摄像头测试 */
#include "TEST_ENC.h"       /* 带方向编码器测试 */
#include "TEST_EEPROM.h"    /* 测试FLASH */
#include "TEST_ICM20602.h"  /* 测试ICM20602 SPI接线方式 */
#include "TEST_MPU6050.h"   /* 测试MPU6050/ICM20602 IIC接线方式 */
#include "TEST_MRT.h"       /* 测试MRT定时器 */
#include "TEST_RIT.h"       /* 测试RIT */
#include "TEST_PWM.h"       /* PWM输出测试 */
#include "TEST_SYSTICK.h"   /* 测试systick系统计时器 */
#include "TEST_UART.h"      /* 测试串口 */
#include "TEST_Ultrasonic.h"/* 测试超声波 */
#include "TEST_VL53.h"      /* 测试VL53 测距 */
#include "TEST_WDog.h"      /* 测试看门狗 */


#endif
