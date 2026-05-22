#ifndef __SYS_TIMER_H__
#define __SYS_TIMER_H__

#include "bt_common.h"

#include "slist.h"
#include "sys_timeout.h"


/**
 * @}
 */

/**
 * @cond INTERNAL_HIDDEN
 */

struct sys_timer
{
    /*
     * _timeout structure must be first here if we want to use
     * dynamic timer allocation. timeout.node is used in the double-linked
     * list of free timers
     */
    struct _timeout timeout;

    /* runs in ISR context */
    void (*expiry_fn)(struct sys_timer *timer);

    /* runs in the context of the thread that calls sys_timer_stop() */
    void (*stop_fn)(struct sys_timer *timer);

    /* timer period */
    uint32_t period;

    /* user-specific data, also used to support legacy features */
    void *user_data;
};

#define SYS_TIMER_INITIALIZER(obj, expiry, stop)                                                     \
    {                                                                                              \
        .expiry_fn = expiry, .status = 0, .user_data = 0,                                          \
    }

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup timer_apis Timer APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @typedef sys_timer_expiry_t
 * @brief Timer expiry function type.
 *
 * A timer's expiry function is executed by the system clock interrupt handler
 * each time the timer expires. The expiry function is optional, and is only
 * invoked if the timer has been initialized with one.
 *
 * @param timer     Address of timer.
 */
typedef void (*sys_timer_expiry_t)(struct sys_timer *timer);

/**
 * @typedef sys_timer_stop_t
 * @brief Timer stop function type.
 *
 * A timer's stop function is executed if the timer is stopped prematurely.
 * The function runs in the context of call that stops the timer.  As
 * sys_timer_stop() can be invoked from an ISR, the stop function must be
 * callable from interrupt context (isr-ok).
 *
 * The stop function is optional, and is only invoked if the timer has been
 * initialized with one.
 *
 * @param timer     Address of timer.
 */
typedef void (*sys_timer_stop_t)(struct sys_timer *timer);

/**
 * @brief Statically define and initialize a timer.
 *
 * The timer can be accessed outside the module where it is defined using:
 *
 * @code extern struct sys_timer <name>; @endcode
 *
 * @param name Name of the timer variable.
 * @param expiry_fn Function to invoke each time the timer expires.
 * @param stop_fn   Function to invoke if the timer is stopped while running.
 */
#define SYS_TIMER_DEFINE(name, expiry_fn, stop_fn)                                                   \
    struct sys_timer name = SYS_TIMER_INITIALIZER(name, expiry_fn, stop_fn)

/**
 * @brief Initialize a timer.
 *
 * This routine initializes a timer, prior to its first use.
 *
 * @param timer     Address of timer.
 * @param expiry_fn Function to invoke each time the timer expires.
 * @param stop_fn   Function to invoke if the timer is stopped while running.
 */
void sys_timer_init(struct sys_timer *timer, sys_timer_expiry_t expiry_fn, sys_timer_stop_t stop_fn);

/**
 * @brief Start a timer.
 *
 * This routine starts a timer, and resets its status to zero. The timer
 * begins counting down using the specified duration and period values.
 *
 * Attempting to start a timer that is already running is permitted.
 * The timer's status is reset to zero and the timer begins counting down
 * using the new duration and period values.
 *
 * @param timer     Address of timer.
 * @param duration  Initial timer duration.
 * @param period    Timer period.
 */
void sys_timer_start(struct sys_timer *timer, uint32_t duration, uint32_t period);

/**
 * @brief Stop a timer.
 *
 * This routine stops a running timer prematurely. The timer's stop function,
 * if one exists, is invoked by the caller.
 *
 * Attempting to stop a timer that is not running is permitted, but has no
 * effect on the timer.
 *
 * @note The stop handler has to be callable from ISRs if @a sys_timer_stop is to
 * be called from ISRs.
 *
 * @funcprops \isr_ok
 *
 * @param timer     Address of timer.
 */
void sys_timer_stop(struct sys_timer *timer);

/**
 * @brief Read timer status.
 *
 * This routine reads the timer's status, which indicates the number of times
 * it has expired since its status was last read.
 *
 * Calling this routine resets the timer's status to zero.
 *
 * @param timer     Address of timer.
 *
 * @return Timer status.
 */
uint32_t sys_timer_status_get(struct sys_timer *timer);

/**
 * @brief Associate user-specific data with a timer.
 *
 * This routine records the @a user_data with the @a timer, to be retrieved
 * later.
 *
 * It can be used e.g. in a timer handler shared across multiple subsystems to
 * retrieve data specific to the subsystem this timer is associated with.
 *
 * @param timer     Address of timer.
 * @param user_data User data to associate with the timer.
 */
static inline void sys_timer_user_data_set(struct sys_timer *timer, void *user_data)
{
    timer->user_data = user_data;
}

/**
 * @brief Retrieve the user-specific data from a timer.
 *
 * @param timer     Address of timer.
 *
 * @return The user data.
 */
static inline void *sys_timer_user_data_get(const struct sys_timer *timer)
{
    return timer->user_data;
}

/**
 * @brief Get next expiration time of a timer, in system ticks
 *
 * This routine returns the future system uptime reached at the next
 * time of expiration of the timer, in units of system ticks.  If the
 * timer is not running, current system time is returned.
 *
 * @param timer The timer object
 * @return Uptime of expiration, in ticks
 */
static inline uint32_t sys_timer_expires_ticks(const struct sys_timer *timer)
{
    return sys_timeout_expires(&timer->timeout);
}

/**
 * @brief Get time remaining before a timer next expires.
 *
 * This routine computes the (approximate) time remaining before a running
 * timer next expires. If the timer is not running, it returns zero.
 *
 * @param timer     Address of timer.
 *
 * @return Remaining time (in milliseconds).
 */
static inline uint32_t sys_timer_remaining_get(struct sys_timer *timer)
{
    return sys_timeout_remaining(&timer->timeout);
}

#endif