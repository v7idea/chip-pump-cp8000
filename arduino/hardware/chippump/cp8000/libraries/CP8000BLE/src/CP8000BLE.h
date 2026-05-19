#ifndef CP8000_BLE_H
#define CP8000_BLE_H

#include <Arduino.h>

#define UART_SERVICE_UUID      "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

typedef void (*CP8000BLEConnectedCallback)(void);
typedef void (*CP8000BLEDisconnectedCallback)(uint8_t reason);
typedef void (*CP8000BLEWriteCallback)(const uint8_t *data, size_t length);

class CP8000BLEClass {
public:
  bool begin(void);
  bool advertise(const uint8_t *payload, size_t length);
  bool advertiseName(const char *name);
  bool advertiseUartService(const char *name = nullptr);
  bool advertiseManufacturerData(uint16_t companyId,
                                 const uint8_t *data,
                                 size_t length,
                                 const char *name = nullptr);
  bool notify(const uint8_t *data, size_t length);
  bool notify(const char *text);
  bool write(const uint8_t *data, size_t length);
  bool write(const char *text);
  bool setReadValue(const uint8_t *data, size_t length);
  bool setReadValue(const char *text);
  bool connected(void);
  bool subscribed(void);
  int available(void);
  int read(void);
  size_t read(uint8_t *buffer, size_t length);
  void onConnect(CP8000BLEConnectedCallback callback);
  void onDisconnect(CP8000BLEDisconnectedCallback callback);
  void onWrite(CP8000BLEWriteCallback callback);
  void poll(void);
};

extern CP8000BLEClass CP8000BLE;

#endif
