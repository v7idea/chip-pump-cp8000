/*************************************************************************************************
 * @file       driver_uart.c
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
 #include <stdint.h>
#include "mcu.h"
#include "driver_gpio.h"
#include "driver_uart.h"

/**
 * @brief Get current UART clock frequency
 * @return Clock frequency in Hz (24MHz or 48MHz)
 * 
 * @note Checks SYS_CLKSEL register configuration
 */
uint32_t get_uart_clk(void)
{
    if( SYS_CTRL->SYS_CLKSEL_b.REG_UART_CLK_SEL == 2)
    {
        return 48000000;
    }
    else
    {
        return 24000000;
    }
}

/**
 * @brief Switch UART clock source
 * @param new_clk_val 2-bit clock selection value
 * 
 * @warning Must be called within atomic section
 */
void uart_clk_config(uint8_t clk_div)
{
    SYS_CTRL->SYS_CLKSEL_b.REG_UART_CLK_SEL = clk_div;
}

/**
 * @brief Wait until specified UART interface becomes idle
 * 
 * This function polls the UART status register until the BUSY flag is cleared.
 * During waiting period, automatically handles received data in FIFO to prevent overflow.
 * 
 * @param uartx UART module selection enum (UART0/UART1) that specifies peripheral instance
 */
void uart_wait_not_busy(UART_Sel_e uartx)
{
	UART_Type *UARTx = (UART_Type*)uartx;

    while(UARTx->USR_b.BUSY)
    {
        if (UARTx->LSR_b.DR)
        {
            UARTx->RBR;
        }
    }
}

/**
 * @brief Configure UART baud rate
 * @param uartx UART module selection enum (UART0/UART1) that specifies peripheral instance
 * @param baudrate Target baud rate (2400-3000000)
 * 
 * @sequence
 * 1. Calculate divisor: (clock_hz / (16 * baudrate)) 
 * 2. Set Divisor Latch Access Bit (DLAB)
 * 3. Program DLL/DLH/DLF registers
 * 4. Clear DLAB
 */
void uart_set_baudrate(UART_Sel_e uartx, UART_BAUDRATE_E baudrate)
{
	UART_Type *UARTx = (UART_Type*)uartx;

    int divisor = ((get_uart_clk() / baudrate) >> 4);
	
	int fract = (get_uart_clk() / baudrate)&0xF;
	
    //Set Divisor Latch Access Bit (DLAB)
    UARTx->LCR_b.DLAB = 1;

    /* DLL and DLH is lower 8-bits and higher 8-bits of cfg_val.*/
    UARTx->DLL = divisor & 0xff;
    UARTx->DLH = (divisor >> 8) & 0xff;
    UARTx->DLF = fract;
    
    //Clear DLAB
    UARTx->LCR_b.DLAB = 0;
}

/**
 * @brief Initialize UART peripheral
 * @param uartx UART module selection enum (UART0/UART1) that specifies peripheral instance
 * @param baudrate Configured baud rate
 * 
 * @details Configures:
 * - 8 data bits, 1 stop bit, no parity
 * - FIFO enabled with selected trigger level
 * - Receiver interrupt enabled
 */
void uart_init(UART_Sel_e uartx, UART_BAUDRATE_E baudrate)
{
	UART_Type *UARTx = (UART_Type*)uartx;
    
    //Clock select: 24MHz
    SYS_CTRL->SYS_CLKSEL_b.REG_UART_CLK_SEL = 1;

    //make uart device in idle state before starting to config
	uint8_t uart_id =(uartx == UART0)?0:1;    //modify, 20250502
	RESET_UART(uart_id);
    
    //Baudrate config
    uart_set_baudrate(uartx, baudrate);

    //SetParity: NONE
    UARTx->LCR &= (~LCR_PARITY_ENABLE);

    //SetWordSize: LCR_WORD_SIZE_8
    UARTx->LCR |= LCR_WORD_SIZE_8;

    //SetStopBit: LCR_STOP_BIT_1
    UARTx->LCR &= LCR_STOP_BIT1;

    //SetRXMode: INT mode
    UARTx->IER_b.ERBFI = 0;

    //SetTXMode: Query mode

    UARTx->IER_b.ETBEI = 0;
    //SetFIFOMode
    UARTx->FCR_b.FIFOE = 0x1;
    UARTx->FCR_b.RT = 1;
    
    uint32_t irq_n  = (uartx == UART0)?UART0_IRQn:UART1_IRQn;
    NVIC_SetPriority(irq_n, IRQ_HIGH_PRIORITY);
    NVIC_EnableIRQ(irq_n);
}

void uart_int_enable(UART_Sel_e uartx,uint8_t tx_int_enable,uint8_t rx_int_enable)
{
	UART_Type *UARTx = (UART_Type*)uartx;

    if(tx_int_enable)
    {
        //SetTXMode: Query mode
        UARTx->IER |= IER_THRE_INT_ENABLE;
    }
    else 
    {
        //SetTXMode: Query mode
        UARTx->IER &= (~IER_THRE_INT_ENABLE);
    }

    if(rx_int_enable)
    {
        //SetTXMode: Query mode
        UARTx->IER |= IER_RDA_INT_ENABLE;
    }
    else 
    {
        //SetTXMode: Query mode
        UARTx->IER &= (~IER_RDA_INT_ENABLE);
    }
}

/**
 * @brief Transmit single character
 * @param uartx UART module selection enum (UART0/UART1) that specifies peripheral instance
 * @param c Character to send
 * 
 * @note Implements timeout to prevent infinite blocking
 */
void uart_putchar(UART_Sel_e uartx,uint8_t c)
{
    uint32_t uart_timecount =0;
	UART_Type *UARTx = (UART_Type*)uartx;

    while( !(UARTx->LSR & LSR_THRE) )
    {
        uart_timecount++;
        if(uart_timecount > UART_BUSY_TIMEOUT)
        {
            return;
        }
    }
    UARTx->THR = c;
}
void uart_send(UART_Sel_e uartx, void * pdata, uint32_t len)
{
	UART_Type *UARTx = (UART_Type*)uartx;
    uint8_t  *ptmp = pdata;
    uint32_t pos = 0;

    while (pos < len)
    {
        while (!(UARTx->LSR& LSR_TRANS_EMPTY));

        UARTx->THR = ptmp[pos++];
    }
}

/**
 * @brief Receive single character (blocking)
 * @param uartx UART module selection enum (UART0/UART1) that specifies peripheral instance
 * @return Received character
 */
uint8_t uart_getchar(UART_Sel_e uartx)
{
	UART_Type *UARTx = (UART_Type*)uartx;
//    while(UARTx->LSR& LSR_DATA_READY)
    return UARTx->RBR;
}

uint8_t uart_get_status(UART_Sel_e uartx)
{
	UART_Type *UARTx = (UART_Type*)uartx;

    return UARTx->LSR;
}
uint8_t uart_get_state(UART_Sel_e uartx)
{
	UART_Type *UARTx = (UART_Type*)uartx;
    return UARTx->USR;
}

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
void uart_set_port(UART_Sel_e uartx,ENUM_GPIO_PIN uart_rx_pin,ENUM_GPIO_PIN uart_tx_pin)
{
    /* Configure GPIO for UART0 instance */
    if(UART0 == uartx)
    {
        gpio_set_func(uart_rx_pin,UART0_RX_FUNC|GPIO_MODE_IN_PULL_UP);
        gpio_set_func(uart_tx_pin,UART0_TX_FUNC);
    }
    /* Configure GPIO for UART1 instance */
    else if(UART1 == uartx)
    {
        gpio_set_func(uart_rx_pin,UART1_RX_FUNC|GPIO_MODE_IN_PULL_UP);
        gpio_set_func(uart_tx_pin,UART1_TX_FUNC);
    }
}