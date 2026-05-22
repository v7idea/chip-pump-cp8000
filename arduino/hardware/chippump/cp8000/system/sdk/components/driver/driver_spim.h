/*************************************************************************************************
 * @file       driver_spim.h
 * @author     BLE Group
 * @brief      SPI Master Controller Driver for CP8xxx Series MCUs
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_SPIM_H__
#define __DRIVER_SPIM_H__

#include <stdint.h>
#include "mcu.h"

#define SPIM_FUN 2  // SPI Master function identifier

// SPI Master Status Flags
#define SPIM_FLAG_DATA_COLLISION_ERROR    (0x40)  // Data collision error flag
#define SPIM_FLAG_TRANSMISSION_ERROR      (0x20)  // Transmission error flag
#define SPIM_FLAG_RECEIVE_FIFO_FULL       (0x10)  // Receive FIFO full flag
#define SPIM_FLAG_RECEIVE_FIFO_NOT_EMPTY  (0x08)  // Receive FIFO not empty flag
#define SPIM_FLAG_TRANSMIT_FIFO_EMPTY     (0x04)  // Transmit FIFO empty flag
#define SPIM_FLAG_TRANSMIT_FIFO_NOT_FULL  (0x02)  // Transmit FIFO not full flag
#define SPIM_FLAG_BUSY                    (0x01)  // Busy flag

// SPI Master Interrupts
#define SPIM_IT_RX_FIFO_FULL              (0x10)  // Receive FIFO full interrupt
#define SPIM_IT_RX_FIFO_OVERFLOW          (0x08)  // Receive FIFO overflow interrupt
#define SPIM_IT_RX_FIFO_UNDERFLOW         (0x04)  // Receive FIFO underflow interrupt
#define SPIM_IT_TX_FIFO_OVERFLOW          (0x02)  // Transmit FIFO overflow interrupt
#define SPIM_IT_TX_FIFO_EMPTY             (0x01)  // Transmit FIFO empty interrupt
#define SPIM_IT_ALL                       (0x3F)  // All interrupts
#define SPIM_IT_NONE                      (0x00)  // No interrupts

// SPI Master Frame Data
#define SPIM_DATA_SIZE_8BITS              (0x07)  // 8-bit data size

// SPI Master Transfer Mode Enumeration
typedef enum
{
    TX_AND_RX = 0,  // Transmit and Receive mode
    TX_ONLY = 1,    // Transmit only mode
    RX_ONLY = 2     // Receive only mode
} spim_transfer_mode_e;

// SPI Master Frame Format Enumeration
typedef enum
{
    SPIM_FRF_MOTOROLA_SPI = 0,  // Motorola SPI frame format
    SPIM_FRF_TI_SPI = 1,        // Texas Instruments SPI frame format
    SPIM_FRF_NXP_SPI = 2        // NXP SPI frame format
} spim_frame_format_e;

// SPI Master Clock Polarity Enumeration
typedef enum
{
    SPIM_CPOL_LOW = 0,  // Clock polarity low
    SPIM_CPOL_HIGH = 1  // Clock polarity high
} spim_clock_polarity_e;

// SPI Master Clock Phase Enumeration
typedef enum
{
    SPIM_CPHA_MIDDLE = 0,  // Clock phase middle
    SPIM_CPHA_START = 1    // Clock phase start
} spim_clock_phase_e;

// SPI Master Wires Enumeration
typedef enum
{
    SPIM_WIRES_4  = 0,  // 4-wire mode
    SPIM_WIRES_3  = 1   // 3-wire mode
} spim_wires_e;

// SPI Master Initialization Structure
typedef struct
{
    uint8_t SPIM_DFS;  // Data frame size
    spim_transfer_mode_e SPIM_TMOD;  // Transfer mode
    spim_clock_polarity_e SPIM_SCPOL;  // Clock polarity
    spim_clock_phase_e SPIM_SCPH;  // Clock phase
    spim_frame_format_e SPIM_FRF;  // Frame format
    spim_wires_e SPIM_WIRES;  // Number of wires
    uint32_t SPIM_RxFIFOThreshold;  // Receive FIFO threshold
    uint32_t SPIM_TxFIFOThreshold;  // Transmit FIFO threshold
    uint16_t SPIM_BaudRatePrescaler;  // Baud rate prescaler
    uint8_t int_mask;  // Interrupt mask
} SPIM_InitTypeDef;

/**
 * @brief Deinitializes the SPI Master peripheral and associated clock
 * @note  Performs a hardware reset sequence and clock gating:
 *        1. Assert/deassert reset via SYS_CTRL register
 *        2. Disable peripheral clock (CLK_ENABLE register at 0x40000028)
 */
void spim_deinit(void); 

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
void spim_init(SPIM_InitTypeDef* spim_str); 

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
void spim_struct_init(SPIM_InitTypeDef* SPIS_InitStruct);  // Initialize the SPI Master structure

/**
 * @brief Writes data to SPI data register
 * @param data Data to transmit (16-bit aligned)
 */
void spim_send_data(uint32_t data);  

/**
 * @brief Reads data from SPI data register
 * @return Received data from DR16 register
 */
uint32_t spim_receive_data(void);  

/**
 * @brief Gets SPI status register value
 * @return Current value of SR (Status Register)
 */
uint8_t spim_get_status(void);  

/**
 * @brief Configures SPI interrupt mask
 * @param spim_int Bitmask of interrupts to enable
 */
void spim_int_mask(uint8_t spim_int);  

/**
 * @brief Gets SPI interrupt status
 * @return Current value of ISR (Interrupt Status Register)
 */
uint8_t spim_get_intstatus(void);  

/**
 * @brief Clears SPI interrupts
 * @note Reads ICR (Interrupt Clear Register) to acknowledge interrupts
 */
void spim_int_clear(void);  

#endif /* __DRIVER_SPIM_H__ */