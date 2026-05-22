/*************************************************************************************************
 * @file       driver_spis.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.0
 * @date       2024-08-27
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_SPIS_H__
#define __DRIVER_SPIS_H__

#include <stdint.h>

#define SPIS_FUNC  3

//SPIS Status Flag
#define SPIS_FLAG_DATA_COLLISION_ERROR    (0x40) 
#define SPIS_FLAG_TRANSMISSION_ERROR      (0x20)
#define SPIS_FLAG_RECEIVE_FIFO_FULL       (0x10)
#define SPIS_FLAG_RECEIVE_FIFO_NOT_EMPTY  (0x08)
#define SPIS_FLAG_TRANSMIT_FIFO_EMPTY     (0x04)
#define SPIS_FLAG_TRANSMIT_FIFO_NOT_FULL  (0x02)
#define SPIS_FLAG_BUSY                    (0x01)

//SPIS Interrupt
#define SPIS_IT_RX_FIFO_FULL              (0x10)
#define SPIS_IT_RX_FIFO_OVERFLOW          (0x08)
#define SPIS_IT_RX_FIFO_UNDERFLOW         (0x04)
#define SPIS_IT_TX_FIFO_OVERFLOW          (0x02)
#define SPIS_IT_TX_FIFO_EMPTY             (0x01)
#define SPIS_IT_ALL                       (0x3F)
#define SPIS_IT_NONE                      (0x00)
//SPIS FRAME DATA
#define SPIS_DATA_SIZE_8BITS              (0x07)


typedef enum
{
    TX_AND_RX = 0,
    TX_ONLY = 1,
    RX_ONLY = 2
}spis_transfer_mode_e;

typedef enum
{
    SPIS_FRF_MOTOROLA_SPI = 0,
    SPIS_FRF_TI_SPI = 1,
    SPIS_FRF_NXP_SPI = 2
}spis_frame_format_e;

typedef enum
{
    SPIS_CPOL_LOW = 0,
    SPIS_CPOL_HIGH = 1
}spis_clock_polarity_e;

typedef enum
{
    SPIS_CPHA_MIDDLE = 0,
    SPIS_CPHA_START = 1
}spis_clock_phase_e;


typedef enum
{
    SPIS_WIRES_4  = 0,
    SPIS_WIRES_3  = 1
}spis_wires_e;

typedef struct
{
    uint8_t SPIS_DFS;
    spis_transfer_mode_e SPIS_TMOD;
    spis_clock_polarity_e SPIS_SCPOL;                
    spis_clock_phase_e SPIS_SCPH;
    spis_frame_format_e SPIS_FRF;
    spis_wires_e SPIS_WIRES;
    uint32_t SPIS_RxFIFOThreshold;
    uint32_t SPIS_TxFIFOThreshold;
    uint8_t int_mask;

}SPIS_InitTypeDef;


/**
 * @brief Deinitializes the SPI Slave peripheral
 * @note Performs hardware reset sequence and clock gating:
 *       - Asserts/deasserts SPI Slave reset via SYS_CTRL register (bit 14)
 *       - Disables peripheral clock through CLK_ENABLE register (0x40000028 bit 11)
 */
void spis_deinit(void);

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
void spis_struct_init(SPIS_InitTypeDef* SPIS_InitStruct);

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
void spis_init(SPIS_InitTypeDef* spis_str);

/**
 * @brief Enables SPI Slave peripheral operation
 * @note Sets SSI_EN bit in SSIENR register to activate peripheral
 */
void spis_enable(void);

/**
 * @brief Disables SPI Slave peripheral operation
 * @note Clears SSI_EN bit in SSIENR register to deactivate peripheral
 */
void spis_disable(void);

/**
 * @brief Configures SPI Slave transfer mode
 * @param mode Transfer mode (TX_ONLY, RX_ONLY, TX_AND_RX, etc.)
 * @note Directly modifies CTRLR0_b.TMOD field
 */
void spis_transmode(spis_transfer_mode_e mode);

/**
 * @brief Configures SPI Slave data frame size
 * @param spi_datasize Data frame size (4-16 bits)
 * @note Directly sets CTRLR0_b.DFS field
 */
void spis_datasize_config(uint32_t spi_datasize);
/**
 * @brief Writes data to SPI Slave data register
 * @param data Data to transmit (16-bit aligned)
 * @note Writes directly to DR16 register
 */
void spis_send_data(uint16_t data);

/**
 * @brief Reads data from SPI Slave data register
 * @return Received data from DR16 register
 */
uint16_t spis_receive_data(void);

/**
 * @brief Gets SPI Slave status register value
 * @return Current value of SR (Status Register)
 * @note Includes flags like TX_FULL, RX_EMPTY, BUSY, etc.
 */
uint8_t spis_get_status(void);

/**
 * @brief Configures SPI Slave interrupt mask
 * @param spis_int Bitmask of interrupts to enable
 * @note Directly sets IMR (Interrupt Mask Register)
 */
void spis_int_mask(uint8_t spis_int);

/**
 * @brief Gets SPI Slave interrupt status
 * @return Current value of ISR (Interrupt Status Register)
 * @note Indicates active interrupt sources
 */
uint8_t spis_get_intstatus(void);

/**
 * @brief Clears SPI Slave interrupts
 * @note Reads ICR (Interrupt Clear Register) to acknowledge and clear interrupts
 */
void spis_int_clear(void);






#if 0


/**
 * @brief Transmit data block
 * @param pdata Transmit buffer pointer
 * @param len Data length (bytes)
 * @param ncs_pin_cfg Chip select config
 * @param line_mode 3/4-wire mode
 * 
 * @process
 * 1. Initialize TX mode
 * 2. Stream data through FIFO
 * 3. Wait for transmission completion
 * 4. Add post-delay for bus turnaround
 * 5. Switch back to RX mode
 */
void spis_send(void * pdata, uint32_t len, struct gpio_cfg_tag *ncs_pin_cfg, uint8_t line_mode);

/**
 * @brief Receive available data
 * @param pbuf Receive buffer pointer
 * @param blen Buffer capacity
 * @param line_mode 3/4-wire mode
 * @return Number of bytes received
 * 
 * @note Different status checks for 3-wire vs 4-wire modes:
 * - 3-wire: Check SR_RCV_NOTEMPTY
 * - 4-wire: Check RX FIFO level
 */
uint32_t spis_rece(void * pbuf, uint32_t blen, uint8_t line_mode);

/**
 * @brief Initialize SPI Slave controller
 * @param line_mode Communication mode:
 *        - SPIS_3LINES: 3-wire (SCK, MOSI, MISO)
 *        - SPIS_4LINES: 4-wire (+NSS)
 * 
 * @sequence
 * 1. Disable controller
 * 2. Configure control register (RX mode, slave OE)
 * 3. Set line mode and enable
 */
void spis_init(uint8_t line_mode);
#endif
#endif