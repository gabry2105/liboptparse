lib_LTLIBRARIES = liboptparse.la
nobase_include_HEADERS = liboptparse/liboptparse.hh \
	liboptparse/optargs.hh \
	liboptparse/parser.hh \
	liboptparse/program_info.hh \
	liboptparse/utils.hh

# To include some lib, es libcurl:
# liboptparse_la_LIBADD = -lcurl

liboptparse_la_CXXFLAGS = -std=c++17

liboptparse_la_SOURCES = \
	liboptparse/liboptparse.hh \
	liboptparse/optargs.hh \
	optargs.cc \
	liboptparse/parser.hh \
	parser.cc \
	liboptparse/program_info.hh \
	program_info.cc \
	liboptparse/utils.hh \
	utils.cc
