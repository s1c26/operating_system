#ifndef _KERNEL_SYMBOLS_H
#define _KERNEL_SYMBOLS_H

#include <stdint.h>

extern uint32_t kernel_start;
extern uint32_t header_start;
extern uint32_t header_end;
extern uint32_t text_start;
extern uint32_t text_end;
extern uint32_t rodata_start;
extern uint32_t rodata_end;
extern uint32_t data_start;
extern uint32_t data_end;
extern uint32_t bss_start;
extern uint32_t bss_end;
extern uint32_t kernel_end;

#endif
