#include "../src/liboptparse/parser.hh"
#include "../src/liboptparse/optargs.hh"
#include "../src/liboptparse/program_info.hh"
#include <sstream>
#include <string>
#include <algorithm>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

TEST_GROUP(Options) {
    void setup() {
    }
    void teardown() {
        mock().clear();
    }
};


/**
 * HAVE A new option object from an existing map
 * WHEN gets a value from a key contained in the map
 * THEN righe object to be returned.
 */
TEST(Options, Test_01) {
    ProgramInfo program_info("program_info");
    Options::opts_container container;
    Options::value_type opt_value(new OptionArgumentValue("42"));
    container['r'] = Options::value_type(opt_value);
    Options options(program_info,
                    container.cbegin(),
                    container.cend());
    CHECK_TRUE(options.at('r') == opt_value);    
}

/**
 * HAVE A new option object from an existing map
 * WHEN gets a value from a key through [] operator overload
 * THEN right object to be returned.
 */
TEST(Options, Test_02) {
    ProgramInfo program_info("program_info");
    Options::opts_container container;
    Options::value_type opt_value(new OptionArgumentValue("42"));
    container['r'] = Options::value_type(opt_value);
    Options options(program_info,
                    container.cbegin(),
                    container.cend());
    CHECK_TRUE(options['r'] == opt_value);
}

TEST_GROUP(OptionParser) {
    void setup() { }
    void teardown() {
        mock().clear();
    }
};


/**
 * HAVE A new parser
 * WHEN add an argument inside it through a reference
 * THEN the arguments added to be equals of the one passed.
 */
TEST(OptionParser, Test_01) {
    OptionParser parser;
    OptionArgument arg('a');
    parser.add(arg);
    CHECK_TRUE(**parser.cbegin() == arg);
}

/**
 * HAVE A new parser
 * WHEN add an argument through a short name
 * THEN first element must have the same short name passed as
 *      parameter when added.
 */
TEST(OptionParser, Test_02) {
    OptionParser parser;
    parser.add('a');
    auto front = *parser.cbegin();
    CHECK_TRUE(front -> get_short_name() == 'a');
}

/**
 * HAVE A new parser
 * WHEN add an argument through a short name and a long name
 * THEN first element must have the same short and long  passed as
 *      parameters when added.
 */
TEST(OptionParser, Test_03) {
    OptionParser parser;
    parser.add('a', "answer");
    auto front = *parser.cbegin();
    CHECK_TRUE(front -> get_short_name()  == 'a');
    CHECK_TRUE(front -> get_long_name()  == "answer");
}

/**
 * HAVE A new parser with an option
 * WHEN parse argumnents
 * THEN That option to be true.
 */
TEST(OptionParser, Test_04) {
    OptionParser parser;
    parser.add('a' );
    const char *argv[] = { "program_name", "-a" };
    auto options = parser.parse(2, argv);
    bool answer = *(options -> at('a'));
    CHECK_TRUE(answer);
}

/**
 * HAVE A new parser with options
 * WHEN parse empty arguments
 * THEN option to be false
 */
TEST(OptionParser, Test_05) {
    OptionParser parser;
    parser.add('a' );
    const char *argv[] = { "program_name" };
    auto options = parser.parse(1, argv);
    bool answer = *(options -> at('a'));
    CHECK_FALSE(answer);
}

/**
 * HAVE A new parser with multiple options
 * WHEN parse arguments with single option in a row
 * THEN options are set to true
 */
TEST(OptionParser, Test_06) {
    OptionParser parser;
    parser.add('a');
    parser.add('r');
    parser.add('g');
    parser.add('h');
    const char *argv[] = { "program_name", "-argh" };
    auto options = parser.parse(2, argv);
    CHECK_TRUE((bool)(*options)['a']);
    CHECK_TRUE((bool)(*options)['r']);
    CHECK_TRUE((bool)(*options)['g']);
    CHECK_TRUE((bool)(*options)['h']);
}

/**
 * HAVE A new parser with an option with a default value
 * WHEN parse arguments without any option
 * THEN defualt to be returned.
 */
TEST(OptionParser, Test_07) {
    OptionParser parser;
    parser.add('r', "reply").set_default_value("42");
    const char *argv[] = { "program_name", "test" };
    auto options = parser.parse(2, argv);
    auto opt = (*options)['r'];
    CHECK_TRUE((std::string)(*opt)  == "42");
}

/**
 * HAVE A new parser with an option
 * WHEN parse arguments with that option in short version and a value
 *      specified
 * THEN value specified to returned.
 */
TEST(OptionParser, Test_08) {
    OptionParser parser;
    parser.add('r', "reply");
    const char *argv[] = { "program_name", "-r", "42" };
    auto options = parser.parse(3, argv);
    auto opt = (*options)['r'];
    CHECK_TRUE((std::string)(*opt) == "42");
}

/**
 * HAVE A new parser with an option
 * WHEN parse arguments with long option specified by space
 * THEN value passed to returned.
 */
TEST(OptionParser, Test_09) {
    OptionParser parser;
    parser.add('r', "reply");
    const char *argv[] = { "program_name", "--reply", "42" };
    auto options = parser.parse(3, argv);
    auto opt = (*options)['r'];
    CHECK_TRUE((std::string)(*opt) == "42");
}

/**
 * HAVE A new parser with an option
 * WHEN parse arguments with long option specified by equal
 * THEN value passed to returned.
 */
TEST(OptionParser, Test_10) {
    OptionParser parser;
    parser.add('r', "reply");
    const char *argv[] = { "program_name", "--reply=42" };
    auto options = parser.parse(2, argv);
    auto opt = options -> at('r');
    CHECK_TRUE((std::string)(*opt) == "42");
}

/**
 * HAVE A new parser with an option set as flag
 * WHEN parse arguments with that option in short format
 * THEN true to be returned.
 */
TEST(OptionParser, Test_11) {
    OptionParser parser;
    parser.add('r', "reply").set_type(OptionArgumentType::flag);
    const char *argv[] = { "program_name", "-r", "ciao"};
    auto options = parser.parse(3, argv);
    auto opt = options -> at('r');
    CHECK_TRUE((bool)*opt);
}

/**
 * HAVE A new parser with an option set as flag
 * WHEN parse arguments with that option in long format
 * THEN true to be returned.
 */
TEST(OptionParser, Test_12) {
    OptionParser parser;
    parser.add('r', "reply").set_type(OptionArgumentType::flag);
    const char *argv[] = { "program_name", "--reply", "ciao"};
    auto options = parser.parse(3, argv);
    auto opt = options -> at('r');
    CHECK_TRUE((bool)*opt);
}

/**
 * HAVE A new parser with an option flag set
 * WHEN parse arguments with the option in short format and some other
 *      arguments
 * THEN there is one argument in the parsing result.
 */
TEST(OptionParser, Test_13) {
    OptionParser parser;
    parser.add('r', "reply").set_type(OptionArgumentType::flag);
    const char *argv[] = { "program_name", "-r", "42" };
    auto options = parser.parse(3, argv);
    int args_size = std::count_if(
        options -> args_cbegin(),
        options -> args_cend(),
        [](auto elem) { return elem == elem; });
    CHECK_EQUAL(1, args_size);
}

/**
 * HAVE A new parser with an option flag set
 * WHEN parse arguments with the option in short format and some other
 *      arguments
 * THEN the argument is equals to the one in the parsing result.
 */
TEST(OptionParser, Test_14) {
    OptionParser parser;
    parser.add('r', "reply").set_type(OptionArgumentType::flag);
    const char *argv[] = { "program_name", "-r", "42" };
    auto options = parser.parse(3, argv);
    auto first = *(options -> args_cbegin());
    CHECK_EQUAL((std::string)(*first), "42")
}

/**
 * HAVE A new parser with some options
 * WHEN get the program name from parser
 * THEN the right name to be returned.
 */
TEST(OptionParser, Test_15) {
    OptionParser parser;
    parser.add('r', "reply").set_type(OptionArgumentType::flag);
    const char *argv[] = { "program_name", "-r", "42" };
    auto options = parser.parse(3, argv);
    CHECK_EQUAL(options -> get_program_name(), "program_name");
}

/**
 * HAVE A new parser with a program name specified
 * WHEN get the program name
 * THEN the name passed to the parser to be returned.
 */
TEST(OptionParser, Test_16) {
    ProgramInfo program_info("program");
    OptionParser parser(program_info);
    parser.add('r', "reply").set_type(OptionArgumentType::flag);
    const char *argv[] = { "program_name", "-r", "42" };
    auto options = parser.parse(3, argv);
    CHECK_EQUAL(options -> get_program_name(), "program");
}
