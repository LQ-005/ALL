/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "pin_mux.h"
#include <stdint.h>
#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_emc.h"
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_i2c.h"
#endif /* SDK_I2C_BASED_COMPONENT_USED */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The SDRAM timing. */
#define SDRAM_REFRESHPERIOD_NS (64 * 1000000 / 4096) /* 4096 rows/ 64ms */
#define SDRAM_TRP_NS (18u)
#define SDRAM_TRAS_NS (42u)
#define SDRAM_TSREX_NS (67u)
#define SDRAM_TAPR_NS (18u)
#define SDRAM_TWRDELT_NS (6u)
#define SDRAM_TRC_NS (60u)
#define SDRAM_RFC_NS (60u)
#define SDRAM_XSR_NS (67u)
#define SDRAM_RRD_NS (12u)
#define SDRAM_MRD_NCLK (2u)
#define SDRAM_RAS_NCLK (2u)
#define SDRAM_MODEREG_VALUE (0x23u)
#define SDRAM_DEV_MEMORYMAP (0x09u) /* 128Mbits (8M*16, 4banks, 12 rows, 9 columns)*/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Clock rate on the CLKIN pin */
const uint32_t ExtClockIn = BOARD_EXTCLKINRATE;
/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize debug console. */
status_t BOARD_InitDebugConsole(void)
{
    /* 声明 管脚初始化函数 */
    extern void UART_PinInit(USART_Type * uratn);
    UART_PinInit((USART_Type *)BOARD_DEBUG_UART_BASEADDR);
    
    status_t result;
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
    RESET_PeripheralReset(BOARD_DEBUG_UART_RST);
    result = DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE,
                             BOARD_DEBUG_UART_CLK_FREQ);
    assert(kStatus_Success == result);
    return result;
}
