
#ifndef __SYS_TIMEOUT_H__
#define __SYS_TIMEOUT_H__

#include "dlist.h"

#define NSEC_PER_USEC 1000U
#define USEC_PER_MSEC 1000U
#define MSEC_PER_SEC 1000U

#define K_TICKS(t) (t)
#define K_MSEC(ms) (ms)
#define K_SECONDS(s) K_MSEC((s)*MSEC_PER_SEC)
#define K_MINUTES(m) K_SECONDS((m)*60)
#define K_HOURS(h) K_MINUTES((h)*60)

struct _timeout;
typedef void (*_timeout_func_t)(struct _timeout *t);

struct _timeout
{
    sys_dnode_t node;
    _timeout_func_t fn;
    uint32_t dticks;
};


typedef uint32_t (*SYS_TIMEOUT_TICK_GET_HOOK)(void);
void sys_timeout_init(SYS_TIMEOUT_TICK_GET_HOOK tick_hook);
int sys_timeout_abort(struct _timeout *to);
void sys_timeout_add(struct _timeout *to, _timeout_func_t fn, uint32_t timeout);
uint32_t sys_timeout_expires(const struct _timeout *timeout);
uint32_t sys_timeout_remaining(const struct _timeout *timeout);

static inline void sys_timeout_node_init(struct _timeout *to)
{
    sys_dnode_init(&to->node);
}

#endif