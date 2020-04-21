TESTS = optparse_test
LDADD = -lCppUTest -lCppUTestExt
check_PROGRAMS = optparse_test
optparse_test_CXXFLAGS =  -W -Wall -std=c++17 --coverage

optparse_test_SOURCES = \
	cpputest_main.cc \
	optargs_test.cc \
	options_test.cc \
	parser_test.cc \
	plain_arguments_test.cc \
	$(top_builddir)/src/liboptparse/types.hh \
	$(top_builddir)/src/liboptparse/optargs.hh \
	$(top_builddir)/src/liboptparse/options.hh \
	$(top_builddir)/src/liboptparse/options_priv.hpp \
	$(top_builddir)/src/liboptparse/parser.hh \
	$(top_builddir)/src/liboptparse/plain_arguments.hh \
	$(top_builddir)/src/liboptparse/plain_arguments_priv.hpp \
	$(top_builddir)/src/liboptparse/program_info.hh \
	$(top_builddir)/src/liboptparse/utils.hh \
	$(top_builddir)/src/optargs.cc \
	$(top_builddir)/src/options.cc \
	$(top_builddir)/src/parser.cc \
	$(top_builddir)/src/program_info.cc \
	$(top_builddir)/src/utils.cc
