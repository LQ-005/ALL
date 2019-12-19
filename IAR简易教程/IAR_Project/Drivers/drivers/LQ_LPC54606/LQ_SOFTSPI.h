/*!
  * @file     LQ_SOFTSPI.h
  *
  * @brief    模拟SPI驱动
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
  * @date     2019/10/19 星期六
  */ 
#ifndef __LQ_SOFTSPI_H
#define __LQ_SOFTSPI_H

#include "fsl_common.h" 
#include "LQ_GPIO.h"

/* 注意 ICM20602 时钟空闲时为高电平  在时钟第二个跳边沿传输数据  与NRF2401的不同，所以SPI不通用  */
/*! 0: 时钟空闲时刻为低电平   1：时钟空闲时刻为高电平*/ 
#define CPOL  1

/*! 0：时钟第一个跳边沿传输数据   1：时钟的第二个跳边沿传输数据 */
#define CPHA  1 


#define SOFT_SPI_SCK_PIN    P0_6   /*!< 模拟SPI SCK管脚 */
#define SOFT_SPI_MISO_PIN   P0_2   /*!< 模拟SPI MISO管脚 */
#define SOFT_SPI_MOSI_PIN   P0_3   /*!< 模拟SPI MOSI管脚 */
#define SOFT_SPI_CS_PIN     P0_20  /*!< 模拟SPI CS管脚 */


#if CPOL
#define SPI_SCK_IDLE      PIN_Write(SOFT_SPI_SCK_PIN, 1); 
#define SPI_SCK_ACTIVE    PIN_Write(SOFT_SPI_SCK_PIN, 0); 
#else
#define SPI_SCK_IDLE      PIN_Write(SOFT_SPI_SCK_PIN, 0); 
#define SPI_SCK_ACTIVE    PIN_Write(SOFT_SPI_SCK_PIN, 1); 
#endif

#define SPI_MOSI_OUT(x)   PIN_Write(SOFT_SPI_MOSI_PIN, x); 
#define SPI_MISO_IN       PIN_Read(SOFT_SPI_MISO_PIN);
#define SPI_CS_OUT(x)     PIN_Write(SOFT_SPI_CS_PIN, x); 


/*!
  * @brief    模拟SPI初始化
  *
  * @param    无
  *
  * @return   无
  *
  * @note     模拟SPI使用管脚 LQ_SOFTSPI.h中宏定义
  *
  * @see      SPI_SoftInit();  //模拟SPI管脚初始化
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftInit(void);


/*!
  * @brief    模拟SPI读写n 字节
  *
  * @param    buff[] 存放要写入的值 写入后存放读取的值
  *
  * @return   无
  *
  * @note     无
  *
  * @see      uint8_t data[8];
  * @see      SPI_SoftRadeWriteNbyte(data, sizeof(data)); //SPI读写8个字节
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len);

#endif
