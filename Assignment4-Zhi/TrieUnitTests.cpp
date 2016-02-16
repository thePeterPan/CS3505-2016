#include "Trie/Node.h"
#include "Trie/Trie.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <string>

// TEST(test_case_name, test_name) {
//  ... test body ...
// }

TEST(TrieUnitTests, Dummy) {
    Trie trie;
    trie.addWord("cnm");
    
	ASSERT_EQ(true, trie.isWord("cnm"));
}
TEST(TrieUnitTests, Dummy1) {
    Trie trie;
    trie.addWord("cnm");
    
	ASSERT_EQ(false, trie.isWord("c"));
}
TEST(TrieUnitTests, Dummy2) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
    
	ASSERT_EQ(true, trie.isWord("people"));
}
TEST(TrieUnitTests, Dummy3) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	vector<string> v = trie.allWordsWithPrefix("pe");
    
	ASSERT_EQ(16, v.size());
}




int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
