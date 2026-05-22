/*************************************************************************************************
 * @file driver_lvd.h
 * @author BLE GROUP ()
 * @brief 
 * @version 1.0.0
 * @date 2025-06-27
 * 
 * 
*************************************************************************************************/

#ifndef __DRIVER_LVD_H
#define __DRIVER_LVD_H

#include <stdint.h>
#include "mcu.h"


/*************************************************************************************************
 *                                          INCLUDES
*************************************************************************************************/



/*************************************************************************************************
 *                                          DEFINES
*************************************************************************************************/


typedef enum 
{
    VDDIO_SUPPLY = 0,     /*!< VDDIO power supply detection */
    VBAT_SUPPLY = 1,      /*!< Battery power supply detection */
    GPIO2_SUPPLY = 2,     /*!< GPIO2 pin voltage detection */
    GPIO10_SUPPLY = 3     /*!< GPIO10 pin voltage detection */
}LVD_DECT_INPUT_ENUM;

typedef enum 
{
    LVD_THRESHOLD_LOW = 0,  /*!< Low threshold range: 1.2V to 2.2V in 66.7mV steps */
    LVD_THRESHOLD_MID = 1,  /*!< Medium threshold range: 1.8V to 3.3V in 100mV steps */
    LVD_THRESHOLD_HIGH = 2  /*!< High threshold range: 3V to 5.5V in 167mV steps */
}LVD_THRESHOLD_MODE_ENUM;

typedef enum 
{
    // Threshold values for different voltage ranges
    LVD_THRESHOLD_L_THR11 = 0xB,  /*!< Low range threshold 1.78V */
    LVD_THRESHOLD_L_THR12 = 0xC,  /*!< Low range threshold 1.84V */
    LVD_THRESHOLD_L_THR13 = 0xD,  /*!< Low range threshold 1.90V */
    LVD_THRESHOLD_L_THR14 = 0xE,  /*!< Low range threshold 1.96V */
    LVD_THRESHOLD_L_THR15 = 0xF,  /*!< Low range threshold 2.04V */
    
    LVD_THRESHOLD_M_1P80V = 0x12, /*!< Medium range threshold 1.80V */
    LVD_THRESHOLD_M_1P90V = 0x13, /*!< Medium range threshold 1.90V */
    LVD_THRESHOLD_M_2P00V = 0x14, /*!< Medium range threshold 2.00V */
    LVD_THRESHOLD_M_2P10V = 0x15, /*!< Medium range threshold 2.10V */
    LVD_THRESHOLD_M_2P20V = 0x16, /*!< Medium range threshold 2.20V */
    LVD_THRESHOLD_M_2P30V = 0x17, /*!< Medium range threshold 2.30V */
    LVD_THRESHOLD_M_2P40V = 0x18, /*!< Medium range threshold 2.40V */
    LVD_THRESHOLD_M_2P50V = 0x19, /*!< Medium range threshold 2.50V */
    LVD_THRESHOLD_M_2P60V = 0x1A, /*!< Medium range threshold 2.60V */
    LVD_THRESHOLD_M_2P70V = 0x1B, /*!< Medium range threshold 2.70V */
    LVD_THRESHOLD_M_2P80V = 0x1C, /*!< Medium range threshold 2.80V */
    LVD_THRESHOLD_M_2P90V = 0x1D, /*!< Medium range threshold 2.90V */
    LVD_THRESHOLD_M_3P00V = 0x1E, /*!< Medium range threshold 3.00V */
    LVD_THRESHOLD_M_3P10V = 0x1F, /*!< Medium range threshold 3.10V */
    
    LVD_THRESHOLD_H_2P91V = 0x20, /*!< High range threshold 2.91V */
    LVD_THRESHOLD_H_3P08V = 0x21, /*!< High range threshold 3.08V */
    LVD_THRESHOLD_H_3P25V = 0x22, /*!< High range threshold 3.25V */
    LVD_THRESHOLD_H_3P44V = 0x23  /*!< High range threshold 3.44V */
}LVD_THRESHOLD_VAL_ENUM;


typedef enum { 
    LVD_INT_HIGH =     0x1,  /*!< Interrupt on high level detection */
    LVD_INT_LOW =      0x2,  /*!< Interrupt on low level detection */
    LVD_INT_RISING =   0x4,  /*!< Interrupt on rising edge detection */
    LVD_INT_FALLING =  0x8,  /*!< Interrupt on falling edge detection */
    LVD_INT_HIGH_LOW = 0x3,  /*!< Interrupt on both high and low level detection */
    LVD_INT_EDGE= 0xC        /*!< Interrupt on both rising and falling edge detection */
}LVD_INT_TYPE_ENUM;


typedef struct
{
    uint32_t LVD_Threshold;  /*!< Specifies the LVD threshold voltage level */
    uint32_t LVD_Input;      /*!< Specifies the LVD input source selection */
    uint32_t LVD_IT;         /*!< Specifies the LVD interrupt trigger type */
    uint32_t LVD_Reset;      /*!< Specifies whether LVD reset is enabled */
}LVD_InitTypeDef;

/**
 * @brief Enable Low Voltage Detection (LVD) function
 *        Enables both analog and digital parts of the LVD module
 */
void lvd_enable(void);

/**
 * @brief Disable Low Voltage Detection (LVD) function
 *        Disables both analog and digital parts of the LVD module
 */
void lvd_disable(void);

/**
 * @brief Enable LVD reset function
 *        Allows LVD to trigger system reset when low voltage is detected
 */
void lvd_reset_en(void);

/**
 * @brief Set LVD detection threshold voltage
 * @param lvd_threshold LVD threshold voltage selection from @ref LVD_THRESHOLD_VAL_ENUM
 */
void lvd_set_threshold(LVD_THRESHOLD_VAL_ENUM lvd_threshold);

/**
 * @brief Set LVD interrupt trigger type
 * @param lvd_int_type LVD interrupt type selection from @ref LVD_INT_TYPE_ENUM
 */
void lvd_set_int_type(LVD_INT_TYPE_ENUM lvd_int_type);

/**
 * @brief Clear LVD interrupt status flag
 */
void lvd_int_clear(void);

/**
 * @brief Get current LVD interrupt status
 * @return Returns LVD interrupt status value (bits 24-27 of LVD control register)
 */
uint8_t lvd_get_interrupt_status(void);

/**
 * @brief Initialize LVD module with specified configuration
 * @param lvd_init Pointer to @ref LVD_InitTypeDef structure containing initialization parameters
 */
void lvd_init(LVD_InitTypeDef *lvd_init);

#endif
