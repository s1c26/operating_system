section .text
global gdt_load
gdt_load:
    push    ebp
    mov     ebp, esp

    mov     eax, [ebp + 8]
    lgdt    [eax]

    ; Do some hacky stuff to effectuate new GDT
    mov     eax, [ebp + 12]
    push    eax
    push    .reload_cs
    retf

.reload_cs:
    mov     eax, [ebp + 16]
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax

    pop     ebp
    ret
