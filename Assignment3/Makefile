#
#  Peter Pan
#  u0680482
#  CS3505
#  Assignment 3
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
EXECUTABLE = $(BUILDDIR)/TrieTest



### Directives/Special Variables ###
# Just in case you have a file also named "all" or "clean" this 
# will let make know that it should run these commands no matter what.
.PHONY: all clean
# Sets the default goal to be used if no targets were specified on the command line 
# Reset the default goal by using: 
# .DEFAULT_GOAL := 
.DEFAULT_GOAL := all



### Directory Variables ###
# Target directory if we want to change output to another folder.
BUILDDIR = ./bin
# Library directory to include any additional library files.
LIBDIR = .



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
	
# compile the main executable linking all object files
# Tried to use dependency of $(LIBHARU_INCLUDE), but it didn't like it. I guess 
# it doesn't traverse variable dependencies.
$(EXECUTABLE): TrieTest.cpp $(BUILDDIR) $(BUILDDIR)/Trie.o $(BUILDDIR)/node.o
	$(CXX) $(CXXFLAGS) $< $(BUILDDIR)/Trie.o $(BUILDDIR)/node.o -o $@

# List and compile all object files 
#TRIETEST_OBJS = \
#    $(BUILDDIR)/Trie.o \
#    $(BUILDDIR)/node.o
$(BUILDDIR)/Trie.o: Trie.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(BUILDDIR)/node.o: node.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
# Delete all generated files
clean:
	rm -rf $(EXECUTABLE) *.o