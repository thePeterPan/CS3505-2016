### Makefile

# CXX = g++
.PHONY: travis_ci clean local 
.DEFAULT_GOAL := travis_ci

# Flags passed to the C++ compiler.
OPTFLAGS = -O0
CXXFLAGS = -g -Wall -std=c++11 -Wextra -pthread $(OPTFLAGS)

### GTEST
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
LOCAL_GTEST_DIR = ./googletest/googletest
# All Google Test headers.  Usually you shouldn't change this
# definition.
LOCAL_GTEST_HEADERS = $(LOCAL_GTEST_DIR)/include/gtest/*.h \
                $(LOCAL_GTEST_DIR)/include/gtest/internal/*.h


# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(LOCAL_GTEST_DIR)/include


### MAIN LOCAL_EXECUTABLE
LOCAL_BUILDDIR = ./bin
LOCAL_EXECUTABLE = $(LOCAL_BUILDDIR)/test

TRAVIS_BUILDDIR = ./bin
TRAVIS_EXECUTABLE = $(TRAVIS_BUILDDIR)/test

TRAVIS_LIB = $(LIBRARY_PATH)/libgtest_main.a \
			$(LIBRARY_PATH)/libgtest.a

travis_ci : $(TRAVIS_BUILDDIR) $(TRAVIS_EXECUTABLE)

$(TRAVIS_BUILDDIR) : 
	mkdir -p $@

$(TRAVIS_EXECUTABLE) : $(TRAVIS_BUILDDIR)/test.o 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ Students.o $(TRAVIS_LIB) -o $@

$(TRAVIS_BUILDDIR)/test.o : StudentsTest.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 
