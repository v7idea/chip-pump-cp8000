/*************************************************************************************************
 * @file       driver_spis.c
 * @author     BLE Group
 * @brief 
 * @version    1.0.4
 * @date       2024-04-18
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ***********************************************************************************************/
#include "mcu_reg_def.h"
#include "mcu.h"
#include "driver_spis.h"

/**
 * @brief Deinitializes the SPI Slave peripheral
 * @note Performs hardware reset sequence and clock gating:
 *       - Asserts/deasserts SPI Slave reset via SYS_CTRL register (bit 14)
 *       - Disables peripheral clock through CLK_ENABLE register (0x40000028 bit 11)
 */
void spis_deinit(void)
{
    SYS_CTRL->SYS_RESET |= (1 << 14);
    SYS_CTRL->SYS_RESET &= (~(1 << 14));
    *(volatile int *)(0x40000028) &= (~(1<<11));
}

/**
 * @brief Initializes SPI Slave configuration structure with default values
 * @param SPIS_InitStruct Pointer to configuration structure
 * @default Configuration:
 *         - 8-bit data frames
 *         - Full-duplex mode (TX & RX)
 *         - CPOL=0, CPHA=0 (Mode 0)
 *         - Motorola frame format
 *         - 4-wire operation
 *         - RX FIFO threshold = 3, TX FIFO threshold = 8
 */
void spis_struct_init(SPIS_InitTypeDef* SPIS_InitStruct)
{
    SPIS_InitStruct->SPIS_DFS = SPIS_DATA_SIZE_8BITS;  
    SPIS_InitStruct->SPIS_TMOD = TX_AND_RX;
    SPIS_InitStruct->SPIS_SCPOL = SPIS_CPOL_LOW;
    SPIS_InitStruct->SPIS_SCPH = SPIS_CPHA_MIDDLE;
    SPIS_InitStruct->SPIS_FRF = SPIS_FRF_MOTOROLA_SPI;
    SPIS_InitStruct->SPIS_WIRES = SPIS_WIRES_4;
    SPIS_InitStruct->SPIS_RxFIFOThreshold = 0x03;
    SPIS_InitStruct->SPIS_TxFIFOThreshold = 0x08;
}

/**
 * @brief Initializes SPI Slave peripheral with specified configuration
 * @param spis_str Pointer to initialization structure containing:
 *        - Data frame size
 *        - Transfer mode
 *        - Clock characteristics
 *        - FIFO thresholds
 *        - Interrupt configuration
 * @details Initialization sequence:
 *          1. Enable peripheral clock
 *          2. Configure control registers (CTRLR0, FIFO thresholds)
 *          3. Set wire mode (3/4 wire)
 *          4. Enable FIFO functionality
 *          5. Apply interrupt mask
 *          6. Enable peripheral
 */
void spis_init(SPIS_InitTypeDef* spis_str)
{
    // RCC
    *(volatile int *)(0x40000028) |= (1<<11);

    /* Configure SPIS0: direction, NSS management, first transmitted bit, BaudRate prescaler
    master/salve mode, CPOL and CPHA */
    /* Set BR bits according to SPI_BaudRatePrescaler value */
    /* Set CPOL bit according to SPI_CPOL value */
    /* Set CPHA bit according to SPI_CPHA value */
    /* Write to SPIS0 CTRLR0 */
	SPIS->CTRLR0 = 0;
    SPIS->CTRLR0_b.DFS = spis_str->SPIS_DFS;
    SPIS->CTRLR0_b.TMOD = spis_str->SPIS_TMOD;
    SPIS->CTRLR0_b.SCPOL = spis_str->SPIS_SCPOL;
    SPIS->CTRLR0_b.SCPH = spis_str->SPIS_SCPH;
    SPIS->CTRLR0_b.FRF = spis_str->SPIS_FRF;

    //Set number of wires
    SPIS->SSIENR_b.MODE_3WIRE = spis_str->SPIS_WIRES;
    SPIS->SSIENR_b.FIFO_FEN =1;

    //Set TX FIFO Threshold level
    SPIS->TXFTLR = spis_str->SPIS_TxFIFOThreshold;
    
    //Set RX FIFO Threshold level
    SPIS->RXFTLR = spis_str->SPIS_RxFIFOThreshold;

    SPIS->IMR = spis_str->int_mask;

    SPIS->SSIENR_b.SSI_EN = 1;

}

/**
 * @brief Enables SPI Slave peripheral operation
 * @note Sets SSI_EN bit in SSIENR register to activate peripheral
 */
void spis_enable(void)
{
    /* Enable the selected SPI peripheral */
    SPIS->SSIENR_b.SSI_EN = 1;
}

/**
 * @brief Disables SPI Slave peripheral operation
 * @note Clears SSI_EN bit in SSIENR register to deactivate peripheral
 */
void spis_disable(void)
{
    /* Disable the selected SPI peripheral */
    SPIS->SSIENR_b.SSI_EN = 0;
}

/**
 * @brief Configures SPI Slave transfer mode
 * @param mode Transfer mode (TX_ONLY, RX_ONLY, TX_AND_RX, etc.)
 * @note Directly modifies CTRLR0_b.TMOD field
 */
void spis_transmode(spis_transfer_mode_e mode)
{
    SPIS->CTRLR0_b.TMOD = mode;
}

/**
 * @brief Configures SPI Slave data frame size
 * @param spi_datasize Data frame size (4-16 bits)
 * @note Directly sets CTRLR0_b.DFS field
 */
void spis_datasize_config(uint32_t spi_datasize)
{
    SPIS->CTRLR0_b.DFS = spi_datasize;
}

/**
 * @brief Writes data to SPI Slave data register
 * @param data Data to transmit (16-bit aligned)
 * @note Writes directly to DR16 register
 */
void spis_send_data(uint16_t data)
{
    SPIS->DR16 = data;
}

/**
 * @brief Reads data from SPI Slave data register
 * @return Received data from DR16 register
 */
uint16_t spis_receive_data(void)
{
    /* Return the data in the DR16 register */
    return SPIS->DR16;
}

/**
 * @brief Configures SPI Slave interrupt mask
 * @param spis_int Bitmask of interrupts to enable
 * @note Directly sets IMR (Interrupt Mask Register)
 */
void spis_int_mask(uint8_t spis_int)
{
    /* Enable the selected SPI interrupt */
    SPIS->IMR = spis_int;
}

/**
 * @brief Gets SPI Slave status register value
 * @return Current value of SR (Status Register)
 * @note Includes flags like TX_FULL, RX_EMPTY, BUSY, etc.
 */
uint8_t spis_get_status(void)
{
    /* Return the SPI_FLAG status */
    return  SPIS->SR;

}

/**
 * @brief Gets SPI Slave interrupt status
 * @return Current value of ISR (Interrupt Status Register)
 * @note Indicates active interrupt sources
 */
uint8_t spis_get_intstatus(void)
{
    return SPIS->ISR;
}

/**
 * @brief Clears SPI Slave interrupts
 * @note Reads ICR (Interrupt Clear Register) to acknowledge and clear interrupts
 */
void spis_int_clear(void)
{
    SPIS->ICR;
}