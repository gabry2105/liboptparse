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


#include <cassert>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include "liboptparse/optargs.hh"
#include "liboptparse/program_info.hh"
#include "liboptparse/parser.hh"
#include "liboptparse/utils.hh"

namespace {
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

class OptionParser::Impl {
public:
    Impl()
        : _option_arguments(new OptionParser::container()),
          _program_info(new ProgramInfo()) { }

    explicit Impl(const ProgramInfo& program_info)
        : _option_arguments(new OptionParser::container()),
          _program_info(new ProgramInfo(program_info)) { }

    explicit Impl(const Impl& impl)
        : _option_arguments(new OptionParser::container(
                                impl._option_arguments -> begin(),
                                impl._option_arguments -> end())),
          _program_info(new ProgramInfo(*impl._program_info)) { }

    explicit Impl(Impl&& impl)
        : _option_arguments(impl._option_arguments.release()),
          _program_info(impl._program_info) {
    }

    OptionArgument& add(const OptionArgument& argument) {
        std::shared_ptr<OptionArgument> ptr(
            new OptionArgument(argument));
        _option_arguments -> push_back(ptr);
        return *ptr;
    }

    OptionArgument& add(char short_name) {
        std::shared_ptr<OptionArgument> ptr(
            new OptionArgument(short_name));
        _option_arguments -> push_back(ptr);
        return *ptr;
    }

    OptionArgument& add(char short_name,
                        const std::string& long_name) {
        std::shared_ptr<OptionArgument> ptr(new OptionArgument(
                                            short_name,
                                            long_name));
        _option_arguments -> push_back(ptr);
        return *ptr;
    }

    std::unique_ptr<const Options> parse(
        int argc, const char *argv[]) {
        Options::options_container opts_values;
        Options::arguments_container args_values;
        std::map<char, const OptionArgument*> arguments;
        std::map<std::string, char> opt_mapping;
        std::list<Token> tokens;
        for(auto option_arg : *_option_arguments) {
            arguments[option_arg -> get_short_name()] =
                option_arg.get();
            opt_mapping[option_arg -> get_long_name()] =
                option_arg -> get_short_name();
            opts_values[option_arg -> get_short_name()] =
                Options::value_type(
                    new OptionArgumentValue(
                        option_arg -> get_default_value()));
        }    
        tokenize(argc, argv, std::back_inserter(tokens));
        evaluate(tokens.begin(),
                 tokens.end(),
                 *_program_info,
                 arguments,
                 opt_mapping,
                 opts_values,
                 std::back_inserter(args_values));
        return std::unique_ptr<const Options>(
            new Options(
                *_program_info,
                opts_values.cbegin(),
                opts_values.cend(),
                args_values.cbegin(),
                args_values.cend()));
    }

    OptionParser::const_iterator cbegin() {
        return _option_arguments -> cbegin();
    }

    OptionParser::const_iterator cend() {
        return _option_arguments -> cend();
    }

    /*!
     * Assertion method used to check if this parser is valid or not.
     * \return True if this parser is valid, false otherwise.
     */
    bool OK() const noexcept {    
        for (auto& opt_arg : *_option_arguments) {
            _LIBOPTPARSE_::is_valid_opt_arg(*opt_arg);
        }
        return true;
    }

private:
    
    /*! Pointer to the option argument list. */
    std::unique_ptr<container>   _option_arguments;

    /*! Pointer to the program informations.  */
    std::shared_ptr<ProgramInfo> _program_info;

};


OptionParser::OptionParser()
    : _pimpl(new Impl())  { }

OptionParser::OptionParser(const ProgramInfo& program_info)
    : _pimpl(new Impl(program_info)) { }

OptionParser::OptionParser(const OptionParser& option_parser)
    : _pimpl(new Impl(*option_parser._pimpl)) { }

OptionParser::OptionParser(OptionParser&& option_parser)
    : _pimpl(std::move(option_parser._pimpl)) { }

OptionParser::~OptionParser() { }

OptionArgument& OptionParser::add(const OptionArgument& argument) {
    assert(_pimpl -> OK() && _LIBOPTPARSE_::is_valid_opt_arg(argument));
    OptionArgument& added = _pimpl -> add(argument);
    assert(_pimpl -> OK() &&
           _LIBOPTPARSE_::is_valid_opt_arg(added) &&
           added == argument);
    return added;
}

OptionArgument& OptionParser::add(char short_name) {
    assert(_pimpl -> OK() &&
           _LIBOPTPARSE_::is_valid_short_name(short_name));
    OptionArgument& added = _pimpl -> add(short_name);
    assert(_pimpl -> OK() &&
           _LIBOPTPARSE_::is_valid_opt_arg(added) &&
           added.get_short_name() == short_name);
    return added;
}

OptionArgument& OptionParser::add(char short_name,
                                  const std::string& long_name) {
    assert(_pimpl -> OK() &&
           _LIBOPTPARSE_::is_valid_short_name(short_name) &&
           _LIBOPTPARSE_::is_valid_long_name(long_name));
    OptionArgument& added = _pimpl -> add(short_name, long_name);
    assert(_pimpl -> OK() &&
           _LIBOPTPARSE_::is_valid_opt_arg(added) &&
           added.get_short_name() == short_name &&
           added.get_long_name() == long_name);    
    return added;
}

OptionParser::const_iterator OptionParser::cbegin() {
    assert(_pimpl -> OK());
    auto itr = _pimpl -> cbegin();
    assert(_pimpl -> OK());
    return itr;
}

OptionParser::const_iterator OptionParser::cend() {
    assert(_pimpl -> OK());
    auto itr = _pimpl -> cend();
    assert(_pimpl -> OK());
    return itr;
}


std::unique_ptr<const Options> OptionParser::parse(
    int argc, const char *argv[]) {
    assert(_pimpl -> OK());
    std::unique_ptr<const Options> options =
        _pimpl -> parse(argc, argv);
    assert(_pimpl -> OK());
    return options;
}
