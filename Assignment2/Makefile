#
#  Peter Pan
#  u0680482
#  CS3505
#  Assignment 2 
# 
## Make file

## running with a -j56 option: 6s
## general principle is 7 * cores
## http://programmers.stackexchange.com/questions/156569/how-many-make-threads-to-use

# the compiler to use
CXX = g++
# -g turns on debugging
# -Wall turns on almost all warnings for g++
# -std=c++11 does something
CXXFLAGS = -g -Wall -std=c++11 $(OPTFLAGS)
# Optimization flags: 
OPTFLAGS = -O0
# The main resulting executable that will be compiled into.
EXECUTABLE = $(BUILDDIR)/spiralPDF

### Directives/Special Variables ###
# Just in case you have a file also named "all" or "clean" this 
# will let make know that it should run these commands no matter what.
.PHONY: all clean
# Sets the default goal to be used if no targets were specified on the command line 
# Reset the default goal by using: 
# .DEFAULT_GOAL := 
.DEFAULT_GOAL := all

### Directories ###
# Target directory if we want to change output to another folder.
BUILDDIR = ./bin
# Library directory to include any library files.
LIBDIR = .

### libHaru variables ###
# libHaru Library files.
LIBHARU = $(BUILDDIR)/libharu-libharu-d84867e
LIBHARU_INCLUDE = $(LIBHARU)/include
LIBHARU_SRC = $(LIBHARU)/src
LIBHARU_FLAGS = -L $(LIBHARU_SRC) -I $(LIBHARU_INCLUDE) -l hpdfs -lz
# Compile libHaru:
# If the directory doesn't exist, extract it and then build it.
# The -C option changes the directory before invoking the make command.
# The $(MAKE) variable will use the same make executable as the top-level makefile. 
# Commands on different lines are executed on different shells.
$(LIBHARU): $(BUILDDIR)
	unzip -o libharu.zip -d $(BUILDDIR) 
	cd $(LIBHARU) && cmake . && $(MAKE) -C .


# If you just write make in command line, without specifying the target, 
# it will build the first target. But we have the .DEFAULT_GOAL special 
# variable, so it will default to this target. 
all: $(EXECUTABLE)

# Create the target directory if it doesn't exist
# -p: will also create all directories leading up to the given 
#		directory that do not exist already. If the given 
#		directory already exists, ignore the error.
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# compile the main executable 
$(EXECUTABLE): spiralPDF.cpp $(BUILDDIR)/HaruPDF.o $(BUILDDIR)/Spiral.o $(BUILDDIR)/pdfExample.o
	$(CXX) $(CXXFLAGS) $< -o $@ 

# Compile all source files into .o files 
$(BUILDDIR)/HaruPDF.o: HaruPDF.cpp $(LIBHARU)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBHARU_FLAGS)

$(BUILDDIR)/Spiral.o: Spiral.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tried to use dependency of $(LIBHARU_INCLUDE), but it didn't like it. I guess it
# doesn't traverse variable dependencies.
$(BUILDDIR)/pdfExample.o: pdfExample.cpp $(LIBHARU)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBHARU_FLAGS)

# just for the record, the working compile statement expanded: 
# g++ -o pdfExample -O2 -Wall pdfExample.cpp -L ./bin/libharu-libharu-d84867e/src -I ./bin/libharu-libharu-d84867e/include -l hpdfs -lz
pdfExample: pdfExample.cpp $(LIBHARU)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBHARU_FLAGS)

# Delete all generated files
clean:
	rm -rf $(EXECUTABLE) *.o
	rm -rf $(LIBHARU)
