/*************************************************************************************************
 * @file       driver_uart.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_UART_H__
#define __DRIVER_UART_H__
 #include <stdint.h>
#include "mcu_reg_def.h"
#include "driver_gpio.h"

/* UART function code */
#define UART0_RX_FUNC     (8)
#define UART0_TX_FUNC     (9)
#define UART1_RX_FUNC     (10)
#define UART1_TX_FUNC     (11)

/* UART registers addr definition */
#define  UART_RBR       0x00    /* Receive Buffer Register (32 bits, R) */
#define  UART_THR       0x00    /* Transmit Holding Register (32 bits, W) */
#define  UART_DLL       0x00    /* Divisor Latch(Low)  (32 bits, R/W) */
#define  UART_IER       0x01    /* Interrupt Enable Register (32 bits, R/W) */
#define  UART_DLH       0x01    /* Divisor Latch(High) (32 bits, R/W) */
#define  UART_IIR       0x02    /* Interrupt Identity Register (32 bits, R) */
#define  UART_FCR       0x02    /* fifo Countrol Register (32 bits, W) */
#define  UART_LCR       0x03    /* Line Control Register (32 bits, R/W) */
#define  UART_MCR       0x04    /* Modem Control Register (32 bits, W) */
#define  UART_LSR       0x05    /* Line Status Register (32 bits, R) */
#define  UART_MSR       0x06    /* Modem Status Register (32 bits, R/W) */
#define  UART_USR       0x1f    /* UART Status Register (32 bits, R/W) */
#define  UART_DLF       0x30    /* UART Divisor Latch(Float)(4 bits, R/W) */
#define  UART_LCR_EXT   0x33    /* UART Divisor Latch(Float)(4 bits, R/W) */

#define  UART_BUSY_TIMEOUT      1000000
#define  UART_RECEIVE_TIMEOUT   1000
#define  UART_TRANSMIT_TIMEOUT  1000

/* UART register bit definitions */
#define  USR_UART_BUSY           0x01
#define  LSR_DATA_READY          0x01
#define  LSR_THR_EMPTY           0x20
#define  IER_RDA_INT_ENABLE      0x01
#define  IER_THRE_INT_ENABLE     0x02
#define  IIR_NO_ISQ_PEND         0x01

#define  LCR_SET_DLAB            0x80   /* enable r/w DLR to set the baud rate */
#define  LCR_PARITY_ENABLE       0x08   /* parity enabled */
#define  LCR_PARITY_EVEN         0x10   /* Even parity enabled */
#define  LCR_PARITY_ODD          0xef   /* Odd parity enabled */
#define  LCR_WORD_SIZE_5         0xfc   /* the data length is 5 bits */
#define  LCR_WORD_SIZE_6         0x01   /* the data length is 6 bits */
#define  LCR_WORD_SIZE_7         0x02   /* the data length is 7 bits */
#define  LCR_WORD_SIZE_8         0x03   /* the data length is 8 bits */
#define  LCR_STOP_BIT1           0xfb   /* 1 stop bit */
#define  LCR_STOP_BIT2           0x04   /* 1.5 stop bit */

#define  LSR_PFE              0x80
#define  LSR_TEMT             0x40
#define  LSR_THRE             0x40
#define  LSR_BI               0x10
#define  LSR_FE               0x08
#define  LSR_PE               0x04
#define  LSR_OE               0x02
#define  LSR_DR               0x01
#define  LSR_TRANS_EMPTY      0x20

#define MAX_UART_NUM    2

typedef enum
{
    UART0 = 0x41001000,
    UART1 = 0x41002000
}UART_Sel_e;

typedef enum
{
    UART_BAUDRATE_2400    = 2400,
    UART_BAUDRATE_9600    = 9600,
    UART_BAUDRATE_19200   = 19200,
    UART_BAUDRATE_38400   = 38400,
    UART_BAUDRATE_57600   = 57600,
    UART_BAUDRATE_115200  = 115200,
    UART_BAUDRATE_230400  = 230400,
    UART_BAUDRATE_460800  = 460800,
    UART_BAUDRATE_921600  = 921600,
    UART_BAUDRATE_1000000 = 1000000,
    UART_BAUDRATE_1500000 = 1500000,
    UART_BAUDRATE_3000000 = 3000000
}UART_BAUDRATE_E;


/**
 * @brief Configure UART baud rate
 * @param uartx UART register base pointer
 * @param baudrate Target baud rate (2400-3000000)
 * 
 * @sequence
 * 1. Calculate divisor: (clock_hz / (16 * baudrate)) 
 * 2. Set Divisor Latch Access Bit (DLAB)
 * 3. Program DLL/DLH/DLF registers
 * 4. Clear DLAB
 */
void uart_set_baudrate(UART_Sel_e uartx, UART_BAUDRATE_E baudrate);

/**
 * @brief Initialize UART peripheral
 * @param uartx UART register base pointer
 * @param baudrate Configured baud rate
 * 
 * @details Configures:
 * - 8 data bits, 1 stop bit, no parity
 * - FIFO enabled with selected trigger level
 * - Receiver interrupt enabled
 */
void uart_init(UART_Sel_e uartx, UART_BAUDRATE_E baudrate);

void uart_int_enable(UART_Sel_e uartx,uint8_t tx_int_enable,uint8_t rx_int_enable);

/**
 * @brief Transmit single character
 * @param uartx UART register base pointer 
 * @param c Character to send
 * 
 * @note Implements timeout to prevent infinite blocking
 */
void uart_putchar(UART_Sel_e uartx, uint8_t c);
void uart_send(UART_Sel_e uartx, void * pdata, uint32_t len);

/**
 * @brief Receive single character (blocking)
 * @param uartx UART register base pointer
 * @return Received character
 */
uint8_t uart_getchar(UART_Sel_e uartx);

uint8_t uart_get_status(UART_Sel_e uartx);
uint8_t uart_get_state(UART_Sel_e uartx);

/**
 * @brief Configure GPIO pin multiplexing for specified UART instance
 * 
 * This function maps given GPIO pins to UART RX/TX functions based on selected UART instance.
 * Note: Caller must ensure the selected pins support the required UART functions
 *
 * @param uartx        UART instance selection (UART0/UART1)
 * @param uart_rx_pin  GPIO pin number to be configured as UART RX
 * @param uart_tx_pin  GPIO pin number to be configured as UART TX
 */
void uart_set_port(UART_Sel_e uartx,ENUM_GPIO_PIN uart_rx_pin,ENUM_GPIO_PIN uart_tx_pin);

#endif
