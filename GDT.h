#include <stdint.h>

// GDT entry structure
struct GDTEntry {
    uint16_t limit_low;  // Lower 16 bits of the limit
    uint16_t base_low;   // Lower 16 bits of the base
    uint8_t base_middle; // Next 8 bits of the base
    uint8_t access;      // Access flags
    uint8_t granularity; // Granularity and high limit
    uint8_t base_high;   // Last 8 bits of the base
} __attribute__((packed));

// GDTR structure
struct GDTPointer {
    uint16_t limit; // Size of the GDT
    uint32_t base;  // Base address of the GDT
} __attribute__((packed));

// Declare GDT and GDTR
#define GDT_ENTRIES 3
struct GDTEntry gdt[GDT_ENTRIES];
struct GDTPointer gdt_pointer;

// Function to set a GDT entry
void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
  
// Function to load the GDT
extern void load_gdt(struct GDTPointer* gdt_ptr);

// Main function to initialize GDT
void init_gdt();