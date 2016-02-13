### Makefile

# CXX = g++
.PHONY: all make-clean clean
.DEFAULT_GOAL := all

### GTEST
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = ./googletest/googletest
# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h


# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
OPTFLAGS = -O0
CXXFLAGS = -g -Wall -std=c++11 -Wextra -pthread $(OPTFLAGS)


### MAIN EXECUTABLE
BUILDDIR = ./bin
EXECUTABLE = $(BUILDDIR)/test

all : $(BUILDDIR) $(EXECUTABLE)

$(BUILDDIR) :
	mkdir -p $(BUILDDIR)

clean : 
	rm -rf $(BUILDDIR)

$(EXECUTABLE) : $(BUILDDIR)/test.o $(BUILDDIR)/gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ Students.o -o $@

$(BUILDDIR)/test.o : StudentsTest.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 


### GTEST
# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$(BUILDDIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc \
            -o $@

$(BUILDDIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc \
            -o $@

$(BUILDDIR)/gtest.a : $(BUILDDIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILDDIR)/gtest_main.a : $(BUILDDIR)/gtest-all.o $(BUILDDIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


test.cpp:
	$(CXX) -std=c++11 -g -Wall test.cpp && ./a.out