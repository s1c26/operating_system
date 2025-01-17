section .text

; value is in rcx, address is in rdx

global outb
outb:
    mov     al, cl
    out     al, dx 
    ret

global outw
outw:
    mov     ax, cx
    out     ax, dx 
    ret

global outl
outl:
    mov     eax, ecx
    out     eax, dx
    ret

; address is in rcx

global inb
inb:
    mov     dx, cx
    in      al, dx
    ret

global inw
inw:
    mov     dx, cx
    in      ax, dx
    ret

global inl
inl:
    mov     dx, cx
    in      eax, dx
    ret
