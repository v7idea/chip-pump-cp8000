/*************************************************************************************************
 * @file       global.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.0
 * @date       2024-07-25
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "mcu.h"
#include "mcu_reg_def.h"

#define CONFIG_BT_MAX_CONN_NEW   2
#define CONFIG_BT_MAX_CONN    ble_max_conn_nr

#define CONFIG_BT_SMP
#define CONFIG_BT_CONN        1
#define CONFIG_BT_HCI_RESERVE 4

#define BLE_LL_GAP_TIME_DEFAULT  110

#endif