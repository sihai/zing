###########################################################################
#								zing
#
#
###########################################################################

include ../../config.mk

CFLAGS += -I../inc -I../

OBJECTS = zing.o

.PHONY : all clean

all:${OBJECTS}

-include *.d
	
clean:
	rm -fr ${OBJECTS}
