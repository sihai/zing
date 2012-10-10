###########################################################################
#								zing
#
#
###########################################################################


include ../../../../config.mk

CFLAGS += -I../inc -I../../../inc

all:bootblock

bootblock: bootsector.o loader.o
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootsector.o loader.o
	$(OBJDUMP) -S bootblock.o > bootblock.asm
	$(OBJCOPY) -R .eh_frame -S -O binary bootblock.o bootblock

loader.o:
	$(CC) $(CFLAGS) -O -nostdinc -c loader.c

bootsector.o: bootsector.S
	$(CC) $(CFLAGS) -nostdinc -c bootsector.S

bootother: bootother.S
	$(CC) $(CFLAGS) -nostdinc -c bootother.S
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7000 -o bootother.out bootother.o
	$(OBJCOPY) -S -O binary bootother.out bootother
	$(OBJDUMP) -S bootother.o > bootother.asm

.PHONY : clean
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
