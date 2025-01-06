CC=clang
LD=lld-link

CFLAGS:=-target x86_64-pc-win32-coff \
        -fno-stack-protector \
		-I/usr/include \
		-fshort-wchar \
		-mno-red-zone \
		-c

LDFLAGS:=-filealign:16 \
		 -subsystem:efi_application \
		 -nodefaultlib \
		 -dll \
		 -entry:efi_main

BUILD:=build

TARGET:=BOOTX64.EFI
OBJECTS:=loader/loader.c
_OBJECTS:=$(patsubst %.c, build/%.o, $(OBJECTS))
_TARGET:=$(BUILD)/$(TARGET)

$(_TARGET): $(_OBJECTS)
	$(LD) $(LDFLAGS) $< -out:$(_TARGET)

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean run

clean:
	rm -rf $(BUILD)

run: $(_TARGET)
	uefi-run $(_TARGET)