#include "Trie/node.h"
#include "Trie/Trie.h"
#include "gtest/gtest.h"

#include <iostream>
#include <string>

// You should add to your test file an int variable called refCount in 
// global scope and initialize it to 0. The definition of the refCount
// variable. 
int refCount = 0;

// TEST(test_case_name, test_name) {
//  ... test body ...
// }

TEST(TrieUnitTests, Dummy) {
	ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
