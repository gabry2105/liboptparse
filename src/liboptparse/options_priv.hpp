/* liboptparse is a library used to handle command line options.
 * Copyright (C) 2020 Guybrush aka Gabriele Labita
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

/*!
 * \file      options_priv.hh
 * \brief     This file contains the definition of the template
 *            part of options.hh
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of the template part of
 * options.hh and Impl class. Implementation class is defined here
 * beacuse its constructor is a template, so it must be include
 * at template instantion time.
 * Don't use this file directly! Use options.hh instead.
 */


#ifndef OPTIONS_PRIV_INCLUDE_GUARD_HH
#define OPTIONS_PRIV_INCLUDE_GUARD_HH 1

class Options::Impl {
public:
    template<class OptsForwardIterator, class ArgsForwardIterator>
    Impl (
        const ProgramInfo&  program_info,
        OptsForwardIterator opts_begin,
        OptsForwardIterator opts_end,
        ArgsForwardIterator args_begin,
        ArgsForwardIterator args_end)
        : _args(new Options::arguments_container(args_begin, args_end)),
          _program_info(new ProgramInfo(program_info)),
          _opts(new Options::options_container(opts_begin, opts_end)) { };
    
    template<class OptsForwardIterator>
    Impl(
        const ProgramInfo&  program_info,
        OptsForwardIterator opts_begin,
        OptsForwardIterator opts_end)
        : _args(new Options::arguments_container()),
          _program_info(new ProgramInfo(program_info)),
          _opts(new Options::options_container(opts_begin, opts_end)) { };

    bool OK() const noexcept;

    bool contains_option(char key) const noexcept;
    Options::value_type at(char key) const noexcept;

    Options::options_const_iterator options_cbegin() const noexcept;
    
    Options::options_const_iterator options_cend() const noexcept;

    Options::arguments_const_iterator arguments_cbegin() const noexcept;

    Options::arguments_const_iterator arguments_cend() const noexcept;

    const std::string& get_program_name() const noexcept;
private:
    std::unique_ptr<arguments_container> _args;
    std::shared_ptr<ProgramInfo>    _program_info;
    std::unique_ptr<options_container> _opts;
};


template<class OptsForwardIterator, class ArgsForwardIterator>
Options::Options (
    const ProgramInfo&  program_info,
    OptsForwardIterator opts_begin,
    OptsForwardIterator opts_end,
    ArgsForwardIterator args_begin,
    ArgsForwardIterator args_end)
    : _pimpl(new Impl(program_info,
                      opts_begin,
                      opts_end,
                      args_begin,
                      args_end)) { }

template<class OptsForwardIterator>
Options::Options(
    const ProgramInfo&  program_info,
    OptsForwardIterator opts_begin,
    OptsForwardIterator opts_end)
             : _pimpl(new Impl(program_info,
                               opts_begin,
                               opts_end)) { }

#endif
