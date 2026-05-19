#include <stdint.h>

#ifndef FIRMWARE_RAM
#define FIRMWARE_RAM 0x20001000u
#endif
#ifndef CONTROL_RAM
#define CONTROL_RAM 0x20003700u
#endif
#define SYS_MODE_REG 0x40000004u
#define SYS_RESET_REG 0x40000008u

typedef int (*init_fn_t)(void);
typedef void (*write_fn_t)(uint32_t address, const uint8_t *data, uint32_t length);

typedef struct {
  uint32_t flash_address;
  uint32_t length;
} program_control_t;

__attribute__((section(".text.startup"))) void _start(void) {
  init_fn_t flash_init = (init_fn_t)0x20000246u;
  write_fn_t flash_write = (write_fn_t)0x20000804u;
  volatile uint32_t *mode = (volatile uint32_t *)SYS_MODE_REG;
  volatile uint32_t *reset = (volatile uint32_t *)SYS_RESET_REG;
  volatile const program_control_t *control = (volatile const program_control_t *)CONTROL_RAM;

  *mode = 8u;
  flash_init();
  flash_write(control->flash_address, (const uint8_t *)FIRMWARE_RAM, control->length);
  *reset = 1u;

  while (1) {
    __asm__ volatile("wfi");
  }
}
