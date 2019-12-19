/*!
  * @file     TEST_UART.c
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
#include "fsl_debug_console.h"
#include "stdio.h"
#include "stdlib.h"
#include "LQ_UART.h"
#include "LQ_UART_DMA.h"
#include "LQ_LED.h"
#include "TEST_UART.h"

/* 声明外部延时函数 */
extern void delayms(uint16_t ms);


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
void Test_UART(void)
{
    /* 初始化串口0 */
    UART_InitConfig(USART0, 115200);
    
    /* 初始化串口4 */
    UART_InitConfig(USART3, 115200);
    
    /* 使能串口0接收中断 */
    //优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级高的可打断抢占优先级低的中断
    NVIC_SetPriority(FLEXCOMM0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(FLEXCOMM0_IRQn);  //使能中断  FLEXCOMM0用作USART0了，所以使能中断使能的是FLEXCOMM0

    /* 使能串口3接收中断 */
    //优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级高的可打断抢占优先级低的中断
    NVIC_SetPriority(FLEXCOMM3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(FLEXCOMM3_IRQn);  //使能中断  FLEXCOMM3用作USART3了，所以使能中断使能的是FLEXCOMM3
    
    /* printf 使用串口0 可以在LQ_UART.c中修改 fputc 函数修改printf的串口 */
    printf("\n\r串口打印测试\n\r");
    
    while(1)
    {
        UART_PutStr(USART0, "123456789\r\n");
        UART_PutStr(USART3, "123456789\r\n");
        
        UART_PutBuff(USART0, "123456789",5);
        UART_PutBuff(USART3, "123456789",5);
        
        /* 发送换行 */
        UART_PutChar(USART3, 0x0d);
        
        printf("\n\r串口打印测试\n\r");
        delayms(2000);
    }
}







//                       .::::.
//                     .::::::::.
//                    :::::::::::
//                 ..:::::::::::'
//              '::::::::::::'
//                .::::::::::
//           '::::::::::::::..
//                ..::::::::::::.
//              ``::::::::::::::::
//               ::::``:::::::::'        .:::.
//              ::::'   ':::::'       .::::::::.
//            .::::'      ::::     .:::::::'::::.
//           .:::'       :::::  .:::::::::' ':::::.
//          .::'        :::::.:::::::::'      ':::::.
//         .::'         ::::::::::::::'         ``::::.
//     ...:::           ::::::::::::'              ``::.
//    ```` ':.          ':::::::::'                  ::::..
//                       '.:::::'                    ':'````..
/*************************************************************************/
/*************************************************************************/
/***************************DMA测试例程***********************************/
/*************************************************************************/
/*************************************************************************/


/*! DMA收发长度 */
#define USART_DMA_LEN  10



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
void Test_UART_DMA(void)
{
    /* 串口收发 缓冲区 */
    uint8_t g_txBuffer[USART_DMA_LEN] = {0};
    uint8_t g_rxBuffer[USART_DMA_LEN] = {0};

    LED_Init();   
    
    /* 初始化 串口0 */
    UART_DMAInitConfig(USART0, 115200);   
    
    //优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(FLEXCOMM0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(FLEXCOMM0_IRQn);	                            //使能FLEXCOMM0_IRQn中断
	
    delayms(100);
    PRINTF("\r\n龙邱串口测试例程\r\n");
    PRINTF("串口模块波特率:\n");
    PRINTF("LPUART1 init: 115200!\n"); 
    
    /* 接收配置 */
    receiveXfer.data = g_rxBuffer;              //接收数据存放位置
    receiveXfer.dataSize = USART_DMA_LEN;       //接收数据长度
    
    /* 发送配置 */
    sendXfer.data    = g_txBuffer;              //发送数据存放位置
    sendXfer.dataSize = USART_DMA_LEN;          //发送数据长度
    while(1)
    {
        
        /* 接收到数据，并且已经copy到发送缓冲区发送出去. */
        if ((!rxOnGoing) && rxBufferEmpty)
        {
            rxOnGoing = true;
            
            /* 开启DMA 接收 */
            USART_TransferReceiveDMA(USART0, &g_uartDmaHandle, &receiveXfer);
        }

        /* 接收完成后，发送出去. */
        if ((!txOnGoing) && txBufferFull)
        {
            txOnGoing = true;

            /* 使能发送 */
            USART_TransferSendDMA(USART0, &g_uartDmaHandle, &sendXfer);
        }

        /* 接收到一帧数据后，从接收字符缓冲区copy到发送缓冲区. */
        if ((!rxBufferEmpty) && (!txBufferFull))
        {
            memcpy(g_txBuffer, g_rxBuffer, USART_DMA_LEN);
            rxBufferEmpty = true;
            txBufferFull = true;
            LED_ColorReverse(blue);
        }
        
    }  
}


