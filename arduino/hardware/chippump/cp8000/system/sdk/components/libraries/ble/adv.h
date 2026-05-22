#ifndef __ADV_H__
#define __ADV_H__

#include "bt_common.h"
#include "gap_def.h"
#include "hci_def.h"

void bt_adv_data_copy(uint8_t *data, uint8_t *data_len,
                                 const struct bt_data *ad, size_t ad_len);

int hci_send_cmd_le_set_adv_param(uint16_t min_interval,
    uint16_t max_interval,
    uint8_t type,
    uint8_t own_addr_type,
    const bt_addr_le_t* direct_addr,
    uint8_t channel_map,
    uint8_t filter_policy);
int hci_send_cmd_le_set_adv_data(const struct bt_data *ad, size_t ad_len);
int hci_send_cmd_le_set_scan_rsp_data(const struct bt_data *sd, size_t sd_len);
int hci_send_cmd_le_set_adv_enable(uint8_t enable);

#endif