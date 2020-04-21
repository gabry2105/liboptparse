#include <list>
#include <memory>
#include "../src/liboptparse/plain_arguments.hh"
#include <CppUTest/TestHarness.h>


TEST_GROUP(PlainArguments) {
    void setup() { }
    void teardown() { }
};

/**
 * HAVE A new plain arguments container
 * WHEN check its size through iterators
 * THEN it is empty: begin and end iterators are equals.
 */
TEST(PlainArguments, Test_01) {
    PlainArguments<int> arguments;
    CHECK_TRUE(arguments.cbegin() == arguments.cend())
}

/**
 * HAVE A list of arguments
 * WHEN initialize the PlainArguments container with that list
 * THEN each element of the lsit to be put on the PlainArguments.
 */
TEST(PlainArguments, Test_02) {
    std::list<int> args_list { 1, 2, 3 };
    PlainArguments<int> arguments(args_list.begin(), args_list.end());
    auto itr = arguments.cbegin();
    int first = *itr;
    ++itr;
    int second = *itr;
    ++itr;
    int third = *itr;
    ++itr;
    CHECK_TRUE(first == 1);
    CHECK_TRUE(second == 2);
    CHECK_TRUE(third == 3);
    CHECK_TRUE(itr == arguments.cend());
}

/**
 * HAVE A initialize arguments object
 * WHEN create a new one from copy constructor
 * THEN each element of the first arguments object to be put on the
 *      second arguments object.
 */
TEST(PlainArguments, Test_03) {
    std::list<int> args_list { 1, 2, 3 };
    PlainArguments<int> arguments1(args_list.begin(),
                                   args_list.end());
    PlainArguments<int> arguments2(arguments1);
    auto itr = arguments2.cbegin();
    int first = *itr;
    ++itr;
    int second = *itr;
    ++itr;
    int third = *itr;
    ++itr;
    CHECK_TRUE(first == 1);
    CHECK_TRUE(second == 2);
    CHECK_TRUE(third == 3);
    CHECK_TRUE(itr == arguments2.cend());
}

/**
 * HAVE An initialized arguments object
 * WHEN move it to an other arguments object
 * THEN each element of the first arguments object to be put on the
 *      second arguments object.
 */
TEST(PlainArguments, Test_04) {
    std::list<int> args_list { 1, 2, 3 };
    PlainArguments<int> arguments1(args_list.begin(),
                                   args_list.end());
    PlainArguments<int> arguments2 = std::move(arguments1);
    auto itr = arguments2.cbegin();
    int first = *itr;
    ++itr;
    int second = *itr;
    ++itr;
    int third = *itr;
    ++itr;
    CHECK_TRUE(first == 1);
    CHECK_TRUE(second == 2);
    CHECK_TRUE(third == 3);
    CHECK_TRUE(itr == arguments2.cend());
}


/**
 * HAVE Two initialized arguments object
 * WHEN assing first one to second one
 * THEN each element of the first one is equals to each element
 *      of second one;
 */
TEST(PlainArguments, Test_05) {
    std::list<int> args_list1 { 1, 2 };
    std::list<int> args_list2 { 3, 4 };
    PlainArguments<int> arguments1(args_list1.begin(),
                                   args_list1.end());
    PlainArguments<int> arguments2(args_list2.begin(),
                                   args_list2.end());
    arguments2 = arguments1;
    auto itr1 = arguments1.cbegin();
    auto itr2 = arguments2.cbegin();
    CHECK_TRUE(*itr1 == *itr2);
    ++itr1;
    ++itr2;
    CHECK_TRUE(*itr1 == *itr2);
    ++itr1;
    ++itr2;
    CHECK_TRUE(*itr1 == *itr2);
    CHECK_TRUE(itr1 == arguments1.cend());
    CHECK_TRUE(itr2 == arguments2.cend());
}
