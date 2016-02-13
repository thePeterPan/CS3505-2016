### Makefile

# CXX = g++
.PHONY: clean_local local travis_ci
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



local : $(LOCAL_BUILDDIR) $(LOCAL_EXECUTABLE)

$(LOCAL_BUILDDIR) :
	mkdir -p $@

$(LOCAL_EXECUTABLE) : $(LOCAL_BUILDDIR)/test.o $(LOCAL_BUILDDIR)/gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ Students.o -o $@

$(LOCAL_BUILDDIR)/test.o : StudentsTest.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 


### GTEST
# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$(LOCAL_BUILDDIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(LOCAL_GTEST_DIR) $(CXXFLAGS) -c \
            $(LOCAL_GTEST_DIR)/src/gtest-all.cc \
            -o $@

$(LOCAL_BUILDDIR)/gtest_main.o : $(GTEST_SRCS_)
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

test.cpp:
	$(CXX) -std=c++11 -g -Wall test.cpp && ./a.out