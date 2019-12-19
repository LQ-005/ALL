/*!
  * @file     LQ_UART_DMA.c
  *
  * @brief    串口DMA驱动
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
  * @date     2019/10/29 星期二
  */ 
#include "LQ_UART_DMA.h"
#include "LQ_UART.h"
#include "fsl_usart_dma.h"

/* 串口+DMA 标志位 */
volatile bool rxBufferEmpty = true;   /** 接收空 */
volatile bool txBufferFull = false;   /** 发送满 */
volatile bool txOnGoing = false;      /** 正在发送 */
volatile bool rxOnGoing = false;      /** 正在接收 */


/**
  * @brief    串口+DMA 的回调函数  当串口发送完成或者接受完成，会自动调用该函数
  *
  * @param    用户无需关系参数问题
  *
  * @return   无
  *
  * @note     如果使用回调函数，不能自己定义相应的中断服务函数
  *
  * @see      无
  *
  * @date     2019/6/15 星期六
  */
void USART_UserCallback(USART_Type *base, usart_dma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_USART_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing    = false;
    }

    if (kStatus_USART_RxIdle == status)
    {
        rxBufferEmpty = false;
        rxOnGoing     = false;
    }
}


/* 串口 + DMA 配置结构体 */
usart_dma_handle_t g_uartDmaHandle;  /** 串口DMA句柄 */
dma_handle_t g_uartTxDmaHandle;      /** DMA发送句柄 */
dma_handle_t g_uartRxDmaHandle;      /** DMA接收句柄 */

/* DMA 传输结构体 */
usart_transfer_t sendXfer;           /** 串口DMA发送传输结构体 */
usart_transfer_t receiveXfer;        /** 串口DMA接收传输结构体 */


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
void UART_DMAInitConfig(USART_Type *base, uint32_t bound)
{
    /* 初始化串口对应的管脚 对应管脚在LQ_UART.h 中通过宏定义确定 */
    UART_InitConfig(base, bound);
    
    /* 关闭接收中断 */
    USART_DisableInterrupts(base, kUSART_RxLevelInterruptEnable);
    
    uint8_t temp = USART_GetInstance(base);
    
    uint8_t RX_channel = 0;
    
    if(temp > 7)
    {
        RX_channel = (kDmaRequestFlexcomm8Rx + (temp - 8)*2);
    }
    else
    {
        RX_channel = (kDmaRequestFlexcomm0Rx + temp *2);
    }
    
    
    /* 使能DMA */
    DMA_Init(DMA0);
    DMA_EnableChannel(DMA0, RX_channel);
    DMA_EnableChannel(DMA0, RX_channel + 1);

    /* 创建DMA句柄 .*/
    DMA_CreateHandle(&g_uartRxDmaHandle, DMA0, RX_channel);
    DMA_CreateHandle(&g_uartTxDmaHandle, DMA0, RX_channel + 1);

    /* 创建USART_DMA句柄 .*/
    USART_TransferCreateHandleDMA(base, &g_uartDmaHandle, USART_UserCallback, NULL, &g_uartTxDmaHandle,
                                  &g_uartRxDmaHandle);
    
    
}









