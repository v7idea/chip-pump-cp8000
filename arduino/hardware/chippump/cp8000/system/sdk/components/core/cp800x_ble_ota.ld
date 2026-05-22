/*
 app ble ota
*/
__FLASH_BASE = 0x10001000;
__FLASH_SIZE = 0x0001E000;

__RAM_BASE = 0x20000A00;
__RAM_SIZE = 0x00003600;

__STACK_SIZE = 0x00000400;
__HEAP_SIZE  = 0x00000000;

MEMORY
{
    FLASH (rx)  : ORIGIN = __FLASH_BASE, LENGTH = __FLASH_SIZE
    RAM   (rwx) : ORIGIN = __RAM_BASE, LENGTH = __RAM_SIZE
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */

ENTRY(reset_handler)
INCLUDE "/../../../components/core/cp800x_ble2g4_api.ld"

SECTIONS
{
  .text :
  {
    *crt0*.o(.text .text.*)
	  /* *(EXCLUDE_FILE(*t1001_flash.o) .text*) */
    *(.text*)
    *(.rodata*)
    KEEP(*(.eh_frame*))
  } > FLASH

  __exidx_end = .;

  .copy.table :
  {
    . = ALIGN(4);
    __copy_table_start__ = .;

    LONG (__etext)
    LONG (__data_start__)
    LONG ((__data_end__ - __data_start__) / 4)

    __copy_table_end__ = .;
  } > FLASH

  .zero.table :
  {
    . = ALIGN(4);
    __zero_table_start__ = .;
    /* Add each additional bss section here */
    LONG (__bss_start__)
    LONG ((__bss_end__ - __bss_start__) / 4)

    __zero_table_end__ = .;
  } > FLASH

  __etext = ALIGN (4);

  .data : AT (__etext)
  {
    __data_start__ = .;
    *(.vectors)
    *(.data)
    *(.data.*)

    . = ALIGN(4);

    KEEP(*(.data.rf_common_desc_setfreq))

    *(.ram_code_section .ram_code_section.*)
    /* must align 4 */
    . = ALIGN(4);
    /* All data end */
    __data_end__ = .;
  } > RAM

  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > RAM

  .heap (COPY) :
  {
    . = ALIGN(4);
    __end__ = .;
    PROVIDE(end = .);
    . = . + __HEAP_SIZE;
    . = ALIGN(4);
    __HeapLimit = .;
  } > RAM

  .stack (ORIGIN(RAM) + LENGTH(RAM) - __STACK_SIZE) (COPY) :
  {
    . = ALIGN(4);
    __StackLimit = .;
    . = . + __STACK_SIZE;
    . = ALIGN(4);
    __StackTop = .;
  } > RAM
  PROVIDE(__stack = __StackTop);

  /* Check if data + heap + stack exceeds RAM limit */
  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
