#include <stdint.h>

#ifndef FLASH_BASE
#define FLASH_BASE 0x10000000u
#endif
#ifndef FIRMWARE_RAM
#define FIRMWARE_RAM 0x20004000u
#endif
#ifndef FIRMWARE_SIZE
#define FIRMWARE_SIZE 7428u
#endif
#ifndef FLASH_ERASE_SIZE
#define FLASH_ERASE_SIZE 0x40000u
#endif
#define SYS_MODE_REG 0x40000004u
#define UART_BASE 0x41001000u

typedef void (*void_fn_t)(void);
typedef int (*init_fn_t)(void);
typedef int (*erase_fn_t)(uint32_t address, uint32_t size);
typedef void (*write_fn_t)(uint32_t address, const uint8_t *data, uint32_t length);

static void uart_putc(char c) {
  volatile uint16_t *thr = (volatile uint16_t *)(UART_BASE + 0x00u);
  *thr = (uint16_t)c;
}

static void delay(volatile uint32_t count) {
  while (count--) {
    __asm__ volatile("nop");
  }
}

__attribute__((section(".text.startup"))) void _start(void) {
  init_fn_t flash_init = (init_fn_t)0x20000246u;
  erase_fn_t flash_erase = (erase_fn_t)0x20000326u;
  write_fn_t flash_write = (write_fn_t)0x20000804u;
  volatile uint32_t *mode = (volatile uint32_t *)SYS_MODE_REG;
  void_fn_t app_start = (void_fn_t)FLASH_BASE;

  *mode = 8u;
  uart_putc('S');

  uart_putc('I');
  flash_init();
  uart_putc('i');

  uart_putc('E');
  flash_erase(FLASH_BASE, FLASH_ERASE_SIZE);
  uart_putc('e');

  uart_putc('W');
  flash_write(FLASH_BASE, (const uint8_t *)FIRMWARE_RAM, FIRMWARE_SIZE);
  uart_putc('w');

  uart_putc('J');
  delay(100000u);
  app_start();

  while (1) {
    __asm__ volatile("wfi");
  }
}
