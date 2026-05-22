/*************************************************************************************************
 * @file driver_lvd.c
 * @author BLE GROUP ()
 * @brief 
 * @version 1.0.0
 * @date 2025-06-27
 * 
 * 
*************************************************************************************************/
#include "mcu_reg_def.h"
#include "driver_lvd.h"

/**
 * @brief Enable Low Voltage Detection (LVD) function
 *        Enable both analog and digital parts of the LVD module
 */
void lvd_enable(void)
{
    SYS_CTRL->LVD_CTRL_ANA_b.DA_LVD_EN = 1;  // Enable analog part of LVD
    SYS_CTRL->LVD_CTRL_DIG_b.LVD_EN =1;      // Enable digital part of LVD
}

/**
 * @brief Disable Low Voltage Detection (LVD) function
 *        Disable both analog and digital parts of the LVD module
 */
void lvd_disable(void)
{
    SYS_CTRL->LVD_CTRL_ANA_b.DA_LVD_EN = 0;  // Disable analog part of LVD
    SYS_CTRL->LVD_CTRL_DIG_b.LVD_EN =0;      // Disable digital part of LVD
}

/**
 * @brief Enable LVD reset function
 *        Allow LVD to trigger system reset when low voltage is detected
 */
void lvd_reset_en(void)
{
	SYS_CTRL->LVD_CTRL_DIG_b.LVD_RST_EN =1;  // Enable LVD reset function
}

/**
 * @brief Set LVD detection input source
 * @param input LVD detection input source selection, refer to @ref LVD_DECT_INPUT_ENUM enumeration
 */
void lvd_set_input(LVD_DECT_INPUT_ENUM input)
{
	SYS_CTRL->LVD_CTRL_ANA_b.DA_LVD_SEL = input;  // Configure LVD input source selection
}

/**
 * @brief Set LVD detection threshold voltage
 * @param lvd_threshold LVD threshold voltage selection, refer to @ref LVD_THRESHOLD_VAL_ENUM enumeration
 */
void lvd_set_threshold(LVD_THRESHOLD_VAL_ENUM lvd_threshold)
{
    SYS_CTRL->LVD_CTRL_ANA_b.RG_LVD_VTHC = (lvd_threshold&0x3f);  // Configure LVD threshold voltage (lower 6 bits)
}

/**
 * @brief Set LVD reset enable status
 * @param reset_en Reset enable flag, 1-enable reset, 0-disable reset
 */
void lvd_set_reset(uint8_t reset_en)
{
    SYS_CTRL->LVD_CTRL_DIG_b.LVD_RST_EN = reset_en;  // Configure LVD reset enable
}

/**
 * @brief Set LVD interrupt type
 * @param lvd_int_type LVD interrupt type configuration, refer to @ref LVD_INT_TYPE_ENUM enumeration
 */
void lvd_set_int_type(LVD_INT_TYPE_ENUM lvd_int_type)
{
    uint32_t lvd_int_type_val = SYS_CTRL->LVD_CTRL_DIG;
    lvd_int_type_val &= ~(0x0F << 16);  // Clear previous interrupt type configuration (bits 16-19)
    SYS_CTRL->LVD_CTRL_DIG = lvd_int_type_val | (lvd_int_type << 16);  // Set new interrupt type configuration
    if(lvd_int_type&0xF)  // If interrupt type is non-zero, enable LVD interrupt
        SYS_CTRL->LVD_CTRL_DIG_b.LVD_INT_EN = 1;
}

/**
 * @brief Clear LVD interrupt status flag
 */
void lvd_int_clear(void)
{
    SYS_CTRL->LVD_CTRL_DIG_b.LVD_STAT_CLR = 1;  // Write 1 to clear LVD interrupt status flag
}

/**
 * @brief Get LVD interrupt status
 * @return Returns current LVD interrupt status (bits 24-27)
 */
uint8_t lvd_get_interrupt_status(void)
{
    uint32_t lvd_int_type_status = SYS_CTRL->LVD_CTRL_DIG;
    return (lvd_int_type_status>>24)&0xF;  // Extract and return interrupt status bits
}

/**
 * @brief Initialize LVD module
 * @param lvd_init Pointer to LVD initialization configuration structure, containing threshold and interrupt type settings
 */
void lvd_init(LVD_InitTypeDef *lvd_init)
{
    lvd_set_threshold(lvd_init->LVD_Threshold);  // Set LVD threshold voltage
    lvd_set_int_type(lvd_init->LVD_IT);          // Set LVD interrupt type
    NVIC_SetPriority(Interrupt23_IRQn, IRQ_HIGH_PRIORITY);  // Set LVD interrupt priority to high
    NVIC_EnableIRQ(Interrupt23_IRQn);            // Enable LVD interrupt
    lvd_enable();                                // Enable LVD module
}

