###########################################################################
#								zing
#
#
###########################################################################

include ../config.mk

CFLAGS = ${CFLAGS} -Iinc

 ifeq (${TARGET}, x86)
 	ARCH = x86
 endif
 

.PHONY : all clean

all:zing-kernel.img

zing-kernel.img: ${ARCH} init/init.o
	dd if=/dev/zero of=zing-kernel.img count=400
	dd if=arch/x86/boot/bootblock of=zing-kernel.img conv=notrunc
	dd if=init.o of=zing-kernel.img seek=1 conv=notrunc

x86:
	cd arch/x86/boot;make 
	./sign.pl arch/x86/boot/bootblock

init/init.o:
	cd init;make

clean:
	cd init;make clean
	rm -f zing-kernel.img
	cd x86;make clean 
	rm -fr kernel
