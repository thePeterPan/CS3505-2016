#include "Trie/Node.h"
#include "Trie/Trie.h"
#include "gtest/gtest.h"

#include <iostream>
#include <string>

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
