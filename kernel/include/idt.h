#ifndef _IDT_H
#define _IDT_H

#include "stdint.h"

// IDT Type Attribute Flags
#define IDT_PRES ((uint8_t)0x80)
#define IDT_INT_GATE ((uint8_t)0x0f)
#define IDT_TRAP_GATE ((uint8_t)0x0e)
#define IDT_PRIV(x) ((uint8_t)(x & 0x03) << 5)

// IDT entry structure
struct IDTEntry {
    uint16_t base_low;  // Lower 16 bits of the handler function address
    uint16_t segment;  // Kernel segment selector
    uint8_t ist;        // Reserved, always 0
    uint8_t type_attr;  // Descriptor type and attributes
    uint16_t base_mid;  // Higher 16 bits of the handler function address
    uint32_t base_high;
    uint32_t zero;
} __attribute__((packed));

typedef struct IDTEntry idt_entry_t;

// IDTR structure
struct IDTPointer {
    uint16_t limit; // Size of the IDT
    uint64_t base;  // Base address of the IDT
} __attribute__((packed));

typedef struct IDTPointer idt_pointer_t;

/**
 * Sets an idt entry with the base, segment, type attributes, and interrupt
 * stack table.
 * 
 * @param entry pointer to the entry to be modified
 * @param base base address of interrupt routine
 * @param segment segment offset to run routine in
 * @param ist offset into interrupt stack table
 * @param type_attr type attributes
 */
void set_idt_entry(idt_entry_t *entry,
                   uint64_t base,
                   uint16_t segment,
                   uint8_t ist,
                   uint8_t type_attr);

/**
 * Loads an idt.
 * 
 * @param idt_ptr pointer to the IDT pointer
 */
extern void idt_load(idt_pointer_t *idt_ptr);

// Main function to initialize IDT
void init_idt();

#endif
