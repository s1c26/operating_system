#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>

// GDT Access Byte flags
#define GDT_AC_PRES ((uint8_t)0x80)
#define GDT_AC_PRIV(x) ((uint8_t)((x & 0x03) << 5))
#define GDT_AC_NONSYS ((uint8_t)0x10)
#define GDT_AC_AC ((uint8_t)1)

#define GDT_AC_DATA_R ((uint8_t)0x00)
#define GDT_AC_DATA_RW ((uint8_t)0x02)
#define GDT_AC_DATA_RXD ((uint8_t)0x04)
#define GDT_AC_DATA_RWXD ((uint8_t)0x06)
#define GDT_AC_CODE_X ((uint8_t)0x08)
#define GDT_AC_CODE_XR ((uint8_t)0x0a)
#define GDT_AC_CODE_XC ((uint8_t)0x0c)
#define GDT_AC_CODE_XRC ((uint8_t)0x0e)

// GDT Granularity Byte flags
#define GDT_GR_PAGE ((uint8_t)(1 << 7))
#define GDT_GR_32 ((uint8_t)(1 << 6))
#define GDT_GR_64 ((uint8_t)(1 << 5))

// GDT entry structure
struct GDTEntry {
    uint16_t limit_low;  // Lower 16 bits of the limit
    uint16_t base_low;   // Lower 16 bits of the base
    uint8_t base_middle; // Next 8 bits of the base
    uint8_t access;      // Access flags
    uint8_t granularity; // Granularity and high limit
    uint8_t base_high;   // Last 8 bits of the base
} __attribute__((packed));

typedef struct GDTEntry gdt_entry_t;

// GDTR structure
struct GDTPointer {
    uint16_t limit; // Size of the GDT
    uint64_t base;  // Base address of the GDT
} __attribute__((packed));

typedef struct GDTPointer gdt_pointer_t;

/**
 * Sets a gdt entry with the base, limit, access, and granularity flags
 * provided.
 * 
 * @param entry pointer to the entry to be modified
 * @param base base address of descriptor
 * @param limit length of descriptor
 * @param access access flags
 * @param granularity granularity and other flags
 */
void gdt_set_entry(gdt_entry_t *entry,
                   uint32_t base,
                   uint32_t limit,
                   uint8_t access,
                   uint8_t granularity);
  
/**
 * Loads a gdt.
 * 
 * @param pointer pointer to the GDT pointer
 */
extern void gdt_load(gdt_pointer_t *pointer, uint8_t kernel_code_idx, uint8_t kernel_data_idx);

// Main function to initialize GDT
void gdt_init();

#endif
