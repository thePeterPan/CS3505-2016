## Make file

## running with a -j56 option: 6s
## general principle is 7 * cores
## http://programmers.stackexchange.com/questions/156569/how-many-make-threads-to-use

# the compiler to use
CXX = g++
# -g turns on debugging
# -Wall turns on almost all warnings for g++
# -std=c++11 does something
CXXFLAGS = -g -Wall -std=c++11
# The main resulting executable that will be compiled into.
EXECUTABLE = spiralPDF


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
TARGETDIR = .
# libHaru Library files.
LIBHARU = ./libharu-libharu-d84867e
# Library directory to include any library files.
LIBDIR = $(LIBHARU)/include


# If you just write make in command line, without specifying the target, 
# it will build the first target. That's why this goes first here. But 
# we have the .DEFAULT_GOAL special variable, so it will already default
# to this target. 
all: $(TARGETDIR)/$(EXECUTABLE)

# Create the target directory if it doesn't exist
# -p: will also create all directories leading up to the given 
#		directory that do not exist already. If the given 
#		directory already exists, ignore the error.
$(TARGETDIR):
	mkdir -p $(TARGETDIR)
# Compile libHaru:
# If the directory doesn't exist, extract it and then build it.
# The -C option changes the directory before invoking the make command.
# The $(MAKE) variable will use the same make executable as the top-level makefile. 
# Commands on different lines are executed on different shells.
$(LIBHARU):
	unzip libharu.zip -d . 
	cd $(LIBHARU) && cmake . && $(MAKE) -C .

# compile the main executable 
$(EXECUTABLE): spiralPDF.cpp HaruPDF.o Spiral.o pdfExample.o
	$(CXX) $(CXXFLAGS) -o $@ spiralPDF.cpp

# Compile all source files into .o files 
HaruPDF.o: HaruPDF.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Sprial.o: Sprial.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

pdfExample.o: pdfExample.cpp $(LIBHARU)
	$(CXX) $(CXXFLAGS) -I$(LIBDIR) -c $< -o $@ 

# Delete all generated files
clean: 
	rm -rf $(EXECUTABLE) *.o
	rm -rf $(LIBHARU)