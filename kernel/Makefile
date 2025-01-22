CC=clang
AS=nasm
LD=ld.lld

CFLAGS:=-m32 \
		-nostdlib \
        -fno-builtin \
		-fno-stack-protector \
		-nostartfiles \
		-nodefaultlibs \
		-ffreestanding \
		-I../include \
		-Iinclude \
		-masm=intel \
		-Wall -Werror -Wextra -Wpedantic \
		-O0

ASFLAGS:=-felf32

LINKERSCRIPT:=linkerscript.ld
LDFLAGS:=-T$(LINKERSCRIPT) \
		 -melf_i386 \
		 -nostdlib

TARGET:=KERNEL.ELF

_BUILD:=$(BUILD)/kernel

OBJECTS:=entry.asm kernel_main.c gdt_load.asm gdt.c
_OBJECTS:=$(patsubst %.c, $(_BUILD)/%.o, $(OBJECTS))
_OBJECTS:=$(patsubst %.asm, $(_BUILD)/%.o, $(_OBJECTS))
_TARGET:=$(BUILD)/$(TARGET)

all: $(_TARGET)

$(_TARGET): $(_OBJECTS)
	$(LD) $(LDFLAGS) $(_OBJECTS) -o $(_TARGET)

$(_BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

$(_BUILD)/%.o: %.asm
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<
