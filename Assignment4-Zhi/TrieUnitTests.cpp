#include "Trie/Node.h"
#include "Trie/Trie.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <string>

// TEST(test_case_name, test_name) {
//  ... test body ...
// }
int refCount = 0;
// test for the refcount for counting the nodes of test.txt which should has 25 chars at all
TEST(TrieUnitTests, Dummy1) {
    refCount = 0;
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	 refCount = 0;
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();

	ASSERT_EQ(25, refCount);
}

// test for adding a single word after adding amount of words 
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
	
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	
	 trie2.addWord("cnm");
    
	ASSERT_TRUE(trie2.isWord("cnm"));
}
// test for adding a single word.
TEST(TrieUnitTests, Dummy3) {
    Trie trie;
    trie.addWord("cnm");
    
	ASSERT_EQ(true, trie.isWord("cnm"));
}
// test for checking the word that is not in the Trie
TEST(TrieUnitTests, Dummy4) {
    Trie trie;
    trie.addWord("cnm");
    
	ASSERT_EQ(false, trie.isWord("c"));
}
// test for checking a word should in trie after adding a mount of words
TEST(TrieUnitTests, Dummy5) {
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
// test for checking all the perfix for the word pe, it should be 16 elements in it.
TEST(TrieUnitTests, Dummy6) {
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
//test for checking a word that is not in the trie with reading and adding from a file
TEST(TrieUnitTests, Dummy7) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	vector<string> v = trie.allWordsWithPrefix("asdfghjkl");
    
	ASSERT_EQ(0, v.size());
}
//test for checking a word that is  in the trie with reading and adding from a file
TEST(TrieUnitTests, Dummy8) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	vector<string> v = trie.allWordsWithPrefix("peace");
    
	ASSERT_EQ(1, v.size());
}

// test for making different tries for adding and checking word exists
TEST(TrieUnitTests, Dummy9) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	
	
	vector<string> v = trie2.allWordsWithPrefix("map");
    
	ASSERT_EQ(0, v.size());
	
	vector<string> v1 = trie2.allWordsWithPrefix("map");
	ASSERT_EQ(0, v1.size());
	
	ASSERT_EQ(false, trie2.isWord("map"));
	
	vector<string> v3 = trie2.allWordsWithPrefix("map");
	ASSERT_EQ(0, v3.size());
	
	
	
	
}
//counting nodes from dictionary and test 2 files 
TEST(TrieUnitTests, Dummy10) {
refCount = 0;
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	ASSERT_EQ(9214, refCount);
}


//test for counting deleting nodes
TEST(TrieUnitTests, Dummy11) {
refCount = 0;
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	ASSERT_EQ(9189, refCount);
	
	
	refCount = 0;
	
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	ASSERT_EQ(25, refCount);
	 
	 trie2.~Trie();
	
    
	ASSERT_EQ(0, refCount);
}


// test for copy trie2 it should not have word map
TEST(TrieUnitTests, DISABLED_Dummy12) {
    Trie trie;
    ifstream input("dictionary.txt");
    for(string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	
	 Trie trie2;
	ifstream input2("test.txt");
    for(string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	
	Trie trie3(trie);
	
	trie3=trie2;
	
	vector<string> v = trie3.allWordsWithPrefix("map");
    
	ASSERT_EQ(0, v.size());
}















int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
