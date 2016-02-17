#include "Trie/node.h"
#include "gtest/gtest.h"

#include <string>

// The fixture for testing class node
class NodeUnitTests : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    node rootNode;

    NodeUnitTests() 
        : rootNode('0') {
        // You can do set-up work for each test here.
    }

    virtual ~NodeUnitTests() {
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

TEST_F(NodeUnitTests, NodeDummy1) {
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    // parses the command line for Google Test flags, and removes all recognized flags
    ::testing::InitGoogleTest(&argc, argv);
    // Run all tests registered w/ gtest.    
    return RUN_ALL_TESTS();
}
