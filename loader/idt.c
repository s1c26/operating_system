#include "idt.h"

void set_idt_entry(idt_entry_t *entry,
                   uint64_t base,
                   uint16_t segment,
                   uint8_t ist,
                   uint8_t type_attr)
{
    entry->base_low = base & 0xffff;
    entry->base_mid = (base >> 16) & 0xffff;
    entry->segment = segment;
    entry->zero = 0;
    entry->ist = ist;
    entry->type_attr = type_attr;
    entry->base_high = (base >> 32) & 0xffffffff
}

void init_idt() {
    idt_pointer.limit = (sizeof(struct IDTEntry) * IDT_ENTRIES) - 1;
    idt_pointer.base = (uint32_t)&idt;

    // Set all IDT entries to 0 (unused interrupts)
    for (int i = 0; i < IDT_ENTRIES; i++) {
        set_idt_entry(i, 0, 0x08, 0x8E); // Null handler, ring 0, 32-bit interrupt gate
    }

    // Example: Set an interrupt handler for interrupt 0x21 (keyboard, for instance)
    extern void keyboard_interrupt_handler();
    set_idt_entry(0x21, (uint32_t)keyboard_interrupt_handler, 0x08, 0x8E);

    // Load the IDT
    load_idt(&idt_pointer);
}