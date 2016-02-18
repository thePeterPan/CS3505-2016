#zhiwang
#u0761669

file=dictionary.txt
qfile=test.txt

TrieTest: 
	$(CXX) -g -std=c++11 -Wextra -o TrieUnitTests TrieUnitTests.cpp ./Trie/Trie.cpp ./Trie/Node.cpp \
	-pthread -lpthread $(LIBRARY_PATH)/libgtest_main.a $(LIBRARY_PATH)/libgtest.a 

test:
	./TrieUnitTests

local: 
	g++ -g -std=c++11 -Wextra -isystem ./googletest/include -pthread -lpthread \
	-o TrieUnitTests TrieUnitTests.cpp ./Trie/Trie.cpp ./Trie/Node.cpp \
	./googletest/gtest_main.a

clean: 
	$ rm *.o TrieUnitTests

