/* linker.ld */
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS {
  . = 0x100000;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss  : { *(.bss)  }
  .fs : {
    . = ALIGN(0x1000);
    KEEP(*(.fs))
    . = . + 64K; /* Reserve 64KB for FS */
}
}

