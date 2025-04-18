ENTRY(boot_main)

SECTIONS
{
  

  .boot ALIGN(4):
{
    KEEP(*(.boot))
    *(.rodata*)
}

}
