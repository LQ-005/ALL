/*!
  * @file     TEST_UART.h
  *
  * @brief    串口测试文件
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
#ifndef __TEST_UART_H
#define __TEST_UART_H

/*!
  * @brief    串口测试例程
  *
  * @param    无
  *
  * @return   无
  *
  * @note     
  *
  * @example      
  *
  * @date     2019/10/31 星期四
  */
void Test_UART(void);



/**
  * @brief    串口 + DMA 测试函数
  *
  * @param    无
  *
  * @return   无
  *
  * @note     接收USART_DMA_LEN个数据， 并打印出来 注意会调用回调函数，不要自己写串口中断服务函数
  * @note     摄像头默认占用 DMA通道CAMERA_DMA_CH --- CAMERA_DMA_CH + 22  默认串口0、串口1可以用DMA
  *
  * @example  
  *
  * @date     2019/6/6 星期四
  */
void Test_UART_DMA(void);

#endif
