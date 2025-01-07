#include "GDT.h"

void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].granularity = (limit >> 16) & 0x0F;

    gdt[index].granularity |= (granularity & 0xF0);
    gdt[index].access = access;
}

void init_gdt() {
    gdt_pointer.limit = (sizeof(struct GDTEntry) * GDT_ENTRIES) - 1;
    gdt_pointer.base = (uint32_t)&gdt;

    // Null descriptor
    set_gdt_entry(0, 0, 0, 0, 0);

    // Code segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Data segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Load the GDT
    load_gdt(&gdt_pointer);
}