#include "Trie/node.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>       // std::vector
#include <algorithm>    // std::find

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

/**
 * Make sure that the constructor does not count as a node.
 */
TEST_F(NodeUnitTests, RefCount) {
    ASSERT_EQ(0, refCount);
}

TEST_F(NodeUnitTests, RefCountMultiple) {
    rootNode.addChildNode('a');
    
    ASSERT_EQ(1, refCount);
    
    rootNode.addChildNode('b');
    
    ASSERT_EQ(2, refCount);
    
    rootNode.addChildNode('c');
    rootNode.addChildNode('d');
    rootNode.addChildNode('f');
    rootNode.addChildNode('g');
    rootNode.addChildNode('z');
    
    ASSERT_EQ(7, refCount);
}

TEST_F(NodeUnitTests, RefCountDuplicates) {
    rootNode.addChildNode('a');
    
    ASSERT_EQ(1, refCount);
    
    rootNode.addChildNode('a');
    
    ASSERT_EQ(1, refCount);
}

TEST_F(NodeUnitTests, RefCountSubNodes) {
    rootNode.addChildNode('a');
    
    node* secondLevelNode = rootNode.getChildNode('a');
    
    secondLevelNode->addChildNode('a');
    secondLevelNode->addChildNode('b');
    secondLevelNode->addChildNode('b'); // duplicate
    secondLevelNode->addChildNode('c');
    secondLevelNode->addChildNode('d');
    
    ASSERT_EQ(5, refCount);
}

TEST_F(NodeUnitTests, DISABLED_RefCountDestructor) {
    char charArray[10] = {'a','b','c','d','e','f','g','h','i','k'};    
    for (int i = 0; i < 10; ++i) {
        rootNode.addChildNode(charArray[i]);
    }
    
    ASSERT_EQ(10, refCount);
    
    // Pretty sure this is not the right way to test this.
    rootNode.~node();
    
    ASSERT_EQ(0, refCount);
}

TEST_F(NodeUnitTests, DISABLED_RefCountCopyConstructor) {
    char charArray[10] = {'a','b','c','d','e','f','g','h','i','k'};    
    for (int i = 0; i < 10; ++i) {
        rootNode.addChildNode(charArray[i]);
    }
    
    ASSERT_EQ(10, refCount);
    
    node duplicateNode(rootNode);
    
    ASSERT_EQ(20, refCount);
}

TEST_F(NodeUnitTests, DISABLED_RefCountAssignmentOperator) {
    char charArray[10] = {'a','b','c','d','e','f','g','h','i','k'};    
    for (int i = 0; i < 10; ++i) {
        rootNode.addChildNode(charArray[i]);
    }
    
    ASSERT_EQ(10, refCount);
    
    node duplicateNode('0');
    duplicateNode = rootNode;
    
    ASSERT_EQ(20, refCount);
}

TEST_F(NodeUnitTests, AddChildNodesOneChild) {
    rootNode.addChildNode('a');
    
    std::vector<char> childList(rootNode.getListOfChildren());
    
    ASSERT_EQ(1, childList.size());
    ASSERT_EQ('a', childList[0]);
}

TEST_F(NodeUnitTests, AddChildNodesCheckNodeValue) {
    rootNode.addChildNode('a');
    
    ASSERT_EQ('a', rootNode.getChildNode('a')->getValue());
    
    rootNode.addChildNode('b');
    
    ASSERT_EQ('b', rootNode.getChildNode('b')->getValue());
    
    rootNode.addChildNode('g');
    
    ASSERT_EQ('g', rootNode.getChildNode('g')->getValue());
    
    rootNode.addChildNode('z');
    
    ASSERT_EQ('z', rootNode.getChildNode('z')->getValue());
    
    rootNode.addChildNode('c');
    
    ASSERT_EQ('c', rootNode.getChildNode('c')->getValue());
    
}

TEST_F(NodeUnitTests, AddChildNodesMultipleChildren) {
    char charArray[10] = {'a','b','c','d','e','f','g','h','i','k'};    
    for (int i = 0; i < 10; ++i) {
        rootNode.addChildNode(charArray[i]);
    }
    
    std::vector<char> childList(rootNode.getListOfChildren());
    
    ASSERT_EQ(10, childList.size());
    
    for (int i = 0; i < 10; ++i) {
        ASSERT_TRUE(std::find(childList.begin(), childList.end(), charArray[i]) != childList.end());
        ASSERT_TRUE(rootNode.childNodeExists(charArray[i]));
    }
}

TEST_F(NodeUnitTests, AddChildNodesDuplicateChildren) {
    char charArray[10] = {'a','b','a','d','b','b','a','c','d','k'};
    for (int i = 0; i < 10; ++i) {
        rootNode.addChildNode(charArray[i]);
    }
    
    std::vector<char> childList(rootNode.getListOfChildren());
    
    ASSERT_EQ(5, childList.size());
    
    char charArrayNoDuplicates[5] = {'a','b','d','c','k'};
    for (int i = 0; i < 5; ++i) {
        ASSERT_TRUE(std::find(childList.begin(), childList.end(), charArrayNoDuplicates[i]) != childList.end());
        ASSERT_TRUE(rootNode.childNodeExists(charArrayNoDuplicates[i]));
    }
}

/**
 * I think the behavior should be to just quit, but I think this 
 * may also cause a seg fault, but we're testing it as such for 
 * now. 
 */
TEST_F(NodeUnitTests, AddChildNodesInvalidCharacter) { 
    rootNode.addChildNode('4');
    rootNode.addChildNode('A');
    rootNode.addChildNode('^');
    rootNode.addChildNode('.');
    rootNode.addChildNode('[');
    
    std::vector<char> childList(rootNode.getListOfChildren());
    
    ASSERT_EQ(0, childList.size());
}

TEST_F(NodeUnitTests, GetChildNodes) {
    rootNode.addChildNode('a');
    
    ASSERT_EQ('a', rootNode.getChildNode('a')->getValue());
}

TEST_F(NodeUnitTests, GetChildNodesInvalidCharacter) {
    char charArray[10] = {'a','b','c','d','e','f','g','h','i','k'};    
    for (int i = 0; i < 10; ++i) {
        rootNode.addChildNode(charArray[i]);
    }
    
    ASSERT_EQ(nullptr, rootNode.getChildNode(']'));
    ASSERT_EQ(nullptr, rootNode.getChildNode('4'));
    ASSERT_EQ(nullptr, rootNode.getChildNode('A'));
    ASSERT_EQ(nullptr, rootNode.getChildNode('^'));
    ASSERT_EQ(nullptr, rootNode.getChildNode('.'));
}

TEST_F(NodeUnitTests, ChildNodeExists) {
    rootNode.addChildNode('a');
    
    ASSERT_TRUE(rootNode.childNodeExists('a'));
}

TEST_F(NodeUnitTests, ChildNodeExistsDoesNotExist) {
    char charArray[10] = {'a','b','c','d','e','f','g','h','i','k'};    
    for (int i = 0; i < 10; ++i) {
        rootNode.addChildNode(charArray[i]);
    }
    
    ASSERT_FALSE(rootNode.childNodeExists('z'));
    ASSERT_FALSE(rootNode.childNodeExists('l'));
}

TEST_F(NodeUnitTests, ChildNodeExistsInvalidCharacter) {
    char charArray[10] = {'a','b','c','d','e','f','g','h','i','k'};    
    for (int i = 0; i < 10; ++i) {
        rootNode.addChildNode(charArray[i]);
    }
    
    ASSERT_FALSE(rootNode.childNodeExists(']'));
    ASSERT_FALSE(rootNode.childNodeExists('4'));
    ASSERT_FALSE(rootNode.childNodeExists('A'));
    ASSERT_FALSE(rootNode.childNodeExists('^'));
    ASSERT_FALSE(rootNode.childNodeExists('.'));
}

int main(int argc, char **argv) {
    // parses the command line for Google Test flags, and removes all recognized flags
    ::testing::InitGoogleTest(&argc, argv);
    // Run all tests registered w/ gtest.    
    return RUN_ALL_TESTS();
}
