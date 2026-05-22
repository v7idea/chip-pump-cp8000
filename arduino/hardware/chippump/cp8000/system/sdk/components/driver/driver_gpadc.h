/*************************************************************************************************
 * @file       driver_gpadc.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __DRIVER_GPADC_H__
#define __DRIVER_GPADC_H__

#include <stdint.h>
#include "mcu.h"



// library
extern void clkcal_delayus(int us);
extern void clkcal_delayms(int ms);
#ifndef DELAY_US
#define DELAY_US(d) clkcal_delayus(d)
#endif
#ifndef DELAY_MS
#define DELAY_MS(d) clkcal_delayms(d)
#endif

// 低压校准表
extern const int8_t gpadc_voltoffset[][15];
extern const int8_t gpadc_batvoltoffset[];

// global
extern uint16_t g_gpadc_vbat;

#define REG_GPADC_LDO_VC            *(volatile uint32_t *)(0X40080104)
#define REG_GPADC_LDO_EN            *(volatile uint8_t *)(0X42002004)
#define REG_TEMPERATURE_SENSOR_EN   *(volatile uint8_t *)(0X420020E8)

#define GPADC_SAMP_MAX              1024
#define GPADC_DIV1_VOLT_MAX         900
#define GPADC_DIV1_CALI_VHI         600
#define GPADC_DIV1_CALI_VLO         200
#define GPADC_CALI_ZOOM             4096
#define GPADC_FIX_COEF              256

#define GPADC_CALI_DIV1_DELTA_HI    0//1497
#define GPADC_CALI_DIV1_DELTA_LO    0//1354
#define GPADC_CALI_DIV2_DELTA_HI    0//1005
#define GPADC_CALI_DIV2_DELTA_LO    0//723
// #define GPADC_CALI_DIV3_DELTA_HI    787    //1800mV
// #define GPADC_CALI_DIV3_DELTA_LO    461    //600mV
// #define GPADC_CALI_DIV4_DELTA_HI    589    //2400mV
// #define GPADC_CALI_DIV4_DELTA_LO    403    //800mV
#define GPADC_CALI_DIV3_DELTA_HI    0//640     //2400mV
#define GPADC_CALI_DIV3_DELTA_LO    0//576    //1800mV
#define GPADC_CALI_DIV4_DELTA_HI    0//768     //3200mV
#define GPADC_CALI_DIV4_DELTA_LO    0//768     //2600mV
#define GPADC_CALI_VBAT_DELTA_LO    0//768
#define GPADC_CALI_VBAT_DELTA_HI    0//859

#define GPADC_OTP_INTERNAL_RESISTANCE  REG_RD(0x1f803f6c)

#define GPADC_OTP_CALI_DIV1_HIGH    REG_RD(0x1f803f3c)
#define GPADC_OTP_CALI_DIV1_LOW     REG_RD(0x1f803f40)
#define GPADC_OTP_CALI_DIV2_HIGH    REG_RD(0x1f803f44)
#define GPADC_OTP_CALI_DIV2_LOW     REG_RD(0x1f803f48)
#define GPADC_OTP_CALI_DIV3_HIGH    REG_RD(0x1f803f4c)
#define GPADC_OTP_CALI_DIV3_LOW     REG_RD(0x1f803f50)
#define GPADC_OTP_CALI_DIV4_HIGH    REG_RD(0x1f803f54)
#define GPADC_OTP_CALI_DIV4_LOW     REG_RD(0x1f803f58)
#define GPADC_OTP_CALI_VBAT_HIGH    REG_RD(0x1f803f70)
#define GPADC_OTP_CALI_VBAT_LOW     REG_RD(0x1f803f74)

#define GPADC_DIV1_VALID_MIN        0
#define GPADC_DIV1_VALID_MAX        140
#define GPADC_DIV2_VALID_MIN        120
#define GPADC_DIV2_VALID_MAX        1700
#define GPADC_DIV3_VALID_MIN        1600
#define GPADC_DIV3_VALID_MAX        2600
#define GPADC_DIV4_VALID_MIN        2500
#define GPADC_DIV4_VALID_MAX        4000


#define GPADC_CLK_SRC_RC24M         0
#define GPADC_CLK_SRC_XT24M         1

#define GPADC_AVG_NUM_1             0
#define GPADC_AVG_NUM_2             1
#define GPADC_AVG_NUM_4             2
#define GPADC_AVG_NUM_8             3
#define GPADC_AVG_NUM_16            4
#define GPADC_AVG_NUM_32            5
#define GPADC_AVG_NUM_64            6
#define GPADC_AVG_NUM_128           7
#define GPADC_AVG_NUM_256           8

#define GPADC_INPUT_DIV1            0
#define GPADC_INPUT_DIV2            1
#define GPADC_INPUT_DIV3            2
#define GPADC_INPUT_DIV4            3

#define GPADC_CHANNEL_N_GPIO2       0
#define GPADC_CHANNEL_N_GPIO6       1
#define GPADC_CHANNEL_N_GPIO7       2
#define GPADC_CHANNEL_N_GPIO10      3
#define GPADC_CHANNEL_N_GPIO15      4
#define GPADC_CHANNEL_N_GPIO17      5
#define GPADC_CHANNEL_N_GPIO19      6
#define GPADC_CHANNEL_N_GPIO21      7
#define GPADC_CHANNEL_N_REF0V9      8

#define GPADC_CHANNEL_P_GPIO2       0
#define GPADC_CHANNEL_P_GPIO6       1
#define GPADC_CHANNEL_P_GPIO7       2
#define GPADC_CHANNEL_P_GPIO10      3
#define GPADC_CHANNEL_P_GPIO15      4
#define GPADC_CHANNEL_P_GPIO17      5
#define GPADC_CHANNEL_P_GPIO19      6
#define GPADC_CHANNEL_P_GPIO21      7
#define GPADC_CHANNEL_P_TEMP        8
#define GPADC_CHANNEL_P_BAT         9
#define GPADC_CHANNEL_P_CIN         10
#define GPADC_CHANNEL_P_CSUP        11

// #define GPADC_CHANNEL_GPIO2         0
// #define GPADC_CHANNEL_GPIO6         1
// #define GPADC_CHANNEL_GPIO7         2
// #define GPADC_CHANNEL_GPIO10        3
// #define GPADC_CHANNEL_GPIO15        4
// #define GPADC_CHANNEL_GPIO17        5
// #define GPADC_CHANNEL_GPIO19        6
// #define GPADC_CHANNEL_GPIO21        7
// #define GPADC_CHANNEL_TEMP          8
// #define GPADC_CHANNEL_BAT           9
// #define GPADC_CHANNEL_CIN           10
// #define GPADC_CHANNEL_CSUP          11

#define GPADC_CHANNEL_0             0
#define GPADC_CHANNEL_1             1
#define GPADC_CHANNEL_2             2
#define GPADC_CHANNEL_3             3
#define GPADC_CHANNEL_4             4
#define GPADC_CHANNEL_5             5
#define GPADC_CHANNEL_6             6
#define GPADC_CHANNEL_7             7
#define GPADC_CHANNEL_8             8
#define GPADC_CHANNEL_9             9
#define GPADC_CHANNEL_10            10
#define GPADC_CHANNEL_11            11

#define GPADC_TRIG_TIMER_0          0
#define GPADC_TRIG_TIMER_1          1
#define GPADC_TRIG_TIMER_2          2
#define GPADC_TRIG_TIMER_3          3
#define GPADC_TRIG_TIMER_4          4
#define GPADC_TRIG_TIMER_5          5
#define GPADC_TRIG_TIMER_6          6
#define GPADC_TRIG_TIMER_7          7

#define GPADC_FLAG_SAMP             0x02
#define GPADC_FLAG_DMA              0x01
#define GPADC_ITMODE_SAMP           0x02
#define GPADC_ITMODE_DMA            0x01


/** 
 *  @brief GPADC channel enumeration definition 
 *  @note Channels 0-7 correspond to GPIO pins, 8-11 for internal sensors 
 **/
typedef enum
{
   GPADC_CHANNEL_GPIO2 =        0,
   GPADC_CHANNEL_GPIO6 =        1,
   GPADC_CHANNEL_GPIO7 =        2,
   GPADC_CHANNEL_GPIO10 =       3,
   GPADC_CHANNEL_GPIO15 =       4,
   GPADC_CHANNEL_GPIO17 =       5,
   GPADC_CHANNEL_GPIO19 =       6,
   GPADC_CHANNEL_GPIO21 =       7,
   GPADC_CHANNEL_TEMP  =        8,
   GPADC_CHANNEL_BAT   =        9,
   GPADC_CHANNEL_CIN   =        10,
   GPADC_CHANNEL_CSUP  =        11
}GPADC_ChannelTypeDef;


/** @brief GPADC initialization structure 
 *  @details Configures ADC operating parameters 
 **/
typedef struct 
{
   uint8_t GPADC_InputDivide;
   FunctionalState GPADC_DiffEN;
   uint8_t GPADC_NegativeInputChannel;
   uint8_t GPADC_PositiveInputChannel;  //配置为GPADC_CHANNEL_P_BAT通道时，分压系数必须使用GPADC_INPUT_DIV4
   uint8_t GPADC_AverageWindow;
   FunctionalState GPADC_TimerTrigEN;
   uint8_t GPADC_TimerSelect;
   FunctionalState GPADC_ContinueMode;
   uint8_t GPADC_ClkDivide;
   uint8_t GPADC_ClkSelect;
   FunctionalState GPADC_ClkAutoGate;
} GPADC_InitTypeDef;


typedef enum
{
   GPADC_DMASTARTADDR_0X2000_2000 = 0,
   GPADC_DMASTARTADDR_0X2000_2800 = 1,
   GPADC_DMASTARTADDR_0X2000_3000 = 2,
   GPADC_DMASTARTADDR_0X2000_3800 = 3, 
} GPADC_DMASTARTADDR;

typedef enum
{
   GPADC_DMAENDADDR_0X2000_27FF = 0,
   GPADC_DMAENDADDR_0X2000_2FFF = 1,
   GPADC_DMAENDADDR_0X2000_37FF = 2,
   GPADC_DMAENDADDR_0X2000_3FFF = 3, 
} GPADC_DMAENDADDR;


void gpadc_ClearFlag(uint8_t ADC_FLAG);
void gpadc_itConfig(uint8_t ADC_ITMODE, FunctionalState NewState);
FlagStatus gpadc_get_status(uint8_t ADC_FLAG);
/**
 * @brief Enable/disable ADC module
 * @param NewState ENABLE/DISABLE control flag
 * @note Disabling preserves configuration but stops conversions
 */
void gpadc_cmd(FunctionalState NewState);

/**
 * @brief Smart sampling with automatic range switching
 * @return Valid voltage or 0xFFFF on error
 * 
 * @algorithm
 * 1. Take initial measurement
 * 2. Verify within current range validity window
 * 3. If out-of-range:
 *    - Switch to appropriate divider
 *    - Retry measurement
 *    - Max 4 attempts to prevent loop lock
 */
uint16_t gpadc_get_samplevoltage(void);

/**
 * @brief Update battery voltage measurement
 * @return Measured battery voltage in millivolts (mV), 
 *         returns 0xFFFF if measurement is invalid
 * 
 * @note This function performs the following operations:
 * 1. Configures ADC to battery channel (BAT) with appropriate settings
 * 2. Performs voltage sampling using pre-configured calibration data
 * 3. Applies temperature compensation and linearization
 * 4. Updates global battery voltage variable (g_gpadc_vbat)
 * 5. Validates measurement against configured voltage ranges
 * 
 * @attention When using this function:
 * - Ensure LDO and ADC clock are properly initialized
 * - The input divider must be configured as GPADC_INPUT_DIV4
 * - Calibration data from OTP should be pre-loaded
 */
uint16_t gpadc_get_sampleBAT(void);

/**
 * @brief Get the sampled voltage value for a specified GPADC channel
 * 
 * This function samples the voltage on a given ADC channel. It handles battery channels
 * (GPADC_CHANNEL_P_BAT) differently from other channels:
 * - For battery channels: Uses dedicated calibration coefficients and applies battery-specific compensation
 * - For other channels: Performs adaptive voltage range switching with up to 4 sampling attempts
 * 
 * @param adc_ch Target ADC channel to sample (GPADC_ChannelTypeDef)
 * 
 * @return uint16_t 
 *   - Sampled voltage in millivolts (mV) for valid measurements
 *   - Returns 0 for invalid measurements (out-of-range after 4 attempts)
 * 
 * @process
 * 1. Saves current GPADC configuration registers (CTRL, CLK_CTRL, ACTION, EN)
 * 2. Switches to target channel using gpadc_changeChannel()
 * 3. Configures ADC clock (0x30E) and sampling parameters (0x7002)
 * 4. Triggers conversion and waits for completion
 * 5. Channel-specific processing:
 *    a) BAT channels:
 *       - Applies linear calibration: volt = (raw_sample * a + b)/GPADC_CALI_ZOOM
 *       - Performs battery voltage compensation via gpadc_InternalSearchBATVoltageOffset()
 *       - Updates global battery voltage (g_gpadc_vbat)
 *    b) Other channels:
 *       - Performs up to 4 sampling attempts with dynamic range adjustment
 *       - Validates voltage against divider-specific ranges (DIV1-DIV4)
 *       - Adjusts divider coefficient dynamically based on voltage reading
 * 6. Restores original GPADC configuration
 * 7. Clamps negative voltages to 0 before return
 */
uint16_t gpadc_get_sample(GPADC_ChannelTypeDef adc_ch);

/**
 * @brief Initialize general-purpose ADC channel configuration
 * @param channel ADC analog input channel to configure (refer to GPADC_ChannelTypeDef enum)
 * 
 * Function workflow:
 * 1. Initialize ADC configuration structure with default parameters
 * 2. Configure channel-specific ADC acquisition parameters:
 *    - Input divider ratio (DIV4)
 *    - Single-ended measurement mode
 *    - 128-sample averaging
 *    - Single conversion mode
 * 3. Apply hardware configuration
 * 4. Perform ADC calibration
 * 5. Enable ADC module
 */
void gpadc_channel_Init(GPADC_ChannelTypeDef channel);


uint16_t gpadc_get_sample_tmp(GPADC_ChannelTypeDef adc_ch, uint8_t gain);

#endif

     