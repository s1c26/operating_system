CC=clang
AS=nasm
LD=ld.lld

CFLAGS:=-nostdlib \
        -fno-builtin \
		-fno-stack-protector \
		-nostartfiles \
		-nodefaultlibs \
		-ffreestanding \
		-mno-red-zone \
		-mno-mmx \
		-mno-sse \
		-mno-sse2 \
		-masm=intel \
		-Wall -Werror -Wextra -Wpedantic \
		-O0

ASFLAGS:=-felf64

LINKERSCRIPT:=linkerscript.ld
LDFLAGS:=-T$(LINKERSCRIPT) \
		 -melf_x86_64 \
		 -nostdlib

TARGET:=KERNEL.ELF

_BUILD:=$(BUILD)/kernel

OBJECTS:=entry.c
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
