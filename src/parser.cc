/* liboptparse is a library used to handle command line options.
 * Copyright (C) 2019 Guybrush aka Gabriele Labita
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include "liboptparse/optargs.hh"
#include "liboptparse/parser.hh"
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

bool operator==(const OptionArgumentValue& first,
                const OptionArgumentValue& second) {
    return first.get_value() == second.get_value();
}

bool operator!=(const OptionArgumentValue& first,
                const OptionArgumentValue& second) {
    return !(first == second);
}

std::ostream& operator<<(std::ostream& os,
                         const OptionArgumentValue& value) {
    os << value.get_value();
    return os;
}

OptionParser::OptionParser()
    : _option_arguments(new container()),
      _program_info(new ProgramInfo()) { }

OptionParser::OptionParser(const ProgramInfo& program_info)
    : _option_arguments(new container()),
      _program_info(new ProgramInfo(program_info)) { }

OptionParser::~OptionParser() { }

OptionArgument& OptionParser::add(const OptionArgument& argument) {
    assert(OK() && _LIBOPTPARSE_::is_valid_opt_arg(argument));
    std::shared_ptr<OptionArgument> ptr(new OptionArgument(argument));
    _option_arguments -> push_back(ptr);
    assert(OK() &&
           _LIBOPTPARSE_::is_valid_opt_arg(*ptr) &&
           *ptr == argument);
    return *ptr;
}

OptionArgument& OptionParser::add(char short_name) {
    assert(OK() && _LIBOPTPARSE_::is_valid_short_name(short_name));
    std::shared_ptr<OptionArgument> ptr(new OptionArgument(
                                            short_name));
    _option_arguments -> push_back(ptr);
    assert(OK() &&
           _LIBOPTPARSE_::is_valid_opt_arg(*ptr) &&
           ptr -> get_short_name() == short_name);
    return *ptr;
}

OptionArgument& OptionParser::add(char short_name,
                                  const std::string& long_name) {
    assert(OK() &&
           _LIBOPTPARSE_::is_valid_short_name(short_name) &&
           _LIBOPTPARSE_::is_valid_long_name(long_name));
    std::shared_ptr<OptionArgument> ptr(new OptionArgument(
                                            short_name,
                                            long_name));
    _option_arguments -> push_back(ptr);
    assert(OK() &&
           _LIBOPTPARSE_::is_valid_opt_arg(*ptr) &&
           ptr -> get_short_name() == short_name &&
           ptr -> get_long_name() == long_name);
    return *ptr;
}

OptionParser::const_iterator OptionParser::cbegin() {
    assert(OK());
    auto itr = _option_arguments -> cbegin();
    assert(OK());
    return itr;
}

OptionParser::const_iterator OptionParser::cend() {
    assert(OK());
    auto itr = _option_arguments -> cend();
    assert(OK());
    return itr;
}

bool OptionParser::OK() const noexcept {
    for (auto& opt_arg : *_option_arguments) {
        _LIBOPTPARSE_::is_valid_opt_arg(*opt_arg);
    }
    return true;
}

namespace __LIBOPTPARSE__ {
    const std::shared_ptr<OptionArgumentValue> TRUE(
        new OptionArgumentValue("true"));

    enum TokenType {
        MINUS,
        NAME
    };
    
    struct Token {
        TokenType   type;
        std::string value;

        explicit Token(TokenType token_type)
            : type(token_type) { }
        explicit Token(TokenType token_type,
                       const std::string& token_value)
            : type(token_type), value(token_value) { }
    };

    std::string build_name(const char buffer[], int& pos) {
         std::ostringstream ss;
         std::ostream_iterator<const char> out(ss);
         while(buffer[pos] != '\0' &&
               buffer[pos] != ' ' &&
               buffer[pos] != '=') {
             if(buffer[pos] == '\\') {
                 ++pos;
             }
             if (buffer[pos] != '\0') {
                 *out = buffer[pos];
                 ++pos;
             }
         }
         return ss.str();
    }

    template<class InserterIterator>
    void tokenize(int argc,
                  const char *argv[],
                  InserterIterator out) {
        for (int i = 0; i < argc; ++i) {
            int j = 0;
            char current = argv[i][j];
            while(current != '\0') {
                switch(current) {
                case '=':
                case ' ':
                    current = argv[i][++j];
                    break;
                case '-':
                    *out = Token(MINUS);
                    current = argv[i][++j];
                    break;
                default:
                    *out = Token(NAME, build_name(argv[i], j));
                    current = argv[i][j];
                }
            }
        }
    }

    template<class ForwardIterator>
    void parse_minus(ForwardIterator& itr, ForwardIterator end) {
        while(itr != end && itr -> type != MINUS) {
            ++itr;
        }
        ++itr;
    }

    template<class ForwardIterator>
    void parse_short_options(
        ForwardIterator& itr,
        ForwardIterator end,
        const std::map<char, const OptionArgument*>& opt_arg,
        std::map<char, Options::value_type>& values) {
        while(itr != end && itr -> type != NAME) {
            ++itr;
        }
        if (itr == end) {
            return;
        }
        auto opt_name = itr -> value;
        ++itr;
                
        if (opt_name.length() > 1) {
            for (auto& opt : opt_name) {
                values[opt] = TRUE;
            }
        } else {
            char short_name = opt_name[0];
            auto arg = opt_arg.at(short_name);
            if (arg-> get_type() == OptionArgumentType::flag) {
                values[short_name] = TRUE;
            } else if (itr != end && itr -> type == NAME) {
                values[short_name] = Options::value_type(
                    new OptionArgumentValue(itr -> value));
                ++itr;
            } else {
                values[short_name] = TRUE;
            }
        }
    }
    
    template<class ForwardIterator>
    void parse_long_option(
        ForwardIterator& itr,
        ForwardIterator end,
        const std::map<char, const OptionArgument*>& opt_arg,
        const std::map<std::string, char>& opt_mapping,
        std::map<char, Options::value_type>& values) {
        while(itr != end && itr -> type != NAME) {
            ++itr;
        }
        char short_name = opt_mapping.at(itr -> value);
                ++itr;
        if (itr != end && itr -> type == NAME) {
            auto arg = opt_arg.at(short_name);
            if(arg -> get_type() == OptionArgumentType::flag) {
                values[short_name] = TRUE;
            } else {
                values[short_name] = Options::value_type(
                    new OptionArgumentValue(itr -> value));
                ++itr;
            }
        }
    }
    
    template<class ForwardIterator, class ArgsInserterIterator>
    void evaluate(
        ForwardIterator begin,
        ForwardIterator end,
        ProgramInfo& program_info,
        const std::map<char, const OptionArgument*>& opt_arg,
        const std::map<std::string, char>& opt_mapping,
        std::map<char, Options::value_type>& values,
        ArgsInserterIterator args_inserter_iterator) {
        auto itr = begin;
        bool is_program_name = true;
        while(itr != end) {
            switch(itr -> type) {
            case MINUS:
                parse_minus(itr, end);
                if (itr -> type == MINUS) {
                    parse_long_option(
                        itr, end, opt_arg, opt_mapping, values);
                } else {
                    parse_short_options(itr, end, opt_arg, values);
                }
                break;
            case NAME:
                if (!is_program_name) {
                    args_inserter_iterator = Options::value_type(
                        new OptionArgumentValue(itr -> value));
                } else {
                    is_program_name = false;
                    if (program_info.program_name.empty()) {
                        program_info.program_name = itr -> value;
                    }
                }
                ++itr;
                break;
            }           
        }
    }
}

std::shared_ptr<const Options> OptionParser::parse(
    int argc, const char *argv[]) {
    assert(OK());
    Options::opts_container opts_values;
    Options::args_container args_values;
    std::map<char, const OptionArgument*> arguments;
    std::map<std::string, char> opt_mapping;
    std::list<__LIBOPTPARSE__::Token> tokens;
    for(auto option_arg : *_option_arguments) {
        arguments[option_arg -> get_short_name()] = option_arg.get();
        opt_mapping[option_arg -> get_long_name()] =
            option_arg -> get_short_name();
        opts_values[option_arg -> get_short_name()] =
            Options::value_type(
                new OptionArgumentValue(
                    option_arg -> get_default_value()));
    }    
    __LIBOPTPARSE__::tokenize(argc, argv, std::back_inserter(tokens));
    __LIBOPTPARSE__::evaluate(tokens.begin(),
                              tokens.end(),
                              *_program_info,
                              arguments,
                              opt_mapping,
                              opts_values,
                              std::back_inserter(args_values));
    std::shared_ptr<const Options> options(
        new Options(
            *_program_info,
            opts_values.cbegin(),
            opts_values.cend(),
            args_values.cbegin(),
            args_values.cend()));
    assert(OK());
    return options;
}
