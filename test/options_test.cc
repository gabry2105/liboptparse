#include "../src/liboptparse/options.hh"
#include "../src/liboptparse/optargs.hh"
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
    Options::options_container container;
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
    Options::options_container container;
    Options::value_type opt_value(new OptionArgumentValue("42"));
    container['r'] = Options::value_type(opt_value);
    Options options(program_info,
                    container.cbegin(),
                    container.cend());
    CHECK_TRUE(options['r'] == opt_value);
}
