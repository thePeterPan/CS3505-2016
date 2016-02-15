#zhiwang
#u0761669

file=dictionary.txt
qfile=test.txt

TrieTest: 
	$(CXX) -g -std=c++11 -Wextra -o TrieUnitTests TrieUnitTests.cpp Trie.cpp Node.cpp \
	-pthread -lpthread $(LIBRARY_PATH)/libgtest_main.a $(LIBRARY_PATH)/libgtest.a 
clean: 
	$ rm *.o TrieTest

test:
	./TrieUnitTests
