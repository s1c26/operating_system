
MULTIBOOT_MAGIC equ 0x1badb002
MULTIBOOT_FLAGS equ 0x00000003
MULTIBOOT_CHECK equ - MULTIBOOT_MAGIC - MULTIBOOT_FLAGS
STACK_SIZE equ 16384
PAGE_SIZE equ 0x1000

%define physical(addr) (addr - 0xc0000000)

extern kernel_start
extern kernel_end
extern kernel_main

section .start
align 4

header:
    dd MULTIBOOT_MAGIC
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECK

global entry
entry:
    ; The source pointer points to the entry of our page table;
    ; The destination pointer will keep track of the physical address of the 
    ; kernel.
    ; ECX stores the number of pages in a table
    mov     edi, physical(page_table0)
    xor     esi, esi
    mov     ecx, 1024

.skip:
    ; While we are still less than the kernel start address, increment
    cmp     esi, physical(kernel_start)
    jge     .map
    add     esi, PAGE_SIZE
    add     edi, 4
    loop    .skip
    
.map:
    ; Check that we haven't reached the end of the kernel yet
    cmp     esi, physical(kernel_end)
    jge     .done

    ; Put the page address into our table in the next entry and set the present
    ; and writable bits
    mov     edx, esi
    or      edx, 0x003
    mov     [edi], edx

    ; Advance to the next page
    add     esi, PAGE_SIZE
    add     edi, 4
    loop    .map

.done:
    ; Now we are finished with our page table, so we have to put it in our page
    ; directory and load it.
    mov     dword [physical(page_dir)], physical(page_table0) + 0x0003
    mov     dword [physical(page_dir) + 0xc00], physical(page_table0) + 0x0003
    mov     ecx, physical(page_dir)
    mov     cr3, ecx

    ; Enable paging
    mov     ecx, cr0
    or      ecx, 0x80010000
    mov     cr0, ecx

    ; Jump to the relocated section of code
    jmp     relocated

section .text
relocated:
    ; Remove the identity page mapping
    mov     dword [page_dir], 0

    ; Reload the page directory
    mov     ecx, cr3
    mov     cr3, ecx

    ; Set up kernel stack and call kernel
    mov     esp, stack_top

    ; Call the kernel, providing the multiboot information structure
    push    ebx
    call    kernel_main

    cli
    hlt    

section .bss
stack_bottom:
    resb STACK_SIZE
stack_top:

section .bss
align PAGE_SIZE
page_dir:
    resb PAGE_SIZE
page_table0:
    resb PAGE_SIZE
