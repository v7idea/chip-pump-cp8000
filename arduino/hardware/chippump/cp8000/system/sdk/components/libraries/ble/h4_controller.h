#ifndef __H4_CONTROLLER_H__
#define __H4_CONTROLLER_H__

#include "bt_buf.h"

void h4_polling_rx(void);
void h4_send_data(simple_buf_t *buf);
void h4_open(void);

#endif

