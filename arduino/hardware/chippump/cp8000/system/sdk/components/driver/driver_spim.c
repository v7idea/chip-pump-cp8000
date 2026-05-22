 /*************************************************************************************************
 * @file       driver_spim.c
 * @author     BLE Group
 * @brief      SPI Master Controller Driver for CP8xxx Series MCUs
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdint.h>
#include "mcu_reg_def.h"
#include "driver_spim.h"

/**
 * @brief Deinitializes the SPI Master peripheral and associated clock
 * @note  Performs a hardware reset sequence and clock gating:
 *        1. Assert/deassert reset via SYS_CTRL register
 *        2. Disable peripheral clock (CLK_ENABLE register at 0x40000028)
 */
void spim_deinit(void)
{
    // Hardware reset sequence
    SYS_CTRL->SYS_RESET |= (1 << 12);      // Assert SPI Master reset
    SYS_CTRL->SYS_RESET &= (~(1 << 12));   // Deassert reset
    
    // Clock gating control
    *(volatile int *)(0x40000028) &= (~(1<<8));  // Clear clock enable bit
}

/**
 * @brief Initializes SPI Master peripheral with specified configuration
 * @param spim_str Pointer to initialization structure containing:
 *        - Data frame size
 *        - Transfer mode
 *        - Clock characteristics
 *        - FIFO thresholds
 *        - Interrupt configuration
 * 
 * @detail Implementation sequence:
 *         1. Enable peripheral clock
 *         2. Configure control registers (CTRLR0, BAUDR, FIFO thresholds)
 *         3. Set up wire mode (3/4 wire)
 *         4. Apply interrupt mask
 *         5. Enable peripheral and slave select
 */
void spim_init(SPIM_InitTypeDef* spim_str)
{
    // Enable peripheral clock
    *(volatile int *)(0x40000028) |= (1<<8);

    // Configure CTRLR0 register
    SPIM->CTRLR0 = 0;  // Clear configuration
    SPIM->CTRLR0_b.DFS = spim_str->SPIM_DFS;    // Data Frame Size (4-16 bits)
    SPIM->CTRLR0_b.TMOD = spim_str->SPIM_TMOD;  // Transfer Mode (TX/RX combinations)
    SPIM->CTRLR0_b.SCPOL = spim_str->SPIM_SCPOL;// Clock Polarity (CPOL)
    SPIM->CTRLR0_b.SCPH = spim_str->SPIM_SCPH;  // Clock Phase (CPHA)
    SPIM->CTRLR0_b.FRF = spim_str->SPIM_FRF;    // Frame Format (Motorola/TI/NXP)

    // Configure wire mode (3/4 wire SPI)
    SPIM->SSIENR_b.MODE_3WIRE = spim_str->SPIM_WIRES;

    // Baud rate configuration (SCLK = PCLK / (SCKDV + 1))
    SPIM->BAUDR = spim_str->SPIM_BaudRatePrescaler;

    // FIFO Configuration
    SPIM->TXFTLR = spim_str->SPIM_TxFIFOThreshold;  // TX FIFO Trigger Level
    SPIM->RXFTLR = spim_str->SPIM_RxFIFOThreshold;  // RX FIFO Trigger Level

    // Interrupt Configuration
    SPIM->IMR = spim_str->int_mask;  // Interrupt Mask Register

    // Enable peripheral and slave select
    SPIM->SSIENR_b.SSI_EN = 1;  // Peripheral enable
    SPIM->SER = 1;              // Slave select enable
}

/**
 * @brief Enables SPI Master peripheral operation
 * @note  Must be called after initialization for normal operation
 */
void spim_enable(void)
{
    SPIM->SSIENR_b.SSI_EN = 1;  // Peripheral enable
    SPIM->SER = 1;              // Slave select assertion
}

/**
 * @brief Disables SPI Master peripheral operation
 */
void spim_disable(void)
{
    SPIM->SSIENR_b.SSI_EN = 0;  // Peripheral disable
    SPIM->SER = 0;              // Slave select deassertion
}

/**
 * @brief Initializes SPI Master configuration structure with default values
 * @param SPIM_InitStruct Pointer to configuration structure to initialize
 * 
 * @default Configuration:
 *         - 8-bit data frames
 *         - Full-duplex mode (TX & RX)
 *         - CPOL=0, CPHA=0 (Mode 0)
 *         - Motorola frame format
 *         - 4-wire operation
 *         - Baud rate prescaler = 8
 *         - RX FIFO threshold = 3, TX FIFO threshold = 8
 */
void spim_struct_init(SPIM_InitTypeDef* SPIM_InitStruct)
{
    SPIM_InitStruct->SPIM_DFS = SPIM_DATA_SIZE_8BITS;   // 8-bit frames
    SPIM_InitStruct->SPIM_TMOD = TX_AND_RX;             // Full-duplex
    SPIM_InitStruct->SPIM_SCPOL = SPIM_CPOL_LOW;       // Clock polarity low
    SPIM_InitStruct->SPIM_SCPH = SPIM_CPHA_MIDDLE;     // Data capture on first edge
    SPIM_InitStruct->SPIM_FRF = SPIM_FRF_MOTOROLA_SPI; // Standard SPI format
    SPIM_InitStruct->SPIM_WIRES = SPIM_WIRES_4;        // 4-wire mode
    SPIM_InitStruct->SPIM_BaudRatePrescaler = 0x8;     // SCK = PCLK/8
    SPIM_InitStruct->SPIM_RxFIFOThreshold = 0x03;      // RX FIFO trigger at 4 bytes
    SPIM_InitStruct->SPIM_TxFIFOThreshold = 0x08;      // TX FIFO trigger at 8 bytes
}

/* Additional function comments follow similar patterns with technical details: */

/**
 * @brief Configures receive data frame count
 * @param RxLen Number of data frames to receive
 * @note  CTRLR1 value = RxLen - 1 (hardware requirement)
 */
void spim_recvive_length_set(uint8_t RxLen)
{
    SPIM->CTRLR1 = RxLen - 1;  // Hardware expects n-1 value
}


void spim_transmode(spim_transfer_mode_e mode)
{
    SPIM->CTRLR0_b.TMOD = mode;
}
void spim_datasize_config(uint32_t spi_datasize)
{
    SPIM->CTRLR0_b.DFS = spi_datasize;
}

void spim_send_data(uint32_t data)
{
    SPIM->DR16 = data;
}
/**
 * @brief Reads data from SPI data register
 * @return Received data from DR16 register
 */
uint32_t spim_receive_data(void)
{
    /* Return the data in the DR16 register */
    return SPIM->DR16;
}

/**
 * @brief Configures SPI interrupt mask
 * @param spim_int Bitmask of interrupts to enable
 */
void spim_int_mask(uint8_t spim_int)
{
    /* Enable the selected SPI interrupt */
    SPIM->IMR = spim_int;
}

/**
 * @brief Gets SPI status register value
 * @return Current value of SR (Status Register)
 */
uint8_t spim_get_status(void)
{
    /* Return the SPI_FLAG status */
    return  SPIM->SR;

}

/**
 * @brief Gets SPI interrupt status
 * @return Current value of ISR (Interrupt Status Register)
 */
uint8_t spim_get_intstatus(void)
{
    return SPIM->ISR;
}

/**
 * @brief Clears SPI interrupts
 * @note Reads ICR (Interrupt Clear Register) to acknowledge interrupts
 */
void spim_int_clear(void)
{
    SPIM->ICR;
}