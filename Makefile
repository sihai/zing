# Cross-compiling (e.g., on Mac OS X)
# TOOLPREFIX = i386-jos-elf-

# Using native tools (e.g., on X86 Linux)
TOOLPREFIX = 

CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)gas
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump
CFLAGS = -fno-builtin -O2 -Wall -MD -ggdb -m32 -I include
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
ASFLAGS = -m32
# FreeBSD ld wants ``elf_i386_fbsd''
LDFLAGS += -m $(shell $(LD) -V | grep elf_i386 2>/dev/null)


# try to infer the correct QEMU
ifndef QEMU
QEMU := $(shell if which qemu > /dev/null; \
	then echo qemu; exit; \
	else \
	qemu=; \
	if test -x $$qemu; then echo $$qemu; exit; fi; fi; \
	echo "***" 1>&2; \
	echo "*** Error: Couldn't find a working QEMU executable." 1>&2; \
	echo "*** Is the directory containing the qemu binary in your PATH" 1>&2; \
	echo "*** or have you tried setting the QEMU variable in conf/env.mk?" 1>&2; \
	echo "***" 1>&2; exit 1)
endif

# try to generate a unique GDB port
GDBPORT	:= $(shell expr `id -u` % 5000 + 25000)
# QEMU's gdb stub command line changed in 0.11
QEMUGDB = $(shell if $(QEMU) -nographic -help | grep -q '^-gdb'; \
	then echo "-gdb tcp::$(GDBPORT)"; \
	else echo "-s -p $(GDBPORT)"; fi)

all:zing.img

zing.img:kernel/arch/x86/boot/bootblock kernel/kernel
	dd if=/dev/zero of=zing.img count=400
	dd if=kernel/arch/x86/boot/bootblock of=zing.img conv=notrunc
	dd if=kernel/kernel of=zing.img seek=1 conv=notrunc

kernel/arch/x86/boot/bootblock:
	cd kernel/arch/x86/boot;make 

kernel/kernel:
	cd kernel;make


qemu: zing.img
	qemu -smp 2 -parallel stdio -hdb fs.img zing.img

qemu-gdb: zing.img .gdbinit
	@echo "***"
	@echo "*** Now run 'gdb'." 1>&2
	@echo "***"
	qemu -parallel stdio -hdb fs.img myos.img -S $(QEMUGDB)

.gdbinit: .gdbinit.tmpl
	sed "s/localhost:1234/localhost:$(GDBPORT)/" < $^ > $@

clean:

	rm -f zing.img
	cd boot;make clean 
	cd kernel;make clean
