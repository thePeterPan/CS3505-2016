#include "Trie/Trie.h"
#include "gtest/gtest.h"

#include <iostream>     // std::cout, std::cin
#include <fstream>      // std::ifstream
#include <string>

// You should add to your test file an int variable called refCount in 
// global scope and initialize it to 0. The definition of the refCount
// variable. 
int refCount = 0;

// The fixture for testing class TrieUnitTests
class TrieUnitTests : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    Trie trie;
    Trie trie2;
    
    std::ifstream input;
    std::ifstream input2;
    std::ifstream input3;
    
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
        input.open("dictionary.txt");
        input2.open("test.txt");
        input3.open("queries.txt");
    }
    
    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
        input.close();
        input2.close();
    }
    
    // Objects declared here can be used by all tests in the test case for
    // TrieUnitTests.
};

/**
 * Test adding a single word.
 */
TEST_F(TrieUnitTests, AddWord) {
    trie.addWord("lorem");

    ASSERT_TRUE(trie.isWord("lorem"));    
}

/**
 * Make sure that the characters are converted to lowercase.
 */
TEST_F(TrieUnitTests, DISABLED_AddWordUppercase) {
    trie.addWord("LoRem");
    
    ASSERT_TRUE(trie.isWord("lorem"));
}

/**
 * 
 */
TEST_F(TrieUnitTests, AddWordWithNewline) {
    trie.addWord("lorem\n");
    
    ASSERT_TRUE(trie.isWord("lorem"));
}

/**
 * 
 */
TEST_F(TrieUnitTests, AddEmptyWord) {
    trie.addWord("");
    
    ASSERT_FALSE(trie.isWord("lorem"));
}

/**
 * 
 */
TEST_F(TrieUnitTests, AddWordSubwordIsNotWord) {
    trie.addWord("loremipsum");
    
    ASSERT_FALSE(trie.isWord("remi"));
}

/**
 * 
 */
TEST_F(TrieUnitTests, AddWordExtendedWord) {
    trie.addWord("lorem");
    
    ASSERT_FALSE(trie.isWord("loremipsum"));
}

/**
 * 
 */
TEST_F(TrieUnitTests, AddWordSmallWords) {
    char charArray[10] = {'a','b','c','d','e','f','g','h','i','k'};
    for (int i = 0; i < 10; i++) {
        std::string s(1, charArray[i]);
        trie.addWord(s);
    }
    
    for (int i = 0; i < 10; i++) {
        std::string s(1, charArray[i]);
        ASSERT_TRUE(trie.isWord(s));
    }
    
    ASSERT_FALSE(trie.isWord("lorem"));
}

/**
 * 
 */
TEST_F(TrieUnitTests, AddWordFromDictionaryFile) {
    for(std::string inputStr; !input.eof();) {
        input >> inputStr;
        trie.addWord(inputStr);
    }
    
    ASSERT_TRUE(trie.isWord("people"));
    ASSERT_TRUE(trie.isWord("internet"));
    ASSERT_FALSE(trie.isWord("rtdeds"));
    ASSERT_TRUE(trie.isWord("trust"));
}

/**
 * isWord should return false when checking an empty string.
 */
TEST_F(TrieUnitTests, IsWordEmpty) {
    ASSERT_FALSE(trie.isWord(""));
}

TEST_F(TrieUnitTests, IsWordNewline) {
    trie.addWord("lorem");
    
    ASSERT_TRUE(trie.isWord("lorem\n"));
}

/**
 * Test for checking the word that is not in the Trie.
 */
TEST_F(TrieUnitTests, IsWordIsNotAWord) {
    trie.addWord("cnm");
    
    ASSERT_FALSE(trie.isWord("c"));
}

/**
 * Test for the refCount for counting the nodes of test.txt which should 
 * has 25 chars at all.
 */
TEST_F(TrieUnitTests, DISABLED_CountNodesForDictionaryFile) {
    for (std::string inputStr; !input.eof();) {
        input >> inputStr;
        trie.addWord(inputStr);
    }
    
    ASSERT_EQ(10066, refCount);
}

TEST_F(TrieUnitTests, CountNodesForTestFile) {
    for (std::string inputStr; !input2.eof();) {
        input2 >> inputStr;
        trie.addWord(inputStr);
    }
    
    ASSERT_EQ(19, refCount);
}

TEST_F(TrieUnitTests, CountNodesForQueriesFile) {
    for (std::string inputStr; !input3.eof();) {
        input3 >> inputStr;
        trie.addWord(inputStr);
    }
    
    ASSERT_EQ(10, refCount);
}

/**
 * Test for adding a single word after adding amount of words.
 */
TEST_F(TrieUnitTests, Dummy2) {
    for (std::string inputStr; !input.eof();) {
        input >> inputStr;
        trie.addWord(inputStr);
    }

    for (std::string inputStr; !input2.eof();)
    {
        input2 >> inputStr;
        trie2.addWord(inputStr);
    }

    trie2.addWord("cnm");
    
    ASSERT_TRUE(trie2.isWord("cnm"));
}

/**
 * Count the number of words that have the specified prefix. 
 */
TEST_F(TrieUnitTests, AllWordWithPrefixCount) {
    for(std::string inputStr; !input.eof();) {
        input >> inputStr;
        trie.addWord(inputStr);
    }
    
    std::vector<std::string> v(trie.allWordsWithPrefix("pe"));

    ASSERT_EQ(16, v.size());
}

/**
 * Count the number of words that have the specified prefix. 
 */
TEST_F(TrieUnitTests, AllWordWithPrefixCountNewLine) {
    for(std::string inputStr; !input.eof();) {
        input >> inputStr;
        trie.addWord(inputStr);
    }
    
    std::vector<std::string> v(trie.allWordsWithPrefix("pe\n"));

    ASSERT_EQ(16, v.size());
}

/**
 * Count the number of words that have the specified prefix.
 */
TEST_F(TrieUnitTests, AllWordWithPrefixCountZero) {
    for(std::string inputStr; !input.eof();) {
        input >> inputStr;
        trie.addWord(inputStr);
    }
    
    std::vector<std::string> v = trie.allWordsWithPrefix("asdfghjkl");

    ASSERT_EQ(0, v.size());
}

/**
 * Count the number of words that have the specified prefix where the prefix
 * is the entire word.
 */
TEST_F(TrieUnitTests, AllWordWithPrefixCountWhole) {
    for(std::string inputStr; !input.eof();) {
        input >> inputStr;
        trie.addWord(inputStr);
    }
    std::vector<std::string> v = trie.allWordsWithPrefix("peace");

    ASSERT_EQ(1, v.size());
}

/**
 *  Test for making multiple tries for adding and checking word exists.
 */
TEST_F(TrieUnitTests, MultipleTrieObjects) {
    for(std::string inputStr; !input.eof();) {
        input >> inputStr;
        trie.addWord(inputStr);
    }
	
    for(std::string inputStr; !input2.eof();) {
        input2 >> inputStr;
        trie2.addWord(inputStr);
    }	
    
    std::vector<std::string> v(trie2.allWordsWithPrefix("map"));
    ASSERT_EQ(0, v.size());

    std::vector<std::string> v1(trie2.allWordsWithPrefix("map"));
    ASSERT_EQ(0, v1.size());

    ASSERT_FALSE(trie2.isWord("map"));

    std::vector<std::string> v3(trie2.allWordsWithPrefix("map"));
    ASSERT_EQ(0, v3.size());
}

/**
 * 
 */
TEST_F(TrieUnitTests, DISABLED_CountNodesBeingDeleted) {
    refCount = 0;
    for(std::string inputStr; !input.eof();)
    {
        input >> inputStr;
        trie.addWord(inputStr);
    }
    ASSERT_EQ(9189, refCount);

    refCount = 0;
	
    for(std::string inputStr; !input2.eof();)
    {
        input2 >> inputStr;
        trie2.addWord(inputStr);
    }
    ASSERT_EQ(25, refCount);

    trie2.~Trie();

    ASSERT_EQ(0, refCount);
}

// test for copy trie2 it should not have word map
TEST_F(TrieUnitTests, DISABLED_TrieCopyConstructor) {
    for(std::string inputStr; !input.eof();)
    {
        input >> inputStr;
        trie.addWord(inputStr);
    }
    for(std::string inputStr; !input2.eof();)
    {
        input2 >> inputStr;
        trie2.addWord(inputStr);
    }

    Trie trie3(trie);
    trie3 = trie2;

    std::vector<std::string> v = trie3.allWordsWithPrefix("map");

    ASSERT_EQ(0, v.size());
}
