#include <algorithm>
#include <cassert>

#include "liboptparse/options.hh"
#include "liboptparse/program_info.hh"
#include "liboptparse/utils.hh"

Options::~Options() { }

Options::value_type Options::at(char key) const noexcept {
    assert(OK() && _opts -> find(key) != _opts -> end());
    auto elem = _opts -> at(key);
    assert(OK() && elem != NULL);
    return elem;
}

Options::value_type Options::operator[](char key) const noexcept {
    assert(OK() && _opts -> find(key) != _opts -> end());
    auto elem = at(key);
    assert(OK() && elem != NULL);
    return elem;
}


Options::opts_const_iterator Options::opts_cbegin() const noexcept {
    assert(OK());
    auto itr = _opts -> cbegin();
    assert(OK());
    return itr;
}

Options::opts_const_iterator Options::opts_cend() const noexcept {
    assert(OK());
    auto itr = _opts -> cend();
    assert(OK());
    return itr;
}

Options::args_const_iterator Options::args_cbegin() const noexcept {
    assert(OK());
    auto itr = _args -> cbegin();
    assert(OK());
    return itr;
}

Options::args_const_iterator Options::args_cend() const noexcept {
    assert(OK());
    auto itr = _args -> cend();
    assert(OK());
    return itr;
}

const std::string& Options::get_program_name() const noexcept {
    assert(OK());
    return _program_info -> program_name;
}

bool Options::OK() const noexcept{
    bool is_valid = _args != NULL &&
        _opts != NULL &&
        _program_info != NULL &&
        _LIBOPTPARSE_::is_valid_program_info(*_program_info);
    if (is_valid) {
        is_valid = std::all_of(
            _opts -> begin(),
            _opts -> end(),
            [&](auto opt) { return opt.second != NULL;  });
        is_valid = is_valid &&
            std::all_of(
                _args -> begin(),
                _args -> end(),
                [&](auto arg) { return arg != NULL;  });
    }
    return is_valid;
}
