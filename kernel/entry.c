void kernel_entry()
{
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
    asm volatile("mov rax,0xdead0000deaddead;"
                 "cli;"
                 "hlt;"
                 :
                 :
                 :"rax");
}
