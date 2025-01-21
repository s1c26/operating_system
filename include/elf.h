#ifndef _ELF_H
#define _ELF_H

#include "stdint.h"

struct ElfHeader
{
    uint32_t header;
    uint8_t class;
    uint8_t data;
    uint8_t version;


} __attribute__((packed));

typedef struct ElfHeader elf_header_t;

#endif
