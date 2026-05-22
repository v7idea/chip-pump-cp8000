/*************************************************************************************************
 * @file       driver_iic.h
 * @author     BLE Group
 * @brief      I2C Controller Driver Header for CP8xxx Series MCUs
 * @version    1.0.1
 * @date       2025-02-26
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_IIC_H__
#define __DRIVER_IIC_H__

#include <stdint.h>
#include "mcu.h"

/*-------------------------------------
  GPIO Configuration
-------------------------------------*/
#define IIC_PIN_NUM          2  ///< Number of pins required for I2C interface
#define IIC_FUN_SCL      12     ///< GPIO function code for SCL pin
#define IIC_FUN_SDA      13     ///< GPIO function code for SDA pin

/*-------------------------------------
  Speed Mode Configuration
-------------------------------------*/
/**
 * @brief I2C bus speed modes
 * @note Actual frequencies depend on PCLK and divider settings
 */
typedef enum {
    IIC_SPEED_STANDARD = 0x1,  ///< Standard mode (100 kHz typical)
    IIC_SPEED_FAST = 0x2       ///< Fast mode (400 kHz typical)
} IIC_Speed_Mode_e;

/*-------------------------------------
  Operation Modes
-------------------------------------*/
typedef enum {
    IIC_MODE_SLAVE,   ///< Operate as I2C slave device
    IIC_MODE_MASTER   ///< Operate as I2C bus master
} IIC_Mode_e;

/*-------------------------------------
  Clock Configuration Values
-------------------------------------*/
/**
 * @brief Predefined clock divider values
 */
typedef enum {
    IIC_CLK_400K = 0x34,  ///< 400kHz clock divider
    IIC_CLK_200K = 0x70,  ///< 200kHz clock divider
    IIC_CLK_100K = 0xe8,  ///< 100kHz clock divider
    IIC_CLK_50K = 0x1d8   ///< 50kHz clock divider
} IIC_Speed_e;

/*-------------------------------------
  Addressing Modes
-------------------------------------*/
enum {
    IIC_ADDR_METHOD_7BIT,   ///< 7-bit device addressing
    IIC_ADDR_METHOD_10BIT   ///< 10-bit extended addressing
};

/*-------------------------------------
  Command Codes
-------------------------------------*/
enum {
    IIC_WRITE = 0x0,    ///< Write operation flag
    IIC_READ = 0x1,     ///< Read operation flag
    IIC_STOP = 0x2,     ///< Generate STOP condition
    IIC_RESTART = 0x4   ///< Generate RESTART condition
};

/*-------------------------------------
  Interrupt Types
-------------------------------------*/
/**
 * @brief I2C interrupt status flags
 * @note Use with iic_int_mask() to enable/disable specific interrupts
 */
typedef enum {
    IIC_INT_RX_UNDER = 1,      ///< RX underflow (read from empty buffer)
    IIC_INT_RX_OVER  = 2,      ///< RX overflow (FIFO overrun)
    IIC_INT_RX_FULL  = 4,      ///< RX FIFO full
    IIC_INT_TX_OVER  = 8,      ///< TX overflow (FIFO overrun)
    IIC_INT_TX_EMPTY = 0x10,   ///< TX FIFO empty
    IIC_INT_RD_REQ   = 0x20,   ///< Slave read request
    IIC_INT_TX_ABRT  = 0x40,   ///< Master transaction aborted
    IIC_INT_RX_DONE  = 0x80,   ///< Slave transaction complete
    IIC_INT_ACTIVITY = 0x100,  ///< Bus activity detected
    IIC_INT_STOP     = 0x200,  ///< STOP condition detected
    IIC_INT_START    = 0x400,  ///< START condition detected
} ENUM_IIC_INT_TYPE;

/*-------------------------------------
  Initialization Structure
-------------------------------------*/
/**
 * @brief I2C controller configuration parameters
 * @note All fields must be initialized before calling iic_init()
 */
typedef struct {
    IIC_Mode_e i2c_mode;        ///< Master/Slave mode selection
    IIC_Speed_Mode_e speed_mode;///< Standard/Fast mode selection
    IIC_Speed_e speed;          ///< Clock divider value (see IIC_Speed_e)
    uint8_t device_addr;        ///< Device address (7-bit format)
    uint8_t i2c_sda_pin;        ///< GPIO pin number for SDA
    uint8_t i2c_scl_pin;        ///< GPIO pin number for SCL
} I2C_Init_structure_typedef;

/*-------------------------------------
  Driver API
-------------------------------------*/
/**
 * @brief Initialize I2C controller with specified configuration
 * @param i2c_init_str Pointer to initialization structure containing:
 *        - GPIO pin assignments
 *        - Operation mode (Master/Slave)
 *        - Speed configuration
 *        - Device address
 * 
 * @details Performs:
 * 1. GPIO multiplexing configuration
 * 2. Controller register setup
 * 3. Speed mode configuration (Standard/Fast)
 * 4. Device addressing setup
 */
void iic_init(I2C_Init_structure_typedef *i2c_init_str);

/**
 * @brief Set interrupt mask register
 * @param int_mask 16-bit mask pattern:
 *        Bit 0: RX_FULL   - Receive FIFO full
 *        Bit 1: TX_EMPTY  - Transmit FIFO empty
 *        ... (other bits per IC_INTR_MASK register spec)
 */
void iic_int_mask(uint16_t int_mask);

/**
 * @brief Get masked interrupt status
 * @return uint16_t Current interrupt status filtered by mask
 */
uint16_t iic_int_status(void);

/**
 * @brief Clear pending interrupts
 * @note Writing any value clears all interrupt sources
 */
void iic_int_clear(void);

/**
 * @brief Send data through I2C interface
 * @param data Pointer to the data buffer to be transmitted
 * @param len  Length of data to be transmitted in bytes
 * 
 * @details This function sends data byte by byte through the I2C bus:
 * 1. Waits until TX FIFO has available space (prevents overflow)
 * 2. Writes data byte to the I2C data command register
 * 3. Continues until all data is transmitted
 * 
 * @note The comment in the original code indicates that when txfifo is empty, 
 *       a stop signal will be sent automatically
 */
void I2C_send(uint8_t *data, uint8_t len);

/**
 * @brief Receive data from I2C device
 * @param data Pointer to the buffer where received data will be stored
 * @param len  Number of bytes to receive
 * 
 * @details This function implements a two-stage I2C read process:
 * 1. First stage: Send read commands while simultaneously reading available data
 * 2. Second stage: Read remaining data after all commands have been sent
 * 
 * The function uses FIFO level checks to optimize data transfer efficiency.
 */
void I2C_recv(uint8_t *data, uint8_t len);

/**
 * @brief Write data to I2C device
 * @param reg_addr Target register address
 * @param data Pointer to transmit buffer
 * @param len Number of bytes to write
 * 
 * @note Implements:
 * 1. Register address write
 * 2. Sequential data writes
 * 3. Automatic STOP condition generation
 */
void I2C_write(uint8_t reg_addr, uint8_t *data, uint8_t len);

/**
 * @brief Read data from I2C device
 * @param reg_addr Target register address
 * @param data Pointer to receive buffer
 * @param len Number of bytes to read
 * 
 * @note Implements:
 * 1. Register address write (set read pointer)
 * 2. Sequential read operations
 * 3. STOP condition on final read
 * 4. Blocking FIFO status checks
 */
void I2C_read(uint8_t reg_addr, uint8_t *data, uint8_t len);

#endif /* __DRIVER_IIC_H__ */