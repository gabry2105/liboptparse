#include "../src/liboptparse/optargs.hh"
#include <string>
#include <sstream>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

TEST_GROUP(OptionArgumentValueTest) {
    void setup() { }
    void teardown() {
        mock().clear();
    }
};

/**
 * HAVE A new OptionArgumentValue created without
 *      parameters
 * WHEN read the value
 * THEN its an empty string.
 */
TEST(OptionArgumentValueTest, Test_01) {
    OptionArgumentValue value;
    CHECK_EQUAL(value.get_value(), "");
}

/**
 * HAVE A new option argument value
 * WHEN create an other one from the first one (copy constructor)
 * THEN the second one has the same value of the first one.
 */
TEST(OptionArgumentValueTest, Test_02) {
    OptionArgumentValue value1("42");
    OptionArgumentValue value2(value1);
    CHECK_EQUAL(value1.get_value(), value2.get_value());
}

/**
 * HAVE An  OptionArgumentValue with a defined value
 * WHEN move it into an other option argument value
 * THEN the new argument value has the same value of the
 *      one inside the function.
 */
TEST(OptionArgumentValueTest, Test_03) {
    std::string value = "42";
    OptionArgumentValue value1(value);
    OptionArgumentValue value2(std::move(value1));
    CHECK_EQUAL(value2.get_value(), value);
}

/**
 * HAVE A valid boolean option value
 * WHEN assign to a boolean variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_04) {
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
TEST(OptionArgumentValueTest, Test_05) {
    OptionArgumentValue int_value("42");
    int check_int = int_value;
    CHECK_EQUAL(42, check_int);
}

/**
 * HAVE A valid short value
 * WHEN assign to a short variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_06) {
    OptionArgumentValue short_value("42");
    short check_short = short_value;
    CHECK_EQUAL(42, check_short);
}

/**
 * HAVE A valid unsigned int value
 * WEHN assign to a unsigned int variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_07) {
    OptionArgumentValue short_value("42");
    unsigned int check_unsigned = short_value;
    CHECK_EQUAL(42, check_unsigned);
}

/**
 * HAVE A valid long value
 * WHEN assign to a long variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_08) {
    OptionArgumentValue long_value("42");
    long check_long = long_value;
    CHECK_EQUAL(42, check_long);
}

/**
 * HAVE A valid unsigned short value
 * WHEN assign to a unsigned short variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_09) {
    OptionArgumentValue ushort_value("42");
    unsigned short check_ushort = ushort_value;
    CHECK_EQUAL(42, check_ushort);
}

/**
 * HAVE A valid unsigned long value
 * WHEN assign to a usigned long variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_10) {
    OptionArgumentValue ulong_value("42");
    unsigned long check_ulong = ulong_value;
    CHECK_EQUAL(42, check_ulong);
}

/**
 * HAVE A valid fload value
 * WHEN assign to a float variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_11) {
    OptionArgumentValue float_value("42.42f");
    float check_float = float_value;
    CHECK_EQUAL(42.42f, check_float);
}

/**
 * HAVE A valid double value
 * WHEN assign to a double variable
 * THEN variable has the right value.
 */
TEST(OptionArgumentValueTest, Test_12) {
    OptionArgumentValue double_value("42.42");
    double check_double = double_value;
    CHECK_EQUAL(42.42, check_double);
}

/**
 * HAVE A string value
 * WHEN assign to a std::string
 * THEN variable is same of the get_value return value.
 */
TEST(OptionArgumentValueTest, Test_13) {
    OptionArgumentValue string_value("Life, universe and all things");
    std::string check_str = string_value;
    CHECK_EQUAL(check_str, "Life, universe and all things");
    CHECK_EQUAL(check_str, string_value.get_value());
}

/**
 * HAVE Two arguments values with the same value
 * WHEN compare them by operator==
 * THEN true to be returned
 */
TEST(OptionArgumentValueTest, Test_14) {
    OptionArgumentValue string_value("Life, universe and all things");
    OptionArgumentValue value1(string_value);
    OptionArgumentValue value2(string_value);
    CHECK_EQUAL(value1 == value2, true);
}

/**
 * HAVE Two arguments values with differente  values
 * WHEN compare them by operator==
 * THEN false to be returned
 */
TEST(OptionArgumentValueTest, Test_15) {
    OptionArgumentValue string_value1(
        "Life, universe and all things");
    OptionArgumentValue string_value2("42");
    OptionArgumentValue value1(string_value1);
    OptionArgumentValue value2(string_value2);
    CHECK_EQUAL(value1 == value2, false);
}



/**
 * HAVE Two arguments values with the same value
 * WHEN compare them by operator!=
 * THEN false to be returned
 */
TEST(OptionArgumentValueTest, Test_16) {
    OptionArgumentValue string_value("Life, universe and all things");
    OptionArgumentValue value1(string_value);
    OptionArgumentValue value2(string_value);
    CHECK_EQUAL(value1 != value2, false);
}

/**
 * HAVE Two arguments values with differente  values
 * WHEN compare them by operator!=
 * THEN true to be returned
 */
TEST(OptionArgumentValueTest, Test_17) {
    OptionArgumentValue string_value1(
        "Life, universe and all things");
    OptionArgumentValue string_value2("42");
    OptionArgumentValue value1(string_value1);
    OptionArgumentValue value2(string_value2);
    CHECK_EQUAL(value1 != value2, true);
}


/**
 * HAVE An option argument value
 * WHEN put it inside an out stream
 * THEN internal value to be returned
 */
TEST(OptionArgumentValueTest, Test_18) {
    OptionArgumentValue value("42");
    std::stringstream os;
    os << value;
    CHECK_EQUAL(os.str(), value.get_value());
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

/**
 * HAVE A new option argument
 * WHEN get type
 * THEN OptionArgumentType::value to be returned.
 */
TEST(OptionArgumentTest, Test_08) {
    OptionArgument option_arg('a');
    CHECK_EQUAL(option_arg.get_type(), OptionArgumentType::value);
}

/**
 * HAVE A new option argument
 * WHEN move it to an other option argument
 * THEN internal status of the new option argument is the same
 *      of the moved one.
 */
TEST(OptionArgumentTest, Test_09) {
    char arg = 'a';
    OptionArgument option_arg1('a');
    OptionArgument option_arg2(std::move(option_arg1));
    CHECK_EQUAL(option_arg2.get_short_name(), arg);
}

/**
 * HAVE Two option arguments with different short name
 * WHEN compare theme through operator!=
 * THEN true to be returned.
 */
TEST(OptionArgumentTest, Test_10) {
    OptionArgument option_arg1('a');
    OptionArgument option_arg2('b');
    CHECK_EQUAL(option_arg1 != option_arg2, true);
}

/**
 * HAVE Two option arguments with same short name
 * WHEN compare theme through operator!=
 * THEN false to be returned.
 */
TEST(OptionArgumentTest, Test_11) {
    OptionArgument option_arg1('a');
    OptionArgument option_arg2('a');
    CHECK_EQUAL(option_arg1 != option_arg2, false);
}
