CC=clang
AS=nasm
LD=lld-link

ASFLAGS:=-fwin64

CFLAGS:=-target x86_64-pc-win32-coff \
		-ffreestanding \
        -fno-stack-protector \
		-I/usr/include \
		-Iinclude \
		-fshort-wchar \
		-mno-red-zone \
		-c \
		-O0 \
		-g

LDFLAGS:=-filealign:16 \
		 -subsystem:efi_application \
		 -nodefaultlib \
		 -dll \
		 -entry:efi_main \
		 -debug

BUILD:=build

TARGET:=BOOTX64.EFI
OBJECTS:=loader/loader.c loader/gdt.c loader/gdt_load.asm
_OBJECTS:=$(patsubst %.c, build/%.o, $(OBJECTS))
_OBJECTS:=$(patsubst %.asm, build/%.o, $(_OBJECTS))
_TARGET:=$(BUILD)/$(TARGET)

$(_TARGET): $(_OBJECTS)
	$(LD) $(LDFLAGS) $(_OBJECTS) -out:$(_TARGET)

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

build/%.o: %.asm
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<

.PHONY: clean run debug

clean:
	rm -rf $(BUILD)

run: $(_TARGET)
	uefi-run -d $(_TARGET)

debug: $(_TARGET)
	uefi-run -d $(_TARGET) -- -s -S &
	lldb $(_TARGET)
