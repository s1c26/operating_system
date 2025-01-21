SUBDIRS:=kernel

BUILD:=build

all: $(SUBDIRS)

$(SUBDIRS): $(BUILD)
	$(MAKE) -C $@ BUILD=$(realpath $(BUILD))

$(BUILD):
	mkdir -p $(BUILD)

.PHONY: all $(SUBDIRS) clean run debug

clean:
	rm -rf $(BUILD)

run: $(SUBDIRS) $(BUILD)/BOOTX64.EFI $(BUILD)/KERNEL.ELF
	uefi-run $(BUILD)/BOOTX64.EFI -f $(BUILD)/KERNEL.ELF

debug: $(_TARGET)
	uefi-run -d $(_TARGET) -- -s -S &
	lldb $(_TARGET)
