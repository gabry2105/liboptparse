#include <algorithm>
#include <cassert>

#include "liboptparse/options.hh"
#include "liboptparse/program_info.hh"
#include "liboptparse/utils.hh"

bool Options::Impl::OK() const noexcept {
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

bool Options::Impl::contains_option(char key) const noexcept {
    return _opts -> find(key) !=  _opts -> end();
}

Options::value_type Options::Impl::at(char key) const noexcept {
    return _opts -> at(key);
}


Options::options_const_iterator
Options::Impl::options_cbegin() const noexcept {
    return _opts -> cbegin();
}

Options::options_const_iterator
Options::Impl::options_cend() const noexcept {
    return _opts -> cend();
}

Options::arguments_const_iterator
Options::Impl::arguments_cbegin() const noexcept {
    return _args -> cbegin();
}

Options::arguments_const_iterator
Options::Impl::arguments_cend() const noexcept {
    return _args -> cend();
}

const std::string& Options::Impl::get_program_name() const noexcept {
    return _program_info -> program_name;
}

Options::~Options() { }

Options::value_type Options::at(char key) const noexcept {
    assert(_pimpl -> OK() && _pimpl -> contains_option(key));
    auto elem = _pimpl -> at(key);
    assert(_pimpl -> OK() && elem != NULL);
    return elem;
}

Options::value_type Options::operator[](char key) const noexcept {
    return at(key);
}

Options::options_const_iterator
Options::options_cbegin() const noexcept {
    assert(_pimpl -> OK());
    auto itr = _pimpl -> options_cbegin();
    assert(_pimpl -> OK());
    return itr;
}

Options::options_const_iterator
Options::options_cend() const noexcept {
    assert(_pimpl -> OK());
    auto itr = _pimpl -> options_cend();
    assert(_pimpl -> OK());
    return itr;
}

Options::arguments_const_iterator
Options::arguments_cbegin() const noexcept {
    assert(_pimpl -> OK());
    auto itr = _pimpl -> arguments_cbegin();
    assert(_pimpl -> OK());
    return itr;
}

Options::arguments_const_iterator
Options::arguments_cend() const noexcept {
    assert(_pimpl -> OK());
    auto itr = _pimpl -> arguments_cend();
    assert(_pimpl -> OK());
    return itr;
}

const std::string& Options::get_program_name() const noexcept {
    assert(_pimpl -> OK());
    return _pimpl -> get_program_name();
}
