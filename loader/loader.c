#include "efi/efi.h"
#include "bootloader.h"
#include "string.h"

EFI_BOOT_SERVICES *bs = NULL;
SIMPLE_TEXT_OUTPUT_INTERFACE *conOut = NULL;

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS status;
    (void)status;

    bs = SystemTable->BootServices;
    conOut = SystemTable->ConOut;

    // Print message and disable watchdog timer
    conOut->OutputString(conOut, L"Loading KERNEL.ELF\r\n");
    bs->SetWatchdogTimer(0, 0, 0, NULL);

    EFI_FILE_PROTOCOL *file = open_file(ImageHandle, L"KERNEL.ELF");

    UINTN filesize = get_file_size(file);

    char buffer[30];
    
    //return EFI_SUCCESS;
}
