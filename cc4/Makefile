COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall
LINKER = g++

all: decoder

decoder : png.o rgbapixel.o decoder.o
	$(LINKER) decoder.o png.o rgbapixel.o -lpng -o decoder

decoder.o : decoder.cpp
	$(COMPILER) $(COMPILER_FLAGS) decoder.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp

clean :
	- rm -f *.o testimage testscene
