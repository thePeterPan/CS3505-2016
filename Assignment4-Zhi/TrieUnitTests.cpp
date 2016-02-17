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

TEST(TrieUnitTests, Dummy4) {
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
	vector<string> v = trie.allWordsWithPrefix("peace");
    
	ASSERT_EQ(1, v.size());
}

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
	
	Trie trie3(trie);
	vector<string> v1 = trie3.allWordsWithPrefix("map");
	ASSERT_EQ(1, v1.size());
	
	trie3=trie2;
	//vector<string> v2 = trie3.allWordsWithPrefix("map");
	ASSERT_EQ(false, trie3.isWord("map"));
	
	trie3.~Trie();
	vector<string> v3 = trie3.allWordsWithPrefix("map");
	ASSERT_EQ(0, v3.size());
	
	
	
	
}
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
	vector<string> v = trie3.allWordsWithPrefix("map");
    
	ASSERT_EQ(1, v.size());
}


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
	
	Trie trie3(trie);
	
	//trie3=trie2;
	 
	 //trie3.~Trie();
	
	vector<string> v = trie2.allWordsWithPrefix("text");
    
	ASSERT_EQ(3, refCount);
}





TEST(TrieUnitTests, Dummy10) {
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
	
	//trie3=trie2;
	 
	 //trie3.~Trie();
	
	vector<string> v = trie3.allWordsWithPrefix("text");
    
	ASSERT_EQ(3, refCount);
}


TEST(TrieUnitTests, Dummy11) {
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
	
	//Trie trie3(trie);
	
	//trie3=trie2;
	 
	 //trie3.~Trie();
	
	 trie2.addWord("cnm");
    
	ASSERT_EQ(false, trie2.isWord("cnm"));
}





int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
