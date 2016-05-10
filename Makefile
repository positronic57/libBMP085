############################################################################
# Makefile for builing and installing libbmp085
############################################################################
RM := rm -rf

PREFIX = /usr

CC = gcc
CFLAGS = -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP
LDFLAGS = -shared
SOURCES = libbmp085.c I2Cbus.c
OBJECTS = $(SOURCES:.c=.o)
	
all: libbmp085.so

libbmp085.so: $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

libbmp085.o: $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

clean:
	-$(RM) libbmp085.o libbmp085.so libbmp085.d I2Cbus.o I2Cbus.d

# Install the library in $(prefix)
install: 
	install -m 0644 libbmp085.so $(PREFIX)/lib
	install -m 0644 libbmp085.h $(PREFIX)/include
	install -m 0644 I2Cbus.h $(PREFIX)/include
# Uninstall the library from the system
uninstall:
	rm $(PREFIX)/lib/libbmp085.so
	rm $(PREFIX)/include/libbmp085.h
	rm $(PREFIX)/include/I2Cbus.h

