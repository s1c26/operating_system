#include "efi/efi.h"
#include "bootloader.h"

EFI_FILE_PROTOCOL *open_file(EFI_HANDLE ImageHandle, CHAR16 *filename)
{
    EFI_STATUS status;

    // Get Loaded Image Protocol
    EFI_GUID loadedImageGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_LOADED_IMAGE_PROTOCOL *loadedImage = NULL;
    status = bs->HandleProtocol(
        ImageHandle,
        &loadedImageGuid,
        (void**)&loadedImage
    );
    if(EFI_ERROR(status))
    {
        conOut->OutputString(conOut, L"ERROR: Could not get Loaded Image Protocol\r\n");
        return NULL;
    }

    // Get simple file system protocol
    // This will be used to load the kernel file from the EFI system partition
    EFI_GUID simpleFilesystemGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simpleFilesystem = NULL;
    status = bs->HandleProtocol(
        loadedImage->DeviceHandle,
        &simpleFilesystemGuid,
        (void**)&simpleFilesystem
    );
    if(EFI_ERROR(status))
    {
        conOut->OutputString(conOut, L"ERROR: Could not get Simple File System Protocol\r\n");
        return NULL;
    }

    // Now open root directory of EFI system partition
    EFI_FILE_PROTOCOL *rootDir = NULL;
    status = simpleFilesystem->OpenVolume(simpleFilesystem, &rootDir);
    if(EFI_ERROR(status))
    {
        conOut->OutputString(conOut, L"ERROR: Could not open root directory\r\n");
        return NULL;
    }

    // Finally, open the kernel image file
    EFI_FILE_PROTOCOL *file = NULL;
    status = rootDir->Open(rootDir, &file, filename, EFI_FILE_MODE_READ, 0);
    if(EFI_ERROR(status))
    {
        conOut->OutputString(conOut, L"ERROR: Could not open kernel image\r\n");
        return NULL;
    }

    return file;
}

UINTN get_file_size(EFI_FILE_PROTOCOL *file)
{
    UINTN fileSize = 0;
    EFI_STATUS status;

    // Allocate memory pool for file info structure:
    UINTN bufferSize = sizeof(EFI_FILE_INFO) + 256;
    EFI_FILE_INFO *fileInfo = NULL;
    status = bs->AllocatePool(
        EfiBootServicesData,
        bufferSize,
        (void**)&fileInfo
    );
    if(EFI_ERROR(status))
    {
        conOut->OutputString(conOut, L"ERROR: Could not allocate memory pool\r\n");
        return 0;
    }

    // Get FileInfo structure
    EFI_GUID fileInfoGuid = EFI_FILE_INFO_ID;
    status = file->GetInfo(file, &fileInfoGuid, &bufferSize, fileInfo);
    if(EFI_ERROR(status))
    {
        conOut->OutputString(conOut, L"ERROR: Could not get file info\r\n");
        return 0;
    }

    // Get file size
    fileSize = fileInfo->FileSize;

    // Free file info
    bs->FreePool(fileInfo);

    return fileSize;
}
