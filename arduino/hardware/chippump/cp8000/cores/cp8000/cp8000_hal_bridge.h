#ifndef ARDUINO_CP8000_HAL_BRIDGE_H
#define ARDUINO_CP8000_HAL_BRIDGE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void cp8000_core_init(void);

void cp8000_gpio_pin_mode(uint8_t pin, uint8_t mode);
void cp8000_gpio_write(uint8_t pin, uint8_t value);
int cp8000_gpio_read(uint8_t pin);
int cp8000_adc_read(uint8_t pin);
void cp8000_pwm_write(uint8_t pin, uint16_t value, uint16_t max_value);
void cp8000_tone_start(uint8_t pin, uint32_t frequency, uint32_t duration_ms);
void cp8000_tone_stop(uint8_t pin);

uint64_t cp8000_time_micros(void);
void cp8000_delay_us(uint32_t us);

void cp8000_uart_begin(uint8_t uart_index, uint32_t baud);
int cp8000_uart_available(uint8_t uart_index);
int cp8000_uart_read(uint8_t uart_index);
void cp8000_uart_write(uint8_t uart_index, uint8_t value);
void cp8000_uart_write_buffer(uint8_t uart_index, const uint8_t *data, uint32_t length);
void cp8000_uart_flush(uint8_t uart_index);

void cp8000_i2c_begin(void);
uint8_t cp8000_i2c_probe(uint8_t address);
uint8_t cp8000_i2c_write(uint8_t address, const uint8_t *data, uint8_t length);

void cp8000_spi_begin(void);
uint8_t cp8000_spi_transfer(uint8_t value);

void cp8000_wdt_begin(uint16_t timeout_ms);
void cp8000_wdt_feed(uint16_t timeout_ms);
void cp8000_wdt_disable(void);

void cp8000_flash_read(uint32_t address, uint8_t *data, uint32_t length);
void cp8000_flash_write(uint32_t address, const uint8_t *data, uint32_t length);
void cp8000_flash_erase_sector(uint32_t address);
void cp8000_flash_uid(uint32_t uid[4]);

void cp8000_sleep_ms(uint32_t ms);

void cp8000_ble_begin(void);
bool cp8000_ble_advertise_raw(const uint8_t *payload, uint8_t length);
bool cp8000_ble_notify(const uint8_t *data, uint16_t length);
bool cp8000_ble_connected(void);
bool cp8000_ble_subscribed(void);
int cp8000_ble_available(void);
int cp8000_ble_read(void);
uint16_t cp8000_ble_read_buffer(uint8_t *buffer, uint16_t length);
void cp8000_ble_set_read_value(const uint8_t *data, uint16_t length);
typedef void (*cp8000_ble_connected_callback_t)(void);
typedef void (*cp8000_ble_disconnected_callback_t)(uint8_t reason);
typedef void (*cp8000_ble_write_callback_t)(const uint8_t *data, uint16_t length);
void cp8000_ble_on_connected(cp8000_ble_connected_callback_t callback);
void cp8000_ble_on_disconnected(cp8000_ble_disconnected_callback_t callback);
void cp8000_ble_on_write(cp8000_ble_write_callback_t callback);
void cp8000_ble_handle_connected(uint32_t conn_handle);
void cp8000_ble_handle_disconnected(uint8_t reason);
void cp8000_ble_handle_subscribed(uint8_t enabled);
void cp8000_ble_handle_write(const uint8_t *data, uint16_t length);
void cp8000_ble_poll(void);

void cp8000_rf24g_begin(void);
void cp8000_rf24g_set_channel(uint16_t channel);
void cp8000_rf24g_set_power(int8_t dbm);
bool cp8000_rf24g_send(const uint8_t *payload, uint8_t length);
int cp8000_rf24g_receive(uint8_t *payload, uint8_t max_length);

#ifdef __cplusplus
}
#endif

#endif
