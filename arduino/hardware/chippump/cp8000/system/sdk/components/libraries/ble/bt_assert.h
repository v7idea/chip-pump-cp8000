#ifndef __BT_ASSERT_H__
#define __BT_ASSERT_H__


#include <stdint.h>

//#define ASSERT_ENABLE

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ASSERT_ENABLE
#define BT_ASSERT(test)                                                                   \
    {                                                                                              \
        if (!(test))                                                                               \
        {                                                                                          \
            while (1)                                                                              \
                ;                                                                                  \
        }                                                                                          \
    }
#define BT_ASSERT_MSG(test, fmt, ...)                                                                   \
    {                                                                                              \
        if (!(test))                                                                               \
        {                                                                                          \
            while (1)                                                                              \
                ;                                                                                  \
        }                                                                                          \
    }
#else
#define BT_ASSERT(test)                                                                   \
    {                                                                                              \
    }
#define BT_ASSERT_MSG(test, fmt, ...)                                                                   \
    {                                                                                              \
    }
#endif

#ifdef __cplusplus
}
#endif


#endif