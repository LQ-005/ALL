/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "LPCXPRESSO54608"

#define BOARD_EXTCLKINRATE (0)

/*! @brief The UART to use for debug messages. */
/* TODO: rename UART to USART */
#define BOARD_DEBUG_UART_TYPE kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) USART0     /* debug 串口想要换成其他 更改这里即可 串口使用的具体管脚 在LQ_UART.h宏定义选择*/
#define BOARD_DEBUG_UART_INSTANCE 0U                    /* debug 串口标号 */
#define BOARD_DEBUG_UART_CLK_FREQ CLOCK_GetFreq(kCLOCK_Flexcomm0)/* debug 串口使用时钟*/
#define BOARD_DEBUG_UART_CLK_ATTACH kFRO12M_to_FLEXCOMM0/* debug 串口时钟 */
#define BOARD_DEBUG_UART_RST kFC0_RST_SHIFT_RSTn        /* debug 串口复位控制 */
#define BOARD_DEBUG_UART_CLKSRC kCLOCK_Flexcomm0        /* debug 串口时钟 */
#define BOARD_UART_IRQ_HANDLER FLEXCOMM0_IRQHandler     /* debug 串口中断服务函数 */
#define BOARD_UART_IRQ FLEXCOMM0_IRQn                   /* debug 串口中断向量号 */
/* TODO: obsolete */

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200                /* debug 串口波特率 */
#endif /* BOARD_DEBUG_UART_BAUDRATE */



#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

status_t BOARD_InitDebugConsole(void);


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
