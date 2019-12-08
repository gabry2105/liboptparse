#include <string>
#include "liboptparse/optargs.hh"
#include "liboptparse/program_info.hh"
#include "liboptparse/utils.hh"

bool _LIBOPTPARSE_::is_valid_short_name(char short_name) {
    return std::isalpha(short_name);
}

bool _LIBOPTPARSE_::is_valid_long_name(const std::string& long_name) {
    bool ok = long_name.empty() ||
        (long_name.size() > 2 && std::isalpha(long_name[0]));
    for (auto itr = long_name.cbegin();
         itr != long_name.cend() && ok;
         ++itr) {
        ok = ok && std::isalpha(*itr);
    }
    return ok;
} 

bool _LIBOPTPARSE_::is_valid_opt_arg(
    const OptionArgument& option_argument) {
    return
        _LIBOPTPARSE_::is_valid_short_name(
            option_argument.get_short_name()) &&
        _LIBOPTPARSE_::is_valid_long_name(
            option_argument.get_long_name());
}


bool _LIBOPTPARSE_::is_valid_program_info(
    const ProgramInfo& program_info) {
    return !program_info.program_name.empty();
}
