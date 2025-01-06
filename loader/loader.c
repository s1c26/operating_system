#include <efi/efi.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, World!\n");

    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);

    return EFI_SUCCESS;
}
