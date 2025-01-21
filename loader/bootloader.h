#ifndef _BOOTLOADER_H
#define _BOOTLOADER_H

#include "efi/efi.h"

extern EFI_BOOT_SERVICES *bs;
extern SIMPLE_TEXT_OUTPUT_INTERFACE *conOut;

EFI_FILE_PROTOCOL *open_file(EFI_HANDLE ImageHandle, CHAR16 *filename);

UINTN get_file_size(EFI_FILE_PROTOCOL *file);

#endif
