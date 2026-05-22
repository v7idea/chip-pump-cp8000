/*************************************************************************************************
 * @file       driver_iic.c
 * @author     BLE Group
 * @brief      I2C Controller Driver Implementation for CP8xxx Series MCUs
 * @version    1.0.1
 * @date       2025-02-26
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include "mcu_reg_def.h"
#include "driver_gpio.h"
#include "driver_iic.h"

/*-------------------------------------
  I2C Controller Initialization
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
void iic_init(I2C_Init_structure_typedef *i2c_init_str)
{
    /* Configure GPIO pin functions for I2C */
    gpio_set_func(i2c_init_str->i2c_sda_pin, IIC_FUN_SDA|0x20);
    gpio_set_func(i2c_init_str->i2c_scl_pin, IIC_FUN_SCL|0x20);

    /* Controller configuration sequence */
    IIC->IC_RX_TL_b.RX_TL = 7;            // Set RX FIFO threshold
    IIC->IC_TX_TL_b.TX_TL = 7;            // Set TX FIFO threshold
    IIC->IC_ENABLE_b.IC_ENABLE = 0;       // Disable controller during config
    IIC->IC_INTR_MASK = 0;                // Mask all interrupts
    IIC->IC_CON_b.IC_10BITADDR_MASTER = 0;// 7-bit addressing mode
    IIC->IC_CON_b.IC_10BITADDR_SLAVE = 0; // 7-bit slave addressing

    /* Mode configuration */
    if(IIC_MODE_MASTER == i2c_init_str->i2c_mode) {
        IIC->IC_CON_b.MASTER_MODE = 0x1;    // Enable master mode
        IIC->IC_CON_b.IC_SLAVE_DISABLE =0x1;// Disable slave mode
        IIC->IC_TAR_b.IC_TAR = i2c_init_str->device_addr; // Target device address
    } else {
        IIC->IC_CON_b.MASTER_MODE = 0x0;    // Disable master mode
        IIC->IC_CON_b.IC_SLAVE_DISABLE =0x0;// Enable slave mode
        IIC->IC_SAR_b.IC_SAR = i2c_init_str->device_addr; // Slave address
    }

    /* Speed mode configuration */
    if(i2c_init_str->speed_mode == IIC_SPEED_STANDARD) {
        IIC->IC_CON_b.SPEED = 0x1;         // Standard mode (100kHz)
        // SCL timing configuration
        IIC->IC_SS_SCL_HCNT_b.IC_SS_SCL_HCNT = i2c_init_str->speed>>1;
        IIC->IC_SS_SCL_LCNT_b.IC_SS_SCL_LCNT = i2c_init_str->speed>>1;
    } else if(i2c_init_str->speed_mode == IIC_SPEED_FAST) {
        IIC->IC_CON_b.SPEED = 0x2;         // Fast mode (400kHz)
        // Fast mode SCL timing
        IIC->IC_FS_SCL_HCNT_b.IC_FS_SCL_HCNT = i2c_init_str->speed>>1;
        IIC->IC_FS_SCL_LCNT_b.IC_FS_SCL_LCNT = i2c_init_str->speed>>1;
    }

    IIC->IC_ENABLE_b.IC_ENABLE =1; // Enable controller after configuration
}

/*-------------------------------------
  Interrupt Management
-------------------------------------*/

/**
 * @brief Set interrupt mask register
 * @param int_mask 16-bit mask pattern:
 *        Bit 0: RX_FULL   - Receive FIFO full
 *        Bit 1: TX_EMPTY  - Transmit FIFO empty
 *        ... (other bits per IC_INTR_MASK register spec)
 */
void iic_int_mask(uint16_t int_mask)
{
    IIC->IC_INTR_MASK = int_mask;
}

/**
 * @brief Get masked interrupt status
 * @return uint16_t Current interrupt status filtered by mask
 */
uint16_t iic_int_status(void)
{
    return IIC->IC_INTR_STAT;
}

/**
 * @brief Get raw interrupt status (unmasked)
 * @return uint16_t All pending interrupts regardless of mask
 */
uint16_t iic_raw_int_status(void)
{
    return IIC->IC_RAW_INTR_STAT;
}

/**
 * @brief Clear pending interrupts
 * @note Writing any value clears all interrupt sources
 */
void iic_int_clear(void)
{
    IIC->IC_CLR_INTR; // Self-clearing register
}

/*-------------------------------------
  Data Transfer Operations
-------------------------------------*/

/**
 * @brief Internal command write helper
 * @param cmd Control command (IIC_WRITE/IIC_READ/IIC_STOP)
 * @param data Byte to transmit
 */
static void iic_write_cmd(uint8_t cmd, uint8_t data)
{
    IIC->IC_DATA_CMD = (cmd << 8) | (data & 0xFF);
}


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
void I2C_send(uint8_t *data, uint8_t len)
{
	uint32_t tc = 0;  // Transmission counter
	
	// Loop until all data is sent
	while(tc < len)
	{
	    // Wait for TX FIFO to have space available (prevent overflow)
	    // When txfifo is empty, a stop signal will be sent
		while(IIC->IC_TXFLR > 5){}
		
		// Send current data byte
		IIC->IC_DATA_CMD = data[tc];
		tc++;  // Increment transmission counter
	}
}

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
void I2C_recv(uint8_t *data, uint8_t len)
{
    uint32_t tc = 0, rc = 0;
    // write cmd and read data
    while(tc < len){
        // check tx fifo and send cmd
        if(IIC->IC_TXFLR <= 6){
            IIC->IC_DATA_CMD = IIC_READ<<8;
            tc ++;
        }
        // read data
        if(IIC->IC_RXFLR >= 4){
            data[rc] = IIC->IC_DATA_CMD;
            rc++;
        }
    }
    // read remaining data
    while(rc < len){
        if(IIC->IC_RXFLR > 0){
            data[rc] = IIC->IC_DATA_CMD;
            rc++;
        }
    }
}


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
void I2C_write(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
	#if 0
    iic_write_cmd(IIC_WRITE, reg_addr); // Send register address
    for(uint8_t i=0; i<(len); i++) 
	{
        iic_write_cmd(IIC_WRITE, data[i]); // Write data bytes
    }
    iic_write_cmd(IIC_STOP,0); // Final byte with STOP
	#else
	uint32_t tc = 0;
	iic_write_cmd(IIC_WRITE, reg_addr); // Send register address
	while(tc < len)
	{
	    while(IIC->IC_TXFLR > 5){} // Wait for TX FIFO space
        IIC->IC_DATA_CMD = data[tc];
        tc++;
	}

	#endif
}

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
void I2C_read(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
	#if 0
    iic_write_cmd(IIC_WRITE, reg_addr); // Set read address
    
    for(uint8_t i=0; i<len; i++) 
	{

		iic_write_cmd(IIC_READ, 0);  //Normal read

        // Block until RX FIFO has data

        data[i] = IIC->IC_DATA_CMD_b.DAT; // Read received byte
    }
	iic_write_cmd(IIC_STOP, 0); // Final read with STOP
	#else
	
    uint32_t tc = 0, rc = 0;
	iic_write_cmd(IIC_WRITE, reg_addr); // Set read address
	
    // write cmd and read data
    while(tc < len){
        // check tx fifo and send cmd
        if(IIC->IC_TXFLR <= 6){
            IIC->IC_DATA_CMD = IIC_READ<<8;
            tc ++;
        }
        // read data
        if(IIC->IC_RXFLR >= 4){
            data[rc] = IIC->IC_DATA_CMD;
            rc++;
        }
    }
    // read remaining data
    while(rc < len){
        if(IIC->IC_RXFLR > 0){
            data[rc] = IIC->IC_DATA_CMD;
            rc++;
        }
    }
	#endif
}


