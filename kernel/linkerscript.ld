ENTRY(kernel_entry)
SECTIONS
{
    . = 0xffff880000000000;

    .text : AT(ADDR(.text) - 0xffff880000000000)
    {
        _code = .;
        *(.text)
        *(.rodata*)
        . = ALIGN(4096);
    }

    .data : AT(ADDR(.data) - 0xffff880000000000)
    {
        _data = .;
        *(.data)
        . = ALIGN(4096);
    }

    .bss : AT(ADDR(.bss) - 0xffff880000000000)
    {
        _bss = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4096);
    }
}
