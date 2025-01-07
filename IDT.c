#include "IDT.h"

void set_idt_entry(int index, uint32_t base, uint16_t selector, uint8_t type_attr) {
    idt[index].base_low = base & 0xFFFF;
    idt[index].base_high = (base >> 16) & 0xFFFF;
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].type_attr = type_attr;
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