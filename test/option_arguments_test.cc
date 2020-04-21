#include <memory>
#include <utility>
#include <map>
#include "../src/liboptparse/option_arguments.hh"
#include <CppUTest/TestHarness.h>

typedef OptionArguments<int, int> TestOptionArguments;

TEST_GROUP(OptionArguments) {
    void setup() { }
    void teardown() { }
};

/**
 * HAVE A new option arguments object
 * WHEN check its size
 * THEN to be zero: begin iterator is equals to end iterator.
 */
TEST(OptionArguments, Test_01) {
    TestOptionArguments option_arguments;
    CHECK_TRUE(option_arguments.cbegin() == option_arguments.cend());
}

/**
 * HAVE A list of option arguments 
 * WHEN iniitialize the OptionArguments object with that list
 * THEN options to be added to the OptionArguments object.
 */
TEST(OptionArguments, Test_02) {
    auto pair1 = std::pair<const int, int>(0, 42);
    auto pair2 = std::pair<const int, int>(1, 42); 
    std::map<int, int> pairs { pair1, pair2 };
    TestOptionArguments option_arguments(pairs.begin(), pairs.end());
    auto itr = option_arguments.cbegin();
    auto first = *itr;
    ++itr;
    auto second = *itr;
    ++itr;
    CHECK_TRUE(first == pair1 );
    CHECK_TRUE(second == pair2 );
    CHECK_TRUE(itr == option_arguments.cend());
}

/**
 * HAVE An initialized option arguments object
 * WHEN create an other option arguments object through copy
 *      constructor
 * THEN the second object has the same elements of the first one.
 */
TEST(OptionArguments, Test_03) {
    auto pair1 = std::pair<const int, int>(0, 42);
    auto pair2 = std::pair<const int, int>(1, 42); 
    std::map<int, int> pairs { pair1, pair2 };
    TestOptionArguments option_arguments1(pairs.begin(), pairs.end());
    TestOptionArguments option_arguments2(option_arguments1);
    auto itr1 = option_arguments1.cbegin();
    auto itr2 = option_arguments2.cbegin();
    auto first1 = *itr1;
    auto first2 = *itr2;
    ++itr1;
    ++itr2;
    auto second1 = *itr1;
    auto second2 = *itr2;
    ++itr1;
    ++itr2;
    CHECK_TRUE(first1 == first2 );
    CHECK_TRUE(second1 == second2 );
    CHECK_TRUE(itr1 == option_arguments1.cend());
    CHECK_TRUE(itr2 == option_arguments2.cend());
}

/**
 * HAVE An initialized option arguments 
 * WHEN move it to an other option arguments
 * THEN new one contains elements of the moved one.
 */
TEST(OptionArguments, Test_04) {
    auto pair1 = std::pair<const int, int>(0, 42);
    auto pair2 = std::pair<const int, int>(1, 42); 
    std::map<int, int> pairs { pair1, pair2 };
    TestOptionArguments option_arguments1(pairs.begin(), pairs.end());
    TestOptionArguments option_arguments2(
        std::move(option_arguments1));
    auto itr = option_arguments2.cbegin();
    auto first = *itr;
    ++itr;
    auto second = *itr;
    ++itr;
    CHECK_TRUE(first == pair1 );
    CHECK_TRUE(second == pair2 );
    CHECK_TRUE(itr == option_arguments2.cend());
}

/**
 * HAVE An initialized option arguments
 * WHEN assign it to an other option arguments
 * THEN second one contains each element of the first one.
 */
TEST(OptionArguments, Test_05) {
    auto pair1 = std::pair<const int, int>(0, 42);
    auto pair2 = std::pair<const int, int>(1, 42);
    auto pair3 = std::pair<const int, int>(2, 42);
    auto pair4 = std::pair<const int, int>(3, 42);
    std::map<int, int> pairs1 { pair1, pair2 };
    std::map<int, int> pairs2 { pair3, pair4 };
    TestOptionArguments option_arguments1(pairs1.begin(),
                                          pairs1.end());
    TestOptionArguments option_arguments2(pairs2.begin(),
                                          pairs2.end());
    option_arguments2 = option_arguments1;
    auto itr1 = option_arguments1.cbegin();
    auto itr2 = option_arguments2.cbegin();
    auto first1 = *itr1;
    auto first2 = *itr2;
    ++itr1;
    ++itr2;
    auto second1 = *itr1;
    auto second2 = *itr2;
    ++itr1;
    ++itr2;
    CHECK_TRUE(first1 == first2 );
    CHECK_TRUE(second1 == second2 );
    CHECK_TRUE(itr1 == option_arguments1.cend());
    CHECK_TRUE(itr2 == option_arguments2.cend());    
}

/**
 * HAVE An initialized option arguments
 * WHEN gets an element by key
 * THEN right element to be returned
 */
TEST(OptionArguments, Test_06) {
    auto pair1 = std::pair<const int, int>(0, 42);
    auto pair2 = std::pair<const int, int>(1, 45);
    std::map<int, int> pairs { pair1, pair2 };
    TestOptionArguments option_arguments(pairs.begin(), pairs.end());
    auto first = option_arguments.at(0);
    auto second = option_arguments.at(1);
    CHECK_TRUE(first == 42);
    CHECK_TRUE(second == 45);
    CHECK_TRUE(first = option_arguments[0]);
    CHECK_TRUE(second = option_arguments[1]);
}

/**
 * HAVE An initialized option arguments
 * WHEN check a key containment
 * THEN true to be returned only if the key is inside the collection.
 */
TEST(OptionArguments, Test_07) {
    auto pair1 = std::pair<const int, int>(0, 42);
    auto pair2 = std::pair<const int, int>(1, 45);
    std::map<int, int> pairs { pair1, pair2 };
    TestOptionArguments option_arguments(pairs.begin(), pairs.end());
    CHECK_TRUE(option_arguments.contains(0));
    CHECK_FALSE(option_arguments.contains(42));
}
