535509# Cross-compiling (e.g., on Mac OS X)
# TOOLPREFIX = i386-jos-elf-

# Using native tools (e.g., on X86 Linux)
TOOLPREFIX = 

CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)as
LD = $(TOOLPREFIX)ld
OBJCOPY = $(TOOLPREFIX)objcopy
OBJDUMP = $(TOOLPREFIX)objdump
CFLAGS = -fno-builtin -O2 -Wall -MD -ggdb -m32 -I ../../inc
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
ASFLAGS = -m32
# FreeBSD ld wants ``elf_i386_fbsd''
LDFLAGS += -m $(shell $(LD) -V | grep elf_i386 2>/dev/null)

all:bootblock

bootblock: bootsector.o loader.o
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootsector.o loader.o
	$(OBJDUMP) -S bootblock.o > bootblock.asm
	$(OBJCOPY) -R .eh_frame -S -O binary bootblock.o bootblock
	./sign.pl bootblock

loader.o:
	$(CC) $(CFLAGS) -O -nostdinc -c loader.c

bootsector.o: bootsector.S
	$(CC) $(CFLAGS) -nostdinc -c bootsector.S

bootother: bootother.S
	$(CC) $(CFLAGS) -nostdinc -c bootother.S
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7000 -o bootother.out bootother.o
	$(OBJCOPY) -S -O binary bootother.out bootother
	$(OBJDUMP) -S bootother.o > bootother.asm

clean:
	rm -f bootblock.o
	rm -f bootblock
	rm -f bootblock.asm
	rm -f loader.d
	rm -f loader.o
	rm -f bootsector.o
	rm -f bootsector.d
	rm -f bootother.o
	rm -f bootother
	rm -f bootother.asm
	rm -f bootother.out
	rm -f bootother.d