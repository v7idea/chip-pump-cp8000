/*************************************************************************************************
 * @file       mcu.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-03-08
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __MCU_H_
#define __MCU_H_

#include <stdint.h>
#include "csi_rv32_gcc.h"
#include "core_rv32.h"


#define  ATTRIBUTE_ISR      __attribute__ ((interrupt ("machine")))
#define  ATTRIBUTE_WEAK    __attribute__((weak))
#define  __PACKED           __attribute__ ((__packed__))
#define __FLASH_CODE_SECTION  __attribute__((noinline, section(".flash_code_section")))
#define __RAM_CODE_SECTION  __attribute__((noinline, section(".ram_code_section")))

typedef void(*VECTOR_TABLE_Type)(void);
typedef void (*isr_t)(void);

#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#define NVIC_EnableIRQ(IRQn) csi_vic_enable_irq(IRQn)
#define NVIC_SetPriority(IRQn, priority) csi_vic_set_prio(IRQn, priority)

typedef struct
{
    uint32_t const* src;
    uint32_t* dest;
    uint32_t  wlen;
} __copy_table_t;

typedef struct
{
    uint32_t* dest;
    uint32_t  wlen;
} __zero_table_t;


#define REG_SYS_RESET (8)
#define RESET_UART(idx) \
do \
{ \
    *(volatile uint32_t *)(SYS_CTRL_BASE + REG_SYS_RESET) = (1 << (10 + idx));  \
    for(volatile int i = 0; i < 10; i++); \
    *(volatile uint32_t *)(SYS_CTRL_BASE + REG_SYS_RESET) = 0;  \
}while(0)

#define WDT_SET_ADDR  0x100
#define WDT_DEFAULT_TIME_S  5000
#define WDT_FEED()         (*(volatile uint32_t *)(SYS_CTRL_BASE + WDT_SET_ADDR) = ((32000 - WDT_DEFAULT_TIME_S)/125))
#define WDT_DIS()          (*(volatile uint32_t *)(SYS_CTRL_BASE + WDT_SET_ADDR + 0x04) = 0)
#define WDT_EN()           (*(volatile uint32_t *)(SYS_CTRL_BASE + WDT_SET_ADDR + 0x04) = 1)
#define WDT_RST()          { \
    (*(volatile uint32_t *)(SYS_CTRL_BASE + WDT_SET_ADDR) = ((32000 - 125)/125)); \
    (*(volatile uint32_t *)(SYS_CTRL_BASE + WDT_SET_ADDR + 0x04) = 1); \
    while (1); \
}

#define REG_RD(addr)        (*(volatile uint32_t *)addr)
#define REG_WRT(addr, val)  (*(volatile uint32_t *)addr = val)

#define REG_CLR_BIT(addr, pos)  (*(volatile uint32_t *)addr &= (~(1 << pos)))
#define REG_SET_BIT(addr, pos)  (*(volatile uint32_t *)addr |= (1 << pos))

#define REG_WRT_BITS(addr, msb, lsb, val)  \
do \
{ \
    uint32_t  msk =  (((1 << (msb - lsb + 1)) - 1) << lsb);  \
    uint32_t  tmp =  *(volatile uint32_t *)addr; \
    tmp &= (~msk); \
    tmp |= (val << lsb); \
    *(volatile uint32_t *)addr = tmp;  \
} while (0)


#ifndef FlagStatus
#ifndef IS_FLAG_STATUS_RESET
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
#define IS_FLAG_STATUS_RESET(state) ((state== RESET) || (state == RESET))
#endif
#endif

#ifndef FunctionalState
#ifndef IS_FUNCTIONAL_STATE
typedef enum {DISABLE = 0, ENABLE =1} FunctionalState;
#define IS_FUNCTIONAL_STATE(state) ((state== DISABLE) || (state == ENABLE))
#endif
#endif
#define ATOMIC_SECTION_BEGIN()                                                         \
    do                                                                                 \
    {                                                                                  \
		int irq_rest;                                                                  \
        __asm__ volatile ("csrrci %0, mstatus, %1" : "=r" (irq_rest) : "i" (INTE_EN)); \
	} while(0);
	 
#define ATOMIC_SECTION_END()                                                           \
    do                                                                                 \
	{                                                                                  \
		int irq_rest;                                                                  \
    /* Restore mstatus to its previous value */                                        \
	__asm__ volatile ("csrrsi %0, mstatus, %1" : "=r" (irq_rest) : "i" (INTE_EN));     \
   } while(0);
   
typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;

#define assert_param 

#define ROM_HOOK_INDEX_DECLAR(_x) ROM_HOOK_##_x##_INDEX
#define ROM_HOOK_ITEM_FUNCTION(_x) _x##_Hook

enum ROM_HOOK_TABLE_INDEX
{
    /* t1001_radio.c */
    ROM_HOOK_INDEX_DECLAR(RADIO_CommonDescInit_SetFreq),
    ROM_HOOK_INDEX_DECLAR(RADIO_StartDmaWithCheck),

    /* t1001_bt.c */
    ROM_HOOK_INDEX_DECLAR(RF_BT_EventPrepare),
    ROM_HOOK_INDEX_DECLAR(RF_BT_SendWork),
    ROM_HOOK_INDEX_DECLAR(RF_BT_ReceiveWork),

    /* hci_driver.c */
    ROM_HOOK_INDEX_DECLAR(hci_driver_send_to_upstack),
    ROM_HOOK_INDEX_DECLAR(hci_driver_node_rx_process),

    /* hci.c */
    ROM_HOOK_INDEX_DECLAR(link_control_cmd_handle),
    ROM_HOOK_INDEX_DECLAR(ctrl_bb_cmd_handle),
    ROM_HOOK_INDEX_DECLAR(info_cmd_handle),
    ROM_HOOK_INDEX_DECLAR(status_cmd_handle),
    ROM_HOOK_INDEX_DECLAR(controller_cmd_handle),
    ROM_HOOK_INDEX_DECLAR(hci_vendor_cmd_handle),
    ROM_HOOK_INDEX_DECLAR(hci_cmd_handle),
    ROM_HOOK_INDEX_DECLAR(hci_acl_handle),
    ROM_HOOK_INDEX_DECLAR(hci_acl_encode),
    ROM_HOOK_INDEX_DECLAR(hci_evt_encode),
    ROM_HOOK_INDEX_DECLAR(hci_msg_polling_work),
    ROM_HOOK_INDEX_DECLAR(hci_init),

    /* ll_adv.c */
    ROM_HOOK_INDEX_DECLAR(ll_adv_enable),
    ROM_HOOK_INDEX_DECLAR(isr_adv_send_timer_cb),
    ROM_HOOK_INDEX_DECLAR(ll_adv_sched),

    /* ll_sch.c */
    ROM_HOOK_INDEX_DECLAR(ll_sch_prepare),
    ROM_HOOK_INDEX_DECLAR(ll_sch_release_work),

    /* ll_conn.c */
    ROM_HOOK_INDEX_DECLAR(ll_conn_reset),
    ROM_HOOK_INDEX_DECLAR(ll_conn_alloc),
    ROM_HOOK_INDEX_DECLAR(ll_conn_tx_enqueue),
    ROM_HOOK_INDEX_DECLAR(ll_tx_acl),
    ROM_HOOK_INDEX_DECLAR(ll_process_tx_acl_buf),
    ROM_HOOK_INDEX_DECLAR(ll_conn_process_tx_acl),
    ROM_HOOK_INDEX_DECLAR(ll_conn_tx_acl),
    ROM_HOOK_INDEX_DECLAR(ll_parse_ctrl),
    ROM_HOOK_INDEX_DECLAR(ll_conn_process_rx_pdu),
    ROM_HOOK_INDEX_DECLAR(ll_conn_polling_work),
    ROM_HOOK_INDEX_DECLAR(isr_conn_tx_process),
    ROM_HOOK_INDEX_DECLAR(isr_conn_check_seq),
    ROM_HOOK_INDEX_DECLAR(isr_conn_rxok),
    ROM_HOOK_INDEX_DECLAR(isr_conn_slave_start_timer_cb),
    ROM_HOOK_INDEX_DECLAR(isr_update_next_hop),
    ROM_HOOK_INDEX_DECLAR(isr_conn_superto),
    ROM_HOOK_INDEX_DECLAR(isr_conn_update_param),
    ROM_HOOK_INDEX_DECLAR(ll_conn_sched),

    /* ll.c */
    ROM_HOOK_INDEX_DECLAR(ll_init),
    ROM_HOOK_INDEX_DECLAR(ll_reset),
    ROM_HOOK_INDEX_DECLAR(ll_node_rx_process),
    ROM_HOOK_INDEX_DECLAR(ll_msg_common_send),
    ROM_HOOK_INDEX_DECLAR(ll_polling_work),
    ROM_HOOK_INDEX_DECLAR(ll_get_next_timestamp),

    /* att.c */
    ROM_HOOK_INDEX_DECLAR(att_send),
    ROM_HOOK_INDEX_DECLAR(att_handle_rsp),
    ROM_HOOK_INDEX_DECLAR(bt_att_recv),

    /* conn.c */
    ROM_HOOK_INDEX_DECLAR(bt_conn_connected),
    ROM_HOOK_INDEX_DECLAR(bt_conn_discconnected),
    ROM_HOOK_INDEX_DECLAR(send_acl),
    ROM_HOOK_INDEX_DECLAR(bt_conn_recv),
    ROM_HOOK_INDEX_DECLAR(bt_conn_set_state),
    ROM_HOOK_INDEX_DECLAR(bt_conn_process_tx),

    /* hci_core.c */
    ROM_HOOK_INDEX_DECLAR(bt_hci_cmd_send_sync),
    ROM_HOOK_INDEX_DECLAR(hci_acl),
    ROM_HOOK_INDEX_DECLAR(hci_event),
    ROM_HOOK_INDEX_DECLAR(bt_send),
    ROM_HOOK_INDEX_DECLAR(bt_recv),

    /* l2cap.c */
    ROM_HOOK_INDEX_DECLAR(le_sig_recv),
    ROM_HOOK_INDEX_DECLAR(bt_l2cap_recv),

    ROM_HOOK_TABLE_END,
};
extern void* rom_hook_table[ROM_HOOK_TABLE_END];

void rom_hook_register(int index, void* func);

/* ------------------------------------------------------------------------------------------------
 *                                        Standard Defines
 * ------------------------------------------------------------------------------------------------
 */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef ENABLE
#define ENABLE 1
#endif

#ifndef DISABLE
#define DISABLE 0
#endif

#define IRQN_OFFSET   16

#define IRQ_CRITICAL_PRIORITY   4
#define IRQ_HIGH_PRIORITY       3
#define IRQ_MED_PRIORITY        2
#define IRQ_LOW_PRIORITY        1


#define  SOFT_IRQ_CTRL_BASE (0xE0000000)
#define  TRIGGER_SOFT_IRQ()   (*(volatile uint32_t *)SOFT_IRQ_CTRL_BASE = 1)
#define  CLR_SOFT_IRQ()       (*(volatile uint32_t *)SOFT_IRQ_CTRL_BASE = 0)


typedef enum IRQn
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */



  SoftIrq_IRQn                = 3,     /*  SoftIrq Interrupt */



  SysTick_IRQn                = 7,     /*  System tick Interrupt */



  ExtIrq_IRQn                 = 11,     /* ExtIrq Interrupt */




/* -------------------  Processor Interrupt Numbers  ------------------------------ */
  WDT_IRQn                      =   0 + IRQN_OFFSET,
  Interrupt1_IRQn               =   1 + IRQN_OFFSET,
  RADIO_DMA_IRQn                =   2 + IRQN_OFFSET,
  RADIO_TICK_IRQn               =   3 + IRQN_OFFSET,
  Interrupt4_IRQn               =   4 + IRQN_OFFSET,
  LEDC_IRQn                     =   5 + IRQN_OFFSET,
  KEYSCAN_IRQn                  =   6 + IRQN_OFFSET,
  GPADC_IRQn                    =   7 + IRQN_OFFSET,
  UART0_IRQn                    =   8 + IRQN_OFFSET,
  UART1_IRQn                    =   9 + IRQN_OFFSET,
  SPIM0_IRQn                    =   10 + IRQN_OFFSET,
  SPIM1_IRQn                    =   11 + IRQN_OFFSET,
  I2C0_IRQn                     =   12 + IRQN_OFFSET,
  Interrupt13_IRQn              =   13 + IRQN_OFFSET,
  SPIS0_IRQn                    =   14 + IRQN_OFFSET,
  USB_IRQn                      =   15 + IRQN_OFFSET,
  GPIO_IRQn                     =   16 + IRQN_OFFSET,
  QDEC_IRQn                     =   17 + IRQN_OFFSET,
  AES_IRQn                      =   18 + IRQN_OFFSET,
  CAPTURE_IRQn                  =   19 + IRQN_OFFSET,
  CLKCAL_IRQn                   =   20 + IRQN_OFFSET,
  RTC_IRQn                      =   21 + IRQN_OFFSET,
  SDMA_IRQn                     =   22 + IRQN_OFFSET,
  Interrupt23_IRQn              =   23 + IRQN_OFFSET,
  TIMER0_IRQn                   =   24 + IRQN_OFFSET,
  TIMER1_IRQn                   =   25 + IRQN_OFFSET,
  TIMER2_IRQn                   =   26 + IRQN_OFFSET,
  TIMER3_IRQn                   =   27 + IRQN_OFFSET,
  TIMER4_IRQn                   =   28 + IRQN_OFFSET,
  TIMER5_IRQn                   =   29 + IRQN_OFFSET,
  TIMER6_IRQn                   =   30 + IRQN_OFFSET,
  TIMER7_IRQn                   =   31 + IRQN_OFFSET,
  /* Interrupts 10 .. 31 are left out */
} IRQn_Type;

/// Interrupt Enable bit in mstatus register
#define INTE_EN_BIT_POS 3
#define INTE_EN (1 << INTE_EN_BIT_POS)

#define GLOBAL_INT_START()                                                            \
    do                                                                                \
    {                                                                                 \
        int mstatus;                                                                  \
        __asm__ volatile ("csrrsi %0, mstatus, %1" : "=r" (mstatus) : "i" (INTE_EN)); \
    } while (0)

#define GLOBAL_INT_STOP()                                                             \
    do                                                                                \
    {                                                                                 \
        int mstatus;                                                                  \
        __asm__ volatile ("csrrci %0, mstatus, %1" : "=r" (mstatus) : "i" (INTE_EN)); \
    } while (0)

void delay_us(uint32_t us);

void delay_ms(uint32_t ms);

#endif

