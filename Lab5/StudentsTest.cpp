#include "Students.h"
#include "gtest/gtest.h"

#include <string>

using namespace std;

TEST(StudentsTest, AddANameAndID) {
    Students t;
    string n("David");
    t.addUser(n, 1);
    unsigned int id = t.idForName(n);
    ASSERT_EQ(1, id);
}
