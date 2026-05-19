#include <stdint.h>

#define FLASH_BASE 0x10000000u
#define FLASH_ERASE_SIZE 0x40000u
#define SYS_MODE_REG 0x40000004u
#define SYS_RESET_REG 0x40000008u

typedef int (*init_fn_t)(void);
typedef int (*erase_fn_t)(uint32_t address, uint32_t size);

__attribute__((section(".text.startup"))) void _start(void) {
  init_fn_t flash_init = (init_fn_t)0x20000246u;
  erase_fn_t flash_erase = (erase_fn_t)0x20000326u;
  volatile uint32_t *mode = (volatile uint32_t *)SYS_MODE_REG;
  volatile uint32_t *reset = (volatile uint32_t *)SYS_RESET_REG;

  *mode = 8u;
  flash_init();
  flash_erase(FLASH_BASE, FLASH_ERASE_SIZE);
  *reset = 1u;

  while (1) {
    __asm__ volatile("wfi");
  }
}
