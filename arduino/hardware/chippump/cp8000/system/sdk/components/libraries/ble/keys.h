#ifndef __KEYS_H__
#define __KEYS_H__

#include "addr.h"

/**
 * @brief Clear pairing information.
 *
 * @param id    Local identity (mostly just BT_ID_DEFAULT).
 * @param addr  Remote address, NULL or BT_ADDR_LE_ANY to clear all remote
 *              devices.
 *
 * @return 0 on success or negative error value on failure.
 */
int bt_unpair(uint8_t id, const bt_addr_le_t *addr);

/** Information about a bond with a remote device. */
struct bt_bond_info
{
    /** Address of the remote device. */
    bt_addr_le_t addr;
};

/**
 * @brief Iterate through all existing bonds.
 *
 * @param id         Local identity (mostly just BT_ID_DEFAULT).
 * @param func       Function to call for each bond.
 * @param user_data  Data to pass to the callback function.
 */
void bt_foreach_bond(uint8_t id, void (*func)(const struct bt_bond_info *info, void *user_data),
                     void *user_data);


enum bt_keys_type
{
    BT_KEYS_PERIPH_LTK = BIT(0),
    BT_KEYS_IRK = BIT(1),
    BT_KEYS_LTK = BIT(2),
    BT_KEYS_LOCAL_CSRK = BIT(3),
    BT_KEYS_REMOTE_CSRK = BIT(4),
    BT_KEYS_LTK_P256 = BIT(5),

    BT_KEYS_ALL = (BT_KEYS_PERIPH_LTK | BT_KEYS_IRK | BT_KEYS_LTK | BT_KEYS_LOCAL_CSRK |
                   BT_KEYS_REMOTE_CSRK | BT_KEYS_LTK_P256),
};

enum
{
    BT_KEYS_ID_PENDING_ADD = BIT(0),
    BT_KEYS_ID_PENDING_DEL = BIT(1),
    BT_KEYS_ID_ADDED = BIT(2),
};

enum
{
    BT_KEYS_AUTHENTICATED = BIT(0),
    BT_KEYS_DEBUG = BIT(1),
    /* Bit 2 and 3 might accidentally exist in old stored keys */
    BT_KEYS_SC = BIT(4),
    BT_KEYS_OOB = BIT(5),
};

struct bt_ltk
{
    uint8_t rand[8];
    uint8_t ediv[2];
    uint8_t val[16];
};

struct bt_irk
{
    uint8_t val[16];
    /* Cache for `bt_keys_find_irk`. Not reliable as "current RPA"! */
    bt_addr_t rpa;
};

static inline bool bt_irk_eq(struct bt_irk const *a, struct bt_irk const *b)
{
    return (memcmp(a->val, b->val, sizeof(a->val)) == 0);
}

struct bt_csrk
{
    uint8_t val[16];
    uint32_t cnt;
};

struct bt_keys
{
    uint8_t id;
    bt_addr_le_t addr;
    uint8_t storage_start[0] __aligned(sizeof(void *)); //Compiling issue
    uint8_t enc_size;
    uint8_t flags;
    uint16_t keys;
    struct bt_ltk ltk;
    struct bt_irk irk;
#if defined(CONFIG_BT_SIGNING)
    struct bt_csrk local_csrk;
    struct bt_csrk remote_csrk;
#endif /* BT_SIGNING */
#if !defined(CONFIG_BT_SMP_SC_PAIR_ONLY)
    struct bt_ltk periph_ltk;
#endif /* CONFIG_BT_SMP_SC_PAIR_ONLY */
#if (defined(CONFIG_BT_KEYS_OVERWRITE_OLDEST))
    uint32_t aging_counter;
#endif /* CONFIG_BT_KEYS_OVERWRITE_OLDEST */
};

#define BT_KEYS_STORAGE_LEN (sizeof(struct bt_keys) - offsetof(struct bt_keys, storage_start))

/**
 * @brief Get a call through the callback for each key with the same type
 *
 * @param type Key type.
 * @param func Callback function to be called when a matched record is found.
 * @param data User data to be passed to the callback function.
 */
void bt_keys_foreach_type(enum bt_keys_type type, void (*func)(struct bt_keys *keys, void *data),
                          void *data);

/**
 * @brief Get the key slot reference for an ID and address pair.
 *
 * If the pair already exists in the keys pool, no new reference is reserved
 * and the same reference is returned directly.
 * Otherwise try to reserve one for the new ID and address pair if there is
 * a room for the new pair.
 *
 * @note If 'CONFIG_BT_KEYS_OVERWRITE_OLDEST' is defined and the keys pool is full,
 *       the function will try to find the oldest key that isn't in use with a connection.
 *       If a key with matched criteria is found, it will be overwritten with the new one.
 *
 * @param id Key identifier.
 * @param addr Destination address.
 *
 * @return A valid reference pointer to the key slot if process succeeded.
 *         Otherwise, a NULL value is returned.
 */
struct bt_keys *bt_keys_get_addr(uint8_t id, const bt_addr_le_t *addr);

/**
 * @brief Get the key slot reference for an ID and address pair with a certain type.
 *
 * If the pair already exists in the keys pool, no new reference is reserved
 * and the same reference is returned directly.
 * Otherwise try to reserve one for the new ID and address pair if there is
 * a room for the new pair and set the type.
 *
 * @param type Key type.
 * @param id Key identifier.
 * @param addr Destination address.
 *
 * @return A valid reference pointer to the key slot if process succeeded.
 *         Otherwise, a NULL value is returned.
 */
struct bt_keys *bt_keys_get_type(enum bt_keys_type type, uint8_t id, const bt_addr_le_t *addr);

/**
 * @brief Find key identified by type, ID and address
 *
 * @param type Key type.
 * @param id Key identifier.
 * @param addr Destination address.
 *
 * @return A valid reference pointer to the key slot if it exists.
 *         Otherwise, a NULL value is returned.
 */
struct bt_keys *bt_keys_find(enum bt_keys_type type, uint8_t id, const bt_addr_le_t *addr);

/**
 * @brief Find key reference by trying to resolve an RPA using IRK
 *
 * @param id Key identifier.
 * @param addr Destination address.
 * @return A valid reference pointer to the key slot on success.
 *         Otherwise, a NULL value is returned.
 */
struct bt_keys *bt_keys_find_irk(uint8_t id, const bt_addr_le_t *addr);

/**
 * @brief Find a key by ID and address
 *
 * @param id Key identifier.
 * @param addr Destination address.
 * @return A valid reference pointer to the key slot if it exists.
 *         Otherwise, a NULL value is returned.
 */
struct bt_keys *bt_keys_find_addr(uint8_t id, const bt_addr_le_t *addr);

/**
 * @brief Add a type to a key
 *
 * @param keys Key reference.
 * @param type Key type to be added.
 */
void bt_keys_add_type(struct bt_keys *keys, enum bt_keys_type type);

/**
 * @brief Clear a key contents
 *
 * @param keys Key reference to be cleared.
 */
void bt_keys_clear(struct bt_keys *keys);

// #if defined(CONFIG_BT_SETTINGS)
#if defined (CONFIG_BT_KEY_STORE)
/**
 * @brief Store key to persistent memory
 *
 * @param keys Key reference.
 * @return 0 on success, non-zero error code otherwise
 */
int bt_keys_store(struct bt_keys *keys);
#else
static inline int bt_keys_store(struct bt_keys *keys)
{
    return 0;
}
#endif

uint8_t bt_storage_kv_is_ccc_item_set(uint16_t h, uint8_t id, const bt_addr_le_t *addr);
void bt_storage_kv_add_ccc_item(uint16_t h, uint8_t id, const bt_addr_le_t *addr);
void bt_storage_kv_del_ccc_item(uint16_t h, uint8_t id, const bt_addr_le_t *addr);

enum
{
    BT_LINK_KEY_AUTHENTICATED = BIT(0),
    BT_LINK_KEY_DEBUG = BIT(1),
    BT_LINK_KEY_SC = BIT(2),
};

#endif