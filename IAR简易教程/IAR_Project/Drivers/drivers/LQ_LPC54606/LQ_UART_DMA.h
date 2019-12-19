/*!
  * @file     LQ_UART_DMA.h
  *
  * @brief    串口DMA驱动
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
  * @date     2019/10/29 星期二
  */ 
#ifndef __LQ_UART_DMA_H
#define __LQ_UART_DMA_H
#include "fsl_usart_dma.h"

/* 串口+DMA 标志位 */
extern volatile bool rxBufferEmpty;  /** 接收空 */
extern volatile bool txBufferFull;   /** 发送满 */
extern volatile bool txOnGoing;      /** 正在发送 */
extern volatile bool rxOnGoing;      /** 正在接收 */

/* DMA 传输结构体 */
extern usart_transfer_t sendXfer;    /** 串口DMA发送传输结构体 */
extern usart_transfer_t receiveXfer; /** 串口DMA接收传输结构体 */

/* 串口 + DMA 配置结构体 */
extern usart_dma_handle_t g_uartDmaHandle; /** 串口DMA句柄 */

/**
  * @brief    串口DMA传输初始化
  *
  * @param    base  ： USART0 - USART8
  * @param    bound ： 串口波特率
  *
  * @return   无
  *
  * @note     DMA 收发 注意摄像头会占用前面通道 如果使用摄像头 
  * @note     会占用DMA通道CAMERA_DMA_CH --- CAMERA_DMA_CH + 22 的通道描述符(DMA最大30个通道描述符)
  * @note     dma_request_source_t 中查看对应通道是否被摄像头占用 
  *
  * @see      UART_DMAInitConfig(USART0, 115200, 29, 28);  //初始化串口0 + DMA
  *
  * @date     2019/6/6 星期四
  */
void UART_DMAInitConfig(USART_Type *base, uint32_t bound);

#endif
