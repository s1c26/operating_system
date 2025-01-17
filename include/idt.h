#include <stdint.h>

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

// Declare IDT and IDTR
#define IDT_ENTRIES 256
struct IDTEntry idt[IDT_ENTRIES];
struct IDTPointer idt_pointer;

// Function to set an IDT entry
void set_idt_entry(idt_entry_t *entry,
                   uint64_t base,
                   uint16_t segment,
                   uint8_t ist,
                   uint8_t type_attr);

// Function to load the IDT
extern void load_idt(struct IDTPointer* idt_ptr);

// Main function to initialize IDT
void init_idt();
