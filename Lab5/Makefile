### Makefile

# CXX = g++
.PHONY: travis_ci test local local_test clean
.DEFAULT_GOAL := travis_ci

# Flags passed to the C++ compiler.
CXXFLAGS = -g -Wall -std=c++11 -Wextra
# Optimization flags
CXXFLAGS += -O0

### GTEST
# https://github.com/google/googletest/blob/master/googletest/make/Makefile
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
CXXFLAGS += -pthread



### TRAVIS BUILD
# I guess if LOCAL_BUILDDIR and TRAVIS_BUILDDIR are the same
# make will get confused.
TRAVIS_BUILDDIR = ./build
TRAVIS_EXECUTABLE = $(TRAVIS_BUILDDIR)/StudentsTest
# LIBRARY_PATH is given by the .travis.yml file
TRAVIS_LIB = $(LIBRARY_PATH)/libgtest_main.a \
			$(LIBRARY_PATH)/libgtest.a

travis_ci : $(TRAVIS_BUILDDIR) $(TRAVIS_EXECUTABLE)

$(TRAVIS_BUILDDIR) : 
	mkdir -p $@

$(TRAVIS_EXECUTABLE) : $(TRAVIS_BUILDDIR)/StudentsTest.o 
	$(CXX) $(CXXFLAGS) -lpthread $^ Students.o $(TRAVIS_LIB) -o $@

$(TRAVIS_BUILDDIR)/StudentsTest.o : StudentsTest.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

test : 
	$(TRAVIS_EXECUTABLE)




### MAIN LOCAL_EXECUTABLE
LOCAL_BUILDDIR = ./bin
LOCAL_EXECUTABLE = $(LOCAL_BUILDDIR)/StudentsTest

local : $(LOCAL_BUILDDIR) $(LOCAL_EXECUTABLE)

$(LOCAL_BUILDDIR) :
	mkdir -p $@

$(LOCAL_EXECUTABLE) : $(LOCAL_BUILDDIR)/StudentsTest.o $(LOCAL_BUILDDIR)/gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ Students.o -o $@

$(LOCAL_BUILDDIR)/StudentsTest.o : StudentsTest.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 

local_test:
	$(LOCAL_EXECUTABLE)

### GTEST
# https://github.com/google/googletest/blob/master/googletest/make/Makefile
# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$(LOCAL_BUILDDIR)/gtest-all.o : 
	$(CXX) $(CPPFLAGS) -I$(LOCAL_GTEST_DIR) $(CXXFLAGS) -c \
            $(LOCAL_GTEST_DIR)/src/gtest-all.cc \
            -o $@

$(LOCAL_BUILDDIR)/gtest_main.o : 
	$(CXX) $(CPPFLAGS) -I$(LOCAL_GTEST_DIR) $(CXXFLAGS) -c \
            $(LOCAL_GTEST_DIR)/src/gtest_main.cc \
            -o $@

$(LOCAL_BUILDDIR)/gtest.a : $(LOCAL_BUILDDIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(LOCAL_BUILDDIR)/gtest_main.a : $(LOCAL_BUILDDIR)/gtest-all.o $(LOCAL_BUILDDIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


clean : 
	rm -rf $(LOCAL_BUILDDIR)
	rm -rf $(TRAVIS_BUILDDIR)
