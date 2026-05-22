#ifndef __HCI_CORE_H__
#define __HCI_CORE_H__

#include "hci_driver.h"

#include "sys_timer.h"
#include "slist.h"

#include "conn.h"

#include "addr.h"

#define LMP_FEAT_PAGES_COUNT 1

#if defined(CONFIG_BT_EXT_ADV_LEGACY_SUPPORT)
/* Check the feature bit for extended or legacy advertising commands */
#define BT_DEV_FEAT_LE_EXT_ADV(feat) BT_FEAT_LE_EXT_ADV(feat)
#else
/* Always use extended advertising commands. */
#define BT_DEV_FEAT_LE_EXT_ADV(feat) 1
#endif

struct bt_dev_le
{
    /* LE features */
    uint8_t features[8];
    /* LE states */
    uint64_t states;

#if defined(CONFIG_BT_CONN)
    /* Controller buffer information */
    uint16_t acl_mtu;
    uint8_t acl_pkts;
#endif /* CONFIG_BT_CONN */
#if defined(CONFIG_BT_SMP)
    /* Size of the the controller resolving list */
    uint8_t rl_size;
    /* Number of entries in the resolving list. rl_entries > rl_size
     * means that host-side resolving is used.
     */
    uint8_t rl_entries;
#endif /* CONFIG_BT_SMP */
};


typedef enum
{
    HCI_STATE_NONE = 0,
    HCI_STATE_INITIALING,
    HCI_STATE_READY,
} HCI_STATE;

/* State tracking for the local Bluetooth controller */
struct bt_dev_set
{
    bt_addr_le_t public_addr;

    /* Current local Random Address */
    bt_addr_le_t random_addr;

    /* Controller version & manufacturer information */
    uint8_t hci_version;
    uint8_t lmp_version;
    uint16_t hci_revision;
    uint16_t lmp_subversion;
    uint16_t manufacturer;

    /* LMP features (pages 0, 1, 2) */
    uint8_t features[LMP_FEAT_PAGES_COUNT][8];

    /* Supported commands */
    uint8_t supported_commands[64];

    /* LE controller specific features */
    struct bt_dev_le le;

    /* Number of commands controller can accept */
    uint8_t ncmd_sem;

    /* Queue for incoming HCI events & ACL data */
    sys_slist_t rx_queue;

    /* Queue for incoming HCI events. */
    sys_slist_t rx_evt_queue;

#if defined(CONFIG_BT_PRIVACY)
    /* Local Identity Resolving Key */
    uint8_t irk[CONFIG_BT_ID_MAX][16];

    /* Work used for RPA rotation */
    struct sys_timer rpa_update;

    /* The RPA timeout value. */
    uint16_t rpa_timeout;
#endif

    HCI_STATE hci_state;

    bt_hci_event_process_t hci_event_process;

    /* Registered HCI driver */
    const struct bt_hci_driver *drv;
};

extern struct bt_dev_set bt_dev;


#if defined(CONFIG_BT_SMP)
enum bt_security_err bt_security_err_get(uint8_t hci_err);
#endif /* CONFIG_BT_SMP */

/**
 * @typedef bt_ready_cb_t
 * @brief Callback for notifying that Bluetooth has been enabled.
 *
 * @param err zero on success or (negative) error code otherwise.
 */
typedef void (*bt_ready_cb_t)(int err);

/**
 * @brief Enable Bluetooth
 *
 * Enable Bluetooth. Must be the called before any calls that
 * require communication with the local Bluetooth hardware.
 *
 * When @kconfig{CONFIG_BT_SETTINGS} is enabled, the application must load the
 * Bluetooth settings after this API call successfully completes before
 * Bluetooth APIs can be used. Loading the settings before calling this function
 * is insufficient. Bluetooth settings can be loaded with settings_load() or
 * settings_load_subtree() with argument "bt". The latter selectively loads only
 * Bluetooth settings and is recommended if settings_load() has been called
 * earlier.
 *
 * @param cb Callback to notify completion or NULL to perform the
 * enabling synchronously.
 *
 * @return Zero on success or (negative) error code otherwise.
 */
int bt_enable(bt_ready_cb_t cb);

/**
 * @brief Disable Bluetooth
 *
 * Disable Bluetooth. Can't be called before bt_enable has completed.
 *
 * Close and release HCI resources. Result is architecture dependent.
 *
 * @return Zero on success or (negative) error code otherwise.
 */
int bt_disable(void);

/**
 * @brief Check if Bluetooth is ready
 *
 * @return true when Bluetooth is ready, false otherwise
 */
bool bt_is_ready(void);

/** Allocate a HCI command buffer.
 *
 * This function allocates a new buffer for a HCI command. It is given
 * the OpCode (encoded e.g. using the BT_OP macro) and the total length
 * of the parameters. Upon successful return the buffer is ready to have
 * the parameters encoded into it.
 *
 * @param opcode     Command OpCode.
 * @param param_len  Length of command parameters.
 *
 * @return Newly allocated buffer.
 */
simple_buf_t *bt_hci_cmd_create(uint16_t opcode, uint8_t param_len);

/** Send a HCI command asynchronously.
 *
 * This function is used for sending a HCI command asynchronously. It can
 * either be called for a buffer created using bt_hci_cmd_create(), or
 * if the command has no parameters a NULL can be passed instead. The
 * sending of the command will happen asynchronously, i.e. upon successful
 * return from this function the caller only knows that it was queued
 * successfully.
 *
 * If synchronous behavior, and retrieval of the Command Complete parameters
 * is desired, the bt_hci_cmd_send_sync() API should be used instead.
 *
 * @param opcode Command OpCode.
 * @param buf    Command buffer or NULL (if no parameters).
 *
 * @return 0 on success or negative error value on failure.
 */
int bt_hci_cmd_send(uint16_t opcode, simple_buf_t *buf);

/** Send a HCI command synchronously.
 *
 * This function is used for sending a HCI command synchronously. It can
 * either be called for a buffer created using bt_hci_cmd_create(), or
 * if the command has no parameters a NULL can be passed instead.
 *
 * The function will block until a Command Status or a Command Complete
 * event is returned. If either of these have a non-zero status the function
 * will return a negative error code and the response reference will not
 * be set. If the command completed successfully and a non-NULL rsp parameter
 * was given, this parameter will be set to point to a buffer containing
 * the response parameters.
 *
 * @param opcode Command OpCode.
 * @param buf    Command buffer or NULL (if no parameters).
 * @param rsp    Place to store a reference to the command response. May
 *               be NULL if the caller is not interested in the response
 *               parameters. If non-NULL is passed the caller is responsible
 *               for calling net_buf_unref() on the buffer when done parsing
 *               it.
 *
 * @return 0 on success or negative error value on failure.
 */
int bt_hci_cmd_send_sync(uint16_t opcode, simple_buf_t *buf, simple_buf_t **rsp);


int bt_hci_cmd_send_sync_with_data(uint16_t opcode, uint8_t* data, int len, simple_buf_t **rsp);

/** @brief Send packet to the Bluetooth controller
 *
 * Send packet to the Bluetooth controller. Caller needs to
 * implement netbuf pool.
 *
 * @param buf netbuf packet to be send
 *
 * @return Zero on success or (negative) error code otherwise.
 */
int bt_send(simple_buf_t *buf);



/** @brief Get Random bytes from the LE Controller.
 *
 * Send the HCI_LE_Rand to the LE Controller as many times as required to
 * fill the provided @p buffer.
 *
 * @note This function is provided as a helper to gather an arbitrary number of
 * random bytes from an LE Controller using the HCI_LE_Rand command.
 *
 * @param buffer Buffer to fill with random bytes.
 * @param len Length of the buffer in bytes.
 *
 * @return 0 on success or negative error value on failure.
 */
int bt_hci_le_rand(void *buffer, size_t len);




/**
 * @brief Helper for parsing advertising (or EIR or OOB) data.
 *
 * A helper for parsing the basic data types used for Extended Inquiry
 * Response (EIR), Advertising Data (AD), and OOB data blocks. The most
 * common scenario is to call this helper on the advertising data
 * received in the callback that was given to bt_le_scan_start().
 *
 * @warning This helper function will consume `ad` when parsing. The user should
 *          make a copy if the original data is to be used afterwards
 *
 * @param ad        Advertising data as given to the bt_le_scan_cb_t callback.
 * @param func      Callback function which will be called for each element
 *                  that's found in the data. The callback should return
 *                  true to continue parsing, or false to stop parsing.
 * @param user_data User data to be passed to the callback.
 */
void bt_data_parse(simple_buf_base_t *ad, bool (*func)(struct bt_data *data, void *user_data),
                   void *user_data);

int bt_hci_disconnect(uint16_t handle, uint8_t reason);

bool bt_addr_le_is_bonded(uint8_t id, const bt_addr_le_t *addr);

int bt_le_conn_params_valid(const struct bt_le_conn_param *param);
int bt_le_set_data_len(struct bt_conn *conn, uint16_t tx_octets, uint16_t tx_time);
int bt_le_set_phy(struct bt_conn *conn, uint8_t all_phys, uint8_t pref_tx_phy, uint8_t pref_rx_phy,
                  uint8_t phy_opts);
uint8_t bt_get_phy(uint8_t hci_phy);

int bt_le_create_conn(const struct bt_conn *conn);
int bt_le_create_conn_cancel(void);

#if defined(CONFIG_BT_MONITOR_SLEEP)
void bt_init_monitor_sleep(void);
uint8_t bt_check_is_in_sleep(void);
uint8_t bt_check_allow_sleep(void);
void bt_monitor_sleep(void);
void bt_sleep_prepare_work(void);
void bt_sleep_wakeup_work_start(void);
void bt_sleep_wakeup_work_end(void);
void bt_sleep_wakeup_work(void);
void bt_sleep_wakeup_with_timeout(void);
#endif

void bt_set_rx_acl_lock(uint8_t rx_lock);
uint8_t bt_get_rx_acl_lock(void);
void bt_polling_work(void);

#if defined (CONFIG_BT_ECC) && defined (CONFIG_BT_SMP)
void bt_hci_evt_le_pkey_complete(simple_buf_t *buf);
void bt_hci_evt_le_dhkey_complete(simple_buf_t *buf);
#endif
#endif