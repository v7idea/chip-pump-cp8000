#ifndef __SIMPLE_BUF_H__
#define __SIMPLE_BUF_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "slist.h"
#include "byteorder.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Network buffer library
 * @defgroup simple_buf Network Buffer Library
 * @ingroup networking
 * @{
 */

/* Alignment needed for various parts of the buffer definition */
#define __simple_buf_align __aligned(sizeof(void *))


/**
 * @brief Simple network buffer representation.
 *
 * This is a simpler variant of the simple_buf object (in fact simple_buf uses
 * simple_buf_base internally). It doesn't provide any kind of reference
 * counting, user data, dynamic allocation, or in general the ability to
 * pass through kernel objects such as FIFOs.
 *
 * The main use of this is for scenarios where the meta-data of the normal
 * simple_buf isn't needed and causes too much overhead. This could be e.g.
 * when the buffer only needs to be allocated on the stack or when the
 * access to and lifetime of the buffer is well controlled and constrained.
 */
typedef struct simple_buf_base
{
    /** Pointer to the start of data in the buffer. */
    uint8_t *data;

    /** Length of the data behind the data pointer. */
    uint16_t len;

    /** Amount of data that this buffer can store. */
    uint16_t size;

    /** Start of the data storage. Not to be accessed directly
     *  (the data pointer should be used instead).
     */
    uint8_t *__buf;
} simple_buf_base_t;


/**
 * @brief Initialize a simple_buf_base object.
 *
 * This needs to be called after creating a simple_buf_base object using
 * the NET_BUF_SIMPLE macro.
 *
 * @param buf Buffer to initialize.
 * @param reserve_head Headroom to reserve.
 */
static inline void simple_buf_base_init(struct simple_buf_base *buf, size_t reserve_head)
{
    if (!buf->__buf)
    {
        buf->__buf = (uint8_t *)buf + sizeof(*buf);
    }

    buf->data = buf->__buf + reserve_head;
    buf->len = 0U;
}

/**
 * @brief Reset buffer
 *
 * Reset buffer data so it can be reused for other purposes.
 *
 * @param buf Buffer to reset.
 */
static inline void simple_buf_base_reset(struct simple_buf_base *buf)
{
    buf->len = 0U;
    buf->data = buf->__buf;
}

/**
 * Clone buffer state, using the same data buffer.
 *
 * Initializes a buffer to point to the same data as an existing buffer.
 * Allows operations on the same data without altering the length and
 * offset of the original.
 *
 * @param original Buffer to clone.
 * @param clone The new clone.
 */

/**
 * @brief Prepare data to be added at the end of the buffer
 *
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param len Number of bytes to increment the length with.
 *
 * @return The original tail of the buffer.
 */
void *simple_buf_base_add(struct simple_buf_base *buf, size_t len);

/**
 * @brief Copy given number of bytes from memory to the end of the buffer
 *
 * Increments the data length of the  buffer to account for more data at the
 * end.
 *
 * @param buf Buffer to update.
 * @param mem Location of data to be added.
 * @param len Length of data to be added
 *
 * @return The original tail of the buffer.
 */
void *simple_buf_base_add_mem(struct simple_buf_base *buf, const void *mem, size_t len);

/**
 * @brief Add (8-bit) uint8_t at the end of the buffer
 *
 * Increments the data length of the  buffer to account for more data at the
 * end.
 *
 * @param buf Buffer to update.
 * @param val uint8_t value to be added.
 *
 * @return Pointer to the value added
 */
uint8_t *simple_buf_base_add_u8(struct simple_buf_base *buf, uint8_t val);

/**
 * @brief Add 16-bit value at the end of the buffer
 *
 * Adds 16-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 16-bit value to be added.
 */

/**
 * @brief Add 16-bit value at the end of the buffer
 *
 * Adds 16-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 16-bit value to be added.
 */

/**
 * @brief Add 24-bit value at the end of the buffer
 *
 * Adds 24-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 24-bit value to be added.
 */

/**
 * @brief Add 24-bit value at the end of the buffer
 *
 * Adds 24-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 24-bit value to be added.
 */

/**
 * @brief Add 32-bit value at the end of the buffer
 *
 * Adds 32-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 32-bit value to be added.
 */

/**
 * @brief Add 32-bit value at the end of the buffer
 *
 * Adds 32-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 32-bit value to be added.
 */

/**
 * @brief Add 48-bit value at the end of the buffer
 *
 * Adds 48-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 48-bit value to be added.
 */

/**
 * @brief Add 48-bit value at the end of the buffer
 *
 * Adds 48-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 48-bit value to be added.
 */

/**
 * @brief Add 64-bit value at the end of the buffer
 *
 * Adds 64-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 64-bit value to be added.
 */

/**
 * @brief Add 64-bit value at the end of the buffer
 *
 * Adds 64-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 64-bit value to be added.
 */

/**
 * @brief Push data to the beginning of the buffer.
 *
 * Modifies the data pointer and buffer length to account for more data
 * in the beginning of the buffer.
 *
 * @param buf Buffer to update.
 * @param len Number of bytes to add to the beginning.
 *
 * @return The new beginning of the buffer data.
 */
void *simple_buf_base_push(struct simple_buf_base *buf, size_t len);

/**
 * @brief Push 16-bit value to the beginning of the buffer
 *
 * Adds 16-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 16-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 16-bit value to the beginning of the buffer
 *
 * Adds 16-bit value in big endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 16-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 8-bit value to the beginning of the buffer
 *
 * Adds 8-bit value the beginning of the buffer.
 *
 * @param buf Buffer to update.
 * @param val 8-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 24-bit value to the beginning of the buffer
 *
 * Adds 24-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 24-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 24-bit value to the beginning of the buffer
 *
 * Adds 24-bit value in big endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 24-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 32-bit value to the beginning of the buffer
 *
 * Adds 32-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 32-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 32-bit value to the beginning of the buffer
 *
 * Adds 32-bit value in big endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 32-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 48-bit value to the beginning of the buffer
 *
 * Adds 48-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 48-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 48-bit value to the beginning of the buffer
 *
 * Adds 48-bit value in big endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 48-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 64-bit value to the beginning of the buffer
 *
 * Adds 64-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 64-bit value to be pushed to the buffer.
 */

/**
 * @brief Push 64-bit value to the beginning of the buffer
 *
 * Adds 64-bit value in big endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 64-bit value to be pushed to the buffer.
 */

/**
 * @brief Remove data from the beginning of the buffer.
 *
 * Removes data from the beginning of the buffer by modifying the data
 * pointer and buffer length.
 *
 * @param buf Buffer to update.
 * @param len Number of bytes to remove.
 *
 * @return New beginning of the buffer data.
 */
static inline void *simple_buf_base_pull(struct simple_buf_base *buf, size_t len)
{

    buf->len -= len;
    return buf->data += len;
}
/**
 * @brief Remove data from the beginning of the buffer.
 *
 * Removes data from the beginning of the buffer by modifying the data
 * pointer and buffer length.
 *
 * @param buf Buffer to update.
 * @param len Number of bytes to remove.
 *
 * @return Pointer to the old location of the buffer data.
 */
void *simple_buf_base_pull_mem(struct simple_buf_base *buf, size_t len);

/**
 * @brief Remove a 8-bit value from the beginning of the buffer
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 8-bit values.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return The 8-bit removed value
 */
uint8_t simple_buf_base_pull_u8(struct simple_buf_base *buf);

/**
 * @brief Remove and convert 16 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 16-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 16-bit value converted from little endian to host endian.
 */
uint16_t simple_buf_base_pull_le16(struct simple_buf_base *buf);

/**
 * @brief Remove and convert 16 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 16-bit big endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 16-bit value converted from big endian to host endian.
 */

/**
 * @brief Remove and convert 24 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 24-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 24-bit value converted from little endian to host endian.
 */

/**
 * @brief Remove and convert 24 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 24-bit big endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 24-bit value converted from big endian to host endian.
 */

/**
 * @brief Remove and convert 32 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 32-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 32-bit value converted from little endian to host endian.
 */

/**
 * @brief Remove and convert 32 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 32-bit big endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 32-bit value converted from big endian to host endian.
 */

/**
 * @brief Remove and convert 48 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 48-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 48-bit value converted from little endian to host endian.
 */

/**
 * @brief Remove and convert 48 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 48-bit big endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 48-bit value converted from big endian to host endian.
 */

/**
 * @brief Remove and convert 64 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 64-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 64-bit value converted from little endian to host endian.
 */

/**
 * @brief Remove and convert 64 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_base_pull(), but a helper for operating
 * on 64-bit big endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 64-bit value converted from big endian to host endian.
 */

static inline void simple_buf_base_push_le16(struct simple_buf_base *buf, uint16_t val)
{
    sys_put_le16(val, simple_buf_base_push(buf, sizeof(val)));
}

static inline void simple_buf_base_push_be16(struct simple_buf_base *buf, uint16_t val)
{
    sys_put_be16(val, simple_buf_base_push(buf, sizeof(val)));
}

static inline void simple_buf_base_push_u8(struct simple_buf_base *buf, uint8_t val)
{
    uint8_t *data = simple_buf_base_push(buf, 1);

    *data = val;
}

static inline void simple_buf_base_push_le24(struct simple_buf_base *buf, uint32_t val)
{
    sys_put_le24(val, simple_buf_base_push(buf, 3));
}

static inline void simple_buf_base_push_be24(struct simple_buf_base *buf, uint32_t val)
{
    sys_put_be24(val, simple_buf_base_push(buf, 3));
}

static inline void simple_buf_base_push_le32(struct simple_buf_base *buf, uint32_t val)
{
    sys_put_le32(val, simple_buf_base_push(buf, sizeof(val)));
}

static inline void simple_buf_base_push_be32(struct simple_buf_base *buf, uint32_t val)
{
    sys_put_be32(val, simple_buf_base_push(buf, sizeof(val)));
}

static inline void simple_buf_base_push_le48(struct simple_buf_base *buf, uint64_t val)
{
    sys_put_le48(val, simple_buf_base_push(buf, 6));
}

static inline void simple_buf_base_push_be48(struct simple_buf_base *buf, uint64_t val)
{
    sys_put_be48(val, simple_buf_base_push(buf, 6));
}

static inline void simple_buf_base_push_le64(struct simple_buf_base *buf, uint64_t val)
{
    sys_put_le64(val, simple_buf_base_push(buf, sizeof(val)));
}

static inline void simple_buf_base_push_be64(struct simple_buf_base *buf, uint64_t val)
{
    sys_put_be64(val, simple_buf_base_push(buf, sizeof(val)));
}


/**
 * @brief Get the tail pointer for a buffer.
 *
 * Get a pointer to the end of the data in a buffer.
 *
 * @param buf Buffer.
 *
 * @return Tail pointer for the buffer.
 */
static inline uint8_t *simple_buf_base_tail(struct simple_buf_base *buf)
{
    return buf->data + buf->len;
}


static inline size_t simple_buf_base_headroom(struct simple_buf_base *buf)
{
    return buf->data - buf->__buf;
}

static inline size_t simple_buf_base_tailroom(struct simple_buf_base *buf)
{
    return buf->size - simple_buf_base_headroom(buf) - buf->len;
}

/**
 * @brief Check buffer headroom.
 *
 * Check how much free space there is in the beginning of the buffer.
 *
 * buf A valid pointer on a buffer
 *
 * @return Number of bytes available in the beginning of the buffer.
 */

/**
 * @brief Check buffer tailroom.
 *
 * Check how much free space there is at the end of the buffer.
 *
 * @param buf A valid pointer on a buffer
 *
 * @return Number of bytes available at the end of the buffer.
 */

/**
 * @brief Parsing state of a buffer.
 *
 * This is used for temporarily storing the parsing state of a buffer
 * while giving control of the parsing to a routine which we don't
 * control.
 */
struct simple_buf_base_state
{
    /** Offset of the data pointer from the beginning of the storage */
    uint16_t offset;
    /** Length of data */
    uint16_t len;
};

/**
 * @brief Save the parsing state of a buffer.
 *
 * Saves the parsing state of a buffer so it can be restored later.
 *
 * @param buf Buffer from which the state should be saved.
 * @param state Storage for the state.
 */
static inline void simple_buf_base_save(struct simple_buf_base *buf,
                                       struct simple_buf_base_state *state)
{
    state->offset = simple_buf_base_headroom(buf);
    state->len = buf->len;
}

/**
 * @brief Restore the parsing state of a buffer.
 *
 * Restores the parsing state of a buffer from a state previously stored
 * by simple_buf_base_save().
 *
 * @param buf Buffer to which the state should be restored.
 * @param state Stored state.
 */
static inline void simple_buf_base_restore(struct simple_buf_base *buf,
                                          struct simple_buf_base_state *state)
{
    buf->data = buf->__buf + state->offset;
    buf->len = state->len;
}

/**
 * @brief Network buffer representation.
 *
 * This struct is used to represent network buffers. Such buffers are
 * normally defined through the NET_BUF_POOL_*_DEFINE() APIs and allocated
 * using the simple_buf_alloc() API.
 */
typedef struct simple_buf
{
    /** Allow placing the buffer into sys_slist_t */
    sys_snode_t node;

    /** Fragments associated with this buffer. */
    struct simple_buf *frags;

    /** Where the buffer should go when freed up. */
    uint8_t  is_bt_buf;
    uint8_t  bt_buf_type;
    uint8_t  rsved[2];

    /** reserve for user spec data. */
    uint32_t user_data;

    /* Union for convenience access to the simple_buf_base members, also
     * preserving the old API.
     */
    union
    {
        /* The ABI of this struct must match simple_buf_base */
        struct
        {
            /** Pointer to the start of data in the buffer. */
            uint8_t *data;

            /** Length of the data behind the data pointer. */
            uint16_t len;

            /** Amount of data that this buffer can store. */
            uint16_t size;

            /** Start of the data storage. Not to be accessed
             *  directly (the data pointer should be used
             *  instead).
             */
            uint8_t *__buf;
        };

        struct simple_buf_base b;
    };
} simple_buf_t;

/**
 * @brief Get a zero-based index for a buffer.
 *
 * This function will translate a buffer into a zero-based index,
 * based on its placement in its buffer pool. This can be useful if you
 * want to associate an external array of meta-data contexts with the
 * buffers of a pool.
 *
 * @param buf  Network buffer.
 *
 * @return Zero-based index for the buffer.
 */
int simple_buf_id(simple_buf_t *buf);

/**
 * @def simple_buf_alloc
 *
 * @copydetails simple_buf_alloc_fixed
 */
simple_buf_t * simple_buf_alloc(uint16_t nl);

/**
 * @brief Get a buffer from a FIFO.
 *
 * @param fifo Which FIFO to take the buffer from.
 * @param timeout Affects the action taken should the FIFO be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then wait as
 *        long as necessary. Otherwise, wait until the specified timeout.
 *
 * @return New buffer or NULL if the FIFO is empty.
 */
simple_buf_t *simple_buf_get(sys_slist_t *fifo);

/**
 * @brief Reset buffer
 *
 * Reset buffer data and flags so it can be reused for other purposes.
 *
 * @param buf Buffer to reset.
 */
void simple_buf_reset(simple_buf_t *buf);

/**
 * @brief Initialize buffer with the given headroom.
 *
 * The buffer is not expected to contain any data when this API is called.
 *
 * @param buf Buffer to initialize.
 * @param reserve How much headroom to reserve.
 */

/**
 * @brief Initialize a simple_buf_base object with data.
 *
 * Initialized buffer object with external data.
 *
 * @param buf Buffer to initialize.
 * @param data External data pointer
 * @param size Amount of data the pointed data buffer if able to fit.
 */
void simple_buf_base_init_with_data(struct simple_buf_base *buf, void *data, size_t size);

/**
 * @brief Put a buffer into a list
 *
 * If the buffer contains follow-up fragments this function will take care of
 * inserting them as well into the list.
 *
 * @param list Which list to append the buffer to.
 * @param buf Buffer.
 */
void simple_buf_slist_put(sys_slist_t *list, simple_buf_t *buf);

/**
 * @brief Get a buffer from a list.
 *
 * If the buffer had any fragments, these will automatically be recovered from
 * the list as well and be placed to the buffer's fragment list.
 *
 * @param list Which list to take the buffer from.
 *
 * @return New buffer or NULL if the FIFO is empty.
 */
simple_buf_t *simple_buf_slist_get(sys_slist_t *list);

/**
 * @brief Put a buffer to the end of a FIFO.
 *
 * If the buffer contains follow-up fragments this function will take care of
 * inserting them as well into the FIFO.
 *
 * @param fifo Which FIFO to put the buffer to.
 * @param buf Buffer.
 */
void simple_buf_put(sys_slist_t *fifo, simple_buf_t *buf);

/**
 * @brief Decrements the reference count of a buffer.
 *
 * The buffer is put back into the pool if the reference count reaches zero.
 *
 * @param buf A valid pointer on a buffer
 */
void simple_buf_free(simple_buf_t * buf);

/**
 * @brief Clone buffer
 *
 * Duplicate given buffer including any data and headers currently stored.
 *
 * @param buf A valid pointer on a buffer
 * @param timeout Affects the action taken should the pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait until the specified
 *        timeout.
 *
 * @return Cloned buffer or NULL if out of buffers.
 */

static inline void simple_buf_base_clone(const struct simple_buf_base *original, struct simple_buf_base *clone)
{
    memcpy(clone, original, sizeof(struct simple_buf_base));
}

static inline void simple_buf_base_add_le16(struct simple_buf_base *buf, uint16_t val)
{
    sys_put_le16(val, simple_buf_base_add(buf, sizeof(val)));
}

static inline void simple_buf_base_add_be16(struct simple_buf_base *buf, uint16_t val)
{
    sys_put_be16(val, simple_buf_base_add(buf, sizeof(val)));
}

static inline void simple_buf_base_add_le24(struct simple_buf_base *buf, uint32_t val)
{
    sys_put_le24(val, simple_buf_base_add(buf, 3));
}

static inline void simple_buf_base_add_be24(struct simple_buf_base *buf, uint32_t val)
{
    sys_put_be24(val, simple_buf_base_add(buf, 3));
}

static inline void simple_buf_base_add_le32(struct simple_buf_base *buf, uint32_t val)
{
    sys_put_le32(val, simple_buf_base_add(buf, sizeof(val)));
}

static inline void simple_buf_base_add_be32(struct simple_buf_base *buf, uint32_t val)
{
    sys_put_be32(val, simple_buf_base_add(buf, sizeof(val)));
}

static inline void simple_buf_base_add_le48(struct simple_buf_base *buf, uint64_t val)
{
    sys_put_le48(val, simple_buf_base_add(buf, 6));
}

static inline void simple_buf_base_add_be48(struct simple_buf_base *buf, uint64_t val)
{
    sys_put_be48(val, simple_buf_base_add(buf, 6));
}

static inline void simple_buf_base_add_le64(struct simple_buf_base *buf, uint64_t val)
{
    sys_put_le64(val, simple_buf_base_add(buf, sizeof(val)));
}

static inline void simple_buf_base_add_be64(struct simple_buf_base *buf, uint64_t val)
{
    sys_put_be64(val, simple_buf_base_add(buf, sizeof(val)));
}

/**
 * @brief Get a pointer to the user data of a buffer.
 *
 * @param buf A valid pointer on a buffer
 *
 * @return Pointer to the user data of the buffer.
 */
static inline void *simple_buf_user_data(const simple_buf_t *buf)
{
    return (void *)&buf->user_data;
}

static inline void simple_buf_base_reserve(struct simple_buf_base *buf, size_t reserve)
{
    buf->data = buf->__buf + reserve;
}
/**
 * @def simple_buf_reserve
 * @brief Initialize buffer with the given headroom.
 *
 * The buffer is not expected to contain any data when this API is called.
 *
 * @param buf Buffer to initialize.
 * @param reserve How much headroom to reserve.
 */
#define simple_buf_reserve(buf, reserve) simple_buf_base_reserve(&(buf)->b, reserve)

/**
 * @def simple_buf_add
 * @brief Prepare data to be added at the end of the buffer
 *
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param len Number of bytes to increment the length with.
 *
 * @return The original tail of the buffer.
 */
#define simple_buf_add(buf, len) simple_buf_base_add(&(buf)->b, len)

/**
 * @def simple_buf_add_mem
 * @brief Copies the given number of bytes to the end of the buffer
 *
 * Increments the data length of the  buffer to account for more data at
 * the end.
 *
 * @param buf Buffer to update.
 * @param mem Location of data to be added.
 * @param len Length of data to be added
 *
 * @return The original tail of the buffer.
 */
#define simple_buf_add_mem(buf, mem, len) simple_buf_base_add_mem(&(buf)->b, mem, len)

/**
 * @def simple_buf_add_u8
 * @brief Add (8-bit) uint8_t at the end of the buffer
 *
 * Increments the data length of the  buffer to account for more data at
 * the end.
 *
 * @param buf Buffer to update.
 * @param val uint8_t value to be added.
 *
 * @return Pointer to the value added
 */
#define simple_buf_add_u8(buf, val) simple_buf_base_add_u8(&(buf)->b, val)

/**
 * @def simple_buf_add_le16
 * @brief Add 16-bit value at the end of the buffer
 *
 * Adds 16-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 16-bit value to be added.
 */
#define simple_buf_add_le16(buf, val) simple_buf_base_add_le16(&(buf)->b, val)

/**
 * @def simple_buf_add_be16
 * @brief Add 16-bit value at the end of the buffer
 *
 * Adds 16-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 16-bit value to be added.
 */
#define simple_buf_add_be16(buf, val) simple_buf_base_add_be16(&(buf)->b, val)

/**
 * @def simple_buf_add_le24
 * @brief Add 24-bit value at the end of the buffer
 *
 * Adds 24-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 24-bit value to be added.
 */
#define simple_buf_add_le24(buf, val) simple_buf_base_add_le24(&(buf)->b, val)

/**
 * @def simple_buf_add_be24
 * @brief Add 24-bit value at the end of the buffer
 *
 * Adds 24-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 24-bit value to be added.
 */
#define simple_buf_add_be24(buf, val) simple_buf_base_add_be24(&(buf)->b, val)

/**
 * @def simple_buf_add_le32
 * @brief Add 32-bit value at the end of the buffer
 *
 * Adds 32-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 32-bit value to be added.
 */
#define simple_buf_add_le32(buf, val) simple_buf_base_add_le32(&(buf)->b, val)

/**
 * @def simple_buf_add_be32
 * @brief Add 32-bit value at the end of the buffer
 *
 * Adds 32-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 32-bit value to be added.
 */
#define simple_buf_add_be32(buf, val) simple_buf_base_add_be32(&(buf)->b, val)

/**
 * @def simple_buf_add_le48
 * @brief Add 48-bit value at the end of the buffer
 *
 * Adds 48-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 48-bit value to be added.
 */
#define simple_buf_add_le48(buf, val) simple_buf_base_add_le48(&(buf)->b, val)

/**
 * @def simple_buf_add_be48
 * @brief Add 48-bit value at the end of the buffer
 *
 * Adds 48-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 48-bit value to be added.
 */
#define simple_buf_add_be48(buf, val) simple_buf_base_add_be48(&(buf)->b, val)

/**
 * @def simple_buf_add_le64
 * @brief Add 64-bit value at the end of the buffer
 *
 * Adds 64-bit value in little endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 64-bit value to be added.
 */
#define simple_buf_add_le64(buf, val) simple_buf_base_add_le64(&(buf)->b, val)

/**
 * @def simple_buf_add_be64
 * @brief Add 64-bit value at the end of the buffer
 *
 * Adds 64-bit value in big endian format at the end of buffer.
 * Increments the data length of a buffer to account for more data
 * at the end.
 *
 * @param buf Buffer to update.
 * @param val 64-bit value to be added.
 */
#define simple_buf_add_be64(buf, val) simple_buf_base_add_be64(&(buf)->b, val)

/**
 * @def simple_buf_push
 * @brief Push data to the beginning of the buffer.
 *
 * Modifies the data pointer and buffer length to account for more data
 * in the beginning of the buffer.
 *
 * @param buf Buffer to update.
 * @param len Number of bytes to add to the beginning.
 *
 * @return The new beginning of the buffer data.
 */
#define simple_buf_push(buf, len) simple_buf_base_push(&(buf)->b, len)

/**
 * @def simple_buf_push_le16
 * @brief Push 16-bit value to the beginning of the buffer
 *
 * Adds 16-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 16-bit value to be pushed to the buffer.
 */
#define simple_buf_push_le16(buf, val) simple_buf_base_push_le16(&(buf)->b, val)

/**
 * @def simple_buf_push_be16
 * @brief Push 16-bit value to the beginning of the buffer
 *
 * Adds 16-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 16-bit value to be pushed to the buffer.
 */
#define simple_buf_push_be16(buf, val) simple_buf_base_push_be16(&(buf)->b, val)

/**
 * @def simple_buf_push_u8
 * @brief Push 8-bit value to the beginning of the buffer
 *
 * Adds 8-bit value the beginning of the buffer.
 *
 * @param buf Buffer to update.
 * @param val 8-bit value to be pushed to the buffer.
 */
#define simple_buf_push_u8(buf, val) simple_buf_base_push_u8(&(buf)->b, val)

/**
 * @def simple_buf_push_le24
 * @brief Push 24-bit value to the beginning of the buffer
 *
 * Adds 24-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 24-bit value to be pushed to the buffer.
 */
#define simple_buf_push_le24(buf, val) simple_buf_base_push_le24(&(buf)->b, val)

/**
 * @def simple_buf_push_be24
 * @brief Push 24-bit value to the beginning of the buffer
 *
 * Adds 24-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 24-bit value to be pushed to the buffer.
 */
#define simple_buf_push_be24(buf, val) simple_buf_base_push_be24(&(buf)->b, val)

/**
 * @def simple_buf_push_le32
 * @brief Push 32-bit value to the beginning of the buffer
 *
 * Adds 32-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 32-bit value to be pushed to the buffer.
 */
#define simple_buf_push_le32(buf, val) simple_buf_base_push_le32(&(buf)->b, val)

/**
 * @def simple_buf_push_be32
 * @brief Push 32-bit value to the beginning of the buffer
 *
 * Adds 32-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 32-bit value to be pushed to the buffer.
 */
#define simple_buf_push_be32(buf, val) simple_buf_base_push_be32(&(buf)->b, val)

/**
 * @def simple_buf_push_le48
 * @brief Push 48-bit value to the beginning of the buffer
 *
 * Adds 48-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 48-bit value to be pushed to the buffer.
 */
#define simple_buf_push_le48(buf, val) simple_buf_base_push_le48(&(buf)->b, val)

/**
 * @def simple_buf_push_be48
 * @brief Push 48-bit value to the beginning of the buffer
 *
 * Adds 48-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 48-bit value to be pushed to the buffer.
 */
#define simple_buf_push_be48(buf, val) simple_buf_base_push_be48(&(buf)->b, val)

/**
 * @def simple_buf_push_le64
 * @brief Push 64-bit value to the beginning of the buffer
 *
 * Adds 64-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 64-bit value to be pushed to the buffer.
 */
#define simple_buf_push_le64(buf, val) simple_buf_base_push_le64(&(buf)->b, val)

/**
 * @def simple_buf_push_be64
 * @brief Push 64-bit value to the beginning of the buffer
 *
 * Adds 64-bit value in little endian format to the beginning of the
 * buffer.
 *
 * @param buf Buffer to update.
 * @param val 64-bit value to be pushed to the buffer.
 */
#define simple_buf_push_be64(buf, val) simple_buf_base_push_be64(&(buf)->b, val)

/**
 * @def simple_buf_pull
 * @brief Remove data from the beginning of the buffer.
 *
 * Removes data from the beginning of the buffer by modifying the data
 * pointer and buffer length.
 *
 * @param buf Buffer to update.
 * @param len Number of bytes to remove.
 *
 * @return New beginning of the buffer data.
 */
#define simple_buf_pull(buf, len) simple_buf_base_pull(&(buf)->b, len)

/**
 * @def simple_buf_pull_mem
 * @brief Remove data from the beginning of the buffer.
 *
 * Removes data from the beginning of the buffer by modifying the data
 * pointer and buffer length.
 *
 * @param buf Buffer to update.
 * @param len Number of bytes to remove.
 *
 * @return Pointer to the old beginning of the buffer data.
 */
#define simple_buf_pull_mem(buf, len) simple_buf_base_pull_mem(&(buf)->b, len)

/**
 * @def simple_buf_pull_u8
 * @brief Remove a 8-bit value from the beginning of the buffer
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 8-bit values.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return The 8-bit removed value
 */
#define simple_buf_pull_u8(buf) simple_buf_base_pull_u8(&(buf)->b)

/**
 * @def simple_buf_pull_le16
 * @brief Remove and convert 16 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 16-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 16-bit value converted from little endian to host endian.
 */
#define simple_buf_pull_le16(buf) simple_buf_base_pull_le16(&(buf)->b)

/**
 * @def simple_buf_pull_be16
 * @brief Remove and convert 16 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 16-bit big endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 16-bit value converted from big endian to host endian.
 */
#define simple_buf_pull_be16(buf) simple_buf_base_pull_be16(&(buf)->b)

/**
 * @def simple_buf_pull_le24
 * @brief Remove and convert 24 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 24-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 24-bit value converted from little endian to host endian.
 */
#define simple_buf_pull_le24(buf) simple_buf_base_pull_le24(&(buf)->b)

/**
 * @def simple_buf_pull_be24
 * @brief Remove and convert 24 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 24-bit big endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 24-bit value converted from big endian to host endian.
 */
#define simple_buf_pull_be24(buf) simple_buf_base_pull_be24(&(buf)->b)

/**
 * @def simple_buf_pull_le32
 * @brief Remove and convert 32 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 32-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 32-bit value converted from little endian to host endian.
 */
#define simple_buf_pull_le32(buf) simple_buf_base_pull_le32(&(buf)->b)

/**
 * @def simple_buf_pull_be32
 * @brief Remove and convert 32 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 32-bit big endian data.
 *
 * @param buf A valid pointer on a buffer
 *
 * @return 32-bit value converted from big endian to host endian.
 */
#define simple_buf_pull_be32(buf) simple_buf_base_pull_be32(&(buf)->b)

/**
 * @def simple_buf_pull_le48
 * @brief Remove and convert 48 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 48-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 48-bit value converted from little endian to host endian.
 */
#define simple_buf_pull_le48(buf) simple_buf_base_pull_le48(&(buf)->b)

/**
 * @def simple_buf_pull_be48
 * @brief Remove and convert 48 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 48-bit big endian data.
 *
 * @param buf A valid pointer on a buffer
 *
 * @return 48-bit value converted from big endian to host endian.
 */
#define simple_buf_pull_be48(buf) simple_buf_base_pull_be48(&(buf)->b)

/**
 * @def simple_buf_pull_le64
 * @brief Remove and convert 64 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 64-bit little endian data.
 *
 * @param buf A valid pointer on a buffer.
 *
 * @return 64-bit value converted from little endian to host endian.
 */
#define simple_buf_pull_le64(buf) simple_buf_base_pull_le64(&(buf)->b)

/**
 * @def simple_buf_pull_be64
 * @brief Remove and convert 64 bits from the beginning of the buffer.
 *
 * Same idea as with simple_buf_pull(), but a helper for operating on
 * 64-bit big endian data.
 *
 * @param buf A valid pointer on a buffer
 *
 * @return 64-bit value converted from big endian to host endian.
 */
#define simple_buf_pull_be64(buf) simple_buf_base_pull_be64(&(buf)->b)

/**
 * @def simple_buf_tailroom
 * @brief Check buffer tailroom.
 *
 * Check how much free space there is at the end of the buffer.
 *
 * @param buf A valid pointer on a buffer
 *
 * @return Number of bytes available at the end of the buffer.
 */
#define simple_buf_tailroom(buf) simple_buf_base_tailroom(&(buf)->b)

/**
 * @def simple_buf_headroom
 * @brief Check buffer headroom.
 *
 * Check how much free space there is in the beginning of the buffer.
 *
 * buf A valid pointer on a buffer
 *
 * @return Number of bytes available in the beginning of the buffer.
 */
#define simple_buf_headroom(buf) simple_buf_base_headroom(&(buf)->b)

/**
 * @def simple_buf_tail
 * @brief Get the tail pointer for a buffer.
 *
 * Get a pointer to the end of the data in a buffer.
 *
 * @param buf Buffer.
 *
 * @return Tail pointer for the buffer.
 */
#define simple_buf_tail(buf) simple_buf_base_tail(&(buf)->b)

/**
 * @brief Find the last fragment in the fragment list.
 *
 * @return Pointer to last fragment in the list.
 */
simple_buf_t *simple_buf_frag_last(simple_buf_t *frags);

/**
 * @brief Insert a new fragment to a chain of bufs.
 *
 * Insert a new fragment into the buffer fragments list after the parent.
 *
 * Note: This function takes ownership of the fragment reference so the
 * caller is not required to unref.
 *
 * @param parent Parent buffer/fragment.
 * @param frag Fragment to insert.
 */
void simple_buf_frag_insert(simple_buf_t *parent, simple_buf_t *frag);

/**
 * @brief Add a new fragment to the end of a chain of bufs.
 *
 * Append a new fragment into the buffer fragments list.
 *
 * Note: This function takes ownership of the fragment reference so the
 * caller is not required to unref.
 *
 * @param head Head of the fragment chain.
 * @param frag Fragment to add.
 *
 * @return New head of the fragment chain. Either head (if head
 *         was non-NULL) or frag (if head was NULL).
 */

/**
 * @brief Delete existing fragment from a chain of bufs.
 *
 * @param parent Parent buffer/fragment, or NULL if there is no parent.
 * @param frag Fragment to delete.
 *
 * @return Pointer to the buffer following the fragment, or NULL if it
 *         had no further fragments.
 */
simple_buf_t *simple_buf_frag_del(simple_buf_t *parent, simple_buf_t *frag);

/**
 * @brief Append data to a list of net_buf
 *
 * @details Append data to a net_buf. If there is not enough space in the
 * net_buf then more net_buf will be added, unless there are no free net_buf
 * and timeout occurs.
 *
 * @param buf Network buffer.
 * @param len Total length of input data
 * @param value Data to be added
 * @param timeout Timeout is passed to the net_buf allocator callback.
 * @param allocate_cb When a new net_buf is required, use this callback.
 * @param user_data A user data pointer to be supplied to the allocate_cb.
 *        This pointer is can be anything from a mem_pool or a net_pkt, the
 *        logic is left up to the allocate_cb function.
 *
 * @return Length of data actually added. This may be less than input
 *         length if other timeout than K_FOREVER was used, and there
 *         were no free fragments in a pool to accommodate all data.
 */
size_t simple_buf_append_bytes(simple_buf_t *buf, size_t len, const void *value);

/**
 * @brief Skip N number of bytes in a simple_buf
 *
 * @details Skip N number of bytes starting from fragment's offset. If the total
 * length of data is placed in multiple fragments, this function will skip from
 * all fragments until it reaches N number of bytes.  Any fully skipped buffers
 * are removed from the simple_buf list.
 *
 * @param buf Network buffer.
 * @param len Total length of data to be skipped.
 *
 * @return Pointer to the fragment or
 *         NULL and pos is 0 after successful skip,
 *         NULL and pos is 0xffff otherwise.
 */
static inline simple_buf_t *simple_buf_skip(simple_buf_t *buf, size_t len)
{
    while (buf && len--)
    {
        simple_buf_pull_u8(buf);
        if (!buf->len)
        {
            buf = simple_buf_frag_del(NULL, buf);
        }
    }

    return buf;
}

static inline simple_buf_t *simple_buf_frag_add(simple_buf_t *head, simple_buf_t *frag)
{
    simple_buf_frag_insert(simple_buf_frag_last(head), frag);

    return head;
}
/**
 * @brief Calculate amount of bytes stored in fragments.
 *
 * Calculates the total amount of data stored in the given buffer and the
 * fragments linked to it.
 *
 * @param buf Buffer to start off with.
 *
 * @return Number of bytes in the buffer and its fragments.
 */
static inline size_t simple_buf_frags_len(simple_buf_t *buf)
{
    size_t bytes = 0;

    while (buf)
    {
        bytes += buf->len;
        buf = buf->frags;
    }

    return bytes;
}

void simple_buf_base_mem_free(void *buf);
void * simple_buf_base_mem_alloc(uint16_t byte_lens);
bool simple_buf_check_empty(uint16_t nl);
bool simple_buf_check_can_sleep();
void simple_buf_init_buf(uint32_t * pool_wa_buf, uint16_t pool_wl);

#define SIMPLE_BUF_ST_FREE    0
#define SIMPLE_BUF_ST_USED    1

#define SIMPLE_BUF_HDR_WD_L    (sizeof(simple_buf_info_t) >> 2)
extern uint8_t g_tail_rsvd_wdl;
extern uint8_t g_hdr_rsvd_wdl;
#define SIMPLE_BUF_TAIL_WD_L   0
#define SIMPLE_BUF_MIN_ALC_L   0

#define SIMPLE_BUF_FREE_NDM_WD_L 2
#define SIMPLE_BUF_USED_HDR_WD_L (SIMPLE_BUF_HDR_WD_L - SIMPLE_BUF_FREE_NDM_WD_L)

#define SIMPLE_BUF_HDR_RSVD_WL  (sizeof(simple_buf_info_t) >> 2)
#define SIMPLE_BUF_TAIL_RSVD_WL (sizeof(simple_buf_info_t) >> 2)

extern uint16_t    g_buf_alloced_wl;
extern uint16_t    g_buf_pool_wl;

typedef struct simple_buf_info simple_buf_info_t;

typedef struct simple_buf_info{
    uint8_t   status;
    uint8_t   rsved;
    uint16_t  wd_len;

    simple_buf_info_t * prv_nb_buf;
    simple_buf_info_t * prv_buf; //alloced buf not need
    simple_buf_info_t * nxt_buf; //alloced buf not need
}simple_buf_info_t;

extern simple_buf_info_t * g_end_buf_ptr;
extern simple_buf_info_t * g_free_buf_hdr;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif