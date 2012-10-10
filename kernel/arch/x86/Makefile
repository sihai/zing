###########################################################################
#								zing
#
#
###########################################################################


include ../../../config.mk

CFLAGS += -I../inc

.PHONY : all clean

all:x86

x86:boot
	

boot:
	cd boot;make
	
bootsector.o: bootsector.S
	$(CC) $(CFLAGS) -nostdinc -c bootsector.S

clean:
	cd boot;make clean