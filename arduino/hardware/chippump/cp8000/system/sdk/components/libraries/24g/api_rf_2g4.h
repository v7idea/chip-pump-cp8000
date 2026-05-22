/*************************************************************************************************
 * @file       api_rf_2g4.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-03-08
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#ifndef __API_RF_2G4_H__
#define __API_RF_2G4_H__

#include <stdint.h>
#include <stdbool.h>

#define MAX_RF_LENGTH                                   39

#define RF_RATE_1M      0
#define RF_RATE_2M      1
#define RF_RATE_S2      2
#define RF_RATE_S8      3
#define RF_RATE_500K    4
#define RF_RATE_250K    5
#define RF_RATE_125K    6
#define RF_RATE_50K     7
#define RF_RATE_25K     8
#define RF_RATE_10K     9
#define RF_RATE_2K      10

/**
 * @brief RF channel enumeration for 2.4GHz band
 */
typedef enum {
	RF_CH37 = 0,
	RF_CH0  = 1,
	RF_CH1  = 2,
	RF_CH2  = 3,
	RF_CH3  = 4,
	RF_CH4  = 5,
	RF_CH5  = 6,
	RF_CH6  = 7,
	RF_CH7  = 8,
	RF_CH8  = 9,
	RF_CH9  = 10,
	RF_CH10 = 11,
	RF_CH38 = 12,
	RF_CH11 = 13,
	RF_CH12 = 14,
	RF_CH13 = 15,
	RF_CH14 = 16,
	RF_CH15 = 17,
	RF_CH16 = 18,
	RF_CH17 = 19,
	RF_CH18 = 20,
	RF_CH19 = 21,
	RF_CH20 = 22,
	RF_CH21 = 23,
	RF_CH22 = 24,
	RF_CH23 = 25,
	RF_CH24 = 26,
	RF_CH25 = 27,
	RF_CH26 = 28,
	RF_CH27 = 29,
	RF_CH28 = 30,
	RF_CH29 = 31,
	RF_CH30 = 32,
	RF_CH31 = 33,
	RF_CH32 = 34,
	RF_CH33 = 35,
	RF_CH34 = 36,
	RF_CH35 = 37,
	RF_CH36 = 38,
	RF_CH39 = 39
	
}rf_channel_e;

/**
 * @brief RF configuration parameters structure
 * @note All timing parameters are in milliseconds unless specified otherwise
 */
typedef struct
{
    /** Channel configuration: (bandwidth/100) << 11 | channel */
    uint16_t channel;

    /** PHY layer mode (modulation scheme) */
    uint8_t phy_mode;

    /** Preamble length in symbols */
    uint8_t preamble_len;

    /** Access code pattern (8-byte synchronization word) */
    uint8_t access_code[8];
    /** Access code length in bytes */
    uint8_t access_len;

    /** RX operation timeout value */
    uint16_t rx_timeout;

    /** Whitening enable flag */
    uint8_t white_en;
    /** Whitening initial value */
    uint8_t white_init;

    /** Forward Error Correction mode */
    uint8_t fec_mode;

    /** CRC enable flag */
    uint8_t crc_en;
    /** CRC length in bytes */
    uint8_t crc_len;

    /** Initial value for CRC calculation */
    uint32_t crc_init;
    /** Polynomial for CRC calculation */
    uint32_t crc_poly;

    /** Automatic length field configuration */

    uint8_t auto_len_size;
    uint8_t auto_len_pre_size;
    uint8_t auto_header_sign;
    uint8_t auto_len_ext_size;
    uint8_t auto_len_ext;
    /** Maximum allowed RX bits in auto-length mode */
    uint16_t auto_max_allow_rx_bits;
	
    /** FIFO memory configuration */
    uint16_t fifo_offset;
    uint16_t fifo_len;

    /** Automatic ACK retransmission control */
    uint8_t auto_ack_resend_en;
    uint16_t auto_rx_ack_timeout;
    uint16_t auto_resend_delay;
    uint16_t auto_tx_ack_delay;
    uint16_t auto_resend_limit;

    /** Wake-On-Radio (WOR) configurations */
    uint8_t wor_en;    /**< WOR enable flag */
    uint8_t twor_en;   /**< Timer-based WOR enable flag */
    
    /** WOR specific parameters */
    uint16_t wor_sl;   /**< WOR sleep interval */
    
    /** TWOR specific parameters */
    uint16_t twor_ac;  /**< TWOR activity window */
    uint16_t twor_sl;  /**< TWOR sleep interval */

    /** General Purpose I/O Settings */
    volatile uint8_t GIOS_WTR;    /**< Wait Until TX/RX Finished */
    volatile uint8_t GIOS_VPOAK;  /**< Valid Packet/Auto ACK OK */
    volatile uint8_t GIOS_TWOR;   /**< Timer Wake On GPIO */

    /** RX related I/O status */
    volatile uint8_t GIOS_RX;     /**< RX activity indicator */
    volatile uint8_t GIOS_SYNC;   /**< Frame synchronization status */
    volatile uint8_t GIOS_CRC;    /**< CRC error flag */

    /** TX related I/O control */
    volatile uint8_t GIOS_TX;     /**< TX modulation enable */

    /** System status flags */
    volatile uint8_t status_WTR;  /**< Wait Until Done status */
    volatile uint8_t status_VPOAK;/**< Packet/Ack validation status */

    /** Reserved for future extensions */
    uint8_t res[10];

} __PACKED rf_2g4_param_t;

extern rf_2g4_param_t *rf_2g4_para;
extern uint8_t* rf_2g4_fifo;
extern uint8_t rf_2g4_thld[4];
extern uint8_t rf_2g4_rx_data_buf[];

void rf_private_2g4_init(rf_2g4_param_t *tmp_rf_cfg);

void rf_private_2g4_tx_data(uint8_t *data, uint16_t len, uint16_t rf_chl);

void rf_private_2g4_rx_data(uint8_t *data, uint16_t len, uint16_t rf_chl);

void rf_private2g4_rx_start(uint16_t rf_chl);

/** 
 * @brief Initialize 2.4GHz RF module
 */
void rf_2g4_init(void);

void rf_2g4_set_access_word(uint32_t acc_word);

void rf_2g4_set_msb_first(uint8_t en);

void rf_2g4_rx_whiten_en(uint8_t en);

void rf_2g4_tx_whiten_en(uint8_t en);


/**
 * @brief Transmit data with channel switching
 * @param data Pointer to transmit buffer
 * @param len Length of data in bytes
 */
void rf_2g4_tx_data_switch_chl(uint8_t * data, uint16_t len);

/**
 * @brief Transmit data on specified channel
 * @param data Pointer to transmit buffer
 * @param len Length of data in bytes
 * @param rf_chl Target RF channel
 */
void rf_2g4_tx_data(uint8_t * data, uint16_t len, uint16_t rf_chl);

/**
 * @brief Set TX output power level
 * @param dbm Requested output power in dBm（range：-25 - +12dbm）
 * @note Actual power depends on hardware capabilities
 */
void rf_2g4_set_tx_power(int dbm);

/**
 * @brief Receive data from specified channel
 * @param data Buffer for received data
 * @param len Expected data length
 * @param rf_chl Reception channel (use rf_channel_e values)
 */
void rf_2g4_rx_data(uint8_t * data, uint16_t len, uint16_t rf_chl);

/**
 * @brief Start continuous RX mode on specified channel
 * @param rf_chl Reception channel (use rf_channel_e values)
 */
void rf_2g4_rx_start(uint8_t rf_chl);

/**
 * @brief RX interrupt handler (user-implemented)
 * @param data Pointer to received data
 * @param len Received data length
 */
void rf_2g4_rx_handler(uint8_t *data ,uint8_t len);

/** Set RF to IDLE state, current operation will be aborted */
void rf_2g4_set_idle(void);

/** \brief Check if the RF module is idle.
 *  \return
 * 0: NOT idle; !0: Idle
 *
 * If call this function, must after you HAVE START TX/RX */
uint8_t rf_2g4_txrx_is_idle(void);

/** @brief Check frame synchronization status */
uint8_t rf_get_sync_ok(void);

/** @brief Check CRC error status */
uint8_t rf_get_crc_error(void);

void rf_set_dynamic_agc_mode(int mode);


/** @brief Get last received signal strength (RSSI) */
int rf_get_rssi(void);

/** @brief Get direct access to RF FIFO buffer */
uint8_t *rf_get_2g4_fifo(void);

/** @brief Get current RF configuration parameters */
rf_2g4_param_t *rf_get_2g4_param(void);

/**
 * @brief Set RX timeout value
 * @param to_val Timeout duration in milliseconds
 */
void rf_set_rx_timeout_val(uint32_t to_val);

#endif
