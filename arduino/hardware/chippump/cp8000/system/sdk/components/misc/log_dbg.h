/*************************************************************************************************
 * @file       log_dbg.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __LOG_DBG_H__
#define __LOG_DBG_H__

#include <stdint.h>
#include <stdarg.h>
#include "config.h"



#define LOG_UART            UART0

#define LOG_UART_RX_PIN     GPIO_PIN8
#define LOG_UART_TX_PIN     GPIO_PIN9
#define LOG_UART_RX_FUNC    GPIO8_UART0_RX
#define LOG_UART_TX_FUNC    GPIO9_UART0_TX
#define LOG_UART_BAUDRATE   115200


#define DEBUG_STRING_LOG_SINGLE_LINE_MAX_SIZE   (200)

// Macro POINT
#define POINT_BUFFER_CNT (200)

typedef struct
{
    uint8_t wptr;
    uint8_t rptr;
    uint32_t buf[POINT_BUFFER_CNT];
}DBG_POINT_CACHE_INFO;

void log_dbg_init(void);

void log_printf(const char *format, ...);

#endif
