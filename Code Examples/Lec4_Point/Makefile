# Turn the Point class into a static library and compile against that instead of the .o

CC = g++
CFLAGS = -Wall -std=c++11

# Define a variable to show where libPoint.a is
POINTLIBDIR = . #it is in the current directory

# Define a directory for where the Point library headers are
POINTLIBINCLUDE = .
# -lPoint expands to libPoint.a
pointTest : libPoint.a main.o
	$(CC) $(CFLAGS) -o pointTest main.o -L$(POINTLIBDIR) -lPoint

# Normally, a library would be built out of a collection of .o files
libPoint.a: Point.o
	ar -rcs libPoint.a Point.o

# We use the POINTLIBINCLUDE variable to let make know where the
# .h is for dependency checking and for letting compiler know
# where to look for including header files.

Point.o : $(POINTLIBINCLUDE)/Point.h Point.cpp
	$(CC) $(CFLAGS) -c -I$(POINTLIBINCLUDE) Point.cpp

main.o : main.cpp $(POINTLIBINCLUDE)/Point.h
	$(CC) $(CFLAGS) -c -I$(POINTLIBINCLUDE) main.cpp

# add a make clean and make test option
clean:
	rm pointTest *.o libPoint.a

test:
	./pointTest
