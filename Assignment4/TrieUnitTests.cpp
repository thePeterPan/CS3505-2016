#include "Trie/node.h"
#include "Trie/Trie.h"
#include "gtest/gtest.h"

#include <iostream>
#include <fstream>
#include <string>

// You should add to your test file an int variable called refCount in 
// global scope and initialize it to 0. The definition of the refCount
// variable. 
int refCount = 0;

// TEST(test_case_name, test_name) {
//  ... test body ...
// }

// The fixture for testing class TrieUnitTests
class TrieUnitTests : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    Trie trie;
    
    TrieUnitTests() {
        // You can do set-up work for each test here.
    }
    
    virtual ~TrieUnitTests() {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).       
        refCount = 0;        
    }
    
    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
        
    }
    
    // Objects declared here can be used by all tests in the test case for
    // TrieUnitTests.
};

/**
 * Test for adding a single word.
 */
TEST_F(TrieUnitTests, TestIsWord) {
    
    trie.addWord("cnm");

    ASSERT_TRUE(trie.isWord("cnm"));
    
    refCount = 3;
    std::cout << refCount << std::endl;
}

/**
 * Test for checking the word that is not in the Trie
 */
TEST_F(TrieUnitTests, TestIsWord2) {
    
    trie.addWord("cnm");
    
    ASSERT_FALSE(trie.isWord("c"));
    std::cout << refCount << std::endl;
}

/**
 * Test for the refCount for counting the nodes of test.txt which should 
 * has 25 chars at all.
 */
TEST_F(TrieUnitTests, Dummy1) {
    refCount = 0;
    Trie trie;
    std::ifstream input("dictionary.txt");
    for(std::string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	 refCount = 0;
	 Trie trie2;
	std::ifstream input2("test.txt");
    for(std::string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();

	ASSERT_EQ(25, refCount);
}

/**
 * Test for adding a single word after adding amount of words.
 */
TEST_F(TrieUnitTests, Dummy2) {
    Trie trie;
    std::ifstream input("dictionary.txt");
    for(std::string inputStr; !input.eof();)
	{
		input >> inputStr;
		trie.addWord(inputStr);
	}
	/* close the stream*/
	input.close();
	
	 Trie trie2;
	std::ifstream input2("test.txt");
    for(std::string inputStr; !input2.eof();)
	{
		input2 >> inputStr;
		trie2.addWord(inputStr);
	}
	/* close the stream*/
	input2.close();
	
	 trie2.addWord("cnm");
    
	ASSERT_TRUE(trie2.isWord("cnm"));
}

int main(int argc, char **argv) {
    // parses the command line for Google Test flags, and removes all recognized flags
    ::testing::InitGoogleTest(&argc, argv);
    // Run all tests registered w/ gtest.    
    return RUN_ALL_TESTS();
}
