#include "../src/liboptparse/optargs.hh"
#include <string>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

TEST_GROUP(OptionArgumentValueTest) {
    void setup() { }
    void teardown() {
        mock().clear();
    }
};

/**
 * HAVE A valid boolean option value
 * WHEN assign to a boolean variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_01) {
    OptionArgumentValue value_true("true");
    OptionArgumentValue value_false("false");
    bool check_true = value_true;
    bool check_false = value_false;
    CHECK_EQUAL(true, check_true);
    CHECK_EQUAL(false, check_false);
}

/**
 * HAVE A valid int value
 * WHEN assign to a int variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_02) {
    OptionArgumentValue int_value("42");
    int check_int = int_value;
    CHECK_EQUAL(42, check_int);
}

/**
 * HAVE A valid short value
 * WHEN assign to a short variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_03) {
    OptionArgumentValue short_value("42");
    short check_short = short_value;
    CHECK_EQUAL(42, check_short);
}

/**
 * HAVE A valid unsigned int value
 * WEHN assign to a unsigned int variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_04) {
    OptionArgumentValue short_value("42");
    unsigned int check_unsigned = short_value;
    CHECK_EQUAL(42, check_unsigned);
}

/**
 * HAVE A valid long value
 * WHEN assign to a long variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_05) {
    OptionArgumentValue long_value("42");
    long check_long = long_value;
    CHECK_EQUAL(42, check_long);
}

/**
 * HAVE A valid unsigned short value
 * WHEN assign to a unsigned short variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_06) {
    OptionArgumentValue ushort_value("42");
    unsigned short check_ushort = ushort_value;
    CHECK_EQUAL(42, check_ushort);
}

/**
 * HAVE A valid unsigned long value
 * WHEN assign to a usigned long variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_07) {
    OptionArgumentValue ulong_value("42");
    unsigned long check_ulong = ulong_value;
    CHECK_EQUAL(42, check_ulong);
}

/**
 * HAVE A valid fload value
 * WHEN assign to a float variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_08) {
    OptionArgumentValue float_value("42.42f");
    float check_float = float_value;
    CHECK_EQUAL(42.42f, check_float);
}

/**
 * HAVE A valid double value
 * WHEN assign to a double variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_09) {
    OptionArgumentValue double_value("42.42");
    double check_double = double_value;
    CHECK_EQUAL(42.42, check_double);
}

/**
 * HAVE A string value
 * WHEN assign to a std::string
 * THEN variable is same of the get_value return value.
 */
TEST(OptionArgumentValueTest, Test_10) {
    OptionArgumentValue string_value("Life, universe and all things");
    std::string check_str = string_value;
    CHECK_EQUAL(check_str, "Life, universe and all things");
    CHECK_EQUAL(check_str, string_value.get_value());
}


TEST_GROUP(OptionArgumentTest) {
    void setup() { }
    void teardown() {
        mock().clear();
    }
};

/**
 * HAVE A option with short name specified
 * WHEN gets the short name
 * THEN same given to be returned.
 */
TEST(OptionArgumentTest, Test_01) {
    OptionArgument arg('a');
    CHECK_EQUAL('a', arg.get_short_name());
}

/**
 * HAVE A option with short and long name specified
 * WHEN get both names
 * THEN same given to be returned.
 */
TEST(OptionArgumentTest, Test_02) {
    OptionArgument arg('a', "answer");
    CHECK_EQUAL('a', arg.get_short_name());
    CHECK_EQUAL("answer", arg.get_long_name());
}

/**
 * HAVE A valid option
 * WHEN set the help message
 * THEN same message to have been returned by get_help.
 */
TEST(OptionArgumentTest, Test_03) {
    OptionArgument arg('a', "answer");
    arg.set_help("Life, universe and all things.");
    CHECK_EQUAL("Life, universe and all things.", arg.get_help());
}

/**
 * HAVE A valid option
 * WHEN set the default value
 * THEN same metavar to have been returned by get_default_value.
 */
TEST(OptionArgumentTest, Test_04) {
    OptionArgument arg('a', "answer");
    arg.set_default_value("42");
    CHECK_EQUAL("42", arg.get_default_value());
}

/**
 * HAVE A valid option
 * WHEN set the metavar
 * THEN same metavar to have been returned by get_metavar.
 */
TEST(OptionArgumentTest, Test_05) {
    OptionArgument arg('a', "answer");
    arg.set_metavar("ANSWER");
    CHECK_EQUAL("ANSWER", arg.get_metavar());
}

/**
 * HAVE A valid option
 * WHEN set the type
 * THEN same type to have been returned by get_type.
 */
TEST(OptionArgumentTest, Test_06) {
    OptionArgument arg('a', "answer");
    arg.set_type(OptionArgumentType::flag);
    CHECK_EQUAL(OptionArgumentType::flag, arg.get_type());
}

/**
 * HAVE A valid option
 * WHEN set values through chaining
 * THEN right values to have been set
 */
TEST(OptionArgumentTest, Test_07) {
    OptionArgument arg('a', "answer");
    arg.set_help("Life, universe and all things.")
        .set_default_value("42")
        .set_metavar("ANSWER");        
    CHECK_EQUAL("Life, universe and all things.", arg.get_help());
    CHECK_EQUAL("42", arg.get_default_value());
    CHECK_EQUAL("ANSWER", arg.get_metavar());
}
