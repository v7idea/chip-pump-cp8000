/*************************************************************************************************
 * @file       mcu_reg_def.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-03-08
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/

#ifndef __MCU_REG_DEF__
#define __MCU_REG_DEF__


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "mcu.h"

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                         SYS_CTRL                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief SYS_CTRL (SYS_CTRL)
  */

typedef struct {                                /*!< (@ 0x40000000) SYS_CTRL Structure                                         */
  
  union {
    __IOM uint16_t REVISION;                    /*!< (@ 0x00000000) REVISION                                                   */
    
    struct {
      __IM  uint16_t REVISION   : 16;           /*!< [15..0] nan                                                               */
    } REVISION_b;
  } ;
  __IM  uint16_t  RESERVED;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IOM uint32_t SYS_RESET;                   /*!< (@ 0x00000008) SYS_RESET                                                  */
    
    struct {
      __IOM uint32_t REG_SWRST  : 32;           /*!< [31..0] nan                                                               */
    } SYS_RESET_b;
  } ;
  
  union {
    __IOM uint8_t SYS_STATUS;                   /*!< (@ 0x0000000C) SYS_STATUS                                                 */
    
    struct {
      __IM  uint8_t CRYSTAL_STABLE : 1;         /*!< [0..0] nan                                                                */
      __IM  uint8_t LPO_CLOCK   : 1;            /*!< [1..1] nan                                                                */
      __IM  uint8_t CODE_CRC_FAIL : 1;          /*!< [2..2] nan                                                                */
            uint8_t             : 5;
    } SYS_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED2;
  __IM  uint16_t  RESERVED3;
  __IM  uint32_t  RESERVED4;
  
  union {
    __IOM uint16_t LOCKUP_CTRL;                 /*!< (@ 0x00000014) LOCKUP_CTRL                                                */
    
    struct {
      __IOM uint16_t LOCKUP_RESET_EN : 1;       /*!< [0..0] nan                                                                */
      __IOM uint16_t LOCKUP_RESET_MODE : 1;     /*!< [1..1] nan                                                                */
      __IOM uint16_t MATRIX_BUS_GATE_EN : 1;    /*!< [2..2] nan                                                                */
      __IOM uint16_t MATRIX_WDATA_GATE_EN : 1;  /*!< [3..3] nan                                                                */
            uint16_t            : 4;
      __IOM uint16_t LOCKUP_RESET_CNT : 8;      /*!< [15..8] nan                                                               */
    } LOCKUP_CTRL_b;
  } ;
  __IM  uint16_t  RESERVED5;
  __IM  uint32_t  RESERVED6[3];
  
  union {
    __IOM uint32_t SYS_CLKSEL;                  /*!< (@ 0x00000024) SYS_CLKSEL                                                 */
    
    struct {
      __IOM uint32_t REG_QSPI_CLK_SEL : 2;      /*!< [1..0] nan                                                                */
      __IOM uint32_t REG_QSPI_CLK_SYSSEL : 2;   /*!< [3..2] nan                                                                */
      __IOM uint32_t REG_CPU_CLK_SEL : 3;       /*!< [6..4] nan                                                                */
            uint32_t            : 1;
      __IOM uint32_t REG_CPU_CLK_SYSSEL : 2;    /*!< [9..8] nan                                                                */
      __IOM uint32_t REG_UART_CLK_SEL : 2;      /*!< [11..10] nan                                                              */
      __IOM uint32_t REG_CAP_CLK_SEL : 3;       /*!< [14..12] nan                                                              */
            uint32_t            : 1;
      __IOM uint32_t REG_OTP_CLK_SEL : 2;       /*!< [17..16] nan                                                              */
      __IOM uint32_t REG_SPIS0_CLK_SEL : 2;     /*!< [19..18] nan                                                              */
      __IOM uint32_t REG_LEDC_CLK_SEL : 2;     /*!< [21..20] nan                                                              */
            uint32_t            : 2;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } SYS_CLKSEL_b;
  } ;
  __IM  uint32_t  RESERVED7[2];
  
  union {
    __IOM uint16_t PWMTT_CLK_SYSSEL;            /*!< (@ 0x00000030) PWMTT_CLK_SYSSEL                                           */
    
    struct {
      __IOM uint16_t REG_PWMTT_CLK_SYSSEL : 16; /*!< [15..0] nan                                                               */
    } PWMTT_CLK_SYSSEL_b;
  } ;
  __IM  uint16_t  RESERVED8;
  
  union {
    __IOM uint32_t PWMTT_CLK_SEL;               /*!< (@ 0x00000034) PWMTT_CLK_SEL                                              */
    
    struct {
      __IOM uint32_t REG_PWMTT_CLK_SEL : 32;    /*!< [31..0] nan                                                               */
    } PWMTT_CLK_SEL_b;
  } ;
  
  union {
    __IOM uint8_t PWM_OUT_SEL;                  /*!< (@ 0x00000038) PWM_OUT_SEL                                                */
    
    struct {
      __IOM uint8_t PWM_OUT_SEL : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } PWM_OUT_SEL_b;
  } ;
  __IM  uint8_t   RESERVED9;
  __IM  uint16_t  RESERVED10;
  __IM  uint32_t  RESERVED11;
  
  union {
    __IOM uint8_t BIST_CTRL;                    /*!< (@ 0x00000040) BIST_CTRL                                                  */
    
    struct {
      __IOM uint8_t BIST_MODE   : 1;            /*!< [0..0] nan                                                                */
      __IOM uint8_t BIST_EN     : 1;            /*!< [1..1] nan                                                                */
      __IOM uint8_t BIST_MUX_MODE : 1;          /*!< [2..2] nan                                                                */
      __IOM uint8_t BIST_RST_EN : 1;            /*!< [3..3] nan                                                                */
      __IOM uint8_t BIST_TMR_EN : 1;            /*!< [4..4] nan                                                                */
            uint8_t             : 3;
    } BIST_CTRL_b;
  } ;
  __IM  uint8_t   RESERVED12;
  __IM  uint16_t  RESERVED13;
  
  union {
    __IOM uint32_t BIST_STATE;                  /*!< (@ 0x00000044) BIST_STATE                                                 */
    
    struct {
      __IM  uint32_t BIST_DONE  : 16;           /*!< [15..0] nan                                                               */
      __IM  uint32_t BIST_FAIL  : 16;           /*!< [31..16] nan                                                              */
    } BIST_STATE_b;
  } ;
  
  union {
    __IOM uint32_t BIST_STATE_NORST;            /*!< (@ 0x00000048) BIST_STATE_NORST                                           */
    
    struct {
      __IOM uint32_t BIST_DONE_NORST : 1;       /*!< [0..0] nan                                                                */
            uint32_t            : 15;
      __IM  uint32_t BIST_FAIL_NORST : 16;      /*!< [31..16] nan                                                              */
    } BIST_STATE_NORST_b;
  } ;
  __IM  uint32_t  RESERVED14;
  
  union {
    __IOM uint16_t OTP_CTRL;                    /*!< (@ 0x00000050) OTP_CTRL                                                   */
    
    struct {
      __IOM uint16_t OTP_CTRL   : 11;           /*!< [10..0] nan                                                               */
            uint16_t            : 5;
    } OTP_CTRL_b;
  } ;
  __IM  uint16_t  RESERVED15;
  
  union {
    __IOM uint32_t OTP_PADDR;                   /*!< (@ 0x00000054) OTP_PADDR                                                  */
    
    struct {
      __IOM uint32_t OTP_PAIO   : 6;            /*!< [5..0] nan                                                                */
            uint32_t            : 2;
      __IOM uint32_t OTP_PA     : 12;           /*!< [19..8] nan                                                               */
      __IOM uint32_t OTP_PA_EN  : 1;            /*!< [20..20] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } OTP_PADDR_b;
  } ;
  
  union {
    __IOM uint32_t OTP_PDIN;                    /*!< (@ 0x00000058) OTP_PDIN                                                   */
    
    struct {
      __IOM uint32_t OTP_PDIN   : 32;           /*!< [31..0] nan                                                               */
    } OTP_PDIN_b;
  } ;
  
  union {
    __IOM uint32_t OTP_PDOUT;                   /*!< (@ 0x0000005C) OTP_PDOUT                                                  */
    
    struct {
      __IM  uint32_t OTP_PDOUT  : 32;           /*!< [31..0] nan                                                               */
    } OTP_PDOUT_b;
  } ;
  
  union {
    __IOM uint8_t OTP_PRG_STATE;                /*!< (@ 0x00000060) OTP_PRG_STATE                                              */
    
    struct {
      __IM  uint8_t OTP_PRG_STATE : 3;          /*!< [2..0] nan                                                                */
            uint8_t             : 5;
    } OTP_PRG_STATE_b;
  } ;
  __IM  uint8_t   RESERVED16;
  __IM  uint16_t  RESERVED17;
  
  union {
    __IOM uint32_t OTP_PRG_CFG0;                /*!< (@ 0x00000064) OTP_PRG_CFG0                                               */
    
    struct {
      __IOM uint32_t OTP_TCSP   : 6;            /*!< [5..0] nan                                                                */
            uint32_t            : 2;
      __IOM uint32_t OTP_TCSH   : 4;            /*!< [11..8] nan                                                               */
            uint32_t            : 4;
      __IOM uint32_t OTP_TPPS   : 5;            /*!< [20..16] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t OTP_TPPH   : 5;            /*!< [28..24] nan                                                              */
            uint32_t            : 3;
    } OTP_PRG_CFG0_b;
  } ;
  
  union {
    __IOM uint32_t OTP_PRG_CFG1;                /*!< (@ 0x00000068) OTP_PRG_CFG1                                               */
    
    struct {
      __IOM uint32_t OTP_TPW    : 6;            /*!< [5..0] nan                                                                */
            uint32_t            : 2;
      __IOM uint32_t OTP_TPWI   : 4;            /*!< [11..8] nan                                                               */
            uint32_t            : 4;
      __IOM uint32_t OTP_PRG_PULSE : 6;         /*!< [21..16] nan                                                              */
            uint32_t            : 2;
      __IOM uint32_t OTP_PWE_MODE : 1;          /*!< [24..24] nan                                                              */
            uint32_t            : 7;
    } OTP_PRG_CFG1_b;
  } ;
  __IM  uint32_t  RESERVED18;
  
  union {
    __IOM uint8_t CLKCAL_CTRL;                  /*!< (@ 0x00000070) CLKCAL_CTRL                                                */
    
    struct {
      __IOM uint8_t CLKCAL_ENABLE : 1;          /*!< [0..0] nan                                                                */
      __IOM uint8_t CLKCAL_RESET : 1;           /*!< [1..1] nan                                                                */
      __IOM uint8_t CLKCAL_INT_EN : 1;          /*!< [2..2] nan                                                                */
      __IOM uint8_t CLKCAL_INT_CLR : 1;         /*!< [3..3] nan                                                                */
      __IM  uint8_t CLKCAL_FINISH : 1;          /*!< [4..4] nan                                                                */
      __IM  uint8_t CLKCAL_INT  : 1;            /*!< [5..5] nan                                                                */
            uint8_t             : 2;
    } CLKCAL_CTRL_b;
  } ;
  __IM  uint8_t   RESERVED19;
  __IM  uint16_t  RESERVED20;
  
  union {
    __IOM uint16_t CLKCAL_CLKSEL;               /*!< (@ 0x00000074) CLKCAL_CLKSEL                                              */
    
    struct {
      __IOM uint16_t CLKCAL_CLK0_SEL : 5;       /*!< [4..0] nan                                                                */
            uint16_t            : 3;
      __IOM uint16_t CLKCAL_CLK1_SEL : 5;       /*!< [12..8] nan                                                               */
            uint16_t            : 3;
    } CLKCAL_CLKSEL_b;
  } ;
  __IM  uint16_t  RESERVED21;
  
  union {
    __IOM uint32_t CLKCAL_CNT0;                 /*!< (@ 0x00000078) CLKCAL_CNT0                                                */
    
    struct {
      __IOM uint32_t CLKCAL_CNT0 : 32;          /*!< [31..0] nan                                                               */
    } CLKCAL_CNT0_b;
  } ;
  
  union {
    __IOM uint32_t CLKCAL_CNT1;                 /*!< (@ 0x0000007C) CLKCAL_CNT1                                                */
    
    struct {
      __IM  uint32_t CLKCAL_CNT1 : 32;          /*!< [31..0] nan                                                               */
    } CLKCAL_CNT1_b;
  } ;
  __IM  uint32_t  RESERVED22[4];
  
  union {
    __IOM uint8_t SPIS0_CTRL;                   /*!< (@ 0x00000090) SPIS0_CTRL                                                 */
    
    struct {
      __IOM uint8_t SPIS0_NCS_FORCE_EN : 1;     /*!< [0..0] nan                                                                */
      __IOM uint8_t SPIS0_NCS_FORCE_VAL : 1;    /*!< [1..1] nan                                                                */
            uint8_t             : 6;
    } SPIS0_CTRL_b;
  } ;
  __IM  uint8_t   RESERVED23;
  __IM  uint16_t  RESERVED24;
  __IM  uint32_t  RESERVED25[7];
  
  union {
    __IOM uint32_t AON_RTC;                     /*!< (@ 0x000000B0) AON_RTC                                                    */
    
    struct {
      __IM  uint32_t AON_RTC    : 32;           /*!< [31..0] nan                                                               */
    } AON_RTC_b;
  } ;
  
  union {
    __IOM uint32_t AON_RTC_TO;                  /*!< (@ 0x000000B4) AON_RTC_TO                                                 */
    
    struct {
      __IOM uint32_t AON_RTC_TO : 32;           /*!< [31..0] nan                                                               */
    } AON_RTC_TO_b;
  } ;
  
  union {
    __IOM uint16_t AON_RTC_IRQ;                 /*!< (@ 0x000000B8) AON_RTC_IRQ                                                */
    
    struct {
      __IOM uint16_t AON_RTC_TO_IE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint16_t AON_RTC_OVFL_IE : 1;       /*!< [1..1] nan                                                                */
            uint16_t            : 6;
      __IOM uint16_t AON_RTC_TO_IS : 1;         /*!< [8..8] nan                                                                */
      __IOM uint16_t AON_RTC_OVFL_IS : 1;       /*!< [9..9] nan                                                                */
            uint16_t            : 6;
    } AON_RTC_IRQ_b;
  } ;
  __IM  uint16_t  RESERVED26;
  __IM  uint32_t  RESERVED27;
  
  union {
    __IOM uint32_t LVD_CTRL_DIG;                /*!< (@ 0x000000C0) LVD_CTRL_DIG                                               */
    
    struct {
      __IOM uint32_t LVD_EN     : 1;            /*!< [0..0] nan                                                                */
      __IOM uint32_t LVD_RST_EN : 1;            /*!< [1..1] nan                                                                */
      __IOM uint32_t LVD_INT_EN : 1;            /*!< [2..2] nan                                                                */
      __IOM uint32_t LVD_FILT_EN : 1;           /*!< [3..3] nan                                                                */
      __OM  uint32_t LVD_STAT_CLR : 1;          /*!< [4..4] nan                                                                */
            uint32_t            : 1;
      __IM  uint32_t LVD_PIN_RAW : 1;           /*!< [6..6] nan                                                                */
      __IM  uint32_t LVD_PIN_FILT : 1;          /*!< [7..7] nan                                                                */
      __IOM uint32_t LVD_FILT_WIN : 5;          /*!< [12..8] nan                                                               */
            uint32_t            : 3;
      __IOM uint32_t LVD_HIGH_EN : 1;           /*!< [16..16] nan                                                              */
      __IOM uint32_t LVD_LOW_EN : 1;            /*!< [17..17] nan                                                              */
      __IOM uint32_t LVD_RISE_EN : 1;           /*!< [18..18] nan                                                              */
      __IOM uint32_t LVD_FALL_EN : 1;           /*!< [19..19] nan                                                              */
            uint32_t            : 4;
      __IM  uint32_t LVD_HIGH_STAT : 1;         /*!< [24..24] nan                                                              */
      __IM  uint32_t LVD_LOW_STAT : 1;          /*!< [25..25] nan                                                              */
      __IM  uint32_t LVD_RISE_STAT : 1;         /*!< [26..26] nan                                                              */
      __IM  uint32_t LVD_FALL_STAT : 1;         /*!< [27..27] nan                                                              */
            uint32_t            : 4;
    } LVD_CTRL_DIG_b;
  } ;
  
  union {
    __IOM uint16_t LVD_CTRL_ANA;                /*!< (@ 0x000000C4) LVD_CTRL_ANA                                               */
    
    struct {
      __IOM uint16_t RG_LVD_VTHC : 6;           /*!< [5..0] nan                                                                */
      __IOM uint16_t DA_LVD_SEL : 2;            /*!< [7..6] nan                                                                */
      __IOM uint16_t DA_LVD_EN  : 1;            /*!< [8..8] nan                                                                */
            uint16_t            : 7;
    } LVD_CTRL_ANA_b;
  } ;
  __IM  uint16_t  RESERVED28;
  __IM  uint32_t  RESERVED29[14];
  
  union {
    __IOM uint8_t WDT_SET;                      /*!< (@ 0x00000100) WDT_SET                                                    */
    
    struct {
      __IOM uint8_t WDT_CNT     : 8;            /*!< [7..0] nan                                                                */
    } WDT_SET_b;
  } ;
  __IM  uint8_t   RESERVED30;
  __IM  uint16_t  RESERVED31;
  
  union {
    __IOM uint8_t WDT_CFG;                      /*!< (@ 0x00000104) WDT_CFG                                                    */
    
    struct {
      __IOM uint8_t WDT_EN      : 1;            /*!< [0..0] nan                                                                */
      __IOM uint8_t WDT_INT_EN  : 1;            /*!< [1..1] nan                                                                */
            uint8_t             : 6;
    } WDT_CFG_b;
  } ;
  __IM  uint8_t   RESERVED32;
  __IM  uint16_t  RESERVED33;
  
  union {
    __IOM uint16_t WDT_STATUS;                  /*!< (@ 0x00000108) WDT_STATUS                                                 */
    
    struct {
      __IM  uint16_t WDT_CNT_MONITOR : 9;       /*!< [8..0] nan                                                                */
            uint16_t            : 3;
      __IM  uint16_t WDT_RST_STATUS : 1;        /*!< [12..12] nan                                                              */
      __IM  uint16_t WDT_RSTN   : 1;            /*!< [13..13] nan                                                              */
            uint16_t            : 2;
    } WDT_STATUS_b;
  } ;
  __IM  uint16_t  RESERVED34;
  __IM  uint32_t  RESERVED35;
  
  union {
    __IOM uint8_t SDMA_EN;                      /*!< (@ 0x00000110) SDMA_EN                                                    */
    
    struct {
      __IOM uint8_t SDMA_EN     : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } SDMA_EN_b;
  } ;
  __IM  uint8_t   RESERVED36;
  __IM  uint16_t  RESERVED37;
  
  union {
    __IOM uint32_t SDMA_TASK_TABLE_ADDR;        /*!< (@ 0x00000114) SDMA_TASK_TABLE_ADDR                                       */
    
    struct {
      __IOM uint32_t SDMA_TASK_TABLE_ADDR : 32; /*!< [31..0] nan                                                               */
    } SDMA_TASK_TABLE_ADDR_b;
  } ;
  
  union {
    __IOM uint8_t SDMA_ACTION;                  /*!< (@ 0x00000118) SDMA_ACTION                                                */
    
    struct {
      __IOM uint8_t SDMA_TASK_LOAD : 1;         /*!< [0..0] nan                                                                */
      __IOM uint8_t SDMA_TASK_ADD : 1;          /*!< [1..1] nan                                                                */
      __IOM uint8_t SDMA_TASK_REMOVE : 1;       /*!< [2..2] nan                                                                */
            uint8_t             : 5;
    } SDMA_ACTION_b;
  } ;
  __IM  uint8_t   RESERVED38;
  __IM  uint16_t  RESERVED39;
  
  union {
    __IOM uint32_t SDMA_TASK_VAL;               /*!< (@ 0x0000011C) SDMA_TASK_VAL                                              */
    
    struct {
      __IOM uint32_t SDMA_TASK_VAL : 32;        /*!< [31..0] nan                                                               */
    } SDMA_TASK_VAL_b;
  } ;
  
  union {
    __IOM uint32_t SDMA_TASK_STATUS;            /*!< (@ 0x00000120) SDMA_TASK_STATUS                                           */
    
    struct {
      __IM  uint32_t SDMA_TASK_STATUS : 32;     /*!< [31..0] nan                                                               */
    } SDMA_TASK_STATUS_b;
  } ;
  
  union {
    __IOM uint32_t SDMA_INT_STATUS;             /*!< (@ 0x00000124) SDMA_INT_STATUS                                            */
    
    struct {
      __IM  uint32_t SDMA_INT_STATUS : 32;      /*!< [31..0] nan                                                               */
    } SDMA_INT_STATUS_b;
  } ;
  
  union {
    __IOM uint32_t SDMA_INT_CLEAR;              /*!< (@ 0x00000128) SDMA_INT_CLEAR                                             */
    
    struct {
      __IOM uint32_t SDMA_INT_CLEAR : 32;       /*!< [31..0] nan                                                               */
    } SDMA_INT_CLEAR_b;
  } ;
} SYS_CTRL_Type;                                /*!< Size = 300 (0x12c)                                                        */



/* =========================================================================================================================== */
/* ================                                        GPIO_INOUT                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief GPIO_INOUT (GPIO_INOUT)
  */

typedef struct {                                /*!< (@ 0x40010010) GPIO_INOUT Structure                                       */
  
  union {
    __IOM uint32_t GPIO_FILT_CTRL;              /*!< (@ 0x00000000) GPIO_FILT_CTRL                                             */
    
    struct {
      __IOM uint32_t GPIO_GRP_EN : 3;           /*!< [2..0] nan                                                                */
            uint32_t            : 5;
      __IOM uint32_t GPIO_FILT_EN : 3;          /*!< [10..8] nan                                                               */
            uint32_t            : 5;
      __IOM uint32_t GPIO_FILT_WIN : 4;         /*!< [19..16] nan                                                              */
            uint32_t            : 4;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_FILT_CTRL_b;
  } ;
  __IM  uint32_t  RESERVED[3];
  
  union {
    __IOM uint32_t GPIO_I;                      /*!< (@ 0x00000010) GPIO_I                                                     */
    
    struct {
      __IM  uint32_t GPIO_I     : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_I_b;
  } ;
  __IM  uint32_t  RESERVED1[3];
  
  union {
    __IOM uint32_t GPIO_OE;                     /*!< (@ 0x00000020) GPIO_OE                                                    */
    
    struct {
      __IOM uint32_t GPIO_OE    : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_OE_b;
  } ;
  __IM  uint32_t  RESERVED2[3];
  
  union {
    __IOM uint32_t GPIO_O;                      /*!< (@ 0x00000030) GPIO_O                                                     */
    
    struct {
      __IOM uint32_t GPIO_O     : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_O_b;
  } ;
  __IM  uint32_t  RESERVED3[15];
  
  union {
    __IOM uint32_t GPIO_O_SET;                  /*!< (@ 0x00000070) GPIO_O_SET                                                 */
    
    struct {
      __OM  uint32_t GPIO_O_SET : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_O_SET_b;
  } ;
  __IM  uint32_t  RESERVED4[3];
  
  union {
    __IOM uint32_t GPIO_O_CLR;                  /*!< (@ 0x00000080) GPIO_O_CLR                                                 */
    
    struct {
      __OM  uint32_t GPIO_O_CLR : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_O_CLR_b;
  } ;

  __IM  uint32_t  RESERVED5[3];
  
  union {
    __IOM uint32_t GPIO_DS_0;                  /*!< (@ 0x00000090) GPIO_DS_0                                                  */
    
    struct {
      __OM  uint32_t GPIO_0_DS : 2;           /*!< [1..0] nan                                                                 */
      __OM  uint32_t GPIO_1_DS : 2;           /*!< [3..2] nan                                                                 */
      __OM  uint32_t GPIO_2_DS : 2;           /*!< [5..4] nan                                                                 */
      __OM  uint32_t GPIO_3_DS : 2;           /*!< [7..6] nan                                                                 */
      __OM  uint32_t GPIO_4_DS : 2;           /*!< [9..8] nan                                                                 */
      __OM  uint32_t GPIO_5_DS : 2;           /*!< [11..10] nan                                                               */
      __OM  uint32_t GPIO_6_DS : 2;           /*!< [13..12] nan                                                               */
      __OM  uint32_t GPIO_7_DS : 2;           /*!< [15..14] nan                                                               */
      __OM  uint32_t GPIO_8_DS : 2;           /*!< [17..16] nan                                                                 */
      __OM  uint32_t GPIO_9_DS : 2;           /*!< [19..18] nan                                                                 */
      __OM  uint32_t GPIO_10_DS : 2;           /*!< [21..20] nan                                                                 */
      __OM  uint32_t GPIO_11_DS : 2;           /*!< [23..22] nan                                                                 */
      __OM  uint32_t GPIO_12_DS : 2;           /*!< [25..24] nan                                                                 */
      __OM  uint32_t GPIO_13_DS : 2;           /*!< [27..26] nan                                                                 */
      __OM  uint32_t GPIO_14_DS : 2;           /*!< [29..28] nan                                                                 */
      __OM  uint32_t GPIO_15_DS : 2;           /*!< [31..30] nan                                                                 */
    } GPIO_DS_0_b;
  } ;

  union {
    __IOM uint32_t GPIO_DS_1;                  /*!< (@ 0x00000094) GPIO_DS_1                                                 */
    
    struct {
      __OM  uint32_t GPIO_16_DS : 2;           /*!< [1..0] nan                                                                 */
      __OM  uint32_t GPIO_17_DS : 2;           /*!< [3..2] nan                                                                 */
      __OM  uint32_t GPIO_18_DS : 2;           /*!< [5..4] nan                                                                 */
      __OM  uint32_t GPIO_19_DS : 2;           /*!< [7..6] nan                                                                 */
      __OM  uint32_t GPIO_20_DS : 2;           /*!< [9..8] nan                                                                 */
      __OM  uint32_t GPIO_21_DS : 2;           /*!< [11..10] nan                                                               */
      __OM  uint32_t GPIO_22_DS : 2;           /*!< [13..12] nan                                                               */
      __OM  uint32_t GPIO_23_DS : 2;           /*!< [15..14] nan                                                               */
      __IOM uint32_t RESERVE    : 16;            /*!< [31..16] nan                                                              */
    } GPIO_DS_1_b;
  } ;

} GPIO_INOUT_Type;                              /*!< Size = 132 (0x84)                                                         */



/* =========================================================================================================================== */
/* ================                                         GPIO_INTR                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief GPIO_INTR (GPIO_INTR)
  */

typedef struct {                                /*!< (@ 0x40010140) GPIO_INTR Structure                                        */
  
  union {
    __IOM uint32_t GPIO_IE;                     /*!< (@ 0x00000000) GPIO_IE                                                    */
    
    struct {
      __IOM uint32_t GPIO_IE    : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_IE_b;
  } ;
  __IM  uint32_t  RESERVED[3];
  
  union {
    __IOM uint32_t GPIO_IS;                     /*!< (@ 0x00000010) GPIO_IS                                                    */
    
    struct {
      __IOM uint32_t GPIO_IS    : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_IS_b;
  } ;
  __IM  uint32_t  RESERVED1[3];
  
  union {
    __IOM uint32_t GPIO_MIS;                    /*!< (@ 0x00000020) GPIO_MIS                                                   */
    
    struct {
      __IOM uint32_t GPIO_MIS   : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_MIS_b;
  } ;
  __IM  uint32_t  RESERVED2[3];
  
  union {
    __IOM uint32_t GPIO_IT_HI;                  /*!< (@ 0x00000030) GPIO_IT_HI                                                 */
    
    struct {
      __IOM uint32_t GPIO_IT_HI : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_IT_HI_b;
  } ;
  __IM  uint32_t  RESERVED3[3];
  
  union {
    __IOM uint32_t GPIO_IT_LO;                  /*!< (@ 0x00000040) GPIO_IT_LO                                                 */
    
    struct {
      __IOM uint32_t GPIO_IT_LO : 24;           /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_IT_LO_b;
  } ;
  __IM  uint32_t  RESERVED4[3];
  
  union {
    __IOM uint32_t GPIO_IT_PEDGE;               /*!< (@ 0x00000050) GPIO_IT_PEDGE                                              */
    
    struct {
      __IOM uint32_t GPIO_IT_PEDGE : 24;        /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_IT_PEDGE_b;
  } ;
  __IM  uint32_t  RESERVED5[3];
  
  union {
    __IOM uint32_t GPIO_IT_NEDGE;               /*!< (@ 0x00000060) GPIO_IT_NEDGE                                              */
    
    struct {
      __IOM uint32_t GPIO_IT_NEDGE : 24;        /*!< [23..0] nan                                                               */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } GPIO_IT_NEDGE_b;
  } ;
} GPIO_INTR_Type;                               /*!< Size = 100 (0x64)                                                         */



/* =========================================================================================================================== */
/* ================                                         GPIO_ATF                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief GPIO_ATF (GPIO_ATF)
  */

typedef struct {                                /*!< (@ 0x40010200) GPIO_ATF Structure                                         */
  
  union {
    __IOM uint32_t GPIO_CFG_0;                  /*!< (@ 0x00000000) GPIO_CFG_0                                                 */
    
    struct {
      __IOM uint32_t GPIO0_CFG  : 8;            /*!< [7..0] nan                                                                */
      __IOM uint32_t GPIO1_CFG  : 8;            /*!< [15..8] nan                                                               */
      __IOM uint32_t GPIO2_CFG  : 8;            /*!< [23..16] nan                                                              */
      __IOM uint32_t GPIO3_CFG  : 8;            /*!< [31..24] nan                                                              */
    } GPIO_CFG_0_b;
  } ;
  
  union {
    __IOM uint32_t GPIO_CFG_1;                  /*!< (@ 0x00000004) GPIO_CFG_1                                                 */
    
    struct {
      __IOM uint32_t GPIO4_CFG  : 8;            /*!< [7..0] nan                                                                */
      __IOM uint32_t GPIO5_CFG  : 8;            /*!< [15..8] nan                                                               */
      __IOM uint32_t GPIO6_CFG  : 8;            /*!< [23..16] nan                                                              */
      __IOM uint32_t GPIO7_CFG  : 8;            /*!< [31..24] nan                                                              */
    } GPIO_CFG_1_b;
  } ;
  
  union {
    __IOM uint32_t GPIO_CFG_2;                  /*!< (@ 0x00000008) GPIO_CFG_2                                                 */
    
    struct {
      __IOM uint32_t GPIO8_CFG  : 8;            /*!< [7..0] nan                                                                */
      __IOM uint32_t GPIO9_CFG  : 8;            /*!< [15..8] nan                                                               */
      __IOM uint32_t GPIO10_CFG : 8;            /*!< [23..16] nan                                                              */
      __IOM uint32_t GPIO11_CFG : 8;            /*!< [31..24] nan                                                              */
    } GPIO_CFG_2_b;
  } ;
  
  union {
    __IOM uint32_t GPIO_CFG_3;                  /*!< (@ 0x0000000C) GPIO_CFG_3                                                 */
    
    struct {
      __IOM uint32_t GPIO12_CFG : 8;            /*!< [7..0] nan                                                                */
      __IOM uint32_t GPIO13_CFG : 8;            /*!< [15..8] nan                                                               */
      __IOM uint32_t GPIO14_CFG : 8;            /*!< [23..16] nan                                                              */
      __IOM uint32_t GPIO15_CFG : 8;            /*!< [31..24] nan                                                              */
    } GPIO_CFG_3_b;
  } ;
  
  union {
    __IOM uint32_t GPIO_CFG_4;                  /*!< (@ 0x00000010) GPIO_CFG_4                                                 */
    
    struct {
      __IOM uint32_t GPIO16_CFG : 8;            /*!< [7..0] nan                                                                */
      __IOM uint32_t GPIO17_CFG : 8;            /*!< [15..8] nan                                                               */
      __IOM uint32_t GPIO18_CFG : 8;            /*!< [23..16] nan                                                              */
      __IOM uint32_t GPIO19_CFG : 8;            /*!< [31..24] nan                                                              */
    } GPIO_CFG_4_b;
  } ;
  
  union {
    __IOM uint32_t GPIO_CFG_5;                  /*!< (@ 0x00000014) GPIO_CFG_5                                                 */
    
    struct {
      __IOM uint32_t GPIO20_CFG : 8;            /*!< [7..0] nan                                                                */
      __IOM uint32_t GPIO21_CFG : 8;            /*!< [15..8] nan                                                               */
      __IOM uint32_t GPIO22_CFG : 8;            /*!< [23..16] nan                                                              */
      __IOM uint32_t GPIO23_CFG : 8;            /*!< [31..24] nan                                                              */
    } GPIO_CFG_5_b;
  } ;
} GPIO_ATF_Type;                                /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                         QDEC_CTRL                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief QDEC_CTRL (QDEC_CTRL)
  */

typedef struct {                                /*!< (@ 0x40020000) QDEC_CTRL Structure                                        */
  
  union {
    __IOM uint32_t QDEC_DIV;                    /*!< (@ 0x00000000) QDEC_DIV                                                   */
    
    struct {
      __IOM uint32_t SAMP_DIV   : 16;           /*!< [15..0] nan                                                               */
      __IOM uint32_t REPORT_DIV : 8;            /*!< [23..16] nan                                                              */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } QDEC_DIV_b;
  } ;
  
  union {
    __IOM uint32_t QDEC_CTRL;                   /*!< (@ 0x00000004) QDEC_CTRL                                                  */
    
    struct {
      __IOM uint32_t X_EN       : 1;            /*!< [0..0] nan                                                                */
            uint32_t            : 3;
      __IOM uint32_t X_MODE     : 2;            /*!< [5..4] nan                                                                */
            uint32_t            : 2;
      __IOM uint32_t Y_EN       : 1;            /*!< [8..8] nan                                                                */
            uint32_t            : 3;
      __IOM uint32_t Y_MODE     : 2;            /*!< [13..12] nan                                                              */
            uint32_t            : 2;
      __IOM uint32_t Z_EN       : 1;            /*!< [16..16] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t Z_MODE     : 2;            /*!< [21..20] nan                                                              */
            uint32_t            : 2;
      __IOM uint32_t DBF_MODE   : 2;            /*!< [25..24] nan                                                              */
            uint32_t            : 6;
    } QDEC_CTRL_b;
  } ;
  
  union {
    __IOM uint32_t LED_CTRL;                    /*!< (@ 0x00000008) LED_CTRL                                                   */
    
    struct {
      __IOM uint32_t LED_EN     : 1;            /*!< [0..0] nan                                                                */
      __IOM uint32_t LED_POL    : 1;            /*!< [1..1] nan                                                                */
            uint32_t            : 14;
      __IOM uint32_t LED_PRE    : 8;            /*!< [23..16] nan                                                              */
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } LED_CTRL_b;
  } ;
} QDEC_CTRL_Type;                               /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                         QDEC_INTR                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief QDEC_INTR (QDEC_INTR)
  */

typedef struct {                                /*!< (@ 0x40020020) QDEC_INTR Structure                                        */
  
  union {
    __IOM uint32_t QDEC_IE;                     /*!< (@ 0x00000000) QDEC_IE                                                    */
    
    struct {
      __IOM uint32_t X_IE       : 5;            /*!< [4..0] nan                                                                */
            uint32_t            : 3;
      __IOM uint32_t Y_IE       : 5;            /*!< [12..8] nan                                                               */
            uint32_t            : 3;
      __IOM uint32_t Z_IE       : 5;            /*!< [20..16] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } QDEC_IE_b;
  } ;
  
  union {
    __IOM uint32_t QDEC_IS;                     /*!< (@ 0x00000004) QDEC_IS                                                    */
    
    struct {
      __IOM uint32_t X_IS       : 5;            /*!< [4..0] nan                                                                */
            uint32_t            : 3;
      __IOM uint32_t Y_IS       : 5;            /*!< [12..8] nan                                                               */
            uint32_t            : 3;
      __IOM uint32_t Z_IS       : 5;            /*!< [20..16] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } QDEC_IS_b;
  } ;
  
  union {
    __IOM uint32_t QDEC_MIS;                    /*!< (@ 0x00000008) QDEC_MIS                                                   */
    
    struct {
      __IOM uint32_t X_MIS      : 5;            /*!< [4..0] nan                                                                */
            uint32_t            : 3;
      __IOM uint32_t Y_MIS      : 5;            /*!< [12..8] nan                                                               */
            uint32_t            : 3;
      __IOM uint32_t Z_MIS      : 5;            /*!< [20..16] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } QDEC_MIS_b;
  } ;
} QDEC_INTR_Type;                               /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                        QDEC_X_AXIS                                        ================ */
/* =========================================================================================================================== */


/**
  * @brief QDEC_X_AXIS (QDEC_X_AXIS)
  */

typedef struct {                                /*!< (@ 0x40020040) QDEC_X_AXIS Structure                                      */
  
  union {
    __IOM uint32_t X_SAMP;                      /*!< (@ 0x00000000) X_SAMP                                                     */
    
    struct {
      __IM  uint32_t X_SAMP     : 32;           /*!< [31..0] nan                                                               */
    } X_SAMP_b;
  } ;
  
  union {
    __IOM uint16_t X_READ;                      /*!< (@ 0x00000004) X_READ                                                     */
    
    struct {
      __OM  uint16_t X_ACC_READ : 1;            /*!< [0..0] nan                                                                */
      __OM  uint16_t X_ACC_READ_CLR : 1;        /*!< [1..1] nan                                                                */
            uint16_t            : 6;
      __OM  uint16_t X_ACCDBL_READ : 1;         /*!< [8..8] nan                                                                */
      __OM  uint16_t X_ACCDBL_READ_CLR : 1;     /*!< [9..9] nan                                                                */
            uint16_t            : 6;
    } X_READ_b;
  } ;
  __IM  uint16_t  RESERVED;
  __IM  uint32_t  RESERVED1[2];
  
  union {
    __IOM uint32_t X_ACC;                       /*!< (@ 0x00000010) X_ACC                                                      */
    
    struct {
      __IM  uint32_t X_ACC      : 32;           /*!< [31..0] nan                                                               */
    } X_ACC_b;
  } ;
  
  union {
    __IOM uint32_t X_ACC_LOAD;                  /*!< (@ 0x00000014) X_ACC_LOAD                                                 */
    
    struct {
      __IM  uint32_t X_ACC_LOAD : 32;           /*!< [31..0] nan                                                               */
    } X_ACC_LOAD_b;
  } ;
  
  union {
    __IOM uint8_t X_ACCDBL;                     /*!< (@ 0x00000018) X_ACCDBL                                                   */
    
    struct {
      __IM  uint8_t X_ACCDBL    : 8;            /*!< [7..0] nan                                                                */
    } X_ACCDBL_b;
  } ;
  __IM  uint8_t   RESERVED2;
  __IM  uint16_t  RESERVED3;
  
  union {
    __IOM uint8_t X_ACCDBL_LOAD;                /*!< (@ 0x0000001C) X_ACCDBL_LOAD                                              */
    
    struct {
      __IM  uint8_t X_ACCDBL_LOAD : 8;          /*!< [7..0] nan                                                                */
    } X_ACCDBL_LOAD_b;
  } ;
  __IM  uint8_t   RESERVED4;
  __IM  uint16_t  RESERVED5;
} QDEC_X_AXIS_Type;                             /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                        QDEC_Y_AXIS                                        ================ */
/* =========================================================================================================================== */


/**
  * @brief QDEC_Y_AXIS (QDEC_Y_AXIS)
  */

typedef struct {                                /*!< (@ 0x40020060) QDEC_Y_AXIS Structure                                      */
  
  union {
    __IOM uint32_t Y_SAMP;                      /*!< (@ 0x00000000) Y_SAMP                                                     */
    
    struct {
      __IM  uint32_t Y_SAMP     : 32;           /*!< [31..0] nan                                                               */
    } Y_SAMP_b;
  } ;
  
  union {
    __IOM uint16_t Y_READ;                      /*!< (@ 0x00000004) Y_READ                                                     */
    
    struct {
      __OM  uint16_t Y_ACC_READ : 1;            /*!< [0..0] nan                                                                */
      __OM  uint16_t Y_ACC_READ_CLR : 1;        /*!< [1..1] nan                                                                */
            uint16_t            : 6;
      __OM  uint16_t Y_ACCDBL_READ : 1;         /*!< [8..8] nan                                                                */
      __OM  uint16_t Y_ACCDBL_READ_CLR : 1;     /*!< [9..9] nan                                                                */
            uint16_t            : 6;
    } Y_READ_b;
  } ;
  __IM  uint16_t  RESERVED;
  __IM  uint32_t  RESERVED1[2];
  
  union {
    __IOM uint32_t Y_ACC;                       /*!< (@ 0x00000010) Y_ACC                                                      */
    
    struct {
      __IM  uint32_t Y_ACC      : 32;           /*!< [31..0] nan                                                               */
    } Y_ACC_b;
  } ;
  
  union {
    __IOM uint32_t Y_ACC_LOAD;                  /*!< (@ 0x00000014) Y_ACC_LOAD                                                 */
    
    struct {
      __IM  uint32_t Y_ACC_LOAD : 32;           /*!< [31..0] nan                                                               */
    } Y_ACC_LOAD_b;
  } ;
  
  union {
    __IOM uint8_t Y_ACCDBL;                     /*!< (@ 0x00000018) Y_ACCDBL                                                   */
    
    struct {
      __IM  uint8_t Y_ACCDBL    : 8;            /*!< [7..0] nan                                                                */
    } Y_ACCDBL_b;
  } ;
  __IM  uint8_t   RESERVED2;
  __IM  uint16_t  RESERVED3;
  
  union {
    __IOM uint8_t Y_ACCDBL_LOAD;                /*!< (@ 0x0000001C) Y_ACCDBL_LOAD                                              */
    
    struct {
      __IM  uint8_t Y_ACCDBL_LOAD : 8;          /*!< [7..0] nan                                                                */
    } Y_ACCDBL_LOAD_b;
  } ;
  __IM  uint8_t   RESERVED4;
  __IM  uint16_t  RESERVED5;
} QDEC_Y_AXIS_Type;                             /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                        QDEC_Z_AXIS                                        ================ */
/* =========================================================================================================================== */


/**
  * @brief QDEC_Z_AXIS (QDEC_Z_AXIS)
  */

typedef struct {                                /*!< (@ 0x40020080) QDEC_Z_AXIS Structure                                      */
  
  union {
    __IOM uint32_t Z_SAMP;                      /*!< (@ 0x00000000) Z_SAMP                                                     */
    
    struct {
      __IM  uint32_t Z_SAMP     : 32;           /*!< [31..0] nan                                                               */
    } Z_SAMP_b;
  } ;
  
  union {
    __IOM uint16_t Z_READ;                      /*!< (@ 0x00000004) Z_READ                                                     */
    
    struct {
      __OM  uint16_t Z_ACC_READ : 1;            /*!< [0..0] nan                                                                */
      __OM  uint16_t Z_ACC_READ_CLR : 1;        /*!< [1..1] nan                                                                */
            uint16_t            : 6;
      __OM  uint16_t Z_ACCDBL_READ : 1;         /*!< [8..8] nan                                                                */
      __OM  uint16_t Z_ACCDBL_READ_CLR : 1;     /*!< [9..9] nan                                                                */
            uint16_t            : 6;
    } Z_READ_b;
  } ;
  __IM  uint16_t  RESERVED;
  __IM  uint32_t  RESERVED1[2];
  
  union {
    __IOM uint32_t Z_ACC;                       /*!< (@ 0x00000010) Z_ACC                                                      */
    
    struct {
      __IM  uint32_t Z_ACC      : 32;           /*!< [31..0] nan                                                               */
    } Z_ACC_b;
  } ;
  
  union {
    __IOM uint32_t Z_ACC_LOAD;                  /*!< (@ 0x00000014) Z_ACC_LOAD                                                 */
    
    struct {
      __IM  uint32_t Z_ACC_LOAD : 32;           /*!< [31..0] nan                                                               */
    } Z_ACC_LOAD_b;
  } ;
  
  union {
    __IOM uint8_t Z_ACCDBL;                     /*!< (@ 0x00000018) Z_ACCDBL                                                   */
    
    struct {
      __IM  uint8_t Z_ACCDBL    : 8;            /*!< [7..0] nan                                                                */
    } Z_ACCDBL_b;
  } ;
  __IM  uint8_t   RESERVED2;
  __IM  uint16_t  RESERVED3;
  
  union {
    __IOM uint8_t Z_ACCDBL_LOAD;                /*!< (@ 0x0000001C) Z_ACCDBL_LOAD                                              */
    
    struct {
      __IM  uint8_t Z_ACCDBL_LOAD : 8;          /*!< [7..0] nan                                                                */
    } Z_ACCDBL_LOAD_b;
  } ;
  __IM  uint8_t   RESERVED4;
  __IM  uint16_t  RESERVED5;
} QDEC_Z_AXIS_Type;                             /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                         KEYSCAN                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief KEYSCAN (KEYSCAN)
  */

typedef struct {                                /*!< (@ 0x40021000) KEYSCAN Structure                                         */
  
  union {
    __IOM uint32_t KB_CTRL0;                    /*!< (@ 0x00000000) KB_CTRL0                                                   */
    
    struct {
      __IOM uint32_t SCAN_EN    : 1;            /*!< [0..0] nan                                                                */
            uint32_t            : 7;
      __IOM uint32_t MUX_SEL    : 2;            /*!< [9..8] nan                                                                */
            uint32_t            : 2;
      __IOM uint32_t SCAN_SEL   : 1;            /*!< [12..12] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t KB_HIGH_EN : 5;            /*!< [20..16] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t DRV_DLY    : 4;            /*!< [27..24] nan                                                              */
      __IOM uint32_t PULL_DLY   : 4;            /*!< [31..28] nan                                                              */
    } KB_CTRL0_b;
  } ;
  
  union {
    __IOM uint32_t KB_CTRL1;                    /*!< (@ 0x00000004) KB_CTRL1                                                   */
    
    struct {
      __IOM uint32_t SCAN_AREA  : 3;            /*!< [2..0] nan                                                                */
            uint32_t            : 1;
      __IOM uint32_t COMB_AREA  : 1;            /*!< [4..4] nan                                                                */
      __IOM uint32_t COMB_MODE  : 1;            /*!< [5..5] nan                                                                */
      __IOM uint32_t COMB_NUM   : 2;            /*!< [7..6] nan                                                                */
      __IOM uint32_t A3_ARCH    : 1;            /*!< [8..8] nan                                                                */
      __IOM uint32_t A3_POLAR   : 1;            /*!< [9..9] nan                                                                */
            uint32_t            : 2;
      __IOM uint32_t A3_SIZE    : 4;            /*!< [15..12] nan                                                              */
      __IOM uint32_t FILT_NUM   : 4;            /*!< [19..16] nan                                                              */
      __IOM uint32_t IDLE_PD    : 1;            /*!< [20..20] nan                                                              */
      __IOM uint32_t IDLE_PU    : 1;            /*!< [21..21] nan                                                              */
            uint32_t            : 2;
      __IOM uint32_t SCAN_DLY   : 8;            /*!< [31..24] nan                                                              */
    } KB_CTRL1_b;
  } ;

    union {
    __IOM uint32_t KEY_MASK;                     /*!< (@ 0x00000008) KEY_MASK                                                    */
    
    struct {
      __IOM uint32_t KEY_MASK   : 11;            /*!< [10..0] nan                                                                */
      __IOM uint32_t reserve    : 21;            /*!< [31..11] 0                                                                */
    } KEY_MASK_b;
  } ;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t KB_INTR;                     /*!< (@ 0x00000010) KB_INTR                                                    */
    
    struct {
      __IOM uint32_t KB_IE      : 2;            /*!< [1..0] nan                                                                */
            uint32_t            : 6;
      __IOM uint32_t KB_IS      : 2;            /*!< [9..8] nan                                                                */
            uint32_t            : 6;
      __IOM uint32_t KB_MIS     : 2;            /*!< [17..16] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t reserve    : 8;            /*!< [31..24] 0                                                                */
    } KB_INTR_b;
  } ;
  __IM  uint32_t  RESERVED1[3];
  
  union {
    __IOM uint8_t KB_INFO0;                     /*!< (@ 0x00000020) KB_INFO0                                                   */
    
    struct {
      __IM  uint8_t PRESS_NUM   : 4;            /*!< [3..0] nan                                                                */
            uint8_t             : 4;
    } KB_INFO0_b;
  } ;
  __IM  uint8_t   RESERVED2;
  __IM  uint16_t  RESERVED3;
  
  union {
    __IOM uint32_t KB_INFO1;                    /*!< (@ 0x00000024) KB_INFO1                                                   */
    
    struct {
      __IM  uint32_t PRESS0     : 7;            /*!< [6..0] nan                                                                */
            uint32_t            : 1;
      __IM  uint32_t PRESS1     : 7;            /*!< [14..8] nan                                                               */
            uint32_t            : 1;
      __IM  uint32_t PRESS2     : 7;            /*!< [22..16] nan                                                              */
            uint32_t            : 1;
      __IM  uint32_t PRESS3     : 7;            /*!< [30..24] nan                                                              */
            uint32_t            : 1;
    } KB_INFO1_b;
  } ;
  
  union {
    __IOM uint16_t KB_INFO2;                    /*!< (@ 0x00000028) KB_INFO2                                                   */
    
    struct {
      __IM  uint16_t VIO_INFO   : 11;           /*!< [10..0] nan                                                               */
            uint16_t            : 5;
    } KB_INFO2_b;
  } ;
  __IM  uint16_t  RESERVED4;
  __IM  uint32_t  RESERVED5[5];
  
  union {
    __IOM uint32_t KB_STS0;                     /*!< (@ 0x00000040) KB_STS0                                                    */
    
    struct {
      __IM  uint32_t KSTS0      : 32;           /*!< [31..0] nan                                                               */
    } KB_STS0_b;
  } ;
  
  union {
    __IOM uint32_t KB_STS1;                     /*!< (@ 0x00000044) KB_STS1                                                    */
    
    struct {
      __IM  uint32_t KSTS1      : 32;           /*!< [31..0] nan                                                               */
    } KB_STS1_b;
  } ;
  
  union {
    __IOM uint32_t KB_STS2;                     /*!< (@ 0x00000048) KB_STS2                                                    */
    
    struct {
      __IM  uint32_t KSTS2      : 32;           /*!< [31..0] nan                                                               */
    } KB_STS2_b;
  } ;
} KEYSCAN_Type;                                /*!< Size = 76 (0x4c)                                                          */



/* =========================================================================================================================== */
/* ================                                        LEDC_CTRL                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief LEDC_CTRL (LEDC_CTRL)
  */

typedef struct {                                /*!< (@ 0x40022000) LEDC_CTRL Structure                                       */
  
  union {
    __IOM uint16_t DMA_CTRL;                        /*!< (@ 0x00000000) CTRL0                                                      */
    
    struct {
      __IOM uint16_t DMA_EN      : 1;            /*!< [0..0] nan                                                                */
      __IOM uint16_t             : 7;            /*!< [7..1] nan                                                                */
      __IOM uint16_t LEVEL_INIT  : 1;            /*!< [8..8] nan                                                                */
      __IOM uint16_t LEVEL_INV   : 1;            /*!< [9..9] nan                                                                */
      __IOM uint16_t LSB_FIRST   : 1;            /*!< [4..4] nan                                                                */
            uint16_t             : 5;
    }DMA_CTRL_b;
  } ;
  __IM  uint16_t  RESERVED;
  __IM  uint32_t  RESERVED1[7];

  
  union {
    __IOM uint16_t REPEAT_NUM1;                 /*!< (@ 0x00000020) REPEAT_NUM1                                                */
    
    struct {
      __IOM uint16_t REPEAT_NUM1 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } REPEAT_NUM1_b;
  } ;

  union {
    __IOM uint16_t REPEAT_NUM2;                 /*!< (@ 0x00000022) REPEAT_NUM2                                                */
    
    struct {
      __IOM uint16_t REPEAT_NUM2 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } REPEAT_NUM2_b;
  } ;

  union {
    __IOM uint16_t REPEAT_NUM3;                 /*!< (@ 0x00000024) REPEAT_NUM3                                                */
    
    struct {
      __IOM uint16_t REPEAT_NUM3 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } REPEAT_NUM3_b;
  } ;

  union {
    __IOM uint16_t REPEAT_NUM4;                 /*!< (@ 0x00000026) REPEAT_NUM4                                                */
    
    struct {
      __IOM uint16_t REPEAT_NUM4 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } REPEAT_NUM4_b;
  } ;

  union {
    __IOM uint16_t REPEAT_NUM5;                 /*!< (@ 0x00000028) REPEAT_NUM5                                                */
    
    struct {
      __IOM uint16_t REPEAT_NUM5 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } REPEAT_NUM5_b;
  } ;
  union {
    __IOM uint16_t REPEAT_NUM6;                 /*!< (@ 0x0000002A) REPEAT_NUM1                                                */
    
    struct {
      __IOM uint16_t REPEAT_NUM6 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } REPEAT_NUM6_b;
  } ;
 __IM  uint32_t  RESERVED2;



union {
    __IOM uint16_t CHANGE_NUM1;                 /*!< (@ 0x00000030) CHANGE_NUM1                                                */
    
    struct {
      __IOM uint16_t CHANGE_NUM1 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } CHANGE_NUM1_b;
  } ;

  
  union {
    __IOM uint16_t CHANGE_NUM2;                 /*!< (@ 0x00000032) CHANGE_NUM2                                                */
    
    struct {
      __IOM uint16_t CHANGE_NUM2 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } CHANGE_NUM2_b;
  } ;

  
  union {
    __IOM uint16_t CHANGE_NUM3;                 /*!< (@ 0x00000034) CHANGE_NUM3                                                */
    
    struct {
      __IOM uint16_t CHANGE_NUM3 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } CHANGE_NUM3_b;
  } ;

  
  union {
    __IOM uint16_t CHANGE_NUM4;                 /*!< (@ 0x00000036) CHANGE_NUM4                                                */
    
    struct {
      __IOM uint16_t CHANGE_NUM4 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } CHANGE_NUM4_b;
  } ;

  
  union {
    __IOM uint16_t CHANGE_NUM5;                 /*!< (@ 0x00000038) CHANGE_NUM5                                                */
    
    struct {
      __IOM uint16_t CHANGE_NUM5 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } CHANGE_NUM5_b;
  } ;
union {
    __IOM uint16_t CHANGE_NUM6;                 /*!< (@ 0x0000003A) CHANGE_NUM6                                                */
    
    struct {
      __IOM uint16_t CHANGE_NUM6 : 12;          /*!< [11..0] nan                                                               */
            uint16_t            : 4;
    } CHANGE_NUM6_b;
  } ;
 __IM  uint32_t  RESERVED3;

  union {
    __IOM uint32_t BIT0_MODU;                   /*!< (@ 0x00000000) BIT0_MODU                                                  */
    
    struct {
      __IOM uint32_t B0_P0_LEN  : 12;           /*!< [11..0] nan                                                               */
            uint32_t            : 3;
      __IOM uint32_t B0_P0_POL  : 1;            /*!< [15..15] nan                                                              */
      __IOM uint32_t B0_P1_LEN  : 12;           /*!< [27..16] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t B0_P1_POL  : 1;            /*!< [31..31] nan                                                              */
    } BIT0_MODU_b;
  } ;
  
  union {
    __IOM uint32_t BIT1_MODU;                   /*!< (@ 0x00000004) BIT1_MODU                                                  */
    
    struct {
      __IOM uint32_t B1_P0_LEN  : 12;           /*!< [11..0] nan                                                               */
            uint32_t            : 3;
      __IOM uint32_t B1_P0_POL  : 1;            /*!< [15..15] nan                                                              */
      __IOM uint32_t B1_P1_LEN  : 12;           /*!< [27..16] nan                                                              */
            uint32_t            : 3;
      __IOM uint32_t B1_P1_POL  : 1;            /*!< [31..31] nan                                                              */
    } BIT1_MODU_b;
  } ;

}LEDC_CTRL_Type;                              /*!< Size = 22 (0x44)                                                          */



/* =========================================================================================================================== */
/* ================                                         LEDC_CHANNEL_CTRL                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief LEDC_CHANNEL_CTRL
  */

typedef struct {                                /*!< (@ 0x400220A0) LEDC_IRQ Structure                                        */
  
  union {
    __IOM uint16_t CTRL1;                        /*!< (@ 0x00000000) CTRL1                                                      */
    
    struct {
      __OM  uint16_t DMA_START   : 1;            /*!< [0..0] nan                                                                */
      __OM  uint16_t DMA_STOP    : 1;            /*!< [1..1] nan                                                                */
      __IM  uint16_t DMA_STATE   : 1;            /*!< [2..2] nan                                                                */
            uint16_t             : 1;
      __IM  uint16_t DMA_RESET   : 1;            /*!< [4..4] nan                                                                */
            uint16_t             : 2;
      __OM  uint16_t DMA_LOOP_MODE   : 1;        /*!< [8..8] nan                                                                */
            uint16_t             : 7;
    } CTRL1_b;
  } ;
  uint16_t RESERVED;
  union {
    __IOM uint8_t DMA_IE;                       /*!< (@ 0x00000004) DMA_IE                                                     */
    
    struct {
      __IOM uint8_t DMA_IE      : 3;            /*!< [2..0] nan                                                                */
            uint8_t             : 5;
    } DMA_IE_b;
  } ;
  uint8_t RESERVED1;
  union {
    __IOM uint8_t DMA_IS;                       /*!< (@ 0x00000006) DMA_IS                                                     */
    
    struct {
      __IOM uint8_t DMA_IS      : 3;            /*!< [2..0] nan                                                                */
            uint8_t             : 5;
    } DMA_IS_b;
  } ;

  union {
    __IOM uint8_t DMA_MIS;                      /*!< (@ 0x00000007) DMA_MIS                                                    */
    
    struct {
      __IOM uint8_t DMA_MIS     : 3;            /*!< [2..0] nan                                                                */
            uint8_t             : 5;
    } DMA_MIS_b;
  } ;

  union {
    __IOM uint16_t TBL_SADDR;                   /*!< (@ 0x0000008) TBL_SADDR                                                  */
    
    struct {
            uint16_t            : 2;
      __IOM uint16_t TBL_SADDR  : 14;           /*!< [15..2] nan                                                               */
    } TBL_SADDR_b;
  } ;  
  union {
    __IOM uint16_t TBL_EADDR;                   /*!< (@ 0x0000000A) TBL_EADDR                                                  */
    
    struct {
            uint16_t            : 2;
      __IOM uint16_t TBL_EADDR  : 14;           /*!< [15..2] nan                                                               */
    } TBL_EADDR_b;
  } ;

  union {
    __IOM uint16_t DESC_ADDR;                   /*!< (@ 0x0000000C) DESC_ADDR                                                  */
    
    struct {
      uint16_t                  : 2;
      __IM  uint16_t DESC_ADDR  : 14;           /*!< [15..2] nan                                                               */
    } DESC_ADDR_b;
  } ;

union {
    __IOM uint16_t TBL_ADDR;                    /*!< (@ 0x0000000E) TBL_ADDR                                                   */
    
    struct {
            uint16_t            : 2;
      __IM  uint16_t TBL_ADDR   : 14;           /*!< [15..2] nan                                                               */
    } TBL_ADDR_b;
  } ;
  

  union {
    __IOM uint16_t STATUS;                      /*!< (@ 0x00000010) STATUS                                                     */
    
    struct {
      __IM  uint16_t STATUS     : 16;           /*!< [31..0] nan                                                               */
    } STATUS_b;
  } ;

  union {
    __IOM uint16_t DATA_ADDR;                   /*!< (@ 0x00000012) DATA_ADDR                                                  */
    
    struct {
      __IM  uint16_t DATA_ADDR  : 16;           /*!< [31..0] nan                                                               */
    } DATA_ADDR_b;
  } ;
  
} LEDC_CHANNEL_CTRL_Type;                               /*!< Size = 20 (0x14)                                                            */



/* =========================================================================================================================== */
/* ================                                         GPADC_ANA                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief GPADC_ANA (GPADC_ANA)
  */

  typedef struct {                                /*!< (@ 0x40040000) GPADC_ANA Structure                                        */
  
    union {
      __IOM uint8_t GPADC_EN;                     /*!< (@ 0x00000000) GPADC_EN                                                   */
      
      struct {
        __IOM uint8_t DA_GPADC_PGA_EN : 1;        /*!< [0..0] nan                                                                */
        __IOM uint8_t DA_GPADC_EN : 1;            /*!< [1..1] nan                                                                */
              uint8_t             : 6;
      } GPADC_EN_b;
    } ;
    __IM  uint8_t   RESERVED;
    __IM  uint16_t  RESERVED1;
    
    union {
      __IOM uint16_t GPADC_CTRL;                  /*!< (@ 0x00000004) GPADC_CTRL                                                 */
      
      struct {
        __IOM uint16_t RG_GPADC_VIP_SEL : 4;      /*!< [3..0] nan                                                                */
        __IOM uint16_t RG_GPADC_VIN_SEL : 4;      /*!< [7..4] nan                                                                */
        __IOM uint16_t RG_GPADC_PGA_GC : 4;       /*!< [11..8] nan                                                               */
        __IOM uint16_t RG_GPADC_DIFF_EN : 1;      /*!< [12..12] nan                                                              */
        __IOM uint16_t RG_GPADC_ATT_SEL : 2;      /*!< [14..13] nan                                                              */
              uint16_t            : 1;
      } GPADC_CTRL_b;
    } ;
    __IM  uint16_t  RESERVED2;
    
    union {
      __IOM uint16_t GPADC_CFG;                   /*!< (@ 0x00000008) GPADC_CFG                                                  */
      
      struct {
        __IOM uint16_t RG_GPADC_PGA_VCM_SEL : 3;  /*!< [2..0] nan                                                                */
        __IOM uint16_t RG_GPADC_PGA_RS : 4;       /*!< [6..3] nan                                                                */
        __IOM uint16_t RG_GPADC_PGA_CM3_IBIAS : 2;/*!< [8..7] nan                                                                */
        __IOM uint16_t RG_GPADC_PGA_CM1_IBIAS : 2;/*!< [10..9] nan                                                               */
              uint16_t            : 5;
      } GPADC_CFG_b;
    } ;
  } GPADC_ANA_Type;                               /*!< Size = 10 (0xa)                                                           */
  
  
  
  /* =========================================================================================================================== */
  /* ================                                         GPADC_DIG                                         ================ */
  /* =========================================================================================================================== */
  
  
  /**
    * @brief GPADC_DIG (GPADC_DIG)
    */
  
  typedef struct {                                /*!< (@ 0x40040060) GPADC_DIG Structure                                        */
    
    union {
      __IOM uint32_t GPADC_ACTION;                /*!< (@ 0x00000000) GPADC_ACTION                                               */
      
      struct {
        __IOM uint32_t GPADC_DMA_EN : 1;          /*!< [0..0] nan                                                                */
        __IOM uint32_t GPADC_SAMP_EN : 1;         /*!< [1..1] nan                                                                */
        __IOM uint32_t GPADC_CONT_MODE : 1;       /*!< [2..2] nan                                                                */
        __IOM uint32_t GPADC_TIMER_MODE : 1;      /*!< [3..3] nan                                                                */
        __IOM uint32_t GPADC_TIMER_SEL : 3;       /*!< [6..4] nan                                                                */
              uint32_t            : 5;
        __IOM uint32_t GPADC_AVG_WIN : 4;         /*!< [15..12] nan                                                              */
        __IM  uint32_t GPADC_WP   : 11;           /*!< [26..16] nan                                                              */
              uint32_t            : 4;
        __OM  uint32_t GPADC_TRIG : 1;            /*!< [31..31] nan                                                              */
      } GPADC_ACTION_b;
    } ;
    
    union {
      __IOM uint16_t GPADC_CFG;                   /*!< (@ 0x00000004) GPADC_CFG                                                  */
      
      struct {
        __IOM uint16_t GPADC_STORE_MODE : 1;      /*!< [0..0] nan                                                                */
        __IOM uint16_t GPADC_FORMAT : 1;          /*!< [1..1] nan                                                                */
        __IOM uint16_t GPADC_SIGNEXT : 1;         /*!< [2..2] nan                                                                */
              uint16_t            : 1;
        __IOM uint16_t GPADC_START_BK : 2;        /*!< [5..4] nan                                                                */
        __IOM uint16_t GPADC_BK_NUM : 2;          /*!< [7..6] nan                                                                */
        __IOM uint16_t GPADC_INT_INTERVAL : 8;    /*!< [15..8] nan                                                               */
      } GPADC_CFG_b;
    } ;
    __IM  uint16_t  RESERVED;
    
    union {
      __IOM uint32_t GPADC_INT_CTRL;              /*!< (@ 0x00000008) GPADC_INT_CTRL                                             */
      __IOM uint8_t GPADC_INT_CTRL_BYTE[4];       /*!< (@ 0x00000008) GPADC_INT_CTRL                                             */   
      
      struct {
        __IOM uint32_t GPADC_IS   : 2;            /*!< [1..0] nan                                                                */
              uint32_t            : 6;
        __IOM uint32_t GPADC_MIS  : 2;            /*!< [9..8] nan                                                                */
              uint32_t            : 6;
        __IOM uint32_t GPADC_IE   : 2;            /*!< [17..16] nan                                                              */
              uint32_t            : 6;
        __IOM uint32_t reserve    : 8;            /*!< [31..24] 0                                                                */
      } GPADC_INT_CTRL_b;
    } ;
    
    union {
      __IOM uint32_t GPADC_SAMP;                  /*!< (@ 0x0000000C) GPADC_SAMP                                                 */
      
      struct {
        __IM  uint32_t GPADC_SAMP : 32;           /*!< [31..0] nan                                                               */
      } GPADC_SAMP_b;
    } ;
    
    union {
      __IOM uint32_t GPADC_CLK_CTRL;              /*!< (@ 0x00000010) GPADC_CLK_CTRL                                             */
      
      struct {
        __IOM uint32_t GPADC_CLK_SEL : 1;         /*!< [0..0] nan                                                                */
        __IOM uint32_t GPADC_CLK_AUTOCG : 1;      /*!< [1..1] nan                                                                */
    
        __IOM uint32_t GPADC_CLK_EN : 1;          /*!< [2..2] nan                                                                */
        __IOM uint32_t GPADC_CLK_SAMP_INV : 1;    /*!< [3..3] nan                                                                */
        __IOM uint32_t GPADC_CLK_OUT_INV : 1;     /*!< [4..4] nan                                                                */
        __IOM uint32_t GPADC_CLK_OUT_POL : 1;     /*!< [5..5] nan                                                                */
    
              uint32_t            : 2;
        __IOM uint32_t GPADC_CLK_DIV : 8;         /*!< [15..8] nan                                                               */
      
        __IOM uint32_t GPADC_CLK_PRE : 4;         /*!< [19..16] nan                                                              */
              uint32_t            : 4;
        __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
      } GPADC_CLK_CTRL_b;
    } ;
  } GPADC_DIG_Type;                               /*!< Size = 20 (0x14)                                                          */



/* =========================================================================================================================== */
/* ================                                         AON_CTRL                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief AON_CTRL (AON_CTRL)
  */

  typedef struct {                                /*!< (@ 0x40080000) AON_CTRL Structure                                         */
  
    union {
      __IOM uint8_t AON_CTRL0;                    /*!< (@ 0x00000000) AON_CTRL0                                                  */
      
      struct {
        __IOM uint8_t HOLD_MODE   : 1;            /*!< [0..0] nan                                                                */
        __IOM uint8_t RET_MODE    : 1;            /*!< [1..1] nan                                                                */
        __IOM uint8_t RET_EN      : 1;            /*!< [2..2] nan                                                                */
        __IOM uint8_t ISO_EN      : 1;            /*!< [3..3] nan                                                                */
        __IOM uint8_t RET_OPEN    : 4;            /*!< [7..4] nan                                                                */
      } AON_CTRL0_b;
    } ;
    __IM  uint8_t   RESERVED;
    __IM  uint16_t  RESERVED1;
    
    union {
      __IOM uint32_t SLEEP_TIME;                  /*!< (@ 0x00000004) SLEEP_TIME                                                 */
      
      struct {
        __IOM uint32_t SLEEP_TIME : 32;           /*!< [31..0] nan                                                               */
      } SLEEP_TIME_b;
    } ;
    __IM  uint32_t  RESERVED2[2];
    
    union {
      __IOM uint32_t WAKEUP_CTRL0;                /*!< (@ 0x00000010) WAKEUP_CTRL0                                               */
      
      struct {
        __IOM uint32_t GPIO_WAKEUP_EN : 24;       /*!< [23..0] nan                                                               */
        __IOM uint32_t reserve    : 8;            /*!< [31..24] 0                                                                */
      } WAKEUP_CTRL0_b;
    } ;
    
    union {
      __IOM uint32_t WAKEUP_CTRL1;                /*!< (@ 0x00000014) WAKEUP_CTRL1                                               */
      
      struct {
        __IOM uint32_t GPION_WAKEUP_EN : 24;      /*!< [23..0] nan                                                               */
        __IOM uint32_t reserve    : 8;            /*!< [31..24] 0                                                                */
      } WAKEUP_CTRL1_b;
    } ;
    
    union {
      __IOM uint32_t WAKEUP_CLEAR;                /*!< (@ 0x00000018) WAKEUP_CLEAR                                               */
      
      struct {
        __IOM uint32_t WAKEUP_CLEAR : 24;         /*!< [23..0] nan                                                               */
        __IOM uint32_t WAKEUP_AUTOCLEAR : 1;      /*!< [24..24] nan                                                              */
              uint32_t            : 7;
      } WAKEUP_CLEAR_b;
    } ;
    
    union {
      __IOM uint32_t WAKEUP_RECORD;               /*!< (@ 0x0000001C) WAKEUP_RECORD                                              */
      
      struct {
        __IM  uint32_t WAKEUP_RECORD : 24;        /*!< [23..0] nan                                                               */
        __IM  uint32_t WAKEUP_RECORD_KB : 1;      /*!< [24..24] nan                                                              */
        __IM  uint32_t WAKEUP_RECORD_IR : 1;      /*!< [25..25] nan                                                              */
        __IM  uint32_t WAKEUP_RECORD_VCORE : 1;   /*!< [26..26] nan                                                              */
        __IM  uint32_t WAKEUP_RECORD_VBAT : 1;    /*!< [27..27] nan                                                              */
              uint32_t            : 4;
      } WAKEUP_RECORD_b;
    } ;
	union {
		__IOM uint32_t SOFT_RECORD0;                /*!< (@ 0x00000020) SOFT_RECORD0                                               */

		struct {
		  __IOM uint32_t SOFT_RECORD0 : 32;         /*!< [31..0] nan                                                               */
		} SOFT_RECORD0_b;
	} ;

	union {
		__IOM uint32_t SOFT_RECORD1;                /*!< (@ 0x00000024) SOFT_RECORD1                                               */

		struct {
		  __IOM uint32_t SOFT_RECORD1 : 32;         /*!< [31..0] nan                                                               */
		} SOFT_RECORD1_b;
		} ;

	union {
		__IOM uint32_t SOFT_RECORD2;                /*!< (@ 0x00000028) SOFT_RECORD2                                               */

		struct {
		  __IOM uint32_t SOFT_RECORD2 : 32;         /*!< [31..0] nan                                                               */
		} SOFT_RECORD2_b;
	} ;

	union {
		__IOM uint32_t SOFT_RECORD3;                /*!< (@ 0x0000002C) SOFT_RECORD3                                               */

		struct {
		  __IOM uint32_t SOFT_RECORD3 : 32;         /*!< [31..0] nan                                                               */
		} SOFT_RECORD3_b;
	} ;

	union {
		__IOM uint32_t CPU_RST_ADDR;                /*!< (@ 0x00000030) CPU_RST_ADDR                                               */

		struct {
		  __IOM uint32_t CPU_RST_ADDR : 32;         /*!< [31..0] nan                                                               */
		} CPU_RST_ADDR_b;
	} ;
  
    union {
      __IOM uint32_t QSPI_CTRL;                   /*!< (@ 0x00000034) QSPI_CTRL                                                  */
      
      struct {
        __IOM uint32_t REG_CMD_DUMMY : 5;         /*!< [4..0] nan                                                                */
              uint32_t            : 3;
        __IOM uint32_t REG_ADDR_DUMMY : 6;        /*!< [13..8] nan                                                               */
              uint32_t            : 2;
        __IOM uint32_t REG_ADDR_MODE : 1;         /*!< [16..16] nan                                                              */
              uint32_t            : 7;
        __IOM uint32_t reserve    : 8;            /*!< [31..24] 0                                                                */
      } QSPI_CTRL_b;
    } ;
    
    union {
      __IOM uint16_t QSPI_CMD_CFG;                /*!< (@ 0x00000038) QSPI_CMD_CFG                                               */
      
      struct {
        __IOM uint16_t REG_CMD_TYPE_RD : 4;       /*!< [3..0] nan                                                                */
              uint16_t            : 4;
        __IOM uint16_t REG_CMD_CODE_RD : 8;       /*!< [15..8] nan                                                               */
      } QSPI_CMD_CFG_b;
    } ;
    __IM  uint16_t  RESERVED4;
    __IM  uint32_t  RESERVED5;
    
    union {
      __IOM uint8_t SET_SCAN_MODE;                /*!< (@ 0x00000040) SET_SCAN_MODE                                              */
      
      struct {
        __IOM uint8_t SET_SCAN_MODE : 1;          /*!< [0..0] nan                                                                */
              uint8_t             : 7;
      } SET_SCAN_MODE_b;
    } ;
    __IM  uint8_t   RESERVED6;
    __IM  uint16_t  RESERVED7;
    __IM  uint32_t  RESERVED8;
    
    union {
      __IOM uint8_t GOSLEEP;                      /*!< (@ 0x00000048) GOSLEEP                                                    */
      
      struct {
        __IOM uint8_t GOSLEEP     : 1;            /*!< [0..0] nan                                                                */
              uint8_t             : 7;
      } GOSLEEP_b;
    } ;
    __IM  uint8_t   RESERVED9;
    __IM  uint16_t  RESERVED10;
    
    union {
      __IOM uint8_t GPIO_HOLD;                    /*!< (@ 0x0000004C) GPIO_HOLD                                                  */
      
      struct {
        __IOM uint8_t GPIO_HOLD   : 1;            /*!< [0..0] nan                                                                */
              uint8_t             : 7;
      } GPIO_HOLD_b;
    } ;
    __IM  uint8_t   RESERVED11;
    __IM  uint16_t  RESERVED12;
    
    union {
      __IOM uint8_t RTC_CTRL;                     /*!< (@ 0x00000050) RTC_CTRL                                                   */
      
      struct {
        __IOM uint8_t RTC_EN      : 1;            /*!< [0..0] nan                                                                */
        __IOM uint8_t RTC_LD      : 1;            /*!< [1..1] nan                                                                */
        __IOM uint8_t RTC_ADD     : 1;            /*!< [2..2] nan                                                                */
        __IOM uint8_t RTC_SUB     : 1;            /*!< [3..3] nan                                                                */
              uint8_t             : 4;
      } RTC_CTRL_b;
    } ;
    __IM  uint8_t   RESERVED13;
    __IM  uint16_t  RESERVED14;
    
    union {
      __IOM uint32_t RTC_VAL;                     /*!< (@ 0x00000054) RTC_VAL                                                    */
      
      struct {
        __IOM uint32_t RTC_VAL    : 32;           /*!< [31..0] nan                                                               */
      } RTC_VAL_b;
    } ;
    __IM  uint32_t  RESERVED15[3];
    
    union {
      __IOM uint32_t KB_WKUP0;                    /*!< (@ 0x00000064) KB_WKUP0                                                   */
      
      struct {
        __IOM uint32_t KB_SCAN_AREA : 3;          /*!< [2..0] nan                                                                */
              uint32_t            : 1;
        __IOM uint32_t KB_IDLE_PD : 1;            /*!< [4..4] nan                                                                */
        __IOM uint32_t KB_IDLE_PU : 1;            /*!< [5..5] nan                                                                */
        __IOM uint32_t KB_A3_ARCH : 1;            /*!< [6..6] nan                                                                */
        __IOM uint32_t KB_A3_POLAR : 1;           /*!< [7..7] nan                                                                */
        __IOM uint32_t KB_A3_SIZE : 4;            /*!< [11..8] nan                                                               */
        __IOM uint32_t KB_FILT_NUM : 4;           /*!< [15..12] nan                                                              */
        __IOM uint32_t KB_OUT_DLY : 8;            /*!< [23..16] nan                                                              */
        __IOM uint32_t KB_SCAN_DLY : 8;           /*!< [31..24] nan                                                              */
      } KB_WKUP0_b;
    } ;
    
    union {
      __IOM uint32_t KB_WKUP1;                    /*!< (@ 0x00000068) KB_WKUP1                                                   */
      
      struct {
        __IOM uint32_t KB_SCAN_EN : 1;            /*!< [0..0] nan                                                                */
        __IOM uint32_t KB_SCAN_SEL : 1;           /*!< [1..1] nan                                                                */
              uint32_t            : 5;
        __IM  uint32_t KB_WKUP_STS : 1;           /*!< [7..7] nan                                                                */
        __IOM uint32_t KB_MUX_SEL : 2;            /*!< [9..8] nan                                                                */
        __IOM uint32_t KB_DS      : 2;            /*!< [11..10] nan                                                              */
        __IOM uint32_t KB_ODE     : 1;            /*!< [12..12] nan                                                              */
        __IOM uint32_t KB_IE      : 1;            /*!< [13..13] nan                                                              */
              uint32_t            : 2;
        __IOM uint32_t KB_PE      : 11;           /*!< [26..16] nan                                                              */
              uint32_t            : 5;
      } KB_WKUP1_b;
    } ;
    __IM  uint32_t  RESERVED16;
    
    union {
      __IOM uint32_t IR_WKUP0;                    /*!< (@ 0x00000070) IR_WKUP0                                                   */
      
      struct {
        __IOM uint32_t IR_ON_TIME : 16;           /*!< [15..0] nan                                                               */
        __IOM uint32_t IR_OFF_TIME : 16;          /*!< [31..16] nan                                                              */
      } IR_WKUP0_b;
    } ;
    
    union {
      __IOM uint32_t IR_WKUP1;                    /*!< (@ 0x00000074) IR_WKUP1                                                   */
      
      struct {
        __IOM uint32_t IR_WKUP_EN : 1;            /*!< [0..0] nan                                                                */
              uint32_t            : 1;
        __IOM uint32_t IR_INV     : 1;            /*!< [2..2] nan                                                                */
              uint32_t            : 1;
        __IOM uint32_t IR_CLK     : 2;            /*!< [5..4] nan                                                                */
        __IM  uint32_t IR_RX_STS  : 1;            /*!< [6..6] nan                                                                */
        __IM  uint32_t IR_WKUP_STS : 1;           /*!< [7..7] nan                                                                */
        __IOM uint32_t IR_SETL    : 4;            /*!< [11..8] nan                                                               */
              uint32_t            : 4;
        __IOM uint32_t IR_DET_WIN : 8;            /*!< [23..16] nan                                                              */
        __IOM uint32_t IR_DET_THRES : 8;          /*!< [31..24] nan                                                              */
      } IR_WKUP1_b;
    } ;
    
    union {
      __IOM uint16_t IR_RX_CTRL;                  /*!< (@ 0x00000078) IR_RX_CTRL                                                 */
      
      struct {
        __IOM uint16_t IR_RX_EN   : 1;            /*!< [0..0] nan                                                                */
        __IOM uint16_t IR_RX_VIN_SEL : 4;         /*!< [4..1] nan                                                                */
        __IOM uint16_t IR_GAIN_CTRL : 3;          /*!< [7..5] nan                                                                */
        __IOM uint16_t IR_RIN_CTRL : 4;           /*!< [11..8] nan                                                               */
        __IOM uint16_t IR_ROUT_CTRL : 4;          /*!< [15..12] nan                                                              */
      } IR_RX_CTRL_b;
    } ;
    __IM  uint16_t  RESERVED17;
    
    union {
      __IOM uint8_t PWR_OV33_WKUP;                /*!< (@ 0x0000007C) PWR_OV33_WKUP                                              */
      
      struct {
        __IOM uint8_t VCORE_OV33_WKUP_EN : 1;     /*!< [0..0] nan                                                                */
        __IOM uint8_t VBAT_OV33_WKUP_EN : 1;      /*!< [1..1] nan                                                                */
              uint8_t             : 6;
      } PWR_OV33_WKUP_b;
    } ;
    __IM  uint8_t   RESERVED18;
    __IM  uint16_t  RESERVED19;
    
    union {
      __IOM uint16_t CPU_RST_RCD;                 /*!< (@ 0x00000080) CPU_RST_RCD                                                */
      
      struct {
        __IM  uint16_t CPU_RST_RCD : 10;          /*!< [9..0] nan                                                                */
              uint16_t            : 6;
      } CPU_RST_RCD_b;
    } ;
    __IM  uint16_t  RESERVED20;
    
    union {
      __IOM uint16_t CPU_RST_CLR;                 /*!< (@ 0x00000084) CPU_RST_CLR                                                */
      
      struct {
        __OM  uint16_t CPU_RST_CLR : 10;          /*!< [9..0] nan                                                                */
              uint16_t            : 6;
      } CPU_RST_CLR_b;
    } ;
    __IM  uint16_t  RESERVED21;
    
    union {
      __IOM uint8_t RST_IGNORE_CTRL;              /*!< (@ 0x00000088) RST_IGNORE_CTRL                                            */
      
      struct {
        __IOM uint8_t RST_IGNORE_CTRL : 6;        /*!< [5..0] nan                                                                */
              uint8_t             : 2;
      } RST_IGNORE_CTRL_b;
    } ;
    __IM  uint8_t   RESERVED22;
    __IM  uint16_t  RESERVED23;
    __IM  uint32_t  RESERVED24;
    
    union {
      __IOM uint32_t SOFT_RECORD4;                /*!< (@ 0x00000090) SOFT_RECORD4                                               */
      
      struct {
        __IOM uint32_t SOFT_RECORD4 : 32;         /*!< [31..0] nan                                                               */
      } SOFT_RECORD4_b;
    } ;
    
    union {
      __IOM uint32_t SOFT_RECORD5;                /*!< (@ 0x00000094) SOFT_RECORD6                                               */
      
      struct {
        __IOM uint32_t SOFT_RECORD5 : 32;         /*!< [31..0] nan                                                               */
      } SOFT_RECORD5_b;
    } ;
    __IM  uint32_t  RESERVED25[2];
    
    union {
      __IOM uint8_t DA_FORCE_CTRL;                /*!< (@ 0x000000A0) DA_FORCE_CTRL                                              */
      
      struct {
        __IOM uint8_t XTAL_SU_FORCE_EN : 1;       /*!< [0..0] nan                                                                */
        __IOM uint8_t RC_OP_FORCE_EN : 1;         /*!< [1..1] nan                                                                */
        __IOM uint8_t HP_FORCE_EN : 1;            /*!< [2..2] nan                                                                */
              uint8_t             : 1;
        __IOM uint8_t XTAL_SU_FORCE_VAL : 1;      /*!< [4..4] nan                                                                */
        __IOM uint8_t RC_OP_FORCE_VAL : 1;        /*!< [5..5] nan                                                                */
        __IOM uint8_t HP_FORCE_VAL : 1;           /*!< [6..6] nan                                                                */
              uint8_t             : 1;
      } DA_FORCE_CTRL_b;
    } ;
    __IM  uint8_t   RESERVED26;
    __IM  uint16_t  RESERVED27;
    __IM  uint32_t  RESERVED28[15];
    
    union {
      __IOM uint8_t RAM_HIGH_CTRL;                /*!< (@ 0x000000E0) RAM_HIGH_CTRL                                              */
      
      struct {
        __IOM uint8_t RAM_HIGH_EN : 1;            /*!< [0..0] nan                                                                */
        __IOM uint8_t RAM_HIGH_LOCK : 1;          /*!< [1..1] nan                                                                */
              uint8_t             : 6;
      } RAM_HIGH_CTRL_b;
    } ;
    __IM  uint8_t   RESERVED29;
    __IM  uint16_t  RESERVED30;
    __IM  uint32_t  RESERVED31[9];
    
    union {
      __IOM uint32_t RCO24M_CFG;                  /*!< (@ 0x00000108) RCO24M_CFG                                                 */
      
      struct {
        __IOM uint32_t AON_RG_RCO24M_TCC : 4;     /*!< [3..0] nan                                                                */
        __IOM uint32_t AON_RG_RCO24M_FREQ_SEL : 3;/*!< [6..4] nan                                                                */
        __IOM uint32_t AON_RG_RCO24M_CMP_HP : 1;  /*!< [7..7] nan                                                                */
        __IOM uint32_t AON_RCO24M_CC : 8;         /*!< [15..8] nan                                                               */
        __IOM uint32_t AON_RCO24M_CC_XO_SU : 8;   /*!< [23..16] nan                                                              */
        __IOM uint32_t reserve    : 8;            /*!< [31..24] 0                                                                */
      } RCO24M_CFG_b;
    } ;
    
    union {
      __IOM uint16_t RCO32K_CFG;                  /*!< (@ 0x0000010C) RCO32K_CFG                                                 */
      
      struct {
        __IOM uint16_t AON_RG_RCO32K_TCC : 4;     /*!< [3..0] nan                                                                */
        __IOM uint16_t AON_RG_RCO32K_IC : 2;      /*!< [5..4] nan                                                                */
        __IOM uint16_t AON_RG_RCO32K_CMP_HP : 1;  /*!< [6..6] nan                                                                */
        __IOM uint16_t AON_RG_RCO32K_CC : 8;      /*!< [14..7] nan                                                               */
              uint16_t            : 1;
      } RCO32K_CFG_b;
    } ;
    __IM  uint16_t  RESERVED32;
    
    union {
      __IOM uint32_t XO_CFG;                      /*!< (@ 0x00000110) XO_CFG                                                     */
      
      struct {
        __IOM uint32_t AON_RG_XO_SU_IC : 3;       /*!< [2..0] nan                                                                */
        __IOM uint32_t AON_RG_XO_OBUF_RC : 2;     /*!< [4..3] nan                                                                */
        __IOM uint32_t AON_RG_XO_OBUF_DOUBLER_DELAY : 2;/*!< [6..5] nan                                                          */
        __IOM uint32_t AON_RG_XO_LDO_VC : 4;      /*!< [10..7] nan                                                               */
        __IOM uint32_t AON_RG_XO_IBC : 4;         /*!< [14..11] nan                                                              */
        __IOM uint32_t AON_RG_XO_ED_VTH_SEL : 2;  /*!< [16..15] nan                                                              */
        __IOM uint32_t AON_RG_XO_ED_EN : 1;       /*!< [17..17] nan                                                              */
        __IOM uint32_t AON_RG_XO_CTUNE : 6;       /*!< [23..18] nan                                                              */
        __IOM uint32_t reserve    : 8;            /*!< [31..24] 0                                                                */
      } XO_CFG_b;
    } ;
    __IM  uint32_t  RESERVED33[3];
    
    union {
      __IOM uint8_t GPIO50_CFG;                   /*!< (@ 0x00000120) GPIO50_CFG                                                 */
      
      struct {
        __IOM uint8_t AON_RG_GPIO50_EN : 1;       /*!< [0..0] nan                                                                */
        __IOM uint8_t AON_RG_GPIO50_PWR_SEL : 1;  /*!< [1..1] nan                                                                */
        __IOM uint8_t AON_RG_GPIO50_AVDD33_AON_SEL : 1;/*!< [2..2] nan                                                           */
              uint8_t             : 5;
      } GPIO50_CFG_b;
    } ;
    __IM  uint8_t   RESERVED34;
    __IM  uint16_t  RESERVED35;
    
    union {
      __IOM uint8_t IO_LDO_CTRL;                  /*!< (@ 0x00000124) IO_LDO_CTRL                                                */
      
      struct {
        __IOM uint8_t AON_RG_LDO_IO_EN : 1;       /*!< [0..0] nan                                                                */
        __IOM uint8_t AON_RG_LDO_IO_BYP : 1;      /*!< [1..1] nan                                                                */
        __IOM uint8_t AON_RG_LDO_IO_WAKE_BIAS_EN : 1;/*!< [2..2] nan                                                             */
        __IOM uint8_t AON_RG_LDO_IO_WAKE_CORE_EN : 1;/*!< [3..3] nan                                                             */
        __IOM uint8_t AON_RG_LDO_IO_PWD_PU : 1;   /*!< [4..4] nan                                                                */
              uint8_t             : 3;
      } IO_LDO_CTRL_b;
    } ;
    __IM  uint8_t   RESERVED36;
    __IM  uint16_t  RESERVED37;
    
    union {
      __IOM uint8_t IO_LDO_CFG;                   /*!< (@ 0x00000128) IO_LDO_CFG                                                 */
      
      struct {
        __IOM uint8_t AON_RG_LDO_IO_VSEL : 1;     /*!< [0..0] nan                                                                */
        __IOM uint8_t AON_RG_LDO_IO_VTRIM : 5;    /*!< [5..1] nan                                                                */
              uint8_t             : 2;
      } IO_LDO_CFG_b;
    } ;
    __IM  uint8_t   RESERVED38;
    __IM  uint16_t  RESERVED39;
    __IM  uint32_t  RESERVED40[53];
    
    union {
      __IOM uint8_t PWR_OV_STATUS;                /*!< (@ 0x00000200) PWR_OV_STATUS                                              */
      
      struct {
        __IM  uint8_t AON_AD_VBAT_OV33_FLAG : 1;  /*!< [0..0] nan                                                                */
        __IM  uint8_t AON_AD_VCORE_OV33_FLAG : 1; /*!< [1..1] nan                                                                */
              uint8_t             : 6;
      } PWR_OV_STATUS_b;
    } ;
    __IM  uint8_t   RESERVED41;
    __IM  uint16_t  RESERVED42;
  } AON_CTRL_Type;                                /*!< Size = 516 (0x204)                                                        */
  

/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief UART (UART)
  */

typedef struct {                                /*!< (@ 0x41001000) UART Structure                                             */
  
  union {
    union {
      __IOM uint16_t RBR;                       /*!< (@ 0x00000000) RBR                                                        */
      
      struct {
        __IM  uint16_t RBR      : 9;            /*!< [8..0] nan                                                                */
              uint16_t          : 7;
      } RBR_b;
    } ;
    
    union {
      __IOM uint16_t THR;                       /*!< (@ 0x00000000) THR                                                        */
      
      struct {
        __OM  uint16_t THR      : 9;            /*!< [8..0] nan                                                                */
              uint16_t          : 7;
      } THR_b;
    } ;
    
    union {
      __IOM uint8_t DLL;                        /*!< (@ 0x00000000) DLL                                                        */
      
      struct {
        __IOM uint8_t DLL       : 8;            /*!< [7..0] nan                                                                */
      } DLL_b;
    } ;
  };
  __IM  uint16_t  RESERVED;
  
  union {
    union {
      __IOM uint8_t DLH;                        /*!< (@ 0x00000004) DLH                                                        */
      
      struct {
        __IOM uint8_t DLH       : 8;            /*!< [7..0] nan                                                                */
      } DLH_b;
    } ;
    
    union {
      __IOM uint8_t IER;                        /*!< (@ 0x00000004) IER                                                        */
      
      struct {
        __IOM uint8_t ERBFI     : 1;            /*!< [0..0] nan                                                                */
        __IOM uint8_t ETBEI     : 1;            /*!< [1..1] nan                                                                */
        __IOM uint8_t ELSI      : 1;            /*!< [2..2] nan                                                                */
        __IOM uint8_t EDSSI     : 1;            /*!< [3..3] nan                                                                */
        __IM  uint8_t ELCOLR    : 1;            /*!< [4..4] nan                                                                */
              uint8_t           : 2;
        __IOM uint8_t PTME      : 1;            /*!< [7..7] nan                                                                */
      } IER_b;
    } ;
  };
  __IM  uint8_t   RESERVED1;
  __IM  uint16_t  RESERVED2;
  
  union {
    union {
      __IOM uint8_t IIR;                        /*!< (@ 0x00000008) IIR                                                        */
      
      struct {
        __IM  uint8_t IID       : 4;            /*!< [3..0] nan                                                                */
              uint8_t           : 2;
        __IM  uint8_t FIFOSE    : 2;            /*!< [7..6] nan                                                                */
      } IIR_b;
    } ;
    
    union {
      __IOM uint8_t FCR;                        /*!< (@ 0x00000008) FCR                                                        */
      
      struct {
        __OM  uint8_t FIFOE     : 1;            /*!< [0..0] nan                                                                */
        __OM  uint8_t RFIFOR    : 1;            /*!< [1..1] nan                                                                */
        __OM  uint8_t XFIFOR    : 1;            /*!< [2..2] nan                                                                */
        __OM  uint8_t DMAM      : 1;            /*!< [3..3] nan                                                                */
        __IOM uint8_t TET       : 2;            /*!< [5..4] nan                                                                */
        __OM  uint8_t RT        : 2;            /*!< [7..6] nan                                                                */
      } FCR_b;
    } ;
  };
  __IM  uint8_t   RESERVED3;
  __IM  uint16_t  RESERVED4;
  
  union {
    __IOM uint8_t LCR;                          /*!< (@ 0x0000000C) LCR                                                        */
    
    struct {
      __IOM uint8_t DLS         : 2;            /*!< [1..0] nan                                                                */
      __IOM uint8_t STOP        : 1;            /*!< [2..2] nan                                                                */
      __IOM uint8_t PEN         : 1;            /*!< [3..3] nan                                                                */
      __IOM uint8_t EPS         : 1;            /*!< [4..4] nan                                                                */
      __IOM uint8_t SP          : 1;            /*!< [5..5] nan                                                                */
      __IOM uint8_t BC          : 1;            /*!< [6..6] nan                                                                */
      __IOM uint8_t DLAB        : 1;            /*!< [7..7] nan                                                                */
    } LCR_b;
  } ;
  __IM  uint8_t   RESERVED5;
  __IM  uint16_t  RESERVED6;
  
  union {
    __IOM uint8_t MCR;                          /*!< (@ 0x00000010) MCR                                                        */
    
    struct {
      __IOM uint8_t DTR         : 1;            /*!< [0..0] nan                                                                */
      __IOM uint8_t RTS         : 1;            /*!< [1..1] nan                                                                */
      __IOM uint8_t OUT1        : 1;            /*!< [2..2] nan                                                                */
      __IOM uint8_t OUT2        : 1;            /*!< [3..3] nan                                                                */
      __IOM uint8_t LOOPBACK    : 1;            /*!< [4..4] nan                                                                */
      __IOM uint8_t AFCE        : 1;            /*!< [5..5] nan                                                                */
            uint8_t             : 2;
    } MCR_b;
  } ;
  __IM  uint8_t   RESERVED7;
  __IM  uint16_t  RESERVED8;
  
  union {
    __IOM uint16_t LSR;                         /*!< (@ 0x00000014) LSR                                                        */
    
    struct {
      __IM  uint16_t DR         : 1;            /*!< [0..0] nan                                                                */
      __IM  uint16_t OE         : 1;            /*!< [1..1] nan                                                                */
      __IM  uint16_t PE         : 1;            /*!< [2..2] nan                                                                */
      __IM  uint16_t FE         : 1;            /*!< [3..3] nan                                                                */
      __IM  uint16_t BI         : 1;            /*!< [4..4] nan                                                                */
      __IM  uint16_t THRE       : 1;            /*!< [5..5] nan                                                                */
      __IM  uint16_t TEMT       : 1;            /*!< [6..6] nan                                                                */
      __IM  uint16_t RFE        : 1;            /*!< [7..7] nan                                                                */
      __IM  uint16_t ADDR_RCVD  : 1;            /*!< [8..8] nan                                                                */
            uint16_t            : 7;
    } LSR_b;
  } ;
  __IM  uint16_t  RESERVED9;
  
  union {
    __IOM uint8_t MSR;                          /*!< (@ 0x00000018) MSR                                                        */
    
    struct {
      __IM  uint8_t DCTS        : 1;            /*!< [0..0] nan                                                                */
      __IM  uint8_t DDSR        : 1;            /*!< [1..1] nan                                                                */
      __IM  uint8_t TERI        : 1;            /*!< [2..2] nan                                                                */
      __IM  uint8_t DDCD        : 1;            /*!< [3..3] nan                                                                */
      __IM  uint8_t CTS         : 1;            /*!< [4..4] nan                                                                */
      __IM  uint8_t DSR         : 1;            /*!< [5..5] nan                                                                */
      __IM  uint8_t RI          : 1;            /*!< [6..6] nan                                                                */
      __IM  uint8_t DCD         : 1;            /*!< [7..7] nan                                                                */
    } MSR_b;
  } ;
  __IM  uint8_t   RESERVED10;
  __IM  uint16_t  RESERVED11[49];
  
  union {
    __IOM uint8_t USR;                          /*!< (@ 0x0000007C) USR                                                        */
    
    struct {
      __IM  uint8_t BUSY        : 1;            /*!< [0..0] nan                                                                */
      __IM  uint8_t TFNF        : 1;            /*!< [1..1] nan                                                                */
      __IM  uint8_t TFE         : 1;            /*!< [2..2] nan                                                                */
      __IM  uint8_t RFNE        : 1;            /*!< [3..3] nan                                                                */
      __IM  uint8_t RFF         : 1;            /*!< [4..4] nan                                                                */
            uint8_t             : 3;
    } USR_b;
  } ;
  __IM  uint8_t   RESERVED12;
  __IM  uint16_t  RESERVED13[33];
  
  union {
    __IOM uint8_t DLF;                          /*!< (@ 0x000000C0) DLF                                                        */
    
    struct {
      __IOM uint8_t DLF         : 4;            /*!< [3..0] nan                                                                */
            uint8_t             : 4;
    } DLF_b;
  } ;
  __IM  uint8_t   RESERVED14;
  __IM  uint16_t  RESERVED15[5];
  
  union {
    __IOM uint8_t LCR_EXT;                      /*!< (@ 0x000000CC) LCR_EXT                                                    */
    
    struct {
      __IOM uint8_t DLS_E       : 1;            /*!< [0..0] nan                                                                */
      __IOM uint8_t ADDR_MATCH  : 1;            /*!< [1..1] nan                                                                */
      __IOM uint8_t SEND_ADDR   : 1;            /*!< [2..2] nan                                                                */
      __IOM uint8_t TRANSMIT_MODE : 1;          /*!< [3..3] nan                                                                */
            uint8_t             : 4;
    } LCR_EXT_b;
  } ;
  __IM  uint8_t   RESERVED16;
  __IM  uint16_t  RESERVED17;
} UART_Type;                                    /*!< Size = 208 (0xd0)                                                         */



/* =========================================================================================================================== */
/* ================                                           SPIM                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SPIM (SPIM)
  */

typedef struct {                                /*!< (@ 0x41003000) SPIM Structure                                             */
  
  union {
    __IOM uint32_t CTRLR0;                      /*!< (@ 0x00000000) CTRLR0                                                     */
    
    struct {
      __IOM uint32_t DFS        : 4;            /*!< [3..0] nan                                                                */
      __IOM uint32_t FRF        : 2;            /*!< [5..4] nan                                                                */
      __IOM uint32_t SCPH       : 1;            /*!< [6..6] nan                                                                */
      __IOM uint32_t SCPOL      : 1;            /*!< [7..7] nan                                                                */
      __IOM uint32_t TMOD       : 2;            /*!< [9..8] nan                                                                */
      __IOM uint32_t SLV_OE     : 1;            /*!< [10..10] nan                                                              */
      __IOM uint32_t SRL        : 1;            /*!< [11..11] nan                                                              */
      __IOM uint32_t CFS        : 4;            /*!< [15..12] nan                                                              */
      __IM  uint32_t DFS_32     : 5;            /*!< [20..16] nan                                                              */
      __IM  uint32_t SPI_FRF    : 2;            /*!< [22..21] nan                                                              */
            uint32_t            : 1;
      __IM  uint32_t SSTE       : 1;            /*!< [24..24] nan                                                              */
            uint32_t            : 7;
    } CTRLR0_b;
  } ;
  
  union {
    __IOM uint16_t CTRLR1;                      /*!< (@ 0x00000004) CTRLR1                                                     */
    
    struct {
      __IOM uint16_t NDF        : 16;           /*!< [15..0] nan                                                               */
    } CTRLR1_b;
  } ;
  __IM  uint16_t  RESERVED;
  
  union {
    __IOM uint8_t SSIENR;                       /*!< (@ 0x00000008) SSIENR                                                     */
    
    struct {
      __IOM uint8_t SSI_EN      : 1;            /*!< [0..0] nan                                                                */
      __IOM uint8_t MODE_3WIRE  : 1;            /*!< [1..1] nan                                                                */
            uint8_t             : 6;
    } SSIENR_b;
  } ;
  __IM  uint8_t   RESERVED1;
  __IM  uint16_t  RESERVED2;
  __IM  uint32_t  RESERVED3;
  
  union {
    __IOM uint8_t SER;                          /*!< (@ 0x00000010) SER                                                        */
    
    struct {
      __IOM uint8_t SER         : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } SER_b;
  } ;
  __IM  uint8_t   RESERVED4;
  __IM  uint16_t  RESERVED5;
  
  union {
    __IOM uint16_t BAUDR;                       /*!< (@ 0x00000014) BAUDR                                                      */
    
    struct {
      __IOM uint16_t SCKDV      : 16;           /*!< [15..0] nan                                                               */
    } BAUDR_b;
  } ;
  __IM  uint16_t  RESERVED6;
  
  union {
    __IOM uint8_t TXFTLR;                       /*!< (@ 0x00000018) TXFTLR                                                     */
    
    struct {
      __IOM uint8_t TFT         : 8;            /*!< [7..0] nan                                                                */
    } TXFTLR_b;
  } ;
  __IM  uint8_t   RESERVED7;
  __IM  uint16_t  RESERVED8;
  
  union {
    __IOM uint8_t RXFTLR;                       /*!< (@ 0x0000001C) RXFTLR                                                     */
    
    struct {
      __IOM uint8_t RFT         : 8;            /*!< [7..0] nan                                                                */
    } RXFTLR_b;
  } ;
  __IM  uint8_t   RESERVED9;
  __IM  uint16_t  RESERVED10;
  
  union {
    __IOM uint16_t TXFLR;                       /*!< (@ 0x00000020) TXFLR                                                      */
    
    struct {
      __IM  uint16_t TXTFL      : 9;            /*!< [8..0] nan                                                                */
            uint16_t            : 7;
    } TXFLR_b;
  } ;
  __IM  uint16_t  RESERVED11;
  
  union {
    __IOM uint16_t RXFLR;                       /*!< (@ 0x00000024) RXFLR                                                      */
    
    struct {
      __IM  uint16_t RXTFL      : 9;            /*!< [8..0] nan                                                                */
            uint16_t            : 7;
    } RXFLR_b;
  } ;
  __IM  uint16_t  RESERVED12;
  
  union {
    __IOM uint8_t SR;                           /*!< (@ 0x00000028) SR                                                         */
    
    struct {
      __IM  uint8_t BUSY        : 1;            /*!< [0..0] nan                                                                */
      __IM  uint8_t TFNF        : 1;            /*!< [1..1] nan                                                                */
      __IM  uint8_t TFE         : 1;            /*!< [2..2] nan                                                                */
      __IM  uint8_t RFNE        : 1;            /*!< [3..3] nan                                                                */
      __IM  uint8_t RFF         : 1;            /*!< [4..4] nan                                                                */
      __IM  uint8_t TXE         : 1;            /*!< [5..5] nan                                                                */
      __IM  uint8_t DCOL        : 1;            /*!< [6..6] nan                                                                */
            uint8_t             : 1;
    } SR_b;
  } ;
  __IM  uint8_t   RESERVED13;
  __IM  uint16_t  RESERVED14;
  
  union {
    __IOM uint8_t IMR;                          /*!< (@ 0x0000002C) IMR                                                        */
    
    struct {
      __IOM uint8_t TXEIM       : 1;            /*!< [0..0] nan                                                                */
      __IOM uint8_t TXOIM       : 1;            /*!< [1..1] nan                                                                */
      __IOM uint8_t RXUIM       : 1;            /*!< [2..2] nan                                                                */
      __IOM uint8_t RXOIM       : 1;            /*!< [3..3] nan                                                                */
      __IOM uint8_t RXFIM       : 1;            /*!< [4..4] nan                                                                */
      __IOM uint8_t MSTIM       : 1;            /*!< [5..5] nan                                                                */
            uint8_t             : 2;
    } IMR_b;
  } ;
  __IM  uint8_t   RESERVED15;
  __IM  uint16_t  RESERVED16;
  
  union {
    __IOM uint8_t ISR;                          /*!< (@ 0x00000030) ISR                                                        */
    
    struct {
      __IM  uint8_t TXEIS       : 1;            /*!< [0..0] nan                                                                */
      __IM  uint8_t TXOIS       : 1;            /*!< [1..1] nan                                                                */
      __IM  uint8_t RXUIS       : 1;            /*!< [2..2] nan                                                                */
      __IM  uint8_t RXOIS       : 1;            /*!< [3..3] nan                                                                */
      __IM  uint8_t RXFIS       : 1;            /*!< [4..4] nan                                                                */
      __IM  uint8_t MSTIS       : 1;            /*!< [5..5] nan                                                                */
            uint8_t             : 2;
    } ISR_b;
  } ;
  __IM  uint8_t   RESERVED17;
  __IM  uint16_t  RESERVED18;
  __IM  uint32_t  RESERVED19[5];
  
  union {
    __IOM uint8_t ICR;                          /*!< (@ 0x00000048) ICR                                                        */
    
    struct {
      __IM  uint8_t ICR         : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } ICR_b;
  } ;
  __IM  uint8_t   RESERVED20;
  __IM  uint16_t  RESERVED21;
  __IM  uint32_t  RESERVED22[5];
  
  union {
    __IOM uint16_t DR16;                        /*!< (@ 0x00000060) DR16                                                       */
    
    struct {
      __IOM uint16_t DR         : 16;           /*!< [15..0] nan                                                               */
    } DR16_b;
  } ;
  __IM  uint16_t  RESERVED23;
} SPIM_Type;                                    /*!< Size = 100 (0x64)                                                         */



/* =========================================================================================================================== */
/* ================                                            IIC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief IIC (IIC)
  */

typedef struct {                                /*!< (@ 0x41005000) IIC Structure                                              */
  
  union {
    __IOM uint8_t IC_CON;                       /*!< IC_CON                                                                    */
    
    struct {
      __IOM uint8_t MASTER_MODE : 1;            /*!< nan                                                                       */
      __IOM uint8_t SPEED       : 2;            /*!< nan                                                                       */
      __IOM uint8_t IC_10BITADDR_SLAVE : 1;     /*!< nan                                                                       */
      __IOM uint8_t IC_10BITADDR_MASTER : 1;    /*!< nan                                                                       */
      __IOM uint8_t IC_RESTART_EN : 1;          /*!< nan                                                                       */
      __IOM uint8_t IC_SLAVE_DISABLE : 1;       /*!< nan                                                                       */
            uint8_t             : 1;
    } IC_CON_b;
  } ;
  __IM  uint8_t   RESERVED;
  __IM  uint16_t  RESERVED1;
  
  union {
    __IOM uint16_t IC_TAR;                      /*!< IC_TAR                                                                    */
    
    struct {
      __IOM uint16_t IC_TAR     : 10;           /*!< nan                                                                       */
            uint16_t            : 6;
    } IC_TAR_b;
  } ;
  __IM  uint16_t  RESERVED2;
  
  union {
    __IOM uint16_t IC_SAR;                      /*!< IC_SAR                                                                    */
    
    struct {
      __IOM uint16_t IC_SAR     : 10;           /*!< nan                                                                       */
            uint16_t            : 6;
    } IC_SAR_b;
  } ;
  __IM  uint16_t  RESERVED3[3];
  
  union {
    __IOM uint16_t IC_DATA_CMD;                 /*!< IC_DATA_CMD                                                               */
    
    struct {
      __IOM uint16_t DAT        : 8;            /*!< nan                                                                       */
      __OM  uint16_t CMD        : 1;            /*!< nan                                                                       */
            uint16_t            : 7;
    } IC_DATA_CMD_b;
  } ;
  __IM  uint16_t  RESERVED4;
  
  union {
    __IOM uint16_t IC_SS_SCL_HCNT;              /*!< (@ 0x00000014) IC_SS_SCL_HCNT                                             */
    
    struct {
      __IOM uint16_t IC_SS_SCL_HCNT : 16;       /*!< [15..0] nan                                                               */
    } IC_SS_SCL_HCNT_b;
  } ;
  __IM  uint16_t  RESERVED5;
  
  union {
    __IOM uint16_t IC_SS_SCL_LCNT;              /*!< (@ 0x00000018) IC_SS_SCL_LCNT                                             */
    
    struct {
      __IOM uint16_t IC_SS_SCL_LCNT : 16;       /*!< [15..0] nan                                                               */
    } IC_SS_SCL_LCNT_b;
  } ;
  __IM  uint16_t  RESERVED6;
  
  union {
    __IOM uint16_t IC_FS_SCL_HCNT;              /*!< (@ 0x0000001C) IC_FS_SCL_HCNT                                             */
    
    struct {
      __IOM uint16_t IC_FS_SCL_HCNT : 16;       /*!< [15..0] nan                                                               */
    } IC_FS_SCL_HCNT_b;
  } ;
  __IM  uint16_t  RESERVED7;
  
  union {
    __IOM uint16_t IC_FS_SCL_LCNT;              /*!< (@ 0x00000020) IC_FS_SCL_LCNT                                             */
    
    struct {
      __IOM uint16_t IC_FS_SCL_LCNT : 16;       /*!< [15..0] nan                                                               */
    } IC_FS_SCL_LCNT_b;
  } ;
  __IM  uint16_t  RESERVED8[5];
  
  union {
    __IOM uint16_t IC_INTR_STAT;                /*!< (@ 0x0000002C) IC_INTR_STAT                                               */
    
    struct {
      __IM  uint16_t R_RX_UNDER : 1;            /*!< [0..0] nan                                                                */
      __IM  uint16_t R_RX_OVER  : 1;            /*!< [1..1] nan                                                                */
      __IM  uint16_t R_RX_FULL  : 1;            /*!< [2..2] nan                                                                */
      __IM  uint16_t R_TX_OVER  : 1;            /*!< [3..3] nan                                                                */
      __IM  uint16_t R_TX_EMPTY : 1;            /*!< [4..4] nan                                                                */
      __IM  uint16_t R_RD_REQ   : 1;            /*!< [5..5] nan                                                                */
      __IM  uint16_t R_TX_ABRT  : 1;            /*!< [6..6] nan                                                                */
      __IM  uint16_t R_RX_DONE  : 1;            /*!< [7..7] nan                                                                */
      __IM  uint16_t R_ACTIVITY : 1;            /*!< [8..8] nan                                                                */
      __IM  uint16_t R_STOP_DET : 1;            /*!< [9..9] nan                                                                */
      __IM  uint16_t R_START_DET : 1;           /*!< [10..10] nan                                                              */
            uint16_t            : 5;
    } IC_INTR_STAT_b;
  } ;
  __IM  uint16_t  RESERVED9;
  
  union {
    __IOM uint16_t IC_INTR_MASK;                /*!< IC_INTR_MASK                                                              */
    
    struct {
      __IOM uint16_t M_RX_UNDER : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_RX_OVER  : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_RX_FULL  : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_TX_OVER  : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_TX_EMPTY : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_RD_REQ   : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_TX_ABRT  : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_RX_DONE  : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_ACTIVITY : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_STOP_DET : 1;            /*!< nan                                                                       */
      __IOM uint16_t M_START_DET : 1;           /*!< nan                                                                       */
            uint16_t            : 5;
    } IC_INTR_MASK_b;
  } ;
  __IM  uint16_t  RESERVED10;
  
  union {
    __IOM uint16_t IC_RAW_INTR_STAT;            /*!< (@ 0x00000034) IC_RAW_INTR_STAT                                           */
    
    struct {
      __IM  uint16_t RX_UNDER   : 1;            /*!< [0..0] nan                                                                */
      __IM  uint16_t RX_OVER    : 1;            /*!< [1..1] nan                                                                */
      __IM  uint16_t RX_FULL    : 1;            /*!< [2..2] nan                                                                */
      __IM  uint16_t TX_OVER    : 1;            /*!< [3..3] nan                                                                */
      __IM  uint16_t TX_EMPTY   : 1;            /*!< [4..4] nan                                                                */
      __IM  uint16_t RD_REQ     : 1;            /*!< [5..5] nan                                                                */
      __IM  uint16_t TX_ABRT    : 1;            /*!< [6..6] nan                                                                */
      __IM  uint16_t RX_DONE    : 1;            /*!< [7..7] nan                                                                */
      __IM  uint16_t ACTIVITY   : 1;            /*!< [8..8] nan                                                                */
      __IM  uint16_t STOP_DET   : 1;            /*!< [9..9] nan                                                                */
      __IM  uint16_t START_DET  : 1;            /*!< [10..10] nan                                                              */
            uint16_t            : 5;
    } IC_RAW_INTR_STAT_b;
  } ;
  __IM  uint16_t  RESERVED11;
  
  union {
    __IOM uint8_t IC_RX_TL;                     /*!< (@ 0x00000038) IC_RX_TL                                                   */
    
    struct {
      __IOM uint8_t RX_TL       : 8;            /*!< [7..0] nan                                                                */
    } IC_RX_TL_b;
  } ;
  __IM  uint8_t   RESERVED12;
  __IM  uint16_t  RESERVED13;
  
  union {
    __IOM uint8_t IC_TX_TL;                     /*!< (@ 0x0000003C) IC_TX_TL                                                   */
    
    struct {
      __IOM uint8_t TX_TL       : 8;            /*!< [7..0] nan                                                                */
    } IC_TX_TL_b;
  } ;
  __IM  uint8_t   RESERVED14;
  __IM  uint16_t  RESERVED15;
  
  union {
    __IOM uint8_t IC_CLR_INTR;                  /*!< (@ 0x00000040) IC_CLR_INTR                                                */
    
    struct {
      __IM  uint8_t CLR_INTR    : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_INTR_b;
  } ;
  __IM  uint8_t   RESERVED16;
  __IM  uint16_t  RESERVED17;
  
  union {
    __IOM uint8_t IC_CLR_RX_UNDER;              /*!< (@ 0x00000044) IC_CLR_RX_UNDER                                            */
    
    struct {
      __IM  uint8_t CLR_RX_UNDER : 1;           /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_RX_UNDER_b;
  } ;
  __IM  uint8_t   RESERVED18;
  __IM  uint16_t  RESERVED19;
  
  union {
    __IOM uint8_t IC_CLR_RX_OVER;               /*!< (@ 0x00000048) IC_CLR_RX_OVER                                             */
    
    struct {
      __IM  uint8_t CLR_RX_OVER : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_RX_OVER_b;
  } ;
  __IM  uint8_t   RESERVED20;
  __IM  uint16_t  RESERVED21;
  
  union {
    __IOM uint8_t IC_CLR_TX_OVER;               /*!< (@ 0x0000004C) IC_CLR_TX_OVER                                             */
    
    struct {
      __IM  uint8_t CLR_TX_OVER : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_TX_OVER_b;
  } ;
  __IM  uint8_t   RESERVED22;
  __IM  uint16_t  RESERVED23;
  
  union {
    __IOM uint8_t IC_CLR_RD_REQ;                /*!< (@ 0x00000050) IC_CLR_RD_REQ                                              */
    
    struct {
      __IM  uint8_t CLR_RD_REQ  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_RD_REQ_b;
  } ;
  __IM  uint8_t   RESERVED24;
  __IM  uint16_t  RESERVED25;
  
  union {
    __IOM uint8_t IC_CLR_TX_ABRT;               /*!< (@ 0x00000054) IC_CLR_TX_ABRT                                             */
    
    struct {
      __IM  uint8_t CLR_TX_ABRT : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_TX_ABRT_b;
  } ;
  __IM  uint8_t   RESERVED26;
  __IM  uint16_t  RESERVED27;
  
  union {
    __IOM uint8_t IC_CLR_RX_DONE;               /*!< (@ 0x00000058) IC_CLR_RX_DONE                                             */
    
    struct {
      __IM  uint8_t CLR_RX_DONE : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_RX_DONE_b;
  } ;
  __IM  uint8_t   RESERVED28;
  __IM  uint16_t  RESERVED29;
  
  union {
    __IOM uint8_t IC_CLR_ACTIVITY;              /*!< (@ 0x0000005C) IC_CLR_ACTIVITY                                            */
    
    struct {
      __IM  uint8_t CLR_ACTIVITY : 1;           /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_ACTIVITY_b;
  } ;
  __IM  uint8_t   RESERVED30;
  __IM  uint16_t  RESERVED31;
  
  union {
    __IOM uint8_t IC_CLR_STOP_DET;              /*!< (@ 0x00000060) IC_CLR_STOP_DET                                            */
    
    struct {
      __IM  uint8_t CLR_STOP_DET : 1;           /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_STOP_DET_b;
  } ;
  __IM  uint8_t   RESERVED32;
  __IM  uint16_t  RESERVED33;
  
  union {
    __IOM uint8_t IC_CLR_START_DET;             /*!< (@ 0x00000064) IC_CLR_START_DET                                           */
    
    struct {
      __IM  uint8_t CLR_START_DET : 1;          /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_CLR_START_DET_b;
  } ;
  __IM  uint8_t   RESERVED34;
  __IM  uint16_t  RESERVED35[3];
  
  union {
    __IOM uint8_t IC_ENABLE;                    /*!< (@ 0x0000006C) IC_ENABLE                                                  */
    
    struct {
      __IOM uint8_t IC_ENABLE   : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } IC_ENABLE_b;
  } ;
  __IM  uint8_t   RESERVED36;
  __IM  uint16_t  RESERVED37;
  union {
    __IOM uint8_t IC_STAUS;                     /*!< IC_STAUS                                                                  */
    struct {
      __IM  uint8_t ACTIVITY    : 1;            /*!< nan                                                                       */
      __IM  uint8_t TFNF        : 1;            /*!< nan                                                                       */
      __IM  uint8_t TFE         : 1;            /*!< nan                                                                       */
      __IM  uint8_t RFNE        : 1;            /*!< nan                                                                       */
      __IM  uint8_t RFF         : 1;            /*!< nan                                                                       */
      __IM  uint8_t MST_ACTIVITY : 1;           /*!< nan                                                                       */
      __IM  uint8_t SLV_ACTIVITY : 1;           /*!< nan                                                                       */
            uint8_t             : 1;
    } IC_STAUS_b;
  } ;
  __IM  uint8_t   RESERVED38;
  __IM  uint16_t  RESERVED39;
  
  union {
    __IOM uint8_t IC_TXFLR;                     /*!< (@ 0x00000074) IC_TXFLR                                                   */
    
    struct {
      __IM  uint8_t TXFLR       : 8;            /*!< [7..0] nan                                                                */
    } IC_TXFLR_b;
  } ;
  __IM  uint8_t   RESERVED40;
  __IM  uint16_t  RESERVED41;
  
  union {
    __IOM uint8_t IC_RXFLR;                     /*!< (@ 0x00000078) IC_RXFLR                                                   */
    
    struct {
      __IM  uint8_t RXFLR       : 8;            /*!< [7..0] nan                                                                */
    } IC_RXFLR_b;
  } ;
  __IM  uint8_t   RESERVED42;
  __IM  uint16_t  RESERVED43;
} IIC_Type;                                     /*!< Size = 124 (0x7c)                                                         */


/* =========================================================================================================================== */
/* ================                                           SPIS                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief SPIS (SPIS)
  */

typedef struct {                                /*!< (@ 0x41007000) SPIS Structure                                             */
  
  union {
    __IOM uint32_t CTRLR0;                      /*!< (@ 0x00000000) CTRLR0                                                     */
    
    struct {
      __IOM uint32_t DFS        : 4;            /*!< [3..0] nan                                                                */
      __IOM uint32_t FRF        : 2;            /*!< [5..4] nan                                                                */
      __IOM uint32_t SCPH       : 1;            /*!< [6..6] nan                                                                */
      __IOM uint32_t SCPOL      : 1;            /*!< [7..7] nan                                                                */
      __IOM uint32_t TMOD       : 2;            /*!< [9..8] nan                                                                */
      __IOM uint32_t SLV_OE     : 1;            /*!< [10..10] nan                                                              */
      __IOM uint32_t SRL        : 1;            /*!< [11..11] nan                                                              */
      __IOM uint32_t CFS        : 4;            /*!< [15..12] nan                                                              */
      __IM  uint32_t DFS_32     : 5;            /*!< [20..16] nan                                                              */
      __IM  uint32_t SPI_FRF    : 2;            /*!< [22..21] nan                                                              */
            uint32_t            : 1;
      __IM  uint32_t SSTE       : 1;            /*!< [24..24] nan                                                              */
            uint32_t            : 7;
    } CTRLR0_b;
  } ;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint8_t SSIENR;                       /*!< (@ 0x00000008) SSIENR                                                     */
    
    struct {
      __IOM uint8_t SSI_EN      : 1;            /*!< [0..0] nan                                                                */
      __IOM uint8_t MODE_3WIRE  : 1;            /*!< [1..1] nan                                                                */
      __IOM uint8_t FIFO_FEN    : 1;            /*!< [2..2] nan                                                                */
      __IOM uint8_t FRX_MODE    : 1;            /*!< [3..3] nan                                                                */
      __IOM uint8_t NCS_MODE    : 2;            /*!< [5..4] nan                                                                */
            uint8_t             : 2;
    } SSIENR_b;
  } ;
  __IM  uint8_t   RESERVED1;
  __IM  uint16_t  RESERVED2;
  __IM  uint32_t  RESERVED3[3];
  
  union {
    __IOM uint8_t TXFTLR;                       /*!< (@ 0x00000018) TXFTLR                                                     */
    
    struct {
      __IOM uint8_t TFT         : 8;            /*!< [7..0] nan                                                                */
    } TXFTLR_b;
  } ;
  __IM  uint8_t   RESERVED4;
  __IM  uint16_t  RESERVED5;
  
  union {
    __IOM uint8_t RXFTLR;                       /*!< (@ 0x0000001C) RXFTLR                                                     */
    
    struct {
      __IOM uint8_t RFT         : 8;            /*!< [7..0] nan                                                                */
    } RXFTLR_b;
  } ;
  __IM  uint8_t   RESERVED6;
  __IM  uint16_t  RESERVED7;
  
  union {
    __IOM uint16_t TXFLR;                       /*!< (@ 0x00000020) TXFLR                                                      */
    
    struct {
      __IM  uint16_t TXTFL      : 9;            /*!< [8..0] nan                                                                */
            uint16_t            : 7;
    } TXFLR_b;
  } ;
  __IM  uint16_t  RESERVED8;
  
  union {
    __IOM uint16_t RXFLR;                       /*!< (@ 0x00000024) RXFLR                                                      */
    
    struct {
      __IM  uint16_t RXTFL      : 9;            /*!< [8..0] nan                                                                */
            uint16_t            : 7;
    } RXFLR_b;
  } ;
  __IM  uint16_t  RESERVED9;
  
  union {
    __IOM uint8_t SR;                           /*!< (@ 0x00000028) SR                                                         */
    
    struct {
      __IM  uint8_t BUSY        : 1;            /*!< [0..0] nan                                                                */
      __IM  uint8_t TFNF        : 1;            /*!< [1..1] nan                                                                */
      __IM  uint8_t TFE         : 1;            /*!< [2..2] nan                                                                */
      __IM  uint8_t RFNE        : 1;            /*!< [3..3] nan                                                                */
      __IM  uint8_t RFF         : 1;            /*!< [4..4] nan                                                                */
      __IM  uint8_t TXE         : 1;            /*!< [5..5] nan                                                                */
      __IM  uint8_t DCOL        : 1;            /*!< [6..6] nan                                                                */
            uint8_t             : 1;
    } SR_b;
  } ;
  __IM  uint8_t   RESERVED10;
  __IM  uint16_t  RESERVED11;
  
  union {
    __IOM uint8_t IMR;                          /*!< (@ 0x0000002C) IMR                                                        */
    
    struct {
      __IOM uint8_t TXEIM       : 1;            /*!< [0..0] nan                                                                */
      __IOM uint8_t TXOIM       : 1;            /*!< [1..1] nan                                                                */
      __IOM uint8_t RXUIM       : 1;            /*!< [2..2] nan                                                                */
      __IOM uint8_t RXOIM       : 1;            /*!< [3..3] nan                                                                */
      __IOM uint8_t RXFIM       : 1;            /*!< [4..4] nan                                                                */
            uint8_t             : 3;
    } IMR_b;
  } ;
  __IM  uint8_t   RESERVED12;
  __IM  uint16_t  RESERVED13;
  
  union {
    __IOM uint8_t ISR;                          /*!< (@ 0x00000030) ISR                                                        */
    
    struct {
      __IM  uint8_t TXEIS       : 1;            /*!< [0..0] nan                                                                */
      __IM  uint8_t TXOIS       : 1;            /*!< [1..1] nan                                                                */
      __IM  uint8_t RXUIS       : 1;            /*!< [2..2] nan                                                                */
      __IM  uint8_t RXOIS       : 1;            /*!< [3..3] nan                                                                */
      __IM  uint8_t RXFIS       : 1;            /*!< [4..4] nan                                                                */
            uint8_t             : 3;
    } ISR_b;
  } ;
  __IM  uint8_t   RESERVED14;
  __IM  uint16_t  RESERVED15;
  __IM  uint32_t  RESERVED16[5];
  
  union {
    __IOM uint8_t ICR;                          /*!< (@ 0x00000048) ICR                                                        */
    
    struct {
      __IM  uint8_t ICR         : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } ICR_b;
  } ;
  __IM  uint8_t   RESERVED17;
  __IM  uint16_t  RESERVED18;
  __IM  uint32_t  RESERVED19[5];
  
  union {
    __IOM uint16_t DR16;                        /*!< (@ 0x00000060) DR16                                                       */
    
    struct {
      __IOM uint16_t DR         : 16;           /*!< [15..0] nan                                                               */
    } DR16_b;
  } ;
  __IM  uint16_t  RESERVED20;
} SPIS_Type;                                    /*!< Size = 100 (0x64)                                                         */



/* =========================================================================================================================== */
/* ================                                           TIMER                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief TIMER (TIMER)
  */

typedef struct {                                /*!< (@ 0x41008000) TIMER Structure                                            */
  
  union {
    __IOM uint16_t TIMER0_LOAD_COUNT;           /*!< (@ 0x00000000) TIMER0_LOAD_COUNT                                          */
    
    struct {
      __IOM uint16_t TIMER0_LOAD_COUNT : 16;    /*!< [15..0] nan                                                               */
    } TIMER0_LOAD_COUNT_b;
  } ;
  __IM  uint16_t  RESERVED;
  
  union {
    __IOM uint16_t TIMER0_CURRENT_VALUE;        /*!< (@ 0x00000004) TIMER0_CURRENT_VALUE                                       */
    
    struct {
      __IM  uint16_t TIMER0_CURRENT_VALUE : 16; /*!< [15..0] nan                                                               */
    } TIMER0_CURRENT_VALUE_b;
  } ;
  __IM  uint16_t  RESERVED1;
  
  union {
    __IOM uint32_t TIMER0_CONTROL_REG;          /*!< (@ 0x00000008) TIMER0_CONTROL_REG                                         */
    
    struct {
      __IOM uint32_t TIMER0_ENABLE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint32_t TIMER0_MODE : 1;           /*!< [1..1] nan                                                                */
      __IOM uint32_t TIMER0_INTERRUPT_MASK : 1; /*!< [2..2] nan                                                                */
      __IOM uint32_t TIMER0_PWM : 1;            /*!< [3..3] nan                                                                */
      __IM  uint32_t TIMER0_0N100PWM_EN : 1;    /*!< [4..4] nan                                                                */
      __IOM uint32_t TIMER0_DT_EN : 1;          /*!< [5..5] nan                                                                */
      __IOM uint32_t TIMER0_PWM_INIT_N : 1;     /*!< [6..6] nan                                                                */
      __IOM uint32_t TIMER0_PWM_INIT_P : 1;     /*!< [7..7] nan                                                                */
      __IOM uint32_t TIMER0_DT_LEN : 8;         /*!< [15..8] nan                                                               */
      __IOM uint32_t TIMER0_PWM_POL_N : 1;      /*!< [16..16] nan                                                              */
      __IOM uint32_t TIMER0_PWM_POL_P : 1;      /*!< [17..17] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } TIMER0_CONTROL_REG_b;
  } ;
  
  union {
    __IOM uint8_t TIMER0_EOI;                   /*!< (@ 0x0000000C) TIMER0_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMER0_EOI  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER0_EOI_b;
  } ;
  __IM  uint8_t   RESERVED2;
  __IM  uint16_t  RESERVED3;
  
  union {
    __IOM uint8_t TIMER0_INT_STATUS;            /*!< (@ 0x00000010) TIMER0_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMER0_INT_STATUS : 1;      /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER0_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED4;
  __IM  uint16_t  RESERVED5;
  
  union {
    __IOM uint16_t TIMER1_LOAD_COUNT;           /*!< (@ 0x00000014) TIMER1_LOAD_COUNT                                          */
    
    struct {
      __IOM uint16_t TIMER1_LOAD_COUNT : 16;    /*!< [15..0] nan                                                               */
    } TIMER1_LOAD_COUNT_b;
  } ;
  __IM  uint16_t  RESERVED6;
  
  union {
    __IOM uint16_t TIMER1_CURRENT_VALUE;        /*!< (@ 0x00000018) TIMER1_CURRENT_VALUE                                       */
    
    struct {
      __IM  uint16_t TIMER1_CURRENT_VALUE : 16; /*!< [15..0] nan                                                               */
    } TIMER1_CURRENT_VALUE_b;
  } ;
  __IM  uint16_t  RESERVED7;
  
  union {
    __IOM uint32_t TIMER1_CONTROL_REG;          /*!< (@ 0x0000001C) TIMER1_CONTROL_REG                                         */
    
    struct {
      __IOM uint32_t TIMER1_ENABLE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint32_t TIMER1_MODE : 1;           /*!< [1..1] nan                                                                */
      __IOM uint32_t TIMER1_INTERRUPT_MASK : 1; /*!< [2..2] nan                                                                */
      __IOM uint32_t TIMER1_PWM : 1;            /*!< [3..3] nan                                                                */
      __IM  uint32_t TIMER1_0N100PWM_EN : 1;    /*!< [4..4] nan                                                                */
      __IOM uint32_t TIMER1_DT_EN : 1;          /*!< [5..5] nan                                                                */
      __IOM uint32_t TIMER1_PWM_INIT_N : 1;     /*!< [6..6] nan                                                                */
      __IOM uint32_t TIMER1_PWM_INIT_P : 1;     /*!< [7..7] nan                                                                */
      __IOM uint32_t TIMER1_DT_LEN : 8;         /*!< [15..8] nan                                                               */
      __IOM uint32_t TIMER1_PWM_POL_N : 1;      /*!< [16..16] nan                                                              */
      __IOM uint32_t TIMER1_PWM_POL_P : 1;      /*!< [17..17] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } TIMER1_CONTROL_REG_b;
  } ;
  
  union {
    __IOM uint8_t TIMER1_EOI;                   /*!< (@ 0x00000020) TIMER1_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMER1_EOI  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER1_EOI_b;
  } ;
  __IM  uint8_t   RESERVED8;
  __IM  uint16_t  RESERVED9;
  
  union {
    __IOM uint8_t TIMER1_INT_STATUS;            /*!< (@ 0x00000024) TIMER1_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMER1_INT_STATUS : 1;      /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER1_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED10;
  __IM  uint16_t  RESERVED11;
  
  union {
    __IOM uint16_t TIMER2_LOAD_COUNT;           /*!< (@ 0x00000028) TIMER2_LOAD_COUNT                                          */
    
    struct {
      __IOM uint16_t TIMER2_LOAD_COUNT : 16;    /*!< [15..0] nan                                                               */
    } TIMER2_LOAD_COUNT_b;
  } ;
  __IM  uint16_t  RESERVED12;
  
  union {
    __IOM uint16_t TIMER2_CURRENT_VALUE;        /*!< (@ 0x0000002C) TIMER2_CURRENT_VALUE                                       */
    
    struct {
      __IM  uint16_t TIMER2_CURRENT_VALUE : 16; /*!< [15..0] nan                                                               */
    } TIMER2_CURRENT_VALUE_b;
  } ;
  __IM  uint16_t  RESERVED13;
  
  union {
    __IOM uint32_t TIMER2_CONTROL_REG;          /*!< (@ 0x00000030) TIMER2_CONTROL_REG                                         */
    
    struct {
      __IOM uint32_t TIMER2_ENABLE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint32_t TIMER2_MODE : 1;           /*!< [1..1] nan                                                                */
      __IOM uint32_t TIMER2_INTERRUPT_MASK : 1; /*!< [2..2] nan                                                                */
      __IOM uint32_t TIMER2_PWM : 1;            /*!< [3..3] nan                                                                */
      __IM  uint32_t TIMER2_0N100PWM_EN : 1;    /*!< [4..4] nan                                                                */
      __IOM uint32_t TIMER2_DT_EN : 1;          /*!< [5..5] nan                                                                */
      __IOM uint32_t TIMER2_PWM_INIT_N : 1;     /*!< [6..6] nan                                                                */
      __IOM uint32_t TIMER2_PWM_INIT_P : 1;     /*!< [7..7] nan                                                                */
      __IOM uint32_t TIMER2_DT_LEN : 8;         /*!< [15..8] nan                                                               */
      __IOM uint32_t TIMER2_PWM_POL_N : 1;      /*!< [16..16] nan                                                              */
      __IOM uint32_t TIMER2_PWM_POL_P : 1;      /*!< [17..17] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } TIMER2_CONTROL_REG_b;
  } ;
  
  union {
    __IOM uint8_t TIMER2_EOI;                   /*!< (@ 0x00000034) TIMER2_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMER2_EOI  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER2_EOI_b;
  } ;
  __IM  uint8_t   RESERVED14;
  __IM  uint16_t  RESERVED15;
  
  union {
    __IOM uint8_t TIMER2_INT_STATUS;            /*!< (@ 0x00000038) TIMER2_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMER2_INT_STATUS : 1;      /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER2_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED16;
  __IM  uint16_t  RESERVED17;
  
  union {
    __IOM uint16_t TIMER3_LOAD_COUNT;           /*!< (@ 0x0000003C) TIMER3_LOAD_COUNT                                          */
    
    struct {
      __IOM uint16_t TIMER3_LOAD_COUNT : 16;    /*!< [15..0] nan                                                               */
    } TIMER3_LOAD_COUNT_b;
  } ;
  __IM  uint16_t  RESERVED18;
  
  union {
    __IOM uint16_t TIMER3_CURRENT_VALUE;        /*!< (@ 0x00000040) TIMER3_CURRENT_VALUE                                       */
    
    struct {
      __IM  uint16_t TIMER3_CURRENT_VALUE : 16; /*!< [15..0] nan                                                               */
    } TIMER3_CURRENT_VALUE_b;
  } ;
  __IM  uint16_t  RESERVED19;
  
  union {
    __IOM uint32_t TIMER3_CONTROL_REG;          /*!< (@ 0x00000044) TIMER3_CONTROL_REG                                         */
    
    struct {
      __IOM uint32_t TIMER3_ENABLE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint32_t TIMER3_MODE : 1;           /*!< [1..1] nan                                                                */
      __IOM uint32_t TIMER3_INTERRUPT_MASK : 1; /*!< [2..2] nan                                                                */
      __IOM uint32_t TIMER3_PWM : 1;            /*!< [3..3] nan                                                                */
      __IM  uint32_t TIMER3_0N100PWM_EN : 1;    /*!< [4..4] nan                                                                */
      __IOM uint32_t TIMER3_DT_EN : 1;          /*!< [5..5] nan                                                                */
      __IOM uint32_t TIMER3_PWM_INIT_N : 1;     /*!< [6..6] nan                                                                */
      __IOM uint32_t TIMER3_PWM_INIT_P : 1;     /*!< [7..7] nan                                                                */
      __IOM uint32_t TIMER3_DT_LEN : 8;         /*!< [15..8] nan                                                               */
      __IOM uint32_t TIMER3_PWM_POL_N : 1;      /*!< [16..16] nan                                                              */
      __IOM uint32_t TIMER3_PWM_POL_P : 1;      /*!< [17..17] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } TIMER3_CONTROL_REG_b;
  } ;
  
  union {
    __IOM uint8_t TIMER3_EOI;                   /*!< (@ 0x00000048) TIMER3_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMER3_EOI  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER3_EOI_b;
  } ;
  __IM  uint8_t   RESERVED20;
  __IM  uint16_t  RESERVED21;
  
  union {
    __IOM uint8_t TIMER3_INT_STATUS;            /*!< (@ 0x0000004C) TIMER3_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMER3_INT_STATUS : 1;      /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER3_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED22;
  __IM  uint16_t  RESERVED23;
  
  union {
    __IOM uint16_t TIMER4_LOAD_COUNT;           /*!< (@ 0x00000050) TIMER4_LOAD_COUNT                                          */
    
    struct {
      __IOM uint16_t TIMER4_LOAD_COUNT : 16;    /*!< [15..0] nan                                                               */
    } TIMER4_LOAD_COUNT_b;
  } ;
  __IM  uint16_t  RESERVED24;
  
  union {
    __IOM uint16_t TIMER4_CURRENT_VALUE;        /*!< (@ 0x00000054) TIMER4_CURRENT_VALUE                                       */
    
    struct {
      __IM  uint16_t TIMER4_CURRENT_VALUE : 16; /*!< [15..0] nan                                                               */
    } TIMER4_CURRENT_VALUE_b;
  } ;
  __IM  uint16_t  RESERVED25;
  
  union {
    __IOM uint32_t TIMER4_CONTROL_REG;          /*!< (@ 0x00000058) TIMER4_CONTROL_REG                                         */
    
    struct {
      __IOM uint32_t TIMER4_ENABLE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint32_t TIMER4_MODE : 1;           /*!< [1..1] nan                                                                */
      __IOM uint32_t TIMER4_INTERRUPT_MASK : 1; /*!< [2..2] nan                                                                */
      __IOM uint32_t TIMER4_PWM : 1;            /*!< [3..3] nan                                                                */
      __IM  uint32_t TIMER4_0N100PWM_EN : 1;    /*!< [4..4] nan                                                                */
      __IOM uint32_t TIMER4_DT_EN : 1;          /*!< [5..5] nan                                                                */
      __IOM uint32_t TIMER4_PWM_INIT_N : 1;     /*!< [6..6] nan                                                                */
      __IOM uint32_t TIMER4_PWM_INIT_P : 1;     /*!< [7..7] nan                                                                */
      __IOM uint32_t TIMER4_DT_LEN : 8;         /*!< [15..8] nan                                                               */
      __IOM uint32_t TIMER4_PWM_POL_N : 1;      /*!< [16..16] nan                                                              */
      __IOM uint32_t TIMER4_PWM_POL_P : 1;      /*!< [17..17] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } TIMER4_CONTROL_REG_b;
  } ;
  
  union {
    __IOM uint8_t TIMER4_EOI;                   /*!< (@ 0x0000005C) TIMER4_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMER4_EOI  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER4_EOI_b;
  } ;
  __IM  uint8_t   RESERVED26;
  __IM  uint16_t  RESERVED27;
  
  union {
    __IOM uint8_t TIMER4_INT_STATUS;            /*!< (@ 0x00000060) TIMER4_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMER4_INT_STATUS : 1;      /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER4_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED28;
  __IM  uint16_t  RESERVED29;
  
  union {
    __IOM uint16_t TIMER5_LOAD_COUNT;           /*!< (@ 0x00000064) TIMER5_LOAD_COUNT                                          */
    
    struct {
      __IOM uint16_t TIMER5_LOAD_COUNT : 16;    /*!< [15..0] nan                                                               */
    } TIMER5_LOAD_COUNT_b;
  } ;
  __IM  uint16_t  RESERVED30;
  
  union {
    __IOM uint16_t TIMER5_CURRENT_VALUE;        /*!< (@ 0x00000068) TIMER5_CURRENT_VALUE                                       */
    
    struct {
      __IM  uint16_t TIMER5_CURRENT_VALUE : 16; /*!< [15..0] nan                                                               */
    } TIMER5_CURRENT_VALUE_b;
  } ;
  __IM  uint16_t  RESERVED31;
  
  union {
    __IOM uint32_t TIMER5_CONTROL_REG;          /*!< (@ 0x0000006C) TIMER5_CONTROL_REG                                         */
    
    struct {
      __IOM uint32_t TIMER5_ENABLE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint32_t TIMER5_MODE : 1;           /*!< [1..1] nan                                                                */
      __IOM uint32_t TIMER5_INTERRUPT_MASK : 1; /*!< [2..2] nan                                                                */
      __IOM uint32_t TIMER5_PWM : 1;            /*!< [3..3] nan                                                                */
      __IM  uint32_t TIMER5_0N100PWM_EN : 1;    /*!< [4..4] nan                                                                */
      __IOM uint32_t TIMER5_DT_EN : 1;          /*!< [5..5] nan                                                                */
      __IOM uint32_t TIMER5_PWM_INIT_N : 1;     /*!< [6..6] nan                                                                */
      __IOM uint32_t TIMER5_PWM_INIT_P : 1;     /*!< [7..7] nan                                                                */
      __IOM uint32_t TIMER5_DT_LEN : 8;         /*!< [15..8] nan                                                               */
      __IOM uint32_t TIMER5_PWM_POL_N : 1;      /*!< [16..16] nan                                                              */
      __IOM uint32_t TIMER5_PWM_POL_P : 1;      /*!< [17..17] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } TIMER5_CONTROL_REG_b;
  } ;
  
  union {
    __IOM uint8_t TIMER5_EOI;                   /*!< (@ 0x00000070) TIMER5_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMER5_EOI  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER5_EOI_b;
  } ;
  __IM  uint8_t   RESERVED32;
  __IM  uint16_t  RESERVED33;
  
  union {
    __IOM uint8_t TIMER5_INT_STATUS;            /*!< (@ 0x00000074) TIMER5_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMER5_INT_STATUS : 1;      /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER5_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED34;
  __IM  uint16_t  RESERVED35;
  
  union {
    __IOM uint16_t TIMER6_LOAD_COUNT;           /*!< (@ 0x00000078) TIMER6_LOAD_COUNT                                          */
    
    struct {
      __IOM uint16_t TIMER6_LOAD_COUNT : 16;    /*!< [15..0] nan                                                               */
    } TIMER6_LOAD_COUNT_b;
  } ;
  __IM  uint16_t  RESERVED36;
  
  union {
    __IOM uint16_t TIMER6_CURRENT_VALUE;        /*!< (@ 0x0000007C) TIMER6_CURRENT_VALUE                                       */
    
    struct {
      __IM  uint16_t TIMER6_CURRENT_VALUE : 16; /*!< [15..0] nan                                                               */
    } TIMER6_CURRENT_VALUE_b;
  } ;
  __IM  uint16_t  RESERVED37;
  
  union {
    __IOM uint32_t TIMER6_CONTROL_REG;          /*!< (@ 0x00000080) TIMER6_CONTROL_REG                                         */
    
    struct {
      __IOM uint32_t TIMER6_ENABLE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint32_t TIMER6_MODE : 1;           /*!< [1..1] nan                                                                */
      __IOM uint32_t TIMER6_INTERRUPT_MASK : 1; /*!< [2..2] nan                                                                */
      __IOM uint32_t TIMER6_PWM : 1;            /*!< [3..3] nan                                                                */
      __IM  uint32_t TIMER6_0N100PWM_EN : 1;    /*!< [4..4] nan                                                                */
      __IOM uint32_t TIMER6_DT_EN : 1;          /*!< [5..5] nan                                                                */
      __IOM uint32_t TIMER6_PWM_INIT_N : 1;     /*!< [6..6] nan                                                                */
      __IOM uint32_t TIMER6_PWM_INIT_P : 1;     /*!< [7..7] nan                                                                */
      __IOM uint32_t TIMER6_DT_LEN : 8;         /*!< [15..8] nan                                                               */
      __IOM uint32_t TIMER6_PWM_POL_N : 1;      /*!< [16..16] nan                                                              */
      __IOM uint32_t TIMER6_PWM_POL_P : 1;      /*!< [17..17] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } TIMER6_CONTROL_REG_b;
  } ;
  
  union {
    __IOM uint8_t TIMER6_EOI;                   /*!< (@ 0x00000084) TIMER6_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMER6_EOI  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER6_EOI_b;
  } ;
  __IM  uint8_t   RESERVED38;
  __IM  uint16_t  RESERVED39;
  
  union {
    __IOM uint8_t TIMER6_INT_STATUS;            /*!< (@ 0x00000088) TIMER6_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMER6_INT_STATUS : 1;      /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER6_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED40;
  __IM  uint16_t  RESERVED41;
  
  union {
    __IOM uint16_t TIMER7_LOAD_COUNT;           /*!< (@ 0x0000008C) TIMER7_LOAD_COUNT                                          */
    
    struct {
      __IOM uint16_t TIMER7_LOAD_COUNT : 16;    /*!< [15..0] nan                                                               */
    } TIMER7_LOAD_COUNT_b;
  } ;
  __IM  uint16_t  RESERVED42;
  
  union {
    __IOM uint16_t TIMER7_CURRENT_VALUE;        /*!< (@ 0x00000090) TIMER7_CURRENT_VALUE                                       */
    
    struct {
      __IM  uint16_t TIMER7_CURRENT_VALUE : 16; /*!< [15..0] nan                                                               */
    } TIMER7_CURRENT_VALUE_b;
  } ;
  __IM  uint16_t  RESERVED43;
  
  union {
    __IOM uint32_t TIMER7_CONTROL_REG;          /*!< (@ 0x00000094) TIMER7_CONTROL_REG                                         */
    
    struct {
      __IOM uint32_t TIMER7_ENABLE : 1;         /*!< [0..0] nan                                                                */
      __IOM uint32_t TIMER7_MODE : 1;           /*!< [1..1] nan                                                                */
      __IOM uint32_t TIMER7_INTERRUPT_MASK : 1; /*!< [2..2] nan                                                                */
      __IOM uint32_t TIMER7_PWM : 1;            /*!< [3..3] nan                                                                */
      __IM  uint32_t TIMER7_0N100PWM_EN : 1;    /*!< [4..4] nan                                                                */
      __IOM uint32_t TIMER7_DT_EN : 1;          /*!< [5..5] nan                                                                */
      __IOM uint32_t TIMER7_PWM_INIT_N : 1;     /*!< [6..6] nan                                                                */
      __IOM uint32_t TIMER7_PWM_INIT_P : 1;     /*!< [7..7] nan                                                                */
      __IOM uint32_t TIMER7_DT_LEN : 8;         /*!< [15..8] nan                                                               */
      __IOM uint32_t TIMER7_PWM_POL_N : 1;      /*!< [16..16] nan                                                              */
      __IOM uint32_t TIMER7_PWM_POL_P : 1;      /*!< [17..17] nan                                                              */
            uint32_t            : 6;
      __IOM uint32_t RESERVE    : 8;            /*!< [31..24] nan                                                              */
    } TIMER7_CONTROL_REG_b;
  } ;
  
  union {
    __IOM uint8_t TIMER7_EOI;                   /*!< (@ 0x00000098) TIMER7_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMER7_EOI  : 1;            /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER7_EOI_b;
  } ;
  __IM  uint8_t   RESERVED44;
  __IM  uint16_t  RESERVED45;
  
  union {
    __IOM uint8_t TIMER7_INT_STATUS;            /*!< (@ 0x0000009C) TIMER7_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMER7_INT_STATUS : 1;      /*!< [0..0] nan                                                                */
            uint8_t             : 7;
    } TIMER7_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED46;
  __IM  uint16_t  RESERVED47;
  
  union {
    __IOM uint8_t TIMERS_INT_STATUS;            /*!< (@ 0x000000A0) TIMERS_INT_STATUS                                          */
    
    struct {
      __IM  uint8_t TIMERS_INT_STATUS : 8;      /*!< [7..0] nan                                                                */
    } TIMERS_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED48;
  __IM  uint16_t  RESERVED49;
  
  union {
    __IOM uint8_t TIMERS_EOI;                   /*!< (@ 0x000000A4) TIMERS_EOI                                                 */
    
    struct {
      __IM  uint8_t TIMERS_EOI  : 8;            /*!< [7..0] nan                                                                */
    } TIMERS_EOI_b;
  } ;
  __IM  uint8_t   RESERVED50;
  __IM  uint16_t  RESERVED51;
  
  union {
    __IOM uint8_t TIMERS_RAW_INT_STATUS;        /*!< (@ 0x000000A8) TIMERS_RAW_INT_STATUS                                      */
    
    struct {
      __IM  uint8_t TIMERS_RAW_INT_STATUS : 8;  /*!< [7..0] nan                                                                */
    } TIMERS_RAW_INT_STATUS_b;
  } ;
  __IM  uint8_t   RESERVED52;
  __IM  uint16_t  RESERVED53;
  __IM  uint32_t  RESERVED54;
  
  union {
    __IOM uint16_t TIMER0_LOAD_COUNT2;          /*!< (@ 0x000000B0) TIMER0_LOAD_COUNT2                                         */
    
    struct {
      __IOM uint16_t TIMER0_LOAD_COUNT2 : 16;   /*!< [15..0] nan                                                               */
    } TIMER0_LOAD_COUNT2_b;
  } ;
  __IM  uint16_t  RESERVED55;
  
  union {
    __IOM uint16_t TIMER1_LOAD_COUNT2;          /*!< (@ 0x000000B4) TIMER1_LOAD_COUNT2                                         */
    
    struct {
      __IOM uint16_t TIMER1_LOAD_COUNT2 : 16;   /*!< [15..0] nan                                                               */
    } TIMER1_LOAD_COUNT2_b;
  } ;
  __IM  uint16_t  RESERVED56;
  
  union {
    __IOM uint16_t TIMER2_LOAD_COUNT2;          /*!< (@ 0x000000B8) TIMER2_LOAD_COUNT2                                         */
    
    struct {
      __IOM uint16_t TIMER2_LOAD_COUNT2 : 16;   /*!< [15..0] nan                                                               */
    } TIMER2_LOAD_COUNT2_b;
  } ;
  __IM  uint16_t  RESERVED57;
  
  union {
    __IOM uint16_t TIMER3_LOAD_COUNT2;          /*!< (@ 0x000000BC) TIMER3_LOAD_COUNT2                                         */
    
    struct {
      __IOM uint16_t TIMER3_LOAD_COUNT2 : 16;   /*!< [15..0] nan                                                               */
    } TIMER3_LOAD_COUNT2_b;
  } ;
  __IM  uint16_t  RESERVED58;
  
  union {
    __IOM uint16_t TIMER4_LOAD_COUNT2;          /*!< (@ 0x000000C0) TIMER4_LOAD_COUNT2                                         */
    
    struct {
      __IOM uint16_t TIMER4_LOAD_COUNT2 : 16;   /*!< [15..0] nan                                                               */
    } TIMER4_LOAD_COUNT2_b;
  } ;
  __IM  uint16_t  RESERVED59;
  
  union {
    __IOM uint16_t TIMER5_LOAD_COUNT2;          /*!< (@ 0x000000C4) TIMER5_LOAD_COUNT2                                         */
    
    struct {
      __IOM uint16_t TIMER5_LOAD_COUNT2 : 16;   /*!< [15..0] nan                                                               */
    } TIMER5_LOAD_COUNT2_b;
  } ;
  __IM  uint16_t  RESERVED60;
  
  union {
    __IOM uint16_t TIMER6_LOAD_COUNT2;          /*!< (@ 0x000000C8) TIMER6_LOAD_COUNT2                                         */
    
    struct {
      __IOM uint16_t TIMER6_LOAD_COUNT2 : 16;   /*!< [15..0] nan                                                               */
    } TIMER6_LOAD_COUNT2_b;
  } ;
  __IM  uint16_t  RESERVED61;
  
  union {
    __IOM uint16_t TIMER7_LOAD_COUNT2;          /*!< (@ 0x000000CC) TIMER7_LOAD_COUNT2                                         */
    
    struct {
      __IOM uint16_t TIMER7_LOAD_COUNT2 : 16;   /*!< [15..0] nan                                                               */
    } TIMER7_LOAD_COUNT2_b;
  } ;
  __IM  uint16_t  RESERVED62;
} TIMER_Type;                                   /*!< Size = 208 (0xd0)                                                         */


/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define SYS_CTRL_BASE               0x40000000UL
#define GPIO_INOUT_BASE             0x40010010UL
#define GPIO_INTR_BASE              0x40010140UL
#define GPIO_ATF_BASE               0x40010200UL
#define QDEC_CTRL_BASE              0x40020000UL
#define QDEC_INTR_BASE              0x40020020UL
#define QDEC_X_AXIS_BASE            0x40020040UL
#define QDEC_Y_AXIS_BASE            0x40020060UL
#define QDEC_Z_AXIS_BASE            0x40020080UL
#define KEYSCAN_BASE                0x40021000UL
#define LEDC_CTRL_BASE              0x40022000UL
#define LEDC_CH0_BASE               0x40022080UL
#define LEDC_CH1_BASE               0x400220A0UL
#define GPADC_ANA_BASE              0x40040000UL
#define GPADC_DIG_BASE              0x40040060UL
#define AON_CTRL_BASE               0x40080000UL
#define FPGA_CTRL_BASE              0x40090000UL
#define FPGA_CTRL_AD9961_BASE       0x40090010UL
#define FPGA_CTRL_MAX2829_BASE      0x40090050UL
#define UART_BASE                   0x41001000UL
#define SPIM_BASE                   0x41003000UL
#define IIC_BASE                    0x41005000UL
#define SPIS_BASE                   0x41007000UL
#define TIMER_BASE                  0x41008000UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define SYS_CTRL                    ((SYS_CTRL_Type*)          SYS_CTRL_BASE)
#define GPIO_INOUT                  ((GPIO_INOUT_Type*)        GPIO_INOUT_BASE)
#define GPIO_INTR                   ((GPIO_INTR_Type*)         GPIO_INTR_BASE)
#define GPIO_ATF                    ((GPIO_ATF_Type*)          GPIO_ATF_BASE)
#define QDEC_CTRL                   ((QDEC_CTRL_Type*)         QDEC_CTRL_BASE)
#define QDEC_INTR                   ((QDEC_INTR_Type*)         QDEC_INTR_BASE)
#define QDEC_X_AXIS                 ((QDEC_X_AXIS_Type*)       QDEC_X_AXIS_BASE)
#define QDEC_Y_AXIS                 ((QDEC_Y_AXIS_Type*)       QDEC_Y_AXIS_BASE)
#define QDEC_Z_AXIS                 ((QDEC_Z_AXIS_Type*)       QDEC_Z_AXIS_BASE)
#define KEYSCAN                    ((KEYSCAN_Type*)            KEYSCAN_BASE)
#define LEDC_CTRL                  ((LEDC_CTRL_Type*)          LEDC_CTRL_BASE)
#define LEDC_CH0                   ((LEDC_CHANNEL_CTRL_Type*)  LEDC_CH0_BASE)
#define LEDC_CH1                   ((LEDC_CHANNEL_CTRL_Type*)  LEDC_CH1_BASE)
#define GPADC_ANA                   ((GPADC_ANA_Type*)         GPADC_ANA_BASE)
#define GPADC_DIG                   ((GPADC_DIG_Type*)         GPADC_DIG_BASE)
#define AON_CTRL                    ((AON_CTRL_Type*)          AON_CTRL_BASE)
#define UART                        ((UART_Type*)              UART_BASE)
#define SPIM                        ((SPIM_Type*)              SPIM_BASE)
#define IIC                         ((IIC_Type*)               IIC_BASE)
#define SPIS                        ((SPIS_Type*)              SPIS_BASE)
#define TIMER                       ((TIMER_Type*)             TIMER_BASE)

/** @} */ /* End of group Device_Peripheral_declaration */


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif


/* =========================================================================================================================== */
/* ================                                Pos/Mask Peripheral Section                                ================ */
/* =========================================================================================================================== */


/** @addtogroup PosMask_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                         SYS_CTRL                                          ================ */
/* =========================================================================================================================== */

/* =======================================================  REVISION  ======================================================== */
#define SYS_CTRL_REVISION_REVISION_Pos    (0UL)                     /*!< REVISION (Bit 0)                                      */
#define SYS_CTRL_REVISION_REVISION_Msk    (0xffffUL)                /*!< REVISION (Bitfield-Mask: 0xffff)                      */
/* =======================================================  SYS_RESET  ======================================================= */
#define SYS_CTRL_SYS_RESET_REG_SWRST_Pos  (0UL)                     /*!< REG_SWRST (Bit 0)                                     */
#define SYS_CTRL_SYS_RESET_REG_SWRST_Msk  (0xffffffffUL)            /*!< REG_SWRST (Bitfield-Mask: 0xffffffff)                 */
/* ======================================================  SYS_STATUS  ======================================================= */
#define SYS_CTRL_SYS_STATUS_CODE_CRC_FAIL_Pos (2UL)                 /*!< CODE_CRC_FAIL (Bit 2)                                 */
#define SYS_CTRL_SYS_STATUS_CODE_CRC_FAIL_Msk (0x4UL)               /*!< CODE_CRC_FAIL (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_SYS_STATUS_LPO_CLOCK_Pos (1UL)                     /*!< LPO_CLOCK (Bit 1)                                     */
#define SYS_CTRL_SYS_STATUS_LPO_CLOCK_Msk (0x2UL)                   /*!< LPO_CLOCK (Bitfield-Mask: 0x01)                       */
#define SYS_CTRL_SYS_STATUS_CRYSTAL_STABLE_Pos (0UL)                /*!< CRYSTAL_STABLE (Bit 0)                                */
#define SYS_CTRL_SYS_STATUS_CRYSTAL_STABLE_Msk (0x1UL)              /*!< CRYSTAL_STABLE (Bitfield-Mask: 0x01)                  */
/* ======================================================  LOCKUP_CTRL  ====================================================== */
#define SYS_CTRL_LOCKUP_CTRL_LOCKUP_RESET_CNT_Pos (8UL)             /*!< LOCKUP_RESET_CNT (Bit 8)                              */
#define SYS_CTRL_LOCKUP_CTRL_LOCKUP_RESET_CNT_Msk (0xff00UL)        /*!< LOCKUP_RESET_CNT (Bitfield-Mask: 0xff)                */
#define SYS_CTRL_LOCKUP_CTRL_MATRIX_WDATA_GATE_EN_Pos (3UL)         /*!< MATRIX_WDATA_GATE_EN (Bit 3)                          */
#define SYS_CTRL_LOCKUP_CTRL_MATRIX_WDATA_GATE_EN_Msk (0x8UL)       /*!< MATRIX_WDATA_GATE_EN (Bitfield-Mask: 0x01)            */
#define SYS_CTRL_LOCKUP_CTRL_MATRIX_BUS_GATE_EN_Pos (2UL)           /*!< MATRIX_BUS_GATE_EN (Bit 2)                            */
#define SYS_CTRL_LOCKUP_CTRL_MATRIX_BUS_GATE_EN_Msk (0x4UL)         /*!< MATRIX_BUS_GATE_EN (Bitfield-Mask: 0x01)              */
#define SYS_CTRL_LOCKUP_CTRL_LOCKUP_RESET_MODE_Pos (1UL)            /*!< LOCKUP_RESET_MODE (Bit 1)                             */
#define SYS_CTRL_LOCKUP_CTRL_LOCKUP_RESET_MODE_Msk (0x2UL)          /*!< LOCKUP_RESET_MODE (Bitfield-Mask: 0x01)               */
#define SYS_CTRL_LOCKUP_CTRL_LOCKUP_RESET_EN_Pos (0UL)              /*!< LOCKUP_RESET_EN (Bit 0)                               */
#define SYS_CTRL_LOCKUP_CTRL_LOCKUP_RESET_EN_Msk (0x1UL)            /*!< LOCKUP_RESET_EN (Bitfield-Mask: 0x01)                 */
/* ======================================================  SYS_CLKSEL  ======================================================= */
#define SYS_CTRL_SYS_CLKSEL_REG_LEDC_CLK_SEL_Pos (20UL)            /*!< REG_LEDC_CLK_SEL (Bit 20)                            */
#define SYS_CTRL_SYS_CLKSEL_REG_LEDC_CLK_SEL_Msk (0x300000UL)      /*!< REG_LEDC_CLK_SEL (Bitfield-Mask: 0x03)               */
#define SYS_CTRL_SYS_CLKSEL_REG_SPIS0_CLK_SEL_Pos (18UL)            /*!< REG_SPIS0_CLK_SEL (Bit 18)                            */
#define SYS_CTRL_SYS_CLKSEL_REG_SPIS0_CLK_SEL_Msk (0xc0000UL)       /*!< REG_SPIS0_CLK_SEL (Bitfield-Mask: 0x03)               */
#define SYS_CTRL_SYS_CLKSEL_REG_OTP_CLK_SEL_Pos (16UL)              /*!< REG_OTP_CLK_SEL (Bit 16)                              */
#define SYS_CTRL_SYS_CLKSEL_REG_OTP_CLK_SEL_Msk (0x30000UL)         /*!< REG_OTP_CLK_SEL (Bitfield-Mask: 0x03)                 */
#define SYS_CTRL_SYS_CLKSEL_REG_CAP_CLK_SEL_Pos (12UL)              /*!< REG_CAP_CLK_SEL (Bit 12)                              */
#define SYS_CTRL_SYS_CLKSEL_REG_CAP_CLK_SEL_Msk (0x7000UL)          /*!< REG_CAP_CLK_SEL (Bitfield-Mask: 0x07)                 */
#define SYS_CTRL_SYS_CLKSEL_REG_UART_CLK_SEL_Pos (10UL)             /*!< REG_UART_CLK_SEL (Bit 10)                             */
#define SYS_CTRL_SYS_CLKSEL_REG_UART_CLK_SEL_Msk (0xc00UL)          /*!< REG_UART_CLK_SEL (Bitfield-Mask: 0x03)                */
#define SYS_CTRL_SYS_CLKSEL_REG_CPU_CLK_SYSSEL_Pos (8UL)            /*!< REG_CPU_CLK_SYSSEL (Bit 8)                            */
#define SYS_CTRL_SYS_CLKSEL_REG_CPU_CLK_SYSSEL_Msk (0x300UL)        /*!< REG_CPU_CLK_SYSSEL (Bitfield-Mask: 0x03)              */
#define SYS_CTRL_SYS_CLKSEL_REG_CPU_CLK_SEL_Pos (4UL)               /*!< REG_CPU_CLK_SEL (Bit 4)                               */
#define SYS_CTRL_SYS_CLKSEL_REG_CPU_CLK_SEL_Msk (0x70UL)            /*!< REG_CPU_CLK_SEL (Bitfield-Mask: 0x07)                 */
#define SYS_CTRL_SYS_CLKSEL_REG_QSPI_CLK_SYSSEL_Pos (2UL)           /*!< REG_QSPI_CLK_SYSSEL (Bit 2)                           */
#define SYS_CTRL_SYS_CLKSEL_REG_QSPI_CLK_SYSSEL_Msk (0xcUL)         /*!< REG_QSPI_CLK_SYSSEL (Bitfield-Mask: 0x03)             */
#define SYS_CTRL_SYS_CLKSEL_REG_QSPI_CLK_SEL_Pos (0UL)              /*!< REG_QSPI_CLK_SEL (Bit 0)                              */
#define SYS_CTRL_SYS_CLKSEL_REG_QSPI_CLK_SEL_Msk (0x3UL)            /*!< REG_QSPI_CLK_SEL (Bitfield-Mask: 0x03)                */
#define SYS_CTRL_SYS_CLKSEL_RESERVE_Pos   (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define SYS_CTRL_SYS_CLKSEL_RESERVE_Msk   (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ===================================================  PWMTT_CLK_SYSSEL  ==================================================== */
#define SYS_CTRL_PWMTT_CLK_SYSSEL_REG_PWMTT_CLK_SYSSEL_Pos (0UL)    /*!< REG_PWMTT_CLK_SYSSEL (Bit 0)                          */
#define SYS_CTRL_PWMTT_CLK_SYSSEL_REG_PWMTT_CLK_SYSSEL_Msk (0xffffUL) /*!< REG_PWMTT_CLK_SYSSEL (Bitfield-Mask: 0xffff)        */
/* =====================================================  PWMTT_CLK_SEL  ===================================================== */
#define SYS_CTRL_PWMTT_CLK_SEL_REG_PWMTT_CLK_SEL_Pos (0UL)          /*!< REG_PWMTT_CLK_SEL (Bit 0)                             */
#define SYS_CTRL_PWMTT_CLK_SEL_REG_PWMTT_CLK_SEL_Msk (0xffffffffUL) /*!< REG_PWMTT_CLK_SEL (Bitfield-Mask: 0xffffffff)         */
/* ======================================================  PWM_OUT_SEL  ====================================================== */
#define SYS_CTRL_PWM_OUT_SEL_PWM_OUT_SEL_Pos (0UL)                  /*!< PWM_OUT_SEL (Bit 0)                                   */
#define SYS_CTRL_PWM_OUT_SEL_PWM_OUT_SEL_Msk (0x1UL)                /*!< PWM_OUT_SEL (Bitfield-Mask: 0x01)                     */
/* =======================================================  BIST_CTRL  ======================================================= */
#define SYS_CTRL_BIST_CTRL_BIST_TMR_EN_Pos (4UL)                    /*!< BIST_TMR_EN (Bit 4)                                   */
#define SYS_CTRL_BIST_CTRL_BIST_TMR_EN_Msk (0x10UL)                 /*!< BIST_TMR_EN (Bitfield-Mask: 0x01)                     */
#define SYS_CTRL_BIST_CTRL_BIST_RST_EN_Pos (3UL)                    /*!< BIST_RST_EN (Bit 3)                                   */
#define SYS_CTRL_BIST_CTRL_BIST_RST_EN_Msk (0x8UL)                  /*!< BIST_RST_EN (Bitfield-Mask: 0x01)                     */
#define SYS_CTRL_BIST_CTRL_BIST_MUX_MODE_Pos (2UL)                  /*!< BIST_MUX_MODE (Bit 2)                                 */
#define SYS_CTRL_BIST_CTRL_BIST_MUX_MODE_Msk (0x4UL)                /*!< BIST_MUX_MODE (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_BIST_CTRL_BIST_EN_Pos    (1UL)                     /*!< BIST_EN (Bit 1)                                       */
#define SYS_CTRL_BIST_CTRL_BIST_EN_Msk    (0x2UL)                   /*!< BIST_EN (Bitfield-Mask: 0x01)                         */
#define SYS_CTRL_BIST_CTRL_BIST_MODE_Pos  (0UL)                     /*!< BIST_MODE (Bit 0)                                     */
#define SYS_CTRL_BIST_CTRL_BIST_MODE_Msk  (0x1UL)                   /*!< BIST_MODE (Bitfield-Mask: 0x01)                       */
/* ======================================================  BIST_STATE  ======================================================= */
#define SYS_CTRL_BIST_STATE_BIST_FAIL_Pos (16UL)                    /*!< BIST_FAIL (Bit 16)                                    */
#define SYS_CTRL_BIST_STATE_BIST_FAIL_Msk (0xffff0000UL)            /*!< BIST_FAIL (Bitfield-Mask: 0xffff)                     */
#define SYS_CTRL_BIST_STATE_BIST_DONE_Pos (0UL)                     /*!< BIST_DONE (Bit 0)                                     */
#define SYS_CTRL_BIST_STATE_BIST_DONE_Msk (0xffffUL)                /*!< BIST_DONE (Bitfield-Mask: 0xffff)                     */
/* ===================================================  BIST_STATE_NORST  ==================================================== */
#define SYS_CTRL_BIST_STATE_NORST_BIST_FAIL_NORST_Pos (16UL)        /*!< BIST_FAIL_NORST (Bit 16)                              */
#define SYS_CTRL_BIST_STATE_NORST_BIST_FAIL_NORST_Msk (0xffff0000UL) /*!< BIST_FAIL_NORST (Bitfield-Mask: 0xffff)              */
#define SYS_CTRL_BIST_STATE_NORST_BIST_DONE_NORST_Pos (0UL)         /*!< BIST_DONE_NORST (Bit 0)                               */
#define SYS_CTRL_BIST_STATE_NORST_BIST_DONE_NORST_Msk (0x1UL)       /*!< BIST_DONE_NORST (Bitfield-Mask: 0x01)                 */
/* =======================================================  OTP_CTRL  ======================================================== */
#define SYS_CTRL_OTP_CTRL_OTP_CTRL_Pos    (0UL)                     /*!< OTP_CTRL (Bit 0)                                      */
#define SYS_CTRL_OTP_CTRL_OTP_CTRL_Msk    (0x7ffUL)                 /*!< OTP_CTRL (Bitfield-Mask: 0x7ff)                       */
/* =======================================================  OTP_PADDR  ======================================================= */
#define SYS_CTRL_OTP_PADDR_OTP_PA_EN_Pos  (20UL)                    /*!< OTP_PA_EN (Bit 20)                                    */
#define SYS_CTRL_OTP_PADDR_OTP_PA_EN_Msk  (0x100000UL)              /*!< OTP_PA_EN (Bitfield-Mask: 0x01)                       */
#define SYS_CTRL_OTP_PADDR_OTP_PA_Pos     (8UL)                     /*!< OTP_PA (Bit 8)                                        */
#define SYS_CTRL_OTP_PADDR_OTP_PA_Msk     (0xfff00UL)               /*!< OTP_PA (Bitfield-Mask: 0xfff)                         */
#define SYS_CTRL_OTP_PADDR_OTP_PAIO_Pos   (0UL)                     /*!< OTP_PAIO (Bit 0)                                      */
#define SYS_CTRL_OTP_PADDR_OTP_PAIO_Msk   (0x3fUL)                  /*!< OTP_PAIO (Bitfield-Mask: 0x3f)                        */
#define SYS_CTRL_OTP_PADDR_RESERVE_Pos    (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define SYS_CTRL_OTP_PADDR_RESERVE_Msk    (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =======================================================  OTP_PDIN  ======================================================== */
#define SYS_CTRL_OTP_PDIN_OTP_PDIN_Pos    (0UL)                     /*!< OTP_PDIN (Bit 0)                                      */
#define SYS_CTRL_OTP_PDIN_OTP_PDIN_Msk    (0xffffffffUL)            /*!< OTP_PDIN (Bitfield-Mask: 0xffffffff)                  */
/* =======================================================  OTP_PDOUT  ======================================================= */
#define SYS_CTRL_OTP_PDOUT_OTP_PDOUT_Pos  (0UL)                     /*!< OTP_PDOUT (Bit 0)                                     */
#define SYS_CTRL_OTP_PDOUT_OTP_PDOUT_Msk  (0xffffffffUL)            /*!< OTP_PDOUT (Bitfield-Mask: 0xffffffff)                 */
/* =====================================================  OTP_PRG_STATE  ===================================================== */
#define SYS_CTRL_OTP_PRG_STATE_OTP_PRG_STATE_Pos (0UL)              /*!< OTP_PRG_STATE (Bit 0)                                 */
#define SYS_CTRL_OTP_PRG_STATE_OTP_PRG_STATE_Msk (0x7UL)            /*!< OTP_PRG_STATE (Bitfield-Mask: 0x07)                   */
/* =====================================================  OTP_PRG_CFG0  ====================================================== */
#define SYS_CTRL_OTP_PRG_CFG0_OTP_TPPH_Pos (24UL)                   /*!< OTP_TPPH (Bit 24)                                     */
#define SYS_CTRL_OTP_PRG_CFG0_OTP_TPPH_Msk (0x1f000000UL)           /*!< OTP_TPPH (Bitfield-Mask: 0x1f)                        */
#define SYS_CTRL_OTP_PRG_CFG0_OTP_TPPS_Pos (16UL)                   /*!< OTP_TPPS (Bit 16)                                     */
#define SYS_CTRL_OTP_PRG_CFG0_OTP_TPPS_Msk (0x1f0000UL)             /*!< OTP_TPPS (Bitfield-Mask: 0x1f)                        */
#define SYS_CTRL_OTP_PRG_CFG0_OTP_TCSH_Pos (8UL)                    /*!< OTP_TCSH (Bit 8)                                      */
#define SYS_CTRL_OTP_PRG_CFG0_OTP_TCSH_Msk (0xf00UL)                /*!< OTP_TCSH (Bitfield-Mask: 0x0f)                        */
#define SYS_CTRL_OTP_PRG_CFG0_OTP_TCSP_Pos (0UL)                    /*!< OTP_TCSP (Bit 0)                                      */
#define SYS_CTRL_OTP_PRG_CFG0_OTP_TCSP_Msk (0x3fUL)                 /*!< OTP_TCSP (Bitfield-Mask: 0x3f)                        */
/* =====================================================  OTP_PRG_CFG1  ====================================================== */
#define SYS_CTRL_OTP_PRG_CFG1_OTP_PWE_MODE_Pos (24UL)               /*!< OTP_PWE_MODE (Bit 24)                                 */
#define SYS_CTRL_OTP_PRG_CFG1_OTP_PWE_MODE_Msk (0x1000000UL)        /*!< OTP_PWE_MODE (Bitfield-Mask: 0x01)                    */
#define SYS_CTRL_OTP_PRG_CFG1_OTP_PRG_PULSE_Pos (16UL)              /*!< OTP_PRG_PULSE (Bit 16)                                */
#define SYS_CTRL_OTP_PRG_CFG1_OTP_PRG_PULSE_Msk (0x3f0000UL)        /*!< OTP_PRG_PULSE (Bitfield-Mask: 0x3f)                   */
#define SYS_CTRL_OTP_PRG_CFG1_OTP_TPWI_Pos (8UL)                    /*!< OTP_TPWI (Bit 8)                                      */
#define SYS_CTRL_OTP_PRG_CFG1_OTP_TPWI_Msk (0xf00UL)                /*!< OTP_TPWI (Bitfield-Mask: 0x0f)                        */
#define SYS_CTRL_OTP_PRG_CFG1_OTP_TPW_Pos (0UL)                     /*!< OTP_TPW (Bit 0)                                       */
#define SYS_CTRL_OTP_PRG_CFG1_OTP_TPW_Msk (0x3fUL)                  /*!< OTP_TPW (Bitfield-Mask: 0x3f)                         */
/* ======================================================  CLKCAL_CTRL  ====================================================== */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_INT_Pos (5UL)                   /*!< CLKCAL_INT (Bit 5)                                    */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_INT_Msk (0x20UL)                /*!< CLKCAL_INT (Bitfield-Mask: 0x01)                      */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_FINISH_Pos (4UL)                /*!< CLKCAL_FINISH (Bit 4)                                 */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_FINISH_Msk (0x10UL)             /*!< CLKCAL_FINISH (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_INT_CLR_Pos (3UL)               /*!< CLKCAL_INT_CLR (Bit 3)                                */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_INT_CLR_Msk (0x8UL)             /*!< CLKCAL_INT_CLR (Bitfield-Mask: 0x01)                  */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_INT_EN_Pos (2UL)                /*!< CLKCAL_INT_EN (Bit 2)                                 */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_INT_EN_Msk (0x4UL)              /*!< CLKCAL_INT_EN (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_RESET_Pos (1UL)                 /*!< CLKCAL_RESET (Bit 1)                                  */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_RESET_Msk (0x2UL)               /*!< CLKCAL_RESET (Bitfield-Mask: 0x01)                    */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_ENABLE_Pos (0UL)                /*!< CLKCAL_ENABLE (Bit 0)                                 */
#define SYS_CTRL_CLKCAL_CTRL_CLKCAL_ENABLE_Msk (0x1UL)              /*!< CLKCAL_ENABLE (Bitfield-Mask: 0x01)                   */
/* =====================================================  CLKCAL_CLKSEL  ===================================================== */
#define SYS_CTRL_CLKCAL_CLKSEL_CLKCAL_CLK1_SEL_Pos (8UL)            /*!< CLKCAL_CLK1_SEL (Bit 8)                               */
#define SYS_CTRL_CLKCAL_CLKSEL_CLKCAL_CLK1_SEL_Msk (0x1f00UL)       /*!< CLKCAL_CLK1_SEL (Bitfield-Mask: 0x1f)                 */
#define SYS_CTRL_CLKCAL_CLKSEL_CLKCAL_CLK0_SEL_Pos (0UL)            /*!< CLKCAL_CLK0_SEL (Bit 0)                               */
#define SYS_CTRL_CLKCAL_CLKSEL_CLKCAL_CLK0_SEL_Msk (0x1fUL)         /*!< CLKCAL_CLK0_SEL (Bitfield-Mask: 0x1f)                 */
/* ======================================================  CLKCAL_CNT0  ====================================================== */
#define SYS_CTRL_CLKCAL_CNT0_CLKCAL_CNT0_Pos (0UL)                  /*!< CLKCAL_CNT0 (Bit 0)                                   */
#define SYS_CTRL_CLKCAL_CNT0_CLKCAL_CNT0_Msk (0xffffffffUL)         /*!< CLKCAL_CNT0 (Bitfield-Mask: 0xffffffff)               */
/* ======================================================  CLKCAL_CNT1  ====================================================== */
#define SYS_CTRL_CLKCAL_CNT1_CLKCAL_CNT1_Pos (0UL)                  /*!< CLKCAL_CNT1 (Bit 0)                                   */
#define SYS_CTRL_CLKCAL_CNT1_CLKCAL_CNT1_Msk (0xffffffffUL)         /*!< CLKCAL_CNT1 (Bitfield-Mask: 0xffffffff)               */
/* ======================================================  SPIS0_CTRL  ======================================================= */
#define SYS_CTRL_SPIS0_CTRL_SPIS0_NCS_FORCE_VAL_Pos (1UL)           /*!< SPIS0_NCS_FORCE_VAL (Bit 1)                           */
#define SYS_CTRL_SPIS0_CTRL_SPIS0_NCS_FORCE_VAL_Msk (0x2UL)         /*!< SPIS0_NCS_FORCE_VAL (Bitfield-Mask: 0x01)             */
#define SYS_CTRL_SPIS0_CTRL_SPIS0_NCS_FORCE_EN_Pos (0UL)            /*!< SPIS0_NCS_FORCE_EN (Bit 0)                            */
#define SYS_CTRL_SPIS0_CTRL_SPIS0_NCS_FORCE_EN_Msk (0x1UL)          /*!< SPIS0_NCS_FORCE_EN (Bitfield-Mask: 0x01)              */
/* ========================================================  AON_RTC  ======================================================== */
#define SYS_CTRL_AON_RTC_AON_RTC_Pos      (0UL)                     /*!< AON_RTC (Bit 0)                                       */
#define SYS_CTRL_AON_RTC_AON_RTC_Msk      (0xffffffffUL)            /*!< AON_RTC (Bitfield-Mask: 0xffffffff)                   */
/* ======================================================  AON_RTC_TO  ======================================================= */
#define SYS_CTRL_AON_RTC_TO_AON_RTC_TO_Pos (0UL)                    /*!< AON_RTC_TO (Bit 0)                                    */
#define SYS_CTRL_AON_RTC_TO_AON_RTC_TO_Msk (0xffffffffUL)           /*!< AON_RTC_TO (Bitfield-Mask: 0xffffffff)                */
/* ======================================================  AON_RTC_IRQ  ====================================================== */
#define SYS_CTRL_AON_RTC_IRQ_AON_RTC_OVFL_IS_Pos (9UL)              /*!< AON_RTC_OVFL_IS (Bit 9)                               */
#define SYS_CTRL_AON_RTC_IRQ_AON_RTC_OVFL_IS_Msk (0x200UL)          /*!< AON_RTC_OVFL_IS (Bitfield-Mask: 0x01)                 */
#define SYS_CTRL_AON_RTC_IRQ_AON_RTC_TO_IS_Pos (8UL)                /*!< AON_RTC_TO_IS (Bit 8)                                 */
#define SYS_CTRL_AON_RTC_IRQ_AON_RTC_TO_IS_Msk (0x100UL)            /*!< AON_RTC_TO_IS (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_AON_RTC_IRQ_AON_RTC_OVFL_IE_Pos (1UL)              /*!< AON_RTC_OVFL_IE (Bit 1)                               */
#define SYS_CTRL_AON_RTC_IRQ_AON_RTC_OVFL_IE_Msk (0x2UL)            /*!< AON_RTC_OVFL_IE (Bitfield-Mask: 0x01)                 */
#define SYS_CTRL_AON_RTC_IRQ_AON_RTC_TO_IE_Pos (0UL)                /*!< AON_RTC_TO_IE (Bit 0)                                 */
#define SYS_CTRL_AON_RTC_IRQ_AON_RTC_TO_IE_Msk (0x1UL)              /*!< AON_RTC_TO_IE (Bitfield-Mask: 0x01)                   */
/* =====================================================  LVD_CTRL_DIG  ====================================================== */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_FALL_STAT_Pos (27UL)              /*!< LVD_FALL_STAT (Bit 27)                                */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_FALL_STAT_Msk (0x8000000UL)       /*!< LVD_FALL_STAT (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_RISE_STAT_Pos (26UL)              /*!< LVD_RISE_STAT (Bit 26)                                */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_RISE_STAT_Msk (0x4000000UL)       /*!< LVD_RISE_STAT (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_LOW_STAT_Pos (25UL)               /*!< LVD_LOW_STAT (Bit 25)                                 */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_LOW_STAT_Msk (0x2000000UL)        /*!< LVD_LOW_STAT (Bitfield-Mask: 0x01)                    */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_HIGH_STAT_Pos (24UL)              /*!< LVD_HIGH_STAT (Bit 24)                                */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_HIGH_STAT_Msk (0x1000000UL)       /*!< LVD_HIGH_STAT (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_FALL_EN_Pos (19UL)                /*!< LVD_FALL_EN (Bit 19)                                  */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_FALL_EN_Msk (0x80000UL)           /*!< LVD_FALL_EN (Bitfield-Mask: 0x01)                     */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_RISE_EN_Pos (18UL)                /*!< LVD_RISE_EN (Bit 18)                                  */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_RISE_EN_Msk (0x40000UL)           /*!< LVD_RISE_EN (Bitfield-Mask: 0x01)                     */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_LOW_EN_Pos (17UL)                 /*!< LVD_LOW_EN (Bit 17)                                   */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_LOW_EN_Msk (0x20000UL)            /*!< LVD_LOW_EN (Bitfield-Mask: 0x01)                      */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_HIGH_EN_Pos (16UL)                /*!< LVD_HIGH_EN (Bit 16)                                  */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_HIGH_EN_Msk (0x10000UL)           /*!< LVD_HIGH_EN (Bitfield-Mask: 0x01)                     */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_FILT_WIN_Pos (8UL)                /*!< LVD_FILT_WIN (Bit 8)                                  */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_FILT_WIN_Msk (0x1f00UL)           /*!< LVD_FILT_WIN (Bitfield-Mask: 0x1f)                    */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_PIN_FILT_Pos (7UL)                /*!< LVD_PIN_FILT (Bit 7)                                  */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_PIN_FILT_Msk (0x80UL)             /*!< LVD_PIN_FILT (Bitfield-Mask: 0x01)                    */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_PIN_RAW_Pos (6UL)                 /*!< LVD_PIN_RAW (Bit 6)                                   */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_PIN_RAW_Msk (0x40UL)              /*!< LVD_PIN_RAW (Bitfield-Mask: 0x01)                     */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_STAT_CLR_Pos (4UL)                /*!< LVD_STAT_CLR (Bit 4)                                  */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_STAT_CLR_Msk (0x10UL)             /*!< LVD_STAT_CLR (Bitfield-Mask: 0x01)                    */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_FILT_EN_Pos (3UL)                 /*!< LVD_FILT_EN (Bit 3)                                   */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_FILT_EN_Msk (0x8UL)               /*!< LVD_FILT_EN (Bitfield-Mask: 0x01)                     */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_INT_EN_Pos (2UL)                  /*!< LVD_INT_EN (Bit 2)                                    */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_INT_EN_Msk (0x4UL)                /*!< LVD_INT_EN (Bitfield-Mask: 0x01)                      */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_RST_EN_Pos (1UL)                  /*!< LVD_RST_EN (Bit 1)                                    */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_RST_EN_Msk (0x2UL)                /*!< LVD_RST_EN (Bitfield-Mask: 0x01)                      */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_EN_Pos  (0UL)                     /*!< LVD_EN (Bit 0)                                        */
#define SYS_CTRL_LVD_CTRL_DIG_LVD_EN_Msk  (0x1UL)                   /*!< LVD_EN (Bitfield-Mask: 0x01)                          */
/* =====================================================  LVD_CTRL_ANA  ====================================================== */
#define SYS_CTRL_LVD_CTRL_ANA_DA_LVD_EN_Pos (8UL)                   /*!< DA_LVD_EN (Bit 8)                                     */
#define SYS_CTRL_LVD_CTRL_ANA_DA_LVD_EN_Msk (0x100UL)               /*!< DA_LVD_EN (Bitfield-Mask: 0x01)                       */
#define SYS_CTRL_LVD_CTRL_ANA_DA_LVD_SEL_Pos (6UL)                  /*!< DA_LVD_SEL (Bit 6)                                    */
#define SYS_CTRL_LVD_CTRL_ANA_DA_LVD_SEL_Msk (0xc0UL)               /*!< DA_LVD_SEL (Bitfield-Mask: 0x03)                      */
#define SYS_CTRL_LVD_CTRL_ANA_RG_LVD_VTHC_Pos (0UL)                 /*!< RG_LVD_VTHC (Bit 0)                                   */
#define SYS_CTRL_LVD_CTRL_ANA_RG_LVD_VTHC_Msk (0x3fUL)              /*!< RG_LVD_VTHC (Bitfield-Mask: 0x3f)                     */
/* ========================================================  WDT_SET  ======================================================== */
#define SYS_CTRL_WDT_SET_WDT_CNT_Pos      (0UL)                     /*!< WDT_CNT (Bit 0)                                       */
#define SYS_CTRL_WDT_SET_WDT_CNT_Msk      (0xffUL)                  /*!< WDT_CNT (Bitfield-Mask: 0xff)                         */
/* ========================================================  WDT_CFG  ======================================================== */
#define SYS_CTRL_WDT_CFG_WDT_INT_EN_Pos   (1UL)                     /*!< WDT_INT_EN (Bit 1)                                    */
#define SYS_CTRL_WDT_CFG_WDT_INT_EN_Msk   (0x2UL)                   /*!< WDT_INT_EN (Bitfield-Mask: 0x01)                      */
#define SYS_CTRL_WDT_CFG_WDT_EN_Pos       (0UL)                     /*!< WDT_EN (Bit 0)                                        */
#define SYS_CTRL_WDT_CFG_WDT_EN_Msk       (0x1UL)                   /*!< WDT_EN (Bitfield-Mask: 0x01)                          */
/* ======================================================  WDT_STATUS  ======================================================= */
#define SYS_CTRL_WDT_STATUS_WDT_RSTN_Pos  (13UL)                    /*!< WDT_RSTN (Bit 13)                                     */
#define SYS_CTRL_WDT_STATUS_WDT_RSTN_Msk  (0x2000UL)                /*!< WDT_RSTN (Bitfield-Mask: 0x01)                        */
#define SYS_CTRL_WDT_STATUS_WDT_RST_STATUS_Pos (12UL)               /*!< WDT_RST_STATUS (Bit 12)                               */
#define SYS_CTRL_WDT_STATUS_WDT_RST_STATUS_Msk (0x1000UL)           /*!< WDT_RST_STATUS (Bitfield-Mask: 0x01)                  */
#define SYS_CTRL_WDT_STATUS_WDT_CNT_MONITOR_Pos (0UL)               /*!< WDT_CNT_MONITOR (Bit 0)                               */
#define SYS_CTRL_WDT_STATUS_WDT_CNT_MONITOR_Msk (0x1ffUL)           /*!< WDT_CNT_MONITOR (Bitfield-Mask: 0x1ff)                */
/* ========================================================  SDMA_EN  ======================================================== */
#define SYS_CTRL_SDMA_EN_SDMA_EN_Pos      (0UL)                     /*!< SDMA_EN (Bit 0)                                       */
#define SYS_CTRL_SDMA_EN_SDMA_EN_Msk      (0x1UL)                   /*!< SDMA_EN (Bitfield-Mask: 0x01)                         */
/* =================================================  SDMA_TASK_TABLE_ADDR  ================================================== */
#define SYS_CTRL_SDMA_TASK_TABLE_ADDR_SDMA_TASK_TABLE_ADDR_Pos (0UL) /*!< SDMA_TASK_TABLE_ADDR (Bit 0)                         */
#define SYS_CTRL_SDMA_TASK_TABLE_ADDR_SDMA_TASK_TABLE_ADDR_Msk (0xffffffffUL) /*!< SDMA_TASK_TABLE_ADDR (Bitfield-Mask: 0xffffffff) */
/* ======================================================  SDMA_ACTION  ====================================================== */
#define SYS_CTRL_SDMA_ACTION_SDMA_TASK_REMOVE_Pos (2UL)             /*!< SDMA_TASK_REMOVE (Bit 2)                              */
#define SYS_CTRL_SDMA_ACTION_SDMA_TASK_REMOVE_Msk (0x4UL)           /*!< SDMA_TASK_REMOVE (Bitfield-Mask: 0x01)                */
#define SYS_CTRL_SDMA_ACTION_SDMA_TASK_ADD_Pos (1UL)                /*!< SDMA_TASK_ADD (Bit 1)                                 */
#define SYS_CTRL_SDMA_ACTION_SDMA_TASK_ADD_Msk (0x2UL)              /*!< SDMA_TASK_ADD (Bitfield-Mask: 0x01)                   */
#define SYS_CTRL_SDMA_ACTION_SDMA_TASK_LOAD_Pos (0UL)               /*!< SDMA_TASK_LOAD (Bit 0)                                */
#define SYS_CTRL_SDMA_ACTION_SDMA_TASK_LOAD_Msk (0x1UL)             /*!< SDMA_TASK_LOAD (Bitfield-Mask: 0x01)                  */
/* =====================================================  SDMA_TASK_VAL  ===================================================== */
#define SYS_CTRL_SDMA_TASK_VAL_SDMA_TASK_VAL_Pos (0UL)              /*!< SDMA_TASK_VAL (Bit 0)                                 */
#define SYS_CTRL_SDMA_TASK_VAL_SDMA_TASK_VAL_Msk (0xffffffffUL)     /*!< SDMA_TASK_VAL (Bitfield-Mask: 0xffffffff)             */
/* ===================================================  SDMA_TASK_STATUS  ==================================================== */
#define SYS_CTRL_SDMA_TASK_STATUS_SDMA_TASK_STATUS_Pos (0UL)        /*!< SDMA_TASK_STATUS (Bit 0)                              */
#define SYS_CTRL_SDMA_TASK_STATUS_SDMA_TASK_STATUS_Msk (0xffffffffUL) /*!< SDMA_TASK_STATUS (Bitfield-Mask: 0xffffffff)        */
/* ====================================================  SDMA_INT_STATUS  ==================================================== */
#define SYS_CTRL_SDMA_INT_STATUS_SDMA_INT_STATUS_Pos (0UL)          /*!< SDMA_INT_STATUS (Bit 0)                               */
#define SYS_CTRL_SDMA_INT_STATUS_SDMA_INT_STATUS_Msk (0xffffffffUL) /*!< SDMA_INT_STATUS (Bitfield-Mask: 0xffffffff)           */
/* ====================================================  SDMA_INT_CLEAR  ===================================================== */
#define SYS_CTRL_SDMA_INT_CLEAR_SDMA_INT_CLEAR_Pos (0UL)            /*!< SDMA_INT_CLEAR (Bit 0)                                */
#define SYS_CTRL_SDMA_INT_CLEAR_SDMA_INT_CLEAR_Msk (0xffffffffUL)   /*!< SDMA_INT_CLEAR (Bitfield-Mask: 0xffffffff)            */


/* =========================================================================================================================== */
/* ================                                        GPIO_INOUT                                         ================ */
/* =========================================================================================================================== */

/* ====================================================  GPIO_FILT_CTRL  ===================================================== */
#define GPIO_INOUT_GPIO_FILT_CTRL_GPIO_FILT_WIN_Pos (16UL)          /*!< GPIO_FILT_WIN (Bit 16)                                */
#define GPIO_INOUT_GPIO_FILT_CTRL_GPIO_FILT_WIN_Msk (0xf0000UL)     /*!< GPIO_FILT_WIN (Bitfield-Mask: 0x0f)                   */
#define GPIO_INOUT_GPIO_FILT_CTRL_GPIO_FILT_EN_Pos (8UL)            /*!< GPIO_FILT_EN (Bit 8)                                  */
#define GPIO_INOUT_GPIO_FILT_CTRL_GPIO_FILT_EN_Msk (0x700UL)        /*!< GPIO_FILT_EN (Bitfield-Mask: 0x07)                    */
#define GPIO_INOUT_GPIO_FILT_CTRL_GPIO_GRP_EN_Pos (0UL)             /*!< GPIO_GRP_EN (Bit 0)                                   */
#define GPIO_INOUT_GPIO_FILT_CTRL_GPIO_GRP_EN_Msk (0x7UL)           /*!< GPIO_GRP_EN (Bitfield-Mask: 0x07)                     */
#define GPIO_INOUT_GPIO_FILT_CTRL_RESERVE_Pos (24UL)                /*!< RESERVE (Bit 24)                                      */
#define GPIO_INOUT_GPIO_FILT_CTRL_RESERVE_Msk (0xff000000UL)        /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ========================================================  GPIO_I  ========================================================= */
#define GPIO_INOUT_GPIO_I_GPIO_I_Pos      (0UL)                     /*!< GPIO_I (Bit 0)                                        */
#define GPIO_INOUT_GPIO_I_GPIO_I_Msk      (0xffffffUL)              /*!< GPIO_I (Bitfield-Mask: 0xffffff)                      */
#define GPIO_INOUT_GPIO_I_RESERVE_Pos     (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INOUT_GPIO_I_RESERVE_Msk     (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ========================================================  GPIO_OE  ======================================================== */
#define GPIO_INOUT_GPIO_OE_GPIO_OE_Pos    (0UL)                     /*!< GPIO_OE (Bit 0)                                       */
#define GPIO_INOUT_GPIO_OE_GPIO_OE_Msk    (0xffffffUL)              /*!< GPIO_OE (Bitfield-Mask: 0xffffff)                     */
#define GPIO_INOUT_GPIO_OE_RESERVE_Pos    (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INOUT_GPIO_OE_RESERVE_Msk    (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ========================================================  GPIO_O  ========================================================= */
#define GPIO_INOUT_GPIO_O_GPIO_O_Pos      (0UL)                     /*!< GPIO_O (Bit 0)                                        */
#define GPIO_INOUT_GPIO_O_GPIO_O_Msk      (0xffffffUL)              /*!< GPIO_O (Bitfield-Mask: 0xffffff)                      */
#define GPIO_INOUT_GPIO_O_RESERVE_Pos     (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INOUT_GPIO_O_RESERVE_Msk     (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  GPIO_O_SET  ======================================================= */
#define GPIO_INOUT_GPIO_O_SET_GPIO_O_SET_Pos (0UL)                  /*!< GPIO_O_SET (Bit 0)                                    */
#define GPIO_INOUT_GPIO_O_SET_GPIO_O_SET_Msk (0xffffffUL)           /*!< GPIO_O_SET (Bitfield-Mask: 0xffffff)                  */
#define GPIO_INOUT_GPIO_O_SET_RESERVE_Pos (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INOUT_GPIO_O_SET_RESERVE_Msk (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  GPIO_O_CLR  ======================================================= */
#define GPIO_INOUT_GPIO_O_CLR_GPIO_O_CLR_Pos (0UL)                  /*!< GPIO_O_CLR (Bit 0)                                    */
#define GPIO_INOUT_GPIO_O_CLR_GPIO_O_CLR_Msk (0xffffffUL)           /*!< GPIO_O_CLR (Bitfield-Mask: 0xffffff)                  */
#define GPIO_INOUT_GPIO_O_CLR_RESERVE_Pos (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INOUT_GPIO_O_CLR_RESERVE_Msk (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */


/* =========================================================================================================================== */
/* ================                                         GPIO_INTR                                         ================ */
/* =========================================================================================================================== */

/* ========================================================  GPIO_IE  ======================================================== */
#define GPIO_INTR_GPIO_IE_GPIO_IE_Pos     (0UL)                     /*!< GPIO_IE (Bit 0)                                       */
#define GPIO_INTR_GPIO_IE_GPIO_IE_Msk     (0xffffffUL)              /*!< GPIO_IE (Bitfield-Mask: 0xffffff)                     */
#define GPIO_INTR_GPIO_IE_RESERVE_Pos     (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INTR_GPIO_IE_RESERVE_Msk     (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ========================================================  GPIO_IS  ======================================================== */
#define GPIO_INTR_GPIO_IS_GPIO_IS_Pos     (0UL)                     /*!< GPIO_IS (Bit 0)                                       */
#define GPIO_INTR_GPIO_IS_GPIO_IS_Msk     (0xffffffUL)              /*!< GPIO_IS (Bitfield-Mask: 0xffffff)                     */
#define GPIO_INTR_GPIO_IS_RESERVE_Pos     (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INTR_GPIO_IS_RESERVE_Msk     (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =======================================================  GPIO_MIS  ======================================================== */
#define GPIO_INTR_GPIO_MIS_GPIO_MIS_Pos   (0UL)                     /*!< GPIO_MIS (Bit 0)                                      */
#define GPIO_INTR_GPIO_MIS_GPIO_MIS_Msk   (0xffffffUL)              /*!< GPIO_MIS (Bitfield-Mask: 0xffffff)                    */
#define GPIO_INTR_GPIO_MIS_RESERVE_Pos    (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INTR_GPIO_MIS_RESERVE_Msk    (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  GPIO_IT_HI  ======================================================= */
#define GPIO_INTR_GPIO_IT_HI_GPIO_IT_HI_Pos (0UL)                   /*!< GPIO_IT_HI (Bit 0)                                    */
#define GPIO_INTR_GPIO_IT_HI_GPIO_IT_HI_Msk (0xffffffUL)            /*!< GPIO_IT_HI (Bitfield-Mask: 0xffffff)                  */
#define GPIO_INTR_GPIO_IT_HI_RESERVE_Pos  (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INTR_GPIO_IT_HI_RESERVE_Msk  (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  GPIO_IT_LO  ======================================================= */
#define GPIO_INTR_GPIO_IT_LO_GPIO_IT_LO_Pos (0UL)                   /*!< GPIO_IT_LO (Bit 0)                                    */
#define GPIO_INTR_GPIO_IT_LO_GPIO_IT_LO_Msk (0xffffffUL)            /*!< GPIO_IT_LO (Bitfield-Mask: 0xffffff)                  */
#define GPIO_INTR_GPIO_IT_LO_RESERVE_Pos  (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define GPIO_INTR_GPIO_IT_LO_RESERVE_Msk  (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =====================================================  GPIO_IT_PEDGE  ===================================================== */
#define GPIO_INTR_GPIO_IT_PEDGE_GPIO_IT_PEDGE_Pos (0UL)             /*!< GPIO_IT_PEDGE (Bit 0)                                 */
#define GPIO_INTR_GPIO_IT_PEDGE_GPIO_IT_PEDGE_Msk (0xffffffUL)      /*!< GPIO_IT_PEDGE (Bitfield-Mask: 0xffffff)               */
#define GPIO_INTR_GPIO_IT_PEDGE_RESERVE_Pos (24UL)                  /*!< RESERVE (Bit 24)                                      */
#define GPIO_INTR_GPIO_IT_PEDGE_RESERVE_Msk (0xff000000UL)          /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =====================================================  GPIO_IT_NEDGE  ===================================================== */
#define GPIO_INTR_GPIO_IT_NEDGE_GPIO_IT_NEDGE_Pos (0UL)             /*!< GPIO_IT_NEDGE (Bit 0)                                 */
#define GPIO_INTR_GPIO_IT_NEDGE_GPIO_IT_NEDGE_Msk (0xffffffUL)      /*!< GPIO_IT_NEDGE (Bitfield-Mask: 0xffffff)               */
#define GPIO_INTR_GPIO_IT_NEDGE_RESERVE_Pos (24UL)                  /*!< RESERVE (Bit 24)                                      */
#define GPIO_INTR_GPIO_IT_NEDGE_RESERVE_Msk (0xff000000UL)          /*!< RESERVE (Bitfield-Mask: 0xff)                         */


/* =========================================================================================================================== */
/* ================                                         GPIO_ATF                                          ================ */
/* =========================================================================================================================== */

/* ======================================================  GPIO_CFG_0  ======================================================= */
#define GPIO_ATF_GPIO_CFG_0_GPIO3_CFG_Pos (24UL)                    /*!< GPIO3_CFG (Bit 24)                                    */
#define GPIO_ATF_GPIO_CFG_0_GPIO3_CFG_Msk (0xff000000UL)            /*!< GPIO3_CFG (Bitfield-Mask: 0xff)                       */
#define GPIO_ATF_GPIO_CFG_0_GPIO2_CFG_Pos (16UL)                    /*!< GPIO2_CFG (Bit 16)                                    */
#define GPIO_ATF_GPIO_CFG_0_GPIO2_CFG_Msk (0xff0000UL)              /*!< GPIO2_CFG (Bitfield-Mask: 0xff)                       */
#define GPIO_ATF_GPIO_CFG_0_GPIO1_CFG_Pos (8UL)                     /*!< GPIO1_CFG (Bit 8)                                     */
#define GPIO_ATF_GPIO_CFG_0_GPIO1_CFG_Msk (0xff00UL)                /*!< GPIO1_CFG (Bitfield-Mask: 0xff)                       */
#define GPIO_ATF_GPIO_CFG_0_GPIO0_CFG_Pos (0UL)                     /*!< GPIO0_CFG (Bit 0)                                     */
#define GPIO_ATF_GPIO_CFG_0_GPIO0_CFG_Msk (0xffUL)                  /*!< GPIO0_CFG (Bitfield-Mask: 0xff)                       */
/* ======================================================  GPIO_CFG_1  ======================================================= */
#define GPIO_ATF_GPIO_CFG_1_GPIO7_CFG_Pos (24UL)                    /*!< GPIO7_CFG (Bit 24)                                    */
#define GPIO_ATF_GPIO_CFG_1_GPIO7_CFG_Msk (0xff000000UL)            /*!< GPIO7_CFG (Bitfield-Mask: 0xff)                       */
#define GPIO_ATF_GPIO_CFG_1_GPIO6_CFG_Pos (16UL)                    /*!< GPIO6_CFG (Bit 16)                                    */
#define GPIO_ATF_GPIO_CFG_1_GPIO6_CFG_Msk (0xff0000UL)              /*!< GPIO6_CFG (Bitfield-Mask: 0xff)                       */
#define GPIO_ATF_GPIO_CFG_1_GPIO5_CFG_Pos (8UL)                     /*!< GPIO5_CFG (Bit 8)                                     */
#define GPIO_ATF_GPIO_CFG_1_GPIO5_CFG_Msk (0xff00UL)                /*!< GPIO5_CFG (Bitfield-Mask: 0xff)                       */
#define GPIO_ATF_GPIO_CFG_1_GPIO4_CFG_Pos (0UL)                     /*!< GPIO4_CFG (Bit 0)                                     */
#define GPIO_ATF_GPIO_CFG_1_GPIO4_CFG_Msk (0xffUL)                  /*!< GPIO4_CFG (Bitfield-Mask: 0xff)                       */
/* ======================================================  GPIO_CFG_2  ======================================================= */
#define GPIO_ATF_GPIO_CFG_2_GPIO11_CFG_Pos (24UL)                   /*!< GPIO11_CFG (Bit 24)                                   */
#define GPIO_ATF_GPIO_CFG_2_GPIO11_CFG_Msk (0xff000000UL)           /*!< GPIO11_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_2_GPIO10_CFG_Pos (16UL)                   /*!< GPIO10_CFG (Bit 16)                                   */
#define GPIO_ATF_GPIO_CFG_2_GPIO10_CFG_Msk (0xff0000UL)             /*!< GPIO10_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_2_GPIO9_CFG_Pos (8UL)                     /*!< GPIO9_CFG (Bit 8)                                     */
#define GPIO_ATF_GPIO_CFG_2_GPIO9_CFG_Msk (0xff00UL)                /*!< GPIO9_CFG (Bitfield-Mask: 0xff)                       */
#define GPIO_ATF_GPIO_CFG_2_GPIO8_CFG_Pos (0UL)                     /*!< GPIO8_CFG (Bit 0)                                     */
#define GPIO_ATF_GPIO_CFG_2_GPIO8_CFG_Msk (0xffUL)                  /*!< GPIO8_CFG (Bitfield-Mask: 0xff)                       */
/* ======================================================  GPIO_CFG_3  ======================================================= */
#define GPIO_ATF_GPIO_CFG_3_GPIO15_CFG_Pos (24UL)                   /*!< GPIO15_CFG (Bit 24)                                   */
#define GPIO_ATF_GPIO_CFG_3_GPIO15_CFG_Msk (0xff000000UL)           /*!< GPIO15_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_3_GPIO14_CFG_Pos (16UL)                   /*!< GPIO14_CFG (Bit 16)                                   */
#define GPIO_ATF_GPIO_CFG_3_GPIO14_CFG_Msk (0xff0000UL)             /*!< GPIO14_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_3_GPIO13_CFG_Pos (8UL)                    /*!< GPIO13_CFG (Bit 8)                                    */
#define GPIO_ATF_GPIO_CFG_3_GPIO13_CFG_Msk (0xff00UL)               /*!< GPIO13_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_3_GPIO12_CFG_Pos (0UL)                    /*!< GPIO12_CFG (Bit 0)                                    */
#define GPIO_ATF_GPIO_CFG_3_GPIO12_CFG_Msk (0xffUL)                 /*!< GPIO12_CFG (Bitfield-Mask: 0xff)                      */
/* ======================================================  GPIO_CFG_4  ======================================================= */
#define GPIO_ATF_GPIO_CFG_4_GPIO19_CFG_Pos (24UL)                   /*!< GPIO19_CFG (Bit 24)                                   */
#define GPIO_ATF_GPIO_CFG_4_GPIO19_CFG_Msk (0xff000000UL)           /*!< GPIO19_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_4_GPIO18_CFG_Pos (16UL)                   /*!< GPIO18_CFG (Bit 16)                                   */
#define GPIO_ATF_GPIO_CFG_4_GPIO18_CFG_Msk (0xff0000UL)             /*!< GPIO18_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_4_GPIO17_CFG_Pos (8UL)                    /*!< GPIO17_CFG (Bit 8)                                    */
#define GPIO_ATF_GPIO_CFG_4_GPIO17_CFG_Msk (0xff00UL)               /*!< GPIO17_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_4_GPIO16_CFG_Pos (0UL)                    /*!< GPIO16_CFG (Bit 0)                                    */
#define GPIO_ATF_GPIO_CFG_4_GPIO16_CFG_Msk (0xffUL)                 /*!< GPIO16_CFG (Bitfield-Mask: 0xff)                      */
/* ======================================================  GPIO_CFG_5  ======================================================= */
#define GPIO_ATF_GPIO_CFG_5_GPIO23_CFG_Pos (24UL)                   /*!< GPIO23_CFG (Bit 24)                                   */
#define GPIO_ATF_GPIO_CFG_5_GPIO23_CFG_Msk (0xff000000UL)           /*!< GPIO23_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_5_GPIO22_CFG_Pos (16UL)                   /*!< GPIO22_CFG (Bit 16)                                   */
#define GPIO_ATF_GPIO_CFG_5_GPIO22_CFG_Msk (0xff0000UL)             /*!< GPIO22_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_5_GPIO21_CFG_Pos (8UL)                    /*!< GPIO21_CFG (Bit 8)                                    */
#define GPIO_ATF_GPIO_CFG_5_GPIO21_CFG_Msk (0xff00UL)               /*!< GPIO21_CFG (Bitfield-Mask: 0xff)                      */
#define GPIO_ATF_GPIO_CFG_5_GPIO20_CFG_Pos (0UL)                    /*!< GPIO20_CFG (Bit 0)                                    */
#define GPIO_ATF_GPIO_CFG_5_GPIO20_CFG_Msk (0xffUL)                 /*!< GPIO20_CFG (Bitfield-Mask: 0xff)                      */


/* =========================================================================================================================== */
/* ================                                         QDEC_CTRL                                         ================ */
/* =========================================================================================================================== */

/* =======================================================  QDEC_DIV  ======================================================== */
#define QDEC_CTRL_QDEC_DIV_REPORT_DIV_Pos (16UL)                    /*!< REPORT_DIV (Bit 16)                                   */
#define QDEC_CTRL_QDEC_DIV_REPORT_DIV_Msk (0xff0000UL)              /*!< REPORT_DIV (Bitfield-Mask: 0xff)                      */
#define QDEC_CTRL_QDEC_DIV_SAMP_DIV_Pos   (0UL)                     /*!< SAMP_DIV (Bit 0)                                      */
#define QDEC_CTRL_QDEC_DIV_SAMP_DIV_Msk   (0xffffUL)                /*!< SAMP_DIV (Bitfield-Mask: 0xffff)                      */
#define QDEC_CTRL_QDEC_DIV_RESERVE_Pos    (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define QDEC_CTRL_QDEC_DIV_RESERVE_Msk    (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =======================================================  QDEC_CTRL  ======================================================= */
#define QDEC_CTRL_QDEC_CTRL_DBF_MODE_Pos  (24UL)                    /*!< DBF_MODE (Bit 24)                                     */
#define QDEC_CTRL_QDEC_CTRL_DBF_MODE_Msk  (0x3000000UL)             /*!< DBF_MODE (Bitfield-Mask: 0x03)                        */
#define QDEC_CTRL_QDEC_CTRL_Z_MODE_Pos    (20UL)                    /*!< Z_MODE (Bit 20)                                       */
#define QDEC_CTRL_QDEC_CTRL_Z_MODE_Msk    (0x300000UL)              /*!< Z_MODE (Bitfield-Mask: 0x03)                          */
#define QDEC_CTRL_QDEC_CTRL_Z_EN_Pos      (16UL)                    /*!< Z_EN (Bit 16)                                         */
#define QDEC_CTRL_QDEC_CTRL_Z_EN_Msk      (0x10000UL)               /*!< Z_EN (Bitfield-Mask: 0x01)                            */
#define QDEC_CTRL_QDEC_CTRL_Y_MODE_Pos    (12UL)                    /*!< Y_MODE (Bit 12)                                       */
#define QDEC_CTRL_QDEC_CTRL_Y_MODE_Msk    (0x3000UL)                /*!< Y_MODE (Bitfield-Mask: 0x03)                          */
#define QDEC_CTRL_QDEC_CTRL_Y_EN_Pos      (8UL)                     /*!< Y_EN (Bit 8)                                          */
#define QDEC_CTRL_QDEC_CTRL_Y_EN_Msk      (0x100UL)                 /*!< Y_EN (Bitfield-Mask: 0x01)                            */
#define QDEC_CTRL_QDEC_CTRL_X_MODE_Pos    (4UL)                     /*!< X_MODE (Bit 4)                                        */
#define QDEC_CTRL_QDEC_CTRL_X_MODE_Msk    (0x30UL)                  /*!< X_MODE (Bitfield-Mask: 0x03)                          */
#define QDEC_CTRL_QDEC_CTRL_X_EN_Pos      (0UL)                     /*!< X_EN (Bit 0)                                          */
#define QDEC_CTRL_QDEC_CTRL_X_EN_Msk      (0x1UL)                   /*!< X_EN (Bitfield-Mask: 0x01)                            */
/* =======================================================  LED_CTRL  ======================================================== */
#define QDEC_CTRL_LED_CTRL_LED_PRE_Pos    (16UL)                    /*!< LED_PRE (Bit 16)                                      */
#define QDEC_CTRL_LED_CTRL_LED_PRE_Msk    (0xff0000UL)              /*!< LED_PRE (Bitfield-Mask: 0xff)                         */
#define QDEC_CTRL_LED_CTRL_LED_POL_Pos    (1UL)                     /*!< LED_POL (Bit 1)                                       */
#define QDEC_CTRL_LED_CTRL_LED_POL_Msk    (0x2UL)                   /*!< LED_POL (Bitfield-Mask: 0x01)                         */
#define QDEC_CTRL_LED_CTRL_LED_EN_Pos     (0UL)                     /*!< LED_EN (Bit 0)                                        */
#define QDEC_CTRL_LED_CTRL_LED_EN_Msk     (0x1UL)                   /*!< LED_EN (Bitfield-Mask: 0x01)                          */
#define QDEC_CTRL_LED_CTRL_RESERVE_Pos    (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define QDEC_CTRL_LED_CTRL_RESERVE_Msk    (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */


/* =========================================================================================================================== */
/* ================                                         QDEC_INTR                                         ================ */
/* =========================================================================================================================== */

/* ========================================================  QDEC_IE  ======================================================== */
#define QDEC_INTR_QDEC_IE_Z_IE_Pos        (16UL)                    /*!< Z_IE (Bit 16)                                         */
#define QDEC_INTR_QDEC_IE_Z_IE_Msk        (0x1f0000UL)              /*!< Z_IE (Bitfield-Mask: 0x1f)                            */
#define QDEC_INTR_QDEC_IE_Y_IE_Pos        (8UL)                     /*!< Y_IE (Bit 8)                                          */
#define QDEC_INTR_QDEC_IE_Y_IE_Msk        (0x1f00UL)                /*!< Y_IE (Bitfield-Mask: 0x1f)                            */
#define QDEC_INTR_QDEC_IE_X_IE_Pos        (0UL)                     /*!< X_IE (Bit 0)                                          */
#define QDEC_INTR_QDEC_IE_X_IE_Msk        (0x1fUL)                  /*!< X_IE (Bitfield-Mask: 0x1f)                            */
#define QDEC_INTR_QDEC_IE_RESERVE_Pos     (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define QDEC_INTR_QDEC_IE_RESERVE_Msk     (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ========================================================  QDEC_IS  ======================================================== */
#define QDEC_INTR_QDEC_IS_Z_IS_Pos        (16UL)                    /*!< Z_IS (Bit 16)                                         */
#define QDEC_INTR_QDEC_IS_Z_IS_Msk        (0x1f0000UL)              /*!< Z_IS (Bitfield-Mask: 0x1f)                            */
#define QDEC_INTR_QDEC_IS_Y_IS_Pos        (8UL)                     /*!< Y_IS (Bit 8)                                          */
#define QDEC_INTR_QDEC_IS_Y_IS_Msk        (0x1f00UL)                /*!< Y_IS (Bitfield-Mask: 0x1f)                            */
#define QDEC_INTR_QDEC_IS_X_IS_Pos        (0UL)                     /*!< X_IS (Bit 0)                                          */
#define QDEC_INTR_QDEC_IS_X_IS_Msk        (0x1fUL)                  /*!< X_IS (Bitfield-Mask: 0x1f)                            */
#define QDEC_INTR_QDEC_IS_RESERVE_Pos     (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define QDEC_INTR_QDEC_IS_RESERVE_Msk     (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =======================================================  QDEC_MIS  ======================================================== */
#define QDEC_INTR_QDEC_MIS_Z_MIS_Pos      (16UL)                    /*!< Z_MIS (Bit 16)                                        */
#define QDEC_INTR_QDEC_MIS_Z_MIS_Msk      (0x1f0000UL)              /*!< Z_MIS (Bitfield-Mask: 0x1f)                           */
#define QDEC_INTR_QDEC_MIS_Y_MIS_Pos      (8UL)                     /*!< Y_MIS (Bit 8)                                         */
#define QDEC_INTR_QDEC_MIS_Y_MIS_Msk      (0x1f00UL)                /*!< Y_MIS (Bitfield-Mask: 0x1f)                           */
#define QDEC_INTR_QDEC_MIS_X_MIS_Pos      (0UL)                     /*!< X_MIS (Bit 0)                                         */
#define QDEC_INTR_QDEC_MIS_X_MIS_Msk      (0x1fUL)                  /*!< X_MIS (Bitfield-Mask: 0x1f)                           */
#define QDEC_INTR_QDEC_MIS_RESERVE_Pos    (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define QDEC_INTR_QDEC_MIS_RESERVE_Msk    (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */


/* =========================================================================================================================== */
/* ================                                        QDEC_X_AXIS                                        ================ */
/* =========================================================================================================================== */

/* ========================================================  X_SAMP  ========================================================= */
#define QDEC_X_AXIS_X_SAMP_X_SAMP_Pos     (0UL)                     /*!< X_SAMP (Bit 0)                                        */
#define QDEC_X_AXIS_X_SAMP_X_SAMP_Msk     (0xffffffffUL)            /*!< X_SAMP (Bitfield-Mask: 0xffffffff)                    */
/* ========================================================  X_READ  ========================================================= */
#define QDEC_X_AXIS_X_READ_X_ACCDBL_READ_CLR_Pos (9UL)              /*!< X_ACCDBL_READ_CLR (Bit 9)                             */
#define QDEC_X_AXIS_X_READ_X_ACCDBL_READ_CLR_Msk (0x200UL)          /*!< X_ACCDBL_READ_CLR (Bitfield-Mask: 0x01)               */
#define QDEC_X_AXIS_X_READ_X_ACCDBL_READ_Pos (8UL)                  /*!< X_ACCDBL_READ (Bit 8)                                 */
#define QDEC_X_AXIS_X_READ_X_ACCDBL_READ_Msk (0x100UL)              /*!< X_ACCDBL_READ (Bitfield-Mask: 0x01)                   */
#define QDEC_X_AXIS_X_READ_X_ACC_READ_CLR_Pos (1UL)                 /*!< X_ACC_READ_CLR (Bit 1)                                */
#define QDEC_X_AXIS_X_READ_X_ACC_READ_CLR_Msk (0x2UL)               /*!< X_ACC_READ_CLR (Bitfield-Mask: 0x01)                  */
#define QDEC_X_AXIS_X_READ_X_ACC_READ_Pos (0UL)                     /*!< X_ACC_READ (Bit 0)                                    */
#define QDEC_X_AXIS_X_READ_X_ACC_READ_Msk (0x1UL)                   /*!< X_ACC_READ (Bitfield-Mask: 0x01)                      */
/* =========================================================  X_ACC  ========================================================= */
#define QDEC_X_AXIS_X_ACC_X_ACC_Pos       (0UL)                     /*!< X_ACC (Bit 0)                                         */
#define QDEC_X_AXIS_X_ACC_X_ACC_Msk       (0xffffffffUL)            /*!< X_ACC (Bitfield-Mask: 0xffffffff)                     */
/* ======================================================  X_ACC_LOAD  ======================================================= */
#define QDEC_X_AXIS_X_ACC_LOAD_X_ACC_LOAD_Pos (0UL)                 /*!< X_ACC_LOAD (Bit 0)                                    */
#define QDEC_X_AXIS_X_ACC_LOAD_X_ACC_LOAD_Msk (0xffffffffUL)        /*!< X_ACC_LOAD (Bitfield-Mask: 0xffffffff)                */
/* =======================================================  X_ACCDBL  ======================================================== */
#define QDEC_X_AXIS_X_ACCDBL_X_ACCDBL_Pos (0UL)                     /*!< X_ACCDBL (Bit 0)                                      */
#define QDEC_X_AXIS_X_ACCDBL_X_ACCDBL_Msk (0xffUL)                  /*!< X_ACCDBL (Bitfield-Mask: 0xff)                        */
/* =====================================================  X_ACCDBL_LOAD  ===================================================== */
#define QDEC_X_AXIS_X_ACCDBL_LOAD_X_ACCDBL_LOAD_Pos (0UL)           /*!< X_ACCDBL_LOAD (Bit 0)                                 */
#define QDEC_X_AXIS_X_ACCDBL_LOAD_X_ACCDBL_LOAD_Msk (0xffUL)        /*!< X_ACCDBL_LOAD (Bitfield-Mask: 0xff)                   */


/* =========================================================================================================================== */
/* ================                                        QDEC_Y_AXIS                                        ================ */
/* =========================================================================================================================== */

/* ========================================================  Y_SAMP  ========================================================= */
#define QDEC_Y_AXIS_Y_SAMP_Y_SAMP_Pos     (0UL)                     /*!< Y_SAMP (Bit 0)                                        */
#define QDEC_Y_AXIS_Y_SAMP_Y_SAMP_Msk     (0xffffffffUL)            /*!< Y_SAMP (Bitfield-Mask: 0xffffffff)                    */
/* ========================================================  Y_READ  ========================================================= */
#define QDEC_Y_AXIS_Y_READ_Y_ACCDBL_READ_CLR_Pos (9UL)              /*!< Y_ACCDBL_READ_CLR (Bit 9)                             */
#define QDEC_Y_AXIS_Y_READ_Y_ACCDBL_READ_CLR_Msk (0x200UL)          /*!< Y_ACCDBL_READ_CLR (Bitfield-Mask: 0x01)               */
#define QDEC_Y_AXIS_Y_READ_Y_ACCDBL_READ_Pos (8UL)                  /*!< Y_ACCDBL_READ (Bit 8)                                 */
#define QDEC_Y_AXIS_Y_READ_Y_ACCDBL_READ_Msk (0x100UL)              /*!< Y_ACCDBL_READ (Bitfield-Mask: 0x01)                   */
#define QDEC_Y_AXIS_Y_READ_Y_ACC_READ_CLR_Pos (1UL)                 /*!< Y_ACC_READ_CLR (Bit 1)                                */
#define QDEC_Y_AXIS_Y_READ_Y_ACC_READ_CLR_Msk (0x2UL)               /*!< Y_ACC_READ_CLR (Bitfield-Mask: 0x01)                  */
#define QDEC_Y_AXIS_Y_READ_Y_ACC_READ_Pos (0UL)                     /*!< Y_ACC_READ (Bit 0)                                    */
#define QDEC_Y_AXIS_Y_READ_Y_ACC_READ_Msk (0x1UL)                   /*!< Y_ACC_READ (Bitfield-Mask: 0x01)                      */
/* =========================================================  Y_ACC  ========================================================= */
#define QDEC_Y_AXIS_Y_ACC_Y_ACC_Pos       (0UL)                     /*!< Y_ACC (Bit 0)                                         */
#define QDEC_Y_AXIS_Y_ACC_Y_ACC_Msk       (0xffffffffUL)            /*!< Y_ACC (Bitfield-Mask: 0xffffffff)                     */
/* ======================================================  Y_ACC_LOAD  ======================================================= */
#define QDEC_Y_AXIS_Y_ACC_LOAD_Y_ACC_LOAD_Pos (0UL)                 /*!< Y_ACC_LOAD (Bit 0)                                    */
#define QDEC_Y_AXIS_Y_ACC_LOAD_Y_ACC_LOAD_Msk (0xffffffffUL)        /*!< Y_ACC_LOAD (Bitfield-Mask: 0xffffffff)                */
/* =======================================================  Y_ACCDBL  ======================================================== */
#define QDEC_Y_AXIS_Y_ACCDBL_Y_ACCDBL_Pos (0UL)                     /*!< Y_ACCDBL (Bit 0)                                      */
#define QDEC_Y_AXIS_Y_ACCDBL_Y_ACCDBL_Msk (0xffUL)                  /*!< Y_ACCDBL (Bitfield-Mask: 0xff)                        */
/* =====================================================  Y_ACCDBL_LOAD  ===================================================== */
#define QDEC_Y_AXIS_Y_ACCDBL_LOAD_Y_ACCDBL_LOAD_Pos (0UL)           /*!< Y_ACCDBL_LOAD (Bit 0)                                 */
#define QDEC_Y_AXIS_Y_ACCDBL_LOAD_Y_ACCDBL_LOAD_Msk (0xffUL)        /*!< Y_ACCDBL_LOAD (Bitfield-Mask: 0xff)                   */


/* =========================================================================================================================== */
/* ================                                        QDEC_Z_AXIS                                        ================ */
/* =========================================================================================================================== */

/* ========================================================  Z_SAMP  ========================================================= */
#define QDEC_Z_AXIS_Z_SAMP_Z_SAMP_Pos     (0UL)                     /*!< Z_SAMP (Bit 0)                                        */
#define QDEC_Z_AXIS_Z_SAMP_Z_SAMP_Msk     (0xffffffffUL)            /*!< Z_SAMP (Bitfield-Mask: 0xffffffff)                    */
/* ========================================================  Z_READ  ========================================================= */
#define QDEC_Z_AXIS_Z_READ_Z_ACCDBL_READ_CLR_Pos (9UL)              /*!< Z_ACCDBL_READ_CLR (Bit 9)                             */
#define QDEC_Z_AXIS_Z_READ_Z_ACCDBL_READ_CLR_Msk (0x200UL)          /*!< Z_ACCDBL_READ_CLR (Bitfield-Mask: 0x01)               */
#define QDEC_Z_AXIS_Z_READ_Z_ACCDBL_READ_Pos (8UL)                  /*!< Z_ACCDBL_READ (Bit 8)                                 */
#define QDEC_Z_AXIS_Z_READ_Z_ACCDBL_READ_Msk (0x100UL)              /*!< Z_ACCDBL_READ (Bitfield-Mask: 0x01)                   */
#define QDEC_Z_AXIS_Z_READ_Z_ACC_READ_CLR_Pos (1UL)                 /*!< Z_ACC_READ_CLR (Bit 1)                                */
#define QDEC_Z_AXIS_Z_READ_Z_ACC_READ_CLR_Msk (0x2UL)               /*!< Z_ACC_READ_CLR (Bitfield-Mask: 0x01)                  */
#define QDEC_Z_AXIS_Z_READ_Z_ACC_READ_Pos (0UL)                     /*!< Z_ACC_READ (Bit 0)                                    */
#define QDEC_Z_AXIS_Z_READ_Z_ACC_READ_Msk (0x1UL)                   /*!< Z_ACC_READ (Bitfield-Mask: 0x01)                      */
/* =========================================================  Z_ACC  ========================================================= */
#define QDEC_Z_AXIS_Z_ACC_Z_ACC_Pos       (0UL)                     /*!< Z_ACC (Bit 0)                                         */
#define QDEC_Z_AXIS_Z_ACC_Z_ACC_Msk       (0xffffffffUL)            /*!< Z_ACC (Bitfield-Mask: 0xffffffff)                     */
/* ======================================================  Z_ACC_LOAD  ======================================================= */
#define QDEC_Z_AXIS_Z_ACC_LOAD_Z_ACC_LOAD_Pos (0UL)                 /*!< Z_ACC_LOAD (Bit 0)                                    */
#define QDEC_Z_AXIS_Z_ACC_LOAD_Z_ACC_LOAD_Msk (0xffffffffUL)        /*!< Z_ACC_LOAD (Bitfield-Mask: 0xffffffff)                */
/* =======================================================  Z_ACCDBL  ======================================================== */
#define QDEC_Z_AXIS_Z_ACCDBL_Z_ACCDBL_Pos (0UL)                     /*!< Z_ACCDBL (Bit 0)                                      */
#define QDEC_Z_AXIS_Z_ACCDBL_Z_ACCDBL_Msk (0xffUL)                  /*!< Z_ACCDBL (Bitfield-Mask: 0xff)                        */
/* =====================================================  Z_ACCDBL_LOAD  ===================================================== */
#define QDEC_Z_AXIS_Z_ACCDBL_LOAD_Z_ACCDBL_LOAD_Pos (0UL)           /*!< Z_ACCDBL_LOAD (Bit 0)                                 */
#define QDEC_Z_AXIS_Z_ACCDBL_LOAD_Z_ACCDBL_LOAD_Msk (0xffUL)        /*!< Z_ACCDBL_LOAD (Bitfield-Mask: 0xff)                   */


/* =========================================================================================================================== */
/* ================                                         KEYSCAN                                          ================ */
/* =========================================================================================================================== */

/* =======================================================  KB_CTRL0  ======================================================== */
#define KEYSCAN_KB_CTRL0_PULL_DLY_Pos    (28UL)                    /*!< PULL_DLY (Bit 28)                                     */
#define KEYSCAN_KB_CTRL0_PULL_DLY_Msk    (0xf0000000UL)            /*!< PULL_DLY (Bitfield-Mask: 0x0f)                        */
#define KEYSCAN_KB_CTRL0_DRV_DLY_Pos     (24UL)                    /*!< DRV_DLY (Bit 24)                                      */
#define KEYSCAN_KB_CTRL0_DRV_DLY_Msk     (0xf000000UL)             /*!< DRV_DLY (Bitfield-Mask: 0x0f)                         */
#define KEYSCAN_KB_CTRL0_KB_HIGH_EN_Pos  (16UL)                    /*!< KB_HIGH_EN (Bit 16)                                   */
#define KEYSCAN_KB_CTRL0_KB_HIGH_EN_Msk  (0x1f0000UL)              /*!< KB_HIGH_EN (Bitfield-Mask: 0x1f)                      */
#define KEYSCAN_KB_CTRL0_SCAN_SEL_Pos    (12UL)                    /*!< SCAN_SEL (Bit 12)                                     */
#define KEYSCAN_KB_CTRL0_SCAN_SEL_Msk    (0x1000UL)                /*!< SCAN_SEL (Bitfield-Mask: 0x01)                        */
#define KEYSCAN_KB_CTRL0_MUX_SEL_Pos     (8UL)                     /*!< MUX_SEL (Bit 8)                                       */
#define KEYSCAN_KB_CTRL0_MUX_SEL_Msk     (0x300UL)                 /*!< MUX_SEL (Bitfield-Mask: 0x03)                         */
#define KEYSCAN_KB_CTRL0_SCAN_EN_Pos     (0UL)                     /*!< SCAN_EN (Bit 0)                                       */
#define KEYSCAN_KB_CTRL0_SCAN_EN_Msk     (0x1UL)                   /*!< SCAN_EN (Bitfield-Mask: 0x01)                         */
/* =======================================================  KB_CTRL1  ======================================================== */
#define KEYSCAN_KB_CTRL1_SCAN_DLY_Pos    (24UL)                    /*!< SCAN_DLY (Bit 24)                                     */
#define KEYSCAN_KB_CTRL1_SCAN_DLY_Msk    (0xff000000UL)            /*!< SCAN_DLY (Bitfield-Mask: 0xff)                        */
#define KEYSCAN_KB_CTRL1_IDLE_PU_Pos     (21UL)                    /*!< IDLE_PU (Bit 21)                                      */
#define KEYSCAN_KB_CTRL1_IDLE_PU_Msk     (0x200000UL)              /*!< IDLE_PU (Bitfield-Mask: 0x01)                         */
#define KEYSCAN_KB_CTRL1_IDLE_PD_Pos     (20UL)                    /*!< IDLE_PD (Bit 20)                                      */
#define KEYSCAN_KB_CTRL1_IDLE_PD_Msk     (0x100000UL)              /*!< IDLE_PD (Bitfield-Mask: 0x01)                         */
#define KEYSCAN_KB_CTRL1_FILT_NUM_Pos    (16UL)                    /*!< FILT_NUM (Bit 16)                                     */
#define KEYSCAN_KB_CTRL1_FILT_NUM_Msk    (0xf0000UL)               /*!< FILT_NUM (Bitfield-Mask: 0x0f)                        */
#define KEYSCAN_KB_CTRL1_A3_SIZE_Pos     (12UL)                    /*!< A3_SIZE (Bit 12)                                      */
#define KEYSCAN_KB_CTRL1_A3_SIZE_Msk     (0xf000UL)                /*!< A3_SIZE (Bitfield-Mask: 0x0f)                         */
#define KEYSCAN_KB_CTRL1_A3_POLAR_Pos    (9UL)                     /*!< A3_POLAR (Bit 9)                                      */
#define KEYSCAN_KB_CTRL1_A3_POLAR_Msk    (0x200UL)                 /*!< A3_POLAR (Bitfield-Mask: 0x01)                        */
#define KEYSCAN_KB_CTRL1_A3_ARCH_Pos     (8UL)                     /*!< A3_ARCH (Bit 8)                                       */
#define KEYSCAN_KB_CTRL1_A3_ARCH_Msk     (0x100UL)                 /*!< A3_ARCH (Bitfield-Mask: 0x01)                         */
#define KEYSCAN_KB_CTRL1_COMB_NUM_Pos    (6UL)                     /*!< COMB_NUM (Bit 6)                                      */
#define KEYSCAN_KB_CTRL1_COMB_NUM_Msk    (0xc0UL)                  /*!< COMB_NUM (Bitfield-Mask: 0x03)                        */
#define KEYSCAN_KB_CTRL1_COMB_MODE_Pos   (5UL)                     /*!< COMB_MODE (Bit 5)                                     */
#define KEYSCAN_KB_CTRL1_COMB_MODE_Msk   (0x20UL)                  /*!< COMB_MODE (Bitfield-Mask: 0x01)                       */
#define KEYSCAN_KB_CTRL1_COMB_AREA_Pos   (4UL)                     /*!< COMB_AREA (Bit 4)                                     */
#define KEYSCAN_KB_CTRL1_COMB_AREA_Msk   (0x10UL)                  /*!< COMB_AREA (Bitfield-Mask: 0x01)                       */
#define KEYSCAN_KB_CTRL1_SCAN_AREA_Pos   (0UL)                     /*!< SCAN_AREA (Bit 0)                                     */
#define KEYSCAN_KB_CTRL1_SCAN_AREA_Msk   (0x7UL)                   /*!< SCAN_AREA (Bitfield-Mask: 0x07)                       */
/* ========================================================  KB_INTR  ======================================================== */
#define KEYSCAN_KB_INTR_KB_MIS_Pos       (16UL)                    /*!< KB_MIS (Bit 16)                                       */
#define KEYSCAN_KB_INTR_KB_MIS_Msk       (0x30000UL)               /*!< KB_MIS (Bitfield-Mask: 0x03)                          */
#define KEYSCAN_KB_INTR_KB_IS_Pos        (8UL)                     /*!< KB_IS (Bit 8)                                         */
#define KEYSCAN_KB_INTR_KB_IS_Msk        (0x300UL)                 /*!< KB_IS (Bitfield-Mask: 0x03)                           */
#define KEYSCAN_KB_INTR_KB_IE_Pos        (0UL)                     /*!< KB_IE (Bit 0)                                         */
#define KEYSCAN_KB_INTR_KB_IE_Msk        (0x3UL)                   /*!< KB_IE (Bitfield-Mask: 0x03)                           */
#define KEYSCAN_KB_INTR_reserve_Pos      (24UL)                    /*!< reserve (Bit 24)                                      */
#define KEYSCAN_KB_INTR_reserve_Msk      (0xff000000UL)            /*!< reserve (Bitfield-Mask: 0xff)                         */
/* =======================================================  KB_INFO0  ======================================================== */
#define KEYSCAN_KB_INFO0_PRESS_NUM_Pos   (0UL)                     /*!< PRESS_NUM (Bit 0)                                     */
#define KEYSCAN_KB_INFO0_PRESS_NUM_Msk   (0xfUL)                   /*!< PRESS_NUM (Bitfield-Mask: 0x0f)                       */
/* =======================================================  KB_INFO1  ======================================================== */
#define KEYSCAN_KB_INFO1_PRESS3_Pos      (24UL)                    /*!< PRESS3 (Bit 24)                                       */
#define KEYSCAN_KB_INFO1_PRESS3_Msk      (0x7f000000UL)            /*!< PRESS3 (Bitfield-Mask: 0x7f)                          */
#define KEYSCAN_KB_INFO1_PRESS2_Pos      (16UL)                    /*!< PRESS2 (Bit 16)                                       */
#define KEYSCAN_KB_INFO1_PRESS2_Msk      (0x7f0000UL)              /*!< PRESS2 (Bitfield-Mask: 0x7f)                          */
#define KEYSCAN_KB_INFO1_PRESS1_Pos      (8UL)                     /*!< PRESS1 (Bit 8)                                        */
#define KEYSCAN_KB_INFO1_PRESS1_Msk      (0x7f00UL)                /*!< PRESS1 (Bitfield-Mask: 0x7f)                          */
#define KEYSCAN_KB_INFO1_PRESS0_Pos      (0UL)                     /*!< PRESS0 (Bit 0)                                        */
#define KEYSCAN_KB_INFO1_PRESS0_Msk      (0x7fUL)                  /*!< PRESS0 (Bitfield-Mask: 0x7f)                          */
/* =======================================================  KB_INFO2  ======================================================== */
#define KEYSCAN_KB_INFO2_VIO_INFO_Pos    (0UL)                     /*!< VIO_INFO (Bit 0)                                      */
#define KEYSCAN_KB_INFO2_VIO_INFO_Msk    (0x7ffUL)                 /*!< VIO_INFO (Bitfield-Mask: 0x7ff)                       */
/* ========================================================  KB_STS0  ======================================================== */
#define KEYSCAN_KB_STS0_KSTS0_Pos        (0UL)                     /*!< KSTS0 (Bit 0)                                         */
#define KEYSCAN_KB_STS0_KSTS0_Msk        (0xffffffffUL)            /*!< KSTS0 (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  KB_STS1  ======================================================== */
#define KEYSCAN_KB_STS1_KSTS1_Pos        (0UL)                     /*!< KSTS1 (Bit 0)                                         */
#define KEYSCAN_KB_STS1_KSTS1_Msk        (0xffffffffUL)            /*!< KSTS1 (Bitfield-Mask: 0xffffffff)                     */
/* ========================================================  KB_STS2  ======================================================== */
#define KEYSCAN_KB_STS2_KSTS2_Pos        (0UL)                     /*!< KSTS2 (Bit 0)                                         */
#define KEYSCAN_KB_STS2_KSTS2_Msk        (0xffffffffUL)            /*!< KSTS2 (Bitfield-Mask: 0xffffffff)                     */


/* =========================================================================================================================== */
/* ================                                        LEDC_CTRL                                         ================ */
/* =========================================================================================================================== */

/* =========================================================  CTRL0  ========================================================= */
#define LEDC_CTRL_CTRL0_LSB_FIRST_Pos    (4UL)                     /*!< LSB_FIRST (Bit 4)                                     */
#define LEDC_CTRL_CTRL0_LSB_FIRST_Msk    (0x10UL)                  /*!< LSB_FIRST (Bitfield-Mask: 0x01)                       */
#define LEDC_CTRL_CTRL0_LEVEL_INV_Pos    (3UL)                     /*!< LEVEL_INV (Bit 3)                                     */
#define LEDC_CTRL_CTRL0_LEVEL_INV_Msk    (0x8UL)                   /*!< LEVEL_INV (Bitfield-Mask: 0x01)                       */
#define LEDC_CTRL_CTRL0_LEVEL_INIT_Pos   (2UL)                     /*!< LEVEL_INIT (Bit 2)                                    */
#define LEDC_CTRL_CTRL0_LEVEL_INIT_Msk   (0x4UL)                   /*!< LEVEL_INIT (Bitfield-Mask: 0x01)                      */
#define LEDC_CTRL_CTRL0_LOOP_MODE_Pos    (1UL)                     /*!< LOOP_MODE (Bit 1)                                     */
#define LEDC_CTRL_CTRL0_LOOP_MODE_Msk    (0x2UL)                   /*!< LOOP_MODE (Bitfield-Mask: 0x01)                       */
#define LEDC_CTRL_CTRL0_DMA_EN_Pos       (0UL)                     /*!< DMA_EN (Bit 0)                                        */
#define LEDC_CTRL_CTRL0_DMA_EN_Msk       (0x1UL)                   /*!< DMA_EN (Bitfield-Mask: 0x01)                          */
/* =========================================================  CTRL1  ========================================================= */
#define LEDC_CTRL_CTRL1_DMA_STATE_Pos    (2UL)                     /*!< DMA_STATE (Bit 2)                                     */
#define LEDC_CTRL_CTRL1_DMA_STATE_Msk    (0x4UL)                   /*!< DMA_STATE (Bitfield-Mask: 0x01)                       */
#define LEDC_CTRL_CTRL1_DMA_STOP_Pos     (1UL)                     /*!< DMA_STOP (Bit 1)                                      */
#define LEDC_CTRL_CTRL1_DMA_STOP_Msk     (0x2UL)                   /*!< DMA_STOP (Bitfield-Mask: 0x01)                        */
#define LEDC_CTRL_CTRL1_DMA_START_Pos    (0UL)                     /*!< DMA_START (Bit 0)                                     */
#define LEDC_CTRL_CTRL1_DMA_START_Msk    (0x1UL)                   /*!< DMA_START (Bitfield-Mask: 0x01)                       */
/* =======================================================  TBL_SADDR  ======================================================= */
#define LEDC_CTRL_TBL_SADDR_TBL_SADDR_Pos (2UL)                    /*!< TBL_SADDR (Bit 2)                                     */
#define LEDC_CTRL_TBL_SADDR_TBL_SADDR_Msk (0xfffcUL)               /*!< TBL_SADDR (Bitfield-Mask: 0x3fff)                     */
/* =======================================================  TBL_EADDR  ======================================================= */
#define LEDC_CTRL_TBL_EADDR_TBL_EADDR_Pos (2UL)                    /*!< TBL_EADDR (Bit 2)                                     */
#define LEDC_CTRL_TBL_EADDR_TBL_EADDR_Msk (0xfffcUL)               /*!< TBL_EADDR (Bitfield-Mask: 0x3fff)                     */


/* =========================================================================================================================== */
/* ================                                        LEDC_MODU                                         ================ */
/* =========================================================================================================================== */

/* =======================================================  BIT0_MODU  ======================================================= */
#define LEDC_MODU_BIT0_MODU_B0_P1_POL_Pos (31UL)                   /*!< B0_P1_POL (Bit 31)                                    */
#define LEDC_MODU_BIT0_MODU_B0_P1_POL_Msk (0x80000000UL)           /*!< B0_P1_POL (Bitfield-Mask: 0x01)                       */
#define LEDC_MODU_BIT0_MODU_B0_P1_LEN_Pos (16UL)                   /*!< B0_P1_LEN (Bit 16)                                    */
#define LEDC_MODU_BIT0_MODU_B0_P1_LEN_Msk (0xfff0000UL)            /*!< B0_P1_LEN (Bitfield-Mask: 0xfff)                      */
#define LEDC_MODU_BIT0_MODU_B0_P0_POL_Pos (15UL)                   /*!< B0_P0_POL (Bit 15)                                    */
#define LEDC_MODU_BIT0_MODU_B0_P0_POL_Msk (0x8000UL)               /*!< B0_P0_POL (Bitfield-Mask: 0x01)                       */
#define LEDC_MODU_BIT0_MODU_B0_P0_LEN_Pos (0UL)                    /*!< B0_P0_LEN (Bit 0)                                     */
#define LEDC_MODU_BIT0_MODU_B0_P0_LEN_Msk (0xfffUL)                /*!< B0_P0_LEN (Bitfield-Mask: 0xfff)                      */
/* =======================================================  BIT1_MODU  ======================================================= */
#define LEDC_MODU_BIT1_MODU_B1_P1_POL_Pos (31UL)                   /*!< B1_P1_POL (Bit 31)                                    */
#define LEDC_MODU_BIT1_MODU_B1_P1_POL_Msk (0x80000000UL)           /*!< B1_P1_POL (Bitfield-Mask: 0x01)                       */
#define LEDC_MODU_BIT1_MODU_B1_P1_LEN_Pos (16UL)                   /*!< B1_P1_LEN (Bit 16)                                    */
#define LEDC_MODU_BIT1_MODU_B1_P1_LEN_Msk (0xfff0000UL)            /*!< B1_P1_LEN (Bitfield-Mask: 0xfff)                      */
#define LEDC_MODU_BIT1_MODU_B1_P0_POL_Pos (15UL)                   /*!< B1_P0_POL (Bit 15)                                    */
#define LEDC_MODU_BIT1_MODU_B1_P0_POL_Msk (0x8000UL)               /*!< B1_P0_POL (Bitfield-Mask: 0x01)                       */
#define LEDC_MODU_BIT1_MODU_B1_P0_LEN_Pos (0UL)                    /*!< B1_P0_LEN (Bit 0)                                     */
#define LEDC_MODU_BIT1_MODU_B1_P0_LEN_Msk (0xfffUL)                /*!< B1_P0_LEN (Bitfield-Mask: 0xfff)                      */


/* =========================================================================================================================== */
/* ================                                         LEDC_NUM                                         ================ */
/* =========================================================================================================================== */

/* ======================================================  CHANGE_NUM1  ====================================================== */
#define LEDC_NUM_CHANGE_NUM1_CHANGE_NUM1_Pos (0UL)                 /*!< CHANGE_NUM1 (Bit 0)                                   */
#define LEDC_NUM_CHANGE_NUM1_CHANGE_NUM1_Msk (0xfffUL)             /*!< CHANGE_NUM1 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  CHANGE_NUM2  ====================================================== */
#define LEDC_NUM_CHANGE_NUM2_CHANGE_NUM2_Pos (0UL)                 /*!< CHANGE_NUM2 (Bit 0)                                   */
#define LEDC_NUM_CHANGE_NUM2_CHANGE_NUM2_Msk (0xfffUL)             /*!< CHANGE_NUM2 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  CHANGE_NUM3  ====================================================== */
#define LEDC_NUM_CHANGE_NUM3_CHANGE_NUM3_Pos (0UL)                 /*!< CHANGE_NUM3 (Bit 0)                                   */
#define LEDC_NUM_CHANGE_NUM3_CHANGE_NUM3_Msk (0xfffUL)             /*!< CHANGE_NUM3 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  CHANGE_NUM4  ====================================================== */
#define LEDC_NUM_CHANGE_NUM4_CHANGE_NUM4_Pos (0UL)                 /*!< CHANGE_NUM4 (Bit 0)                                   */
#define LEDC_NUM_CHANGE_NUM4_CHANGE_NUM4_Msk (0xfffUL)             /*!< CHANGE_NUM4 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  CHANGE_NUM5  ====================================================== */
#define LEDC_NUM_CHANGE_NUM5_CHANGE_NUM5_Pos (0UL)                 /*!< CHANGE_NUM5 (Bit 0)                                   */
#define LEDC_NUM_CHANGE_NUM5_CHANGE_NUM5_Msk (0xfffUL)             /*!< CHANGE_NUM5 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  CHANGE_NUM6  ====================================================== */
#define LEDC_NUM_CHANGE_NUM6_CHANGE_NUM6_Pos (0UL)                 /*!< CHANGE_NUM6 (Bit 0)                                   */
#define LEDC_NUM_CHANGE_NUM6_CHANGE_NUM6_Msk (0xfffUL)             /*!< CHANGE_NUM6 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  REPEAT_NUM1  ====================================================== */
#define LEDC_NUM_REPEAT_NUM1_REPEAT_NUM1_Pos (0UL)                 /*!< REPEAT_NUM1 (Bit 0)                                   */
#define LEDC_NUM_REPEAT_NUM1_REPEAT_NUM1_Msk (0xfffUL)             /*!< REPEAT_NUM1 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  REPEAT_NUM2  ====================================================== */
#define LEDC_NUM_REPEAT_NUM2_REPEAT_NUM2_Pos (0UL)                 /*!< REPEAT_NUM2 (Bit 0)                                   */
#define LEDC_NUM_REPEAT_NUM2_REPEAT_NUM2_Msk (0xfffUL)             /*!< REPEAT_NUM2 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  REPEAT_NUM3  ====================================================== */
#define LEDC_NUM_REPEAT_NUM3_REPEAT_NUM3_Pos (0UL)                 /*!< REPEAT_NUM3 (Bit 0)                                   */
#define LEDC_NUM_REPEAT_NUM3_REPEAT_NUM3_Msk (0xfffUL)             /*!< REPEAT_NUM3 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  REPEAT_NUM4  ====================================================== */
#define LEDC_NUM_REPEAT_NUM4_REPEAT_NUM4_Pos (0UL)                 /*!< REPEAT_NUM4 (Bit 0)                                   */
#define LEDC_NUM_REPEAT_NUM4_REPEAT_NUM4_Msk (0xfffUL)             /*!< REPEAT_NUM4 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  REPEAT_NUM5  ====================================================== */
#define LEDC_NUM_REPEAT_NUM5_REPEAT_NUM5_Pos (0UL)                 /*!< REPEAT_NUM5 (Bit 0)                                   */
#define LEDC_NUM_REPEAT_NUM5_REPEAT_NUM5_Msk (0xfffUL)             /*!< REPEAT_NUM5 (Bitfield-Mask: 0xfff)                    */
/* ======================================================  REPEAT_NUM6  ====================================================== */
#define LEDC_NUM_REPEAT_NUM6_REPEAT_NUM6_Pos (0UL)                 /*!< REPEAT_NUM6 (Bit 0)                                   */
#define LEDC_NUM_REPEAT_NUM6_REPEAT_NUM6_Msk (0xfffUL)             /*!< REPEAT_NUM6 (Bitfield-Mask: 0xfff)                    */


/* =========================================================================================================================== */
/* ================                                         LEDC_IRQ                                         ================ */
/* =========================================================================================================================== */

/* ========================================================  DMA_IE  ========================================================= */
#define LEDC_IRQ_DMA_IE_DMA_IE_Pos       (0UL)                     /*!< DMA_IE (Bit 0)                                        */
#define LEDC_IRQ_DMA_IE_DMA_IE_Msk       (0x7UL)                   /*!< DMA_IE (Bitfield-Mask: 0x07)                          */
/* ========================================================  DMA_IS  ========================================================= */
#define LEDC_IRQ_DMA_IS_DMA_IS_Pos       (0UL)                     /*!< DMA_IS (Bit 0)                                        */
#define LEDC_IRQ_DMA_IS_DMA_IS_Msk       (0x7UL)                   /*!< DMA_IS (Bitfield-Mask: 0x07)                          */
/* ========================================================  DMA_MIS  ======================================================== */
#define LEDC_IRQ_DMA_MIS_DMA_MIS_Pos     (0UL)                     /*!< DMA_MIS (Bit 0)                                       */
#define LEDC_IRQ_DMA_MIS_DMA_MIS_Msk     (0x7UL)                   /*!< DMA_MIS (Bitfield-Mask: 0x07)                         */


/* =========================================================================================================================== */
/* ================                                       LEDC_STATUS                                        ================ */
/* =========================================================================================================================== */

/* =======================================================  TBL_ADDR  ======================================================== */
#define LEDC_STATUS_TBL_ADDR_TBL_ADDR_Pos (0UL)                    /*!< TBL_ADDR (Bit 0)                                      */
#define LEDC_STATUS_TBL_ADDR_TBL_ADDR_Msk (0xffffffffUL)           /*!< TBL_ADDR (Bitfield-Mask: 0xffffffff)                  */
/* =======================================================  DESC_ADDR  ======================================================= */
#define LEDC_STATUS_DESC_ADDR_DESC_ADDR_Pos (0UL)                  /*!< DESC_ADDR (Bit 0)                                     */
#define LEDC_STATUS_DESC_ADDR_DESC_ADDR_Msk (0xffffffffUL)         /*!< DESC_ADDR (Bitfield-Mask: 0xffffffff)                 */
/* =======================================================  DATA_ADDR  ======================================================= */
#define LEDC_STATUS_DATA_ADDR_DATA_ADDR_Pos (0UL)                  /*!< DATA_ADDR (Bit 0)                                     */
#define LEDC_STATUS_DATA_ADDR_DATA_ADDR_Msk (0xffffffffUL)         /*!< DATA_ADDR (Bitfield-Mask: 0xffffffff)                 */
/* ========================================================  STATUS  ========================================================= */
#define LEDC_STATUS_STATUS_STATUS_Pos    (0UL)                     /*!< STATUS (Bit 0)                                        */
#define LEDC_STATUS_STATUS_STATUS_Msk    (0xffffffffUL)            /*!< STATUS (Bitfield-Mask: 0xffffffff)                    */


/* =========================================================================================================================== */
/* ================                                         GPADC_ANA                                         ================ */
/* =========================================================================================================================== */

/* =======================================================  GPADC_EN  ======================================================== */
#define GPADC_ANA_GPADC_EN_DA_GPADC_EN_Pos (1UL)                    /*!< DA_GPADC_EN (Bit 1)                                   */
#define GPADC_ANA_GPADC_EN_DA_GPADC_EN_Msk (0x2UL)                  /*!< DA_GPADC_EN (Bitfield-Mask: 0x01)                     */
#define GPADC_ANA_GPADC_EN_DA_GPADC_PGA_EN_Pos (0UL)                /*!< DA_GPADC_PGA_EN (Bit 0)                               */
#define GPADC_ANA_GPADC_EN_DA_GPADC_PGA_EN_Msk (0x1UL)              /*!< DA_GPADC_PGA_EN (Bitfield-Mask: 0x01)                 */
/* ======================================================  GPADC_CTRL  ======================================================= */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_ATT_SEL_Pos (13UL)            /*!< RG_GPADC_ATT_SEL (Bit 13)                             */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_ATT_SEL_Msk (0x6000UL)        /*!< RG_GPADC_ATT_SEL (Bitfield-Mask: 0x03)                */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_DIFF_EN_Pos (12UL)            /*!< RG_GPADC_DIFF_EN (Bit 12)                             */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_DIFF_EN_Msk (0x1000UL)        /*!< RG_GPADC_DIFF_EN (Bitfield-Mask: 0x01)                */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_PGA_GC_Pos (8UL)              /*!< RG_GPADC_PGA_GC (Bit 8)                               */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_PGA_GC_Msk (0xf00UL)          /*!< RG_GPADC_PGA_GC (Bitfield-Mask: 0x0f)                 */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_VIN_SEL_Pos (4UL)             /*!< RG_GPADC_VIN_SEL (Bit 4)                              */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_VIN_SEL_Msk (0xf0UL)          /*!< RG_GPADC_VIN_SEL (Bitfield-Mask: 0x0f)                */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_VIP_SEL_Pos (0UL)             /*!< RG_GPADC_VIP_SEL (Bit 0)                              */
#define GPADC_ANA_GPADC_CTRL_RG_GPADC_VIP_SEL_Msk (0xfUL)           /*!< RG_GPADC_VIP_SEL (Bitfield-Mask: 0x0f)                */
/* =======================================================  GPADC_CFG  ======================================================= */
#define GPADC_ANA_GPADC_CFG_RG_GPADC_PGA_CM1_IBIAS_Pos (9UL)        /*!< RG_GPADC_PGA_CM1_IBIAS (Bit 9)                        */
#define GPADC_ANA_GPADC_CFG_RG_GPADC_PGA_CM1_IBIAS_Msk (0x600UL)    /*!< RG_GPADC_PGA_CM1_IBIAS (Bitfield-Mask: 0x03)          */
#define GPADC_ANA_GPADC_CFG_RG_GPADC_PGA_CM3_IBIAS_Pos (7UL)        /*!< RG_GPADC_PGA_CM3_IBIAS (Bit 7)                        */
#define GPADC_ANA_GPADC_CFG_RG_GPADC_PGA_CM3_IBIAS_Msk (0x180UL)    /*!< RG_GPADC_PGA_CM3_IBIAS (Bitfield-Mask: 0x03)          */
#define GPADC_ANA_GPADC_CFG_RG_GPADC_PGA_RS_Pos (3UL)               /*!< RG_GPADC_PGA_RS (Bit 3)                               */
#define GPADC_ANA_GPADC_CFG_RG_GPADC_PGA_RS_Msk (0x78UL)            /*!< RG_GPADC_PGA_RS (Bitfield-Mask: 0x0f)                 */
#define GPADC_ANA_GPADC_CFG_RG_GPADC_PGA_VCM_SEL_Pos (0UL)          /*!< RG_GPADC_PGA_VCM_SEL (Bit 0)                          */
#define GPADC_ANA_GPADC_CFG_RG_GPADC_PGA_VCM_SEL_Msk (0x7UL)        /*!< RG_GPADC_PGA_VCM_SEL (Bitfield-Mask: 0x07)            */


/* =========================================================================================================================== */
/* ================                                         GPADC_DIG                                         ================ */
/* =========================================================================================================================== */

/* =====================================================  GPADC_ACTION  ====================================================== */
#define GPADC_DIG_GPADC_ACTION_GPADC_TRIG_Pos (31UL)                /*!< GPADC_TRIG (Bit 31)                                   */
#define GPADC_DIG_GPADC_ACTION_GPADC_TRIG_Msk (0x80000000UL)        /*!< GPADC_TRIG (Bitfield-Mask: 0x01)                      */
#define GPADC_DIG_GPADC_ACTION_GPADC_WP_Pos (16UL)                  /*!< GPADC_WP (Bit 16)                                     */
#define GPADC_DIG_GPADC_ACTION_GPADC_WP_Msk (0x7ff0000UL)           /*!< GPADC_WP (Bitfield-Mask: 0x7ff)                       */
#define GPADC_DIG_GPADC_ACTION_GPADC_AVG_WIN_Pos (12UL)             /*!< GPADC_AVG_WIN (Bit 12)                                */
#define GPADC_DIG_GPADC_ACTION_GPADC_AVG_WIN_Msk (0xf000UL)         /*!< GPADC_AVG_WIN (Bitfield-Mask: 0x0f)                   */
#define GPADC_DIG_GPADC_ACTION_GPADC_TIMER_SEL_Pos (4UL)            /*!< GPADC_TIMER_SEL (Bit 4)                               */
#define GPADC_DIG_GPADC_ACTION_GPADC_TIMER_SEL_Msk (0x70UL)         /*!< GPADC_TIMER_SEL (Bitfield-Mask: 0x07)                 */
#define GPADC_DIG_GPADC_ACTION_GPADC_TIMER_MODE_Pos (3UL)           /*!< GPADC_TIMER_MODE (Bit 3)                              */
#define GPADC_DIG_GPADC_ACTION_GPADC_TIMER_MODE_Msk (0x8UL)         /*!< GPADC_TIMER_MODE (Bitfield-Mask: 0x01)                */
#define GPADC_DIG_GPADC_ACTION_GPADC_CONT_MODE_Pos (2UL)            /*!< GPADC_CONT_MODE (Bit 2)                               */
#define GPADC_DIG_GPADC_ACTION_GPADC_CONT_MODE_Msk (0x4UL)          /*!< GPADC_CONT_MODE (Bitfield-Mask: 0x01)                 */
#define GPADC_DIG_GPADC_ACTION_GPADC_SAMP_EN_Pos (1UL)              /*!< GPADC_SAMP_EN (Bit 1)                                 */
#define GPADC_DIG_GPADC_ACTION_GPADC_SAMP_EN_Msk (0x2UL)            /*!< GPADC_SAMP_EN (Bitfield-Mask: 0x01)                   */
#define GPADC_DIG_GPADC_ACTION_GPADC_DMA_EN_Pos (0UL)               /*!< GPADC_DMA_EN (Bit 0)                                  */
#define GPADC_DIG_GPADC_ACTION_GPADC_DMA_EN_Msk (0x1UL)             /*!< GPADC_DMA_EN (Bitfield-Mask: 0x01)                    */
/* =======================================================  GPADC_CFG  ======================================================= */
#define GPADC_DIG_GPADC_CFG_GPADC_INT_INTERVAL_Pos (8UL)            /*!< GPADC_INT_INTERVAL (Bit 8)                            */
#define GPADC_DIG_GPADC_CFG_GPADC_INT_INTERVAL_Msk (0xff00UL)       /*!< GPADC_INT_INTERVAL (Bitfield-Mask: 0xff)              */
#define GPADC_DIG_GPADC_CFG_GPADC_BK_NUM_Pos (6UL)                  /*!< GPADC_BK_NUM (Bit 6)                                  */
#define GPADC_DIG_GPADC_CFG_GPADC_BK_NUM_Msk (0xc0UL)               /*!< GPADC_BK_NUM (Bitfield-Mask: 0x03)                    */
#define GPADC_DIG_GPADC_CFG_GPADC_START_BK_Pos (4UL)                /*!< GPADC_START_BK (Bit 4)                                */
#define GPADC_DIG_GPADC_CFG_GPADC_START_BK_Msk (0x30UL)             /*!< GPADC_START_BK (Bitfield-Mask: 0x03)                  */
#define GPADC_DIG_GPADC_CFG_GPADC_SIGNEXT_Pos (2UL)                 /*!< GPADC_SIGNEXT (Bit 2)                                 */
#define GPADC_DIG_GPADC_CFG_GPADC_SIGNEXT_Msk (0x4UL)               /*!< GPADC_SIGNEXT (Bitfield-Mask: 0x01)                   */
#define GPADC_DIG_GPADC_CFG_GPADC_FORMAT_Pos (1UL)                  /*!< GPADC_FORMAT (Bit 1)                                  */
#define GPADC_DIG_GPADC_CFG_GPADC_FORMAT_Msk (0x2UL)                /*!< GPADC_FORMAT (Bitfield-Mask: 0x01)                    */
#define GPADC_DIG_GPADC_CFG_GPADC_STORE_MODE_Pos (0UL)              /*!< GPADC_STORE_MODE (Bit 0)                              */
#define GPADC_DIG_GPADC_CFG_GPADC_STORE_MODE_Msk (0x1UL)            /*!< GPADC_STORE_MODE (Bitfield-Mask: 0x01)                */
/* ====================================================  GPADC_INT_CTRL  ===================================================== */
#define GPADC_DIG_GPADC_INT_CTRL_GPADC_IE_Pos (16UL)                /*!< GPADC_IE (Bit 16)                                     */
#define GPADC_DIG_GPADC_INT_CTRL_GPADC_IE_Msk (0x30000UL)           /*!< GPADC_IE (Bitfield-Mask: 0x03)                        */
#define GPADC_DIG_GPADC_INT_CTRL_GPADC_MIS_Pos (8UL)                /*!< GPADC_MIS (Bit 8)                                     */
#define GPADC_DIG_GPADC_INT_CTRL_GPADC_MIS_Msk (0x300UL)            /*!< GPADC_MIS (Bitfield-Mask: 0x03)                       */
#define GPADC_DIG_GPADC_INT_CTRL_GPADC_IS_Pos (0UL)                 /*!< GPADC_IS (Bit 0)                                      */
#define GPADC_DIG_GPADC_INT_CTRL_GPADC_IS_Msk (0x3UL)               /*!< GPADC_IS (Bitfield-Mask: 0x03)                        */
#define GPADC_DIG_GPADC_INT_CTRL_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define GPADC_DIG_GPADC_INT_CTRL_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  GPADC_SAMP  ======================================================= */
#define GPADC_DIG_GPADC_SAMP_GPADC_SAMP_Pos (0UL)                   /*!< GPADC_SAMP (Bit 0)                                    */
#define GPADC_DIG_GPADC_SAMP_GPADC_SAMP_Msk (0xffffffffUL)          /*!< GPADC_SAMP (Bitfield-Mask: 0xffffffff)                */
/* ================================================  GPADC_CLK_CTRL_24_sub_0  ================================================ */
#define GPADC_DIG_GPADC_CLK_CTRL_24_sub_0_GPADC_CLK_CTRL_24_sub_field_0_Pos (0UL) /*!< GPADC_CLK_CTRL_24_sub_field_0 (Bit 0)   */
#define GPADC_DIG_GPADC_CLK_CTRL_24_sub_0_GPADC_CLK_CTRL_24_sub_field_0_Msk (0xffUL) /*!< GPADC_CLK_CTRL_24_sub_field_0 (Bitfield-Mask: 0xff) */
/* ================================================  GPADC_CLK_CTRL_24_sub_1  ================================================ */
#define GPADC_DIG_GPADC_CLK_CTRL_24_sub_1_GPADC_CLK_CTRL_24_sub_field_1_Pos (0UL) /*!< GPADC_CLK_CTRL_24_sub_field_1 (Bit 0)   */
#define GPADC_DIG_GPADC_CLK_CTRL_24_sub_1_GPADC_CLK_CTRL_24_sub_field_1_Msk (0xffUL) /*!< GPADC_CLK_CTRL_24_sub_field_1 (Bitfield-Mask: 0xff) */
/* ================================================  GPADC_CLK_CTRL_24_sub_2  ================================================ */
#define GPADC_DIG_GPADC_CLK_CTRL_24_sub_2_GPADC_CLK_CTRL_24_sub_field_2_Pos (0UL) /*!< GPADC_CLK_CTRL_24_sub_field_2 (Bit 0)   */
#define GPADC_DIG_GPADC_CLK_CTRL_24_sub_2_GPADC_CLK_CTRL_24_sub_field_2_Msk (0xffUL) /*!< GPADC_CLK_CTRL_24_sub_field_2 (Bitfield-Mask: 0xff) */


/* =========================================================================================================================== */
/* ================                                         AON_CTRL                                          ================ */
/* =========================================================================================================================== */

/* =======================================================  AON_CTRL0  ======================================================= */
#define AON_CTRL_AON_CTRL0_RET_OPEN_Pos   (4UL)                     /*!< RET_OPEN (Bit 4)                                      */
#define AON_CTRL_AON_CTRL0_RET_OPEN_Msk   (0xf0UL)                  /*!< RET_OPEN (Bitfield-Mask: 0x0f)                        */
#define AON_CTRL_AON_CTRL0_ISO_EN_Pos     (3UL)                     /*!< ISO_EN (Bit 3)                                        */
#define AON_CTRL_AON_CTRL0_ISO_EN_Msk     (0x8UL)                   /*!< ISO_EN (Bitfield-Mask: 0x01)                          */
#define AON_CTRL_AON_CTRL0_RET_EN_Pos     (2UL)                     /*!< RET_EN (Bit 2)                                        */
#define AON_CTRL_AON_CTRL0_RET_EN_Msk     (0x4UL)                   /*!< RET_EN (Bitfield-Mask: 0x01)                          */
#define AON_CTRL_AON_CTRL0_RET_MODE_Pos   (1UL)                     /*!< RET_MODE (Bit 1)                                      */
#define AON_CTRL_AON_CTRL0_RET_MODE_Msk   (0x2UL)                   /*!< RET_MODE (Bitfield-Mask: 0x01)                        */
#define AON_CTRL_AON_CTRL0_HOLD_MODE_Pos  (0UL)                     /*!< HOLD_MODE (Bit 0)                                     */
#define AON_CTRL_AON_CTRL0_HOLD_MODE_Msk  (0x1UL)                   /*!< HOLD_MODE (Bitfield-Mask: 0x01)                       */
/* ======================================================  SLEEP_TIME  ======================================================= */
#define AON_CTRL_SLEEP_TIME_SLEEP_TIME_Pos (0UL)                    /*!< SLEEP_TIME (Bit 0)                                    */
#define AON_CTRL_SLEEP_TIME_SLEEP_TIME_Msk (0xffffffffUL)           /*!< SLEEP_TIME (Bitfield-Mask: 0xffffffff)                */
/* =====================================================  WAKEUP_CTRL0  ====================================================== */
#define AON_CTRL_WAKEUP_CTRL0_GPIO_WAKEUP_EN_Pos (0UL)              /*!< GPIO_WAKEUP_EN (Bit 0)                                */
#define AON_CTRL_WAKEUP_CTRL0_GPIO_WAKEUP_EN_Msk (0xffffffUL)       /*!< GPIO_WAKEUP_EN (Bitfield-Mask: 0xffffff)              */
#define AON_CTRL_WAKEUP_CTRL0_RESERVE_Pos (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define AON_CTRL_WAKEUP_CTRL0_RESERVE_Msk (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =====================================================  WAKEUP_CTRL1  ====================================================== */
#define AON_CTRL_WAKEUP_CTRL1_GPION_WAKEUP_EN_Pos (0UL)             /*!< GPION_WAKEUP_EN (Bit 0)                               */
#define AON_CTRL_WAKEUP_CTRL1_GPION_WAKEUP_EN_Msk (0xffffffUL)      /*!< GPION_WAKEUP_EN (Bitfield-Mask: 0xffffff)             */
#define AON_CTRL_WAKEUP_CTRL1_RESERVE_Pos (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define AON_CTRL_WAKEUP_CTRL1_RESERVE_Msk (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =====================================================  WAKEUP_CLEAR  ====================================================== */
#define AON_CTRL_WAKEUP_CLEAR_WAKEUP_AUTOCLEAR_Pos (24UL)           /*!< WAKEUP_AUTOCLEAR (Bit 24)                             */
#define AON_CTRL_WAKEUP_CLEAR_WAKEUP_AUTOCLEAR_Msk (0x1000000UL)    /*!< WAKEUP_AUTOCLEAR (Bitfield-Mask: 0x01)                */
#define AON_CTRL_WAKEUP_CLEAR_WAKEUP_CLEAR_Pos (0UL)                /*!< WAKEUP_CLEAR (Bit 0)                                  */
#define AON_CTRL_WAKEUP_CLEAR_WAKEUP_CLEAR_Msk (0xffffffUL)         /*!< WAKEUP_CLEAR (Bitfield-Mask: 0xffffff)                */
/* =====================================================  WAKEUP_RECORD  ===================================================== */
#define AON_CTRL_WAKEUP_RECORD_WAKEUP_RECORD_Pos (0UL)              /*!< WAKEUP_RECORD (Bit 0)                                 */
#define AON_CTRL_WAKEUP_RECORD_WAKEUP_RECORD_Msk (0xffffffUL)       /*!< WAKEUP_RECORD (Bitfield-Mask: 0xffffff)               */
#define AON_CTRL_WAKEUP_RECORD_RESERVE_Pos (24UL)                   /*!< RESERVE (Bit 24)                                      */
#define AON_CTRL_WAKEUP_RECORD_RESERVE_Msk (0xff000000UL)           /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =======================================================  QSPI_CTRL  ======================================================= */
#define AON_CTRL_QSPI_CTRL_REG_ADDR_MODE_Pos (16UL)                 /*!< REG_ADDR_MODE (Bit 16)                                */
#define AON_CTRL_QSPI_CTRL_REG_ADDR_MODE_Msk (0x10000UL)            /*!< REG_ADDR_MODE (Bitfield-Mask: 0x01)                   */
#define AON_CTRL_QSPI_CTRL_REG_ADDR_DUMMY_Pos (8UL)                 /*!< REG_ADDR_DUMMY (Bit 8)                                */
#define AON_CTRL_QSPI_CTRL_REG_ADDR_DUMMY_Msk (0x3f00UL)            /*!< REG_ADDR_DUMMY (Bitfield-Mask: 0x3f)                  */
#define AON_CTRL_QSPI_CTRL_REG_CMD_DUMMY_Pos (0UL)                  /*!< REG_CMD_DUMMY (Bit 0)                                 */
#define AON_CTRL_QSPI_CTRL_REG_CMD_DUMMY_Msk (0x1fUL)               /*!< REG_CMD_DUMMY (Bitfield-Mask: 0x1f)                   */
#define AON_CTRL_QSPI_CTRL_RESERVE_Pos    (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define AON_CTRL_QSPI_CTRL_RESERVE_Msk    (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* =====================================================  QSPI_CMD_CFG  ====================================================== */
#define AON_CTRL_QSPI_CMD_CFG_REG_CMD_CODE_RD_Pos (8UL)             /*!< REG_CMD_CODE_RD (Bit 8)                               */
#define AON_CTRL_QSPI_CMD_CFG_REG_CMD_CODE_RD_Msk (0xff00UL)        /*!< REG_CMD_CODE_RD (Bitfield-Mask: 0xff)                 */
#define AON_CTRL_QSPI_CMD_CFG_REG_CMD_TYPE_RD_Pos (0UL)             /*!< REG_CMD_TYPE_RD (Bit 0)                               */
#define AON_CTRL_QSPI_CMD_CFG_REG_CMD_TYPE_RD_Msk (0xfUL)           /*!< REG_CMD_TYPE_RD (Bitfield-Mask: 0x0f)                 */
/* =====================================================  SET_SCAN_MODE  ===================================================== */
#define AON_CTRL_SET_SCAN_MODE_SET_SCAN_MODE_Pos (0UL)              /*!< SET_SCAN_MODE (Bit 0)                                 */
#define AON_CTRL_SET_SCAN_MODE_SET_SCAN_MODE_Msk (0x1UL)            /*!< SET_SCAN_MODE (Bitfield-Mask: 0x01)                   */
/* ========================================================  GOSLEEP  ======================================================== */
#define AON_CTRL_GOSLEEP_GOSLEEP_Pos      (0UL)                     /*!< GOSLEEP (Bit 0)                                       */
#define AON_CTRL_GOSLEEP_GOSLEEP_Msk      (0x1UL)                   /*!< GOSLEEP (Bitfield-Mask: 0x01)                         */
/* =======================================================  GPIO_HOLD  ======================================================= */
#define AON_CTRL_GPIO_HOLD_GPIO_HOLD_Pos  (0UL)                     /*!< GPIO_HOLD (Bit 0)                                     */
#define AON_CTRL_GPIO_HOLD_GPIO_HOLD_Msk  (0x1UL)                   /*!< GPIO_HOLD (Bitfield-Mask: 0x01)                       */
/* =======================================================  RTC_CTRL  ======================================================== */
#define AON_CTRL_RTC_CTRL_RTC_SUB_Pos     (3UL)                     /*!< RTC_SUB (Bit 3)                                       */
#define AON_CTRL_RTC_CTRL_RTC_SUB_Msk     (0x8UL)                   /*!< RTC_SUB (Bitfield-Mask: 0x01)                         */
#define AON_CTRL_RTC_CTRL_RTC_ADD_Pos     (2UL)                     /*!< RTC_ADD (Bit 2)                                       */
#define AON_CTRL_RTC_CTRL_RTC_ADD_Msk     (0x4UL)                   /*!< RTC_ADD (Bitfield-Mask: 0x01)                         */
#define AON_CTRL_RTC_CTRL_RTC_LD_Pos      (1UL)                     /*!< RTC_LD (Bit 1)                                        */
#define AON_CTRL_RTC_CTRL_RTC_LD_Msk      (0x2UL)                   /*!< RTC_LD (Bitfield-Mask: 0x01)                          */
#define AON_CTRL_RTC_CTRL_RTC_EN_Pos      (0UL)                     /*!< RTC_EN (Bit 0)                                        */
#define AON_CTRL_RTC_CTRL_RTC_EN_Msk      (0x1UL)                   /*!< RTC_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  RTC_VAL  ======================================================== */
#define AON_CTRL_RTC_VAL_RTC_VAL_Pos      (0UL)                     /*!< RTC_VAL (Bit 0)                                       */
#define AON_CTRL_RTC_VAL_RTC_VAL_Msk      (0xffffffffUL)            /*!< RTC_VAL (Bitfield-Mask: 0xffffffff)                   */
/* =======================================================  KB_WKUP0  ======================================================== */
#define AON_CTRL_KB_WKUP0_SCAN_DLY_Pos    (24UL)                    /*!< SCAN_DLY (Bit 24)                                     */
#define AON_CTRL_KB_WKUP0_SCAN_DLY_Msk    (0xff000000UL)            /*!< SCAN_DLY (Bitfield-Mask: 0xff)                        */
#define AON_CTRL_KB_WKUP0_OUT_DLY_Pos     (16UL)                    /*!< OUT_DLY (Bit 16)                                      */
#define AON_CTRL_KB_WKUP0_OUT_DLY_Msk     (0xff0000UL)              /*!< OUT_DLY (Bitfield-Mask: 0xff)                         */
#define AON_CTRL_KB_WKUP0_FILT_NUM_Pos    (12UL)                    /*!< FILT_NUM (Bit 12)                                     */
#define AON_CTRL_KB_WKUP0_FILT_NUM_Msk    (0xf000UL)                /*!< FILT_NUM (Bitfield-Mask: 0x0f)                        */
#define AON_CTRL_KB_WKUP0_A3_SIZE_Pos     (8UL)                     /*!< A3_SIZE (Bit 8)                                       */
#define AON_CTRL_KB_WKUP0_A3_SIZE_Msk     (0xf00UL)                 /*!< A3_SIZE (Bitfield-Mask: 0x0f)                         */
#define AON_CTRL_KB_WKUP0_A3_POLAR_Pos    (7UL)                     /*!< A3_POLAR (Bit 7)                                      */
#define AON_CTRL_KB_WKUP0_A3_POLAR_Msk    (0x80UL)                  /*!< A3_POLAR (Bitfield-Mask: 0x01)                        */
#define AON_CTRL_KB_WKUP0_A3_ARCH_Pos     (6UL)                     /*!< A3_ARCH (Bit 6)                                       */
#define AON_CTRL_KB_WKUP0_A3_ARCH_Msk     (0x40UL)                  /*!< A3_ARCH (Bitfield-Mask: 0x01)                         */
#define AON_CTRL_KB_WKUP0_IDLE_PU_Pos     (5UL)                     /*!< IDLE_PU (Bit 5)                                       */
#define AON_CTRL_KB_WKUP0_IDLE_PU_Msk     (0x20UL)                  /*!< IDLE_PU (Bitfield-Mask: 0x01)                         */
#define AON_CTRL_KB_WKUP0_IDLE_PD_Pos     (4UL)                     /*!< IDLE_PD (Bit 4)                                       */
#define AON_CTRL_KB_WKUP0_IDLE_PD_Msk     (0x10UL)                  /*!< IDLE_PD (Bitfield-Mask: 0x01)                         */
#define AON_CTRL_KB_WKUP0_SCAN_AREA_Pos   (0UL)                     /*!< SCAN_AREA (Bit 0)                                     */
#define AON_CTRL_KB_WKUP0_SCAN_AREA_Msk   (0x7UL)                   /*!< SCAN_AREA (Bitfield-Mask: 0x07)                       */
/* =======================================================  KB_WKUP1  ======================================================== */
#define AON_CTRL_KB_WKUP1_KB_IE_Pos       (13UL)                    /*!< KB_IE (Bit 13)                                        */
#define AON_CTRL_KB_WKUP1_KB_IE_Msk       (0x2000UL)                /*!< KB_IE (Bitfield-Mask: 0x01)                           */
#define AON_CTRL_KB_WKUP1_KB_ODE_Pos      (12UL)                    /*!< KB_ODE (Bit 12)                                       */
#define AON_CTRL_KB_WKUP1_KB_ODE_Msk      (0x1000UL)                /*!< KB_ODE (Bitfield-Mask: 0x01)                          */
#define AON_CTRL_KB_WKUP1_KB_DS_Pos       (10UL)                    /*!< KB_DS (Bit 10)                                        */
#define AON_CTRL_KB_WKUP1_KB_DS_Msk       (0xc00UL)                 /*!< KB_DS (Bitfield-Mask: 0x03)                           */
#define AON_CTRL_KB_WKUP1_MUX_SEL_Pos     (8UL)                     /*!< MUX_SEL (Bit 8)                                       */
#define AON_CTRL_KB_WKUP1_MUX_SEL_Msk     (0x300UL)                 /*!< MUX_SEL (Bitfield-Mask: 0x03)                         */
#define AON_CTRL_KB_WKUP1_SCAN_SEL_Pos    (1UL)                     /*!< SCAN_SEL (Bit 1)                                      */
#define AON_CTRL_KB_WKUP1_SCAN_SEL_Msk    (0x2UL)                   /*!< SCAN_SEL (Bitfield-Mask: 0x01)                        */
#define AON_CTRL_KB_WKUP1_SCAN_EN_Pos     (0UL)                     /*!< SCAN_EN (Bit 0)                                       */
#define AON_CTRL_KB_WKUP1_SCAN_EN_Msk     (0x1UL)                   /*!< SCAN_EN (Bitfield-Mask: 0x01)                         */
/* ========================================================  KB_STS  ========================================================= */
#define AON_CTRL_KB_STS_KB_WKUP_STS_Pos   (0UL)                     /*!< KB_WKUP_STS (Bit 0)                                   */
#define AON_CTRL_KB_STS_KB_WKUP_STS_Msk   (0x1UL)                   /*!< KB_WKUP_STS (Bitfield-Mask: 0x01)                     */
/* ======================================================  CPU_RST_RCD  ====================================================== */
#define AON_CTRL_CPU_RST_RCD_CPU_RST_RCD_Pos (0UL)                  /*!< CPU_RST_RCD (Bit 0)                                   */
#define AON_CTRL_CPU_RST_RCD_CPU_RST_RCD_Msk (0x3ffUL)              /*!< CPU_RST_RCD (Bitfield-Mask: 0x3ff)                    */
/* ======================================================  CPU_RST_CLR  ====================================================== */
#define AON_CTRL_CPU_RST_CLR_CPU_RST_CLR_Pos (0UL)                  /*!< CPU_RST_CLR (Bit 0)                                   */
#define AON_CTRL_CPU_RST_CLR_CPU_RST_CLR_Msk (0x3ffUL)              /*!< CPU_RST_CLR (Bitfield-Mask: 0x3ff)                    */
/* ====================================================  RST_IGNORE_CTRL  ==================================================== */
#define AON_CTRL_RST_IGNORE_CTRL_RST_IGNORE_CTRL_Pos (0UL)          /*!< RST_IGNORE_CTRL (Bit 0)                               */
#define AON_CTRL_RST_IGNORE_CTRL_RST_IGNORE_CTRL_Msk (0x3fUL)       /*!< RST_IGNORE_CTRL (Bitfield-Mask: 0x3f)                 */
/* =====================================================  SOFT_RECORD4  ====================================================== */
#define AON_CTRL_SOFT_RECORD4_SOFT_RECORD4_Pos (0UL)                /*!< SOFT_RECORD4 (Bit 0)                                  */
#define AON_CTRL_SOFT_RECORD4_SOFT_RECORD4_Msk (0xffffffffUL)       /*!< SOFT_RECORD4 (Bitfield-Mask: 0xffffffff)              */
/* =====================================================  SOFT_RECORD6  ====================================================== */
#define AON_CTRL_SOFT_RECORD6_SOFT_RECORD5_Pos (0UL)                /*!< SOFT_RECORD5 (Bit 0)                                  */
#define AON_CTRL_SOFT_RECORD6_SOFT_RECORD5_Msk (0xffffffffUL)       /*!< SOFT_RECORD5 (Bitfield-Mask: 0xffffffff)              */
/* ======================================================  RCO24M_CFG  ======================================================= */
#define AON_CTRL_RCO24M_CFG_AON_RCO24M_CC_XO_SU_Pos (16UL)          /*!< AON_RCO24M_CC_XO_SU (Bit 16)                          */
#define AON_CTRL_RCO24M_CFG_AON_RCO24M_CC_XO_SU_Msk (0xff0000UL)    /*!< AON_RCO24M_CC_XO_SU (Bitfield-Mask: 0xff)             */
#define AON_CTRL_RCO24M_CFG_AON_RCO24M_CC_Pos (8UL)                 /*!< AON_RCO24M_CC (Bit 8)                                 */
#define AON_CTRL_RCO24M_CFG_AON_RCO24M_CC_Msk (0xff00UL)            /*!< AON_RCO24M_CC (Bitfield-Mask: 0xff)                   */
#define AON_CTRL_RCO24M_CFG_AON_RG_RCO24M_CMP_HP_Pos (7UL)          /*!< AON_RG_RCO24M_CMP_HP (Bit 7)                          */
#define AON_CTRL_RCO24M_CFG_AON_RG_RCO24M_CMP_HP_Msk (0x80UL)       /*!< AON_RG_RCO24M_CMP_HP (Bitfield-Mask: 0x01)            */
#define AON_CTRL_RCO24M_CFG_AON_RG_RCO24M_FREQ_SEL_Pos (4UL)        /*!< AON_RG_RCO24M_FREQ_SEL (Bit 4)                        */
#define AON_CTRL_RCO24M_CFG_AON_RG_RCO24M_FREQ_SEL_Msk (0x70UL)     /*!< AON_RG_RCO24M_FREQ_SEL (Bitfield-Mask: 0x07)          */
#define AON_CTRL_RCO24M_CFG_AON_RG_RCO24M_TCC_Pos (0UL)             /*!< AON_RG_RCO24M_TCC (Bit 0)                             */
#define AON_CTRL_RCO24M_CFG_AON_RG_RCO24M_TCC_Msk (0xfUL)           /*!< AON_RG_RCO24M_TCC (Bitfield-Mask: 0x0f)               */
#define AON_CTRL_RCO24M_CFG_RESERVE_Pos   (24UL)                    /*!< RESERVE (Bit 24)                                      */
#define AON_CTRL_RCO24M_CFG_RESERVE_Msk   (0xff000000UL)            /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  RCO32K_CFG  ======================================================= */
#define AON_CTRL_RCO32K_CFG_AON_RG_RCO32K_CC_Pos (7UL)              /*!< AON_RG_RCO32K_CC (Bit 7)                              */
#define AON_CTRL_RCO32K_CFG_AON_RG_RCO32K_CC_Msk (0x7f80UL)         /*!< AON_RG_RCO32K_CC (Bitfield-Mask: 0xff)                */
#define AON_CTRL_RCO32K_CFG_AON_RG_RCO32K_CMP_HP_Pos (6UL)          /*!< AON_RG_RCO32K_CMP_HP (Bit 6)                          */
#define AON_CTRL_RCO32K_CFG_AON_RG_RCO32K_CMP_HP_Msk (0x40UL)       /*!< AON_RG_RCO32K_CMP_HP (Bitfield-Mask: 0x01)            */
#define AON_CTRL_RCO32K_CFG_AON_RG_RCO32K_IC_Pos (4UL)              /*!< AON_RG_RCO32K_IC (Bit 4)                              */
#define AON_CTRL_RCO32K_CFG_AON_RG_RCO32K_IC_Msk (0x30UL)           /*!< AON_RG_RCO32K_IC (Bitfield-Mask: 0x03)                */
#define AON_CTRL_RCO32K_CFG_AON_RG_RCO32K_TCC_Pos (0UL)             /*!< AON_RG_RCO32K_TCC (Bit 0)                             */
#define AON_CTRL_RCO32K_CFG_AON_RG_RCO32K_TCC_Msk (0xfUL)           /*!< AON_RG_RCO32K_TCC (Bitfield-Mask: 0x0f)               */
/* ====================================================  XO_CFG_24_sub_0  ==================================================== */
#define AON_CTRL_XO_CFG_24_sub_0_XO_CFG_24_sub_field_0_Pos (0UL)    /*!< XO_CFG_24_sub_field_0 (Bit 0)                         */
#define AON_CTRL_XO_CFG_24_sub_0_XO_CFG_24_sub_field_0_Msk (0xffUL) /*!< XO_CFG_24_sub_field_0 (Bitfield-Mask: 0xff)           */
/* ====================================================  XO_CFG_24_sub_1  ==================================================== */
#define AON_CTRL_XO_CFG_24_sub_1_XO_CFG_24_sub_field_1_Pos (0UL)    /*!< XO_CFG_24_sub_field_1 (Bit 0)                         */
#define AON_CTRL_XO_CFG_24_sub_1_XO_CFG_24_sub_field_1_Msk (0xffUL) /*!< XO_CFG_24_sub_field_1 (Bitfield-Mask: 0xff)           */
/* ====================================================  XO_CFG_24_sub_2  ==================================================== */
#define AON_CTRL_XO_CFG_24_sub_2_XO_CFG_24_sub_field_2_Pos (0UL)    /*!< XO_CFG_24_sub_field_2 (Bit 0)                         */
#define AON_CTRL_XO_CFG_24_sub_2_XO_CFG_24_sub_field_2_Msk (0xffUL) /*!< XO_CFG_24_sub_field_2 (Bitfield-Mask: 0xff)           */


/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  RBR  ========================================================== */
#define UART_RBR_RBR_Pos                  (0UL)                     /*!< RBR (Bit 0)                                           */
#define UART_RBR_RBR_Msk                  (0x1ffUL)                 /*!< RBR (Bitfield-Mask: 0x1ff)                            */
/* ==========================================================  THR  ========================================================== */
#define UART_THR_THR_Pos                  (0UL)                     /*!< THR (Bit 0)                                           */
#define UART_THR_THR_Msk                  (0x1ffUL)                 /*!< THR (Bitfield-Mask: 0x1ff)                            */
/* ==========================================================  DLL  ========================================================== */
#define UART_DLL_DLL_Pos                  (0UL)                     /*!< DLL (Bit 0)                                           */
#define UART_DLL_DLL_Msk                  (0xffUL)                  /*!< DLL (Bitfield-Mask: 0xff)                             */
/* ==========================================================  DLH  ========================================================== */
#define UART_DLH_DLH_Pos                  (0UL)                     /*!< DLH (Bit 0)                                           */
#define UART_DLH_DLH_Msk                  (0xffUL)                  /*!< DLH (Bitfield-Mask: 0xff)                             */
/* ==========================================================  IER  ========================================================== */
#define UART_IER_PTME_Pos                 (7UL)                     /*!< PTME (Bit 7)                                          */
#define UART_IER_PTME_Msk                 (0x80UL)                  /*!< PTME (Bitfield-Mask: 0x01)                            */
#define UART_IER_ELCOLR_Pos               (4UL)                     /*!< ELCOLR (Bit 4)                                        */
#define UART_IER_ELCOLR_Msk               (0x10UL)                  /*!< ELCOLR (Bitfield-Mask: 0x01)                          */
#define UART_IER_EDSSI_Pos                (3UL)                     /*!< EDSSI (Bit 3)                                         */
#define UART_IER_EDSSI_Msk                (0x8UL)                   /*!< EDSSI (Bitfield-Mask: 0x01)                           */
#define UART_IER_ELSI_Pos                 (2UL)                     /*!< ELSI (Bit 2)                                          */
#define UART_IER_ELSI_Msk                 (0x4UL)                   /*!< ELSI (Bitfield-Mask: 0x01)                            */
#define UART_IER_ETBEI_Pos                (1UL)                     /*!< ETBEI (Bit 1)                                         */
#define UART_IER_ETBEI_Msk                (0x2UL)                   /*!< ETBEI (Bitfield-Mask: 0x01)                           */
#define UART_IER_ERBFI_Pos                (0UL)                     /*!< ERBFI (Bit 0)                                         */
#define UART_IER_ERBFI_Msk                (0x1UL)                   /*!< ERBFI (Bitfield-Mask: 0x01)                           */
/* ==========================================================  IIR  ========================================================== */
#define UART_IIR_FIFOSE_Pos               (6UL)                     /*!< FIFOSE (Bit 6)                                        */
#define UART_IIR_FIFOSE_Msk               (0xc0UL)                  /*!< FIFOSE (Bitfield-Mask: 0x03)                          */
#define UART_IIR_IID_Pos                  (0UL)                     /*!< IID (Bit 0)                                           */
#define UART_IIR_IID_Msk                  (0xfUL)                   /*!< IID (Bitfield-Mask: 0x0f)                             */
/* ==========================================================  FCR  ========================================================== */
#define UART_FCR_RT_Pos                   (6UL)                     /*!< RT (Bit 6)                                            */
#define UART_FCR_RT_Msk                   (0xc0UL)                  /*!< RT (Bitfield-Mask: 0x03)                              */
#define UART_FCR_TET_Pos                  (4UL)                     /*!< TET (Bit 4)                                           */
#define UART_FCR_TET_Msk                  (0x30UL)                  /*!< TET (Bitfield-Mask: 0x03)                             */
#define UART_FCR_DMAM_Pos                 (3UL)                     /*!< DMAM (Bit 3)                                          */
#define UART_FCR_DMAM_Msk                 (0x8UL)                   /*!< DMAM (Bitfield-Mask: 0x01)                            */
#define UART_FCR_XFIFOR_Pos               (2UL)                     /*!< XFIFOR (Bit 2)                                        */
#define UART_FCR_XFIFOR_Msk               (0x4UL)                   /*!< XFIFOR (Bitfield-Mask: 0x01)                          */
#define UART_FCR_RFIFOR_Pos               (1UL)                     /*!< RFIFOR (Bit 1)                                        */
#define UART_FCR_RFIFOR_Msk               (0x2UL)                   /*!< RFIFOR (Bitfield-Mask: 0x01)                          */
#define UART_FCR_FIFOE_Pos                (0UL)                     /*!< FIFOE (Bit 0)                                         */
#define UART_FCR_FIFOE_Msk                (0x1UL)                   /*!< FIFOE (Bitfield-Mask: 0x01)                           */
/* ==========================================================  LCR  ========================================================== */
#define UART_LCR_DLAB_Pos                 (7UL)                     /*!< DLAB (Bit 7)                                          */
#define UART_LCR_DLAB_Msk                 (0x80UL)                  /*!< DLAB (Bitfield-Mask: 0x01)                            */
#define UART_LCR_BC_Pos                   (6UL)                     /*!< BC (Bit 6)                                            */
#define UART_LCR_BC_Msk                   (0x40UL)                  /*!< BC (Bitfield-Mask: 0x01)                              */
#define UART_LCR_SP_Pos                   (5UL)                     /*!< SP (Bit 5)                                            */
#define UART_LCR_SP_Msk                   (0x20UL)                  /*!< SP (Bitfield-Mask: 0x01)                              */
#define UART_LCR_EPS_Pos                  (4UL)                     /*!< EPS (Bit 4)                                           */
#define UART_LCR_EPS_Msk                  (0x10UL)                  /*!< EPS (Bitfield-Mask: 0x01)                             */
#define UART_LCR_PEN_Pos                  (3UL)                     /*!< PEN (Bit 3)                                           */
#define UART_LCR_PEN_Msk                  (0x8UL)                   /*!< PEN (Bitfield-Mask: 0x01)                             */
#define UART_LCR_STOP_Pos                 (2UL)                     /*!< STOP (Bit 2)                                          */
#define UART_LCR_STOP_Msk                 (0x4UL)                   /*!< STOP (Bitfield-Mask: 0x01)                            */
#define UART_LCR_DLS_Pos                  (0UL)                     /*!< DLS (Bit 0)                                           */
#define UART_LCR_DLS_Msk                  (0x3UL)                   /*!< DLS (Bitfield-Mask: 0x03)                             */
/* ==========================================================  MCR  ========================================================== */
#define UART_MCR_AFCE_Pos                 (5UL)                     /*!< AFCE (Bit 5)                                          */
#define UART_MCR_AFCE_Msk                 (0x20UL)                  /*!< AFCE (Bitfield-Mask: 0x01)                            */
#define UART_MCR_LOOPBACK_Pos             (4UL)                     /*!< LOOPBACK (Bit 4)                                      */
#define UART_MCR_LOOPBACK_Msk             (0x10UL)                  /*!< LOOPBACK (Bitfield-Mask: 0x01)                        */
#define UART_MCR_OUT2_Pos                 (3UL)                     /*!< OUT2 (Bit 3)                                          */
#define UART_MCR_OUT2_Msk                 (0x8UL)                   /*!< OUT2 (Bitfield-Mask: 0x01)                            */
#define UART_MCR_OUT1_Pos                 (2UL)                     /*!< OUT1 (Bit 2)                                          */
#define UART_MCR_OUT1_Msk                 (0x4UL)                   /*!< OUT1 (Bitfield-Mask: 0x01)                            */
#define UART_MCR_RTS_Pos                  (1UL)                     /*!< RTS (Bit 1)                                           */
#define UART_MCR_RTS_Msk                  (0x2UL)                   /*!< RTS (Bitfield-Mask: 0x01)                             */
#define UART_MCR_DTR_Pos                  (0UL)                     /*!< DTR (Bit 0)                                           */
#define UART_MCR_DTR_Msk                  (0x1UL)                   /*!< DTR (Bitfield-Mask: 0x01)                             */
/* ==========================================================  LSR  ========================================================== */
#define UART_LSR_ADDR_RCVD_Pos            (8UL)                     /*!< ADDR_RCVD (Bit 8)                                     */
#define UART_LSR_ADDR_RCVD_Msk            (0x100UL)                 /*!< ADDR_RCVD (Bitfield-Mask: 0x01)                       */
#define UART_LSR_RFE_Pos                  (7UL)                     /*!< RFE (Bit 7)                                           */
#define UART_LSR_RFE_Msk                  (0x80UL)                  /*!< RFE (Bitfield-Mask: 0x01)                             */
#define UART_LSR_TEMT_Pos                 (6UL)                     /*!< TEMT (Bit 6)                                          */
#define UART_LSR_TEMT_Msk                 (0x40UL)                  /*!< TEMT (Bitfield-Mask: 0x01)                            */
#define UART_LSR_THRE_Pos                 (5UL)                     /*!< THRE (Bit 5)                                          */
#define UART_LSR_THRE_Msk                 (0x20UL)                  /*!< THRE (Bitfield-Mask: 0x01)                            */
#define UART_LSR_BI_Pos                   (4UL)                     /*!< BI (Bit 4)                                            */
#define UART_LSR_BI_Msk                   (0x10UL)                  /*!< BI (Bitfield-Mask: 0x01)                              */
#define UART_LSR_FE_Pos                   (3UL)                     /*!< FE (Bit 3)                                            */
#define UART_LSR_FE_Msk                   (0x8UL)                   /*!< FE (Bitfield-Mask: 0x01)                              */
#define UART_LSR_PE_Pos                   (2UL)                     /*!< PE (Bit 2)                                            */
#define UART_LSR_PE_Msk                   (0x4UL)                   /*!< PE (Bitfield-Mask: 0x01)                              */
#define UART_LSR_OE_Pos                   (1UL)                     /*!< OE (Bit 1)                                            */
#define UART_LSR_OE_Msk                   (0x2UL)                   /*!< OE (Bitfield-Mask: 0x01)                              */
#define UART_LSR_DR_Pos                   (0UL)                     /*!< DR (Bit 0)                                            */
#define UART_LSR_DR_Msk                   (0x1UL)                   /*!< DR (Bitfield-Mask: 0x01)                              */
/* ==========================================================  MSR  ========================================================== */
#define UART_MSR_DCD_Pos                  (7UL)                     /*!< DCD (Bit 7)                                           */
#define UART_MSR_DCD_Msk                  (0x80UL)                  /*!< DCD (Bitfield-Mask: 0x01)                             */
#define UART_MSR_RI_Pos                   (6UL)                     /*!< RI (Bit 6)                                            */
#define UART_MSR_RI_Msk                   (0x40UL)                  /*!< RI (Bitfield-Mask: 0x01)                              */
#define UART_MSR_DSR_Pos                  (5UL)                     /*!< DSR (Bit 5)                                           */
#define UART_MSR_DSR_Msk                  (0x20UL)                  /*!< DSR (Bitfield-Mask: 0x01)                             */
#define UART_MSR_CTS_Pos                  (4UL)                     /*!< CTS (Bit 4)                                           */
#define UART_MSR_CTS_Msk                  (0x10UL)                  /*!< CTS (Bitfield-Mask: 0x01)                             */
#define UART_MSR_DDCD_Pos                 (3UL)                     /*!< DDCD (Bit 3)                                          */
#define UART_MSR_DDCD_Msk                 (0x8UL)                   /*!< DDCD (Bitfield-Mask: 0x01)                            */
#define UART_MSR_TERI_Pos                 (2UL)                     /*!< TERI (Bit 2)                                          */
#define UART_MSR_TERI_Msk                 (0x4UL)                   /*!< TERI (Bitfield-Mask: 0x01)                            */
#define UART_MSR_DDSR_Pos                 (1UL)                     /*!< DDSR (Bit 1)                                          */
#define UART_MSR_DDSR_Msk                 (0x2UL)                   /*!< DDSR (Bitfield-Mask: 0x01)                            */
#define UART_MSR_DCTS_Pos                 (0UL)                     /*!< DCTS (Bit 0)                                          */
#define UART_MSR_DCTS_Msk                 (0x1UL)                   /*!< DCTS (Bitfield-Mask: 0x01)                            */
/* ==========================================================  USR  ========================================================== */
#define UART_USR_RFF_Pos                  (4UL)                     /*!< RFF (Bit 4)                                           */
#define UART_USR_RFF_Msk                  (0x10UL)                  /*!< RFF (Bitfield-Mask: 0x01)                             */
#define UART_USR_RFNE_Pos                 (3UL)                     /*!< RFNE (Bit 3)                                          */
#define UART_USR_RFNE_Msk                 (0x8UL)                   /*!< RFNE (Bitfield-Mask: 0x01)                            */
#define UART_USR_TFE_Pos                  (2UL)                     /*!< TFE (Bit 2)                                           */
#define UART_USR_TFE_Msk                  (0x4UL)                   /*!< TFE (Bitfield-Mask: 0x01)                             */
#define UART_USR_TFNF_Pos                 (1UL)                     /*!< TFNF (Bit 1)                                          */
#define UART_USR_TFNF_Msk                 (0x2UL)                   /*!< TFNF (Bitfield-Mask: 0x01)                            */
#define UART_USR_BUSY_Pos                 (0UL)                     /*!< BUSY (Bit 0)                                          */
#define UART_USR_BUSY_Msk                 (0x1UL)                   /*!< BUSY (Bitfield-Mask: 0x01)                            */
/* ==========================================================  TCR  ========================================================== */
#define UART_TCR_XFER_MODE_Pos            (3UL)                     /*!< XFER_MODE (Bit 3)                                     */
#define UART_TCR_XFER_MODE_Msk            (0x18UL)                  /*!< XFER_MODE (Bitfield-Mask: 0x03)                       */
#define UART_TCR_DE_POL_Pos               (2UL)                     /*!< DE_POL (Bit 2)                                        */
#define UART_TCR_DE_POL_Msk               (0x4UL)                   /*!< DE_POL (Bitfield-Mask: 0x01)                          */
#define UART_TCR_RE_POL_Pos               (1UL)                     /*!< RE_POL (Bit 1)                                        */
#define UART_TCR_RE_POL_Msk               (0x2UL)                   /*!< RE_POL (Bitfield-Mask: 0x01)                          */
#define UART_TCR_RS485_EN_Pos             (0UL)                     /*!< RS485_EN (Bit 0)                                      */
#define UART_TCR_RS485_EN_Msk             (0x1UL)                   /*!< RS485_EN (Bitfield-Mask: 0x01)                        */
/* ==========================================================  DLF  ========================================================== */
#define UART_DLF_DLF_Pos                  (0UL)                     /*!< DLF (Bit 0)                                           */
#define UART_DLF_DLF_Msk                  (0xfUL)                   /*!< DLF (Bitfield-Mask: 0x0f)                             */
/* ========================================================  LCR_EXT  ======================================================== */
#define UART_LCR_EXT_TRANSMIT_MODE_Pos    (3UL)                     /*!< TRANSMIT_MODE (Bit 3)                                 */
#define UART_LCR_EXT_TRANSMIT_MODE_Msk    (0x8UL)                   /*!< TRANSMIT_MODE (Bitfield-Mask: 0x01)                   */
#define UART_LCR_EXT_SEND_ADDR_Pos        (2UL)                     /*!< SEND_ADDR (Bit 2)                                     */
#define UART_LCR_EXT_SEND_ADDR_Msk        (0x4UL)                   /*!< SEND_ADDR (Bitfield-Mask: 0x01)                       */
#define UART_LCR_EXT_ADDR_MATCH_Pos       (1UL)                     /*!< ADDR_MATCH (Bit 1)                                    */
#define UART_LCR_EXT_ADDR_MATCH_Msk       (0x2UL)                   /*!< ADDR_MATCH (Bitfield-Mask: 0x01)                      */
#define UART_LCR_EXT_DLS_E_Pos            (0UL)                     /*!< DLS_E (Bit 0)                                         */
#define UART_LCR_EXT_DLS_E_Msk            (0x1UL)                   /*!< DLS_E (Bitfield-Mask: 0x01)                           */


/* =========================================================================================================================== */
/* ================                                           SPIM                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  CTRLR0  ========================================================= */
#define SPIM_CTRLR0_SSTE_Pos              (24UL)                    /*!< SSTE (Bit 24)                                         */
#define SPIM_CTRLR0_SSTE_Msk              (0x1000000UL)             /*!< SSTE (Bitfield-Mask: 0x01)                            */
#define SPIM_CTRLR0_SPI_FRF_Pos           (21UL)                    /*!< SPI_FRF (Bit 21)                                      */
#define SPIM_CTRLR0_SPI_FRF_Msk           (0x600000UL)              /*!< SPI_FRF (Bitfield-Mask: 0x03)                         */
#define SPIM_CTRLR0_DFS_32_Pos            (16UL)                    /*!< DFS_32 (Bit 16)                                       */
#define SPIM_CTRLR0_DFS_32_Msk            (0x1f0000UL)              /*!< DFS_32 (Bitfield-Mask: 0x1f)                          */
#define SPIM_CTRLR0_CFS_Pos               (12UL)                    /*!< CFS (Bit 12)                                          */
#define SPIM_CTRLR0_CFS_Msk               (0xf000UL)                /*!< CFS (Bitfield-Mask: 0x0f)                             */
#define SPIM_CTRLR0_SRL_Pos               (11UL)                    /*!< SRL (Bit 11)                                          */
#define SPIM_CTRLR0_SRL_Msk               (0x800UL)                 /*!< SRL (Bitfield-Mask: 0x01)                             */
#define SPIM_CTRLR0_SLV_OE_Pos            (10UL)                    /*!< SLV_OE (Bit 10)                                       */
#define SPIM_CTRLR0_SLV_OE_Msk            (0x400UL)                 /*!< SLV_OE (Bitfield-Mask: 0x01)                          */
#define SPIM_CTRLR0_TMOD_Pos              (8UL)                     /*!< TMOD (Bit 8)                                          */
#define SPIM_CTRLR0_TMOD_Msk              (0x300UL)                 /*!< TMOD (Bitfield-Mask: 0x03)                            */
#define SPIM_CTRLR0_SCPOL_Pos             (7UL)                     /*!< SCPOL (Bit 7)                                         */
#define SPIM_CTRLR0_SCPOL_Msk             (0x80UL)                  /*!< SCPOL (Bitfield-Mask: 0x01)                           */
#define SPIM_CTRLR0_SCPH_Pos              (6UL)                     /*!< SCPH (Bit 6)                                          */
#define SPIM_CTRLR0_SCPH_Msk              (0x40UL)                  /*!< SCPH (Bitfield-Mask: 0x01)                            */
#define SPIM_CTRLR0_FRF_Pos               (4UL)                     /*!< FRF (Bit 4)                                           */
#define SPIM_CTRLR0_FRF_Msk               (0x30UL)                  /*!< FRF (Bitfield-Mask: 0x03)                             */
#define SPIM_CTRLR0_DFS_Pos               (0UL)                     /*!< DFS (Bit 0)                                           */
#define SPIM_CTRLR0_DFS_Msk               (0xfUL)                   /*!< DFS (Bitfield-Mask: 0x0f)                             */
/* ========================================================  CTRLR1  ========================================================= */
#define SPIM_CTRLR1_NDF_Pos               (0UL)                     /*!< NDF (Bit 0)                                           */
#define SPIM_CTRLR1_NDF_Msk               (0xffffUL)                /*!< NDF (Bitfield-Mask: 0xffff)                           */
/* ========================================================  SSIENR  ========================================================= */
#define SPIM_SSIENR_MODE_3WIRE_Pos        (1UL)                     /*!< MODE_3WIRE (Bit 1)                                    */
#define SPIM_SSIENR_MODE_3WIRE_Msk        (0x2UL)                   /*!< MODE_3WIRE (Bitfield-Mask: 0x01)                      */
#define SPIM_SSIENR_SSI_EN_Pos            (0UL)                     /*!< SSI_EN (Bit 0)                                        */
#define SPIM_SSIENR_SSI_EN_Msk            (0x1UL)                   /*!< SSI_EN (Bitfield-Mask: 0x01)                          */
/* ==========================================================  SER  ========================================================== */
#define SPIM_SER_SER_Pos                  (0UL)                     /*!< SER (Bit 0)                                           */
#define SPIM_SER_SER_Msk                  (0x1UL)                   /*!< SER (Bitfield-Mask: 0x01)                             */
/* =========================================================  BAUDR  ========================================================= */
#define SPIM_BAUDR_SCKDV_Pos              (0UL)                     /*!< SCKDV (Bit 0)                                         */
#define SPIM_BAUDR_SCKDV_Msk              (0xffffUL)                /*!< SCKDV (Bitfield-Mask: 0xffff)                         */
/* ========================================================  TXFTLR  ========================================================= */
#define SPIM_TXFTLR_TFT_Pos               (0UL)                     /*!< TFT (Bit 0)                                           */
#define SPIM_TXFTLR_TFT_Msk               (0xffUL)                  /*!< TFT (Bitfield-Mask: 0xff)                             */
/* ========================================================  RXFTLR  ========================================================= */
#define SPIM_RXFTLR_RFT_Pos               (0UL)                     /*!< RFT (Bit 0)                                           */
#define SPIM_RXFTLR_RFT_Msk               (0xffUL)                  /*!< RFT (Bitfield-Mask: 0xff)                             */
/* =========================================================  TXFLR  ========================================================= */
#define SPIM_TXFLR_TXTFL_Pos              (0UL)                     /*!< TXTFL (Bit 0)                                         */
#define SPIM_TXFLR_TXTFL_Msk              (0x1ffUL)                 /*!< TXTFL (Bitfield-Mask: 0x1ff)                          */
/* =========================================================  RXFLR  ========================================================= */
#define SPIM_RXFLR_RXTFL_Pos              (0UL)                     /*!< RXTFL (Bit 0)                                         */
#define SPIM_RXFLR_RXTFL_Msk              (0x1ffUL)                 /*!< RXTFL (Bitfield-Mask: 0x1ff)                          */
/* ==========================================================  SR  =========================================================== */
#define SPIM_SR_DCOL_Pos                  (6UL)                     /*!< DCOL (Bit 6)                                          */
#define SPIM_SR_DCOL_Msk                  (0x40UL)                  /*!< DCOL (Bitfield-Mask: 0x01)                            */
#define SPIM_SR_TXE_Pos                   (5UL)                     /*!< TXE (Bit 5)                                           */
#define SPIM_SR_TXE_Msk                   (0x20UL)                  /*!< TXE (Bitfield-Mask: 0x01)                             */
#define SPIM_SR_RFF_Pos                   (4UL)                     /*!< RFF (Bit 4)                                           */
#define SPIM_SR_RFF_Msk                   (0x10UL)                  /*!< RFF (Bitfield-Mask: 0x01)                             */
#define SPIM_SR_RFNE_Pos                  (3UL)                     /*!< RFNE (Bit 3)                                          */
#define SPIM_SR_RFNE_Msk                  (0x8UL)                   /*!< RFNE (Bitfield-Mask: 0x01)                            */
#define SPIM_SR_TFE_Pos                   (2UL)                     /*!< TFE (Bit 2)                                           */
#define SPIM_SR_TFE_Msk                   (0x4UL)                   /*!< TFE (Bitfield-Mask: 0x01)                             */
#define SPIM_SR_TFNF_Pos                  (1UL)                     /*!< TFNF (Bit 1)                                          */
#define SPIM_SR_TFNF_Msk                  (0x2UL)                   /*!< TFNF (Bitfield-Mask: 0x01)                            */
#define SPIM_SR_BUSY_Pos                  (0UL)                     /*!< BUSY (Bit 0)                                          */
#define SPIM_SR_BUSY_Msk                  (0x1UL)                   /*!< BUSY (Bitfield-Mask: 0x01)                            */
/* ==========================================================  IMR  ========================================================== */
#define SPIM_IMR_MSTIM_Pos                (5UL)                     /*!< MSTIM (Bit 5)                                         */
#define SPIM_IMR_MSTIM_Msk                (0x20UL)                  /*!< MSTIM (Bitfield-Mask: 0x01)                           */
#define SPIM_IMR_RXFIM_Pos                (4UL)                     /*!< RXFIM (Bit 4)                                         */
#define SPIM_IMR_RXFIM_Msk                (0x10UL)                  /*!< RXFIM (Bitfield-Mask: 0x01)                           */
#define SPIM_IMR_RXOIM_Pos                (3UL)                     /*!< RXOIM (Bit 3)                                         */
#define SPIM_IMR_RXOIM_Msk                (0x8UL)                   /*!< RXOIM (Bitfield-Mask: 0x01)                           */
#define SPIM_IMR_RXUIM_Pos                (2UL)                     /*!< RXUIM (Bit 2)                                         */
#define SPIM_IMR_RXUIM_Msk                (0x4UL)                   /*!< RXUIM (Bitfield-Mask: 0x01)                           */
#define SPIM_IMR_TXOIM_Pos                (1UL)                     /*!< TXOIM (Bit 1)                                         */
#define SPIM_IMR_TXOIM_Msk                (0x2UL)                   /*!< TXOIM (Bitfield-Mask: 0x01)                           */
#define SPIM_IMR_TXEIM_Pos                (0UL)                     /*!< TXEIM (Bit 0)                                         */
#define SPIM_IMR_TXEIM_Msk                (0x1UL)                   /*!< TXEIM (Bitfield-Mask: 0x01)                           */
/* ==========================================================  ISR  ========================================================== */
#define SPIM_ISR_MSTIS_Pos                (5UL)                     /*!< MSTIS (Bit 5)                                         */
#define SPIM_ISR_MSTIS_Msk                (0x20UL)                  /*!< MSTIS (Bitfield-Mask: 0x01)                           */
#define SPIM_ISR_RXFIS_Pos                (4UL)                     /*!< RXFIS (Bit 4)                                         */
#define SPIM_ISR_RXFIS_Msk                (0x10UL)                  /*!< RXFIS (Bitfield-Mask: 0x01)                           */
#define SPIM_ISR_RXOIS_Pos                (3UL)                     /*!< RXOIS (Bit 3)                                         */
#define SPIM_ISR_RXOIS_Msk                (0x8UL)                   /*!< RXOIS (Bitfield-Mask: 0x01)                           */
#define SPIM_ISR_RXUIS_Pos                (2UL)                     /*!< RXUIS (Bit 2)                                         */
#define SPIM_ISR_RXUIS_Msk                (0x4UL)                   /*!< RXUIS (Bitfield-Mask: 0x01)                           */
#define SPIM_ISR_TXOIS_Pos                (1UL)                     /*!< TXOIS (Bit 1)                                         */
#define SPIM_ISR_TXOIS_Msk                (0x2UL)                   /*!< TXOIS (Bitfield-Mask: 0x01)                           */
#define SPIM_ISR_TXEIS_Pos                (0UL)                     /*!< TXEIS (Bit 0)                                         */
#define SPIM_ISR_TXEIS_Msk                (0x1UL)                   /*!< TXEIS (Bitfield-Mask: 0x01)                           */
/* ==========================================================  ICR  ========================================================== */
#define SPIM_ICR_ICR_Pos                  (0UL)                     /*!< ICR (Bit 0)                                           */
#define SPIM_ICR_ICR_Msk                  (0x1UL)                   /*!< ICR (Bitfield-Mask: 0x01)                             */
/* =========================================================  DR16  ========================================================== */
#define SPIM_DR16_DR_Pos                  (0UL)                     /*!< DR (Bit 0)                                            */
#define SPIM_DR16_DR_Msk                  (0xffffUL)                /*!< DR (Bitfield-Mask: 0xffff)                            */


/* =========================================================================================================================== */
/* ================                                            IIC                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  IC_CON  ========================================================= */
#define IIC_IC_CON_RSVD_IC_CON_2_Pos      (20UL)                    /*!< RSVD_IC_CON_2 (Bit 20)                                */
#define IIC_IC_CON_RSVD_IC_CON_2_Msk      (0xfff00000UL)            /*!< RSVD_IC_CON_2 (Bitfield-Mask: 0xfff)                  */
#define IIC_IC_CON_SMBUS_PERSISTENT_SLV_ADDR_EN_Pos (19UL)          /*!< SMBUS_PERSISTENT_SLV_ADDR_EN (Bit 19)                 */
#define IIC_IC_CON_SMBUS_PERSISTENT_SLV_ADDR_EN_Msk (0x80000UL)     /*!< SMBUS_PERSISTENT_SLV_ADDR_EN (Bitfield-Mask: 0x01)    */
#define IIC_IC_CON_SMBUS_ARP_EN_Pos       (18UL)                    /*!< SMBUS_ARP_EN (Bit 18)                                 */
#define IIC_IC_CON_SMBUS_ARP_EN_Msk       (0x40000UL)               /*!< SMBUS_ARP_EN (Bitfield-Mask: 0x01)                    */
#define IIC_IC_CON_SMBUS_SLAVE_QUICK_EN_Pos (17UL)                  /*!< SMBUS_SLAVE_QUICK_EN (Bit 17)                         */
#define IIC_IC_CON_SMBUS_SLAVE_QUICK_EN_Msk (0x20000UL)             /*!< SMBUS_SLAVE_QUICK_EN (Bitfield-Mask: 0x01)            */
#define IIC_IC_CON_OPTIONAL_SAR_CTRL_Pos  (16UL)                    /*!< OPTIONAL_SAR_CTRL (Bit 16)                            */
#define IIC_IC_CON_OPTIONAL_SAR_CTRL_Msk  (0x10000UL)               /*!< OPTIONAL_SAR_CTRL (Bitfield-Mask: 0x01)               */
#define IIC_IC_CON_RSVD_IC_CON_1_Pos      (12UL)                    /*!< RSVD_IC_CON_1 (Bit 12)                                */
#define IIC_IC_CON_RSVD_IC_CON_1_Msk      (0xf000UL)                /*!< RSVD_IC_CON_1 (Bitfield-Mask: 0x0f)                   */
#define IIC_IC_CON_BUS_CLEAR_FEATURE_CTRL_Pos (11UL)                /*!< BUS_CLEAR_FEATURE_CTRL (Bit 11)                       */
#define IIC_IC_CON_BUS_CLEAR_FEATURE_CTRL_Msk (0x800UL)             /*!< BUS_CLEAR_FEATURE_CTRL (Bitfield-Mask: 0x01)          */
#define IIC_IC_CON_STOP_DET_IF_MASTER_ACTIVE_Pos (10UL)             /*!< STOP_DET_IF_MASTER_ACTIVE (Bit 10)                    */
#define IIC_IC_CON_STOP_DET_IF_MASTER_ACTIVE_Msk (0x400UL)          /*!< STOP_DET_IF_MASTER_ACTIVE (Bitfield-Mask: 0x01)       */
#define IIC_IC_CON_RX_FIFO_FULL_HLD_CTRL_Pos (9UL)                  /*!< RX_FIFO_FULL_HLD_CTRL (Bit 9)                         */
#define IIC_IC_CON_RX_FIFO_FULL_HLD_CTRL_Msk (0x200UL)              /*!< RX_FIFO_FULL_HLD_CTRL (Bitfield-Mask: 0x01)           */
#define IIC_IC_CON_TX_EMPTY_CTRL_Pos      (8UL)                     /*!< TX_EMPTY_CTRL (Bit 8)                                 */
#define IIC_IC_CON_TX_EMPTY_CTRL_Msk      (0x100UL)                 /*!< TX_EMPTY_CTRL (Bitfield-Mask: 0x01)                   */
#define IIC_IC_CON_STOP_DET_IFADDRESSED_Pos (7UL)                   /*!< STOP_DET_IFADDRESSED (Bit 7)                          */
#define IIC_IC_CON_STOP_DET_IFADDRESSED_Msk (0x80UL)                /*!< STOP_DET_IFADDRESSED (Bitfield-Mask: 0x01)            */
#define IIC_IC_CON_IC_SLAVE_DISABLE_Pos   (6UL)                     /*!< IC_SLAVE_DISABLE (Bit 6)                              */
#define IIC_IC_CON_IC_SLAVE_DISABLE_Msk   (0x40UL)                  /*!< IC_SLAVE_DISABLE (Bitfield-Mask: 0x01)                */
#define IIC_IC_CON_IC_RESTART_EN_Pos      (5UL)                     /*!< IC_RESTART_EN (Bit 5)                                 */
#define IIC_IC_CON_IC_RESTART_EN_Msk      (0x20UL)                  /*!< IC_RESTART_EN (Bitfield-Mask: 0x01)                   */
#define IIC_IC_CON_IC_10BITADDR_MASTER_Pos (4UL)                    /*!< IC_10BITADDR_MASTER (Bit 4)                           */
#define IIC_IC_CON_IC_10BITADDR_MASTER_Msk (0x10UL)                 /*!< IC_10BITADDR_MASTER (Bitfield-Mask: 0x01)             */
#define IIC_IC_CON_IC_10BITADDR_SLAVE_Pos (3UL)                     /*!< IC_10BITADDR_SLAVE (Bit 3)                            */
#define IIC_IC_CON_IC_10BITADDR_SLAVE_Msk (0x8UL)                   /*!< IC_10BITADDR_SLAVE (Bitfield-Mask: 0x01)              */
#define IIC_IC_CON_SPEED_Pos              (1UL)                     /*!< SPEED (Bit 1)                                         */
#define IIC_IC_CON_SPEED_Msk              (0x6UL)                   /*!< SPEED (Bitfield-Mask: 0x03)                           */
#define IIC_IC_CON_MASTER_MODE_Pos        (0UL)                     /*!< MASTER_MODE (Bit 0)                                   */
#define IIC_IC_CON_MASTER_MODE_Msk        (0x1UL)                   /*!< MASTER_MODE (Bitfield-Mask: 0x01)                     */
/* ========================================================  IC_TAR  ========================================================= */
#define IIC_IC_TAR_RSVD_IC_TAR_2_Pos      (17UL)                    /*!< RSVD_IC_TAR_2 (Bit 17)                                */
#define IIC_IC_TAR_RSVD_IC_TAR_2_Msk      (0xfffe0000UL)            /*!< RSVD_IC_TAR_2 (Bitfield-Mask: 0x7fff)                 */
#define IIC_IC_TAR_SMBUS_QUICK_CMD_Pos    (16UL)                    /*!< SMBUS_QUICK_CMD (Bit 16)                              */
#define IIC_IC_TAR_SMBUS_QUICK_CMD_Msk    (0x10000UL)               /*!< SMBUS_QUICK_CMD (Bitfield-Mask: 0x01)                 */
#define IIC_IC_TAR_RSVD_IC_TAR_1_Pos      (14UL)                    /*!< RSVD_IC_TAR_1 (Bit 14)                                */
#define IIC_IC_TAR_RSVD_IC_TAR_1_Msk      (0xc000UL)                /*!< RSVD_IC_TAR_1 (Bitfield-Mask: 0x03)                   */
#define IIC_IC_TAR_DEVICE_ID_Pos          (13UL)                    /*!< DEVICE_ID (Bit 13)                                    */
#define IIC_IC_TAR_DEVICE_ID_Msk          (0x2000UL)                /*!< DEVICE_ID (Bitfield-Mask: 0x01)                       */
#define IIC_IC_TAR_IC_10BITADDR_MASTER_Pos (12UL)                   /*!< IC_10BITADDR_MASTER (Bit 12)                          */
#define IIC_IC_TAR_IC_10BITADDR_MASTER_Msk (0x1000UL)               /*!< IC_10BITADDR_MASTER (Bitfield-Mask: 0x01)             */
#define IIC_IC_TAR_SPECIAL_Pos            (11UL)                    /*!< SPECIAL (Bit 11)                                      */
#define IIC_IC_TAR_SPECIAL_Msk            (0x800UL)                 /*!< SPECIAL (Bitfield-Mask: 0x01)                         */
#define IIC_IC_TAR_GC_OR_START_Pos        (10UL)                    /*!< GC_OR_START (Bit 10)                                  */
#define IIC_IC_TAR_GC_OR_START_Msk        (0x400UL)                 /*!< GC_OR_START (Bitfield-Mask: 0x01)                     */
#define IIC_IC_TAR_IC_TAR_Pos             (0UL)                     /*!< IC_TAR (Bit 0)                                        */
#define IIC_IC_TAR_IC_TAR_Msk             (0x3ffUL)                 /*!< IC_TAR (Bitfield-Mask: 0x3ff)                         */
/* ========================================================  IC_SAR  ========================================================= */
#define IIC_IC_SAR_RSVD_IC_SAR_Pos        (10UL)                    /*!< RSVD_IC_SAR (Bit 10)                                  */
#define IIC_IC_SAR_RSVD_IC_SAR_Msk        (0xfffffc00UL)            /*!< RSVD_IC_SAR (Bitfield-Mask: 0x3fffff)                 */
#define IIC_IC_SAR_IC_SAR_Pos             (0UL)                     /*!< IC_SAR (Bit 0)                                        */
#define IIC_IC_SAR_IC_SAR_Msk             (0x3ffUL)                 /*!< IC_SAR (Bitfield-Mask: 0x3ff)                         */
/* ======================================================  IC_DATA_CMD  ====================================================== */
#define IIC_IC_DATA_CMD_RSVD_IC_DATA_CMD_Pos (12UL)                 /*!< RSVD_IC_DATA_CMD (Bit 12)                             */
#define IIC_IC_DATA_CMD_RSVD_IC_DATA_CMD_Msk (0xfffff000UL)         /*!< RSVD_IC_DATA_CMD (Bitfield-Mask: 0xfffff)             */
#define IIC_IC_DATA_CMD_FIRST_DATA_BYTE_Pos (11UL)                  /*!< FIRST_DATA_BYTE (Bit 11)                              */
#define IIC_IC_DATA_CMD_FIRST_DATA_BYTE_Msk (0x800UL)               /*!< FIRST_DATA_BYTE (Bitfield-Mask: 0x01)                 */
#define IIC_IC_DATA_CMD_RESTART_Pos       (10UL)                    /*!< RESTART (Bit 10)                                      */
#define IIC_IC_DATA_CMD_RESTART_Msk       (0x400UL)                 /*!< RESTART (Bitfield-Mask: 0x01)                         */
#define IIC_IC_DATA_CMD_STOP_Pos          (9UL)                     /*!< STOP (Bit 9)                                          */
#define IIC_IC_DATA_CMD_STOP_Msk          (0x200UL)                 /*!< STOP (Bitfield-Mask: 0x01)                            */
#define IIC_IC_DATA_CMD_CMD_Pos           (8UL)                     /*!< CMD (Bit 8)                                           */
#define IIC_IC_DATA_CMD_CMD_Msk           (0x100UL)                 /*!< CMD (Bitfield-Mask: 0x01)                             */
#define IIC_IC_DATA_CMD_DAT_Pos           (0UL)                     /*!< DAT (Bit 0)                                           */
#define IIC_IC_DATA_CMD_DAT_Msk           (0xffUL)                  /*!< DAT (Bitfield-Mask: 0xff)                             */
/* ====================================================  IC_SS_SCL_HCNT  ===================================================== */
#define IIC_IC_SS_SCL_HCNT_IC_SS_SCL_HCNT_Pos (0UL)                 /*!< IC_SS_SCL_HCNT (Bit 0)                                */
#define IIC_IC_SS_SCL_HCNT_IC_SS_SCL_HCNT_Msk (0xffffUL)            /*!< IC_SS_SCL_HCNT (Bitfield-Mask: 0xffff)                */
/* ====================================================  IC_SS_SCL_LCNT  ===================================================== */
#define IIC_IC_SS_SCL_LCNT_IC_SS_SCL_LCNT_Pos (0UL)                 /*!< IC_SS_SCL_LCNT (Bit 0)                                */
#define IIC_IC_SS_SCL_LCNT_IC_SS_SCL_LCNT_Msk (0xffffUL)            /*!< IC_SS_SCL_LCNT (Bitfield-Mask: 0xffff)                */
/* ====================================================  IC_FS_SCL_HCNT  ===================================================== */
#define IIC_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT_Pos (0UL)                 /*!< IC_FS_SCL_HCNT (Bit 0)                                */
#define IIC_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT_Msk (0xffffUL)            /*!< IC_FS_SCL_HCNT (Bitfield-Mask: 0xffff)                */
/* ====================================================  IC_FS_SCL_LCNT  ===================================================== */
#define IIC_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT_Pos (0UL)                 /*!< IC_FS_SCL_LCNT (Bit 0)                                */
#define IIC_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT_Msk (0xffffUL)            /*!< IC_FS_SCL_LCNT (Bitfield-Mask: 0xffff)                */
/* =====================================================  IC_INTR_STAT  ====================================================== */
#define IIC_IC_INTR_STAT_R_GEN_CALL_Pos   (11UL)                    /*!< R_GEN_CALL (Bit 11)                                   */
#define IIC_IC_INTR_STAT_R_GEN_CALL_Msk   (0x800UL)                 /*!< R_GEN_CALL (Bitfield-Mask: 0x01)                      */
#define IIC_IC_INTR_STAT_R_START_DET_Pos  (10UL)                    /*!< R_START_DET (Bit 10)                                  */
#define IIC_IC_INTR_STAT_R_START_DET_Msk  (0x400UL)                 /*!< R_START_DET (Bitfield-Mask: 0x01)                     */
#define IIC_IC_INTR_STAT_R_STOP_DET_Pos   (9UL)                     /*!< R_STOP_DET (Bit 9)                                    */
#define IIC_IC_INTR_STAT_R_STOP_DET_Msk   (0x200UL)                 /*!< R_STOP_DET (Bitfield-Mask: 0x01)                      */
#define IIC_IC_INTR_STAT_R_ACTIVITY_Pos   (8UL)                     /*!< R_ACTIVITY (Bit 8)                                    */
#define IIC_IC_INTR_STAT_R_ACTIVITY_Msk   (0x100UL)                 /*!< R_ACTIVITY (Bitfield-Mask: 0x01)                      */
#define IIC_IC_INTR_STAT_R_RX_DONE_Pos    (7UL)                     /*!< R_RX_DONE (Bit 7)                                     */
#define IIC_IC_INTR_STAT_R_RX_DONE_Msk    (0x80UL)                  /*!< R_RX_DONE (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_STAT_R_TX_ABRT_Pos    (6UL)                     /*!< R_TX_ABRT (Bit 6)                                     */
#define IIC_IC_INTR_STAT_R_TX_ABRT_Msk    (0x40UL)                  /*!< R_TX_ABRT (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_STAT_R_RD_REQ_Pos     (5UL)                     /*!< R_RD_REQ (Bit 5)                                      */
#define IIC_IC_INTR_STAT_R_RD_REQ_Msk     (0x20UL)                  /*!< R_RD_REQ (Bitfield-Mask: 0x01)                        */
#define IIC_IC_INTR_STAT_R_TX_EMPTY_Pos   (4UL)                     /*!< R_TX_EMPTY (Bit 4)                                    */
#define IIC_IC_INTR_STAT_R_TX_EMPTY_Msk   (0x10UL)                  /*!< R_TX_EMPTY (Bitfield-Mask: 0x01)                      */
#define IIC_IC_INTR_STAT_R_TX_OVER_Pos    (3UL)                     /*!< R_TX_OVER (Bit 3)                                     */
#define IIC_IC_INTR_STAT_R_TX_OVER_Msk    (0x8UL)                   /*!< R_TX_OVER (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_STAT_R_RX_FULL_Pos    (2UL)                     /*!< R_RX_FULL (Bit 2)                                     */
#define IIC_IC_INTR_STAT_R_RX_FULL_Msk    (0x4UL)                   /*!< R_RX_FULL (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_STAT_R_RX_OVER_Pos    (1UL)                     /*!< R_RX_OVER (Bit 1)                                     */
#define IIC_IC_INTR_STAT_R_RX_OVER_Msk    (0x2UL)                   /*!< R_RX_OVER (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_STAT_R_RX_UNDER_Pos   (0UL)                     /*!< R_RX_UNDER (Bit 0)                                    */
#define IIC_IC_INTR_STAT_R_RX_UNDER_Msk   (0x1UL)                   /*!< R_RX_UNDER (Bitfield-Mask: 0x01)                      */
/* =====================================================  IC_INTR_MASK  ====================================================== */
#define IIC_IC_INTR_MASK_RSVD_IC_INTR_STAT_Pos (15UL)               /*!< RSVD_IC_INTR_STAT (Bit 15)                            */
#define IIC_IC_INTR_MASK_RSVD_IC_INTR_STAT_Msk (0xffff8000UL)       /*!< RSVD_IC_INTR_STAT (Bitfield-Mask: 0x1ffff)            */
#define IIC_IC_INTR_MASK_M_SCL_STUCK_AT_LOW_Pos (14UL)              /*!< M_SCL_STUCK_AT_LOW (Bit 14)                           */
#define IIC_IC_INTR_MASK_M_SCL_STUCK_AT_LOW_Msk (0x4000UL)          /*!< M_SCL_STUCK_AT_LOW (Bitfield-Mask: 0x01)              */
#define IIC_IC_INTR_MASK_M_MASTER_ON_HOLD_Pos (13UL)                /*!< M_MASTER_ON_HOLD (Bit 13)                             */
#define IIC_IC_INTR_MASK_M_MASTER_ON_HOLD_Msk (0x2000UL)            /*!< M_MASTER_ON_HOLD (Bitfield-Mask: 0x01)                */
#define IIC_IC_INTR_MASK_M_RESTART_DET_Pos (12UL)                   /*!< M_RESTART_DET (Bit 12)                                */
#define IIC_IC_INTR_MASK_M_RESTART_DET_Msk (0x1000UL)               /*!< M_RESTART_DET (Bitfield-Mask: 0x01)                   */
#define IIC_IC_INTR_MASK_M_GEN_CALL_Pos   (11UL)                    /*!< M_GEN_CALL (Bit 11)                                   */
#define IIC_IC_INTR_MASK_M_GEN_CALL_Msk   (0x800UL)                 /*!< M_GEN_CALL (Bitfield-Mask: 0x01)                      */
#define IIC_IC_INTR_MASK_M_START_DET_Pos  (10UL)                    /*!< M_START_DET (Bit 10)                                  */
#define IIC_IC_INTR_MASK_M_START_DET_Msk  (0x400UL)                 /*!< M_START_DET (Bitfield-Mask: 0x01)                     */
#define IIC_IC_INTR_MASK_M_STOP_DET_Pos   (9UL)                     /*!< M_STOP_DET (Bit 9)                                    */
#define IIC_IC_INTR_MASK_M_STOP_DET_Msk   (0x200UL)                 /*!< M_STOP_DET (Bitfield-Mask: 0x01)                      */
#define IIC_IC_INTR_MASK_M_ACTIVITY_Pos   (8UL)                     /*!< M_ACTIVITY (Bit 8)                                    */
#define IIC_IC_INTR_MASK_M_ACTIVITY_Msk   (0x100UL)                 /*!< M_ACTIVITY (Bitfield-Mask: 0x01)                      */
#define IIC_IC_INTR_MASK_M_RX_DONE_Pos    (7UL)                     /*!< M_RX_DONE (Bit 7)                                     */
#define IIC_IC_INTR_MASK_M_RX_DONE_Msk    (0x80UL)                  /*!< M_RX_DONE (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_MASK_M_TX_ABRT_Pos    (6UL)                     /*!< M_TX_ABRT (Bit 6)                                     */
#define IIC_IC_INTR_MASK_M_TX_ABRT_Msk    (0x40UL)                  /*!< M_TX_ABRT (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_MASK_M_RD_REQ_Pos     (5UL)                     /*!< M_RD_REQ (Bit 5)                                      */
#define IIC_IC_INTR_MASK_M_RD_REQ_Msk     (0x20UL)                  /*!< M_RD_REQ (Bitfield-Mask: 0x01)                        */
#define IIC_IC_INTR_MASK_M_TX_EMPTY_Pos   (4UL)                     /*!< M_TX_EMPTY (Bit 4)                                    */
#define IIC_IC_INTR_MASK_M_TX_EMPTY_Msk   (0x10UL)                  /*!< M_TX_EMPTY (Bitfield-Mask: 0x01)                      */
#define IIC_IC_INTR_MASK_M_TX_OVER_Pos    (3UL)                     /*!< M_TX_OVER (Bit 3)                                     */
#define IIC_IC_INTR_MASK_M_TX_OVER_Msk    (0x8UL)                   /*!< M_TX_OVER (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_MASK_M_RX_FULL_Pos    (2UL)                     /*!< M_RX_FULL (Bit 2)                                     */
#define IIC_IC_INTR_MASK_M_RX_FULL_Msk    (0x4UL)                   /*!< M_RX_FULL (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_MASK_M_RX_OVER_Pos    (1UL)                     /*!< M_RX_OVER (Bit 1)                                     */
#define IIC_IC_INTR_MASK_M_RX_OVER_Msk    (0x2UL)                   /*!< M_RX_OVER (Bitfield-Mask: 0x01)                       */
#define IIC_IC_INTR_MASK_M_RX_UNDER_Pos   (0UL)                     /*!< M_RX_UNDER (Bit 0)                                    */
#define IIC_IC_INTR_MASK_M_RX_UNDER_Msk   (0x1UL)                   /*!< M_RX_UNDER (Bitfield-Mask: 0x01)                      */
/* ===================================================  IC_RAW_INTR_STAT  ==================================================== */
#define IIC_IC_RAW_INTR_STAT_SCL_STUCK_AT_LOW_Pos (14UL)            /*!< SCL_STUCK_AT_LOW (Bit 14)                             */
#define IIC_IC_RAW_INTR_STAT_SCL_STUCK_AT_LOW_Msk (0x4000UL)        /*!< SCL_STUCK_AT_LOW (Bitfield-Mask: 0x01)                */
#define IIC_IC_RAW_INTR_STAT_MASTER_ON_HOLD_Pos (13UL)              /*!< MASTER_ON_HOLD (Bit 13)                               */
#define IIC_IC_RAW_INTR_STAT_MASTER_ON_HOLD_Msk (0x2000UL)          /*!< MASTER_ON_HOLD (Bitfield-Mask: 0x01)                  */
#define IIC_IC_RAW_INTR_STAT_RESTART_DET_Pos (12UL)                 /*!< RESTART_DET (Bit 12)                                  */
#define IIC_IC_RAW_INTR_STAT_RESTART_DET_Msk (0x1000UL)             /*!< RESTART_DET (Bitfield-Mask: 0x01)                     */
#define IIC_IC_RAW_INTR_STAT_GEN_CALL_Pos (11UL)                    /*!< GEN_CALL (Bit 11)                                     */
#define IIC_IC_RAW_INTR_STAT_GEN_CALL_Msk (0x800UL)                 /*!< GEN_CALL (Bitfield-Mask: 0x01)                        */
#define IIC_IC_RAW_INTR_STAT_START_DET_Pos (10UL)                   /*!< START_DET (Bit 10)                                    */
#define IIC_IC_RAW_INTR_STAT_START_DET_Msk (0x400UL)                /*!< START_DET (Bitfield-Mask: 0x01)                       */
#define IIC_IC_RAW_INTR_STAT_STOP_DET_Pos (9UL)                     /*!< STOP_DET (Bit 9)                                      */
#define IIC_IC_RAW_INTR_STAT_STOP_DET_Msk (0x200UL)                 /*!< STOP_DET (Bitfield-Mask: 0x01)                        */
#define IIC_IC_RAW_INTR_STAT_ACTIVITY_Pos (8UL)                     /*!< ACTIVITY (Bit 8)                                      */
#define IIC_IC_RAW_INTR_STAT_ACTIVITY_Msk (0x100UL)                 /*!< ACTIVITY (Bitfield-Mask: 0x01)                        */
#define IIC_IC_RAW_INTR_STAT_RX_DONE_Pos  (7UL)                     /*!< RX_DONE (Bit 7)                                       */
#define IIC_IC_RAW_INTR_STAT_RX_DONE_Msk  (0x80UL)                  /*!< RX_DONE (Bitfield-Mask: 0x01)                         */
#define IIC_IC_RAW_INTR_STAT_TX_ABRT_Pos  (6UL)                     /*!< TX_ABRT (Bit 6)                                       */
#define IIC_IC_RAW_INTR_STAT_TX_ABRT_Msk  (0x40UL)                  /*!< TX_ABRT (Bitfield-Mask: 0x01)                         */
#define IIC_IC_RAW_INTR_STAT_RD_REQ_Pos   (5UL)                     /*!< RD_REQ (Bit 5)                                        */
#define IIC_IC_RAW_INTR_STAT_RD_REQ_Msk   (0x20UL)                  /*!< RD_REQ (Bitfield-Mask: 0x01)                          */
#define IIC_IC_RAW_INTR_STAT_TX_EMPTY_Pos (4UL)                     /*!< TX_EMPTY (Bit 4)                                      */
#define IIC_IC_RAW_INTR_STAT_TX_EMPTY_Msk (0x10UL)                  /*!< TX_EMPTY (Bitfield-Mask: 0x01)                        */
#define IIC_IC_RAW_INTR_STAT_TX_OVER_Pos  (3UL)                     /*!< TX_OVER (Bit 3)                                       */
#define IIC_IC_RAW_INTR_STAT_TX_OVER_Msk  (0x8UL)                   /*!< TX_OVER (Bitfield-Mask: 0x01)                         */
#define IIC_IC_RAW_INTR_STAT_RX_FULL_Pos  (2UL)                     /*!< RX_FULL (Bit 2)                                       */
#define IIC_IC_RAW_INTR_STAT_RX_FULL_Msk  (0x4UL)                   /*!< RX_FULL (Bitfield-Mask: 0x01)                         */
#define IIC_IC_RAW_INTR_STAT_RX_OVER_Pos  (1UL)                     /*!< RX_OVER (Bit 1)                                       */
#define IIC_IC_RAW_INTR_STAT_RX_OVER_Msk  (0x2UL)                   /*!< RX_OVER (Bitfield-Mask: 0x01)                         */
#define IIC_IC_RAW_INTR_STAT_RX_UNDER_Pos (0UL)                     /*!< RX_UNDER (Bit 0)                                      */
#define IIC_IC_RAW_INTR_STAT_RX_UNDER_Msk (0x1UL)                   /*!< RX_UNDER (Bitfield-Mask: 0x01)                        */
/* =======================================================  IC_RX_TL  ======================================================== */
#define IIC_IC_RX_TL_RX_TL_Pos            (0UL)                     /*!< RX_TL (Bit 0)                                         */
#define IIC_IC_RX_TL_RX_TL_Msk            (0xffUL)                  /*!< RX_TL (Bitfield-Mask: 0xff)                           */
/* =======================================================  IC_TX_TL  ======================================================== */
#define IIC_IC_TX_TL_TX_TL_Pos            (0UL)                     /*!< TX_TL (Bit 0)                                         */
#define IIC_IC_TX_TL_TX_TL_Msk            (0xffUL)                  /*!< TX_TL (Bitfield-Mask: 0xff)                           */
/* ======================================================  IC_CLR_INTR  ====================================================== */
#define IIC_IC_CLR_INTR_CLR_INTR_Pos      (0UL)                     /*!< CLR_INTR (Bit 0)                                      */
#define IIC_IC_CLR_INTR_CLR_INTR_Msk      (0x1UL)                   /*!< CLR_INTR (Bitfield-Mask: 0x01)                        */
/* ====================================================  IC_CLR_RX_UNDER  ==================================================== */
#define IIC_IC_CLR_RX_UNDER_CLR_RX_UNDER_Pos (0UL)                  /*!< CLR_RX_UNDER (Bit 0)                                  */
#define IIC_IC_CLR_RX_UNDER_CLR_RX_UNDER_Msk (0x1UL)                /*!< CLR_RX_UNDER (Bitfield-Mask: 0x01)                    */
/* ====================================================  IC_CLR_RX_OVER  ===================================================== */
#define IIC_IC_CLR_RX_OVER_CLR_RX_OVER_Pos (0UL)                    /*!< CLR_RX_OVER (Bit 0)                                   */
#define IIC_IC_CLR_RX_OVER_CLR_RX_OVER_Msk (0x1UL)                  /*!< CLR_RX_OVER (Bitfield-Mask: 0x01)                     */
/* ====================================================  IC_CLR_TX_OVER  ===================================================== */
#define IIC_IC_CLR_TX_OVER_CLR_TX_OVER_Pos (0UL)                    /*!< CLR_TX_OVER (Bit 0)                                   */
#define IIC_IC_CLR_TX_OVER_CLR_TX_OVER_Msk (0x1UL)                  /*!< CLR_TX_OVER (Bitfield-Mask: 0x01)                     */
/* =====================================================  IC_CLR_RD_REQ  ===================================================== */
#define IIC_IC_CLR_RD_REQ_CLR_RD_REQ_Pos  (0UL)                     /*!< CLR_RD_REQ (Bit 0)                                    */
#define IIC_IC_CLR_RD_REQ_CLR_RD_REQ_Msk  (0x1UL)                   /*!< CLR_RD_REQ (Bitfield-Mask: 0x01)                      */
/* ====================================================  IC_CLR_TX_ABRT  ===================================================== */
#define IIC_IC_CLR_TX_ABRT_CLR_TX_ABRT_Pos (0UL)                    /*!< CLR_TX_ABRT (Bit 0)                                   */
#define IIC_IC_CLR_TX_ABRT_CLR_TX_ABRT_Msk (0x1UL)                  /*!< CLR_TX_ABRT (Bitfield-Mask: 0x01)                     */
/* ====================================================  IC_CLR_RX_DONE  ===================================================== */
#define IIC_IC_CLR_RX_DONE_CLR_RX_DONE_Pos (0UL)                    /*!< CLR_RX_DONE (Bit 0)                                   */
#define IIC_IC_CLR_RX_DONE_CLR_RX_DONE_Msk (0x1UL)                  /*!< CLR_RX_DONE (Bitfield-Mask: 0x01)                     */
/* ====================================================  IC_CLR_ACTIVITY  ==================================================== */
#define IIC_IC_CLR_ACTIVITY_CLR_ACTIVITY_Pos (0UL)                  /*!< CLR_ACTIVITY (Bit 0)                                  */
#define IIC_IC_CLR_ACTIVITY_CLR_ACTIVITY_Msk (0x1UL)                /*!< CLR_ACTIVITY (Bitfield-Mask: 0x01)                    */
/* ====================================================  IC_CLR_STOP_DET  ==================================================== */
#define IIC_IC_CLR_STOP_DET_CLR_STOP_DET_Pos (0UL)                  /*!< CLR_STOP_DET (Bit 0)                                  */
#define IIC_IC_CLR_STOP_DET_CLR_STOP_DET_Msk (0x1UL)                /*!< CLR_STOP_DET (Bitfield-Mask: 0x01)                    */
/* ===================================================  IC_CLR_START_DET  ==================================================== */
#define IIC_IC_CLR_START_DET_CLR_START_DET_Pos (0UL)                /*!< CLR_START_DET (Bit 0)                                 */
#define IIC_IC_CLR_START_DET_CLR_START_DET_Msk (0x1UL)              /*!< CLR_START_DET (Bitfield-Mask: 0x01)                   */
/* =======================================================  IC_ENABLE  ======================================================= */
#define IIC_IC_ENABLE_IC_ENABLE_Pos       (0UL)                     /*!< IC_ENABLE (Bit 0)                                     */
#define IIC_IC_ENABLE_IC_ENABLE_Msk       (0x1UL)                   /*!< IC_ENABLE (Bitfield-Mask: 0x01)                       */
/* =======================================================  IC_TXFLR  ======================================================== */
#define IIC_IC_TXFLR_TXFLR_Pos            (0UL)                     /*!< TXFLR (Bit 0)                                         */
#define IIC_IC_TXFLR_TXFLR_Msk            (0xffUL)                  /*!< TXFLR (Bitfield-Mask: 0xff)                           */
/* =======================================================  IC_RXFLR  ======================================================== */
#define IIC_IC_RXFLR_RXFLR_Pos            (0UL)                     /*!< RXFLR (Bit 0)                                         */
#define IIC_IC_RXFLR_RXFLR_Msk            (0xffUL)                  /*!< RXFLR (Bitfield-Mask: 0xff)                           */


/* =========================================================================================================================== */
/* ================                                           SPIS                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  CTRLR0  ========================================================= */
#define SPIS_CTRLR0_SSTE_Pos              (24UL)                    /*!< SSTE (Bit 24)                                         */
#define SPIS_CTRLR0_SSTE_Msk              (0x1000000UL)             /*!< SSTE (Bitfield-Mask: 0x01)                            */
#define SPIS_CTRLR0_SPI_FRF_Pos           (21UL)                    /*!< SPI_FRF (Bit 21)                                      */
#define SPIS_CTRLR0_SPI_FRF_Msk           (0x600000UL)              /*!< SPI_FRF (Bitfield-Mask: 0x03)                         */
#define SPIS_CTRLR0_DFS_32_Pos            (16UL)                    /*!< DFS_32 (Bit 16)                                       */
#define SPIS_CTRLR0_DFS_32_Msk            (0x1f0000UL)              /*!< DFS_32 (Bitfield-Mask: 0x1f)                          */
#define SPIS_CTRLR0_CFS_Pos               (12UL)                    /*!< CFS (Bit 12)                                          */
#define SPIS_CTRLR0_CFS_Msk               (0xf000UL)                /*!< CFS (Bitfield-Mask: 0x0f)                             */
#define SPIS_CTRLR0_SRL_Pos               (11UL)                    /*!< SRL (Bit 11)                                          */
#define SPIS_CTRLR0_SRL_Msk               (0x800UL)                 /*!< SRL (Bitfield-Mask: 0x01)                             */
#define SPIS_CTRLR0_SLV_OE_Pos            (10UL)                    /*!< SLV_OE (Bit 10)                                       */
#define SPIS_CTRLR0_SLV_OE_Msk            (0x400UL)                 /*!< SLV_OE (Bitfield-Mask: 0x01)                          */
#define SPIS_CTRLR0_TMOD_Pos              (8UL)                     /*!< TMOD (Bit 8)                                          */
#define SPIS_CTRLR0_TMOD_Msk              (0x300UL)                 /*!< TMOD (Bitfield-Mask: 0x03)                            */
#define SPIS_CTRLR0_SCPOL_Pos             (7UL)                     /*!< SCPOL (Bit 7)                                         */
#define SPIS_CTRLR0_SCPOL_Msk             (0x80UL)                  /*!< SCPOL (Bitfield-Mask: 0x01)                           */
#define SPIS_CTRLR0_SCPH_Pos              (6UL)                     /*!< SCPH (Bit 6)                                          */
#define SPIS_CTRLR0_SCPH_Msk              (0x40UL)                  /*!< SCPH (Bitfield-Mask: 0x01)                            */
#define SPIS_CTRLR0_FRF_Pos               (4UL)                     /*!< FRF (Bit 4)                                           */
#define SPIS_CTRLR0_FRF_Msk               (0x30UL)                  /*!< FRF (Bitfield-Mask: 0x03)                             */
#define SPIS_CTRLR0_DFS_Pos               (0UL)                     /*!< DFS (Bit 0)                                           */
#define SPIS_CTRLR0_DFS_Msk               (0xfUL)                   /*!< DFS (Bitfield-Mask: 0x0f)                             */
/* ========================================================  SSIENR  ========================================================= */
#define SPIS_SSIENR_NCS_MODE_Pos          (4UL)                     /*!< NCS_MODE (Bit 4)                                      */
#define SPIS_SSIENR_NCS_MODE_Msk          (0x30UL)                  /*!< NCS_MODE (Bitfield-Mask: 0x03)                        */
#define SPIS_SSIENR_FRX_MODE_Pos          (3UL)                     /*!< FRX_MODE (Bit 3)                                      */
#define SPIS_SSIENR_FRX_MODE_Msk          (0x8UL)                   /*!< FRX_MODE (Bitfield-Mask: 0x01)                        */
#define SPIS_SSIENR_FIFO_FEN_Pos          (2UL)                     /*!< FIFO_FEN (Bit 2)                                      */
#define SPIS_SSIENR_FIFO_FEN_Msk          (0x4UL)                   /*!< FIFO_FEN (Bitfield-Mask: 0x01)                        */
#define SPIS_SSIENR_MODE_3WIRE_Pos        (1UL)                     /*!< MODE_3WIRE (Bit 1)                                    */
#define SPIS_SSIENR_MODE_3WIRE_Msk        (0x2UL)                   /*!< MODE_3WIRE (Bitfield-Mask: 0x01)                      */
#define SPIS_SSIENR_SSI_EN_Pos            (0UL)                     /*!< SSI_EN (Bit 0)                                        */
#define SPIS_SSIENR_SSI_EN_Msk            (0x1UL)                   /*!< SSI_EN (Bitfield-Mask: 0x01)                          */
/* ========================================================  TXFTLR  ========================================================= */
#define SPIS_TXFTLR_TFT_Pos               (0UL)                     /*!< TFT (Bit 0)                                           */
#define SPIS_TXFTLR_TFT_Msk               (0xffUL)                  /*!< TFT (Bitfield-Mask: 0xff)                             */
/* ========================================================  RXFTLR  ========================================================= */
#define SPIS_RXFTLR_RFT_Pos               (0UL)                     /*!< RFT (Bit 0)                                           */
#define SPIS_RXFTLR_RFT_Msk               (0xffUL)                  /*!< RFT (Bitfield-Mask: 0xff)                             */
/* =========================================================  TXFLR  ========================================================= */
#define SPIS_TXFLR_TXTFL_Pos              (0UL)                     /*!< TXTFL (Bit 0)                                         */
#define SPIS_TXFLR_TXTFL_Msk              (0x1ffUL)                 /*!< TXTFL (Bitfield-Mask: 0x1ff)                          */
/* =========================================================  RXFLR  ========================================================= */
#define SPIS_RXFLR_RXTFL_Pos              (0UL)                     /*!< RXTFL (Bit 0)                                         */
#define SPIS_RXFLR_RXTFL_Msk              (0x1ffUL)                 /*!< RXTFL (Bitfield-Mask: 0x1ff)                          */
/* ==========================================================  SR  =========================================================== */
#define SPIS_SR_DCOL_Pos                  (6UL)                     /*!< DCOL (Bit 6)                                          */
#define SPIS_SR_DCOL_Msk                  (0x40UL)                  /*!< DCOL (Bitfield-Mask: 0x01)                            */
#define SPIS_SR_TXE_Pos                   (5UL)                     /*!< TXE (Bit 5)                                           */
#define SPIS_SR_TXE_Msk                   (0x20UL)                  /*!< TXE (Bitfield-Mask: 0x01)                             */
#define SPIS_SR_RFF_Pos                   (4UL)                     /*!< RFF (Bit 4)                                           */
#define SPIS_SR_RFF_Msk                   (0x10UL)                  /*!< RFF (Bitfield-Mask: 0x01)                             */
#define SPIS_SR_RFNE_Pos                  (3UL)                     /*!< RFNE (Bit 3)                                          */
#define SPIS_SR_RFNE_Msk                  (0x8UL)                   /*!< RFNE (Bitfield-Mask: 0x01)                            */
#define SPIS_SR_TFE_Pos                   (2UL)                     /*!< TFE (Bit 2)                                           */
#define SPIS_SR_TFE_Msk                   (0x4UL)                   /*!< TFE (Bitfield-Mask: 0x01)                             */
#define SPIS_SR_TFNF_Pos                  (1UL)                     /*!< TFNF (Bit 1)                                          */
#define SPIS_SR_TFNF_Msk                  (0x2UL)                   /*!< TFNF (Bitfield-Mask: 0x01)                            */
#define SPIS_SR_BUSY_Pos                  (0UL)                     /*!< BUSY (Bit 0)                                          */
#define SPIS_SR_BUSY_Msk                  (0x1UL)                   /*!< BUSY (Bitfield-Mask: 0x01)                            */
/* ==========================================================  IMR  ========================================================== */
#define SPIS_IMR_MSTIM_Pos                (5UL)                     /*!< MSTIM (Bit 5)                                         */
#define SPIS_IMR_MSTIM_Msk                (0x20UL)                  /*!< MSTIM (Bitfield-Mask: 0x01)                           */
#define SPIS_IMR_RXFIM_Pos                (4UL)                     /*!< RXFIM (Bit 4)                                         */
#define SPIS_IMR_RXFIM_Msk                (0x10UL)                  /*!< RXFIM (Bitfield-Mask: 0x01)                           */
#define SPIS_IMR_RXOIM_Pos                (3UL)                     /*!< RXOIM (Bit 3)                                         */
#define SPIS_IMR_RXOIM_Msk                (0x8UL)                   /*!< RXOIM (Bitfield-Mask: 0x01)                           */
#define SPIS_IMR_RXUIM_Pos                (2UL)                     /*!< RXUIM (Bit 2)                                         */
#define SPIS_IMR_RXUIM_Msk                (0x4UL)                   /*!< RXUIM (Bitfield-Mask: 0x01)                           */
#define SPIS_IMR_TXOIM_Pos                (1UL)                     /*!< TXOIM (Bit 1)                                         */
#define SPIS_IMR_TXOIM_Msk                (0x2UL)                   /*!< TXOIM (Bitfield-Mask: 0x01)                           */
#define SPIS_IMR_TXEIM_Pos                (0UL)                     /*!< TXEIM (Bit 0)                                         */
#define SPIS_IMR_TXEIM_Msk                (0x1UL)                   /*!< TXEIM (Bitfield-Mask: 0x01)                           */
/* ==========================================================  ISR  ========================================================== */
#define SPIS_ISR_MSTIS_Pos                (5UL)                     /*!< MSTIS (Bit 5)                                         */
#define SPIS_ISR_MSTIS_Msk                (0x20UL)                  /*!< MSTIS (Bitfield-Mask: 0x01)                           */
#define SPIS_ISR_RXFIS_Pos                (4UL)                     /*!< RXFIS (Bit 4)                                         */
#define SPIS_ISR_RXFIS_Msk                (0x10UL)                  /*!< RXFIS (Bitfield-Mask: 0x01)                           */
#define SPIS_ISR_RXOIS_Pos                (3UL)                     /*!< RXOIS (Bit 3)                                         */
#define SPIS_ISR_RXOIS_Msk                (0x8UL)                   /*!< RXOIS (Bitfield-Mask: 0x01)                           */
#define SPIS_ISR_RXUIS_Pos                (2UL)                     /*!< RXUIS (Bit 2)                                         */
#define SPIS_ISR_RXUIS_Msk                (0x4UL)                   /*!< RXUIS (Bitfield-Mask: 0x01)                           */
#define SPIS_ISR_TXOIS_Pos                (1UL)                     /*!< TXOIS (Bit 1)                                         */
#define SPIS_ISR_TXOIS_Msk                (0x2UL)                   /*!< TXOIS (Bitfield-Mask: 0x01)                           */
#define SPIS_ISR_TXEIS_Pos                (0UL)                     /*!< TXEIS (Bit 0)                                         */
#define SPIS_ISR_TXEIS_Msk                (0x1UL)                   /*!< TXEIS (Bitfield-Mask: 0x01)                           */
/* ==========================================================  ICR  ========================================================== */
#define SPIS_ICR_ICR_Pos                  (0UL)                     /*!< ICR (Bit 0)                                           */
#define SPIS_ICR_ICR_Msk                  (0x1UL)                   /*!< ICR (Bitfield-Mask: 0x01)                             */
/* =========================================================  DR16  ========================================================== */
#define SPIS_DR16_DR_Pos                  (0UL)                     /*!< DR (Bit 0)                                            */
#define SPIS_DR16_DR_Msk                  (0xffffUL)                /*!< DR (Bitfield-Mask: 0xffff)                            */


/* =========================================================================================================================== */
/* ================                                           TIMER                                           ================ */
/* =========================================================================================================================== */

/* ===================================================  TIMER0_LOAD_COUNT  =================================================== */
#define TIMER_TIMER0_LOAD_COUNT_TIMER0_LOAD_COUNT_Pos (0UL)         /*!< TIMER0_LOAD_COUNT (Bit 0)                             */
#define TIMER_TIMER0_LOAD_COUNT_TIMER0_LOAD_COUNT_Msk (0xffffUL)    /*!< TIMER0_LOAD_COUNT (Bitfield-Mask: 0xffff)             */
/* =================================================  TIMER0_CURRENT_VALUE  ================================================== */
#define TIMER_TIMER0_CURRENT_VALUE_TIMER0_CURRENT_VALUE_Pos (0UL)   /*!< TIMER0_CURRENT_VALUE (Bit 0)                          */
#define TIMER_TIMER0_CURRENT_VALUE_TIMER0_CURRENT_VALUE_Msk (0xffffUL) /*!< TIMER0_CURRENT_VALUE (Bitfield-Mask: 0xffff)       */
/* ==================================================  TIMER0_CONTROL_REG  =================================================== */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_POL_P_Pos (17UL)        /*!< TIMER0_PWM_POL_P (Bit 17)                             */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_POL_P_Msk (0x20000UL)   /*!< TIMER0_PWM_POL_P (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_POL_N_Pos (16UL)        /*!< TIMER0_PWM_POL_N (Bit 16)                             */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_POL_N_Msk (0x10000UL)   /*!< TIMER0_PWM_POL_N (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_DT_LEN_Pos (8UL)            /*!< TIMER0_DT_LEN (Bit 8)                                 */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_DT_LEN_Msk (0xff00UL)       /*!< TIMER0_DT_LEN (Bitfield-Mask: 0xff)                   */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_INIT_P_Pos (7UL)        /*!< TIMER0_PWM_INIT_P (Bit 7)                             */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_INIT_P_Msk (0x80UL)     /*!< TIMER0_PWM_INIT_P (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_INIT_N_Pos (6UL)        /*!< TIMER0_PWM_INIT_N (Bit 6)                             */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_INIT_N_Msk (0x40UL)     /*!< TIMER0_PWM_INIT_N (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_DT_EN_Pos (5UL)             /*!< TIMER0_DT_EN (Bit 5)                                  */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_DT_EN_Msk (0x20UL)          /*!< TIMER0_DT_EN (Bitfield-Mask: 0x01)                    */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_0N100PWM_EN_Pos (4UL)       /*!< TIMER0_0N100PWM_EN (Bit 4)                            */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_0N100PWM_EN_Msk (0x10UL)    /*!< TIMER0_0N100PWM_EN (Bitfield-Mask: 0x01)              */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_Pos (3UL)               /*!< TIMER0_PWM (Bit 3)                                    */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_PWM_Msk (0x8UL)             /*!< TIMER0_PWM (Bitfield-Mask: 0x01)                      */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_INTERRUPT_MASK_Pos (2UL)    /*!< TIMER0_INTERRUPT_MASK (Bit 2)                         */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_INTERRUPT_MASK_Msk (0x4UL)  /*!< TIMER0_INTERRUPT_MASK (Bitfield-Mask: 0x01)           */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_MODE_Pos (1UL)              /*!< TIMER0_MODE (Bit 1)                                   */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_MODE_Msk (0x2UL)            /*!< TIMER0_MODE (Bitfield-Mask: 0x01)                     */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_ENABLE_Pos (0UL)            /*!< TIMER0_ENABLE (Bit 0)                                 */
#define TIMER_TIMER0_CONTROL_REG_TIMER0_ENABLE_Msk (0x1UL)          /*!< TIMER0_ENABLE (Bitfield-Mask: 0x01)                   */
#define TIMER_TIMER0_CONTROL_REG_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define TIMER_TIMER0_CONTROL_REG_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  TIMER0_EOI  ======================================================= */
#define TIMER_TIMER0_EOI_TIMER0_EOI_Pos   (0UL)                     /*!< TIMER0_EOI (Bit 0)                                    */
#define TIMER_TIMER0_EOI_TIMER0_EOI_Msk   (0x1UL)                   /*!< TIMER0_EOI (Bitfield-Mask: 0x01)                      */
/* ===================================================  TIMER0_INT_STATUS  =================================================== */
#define TIMER_TIMER0_INT_STATUS_TIMER0_INT_STATUS_Pos (0UL)         /*!< TIMER0_INT_STATUS (Bit 0)                             */
#define TIMER_TIMER0_INT_STATUS_TIMER0_INT_STATUS_Msk (0x1UL)       /*!< TIMER0_INT_STATUS (Bitfield-Mask: 0x01)               */
/* ===================================================  TIMER1_LOAD_COUNT  =================================================== */
#define TIMER_TIMER1_LOAD_COUNT_TIMER1_LOAD_COUNT_Pos (0UL)         /*!< TIMER1_LOAD_COUNT (Bit 0)                             */
#define TIMER_TIMER1_LOAD_COUNT_TIMER1_LOAD_COUNT_Msk (0xffffUL)    /*!< TIMER1_LOAD_COUNT (Bitfield-Mask: 0xffff)             */
/* =================================================  TIMER1_CURRENT_VALUE  ================================================== */
#define TIMER_TIMER1_CURRENT_VALUE_TIMER1_CURRENT_VALUE_Pos (0UL)   /*!< TIMER1_CURRENT_VALUE (Bit 0)                          */
#define TIMER_TIMER1_CURRENT_VALUE_TIMER1_CURRENT_VALUE_Msk (0xffffUL) /*!< TIMER1_CURRENT_VALUE (Bitfield-Mask: 0xffff)       */
/* ==================================================  TIMER1_CONTROL_REG  =================================================== */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_POL_P_Pos (17UL)        /*!< TIMER1_PWM_POL_P (Bit 17)                             */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_POL_P_Msk (0x20000UL)   /*!< TIMER1_PWM_POL_P (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_POL_N_Pos (16UL)        /*!< TIMER1_PWM_POL_N (Bit 16)                             */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_POL_N_Msk (0x10000UL)   /*!< TIMER1_PWM_POL_N (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_DT_LEN_Pos (8UL)            /*!< TIMER1_DT_LEN (Bit 8)                                 */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_DT_LEN_Msk (0xff00UL)       /*!< TIMER1_DT_LEN (Bitfield-Mask: 0xff)                   */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_INIT_P_Pos (7UL)        /*!< TIMER1_PWM_INIT_P (Bit 7)                             */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_INIT_P_Msk (0x80UL)     /*!< TIMER1_PWM_INIT_P (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_INIT_N_Pos (6UL)        /*!< TIMER1_PWM_INIT_N (Bit 6)                             */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_INIT_N_Msk (0x40UL)     /*!< TIMER1_PWM_INIT_N (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_DT_EN_Pos (5UL)             /*!< TIMER1_DT_EN (Bit 5)                                  */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_DT_EN_Msk (0x20UL)          /*!< TIMER1_DT_EN (Bitfield-Mask: 0x01)                    */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_0N100PWM_EN_Pos (4UL)       /*!< TIMER1_0N100PWM_EN (Bit 4)                            */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_0N100PWM_EN_Msk (0x10UL)    /*!< TIMER1_0N100PWM_EN (Bitfield-Mask: 0x01)              */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_Pos (3UL)               /*!< TIMER1_PWM (Bit 3)                                    */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_PWM_Msk (0x8UL)             /*!< TIMER1_PWM (Bitfield-Mask: 0x01)                      */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_INTERRUPT_MASK_Pos (2UL)    /*!< TIMER1_INTERRUPT_MASK (Bit 2)                         */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_INTERRUPT_MASK_Msk (0x4UL)  /*!< TIMER1_INTERRUPT_MASK (Bitfield-Mask: 0x01)           */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_MODE_Pos (1UL)              /*!< TIMER1_MODE (Bit 1)                                   */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_MODE_Msk (0x2UL)            /*!< TIMER1_MODE (Bitfield-Mask: 0x01)                     */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_ENABLE_Pos (0UL)            /*!< TIMER1_ENABLE (Bit 0)                                 */
#define TIMER_TIMER1_CONTROL_REG_TIMER1_ENABLE_Msk (0x1UL)          /*!< TIMER1_ENABLE (Bitfield-Mask: 0x01)                   */
#define TIMER_TIMER1_CONTROL_REG_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define TIMER_TIMER1_CONTROL_REG_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  TIMER1_EOI  ======================================================= */
#define TIMER_TIMER1_EOI_TIMER1_EOI_Pos   (0UL)                     /*!< TIMER1_EOI (Bit 0)                                    */
#define TIMER_TIMER1_EOI_TIMER1_EOI_Msk   (0x1UL)                   /*!< TIMER1_EOI (Bitfield-Mask: 0x01)                      */
/* ===================================================  TIMER1_INT_STATUS  =================================================== */
#define TIMER_TIMER1_INT_STATUS_TIMER1_INT_STATUS_Pos (0UL)         /*!< TIMER1_INT_STATUS (Bit 0)                             */
#define TIMER_TIMER1_INT_STATUS_TIMER1_INT_STATUS_Msk (0x1UL)       /*!< TIMER1_INT_STATUS (Bitfield-Mask: 0x01)               */
/* ===================================================  TIMER2_LOAD_COUNT  =================================================== */
#define TIMER_TIMER2_LOAD_COUNT_TIMER2_LOAD_COUNT_Pos (0UL)         /*!< TIMER2_LOAD_COUNT (Bit 0)                             */
#define TIMER_TIMER2_LOAD_COUNT_TIMER2_LOAD_COUNT_Msk (0xffffUL)    /*!< TIMER2_LOAD_COUNT (Bitfield-Mask: 0xffff)             */
/* =================================================  TIMER2_CURRENT_VALUE  ================================================== */
#define TIMER_TIMER2_CURRENT_VALUE_TIMER2_CURRENT_VALUE_Pos (0UL)   /*!< TIMER2_CURRENT_VALUE (Bit 0)                          */
#define TIMER_TIMER2_CURRENT_VALUE_TIMER2_CURRENT_VALUE_Msk (0xffffUL) /*!< TIMER2_CURRENT_VALUE (Bitfield-Mask: 0xffff)       */
/* ==================================================  TIMER2_CONTROL_REG  =================================================== */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_POL_P_Pos (17UL)        /*!< TIMER2_PWM_POL_P (Bit 17)                             */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_POL_P_Msk (0x20000UL)   /*!< TIMER2_PWM_POL_P (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_POL_N_Pos (16UL)        /*!< TIMER2_PWM_POL_N (Bit 16)                             */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_POL_N_Msk (0x10000UL)   /*!< TIMER2_PWM_POL_N (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_DT_LEN_Pos (8UL)            /*!< TIMER2_DT_LEN (Bit 8)                                 */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_DT_LEN_Msk (0xff00UL)       /*!< TIMER2_DT_LEN (Bitfield-Mask: 0xff)                   */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_INIT_P_Pos (7UL)        /*!< TIMER2_PWM_INIT_P (Bit 7)                             */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_INIT_P_Msk (0x80UL)     /*!< TIMER2_PWM_INIT_P (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_INIT_N_Pos (6UL)        /*!< TIMER2_PWM_INIT_N (Bit 6)                             */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_INIT_N_Msk (0x40UL)     /*!< TIMER2_PWM_INIT_N (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_DT_EN_Pos (5UL)             /*!< TIMER2_DT_EN (Bit 5)                                  */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_DT_EN_Msk (0x20UL)          /*!< TIMER2_DT_EN (Bitfield-Mask: 0x01)                    */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_0N100PWM_EN_Pos (4UL)       /*!< TIMER2_0N100PWM_EN (Bit 4)                            */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_0N100PWM_EN_Msk (0x10UL)    /*!< TIMER2_0N100PWM_EN (Bitfield-Mask: 0x01)              */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_Pos (3UL)               /*!< TIMER2_PWM (Bit 3)                                    */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_PWM_Msk (0x8UL)             /*!< TIMER2_PWM (Bitfield-Mask: 0x01)                      */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_INTERRUPT_MASK_Pos (2UL)    /*!< TIMER2_INTERRUPT_MASK (Bit 2)                         */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_INTERRUPT_MASK_Msk (0x4UL)  /*!< TIMER2_INTERRUPT_MASK (Bitfield-Mask: 0x01)           */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_MODE_Pos (1UL)              /*!< TIMER2_MODE (Bit 1)                                   */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_MODE_Msk (0x2UL)            /*!< TIMER2_MODE (Bitfield-Mask: 0x01)                     */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_ENABLE_Pos (0UL)            /*!< TIMER2_ENABLE (Bit 0)                                 */
#define TIMER_TIMER2_CONTROL_REG_TIMER2_ENABLE_Msk (0x1UL)          /*!< TIMER2_ENABLE (Bitfield-Mask: 0x01)                   */
#define TIMER_TIMER2_CONTROL_REG_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define TIMER_TIMER2_CONTROL_REG_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  TIMER2_EOI  ======================================================= */
#define TIMER_TIMER2_EOI_TIMER2_EOI_Pos   (0UL)                     /*!< TIMER2_EOI (Bit 0)                                    */
#define TIMER_TIMER2_EOI_TIMER2_EOI_Msk   (0x1UL)                   /*!< TIMER2_EOI (Bitfield-Mask: 0x01)                      */
/* ===================================================  TIMER2_INT_STATUS  =================================================== */
#define TIMER_TIMER2_INT_STATUS_TIMER2_INT_STATUS_Pos (0UL)         /*!< TIMER2_INT_STATUS (Bit 0)                             */
#define TIMER_TIMER2_INT_STATUS_TIMER2_INT_STATUS_Msk (0x1UL)       /*!< TIMER2_INT_STATUS (Bitfield-Mask: 0x01)               */
/* ===================================================  TIMER3_LOAD_COUNT  =================================================== */
#define TIMER_TIMER3_LOAD_COUNT_TIMER3_LOAD_COUNT_Pos (0UL)         /*!< TIMER3_LOAD_COUNT (Bit 0)                             */
#define TIMER_TIMER3_LOAD_COUNT_TIMER3_LOAD_COUNT_Msk (0xffffUL)    /*!< TIMER3_LOAD_COUNT (Bitfield-Mask: 0xffff)             */
/* =================================================  TIMER3_CURRENT_VALUE  ================================================== */
#define TIMER_TIMER3_CURRENT_VALUE_TIMER3_CURRENT_VALUE_Pos (0UL)   /*!< TIMER3_CURRENT_VALUE (Bit 0)                          */
#define TIMER_TIMER3_CURRENT_VALUE_TIMER3_CURRENT_VALUE_Msk (0xffffUL) /*!< TIMER3_CURRENT_VALUE (Bitfield-Mask: 0xffff)       */
/* ==================================================  TIMER3_CONTROL_REG  =================================================== */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_POL_P_Pos (17UL)        /*!< TIMER3_PWM_POL_P (Bit 17)                             */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_POL_P_Msk (0x20000UL)   /*!< TIMER3_PWM_POL_P (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_POL_N_Pos (16UL)        /*!< TIMER3_PWM_POL_N (Bit 16)                             */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_POL_N_Msk (0x10000UL)   /*!< TIMER3_PWM_POL_N (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_DT_LEN_Pos (8UL)            /*!< TIMER3_DT_LEN (Bit 8)                                 */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_DT_LEN_Msk (0xff00UL)       /*!< TIMER3_DT_LEN (Bitfield-Mask: 0xff)                   */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_INIT_P_Pos (7UL)        /*!< TIMER3_PWM_INIT_P (Bit 7)                             */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_INIT_P_Msk (0x80UL)     /*!< TIMER3_PWM_INIT_P (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_INIT_N_Pos (6UL)        /*!< TIMER3_PWM_INIT_N (Bit 6)                             */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_INIT_N_Msk (0x40UL)     /*!< TIMER3_PWM_INIT_N (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_DT_EN_Pos (5UL)             /*!< TIMER3_DT_EN (Bit 5)                                  */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_DT_EN_Msk (0x20UL)          /*!< TIMER3_DT_EN (Bitfield-Mask: 0x01)                    */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_0N100PWM_EN_Pos (4UL)       /*!< TIMER3_0N100PWM_EN (Bit 4)                            */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_0N100PWM_EN_Msk (0x10UL)    /*!< TIMER3_0N100PWM_EN (Bitfield-Mask: 0x01)              */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_Pos (3UL)               /*!< TIMER3_PWM (Bit 3)                                    */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_PWM_Msk (0x8UL)             /*!< TIMER3_PWM (Bitfield-Mask: 0x01)                      */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_INTERRUPT_MASK_Pos (2UL)    /*!< TIMER3_INTERRUPT_MASK (Bit 2)                         */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_INTERRUPT_MASK_Msk (0x4UL)  /*!< TIMER3_INTERRUPT_MASK (Bitfield-Mask: 0x01)           */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_MODE_Pos (1UL)              /*!< TIMER3_MODE (Bit 1)                                   */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_MODE_Msk (0x2UL)            /*!< TIMER3_MODE (Bitfield-Mask: 0x01)                     */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_ENABLE_Pos (0UL)            /*!< TIMER3_ENABLE (Bit 0)                                 */
#define TIMER_TIMER3_CONTROL_REG_TIMER3_ENABLE_Msk (0x1UL)          /*!< TIMER3_ENABLE (Bitfield-Mask: 0x01)                   */
#define TIMER_TIMER3_CONTROL_REG_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define TIMER_TIMER3_CONTROL_REG_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  TIMER3_EOI  ======================================================= */
#define TIMER_TIMER3_EOI_TIMER3_EOI_Pos   (0UL)                     /*!< TIMER3_EOI (Bit 0)                                    */
#define TIMER_TIMER3_EOI_TIMER3_EOI_Msk   (0x1UL)                   /*!< TIMER3_EOI (Bitfield-Mask: 0x01)                      */
/* ===================================================  TIMER3_INT_STATUS  =================================================== */
#define TIMER_TIMER3_INT_STATUS_TIMER3_INT_STATUS_Pos (0UL)         /*!< TIMER3_INT_STATUS (Bit 0)                             */
#define TIMER_TIMER3_INT_STATUS_TIMER3_INT_STATUS_Msk (0x1UL)       /*!< TIMER3_INT_STATUS (Bitfield-Mask: 0x01)               */
/* ===================================================  TIMER4_LOAD_COUNT  =================================================== */
#define TIMER_TIMER4_LOAD_COUNT_TIMER4_LOAD_COUNT_Pos (0UL)         /*!< TIMER4_LOAD_COUNT (Bit 0)                             */
#define TIMER_TIMER4_LOAD_COUNT_TIMER4_LOAD_COUNT_Msk (0xffffUL)    /*!< TIMER4_LOAD_COUNT (Bitfield-Mask: 0xffff)             */
/* =================================================  TIMER4_CURRENT_VALUE  ================================================== */
#define TIMER_TIMER4_CURRENT_VALUE_TIMER4_CURRENT_VALUE_Pos (0UL)   /*!< TIMER4_CURRENT_VALUE (Bit 0)                          */
#define TIMER_TIMER4_CURRENT_VALUE_TIMER4_CURRENT_VALUE_Msk (0xffffUL) /*!< TIMER4_CURRENT_VALUE (Bitfield-Mask: 0xffff)       */
/* ==================================================  TIMER4_CONTROL_REG  =================================================== */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_POL_P_Pos (17UL)        /*!< TIMER4_PWM_POL_P (Bit 17)                             */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_POL_P_Msk (0x20000UL)   /*!< TIMER4_PWM_POL_P (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_POL_N_Pos (16UL)        /*!< TIMER4_PWM_POL_N (Bit 16)                             */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_POL_N_Msk (0x10000UL)   /*!< TIMER4_PWM_POL_N (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_DT_LEN_Pos (8UL)            /*!< TIMER4_DT_LEN (Bit 8)                                 */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_DT_LEN_Msk (0xff00UL)       /*!< TIMER4_DT_LEN (Bitfield-Mask: 0xff)                   */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_INIT_P_Pos (7UL)        /*!< TIMER4_PWM_INIT_P (Bit 7)                             */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_INIT_P_Msk (0x80UL)     /*!< TIMER4_PWM_INIT_P (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_INIT_N_Pos (6UL)        /*!< TIMER4_PWM_INIT_N (Bit 6)                             */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_INIT_N_Msk (0x40UL)     /*!< TIMER4_PWM_INIT_N (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_DT_EN_Pos (5UL)             /*!< TIMER4_DT_EN (Bit 5)                                  */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_DT_EN_Msk (0x20UL)          /*!< TIMER4_DT_EN (Bitfield-Mask: 0x01)                    */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_0N100PWM_EN_Pos (4UL)       /*!< TIMER4_0N100PWM_EN (Bit 4)                            */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_0N100PWM_EN_Msk (0x10UL)    /*!< TIMER4_0N100PWM_EN (Bitfield-Mask: 0x01)              */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_Pos (3UL)               /*!< TIMER4_PWM (Bit 3)                                    */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_PWM_Msk (0x8UL)             /*!< TIMER4_PWM (Bitfield-Mask: 0x01)                      */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_INTERRUPT_MASK_Pos (2UL)    /*!< TIMER4_INTERRUPT_MASK (Bit 2)                         */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_INTERRUPT_MASK_Msk (0x4UL)  /*!< TIMER4_INTERRUPT_MASK (Bitfield-Mask: 0x01)           */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_MODE_Pos (1UL)              /*!< TIMER4_MODE (Bit 1)                                   */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_MODE_Msk (0x2UL)            /*!< TIMER4_MODE (Bitfield-Mask: 0x01)                     */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_ENABLE_Pos (0UL)            /*!< TIMER4_ENABLE (Bit 0)                                 */
#define TIMER_TIMER4_CONTROL_REG_TIMER4_ENABLE_Msk (0x1UL)          /*!< TIMER4_ENABLE (Bitfield-Mask: 0x01)                   */
#define TIMER_TIMER4_CONTROL_REG_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define TIMER_TIMER4_CONTROL_REG_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  TIMER4_EOI  ======================================================= */
#define TIMER_TIMER4_EOI_TIMER4_EOI_Pos   (0UL)                     /*!< TIMER4_EOI (Bit 0)                                    */
#define TIMER_TIMER4_EOI_TIMER4_EOI_Msk   (0x1UL)                   /*!< TIMER4_EOI (Bitfield-Mask: 0x01)                      */
/* ===================================================  TIMER4_INT_STATUS  =================================================== */
#define TIMER_TIMER4_INT_STATUS_TIMER4_INT_STATUS_Pos (0UL)         /*!< TIMER4_INT_STATUS (Bit 0)                             */
#define TIMER_TIMER4_INT_STATUS_TIMER4_INT_STATUS_Msk (0x1UL)       /*!< TIMER4_INT_STATUS (Bitfield-Mask: 0x01)               */
/* ===================================================  TIMER5_LOAD_COUNT  =================================================== */
#define TIMER_TIMER5_LOAD_COUNT_TIMER5_LOAD_COUNT_Pos (0UL)         /*!< TIMER5_LOAD_COUNT (Bit 0)                             */
#define TIMER_TIMER5_LOAD_COUNT_TIMER5_LOAD_COUNT_Msk (0xffffUL)    /*!< TIMER5_LOAD_COUNT (Bitfield-Mask: 0xffff)             */
/* =================================================  TIMER5_CURRENT_VALUE  ================================================== */
#define TIMER_TIMER5_CURRENT_VALUE_TIMER5_CURRENT_VALUE_Pos (0UL)   /*!< TIMER5_CURRENT_VALUE (Bit 0)                          */
#define TIMER_TIMER5_CURRENT_VALUE_TIMER5_CURRENT_VALUE_Msk (0xffffUL) /*!< TIMER5_CURRENT_VALUE (Bitfield-Mask: 0xffff)       */
/* ==================================================  TIMER5_CONTROL_REG  =================================================== */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_POL_P_Pos (17UL)        /*!< TIMER5_PWM_POL_P (Bit 17)                             */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_POL_P_Msk (0x20000UL)   /*!< TIMER5_PWM_POL_P (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_POL_N_Pos (16UL)        /*!< TIMER5_PWM_POL_N (Bit 16)                             */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_POL_N_Msk (0x10000UL)   /*!< TIMER5_PWM_POL_N (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_DT_LEN_Pos (8UL)            /*!< TIMER5_DT_LEN (Bit 8)                                 */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_DT_LEN_Msk (0xff00UL)       /*!< TIMER5_DT_LEN (Bitfield-Mask: 0xff)                   */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_INIT_P_Pos (7UL)        /*!< TIMER5_PWM_INIT_P (Bit 7)                             */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_INIT_P_Msk (0x80UL)     /*!< TIMER5_PWM_INIT_P (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_INIT_N_Pos (6UL)        /*!< TIMER5_PWM_INIT_N (Bit 6)                             */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_INIT_N_Msk (0x40UL)     /*!< TIMER5_PWM_INIT_N (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_DT_EN_Pos (5UL)             /*!< TIMER5_DT_EN (Bit 5)                                  */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_DT_EN_Msk (0x20UL)          /*!< TIMER5_DT_EN (Bitfield-Mask: 0x01)                    */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_0N100PWM_EN_Pos (4UL)       /*!< TIMER5_0N100PWM_EN (Bit 4)                            */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_0N100PWM_EN_Msk (0x10UL)    /*!< TIMER5_0N100PWM_EN (Bitfield-Mask: 0x01)              */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_Pos (3UL)               /*!< TIMER5_PWM (Bit 3)                                    */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_PWM_Msk (0x8UL)             /*!< TIMER5_PWM (Bitfield-Mask: 0x01)                      */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_INTERRUPT_MASK_Pos (2UL)    /*!< TIMER5_INTERRUPT_MASK (Bit 2)                         */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_INTERRUPT_MASK_Msk (0x4UL)  /*!< TIMER5_INTERRUPT_MASK (Bitfield-Mask: 0x01)           */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_MODE_Pos (1UL)              /*!< TIMER5_MODE (Bit 1)                                   */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_MODE_Msk (0x2UL)            /*!< TIMER5_MODE (Bitfield-Mask: 0x01)                     */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_ENABLE_Pos (0UL)            /*!< TIMER5_ENABLE (Bit 0)                                 */
#define TIMER_TIMER5_CONTROL_REG_TIMER5_ENABLE_Msk (0x1UL)          /*!< TIMER5_ENABLE (Bitfield-Mask: 0x01)                   */
#define TIMER_TIMER5_CONTROL_REG_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define TIMER_TIMER5_CONTROL_REG_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  TIMER5_EOI  ======================================================= */
#define TIMER_TIMER5_EOI_TIMER5_EOI_Pos   (0UL)                     /*!< TIMER5_EOI (Bit 0)                                    */
#define TIMER_TIMER5_EOI_TIMER5_EOI_Msk   (0x1UL)                   /*!< TIMER5_EOI (Bitfield-Mask: 0x01)                      */
/* ===================================================  TIMER5_INT_STATUS  =================================================== */
#define TIMER_TIMER5_INT_STATUS_TIMER5_INT_STATUS_Pos (0UL)         /*!< TIMER5_INT_STATUS (Bit 0)                             */
#define TIMER_TIMER5_INT_STATUS_TIMER5_INT_STATUS_Msk (0x1UL)       /*!< TIMER5_INT_STATUS (Bitfield-Mask: 0x01)               */
/* ===================================================  TIMER6_LOAD_COUNT  =================================================== */
#define TIMER_TIMER6_LOAD_COUNT_TIMER6_LOAD_COUNT_Pos (0UL)         /*!< TIMER6_LOAD_COUNT (Bit 0)                             */
#define TIMER_TIMER6_LOAD_COUNT_TIMER6_LOAD_COUNT_Msk (0xffffUL)    /*!< TIMER6_LOAD_COUNT (Bitfield-Mask: 0xffff)             */
/* =================================================  TIMER6_CURRENT_VALUE  ================================================== */
#define TIMER_TIMER6_CURRENT_VALUE_TIMER6_CURRENT_VALUE_Pos (0UL)   /*!< TIMER6_CURRENT_VALUE (Bit 0)                          */
#define TIMER_TIMER6_CURRENT_VALUE_TIMER6_CURRENT_VALUE_Msk (0xffffUL) /*!< TIMER6_CURRENT_VALUE (Bitfield-Mask: 0xffff)       */
/* ==================================================  TIMER6_CONTROL_REG  =================================================== */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_POL_P_Pos (17UL)        /*!< TIMER6_PWM_POL_P (Bit 17)                             */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_POL_P_Msk (0x20000UL)   /*!< TIMER6_PWM_POL_P (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_POL_N_Pos (16UL)        /*!< TIMER6_PWM_POL_N (Bit 16)                             */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_POL_N_Msk (0x10000UL)   /*!< TIMER6_PWM_POL_N (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_DT_LEN_Pos (8UL)            /*!< TIMER6_DT_LEN (Bit 8)                                 */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_DT_LEN_Msk (0xff00UL)       /*!< TIMER6_DT_LEN (Bitfield-Mask: 0xff)                   */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_INIT_P_Pos (7UL)        /*!< TIMER6_PWM_INIT_P (Bit 7)                             */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_INIT_P_Msk (0x80UL)     /*!< TIMER6_PWM_INIT_P (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_INIT_N_Pos (6UL)        /*!< TIMER6_PWM_INIT_N (Bit 6)                             */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_INIT_N_Msk (0x40UL)     /*!< TIMER6_PWM_INIT_N (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_DT_EN_Pos (5UL)             /*!< TIMER6_DT_EN (Bit 5)                                  */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_DT_EN_Msk (0x20UL)          /*!< TIMER6_DT_EN (Bitfield-Mask: 0x01)                    */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_0N100PWM_EN_Pos (4UL)       /*!< TIMER6_0N100PWM_EN (Bit 4)                            */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_0N100PWM_EN_Msk (0x10UL)    /*!< TIMER6_0N100PWM_EN (Bitfield-Mask: 0x01)              */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_Pos (3UL)               /*!< TIMER6_PWM (Bit 3)                                    */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_PWM_Msk (0x8UL)             /*!< TIMER6_PWM (Bitfield-Mask: 0x01)                      */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_INTERRUPT_MASK_Pos (2UL)    /*!< TIMER6_INTERRUPT_MASK (Bit 2)                         */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_INTERRUPT_MASK_Msk (0x4UL)  /*!< TIMER6_INTERRUPT_MASK (Bitfield-Mask: 0x01)           */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_MODE_Pos (1UL)              /*!< TIMER6_MODE (Bit 1)                                   */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_MODE_Msk (0x2UL)            /*!< TIMER6_MODE (Bitfield-Mask: 0x01)                     */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_ENABLE_Pos (0UL)            /*!< TIMER6_ENABLE (Bit 0)                                 */
#define TIMER_TIMER6_CONTROL_REG_TIMER6_ENABLE_Msk (0x1UL)          /*!< TIMER6_ENABLE (Bitfield-Mask: 0x01)                   */
#define TIMER_TIMER6_CONTROL_REG_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define TIMER_TIMER6_CONTROL_REG_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  TIMER6_EOI  ======================================================= */
#define TIMER_TIMER6_EOI_TIMER6_EOI_Pos   (0UL)                     /*!< TIMER6_EOI (Bit 0)                                    */
#define TIMER_TIMER6_EOI_TIMER6_EOI_Msk   (0x1UL)                   /*!< TIMER6_EOI (Bitfield-Mask: 0x01)                      */
/* ===================================================  TIMER6_INT_STATUS  =================================================== */
#define TIMER_TIMER6_INT_STATUS_TIMER6_INT_STATUS_Pos (0UL)         /*!< TIMER6_INT_STATUS (Bit 0)                             */
#define TIMER_TIMER6_INT_STATUS_TIMER6_INT_STATUS_Msk (0x1UL)       /*!< TIMER6_INT_STATUS (Bitfield-Mask: 0x01)               */
/* ===================================================  TIMER7_LOAD_COUNT  =================================================== */
#define TIMER_TIMER7_LOAD_COUNT_TIMER7_LOAD_COUNT_Pos (0UL)         /*!< TIMER7_LOAD_COUNT (Bit 0)                             */
#define TIMER_TIMER7_LOAD_COUNT_TIMER7_LOAD_COUNT_Msk (0xffffUL)    /*!< TIMER7_LOAD_COUNT (Bitfield-Mask: 0xffff)             */
/* =================================================  TIMER7_CURRENT_VALUE  ================================================== */
#define TIMER_TIMER7_CURRENT_VALUE_TIMER7_CURRENT_VALUE_Pos (0UL)   /*!< TIMER7_CURRENT_VALUE (Bit 0)                          */
#define TIMER_TIMER7_CURRENT_VALUE_TIMER7_CURRENT_VALUE_Msk (0xffffUL) /*!< TIMER7_CURRENT_VALUE (Bitfield-Mask: 0xffff)       */
/* ==================================================  TIMER7_CONTROL_REG  =================================================== */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_POL_P_Pos (17UL)        /*!< TIMER7_PWM_POL_P (Bit 17)                             */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_POL_P_Msk (0x20000UL)   /*!< TIMER7_PWM_POL_P (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_POL_N_Pos (16UL)        /*!< TIMER7_PWM_POL_N (Bit 16)                             */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_POL_N_Msk (0x10000UL)   /*!< TIMER7_PWM_POL_N (Bitfield-Mask: 0x01)                */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_DT_LEN_Pos (8UL)            /*!< TIMER7_DT_LEN (Bit 8)                                 */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_DT_LEN_Msk (0xff00UL)       /*!< TIMER7_DT_LEN (Bitfield-Mask: 0xff)                   */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_INIT_P_Pos (7UL)        /*!< TIMER7_PWM_INIT_P (Bit 7)                             */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_INIT_P_Msk (0x80UL)     /*!< TIMER7_PWM_INIT_P (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_INIT_N_Pos (6UL)        /*!< TIMER7_PWM_INIT_N (Bit 6)                             */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_INIT_N_Msk (0x40UL)     /*!< TIMER7_PWM_INIT_N (Bitfield-Mask: 0x01)               */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_DT_EN_Pos (5UL)             /*!< TIMER7_DT_EN (Bit 5)                                  */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_DT_EN_Msk (0x20UL)          /*!< TIMER7_DT_EN (Bitfield-Mask: 0x01)                    */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_0N100PWM_EN_Pos (4UL)       /*!< TIMER7_0N100PWM_EN (Bit 4)                            */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_0N100PWM_EN_Msk (0x10UL)    /*!< TIMER7_0N100PWM_EN (Bitfield-Mask: 0x01)              */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_Pos (3UL)               /*!< TIMER7_PWM (Bit 3)                                    */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_PWM_Msk (0x8UL)             /*!< TIMER7_PWM (Bitfield-Mask: 0x01)                      */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_INTERRUPT_MASK_Pos (2UL)    /*!< TIMER7_INTERRUPT_MASK (Bit 2)                         */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_INTERRUPT_MASK_Msk (0x4UL)  /*!< TIMER7_INTERRUPT_MASK (Bitfield-Mask: 0x01)           */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_MODE_Pos (1UL)              /*!< TIMER7_MODE (Bit 1)                                   */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_MODE_Msk (0x2UL)            /*!< TIMER7_MODE (Bitfield-Mask: 0x01)                     */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_ENABLE_Pos (0UL)            /*!< TIMER7_ENABLE (Bit 0)                                 */
#define TIMER_TIMER7_CONTROL_REG_TIMER7_ENABLE_Msk (0x1UL)          /*!< TIMER7_ENABLE (Bitfield-Mask: 0x01)                   */
#define TIMER_TIMER7_CONTROL_REG_RESERVE_Pos (24UL)                 /*!< RESERVE (Bit 24)                                      */
#define TIMER_TIMER7_CONTROL_REG_RESERVE_Msk (0xff000000UL)         /*!< RESERVE (Bitfield-Mask: 0xff)                         */
/* ======================================================  TIMER7_EOI  ======================================================= */
#define TIMER_TIMER7_EOI_TIMER7_EOI_Pos   (0UL)                     /*!< TIMER7_EOI (Bit 0)                                    */
#define TIMER_TIMER7_EOI_TIMER7_EOI_Msk   (0x1UL)                   /*!< TIMER7_EOI (Bitfield-Mask: 0x01)                      */
/* ===================================================  TIMER7_INT_STATUS  =================================================== */
#define TIMER_TIMER7_INT_STATUS_TIMER7_INT_STATUS_Pos (0UL)         /*!< TIMER7_INT_STATUS (Bit 0)                             */
#define TIMER_TIMER7_INT_STATUS_TIMER7_INT_STATUS_Msk (0x1UL)       /*!< TIMER7_INT_STATUS (Bitfield-Mask: 0x01)               */
/* ===================================================  TIMERS_INT_STATUS  =================================================== */
#define TIMER_TIMERS_INT_STATUS_TIMERS_INT_STATUS_Pos (0UL)         /*!< TIMERS_INT_STATUS (Bit 0)                             */
#define TIMER_TIMERS_INT_STATUS_TIMERS_INT_STATUS_Msk (0xffUL)      /*!< TIMERS_INT_STATUS (Bitfield-Mask: 0xff)               */
/* ======================================================  TIMERS_EOI  ======================================================= */
#define TIMER_TIMERS_EOI_TIMERS_EOI_Pos   (0UL)                     /*!< TIMERS_EOI (Bit 0)                                    */
#define TIMER_TIMERS_EOI_TIMERS_EOI_Msk   (0xffUL)                  /*!< TIMERS_EOI (Bitfield-Mask: 0xff)                      */
/* =================================================  TIMERS_RAW_INT_STATUS  ================================================= */
#define TIMER_TIMERS_RAW_INT_STATUS_TIMERS_RAW_INT_STATUS_Pos (0UL) /*!< TIMERS_RAW_INT_STATUS (Bit 0)                         */
#define TIMER_TIMERS_RAW_INT_STATUS_TIMERS_RAW_INT_STATUS_Msk (0xffUL) /*!< TIMERS_RAW_INT_STATUS (Bitfield-Mask: 0xff)        */
/* ==================================================  TIMER0_LOAD_COUNT2  =================================================== */
#define TIMER_TIMER0_LOAD_COUNT2_TIMER0_LOAD_COUNT2_Pos (0UL)       /*!< TIMER0_LOAD_COUNT2 (Bit 0)                            */
#define TIMER_TIMER0_LOAD_COUNT2_TIMER0_LOAD_COUNT2_Msk (0xffffUL)  /*!< TIMER0_LOAD_COUNT2 (Bitfield-Mask: 0xffff)            */
/* ==================================================  TIMER1_LOAD_COUNT2  =================================================== */
#define TIMER_TIMER1_LOAD_COUNT2_TIMER1_LOAD_COUNT2_Pos (0UL)       /*!< TIMER1_LOAD_COUNT2 (Bit 0)                            */
#define TIMER_TIMER1_LOAD_COUNT2_TIMER1_LOAD_COUNT2_Msk (0xffffUL)  /*!< TIMER1_LOAD_COUNT2 (Bitfield-Mask: 0xffff)            */
/* ==================================================  TIMER2_LOAD_COUNT2  =================================================== */
#define TIMER_TIMER2_LOAD_COUNT2_TIMER2_LOAD_COUNT2_Pos (0UL)       /*!< TIMER2_LOAD_COUNT2 (Bit 0)                            */
#define TIMER_TIMER2_LOAD_COUNT2_TIMER2_LOAD_COUNT2_Msk (0xffffUL)  /*!< TIMER2_LOAD_COUNT2 (Bitfield-Mask: 0xffff)            */
/* ==================================================  TIMER3_LOAD_COUNT2  =================================================== */
#define TIMER_TIMER3_LOAD_COUNT2_TIMER3_LOAD_COUNT2_Pos (0UL)       /*!< TIMER3_LOAD_COUNT2 (Bit 0)                            */
#define TIMER_TIMER3_LOAD_COUNT2_TIMER3_LOAD_COUNT2_Msk (0xffffUL)  /*!< TIMER3_LOAD_COUNT2 (Bitfield-Mask: 0xffff)            */
/* ==================================================  TIMER4_LOAD_COUNT2  =================================================== */
#define TIMER_TIMER4_LOAD_COUNT2_TIMER4_LOAD_COUNT2_Pos (0UL)       /*!< TIMER4_LOAD_COUNT2 (Bit 0)                            */
#define TIMER_TIMER4_LOAD_COUNT2_TIMER4_LOAD_COUNT2_Msk (0xffffUL)  /*!< TIMER4_LOAD_COUNT2 (Bitfield-Mask: 0xffff)            */
/* ==================================================  TIMER5_LOAD_COUNT2  =================================================== */
#define TIMER_TIMER5_LOAD_COUNT2_TIMER5_LOAD_COUNT2_Pos (0UL)       /*!< TIMER5_LOAD_COUNT2 (Bit 0)                            */
#define TIMER_TIMER5_LOAD_COUNT2_TIMER5_LOAD_COUNT2_Msk (0xffffUL)  /*!< TIMER5_LOAD_COUNT2 (Bitfield-Mask: 0xffff)            */
/* ==================================================  TIMER6_LOAD_COUNT2  =================================================== */
#define TIMER_TIMER6_LOAD_COUNT2_TIMER6_LOAD_COUNT2_Pos (0UL)       /*!< TIMER6_LOAD_COUNT2 (Bit 0)                            */
#define TIMER_TIMER6_LOAD_COUNT2_TIMER6_LOAD_COUNT2_Msk (0xffffUL)  /*!< TIMER6_LOAD_COUNT2 (Bitfield-Mask: 0xffff)            */
/* ==================================================  TIMER7_LOAD_COUNT2  =================================================== */
#define TIMER_TIMER7_LOAD_COUNT2_TIMER7_LOAD_COUNT2_Pos (0UL)       /*!< TIMER7_LOAD_COUNT2 (Bit 0)                            */
#define TIMER_TIMER7_LOAD_COUNT2_TIMER7_LOAD_COUNT2_Msk (0xffffUL)  /*!< TIMER7_LOAD_COUNT2 (Bitfield-Mask: 0xffff)            */

/** @} */ /* End of group PosMask_peripherals */


/* =========================================================================================================================== */
/* ================                           Enumerated Values Peripheral Section                            ================ */
/* =========================================================================================================================== */


/** @addtogroup EnumValue_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                         SYS_CTRL                                          ================ */
/* =========================================================================================================================== */

/* =======================================================  REVISION  ======================================================== */
/* =======================================================  SYS_RESET  ======================================================= */
/* ======================================================  SYS_STATUS  ======================================================= */
/* ======================================================  LOCKUP_CTRL  ====================================================== */
/* ======================================================  SYS_CLKSEL  ======================================================= */
/* ===================================================  PWMTT_CLK_SYSSEL  ==================================================== */
/* =====================================================  PWMTT_CLK_SEL  ===================================================== */
/* ======================================================  PWM_OUT_SEL  ====================================================== */
/* =======================================================  BIST_CTRL  ======================================================= */
/* ======================================================  BIST_STATE  ======================================================= */
/* ===================================================  BIST_STATE_NORST  ==================================================== */
/* =======================================================  OTP_CTRL  ======================================================== */
/* =======================================================  OTP_PADDR  ======================================================= */
/* =======================================================  OTP_PDIN  ======================================================== */
/* =======================================================  OTP_PDOUT  ======================================================= */
/* =====================================================  OTP_PRG_STATE  ===================================================== */
/* =====================================================  OTP_PRG_CFG0  ====================================================== */
/* =====================================================  OTP_PRG_CFG1  ====================================================== */
/* ======================================================  CLKCAL_CTRL  ====================================================== */
/* =====================================================  CLKCAL_CLKSEL  ===================================================== */
/* ======================================================  CLKCAL_CNT0  ====================================================== */
/* ======================================================  CLKCAL_CNT1  ====================================================== */
/* ======================================================  SPIS0_CTRL  ======================================================= */
/* ========================================================  AON_RTC  ======================================================== */
/* ======================================================  AON_RTC_TO  ======================================================= */
/* ======================================================  AON_RTC_IRQ  ====================================================== */
/* =====================================================  LVD_CTRL_DIG  ====================================================== */
/* =====================================================  LVD_CTRL_ANA  ====================================================== */
/* ========================================================  WDT_SET  ======================================================== */
/* ========================================================  WDT_CFG  ======================================================== */
/* ======================================================  WDT_STATUS  ======================================================= */
/* ========================================================  SDMA_EN  ======================================================== */
/* =================================================  SDMA_TASK_TABLE_ADDR  ================================================== */
/* ======================================================  SDMA_ACTION  ====================================================== */
/* =====================================================  SDMA_TASK_VAL  ===================================================== */
/* ===================================================  SDMA_TASK_STATUS  ==================================================== */
/* ====================================================  SDMA_INT_STATUS  ==================================================== */
/* ====================================================  SDMA_INT_CLEAR  ===================================================== */


/* =========================================================================================================================== */
/* ================                                        GPIO_INOUT                                         ================ */
/* =========================================================================================================================== */

/* ====================================================  GPIO_FILT_CTRL  ===================================================== */
/* ========================================================  GPIO_I  ========================================================= */
/* ========================================================  GPIO_OE  ======================================================== */
/* ========================================================  GPIO_O  ========================================================= */
/* ======================================================  GPIO_O_SET  ======================================================= */
/* ======================================================  GPIO_O_CLR  ======================================================= */


/* =========================================================================================================================== */
/* ================                                         GPIO_INTR                                         ================ */
/* =========================================================================================================================== */

/* ========================================================  GPIO_IE  ======================================================== */
/* ========================================================  GPIO_IS  ======================================================== */
/* =======================================================  GPIO_MIS  ======================================================== */
/* ======================================================  GPIO_IT_HI  ======================================================= */
/* ======================================================  GPIO_IT_LO  ======================================================= */
/* =====================================================  GPIO_IT_PEDGE  ===================================================== */
/* =====================================================  GPIO_IT_NEDGE  ===================================================== */


/* =========================================================================================================================== */
/* ================                                         GPIO_ATF                                          ================ */
/* =========================================================================================================================== */

/* ======================================================  GPIO_CFG_0  ======================================================= */
/* ======================================================  GPIO_CFG_1  ======================================================= */
/* ======================================================  GPIO_CFG_2  ======================================================= */
/* ======================================================  GPIO_CFG_3  ======================================================= */
/* ======================================================  GPIO_CFG_4  ======================================================= */
/* ======================================================  GPIO_CFG_5  ======================================================= */


/* =========================================================================================================================== */
/* ================                                         QDEC_CTRL                                         ================ */
/* =========================================================================================================================== */

/* =======================================================  QDEC_DIV  ======================================================== */
/* =======================================================  QDEC_CTRL  ======================================================= */
/* =======================================================  LED_CTRL  ======================================================== */


/* =========================================================================================================================== */
/* ================                                         QDEC_INTR                                         ================ */
/* =========================================================================================================================== */

/* ========================================================  QDEC_IE  ======================================================== */
/* ========================================================  QDEC_IS  ======================================================== */
/* =======================================================  QDEC_MIS  ======================================================== */


/* =========================================================================================================================== */
/* ================                                        QDEC_X_AXIS                                        ================ */
/* =========================================================================================================================== */

/* ========================================================  X_SAMP  ========================================================= */
/* ========================================================  X_READ  ========================================================= */
/* =========================================================  X_ACC  ========================================================= */
/* ======================================================  X_ACC_LOAD  ======================================================= */
/* =======================================================  X_ACCDBL  ======================================================== */
/* =====================================================  X_ACCDBL_LOAD  ===================================================== */


/* =========================================================================================================================== */
/* ================                                        QDEC_Y_AXIS                                        ================ */
/* =========================================================================================================================== */

/* ========================================================  Y_SAMP  ========================================================= */
/* ========================================================  Y_READ  ========================================================= */
/* =========================================================  Y_ACC  ========================================================= */
/* ======================================================  Y_ACC_LOAD  ======================================================= */
/* =======================================================  Y_ACCDBL  ======================================================== */
/* =====================================================  Y_ACCDBL_LOAD  ===================================================== */


/* =========================================================================================================================== */
/* ================                                        QDEC_Z_AXIS                                        ================ */
/* =========================================================================================================================== */

/* ========================================================  Z_SAMP  ========================================================= */
/* ========================================================  Z_READ  ========================================================= */
/* =========================================================  Z_ACC  ========================================================= */
/* ======================================================  Z_ACC_LOAD  ======================================================= */
/* =======================================================  Z_ACCDBL  ======================================================== */
/* =====================================================  Z_ACCDBL_LOAD  ===================================================== */


/* =========================================================================================================================== */
/* ================                                         KEYSCAN                                          ================ */
/* =========================================================================================================================== */

/* =======================================================  KB_CTRL0  ======================================================== */
/* =======================================================  KB_CTRL1  ======================================================== */
/* ========================================================  KB_INTR  ======================================================== */
/* =======================================================  KB_INFO0  ======================================================== */
/* =======================================================  KB_INFO1  ======================================================== */
/* =======================================================  KB_INFO2  ======================================================== */
/* ========================================================  KB_STS0  ======================================================== */
/* ========================================================  KB_STS1  ======================================================== */
/* ========================================================  KB_STS2  ======================================================== */


/* =========================================================================================================================== */
/* ================                                        LEDC_CTRL                                         ================ */
/* =========================================================================================================================== */

/* =========================================================  CTRL0  ========================================================= */
/* =========================================================  CTRL1  ========================================================= */
/* =======================================================  TBL_SADDR  ======================================================= */
/* =======================================================  TBL_EADDR  ======================================================= */


/* =========================================================================================================================== */
/* ================                                        LEDC_MODU                                         ================ */
/* =========================================================================================================================== */

/* =======================================================  BIT0_MODU  ======================================================= */
/* =======================================================  BIT1_MODU  ======================================================= */


/* =========================================================================================================================== */
/* ================                                         LEDC_NUM                                         ================ */
/* =========================================================================================================================== */

/* ======================================================  CHANGE_NUM1  ====================================================== */
/* ======================================================  CHANGE_NUM2  ====================================================== */
/* ======================================================  CHANGE_NUM3  ====================================================== */
/* ======================================================  CHANGE_NUM4  ====================================================== */
/* ======================================================  CHANGE_NUM5  ====================================================== */
/* ======================================================  CHANGE_NUM6  ====================================================== */
/* ======================================================  REPEAT_NUM1  ====================================================== */
/* ======================================================  REPEAT_NUM2  ====================================================== */
/* ======================================================  REPEAT_NUM3  ====================================================== */
/* ======================================================  REPEAT_NUM4  ====================================================== */
/* ======================================================  REPEAT_NUM5  ====================================================== */
/* ======================================================  REPEAT_NUM6  ====================================================== */


/* =========================================================================================================================== */
/* ================                                         LEDC_IRQ                                         ================ */
/* =========================================================================================================================== */

/* ========================================================  DMA_IE  ========================================================= */
/* ========================================================  DMA_IS  ========================================================= */
/* ========================================================  DMA_MIS  ======================================================== */


/* =========================================================================================================================== */
/* ================                                       LEDC_STATUS                                        ================ */
/* =========================================================================================================================== */

/* =======================================================  TBL_ADDR  ======================================================== */
/* =======================================================  DESC_ADDR  ======================================================= */
/* =======================================================  DATA_ADDR  ======================================================= */
/* ========================================================  STATUS  ========================================================= */


/* =========================================================================================================================== */
/* ================                                         GPADC_ANA                                         ================ */
/* =========================================================================================================================== */

/* =======================================================  GPADC_EN  ======================================================== */
/* ======================================================  GPADC_CTRL  ======================================================= */
/* =======================================================  GPADC_CFG  ======================================================= */


/* =========================================================================================================================== */
/* ================                                         GPADC_DIG                                         ================ */
/* =========================================================================================================================== */

/* =====================================================  GPADC_ACTION  ====================================================== */
/* =======================================================  GPADC_CFG  ======================================================= */
/* ====================================================  GPADC_INT_CTRL  ===================================================== */
/* ======================================================  GPADC_SAMP  ======================================================= */
/* ================================================  GPADC_CLK_CTRL_24_sub_0  ================================================ */
/* ================================================  GPADC_CLK_CTRL_24_sub_1  ================================================ */
/* ================================================  GPADC_CLK_CTRL_24_sub_2  ================================================ */


/* =========================================================================================================================== */
/* ================                                         AON_CTRL                                          ================ */
/* =========================================================================================================================== */

/* =======================================================  AON_CTRL0  ======================================================= */
/* ======================================================  SLEEP_TIME  ======================================================= */
/* =====================================================  WAKEUP_CTRL0  ====================================================== */
/* =====================================================  WAKEUP_CTRL1  ====================================================== */
/* =====================================================  WAKEUP_CLEAR  ====================================================== */
/* =====================================================  WAKEUP_RECORD  ===================================================== */
/* =======================================================  QSPI_CTRL  ======================================================= */
/* =====================================================  QSPI_CMD_CFG  ====================================================== */
/* =====================================================  SET_SCAN_MODE  ===================================================== */
/* ========================================================  GOSLEEP  ======================================================== */
/* =======================================================  GPIO_HOLD  ======================================================= */
/* =======================================================  RTC_CTRL  ======================================================== */
/* ========================================================  RTC_VAL  ======================================================== */
/* =======================================================  KB_WKUP0  ======================================================== */
/* =======================================================  KB_WKUP1  ======================================================== */
/* ========================================================  KB_STS  ========================================================= */
/* ======================================================  CPU_RST_RCD  ====================================================== */
/* ======================================================  CPU_RST_CLR  ====================================================== */
/* ====================================================  RST_IGNORE_CTRL  ==================================================== */
/* =====================================================  SOFT_RECORD4  ====================================================== */
/* =====================================================  SOFT_RECORD6  ====================================================== */
/* ======================================================  RCO24M_CFG  ======================================================= */
/* ======================================================  RCO32K_CFG  ======================================================= */
/* ====================================================  XO_CFG_24_sub_0  ==================================================== */
/* ====================================================  XO_CFG_24_sub_1  ==================================================== */
/* ====================================================  XO_CFG_24_sub_2  ==================================================== */


/* =========================================================================================================================== */
/* ================                                         FPGA_CTRL                                         ================ */
/* =========================================================================================================================== */

/* =====================================================  FPGA_REVISION  ===================================================== */
/* =======================================================  FPGA_CTRL  ======================================================= */
/* =======================================================  AGC_STATE  ======================================================= */


/* =========================================================================================================================== */
/* ================                                     FPGA_CTRL_AD9961                                      ================ */
/* =========================================================================================================================== */

/* =======================================================  SPI_CTRL  ======================================================== */
/* ========================================================  SPI_CMD  ======================================================== */
/* =======================================================  SPI_WDATA  ======================================================= */
/* =======================================================  SPI_RDATA  ======================================================= */
/* ======================================================  AD9961_TRX  ======================================================= */
/* =====================================================  AD9961_RAM_0  ====================================================== */
/* =====================================================  AD9961_RAM_1  ====================================================== */
/* ======================================================  AD9961_LOOP  ====================================================== */
/* ===================================================  AD9961_RAM_RDATA  ==================================================== */
/* ======================================================  AD9961_ADC  ======================================================= */
/* =====================================================  AD9961_STATUS  ===================================================== */
/* ======================================================  AD9961_MODE  ====================================================== */
/* ===================================================  AD9961_DAC_OFFSET  =================================================== */
/* =================================================  AD9961_DAC_OFST_TIME  ================================================== */
/* =================================================  AD9961_DAC_OFST_RMEN  ================================================== */


/* =========================================================================================================================== */
/* ================                                     FPGA_CTRL_MAX2829                                     ================ */
/* =========================================================================================================================== */

/* ===================================================  MAX2829_SPI_CTRL0  =================================================== */
/* ===================================================  MAX2829_SPI_CTRL1  =================================================== */
/* ===================================================  MAX2829_PIN_CTRL  ==================================================== */
/* ===================================================  MAX2829_GAIN_CTRL  =================================================== */
/* =======================================================  AGC_MODE  ======================================================== */
/* ========================================================  AGC_VAL  ======================================================== */
/* ========================================================  AGC_LNA  ======================================================== */
/* =====================================================  AGC_SIG_LEVEL  ===================================================== */
/* ====================================================  AGC_NOISE_LEVEL  ==================================================== */
/* =====================================================  FPGA_GPIO_OE  ====================================================== */
/* ======================================================  FPGA_GPIO_O  ====================================================== */
/* ======================================================  FPGA_GPIO_I  ====================================================== */
/* =======================================================  GPADC_EN  ======================================================== */
/* =====================================================  GPADC_CLK_DIV  ===================================================== */
/* ======================================================  GPADC_SAMP  ======================================================= */
/* ======================================================  GPADC_VALUE  ====================================================== */
/* =====================================================  PW_GPIO_CTRL  ====================================================== */
/* ======================================================  PW_GPIO_CNT  ====================================================== */
/* =======================================================  TX_EN_CNT  ======================================================= */
/* =====================================================  SYNC_DET_CNT  ====================================================== */
/* ======================================================  FPGA_CNT_EN  ====================================================== */


/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  RBR  ========================================================== */
/* ==========================================================  THR  ========================================================== */
/* ==========================================================  DLL  ========================================================== */
/* ==========================================================  DLH  ========================================================== */
/* ==========================================================  IER  ========================================================== */
/* ==========================================================  IIR  ========================================================== */
/* ==========================================================  FCR  ========================================================== */
/* ==========================================================  LCR  ========================================================== */
/* ==========================================================  MCR  ========================================================== */
/* ==========================================================  LSR  ========================================================== */
/* ==========================================================  MSR  ========================================================== */
/* ==========================================================  USR  ========================================================== */
/* ==========================================================  TCR  ========================================================== */
/* ==========================================================  DLF  ========================================================== */
/* ========================================================  LCR_EXT  ======================================================== */


/* =========================================================================================================================== */
/* ================                                           SPIM                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  CTRLR0  ========================================================= */
/* ========================================================  CTRLR1  ========================================================= */
/* ========================================================  SSIENR  ========================================================= */
/* ==========================================================  SER  ========================================================== */
/* =========================================================  BAUDR  ========================================================= */
/* ========================================================  TXFTLR  ========================================================= */
/* ========================================================  RXFTLR  ========================================================= */
/* =========================================================  TXFLR  ========================================================= */
/* =========================================================  RXFLR  ========================================================= */
/* ==========================================================  SR  =========================================================== */
/* ==========================================================  IMR  ========================================================== */
/* ==========================================================  ISR  ========================================================== */
/* ==========================================================  ICR  ========================================================== */
/* =========================================================  DR16  ========================================================== */


/* =========================================================================================================================== */
/* ================                                            IIC                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  IC_CON  ========================================================= */
/* ========================================================  IC_TAR  ========================================================= */
/* ========================================================  IC_SAR  ========================================================= */
/* ======================================================  IC_DATA_CMD  ====================================================== */
/* ====================================================  IC_SS_SCL_HCNT  ===================================================== */
/* ====================================================  IC_SS_SCL_LCNT  ===================================================== */
/* ====================================================  IC_FS_SCL_HCNT  ===================================================== */
/* ====================================================  IC_FS_SCL_LCNT  ===================================================== */
/* =====================================================  IC_INTR_STAT  ====================================================== */
/* =====================================================  IC_INTR_MASK  ====================================================== */
/* ===================================================  IC_RAW_INTR_STAT  ==================================================== */
/* =======================================================  IC_RX_TL  ======================================================== */
/* =======================================================  IC_TX_TL  ======================================================== */
/* ======================================================  IC_CLR_INTR  ====================================================== */
/* ====================================================  IC_CLR_RX_UNDER  ==================================================== */
/* ====================================================  IC_CLR_RX_OVER  ===================================================== */
/* ====================================================  IC_CLR_TX_OVER  ===================================================== */
/* =====================================================  IC_CLR_RD_REQ  ===================================================== */
/* ====================================================  IC_CLR_TX_ABRT  ===================================================== */
/* ====================================================  IC_CLR_RX_DONE  ===================================================== */
/* ====================================================  IC_CLR_ACTIVITY  ==================================================== */
/* ====================================================  IC_CLR_STOP_DET  ==================================================== */
/* ===================================================  IC_CLR_START_DET  ==================================================== */
/* =======================================================  IC_ENABLE  ======================================================= */
/* =======================================================  IC_TXFLR  ======================================================== */
/* =======================================================  IC_RXFLR  ======================================================== */


/* =========================================================================================================================== */
/* ================                                           SPIS                                            ================ */
/* =========================================================================================================================== */

/* ========================================================  CTRLR0  ========================================================= */
/* ========================================================  SSIENR  ========================================================= */
/* ========================================================  TXFTLR  ========================================================= */
/* ========================================================  RXFTLR  ========================================================= */
/* =========================================================  TXFLR  ========================================================= */
/* =========================================================  RXFLR  ========================================================= */
/* ==========================================================  SR  =========================================================== */
/* ==========================================================  IMR  ========================================================== */
/* ==========================================================  ISR  ========================================================== */
/* ==========================================================  ICR  ========================================================== */
/* =========================================================  DR16  ========================================================== */


/* =========================================================================================================================== */
/* ================                                           TIMER                                           ================ */
/* =========================================================================================================================== */

/* ===================================================  TIMER0_LOAD_COUNT  =================================================== */
/* =================================================  TIMER0_CURRENT_VALUE  ================================================== */
/* ==================================================  TIMER0_CONTROL_REG  =================================================== */
/* ======================================================  TIMER0_EOI  ======================================================= */
/* ===================================================  TIMER0_INT_STATUS  =================================================== */
/* ===================================================  TIMER1_LOAD_COUNT  =================================================== */
/* =================================================  TIMER1_CURRENT_VALUE  ================================================== */
/* ==================================================  TIMER1_CONTROL_REG  =================================================== */
/* ======================================================  TIMER1_EOI  ======================================================= */
/* ===================================================  TIMER1_INT_STATUS  =================================================== */
/* ===================================================  TIMER2_LOAD_COUNT  =================================================== */
/* =================================================  TIMER2_CURRENT_VALUE  ================================================== */
/* ==================================================  TIMER2_CONTROL_REG  =================================================== */
/* ======================================================  TIMER2_EOI  ======================================================= */
/* ===================================================  TIMER2_INT_STATUS  =================================================== */
/* ===================================================  TIMER3_LOAD_COUNT  =================================================== */
/* =================================================  TIMER3_CURRENT_VALUE  ================================================== */
/* ==================================================  TIMER3_CONTROL_REG  =================================================== */
/* ======================================================  TIMER3_EOI  ======================================================= */
/* ===================================================  TIMER3_INT_STATUS  =================================================== */
/* ===================================================  TIMER4_LOAD_COUNT  =================================================== */
/* =================================================  TIMER4_CURRENT_VALUE  ================================================== */
/* ==================================================  TIMER4_CONTROL_REG  =================================================== */
/* ======================================================  TIMER4_EOI  ======================================================= */
/* ===================================================  TIMER4_INT_STATUS  =================================================== */
/* ===================================================  TIMER5_LOAD_COUNT  =================================================== */
/* =================================================  TIMER5_CURRENT_VALUE  ================================================== */
/* ==================================================  TIMER5_CONTROL_REG  =================================================== */
/* ======================================================  TIMER5_EOI  ======================================================= */
/* ===================================================  TIMER5_INT_STATUS  =================================================== */
/* ===================================================  TIMER6_LOAD_COUNT  =================================================== */
/* =================================================  TIMER6_CURRENT_VALUE  ================================================== */
/* ==================================================  TIMER6_CONTROL_REG  =================================================== */
/* ======================================================  TIMER6_EOI  ======================================================= */
/* ===================================================  TIMER6_INT_STATUS  =================================================== */
/* ===================================================  TIMER7_LOAD_COUNT  =================================================== */
/* =================================================  TIMER7_CURRENT_VALUE  ================================================== */
/* ==================================================  TIMER7_CONTROL_REG  =================================================== */
/* ======================================================  TIMER7_EOI  ======================================================= */
/* ===================================================  TIMER7_INT_STATUS  =================================================== */
/* ===================================================  TIMERS_INT_STATUS  =================================================== */
/* ======================================================  TIMERS_EOI  ======================================================= */
/* =================================================  TIMERS_RAW_INT_STATUS  ================================================= */
/* ==================================================  TIMER0_LOAD_COUNT2  =================================================== */
/* ==================================================  TIMER1_LOAD_COUNT2  =================================================== */
/* ==================================================  TIMER2_LOAD_COUNT2  =================================================== */
/* ==================================================  TIMER3_LOAD_COUNT2  =================================================== */
/* ==================================================  TIMER4_LOAD_COUNT2  =================================================== */
/* ==================================================  TIMER5_LOAD_COUNT2  =================================================== */
/* ==================================================  TIMER6_LOAD_COUNT2  =================================================== */
/* ==================================================  TIMER7_LOAD_COUNT2  =================================================== */

/** @} */ /* End of group EnumValue_peripherals */


#ifdef __cplusplus
}
#endif

#endif  /* _T1001_H_ */
