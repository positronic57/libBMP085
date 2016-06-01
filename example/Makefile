
# Makefile for building the examples distributed 
# with libsetila.

# Header files path (Update this with the library installation folder).
HEADERS_PATH = /usr/include

# Library path (Update this with the library installation folder).
LIBRARY_PATH = /usr/lib

# List of source files
SOURCES += WeatherStation.c

#List of object files
OBJECTS += $(SOURCES:.c=.o)

#Compile all of the source files
%.o: %.c
	@echo Compiling file: $<
	gcc -c $^ -o $@
	@echo

#Building libMAX7221example executable
WeatherStation: WeatherStation.o
	@echo Building target file: $@. 
	gcc -o $@ $^ -L$(LIBRARY_PATH) -lbmp085 -lm
	@echo 

.PHONY: clean

clean:
	rm -f *.o WeatherStation

