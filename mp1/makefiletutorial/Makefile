COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

main.o : main.cpp sphere.h
	$(COMPILER) $(COMPILER_FLAGS) main.cpp

sphere.o : sphere.cpp
	$(COMPILER) $(COMPILER_FLAGS) sphere.cpp

myprogram : main.o sphere.o
	$(LINKER) main.o sphere.o -lpng -o myprogram

clean:
	-rm -f *.o myprogram
