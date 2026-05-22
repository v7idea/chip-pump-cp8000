#ifndef __BT_BUF_H__
#define __BT_BUF_H__

#include "simple_buf.h"
#include "hci_def.h"

#ifdef __cplusplus
extern "C" {
#endif

struct bt_dev_raw
{
    /* Registered HCI driver */
    const struct bt_hci_driver *drv;
};

extern struct bt_dev_raw bt_dev_raw;



/** Possible types of buffers passed around the Bluetooth stack */
enum bt_buf_type
{
    /** HCI command */
    BT_BUF_CMD,
    /** HCI event */
    BT_BUF_EVT,
    /** Outgoing ACL data */
    BT_BUF_ACL_OUT,
    /** Incoming ACL data */
    BT_BUF_ACL_IN,

    BT_BUF_END
};

/** @brief This is a base type for bt_buf user data. */
struct bt_buf_data
{
    uint8_t type;
};

#define BT_BUF_RESERVE CONFIG_BT_HCI_RESERVE

/** Helper to include reserved HCI data in buffer calculations */
#define BT_BUF_SIZE(size) (BT_BUF_RESERVE + (size))

/** Helper to calculate needed buffer size for HCI ACL packets */
#define BT_BUF_ACL_SIZE(size) BT_BUF_SIZE(BT_HCI_ACL_HDR_SIZE + (size))

/** Helper to calculate needed buffer size for HCI Event packets. */
#define BT_BUF_EVT_SIZE(size) BT_BUF_SIZE(BT_HCI_EVT_HDR_SIZE + (size))

/** Helper to calculate needed buffer size for HCI Command packets. */
#define BT_BUF_CMD_SIZE(size) BT_BUF_SIZE(BT_HCI_CMD_HDR_SIZE + (size))

/** Helper to calculate needed buffer size for HCI ISO packets. */
#define BT_BUF_ISO_SIZE(size)                                                                      \
    BT_BUF_SIZE(BT_HCI_ISO_HDR_SIZE + BT_HCI_ISO_TS_DATA_HDR_SIZE + (size))

/** Allocate a buffer for incoming data
 *
 *  This will set the buffer type so bt_buf_set_type() does not need to
 *  be explicitly called before bt_recv_prio().
 *
 *  @param type    Type of buffer. Only BT_BUF_EVT, BT_BUF_ACL_IN and BT_BUF_ISO_IN
 *                 are allowed.
 *  @param timeout Non-negative waiting period to obtain a buffer or one of the
 *                 special values K_NO_WAIT and K_FOREVER.
 *  @return A new buffer.
 */
/** Allocate a buffer for outgoing data
 *
 *  This will set the buffer type so bt_buf_set_type() does not need to
 *  be explicitly called before bt_send().
 *
 *  @param type    Type of buffer. Only BT_BUF_CMD, BT_BUF_ACL_OUT or
 *                 BT_BUF_H4, when operating on H:4 mode, are allowed.
 *  @param timeout Non-negative waiting period to obtain a buffer or one of the
 *                 special values K_NO_WAIT and K_FOREVER.
 *  @param data    Initial data to append to buffer.
 *  @param size    Initial data size.
 *  @return A new buffer.
 */
simple_buf_t *bt_buf_get_tx(enum bt_buf_type type, const void *data,
                              size_t size);

/** Allocate a buffer for an HCI Command Complete/Status Event
 *
 *  This will set the buffer type so bt_buf_set_type() does not need to
 *  be explicitly called before bt_recv_prio().
 *
 *  @param timeout Non-negative waiting period to obtain a buffer or one of the
 *                 special values K_NO_WAIT and K_FOREVER.
 *  @return A new buffer.
 */
simple_buf_t *bt_buf_get_cmd_complete(void);

/** Allocate a buffer for an HCI Event
 *
 *  This will set the buffer type so bt_buf_set_type() does not need to
 *  be explicitly called before bt_recv_prio() or bt_recv().
 *
 *  @param evt          HCI event code
 *  @param discardable  Whether the driver considers the event discardable.
 *  @param timeout      Non-negative waiting period to obtain a buffer or one of
 *                      the special values K_NO_WAIT and K_FOREVER.
 *  @return A new buffer.
 */

/** Set the buffer type
 *
 *  @param buf   Bluetooth buffer
 *  @param type  The BT_* type to set the buffer to
 */
static inline void bt_buf_set_type(simple_buf_t *buf, enum bt_buf_type type)
{
    ((struct bt_buf_data *)simple_buf_user_data(buf))->type = type;
}

/** Get the buffer type
 *
 *  @param buf   Bluetooth buffer
 *
 *  @return The BT_* type to of the buffer
 */
static inline enum bt_buf_type bt_buf_get_type(simple_buf_t *buf)
{
    return (enum bt_buf_type)((struct bt_buf_data *)simple_buf_user_data(buf))->type;
}


/**
 * @brief Setup the HCI transport, which usually means to reset the
 * Bluetooth IC.
 *
 * @note A weak version of this function is included in the H4 driver, so
 *       defining it is optional per board.
 *
 * @param dev The device structure for the bus connecting to the IC
 *
 * @return 0 on success, negative error value on failure
 */
// int bt_hci_transport_setup(const struct device *dev);

/** Allocate an HCI event buffer.
 *
 * This function allocates a new buffer for an HCI event. It is given the
 * avent code and the total length of the parameters. Upon successful return
 * the buffer is ready to have the parameters encoded into it.
 *
 * @param evt        Event OpCode.
 * @param len        Length of event parameters.
 *
 * @return Newly allocated buffer.
 */
simple_buf_t *bt_hci_evt_create(uint8_t evt, uint8_t len);

/** Allocate an HCI Command Complete event buffer.
 *
 * This function allocates a new buffer for HCI Command Complete event.
 * It is given the OpCode (encoded e.g. using the BT_OP macro) and the total
 * length of the parameters. Upon successful return the buffer is ready to have
 * the parameters encoded into it.
 *
 * @param op         Command OpCode.
 * @param plen       Length of command parameters.
 *
 * @return Newly allocated buffer.
 */
simple_buf_t *bt_hci_cmd_complete_create(uint16_t op, uint8_t plen);

/** Allocate an HCI Command Status event buffer.
 *
 * This function allocates a new buffer for HCI Command Status event.
 * It is given the OpCode (encoded e.g. using the BT_OP macro) and the status
 * code. Upon successful return the buffer is ready to have the parameters
 * encoded into it.
 *
 * @param op         Command OpCode.
 * @param status     Status code.
 *
 * @return Newly allocated buffer.
 */
simple_buf_t *bt_hci_cmd_status_create(uint16_t op, uint8_t status);

uint8_t bt_get_h4_type_by_buffer(enum bt_buf_type type);
simple_buf_t *bt_buf_get(enum bt_buf_type type, uint16_t nd_bl);

extern uint16_t bt_buf_max_len;

static inline simple_buf_t *bt_buf_get_host_tx_cmd(uint16_t nd_bl)
{
    return bt_buf_get(BT_BUF_CMD, BT_BUF_CMD_SIZE(nd_bl));
}

static inline simple_buf_t *bt_buf_get_host_tx_acl(uint16_t nd_bl)
{
    return bt_buf_get(BT_BUF_ACL_OUT, BT_BUF_ACL_SIZE(nd_bl));
}

static inline simple_buf_t *bt_buf_get_controller_tx_evt(uint16_t nd_bl)
{
    return bt_buf_get(BT_BUF_EVT, BT_BUF_EVT_SIZE(nd_bl + 1)); //1 byte for Meta Event
}

static inline simple_buf_t *bt_buf_get_controller_tx_acl(uint16_t nd_bl)
{
    return bt_buf_get(BT_BUF_ACL_IN, BT_BUF_ACL_SIZE(nd_bl));
}

extern uint8_t  bt_buf_cnt_info[BT_BUF_END][2];

static inline void bt_buf_free(enum bt_buf_type type)
{
    __bt_disable_isr();
    bt_buf_cnt_info[type][1]--;
    __bt_enable_isr();
}

static inline uint8_t bt_buf_get_max_buf_cnt_by_type(enum bt_buf_type type){
    return bt_buf_cnt_info[type][0];
}

static inline uint8_t bt_buf_reserve_size(enum bt_buf_type type){
    return bt_buf_cnt_info[type][0] - bt_buf_cnt_info[type][1];
}

static inline uint8_t bt_buf_reserve_size_host_tx_cmd(void)
{
    return bt_buf_reserve_size(BT_BUF_CMD);
}

static inline uint8_t bt_buf_reserve_size_host_tx_acl(void)
{
    return bt_buf_reserve_size(BT_BUF_ACL_OUT);
}

static inline uint8_t bt_buf_reserve_size_controller_tx_evt(void)
{
    return bt_buf_reserve_size(BT_BUF_EVT);
}

static inline uint8_t bt_buf_reserve_size_controller_tx_acl(void)
{
    return bt_buf_reserve_size(BT_BUF_ACL_IN);
}

static inline uint8_t bt_check_rx_evt_need_drop(uint8_t *packet)
{
    if (bt_buf_reserve_size(BT_BUF_EVT) < 3)
    {
        if (packet[0] == BT_HCI_EVT_LE_META_EVENT && packet[2] == BT_HCI_EVT_LE_ADVERTISING_REPORT)
        {
            return 1;
        }
    }

    return 0;
}

int bt_buf_check_allow_sleep(void);

static inline uint16_t bt_buf_get_item_size_by_type(enum bt_buf_type type)
{
    return bt_buf_max_len;
}

#ifdef __cplusplus
}
#endif

#endif