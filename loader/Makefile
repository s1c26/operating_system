CC=clang
AS=nasm
LD=lld-link

CFLAGS:=-target x86_64-pc-win32-coff \
		-ffreestanding \
        -fno-stack-protector \
		-iquote /usr/include \
		-iquote ../include \
		-fshort-wchar \
		-mno-red-zone \
		-masm=intel \
		-Wall -Werror -Wextra -Wpedantic \
		-O0

ASFLAGS:=-fwin64

LDFLAGS:=-filealign:16 \
		 -subsystem:efi_application \
		 -nodefaultlib \
		 -dll \
		 -entry:efi_main

TARGET:=BOOTX64.EFI

_BUILD:=$(BUILD)/loader

OBJECTS:=loader.c filesystem.c
_OBJECTS:=$(patsubst %.c, $(_BUILD)/%.o, $(OBJECTS))
_OBJECTS:=$(patsubst %.asm, $(_BUILD)/%.o, $(_OBJECTS))
_TARGET:=$(BUILD)/$(TARGET)

all: $(_TARGET)

$(_TARGET): $(_OBJECTS)
	$(LD) $(LDFLAGS) $(_OBJECTS) -out:$(_TARGET)

$(_BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

$(_BUILD)/%.o: %.asm
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<
