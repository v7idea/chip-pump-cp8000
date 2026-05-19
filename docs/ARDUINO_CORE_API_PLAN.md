# Arduino Core API Plan

This document tracks the Arduino-facing API surface, the CP8000 bridge method,
the vendor SDK source location, and the validation plan.

## Core Runtime

| Arduino surface | Bridge / implementation | Vendor source reference | Status | Test plan |
| --- | --- | --- | --- | --- |
| `main()`, `setup()`, `loop()` | `cores/cp8000/main.cpp` | SDK startup via `libstartlib.a` and linker scripts | Hardware-validated | Blink + Serial prints after reset |
| C++ global constructors | `__libc_init_array()` + linker `.init_array` | `system/linker/cp800x_ble2g4_app.ld` | Hardware-validated | `Serial.println()` does not hang |
| `init()`, `yield()` | `wiring.c` | Arduino-compatible shim | Compile-validated | All examples compile |
| `delay()`, `delayMicroseconds()`, `millis()`, `micros()` | `cp8000_time_micros()` tick-based wait | timer register `0x42000104`, vendor timer refs in `components/driver/driver_timer.*` | Hardware-validated | `CoreHelpers` loop output repeats at about 2.0s with `delay(2000)` |
| ArduinoCore-avr helper macros | `Arduino.h` | AVR `Arduino.h` parity | Hardware-validated | `CoreHelpers` reports `flags=0`, `word=4660`, `low=52`, `high=18`, `clipped=50`, `sq=81`, `degrees=90` |
| `Printable`, fuller `Print` / `Stream` | `Printable.h`, `Print.*`, `Stream.*` parity subset | AVR `Printable.h`, `Print.*`, `Stream.*` | Hardware-validated | `SerialAdvanced` parser/printing example |
| `String` | first fixed-buffer `WString.*` subset for Serial/Stream usage | AVR `WString.*` | Hardware-validated | `Serial.println(String(...))` and UART parser test |
| `pulseIn()`, `pulseInLong()`, `shiftIn()`, `shiftOut()` | planned wiring parity | AVR `wiring_pulse.*`, `wiring_shift.c`; CP8000 GPIO/timer | Not started | generated pulse + shift-register tests |
| `attachInterrupt()`, `detachInterrupt()`, `interrupts()`, `noInterrupts()` | planned interrupt bridge | AVR `WInterrupts.c`; CP8000 GPIO interrupt driver if available | Not started | button interrupt smoke |

## Digital / Analog / Timing

| Arduino surface | Bridge / implementation | Vendor source reference | Status | Test plan |
| --- | --- | --- | --- | --- |
| `pinMode()` | `cp8000_gpio_pin_mode()` | `components/driver/driver_gpio.*`, `app/peripheral_example/GPIO` | Hardware-validated on D0 | D0 LED, input pull-up smoke |
| `digitalWrite()` | `cp8000_gpio_write()` | same as GPIO | Hardware-validated on D0 | LED high/low |
| `digitalRead()` | `cp8000_gpio_read()` | same as GPIO | Compile-validated | input jumper test |
| `analogRead()` | `cp8000_adc_read()` with `gpadc_channel_Init()` and `gpadc_get_sample()` | `components/driver/driver_gpadc.*`, `app/peripheral_example/ADC` | Hardware-validated on D6 | `AnalogReadSerial` reports about 2.9V on D6 and near 0V on D2/D7 |
| `analogWrite()` | `cp8000_pwm_write()` using `pwm_init()` / `pwm_duty_set()` | `components/driver/driver_timer.*` PWM APIs | Hardware-validated on D0 | `Fade` shows visible breathing-light brightness control |
| `tone()` / `noTone()` | `cp8000_tone_start/stop()` | timer/LEDC drivers | First-pass stub | audible/scope test |

## Serial / Buses

| Arduino surface | Bridge / implementation | Vendor source reference | Status | Test plan |
| --- | --- | --- | --- | --- |
| `Serial.begin()` | UART0 setup on P8/P9 | `components/driver/driver_uart.*`, `app/peripheral_example/UART` | Hardware-validated TX | Serial monitor at 115200 |
| `Serial.write()` / `Serial.println()` | `HardwareSerial`, `Print` | UART registers and C++ runtime | Hardware-validated TX | `LED ON/OFF` output |
| `Serial.available/read()` | `cp8000_uart_available/read()` | UART RX path | Hardware-validated | `SerialEcho` loopback + `BLESerialBridge` close-loop + `SerialAdvanced` parser test |
| `Wire` | `cp8000_i2c_*` | `components/driver/driver_iic.*`, `app/peripheral_example/IIC` | Hardware-validated first-pass | I2C scanner and SH1106-compatible OLED demo on SDA=D6/GPIO6 and SCL=D7/GPIO7 |
| `SPI` | `cp8000_spi_*` | `components/driver/driver_spim.*`, `app/peripheral_example/SPI_Master` | Compile-validated first-pass | loopback D2/MOSI to D3/MISO or flash sensor transfer |

## CP8000 Utility Libraries

| Library | Bridge / implementation | Vendor source reference | Status | Test plan |
| --- | --- | --- | --- | --- |
| `CP8000Flash` | `cp8000_flash_*` | `components/driver/driver_flash.*`, `app/peripheral_example/FLASH` | Compile-validated | UID read + scratch sector policy |
| `CP8000Watchdog` | `cp8000_wdt_*` | `components/driver/driver_wdt.*`, `app/peripheral_example/WATCHDOG` | Compile-validated | reset timing |
| `CP8000Sleep` | `cp8000_sleep_ms()` | `api_sleep_wakeup.h`, `app/peripheral_example/SLEEP_WAKEUP` | Stub | current measurement |
| `CP8000RF24G` | `cp8000_rf24g_*` | `api_rf_2g4.h`, `app/ble_adv_example/rf_2g4_proprietary` | First-pass/stub | two-board TX/RX |

## BLE Library

| Arduino surface | Bridge / implementation | Vendor source reference | Status | Test plan |
| --- | --- | --- | --- | --- |
| `CP8000BLE.begin()` | `libraries/CP8000BLE/src/cp8000_ble_bridge.c` | `components/ble/app/ble_app.c`, `app_ble_init()` | Hardware-validated | scanner sees device |
| `CP8000BLE.advertise()` | `libraries/CP8000BLE/src/cp8000_ble_bridge.c` | `ble_set_adv_data()`, `ble_adv_enable()` | Hardware-validated | nRF Connect / LightBlue scan |
| `CP8000BLE.poll()` | `libraries/CP8000BLE/src/cp8000_ble_bridge.c` | `ble_host_work_polling()` | Real-toolchain compile-validated | long-running advertising test |
| named advertising helpers | Arduino payload builder | `gap_def.h` AD types | Hardware-validated | scanner name and payload |
| connection callbacks | `onConnect()`, `onDisconnect()`, `connected()` | `ble_event_callback()`, `bt_conn_cb` | Real-toolchain compile-validated | `BLEConnectionStatus` phone connect/disconnect |
| NUS GATT service | `notify()`, `write()`, `setReadValue()`, `subscribed()`, `onWrite()`, `available()`, `read()` | `ble_service.c`, `gatt.h` | Hardware-validated | `BLESerialBridge` close-loop + `BLEUartEcho` phone write/notify |
| arbitrary UUID GATT builder | planned general wrapper | `ble_user_service_add()` | Deferred | custom service with read/write/notify characteristic |
| OTA | planned wrapper or separate example | `ble_ota_service.*`, `cp800x_ble_ota.ld` | Deferred | OTA transfer and reboot |

## Release-Gating Tests

1. Docker compile on macOS using Linux x86_64 XuanTie toolchain.
2. `arduino-cli compile` for every example.
3. Hardware upload of Blink with `Serial.println()`.
4. Serial monitor receives expected output after upload.
5. BLE advertising visible from a phone scanner.
6. Package archive and `package_chip-pump_cp8000_index.json` generated.
7. Arduino IDE Boards Manager install test on a clean machine.
