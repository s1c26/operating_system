section .text
global gdt_load
gdt_load:
    lgdt    [rcx]

    ; Do some hacky stuff to effectuate new GDT
    mov     rax, rdx
    push    rax
    lea     rax, [rel .reload_cs]
    push    rax
    retfq

.reload_cs:
    mov     rax, r8
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    ret
