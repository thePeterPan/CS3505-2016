### Makefile

# CXX = g++
.PHONY: travis_ci test local local_test clean
.DEFAULT_GOAL := travis_ci

# Flags passed to the C++ compiler.
CXXFLAGS = -g -Wall -std=c++11 -Wextra
# Optimization flags
CXXFLAGS += -O0
# Possible flags that gtest may need
CXXFLAGS += -pthread



### ------------------------ TRAVIS BUILD-------------------------------------

# I guess if LOCAL_BUILDDIR and TRAVIS_BUILDDIR are the same
# make will get confused.
TRAVIS_BUILDDIR = ./build
TRAVIS_EXECUTABLE = $(TRAVIS_BUILDDIR)/TrieUnitTests
# LIBRARY_PATH is given by the .travis.yml file
TRAVIS_GTEST_LIB = \
	$(LIBRARY_PATH)/libgtest_main.a \
	$(LIBRARY_PATH)/libgtest.a
TRAVIS_TRIETEST_OBJS = \
	$(TRAVIS_BUILDDIR)/Trie.o \
	$(TRAVIS_BUILDDIR)/node.o

travis_ci : $(TRAVIS_BUILDDIR) $(TRAVIS_EXECUTABLE)

$(TRAVIS_BUILDDIR) : 
	mkdir -p $@

$(TRAVIS_EXECUTABLE) : $(TRAVIS_TRIETEST_OBJS)
	$(CXX) $(CXXFLAGS) -lpthread $^ $(TRAVIS_GTEST_LIB) -o $@

$(TRAVIS_BUILDDIR)/Trie.o : Trie.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(TRAVIS_BUILDDIR)/node.o : node.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

test : 
	$(TRAVIS_EXECUTABLE)




### --------------------- MAIN LOCAL_EXECUTABLE-------------------------------

LOCAL_BUILDDIR = ./bin
LOCAL_EXECUTABLE = $(LOCAL_BUILDDIR)/TrieUnitTests
LOCAL_TRIETEST_OBJS = \
	$(LOCAL_BUILDDIR)/Trie.o \
	$(LOCAL_BUILDDIR)/node.o

# Apparently order matters here
LOCAL_GTEST_LIB = 
#	./gtest/gtest_main.a
#	./gtest/libgtest_main.a	\
#	./gtest/libgtest.a

GTEST_DIR = ./googletest/googletest

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


$(LOCAL_BUILDDIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc \
            -o $@

$(LOCAL_BUILDDIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc \
            -o $@

$(LOCAL_BUILDDIR)/gtest.a : $(LOCAL_BUILDDIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(LOCAL_BUILDDIR)/gtest_main.a : $(LOCAL_BUILDDIR)/gtest-all.o $(LOCAL_BUILDDIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^



# Build and run it
local : $(LOCAL_BUILDDIR) $(LOCAL_EXECUTABLE)

$(LOCAL_BUILDDIR) :
	mkdir -p $@

$(LOCAL_EXECUTABLE) : $(LOCAL_BUILDDIR)/TrieUnitTests.o $(LOCAL_TRIETEST_OBJS) $(LOCAL_BUILDDIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
## 	$(CXX) $(CXXFLAGS) -lpthread $^ $(LOCAL_GTEST_LIB) -lgtest -o $@

$(LOCAL_BUILDDIR)/TrieUnitTests.o : TrieUnitTests.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LOCAL_BUILDDIR)/Trie.o : Trie.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LOCAL_BUILDDIR)/node.o : node.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


clean : 
	rm -rf $(LOCAL_BUILDDIR)
	rm -rf $(TRAVIS_BUILDDIR)
