#include "gdt.h"

gdt_entry_t gdt[3];
gdt_pointer_t gdt_pointer;

void gdt_set_entry(gdt_entry_t *entry,
                   uint32_t base,
                   uint32_t limit,
                   uint8_t access,
                   uint8_t granularity)
{
    entry->base_low = base & 0xFFFF;
    entry->base_middle = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;

    entry->limit_low = limit & 0xFFFF;
    entry->granularity = (limit >> 16) & 0x0F;

    entry->granularity |= (granularity & 0xF0);
    entry->access = access;
}

void gdt_init() {
    gdt_pointer.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt_pointer.base = (uint64_t)&gdt;

    // Null descriptor
    gdt_set_entry(&gdt[0], 0, 0, 0, 0);

    // Kernel Code segment
    uint8_t code_flags = GDT_AC_PRES
                       | GDT_AC_PRIV(0)
                       | GDT_AC_NONSYS
                       | GDT_AC_CODE_XR;

    // The 64 bit code flag is set because this is a 64-bit code segment. This
    // flag shouldn't be set for data segments
    uint8_t code_gran = GDT_GR_PAGE | GDT_GR_64;

    gdt_set_entry(&gdt[1], 0, 0xFFFFFFFF, code_flags, code_gran);

    // Kernel Data segment
    uint8_t data_flags = GDT_AC_PRES
                       | GDT_AC_PRIV(0)
                       | GDT_AC_NONSYS
                       | GDT_AC_DATA_RW;

    // The 32 bit flag is set because this is a data segment. The 64 bit flag is
    // only for code segments
    uint8_t data_gran = GDT_GR_PAGE | GDT_GR_32;
    
    gdt_set_entry(&gdt[2], 0, 0xFFFFFFFF, data_flags, data_gran);

    // Load the GDT
    gdt_load(&gdt_pointer, 1, 2);
}