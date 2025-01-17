#include <efi/efi.h>
#include "gdt.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, World!\n");
    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);

    SystemTable->BootServices->ExitBootServices(ImageHandle, 0);

    gdt_init();

    asm("movq $0xdeaddeaddeaddead, %%rax;"
        "cli;"
        "hlt;"
        :
        :
        :"%rax"
    );

    return EFI_SUCCESS;
}
