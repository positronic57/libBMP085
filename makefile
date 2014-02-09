############################################################################
# Makefile for builing and installing libbmp085
############################################################################
RM := rm -rf

PREFIX = /usr

CC = gcc
CFLAGS = -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP
LDFLAGS = -shared
SOURCES = libbmp085.c
OBJECTS = $(SOURCES:.c=.o)
	
all: libbmp085.so

libbmp085.so: $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

libbmp085.o: $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

clean:
	-$(RM) libbmp085.o libbmp085.so libbmp085.d

# Install the library in $(prefix)
install: 
	install -m 0644 libbmp085.so $(PREFIX)/lib
	install -m 0644 libbmp085.h $(PREFIX)/include

