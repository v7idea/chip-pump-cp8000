ENTRY(_start)

MEMORY
{
  RAM (rwx) : ORIGIN = 0x20002000, LENGTH = 0x0100
}

SECTIONS
{
  .text :
  {
    *(.text.startup*)
    *(.text*)
    *(.rodata*)
  } > RAM
}
