### Makefile

# will use g++ if the environment variable is not set
CXX ?= g++

.PHONY: travis_ci test local local_test clean
.DEFAULT_GOAL := travis_ci

# Flags passed to the C++ compiler.
CXXFLAGS = -g -std=c++11 -Wextra
# Optimization flags
CXXFLAGS += -O0
# Possible flags that gtest may need
CXXFLAGS += -pthread



### ------------------------ TRAVIS BUILD -------------------------------------- ###

# I guess if LOCAL_BUILDDIR and TRAVIS_BUILDDIR are the same make will get confused.
TRAVIS_BUILDDIR = ./build
TRAVIS_SRC = ./Trie
TRAVIS_EXECUTABLE = $(TRAVIS_BUILDDIR)/TrieUnitTests
# LIBRARY_PATH is given by the .travis.yml file
# Order does matter here
TRAVIS_GTEST_LIB = \
	$(LIBRARY_PATH)/libgtest_main.a \
	$(LIBRARY_PATH)/libgtest.a
TRAVIS_TRIETEST_OBJS = \
	$(TRAVIS_BUILDDIR)/nodeUnitTests.o \
	$(TRAVIS_BUILDDIR)/TrieUnitTests.o \
	$(TRAVIS_BUILDDIR)/Trie.o \
	$(TRAVIS_BUILDDIR)/node.o

travis_ci : $(TRAVIS_BUILDDIR) $(TRAVIS_EXECUTABLE) travis_text_files

travis_text_files : 
	cp *.txt $(TRAVIS_BUILDDIR)

$(TRAVIS_BUILDDIR) :
	mkdir -p $@

$(TRAVIS_EXECUTABLE) : $(TRAVIS_TRIETEST_OBJS)
	$(CXX) $(CXXFLAGS) -lpthread $^ $(TRAVIS_GTEST_LIB) -o $@

# This does not need the GTEST_FLAGS like in the local version because
# I'm assuming that the gtest header files are already located in the
# system where g++ automatically looks for header files because gtest
# was 'installed' in the Travis CI system.
$(TRAVIS_BUILDDIR)/nodeUnitTests.o : nodeUnitTests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TRAVIS_BUILDDIR)/TrieUnitTests.o : TrieUnitTests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TRAVIS_BUILDDIR)/Trie.o : $(TRAVIS_SRC)/Trie.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TRAVIS_BUILDDIR)/node.o : $(TRAVIS_SRC)/node.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test : travis_ci
	$(TRAVIS_EXECUTABLE)



### --------------------- MAIN LOCAL_EXECUTABLE -------------------------------- ###

LOCAL_BUILDDIR = ./bin
LOCAL_SRC = ./Trie
LOCAL_EXECUTABLE = $(LOCAL_BUILDDIR)/TrieUnitTests
LOCAL_TRIETEST_OBJS = \
	$(LOCAL_BUILDDIR)/nodeUnitTests.o \
	$(LOCAL_BUILDDIR)/TrieUnitTests.o \
	$(LOCAL_BUILDDIR)/Trie.o \
	$(LOCAL_BUILDDIR)/node.o

# Apparently order matters here originally when I had
# two library files generated from running cmake && make
# in the googletest directory.
LOCAL_GTEST_LIB = \
	./googletest/gtest_main.a

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
GTEST_FLAGS += -isystem ./googletest/include

# Build and run it
local : $(LOCAL_BUILDDIR) $(LOCAL_EXECUTABLE) local_text_files

local_text_files : 
	cp *.txt $(LOCAL_BUILDDIR)

$(LOCAL_BUILDDIR) :
	mkdir -p $@

$(LOCAL_EXECUTABLE) : $(LOCAL_TRIETEST_OBJS) $(LOCAL_GTEST_LIB)
	$(CXX) $(CXXFLAGS) -lpthread $(GTEST_FLAGS) $^ -o $@

$(LOCAL_BUILDDIR)/nodeUnitTests.o : nodeUnitTests.cpp
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) -c $< -o $@

$(LOCAL_BUILDDIR)/TrieUnitTests.o : TrieUnitTests.cpp
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) -c $< -o $@

$(LOCAL_BUILDDIR)/Trie.o : $(LOCAL_SRC)/Trie.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LOCAL_BUILDDIR)/node.o : $(LOCAL_SRC)/node.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean :
	rm -rf $(LOCAL_BUILDDIR)
	rm -rf $(TRAVIS_BUILDDIR)
