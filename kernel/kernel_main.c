#include "multiboot.h"
#include "gdt.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"
void kernel_main(multiboot_info_t *mboot_table)
{

    gdt_init();

#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
    asm volatile("mov eax,0xdeaddead;"
                 "cli;"
                 "hlt;"
                 :
                 :
                 :"eax");
}
