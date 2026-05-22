/*************************************************************************************************
 * @file       driver_ledc.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-03-23
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_RGB_C_H__
#define __DRIVER_RGB_C_H__
#include <stdint.h>
#include "mcu.h"


#define LEDC0_FUNC   14
#define LEDC1_FUNC   15    

typedef enum {
    LEDC_DONE = 0x1,
    LEDC_DMA  = 0x2,
    LEDC_ERR  = 0x4
} ledc_int_typedef;

typedef enum
{
    LEDC_CHANNEL0 = 0x0,
    LEDC_CHANNEL1 = 0x1,
}ledc_ch_typedef;

typedef struct {
    uint16_t period;
    uint16_t code_0_high;
    uint16_t code_1_high;
    ledc_ch_typedef chnum;
    uint8_t pin;
}ledc_timing_init_typedef;

typedef enum
{
    LEDC_DATA_MODE_24BIT = 0,
    LEDC_DATA_MODE_32BIT = 1
}ledc_data_mode;


/**
 * @brief Initialize RGB controller timing parameters
 * @param ledc_init_str Pointer to initialization structure containing:
 *        - chnum: Channel number (LEDC_CH0/LEDC_CH1)
 *        - pin: GPIO pin configuration
 *        - period: Total signal period
 *        - code_0_high: High duration for code 0
 *        - code_1_high: High duration for code 1
 */
void ledc_init(ledc_timing_init_typedef * ledc_init_str);
/**
 * @brief Configure DMA transfer for RGB controller channel
 * @param ledc_ch Channel selector (LEDC_CH0/LEDC_CH1)
 * @param pdata Pointer to data buffer
 */
void ledc_dma_set(ledc_ch_typedef ledc_ch,uint32_t * pdata);
void ledc_dma_table_set(ledc_ch_typedef ledc_ch,void *pdata,int rows, int cols, uint32_t len);

/**
 * @brief Start LED controller channel
 * @param ch Channel selection (LEDC_CH0/LEDC_CH1)
 */
void ledc_start(ledc_ch_typedef ledc_ch);

/**
 * @brief Stop LED controller channel
 * @param ch Channel selection (LEDC_CH0/LEDC_CH1)
 */
void ledc_stop(ledc_ch_typedef ledc_ch);

void ledc_dma_en(uint8_t en);
void ledc_restart(ledc_ch_typedef ledc_ch);

/**
 * @brief Configure LED controller interrupts
 * @param ch Channel selection (LEDC_CH0/LEDC_CH1)
 * @param int_type Interrupt type mask
 */
void ledc_int_config(ledc_ch_typedef ledc_ch,ledc_int_typedef int_type);


uint8_t ledc_int_status(ledc_ch_typedef ledc_ch);
void ledc_int_clear(ledc_ch_typedef ledc_ch,ledc_int_typedef int_type);

uint32_t* ledc_set_dat(uint32_t *a, int rpt, int chg, int c) ;
uint32_t* ledc_set_ctl(uint32_t *a, int last, int irq, int cmd, int len) ;
uint32_t* ledc_set_sdat(uint32_t *a, int rpt, int chg, int c) ;
uint32_t* ledc_set_mdat(uint32_t *a, int loop, int rpt, int ea, int sa);

/**
 * @brief Configure LED controller (LEDC) DMA transfer buffer
 * 
 * Sets up DMA transfer parameters based on data mode (24-bit or 32-bit), generates corresponding
 * control command sequences, and initiates DMA transfer.
 * 
 * @param ledc_ch      LEDC channel handle specifying hardware channel to configure
 * @param mode         Data transfer mode: LEDC_DATA_MODE_24BIT or LEDC_DATA_MODE_32BIT
 * @param pdata        Pointer to start address of data buffer
 * @param len          Data length (number of items in 24-bit mode, bytes in 32-bit mode)
 * @param interval_ms  Data transfer interval in milliseconds (will be converted to clock units by left-shifting)
 */
void ledc_dma_buffer_set(ledc_ch_typedef ledc_ch,ledc_data_mode mode,uint32_t *pdata,uint16_t len,uint16_t interval_ms);


/**
 * @brief Configure LED controller data repeat parameters
 * 
 * This function generates LED controller command sequences, configures repeat counts and interval timing,
 * and writes parameters to specified data buffer.
 * 
 * @param data_buff  Pointer to data buffer (uint32_t array type) for storing generated command sequences
 * @param data       24-bit LED control data (lower 24 bits are valid)
 * @param repeat_count Number of data repeat transmissions (0 indicates single transmission)
 * @param interval_ms  Repeat interval duration (unit: milliseconds, actual hardware uses 0.5ms timebase)
 */
void ledc_data_repeat_func(void *data_buff,uint32_t data,uint16_t repeat_count,uint16_t interval_ms);

/**
 * @brief LED controller data gradual change configuration function
 * 
 * Configures LED controller to achieve gradual transition effect from source to destination data. 
 * Generates control command sequence in the data buffer with specified transition steps and timing.
 * 
 * @param data_buff Pointer to data buffer for storing generated control command sequence
 * @param src Source data value (starting value for transition)
 * @param dst Destination data value (target value for transition)
 * @param chg_count Number of transition steps (controls smoothness of change)
 * @param interval_ms Transition interval duration in milliseconds (time between steps)
 */
void ledc_data_gradual_chg_func(void *data_buff,uint32_t src ,uint32_t dst,uint16_t chg_count,uint16_t interval_ms);

/**
 * @brief Generate LED waterflow effect control sequence
 * 
 * This function creates a dynamic waterflow effect by sequentially turning off LEDs from both ends 
 * towards the center while maintaining the first LED lit. The effect is built using special data commands.
 * 
 * @param data_buff Pointer to data buffer for storing generated control sequence (uint32_t array)
 * @param data      Main LED display data value (color/brightness) for the first position LED
 * @param count     Number of LEDs/effect iterations (valid range 0-1000)
 * @param interval_ms Effect interval duration in milliseconds (actual interval = interval_ms * 2)
 */
void ledc_data_waterflow_func(void *data_buff,uint32_t data,uint32_t count,uint16_t interval_ms);


#endif