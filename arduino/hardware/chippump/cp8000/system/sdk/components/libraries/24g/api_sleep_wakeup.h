/*************************************************************************************************
 * @file api_sleep_wakeup.h
 * @author BLE GROUP ()
 * @brief 
 * @version    1.0.1
 * @date       2025-03-08
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __API_SLEEP_WAKEUP_H__
#define __API_SLEEP_WAKEUP_H__
#include <stdint.h>
#include <stdbool.h>



uint32_t enter_sleep_mode(void);

void config_sleep_duation(uint32_t sleep_ms);


void unused_gpio_mask_parse_and_set(unsigned int gpio_mask);


//wkup_type: 0 timeout,  1 GPIO trigger
//reture: 0 goto sleep again, 1 fully wake-up
uint8_t sleep_wakeup_handler(uint32_t wakeup_type);

extern uint8_t  gpio_vdd_pin1;
extern uint8_t  gpio_vdd_pin2;
extern uint8_t  has_flash;

extern uint8_t has_otp;
extern uint32_t unused_gpio_mask_when_sleep;
extern uint32_t sleep_wakeup_reason;

#endif