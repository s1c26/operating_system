ENTRY(entry)

SECTIONS
{
    . = 2M;

    kernel_start = . + 0xc0000000;
    header_start = . + 0xc0000000;
    
    .header : {
        *(.header);
    }

    . += 0xc0000000;

    header_end = .;
    text_start = .;

    .text ALIGN(4K) : AT(ADDR(.text) - 0xc0000000)
    {
        *(.text)
    }

    text_end = .;
    rodata_start = .;

    .rodata ALIGN(4K) : AT(ADDR(.text) - 0xc0000000)
    {
        *(.rodata*)
    }

    rodata_end = .;
    data_start = .;

    .data ALIGN(4K) : AT(ADDR(.data) - 0xc0000000)
    {
        *(.data)
    }

    data_end = .;
    bss_start = .;

    .bss ALIGN(4K) : AT(ADDR(.bss) - 0xc0000000)
    {
        *(.bss)
        *(COMMON)
    }

    bss_end = .;
    kernel_end = .;
}
