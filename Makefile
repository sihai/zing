###########################################################################
#								zing
#
#
###########################################################################

include config.mk

.PHONY : all clean

QEMU = qemu-system-i386

# try to infer the correct QEMU
# try to infer the correct QEMU
ifndef QEMU
QEMU := $(shell if which qemu-system-i386 > /dev/null; \
	then echo qemu-system-i386 ; exit; \
	else \
	qemu=/Applications/Q.app/Contents/MacOS/i386-softmmu.app/Contents/MacOS/i386-softmmu; \
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

all:kernel/zing-kernel.img

kernel/zing-kernel.img:
	cd kernel;make

qemu: kernel/zing-kernel.img
	${QEMU} -smp 2 -parallel stdio kernel/zing-kernel.img

qemu-gdb: zing.img .gdbinit
	@echo "***"
	@echo "*** Now run 'gdb'." 1>&2
	@echo "***"
	qemu -parallel stdio -hdb fs.img myos.img -S $(QEMUGDB)

.gdbinit: .gdbinit.tmpl
	sed "s/localhost:1234/localhost:$(GDBPORT)/" < $^ > $@

clean:
	cd kernel;make clean
