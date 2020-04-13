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

/*!
 * \file      options.hh
 * \brief     File containing Option definition.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of the class used to represent
 * the options of the cli in a high level way.
 */

#include "optargs.hh"
#include "program_info.hh"
#include <list>
#include <map>
#include <memory>

#ifndef LIBOTPPARSE_OPTIONS_INCLUDE_GUARD_HH
#define LIBOTPPARSE_OPTIONS_INCLUDE_GUARD_HH 1

/*!
 * This is the object used to take trace of the pair key value of
 * the parsed options.
 * DEF := Options object is a VALID OPTIONS if its options and
 *        arguments pointer to the containers are not null,  each
 *        element inside theme are not null and program_info is not
 *        null and valid.
 */
class Options {

public:
    /*!
     * Typedefintiion for main value (value of the map) inside
     * container.
     */
    typedef std::shared_ptr<const OptionArgumentValue> value_type;
    /*! Typedefinition for the container used for options. */
    typedef std::map<char, value_type>     options_container;
    /*! Typedefinition for the container used for plain aguments. */
    typedef std::list<value_type>          arguments_container;
    /*! Typedefinition for option's container. */
    typedef options_container::const_iterator options_const_iterator;
    /*! Typedefinition for argument's container */
    typedef arguments_container::const_iterator arguments_const_iterator;

public:    
    /*!
     * Constructor with 5 parameters. Initialize this object with
     * options and arguments passed as range parameters.
     * \param progrom_info - Program info object used to initialize
     *                       Options object with the information
     *                       contained in it.
     * \param opts_begin   - Iterator to the begin of options set.
     * \param opts_end     - Iterator to the end of options set.
     * \param args_begin   - Iterator to the begin of arguments set.
     * \param args_end     - Iterator to the end of arguments set.
     *
     * \tparam OptsForwardIterator - Forward iterator for options. It
     *                               must contain
     *                               args_container::vlaue_type
     *                               objects.
     * \tparam ArgsForwardIterator - Forward iterator for arguments.
     *                               It must contains value_type
     *                               objects.
     */
    template<class OptsForwardIterator, class ArgsForwardIterator>
    Options(
        const ProgramInfo&  program_info,
        OptsForwardIterator opts_begin,
        OptsForwardIterator opts_end,
        ArgsForwardIterator args_begin,
        ArgsForwardIterator args_end);

    /*!
     * Constructor with 3 parameters. Initialize this object with
     * options passed as range parameters and empty arguments set.
     * \param progrom_info - Program info object used to initialize
     *                       Options object with the information
     *                       contained in it.
     * \param opts_begin   - Iterator to the begin of options set.
     * \param opts_end     - Iterator to the end of options set.
     *
     * \tparam OptsForwardIterator - Forward iterator for options. It
     *                               must contain
     *                               args_container::vlaue_type
     *                               objects.
     */    
    template<class OptsForwardIterator>
    Options(
        const ProgramInfo&  program_info,
        OptsForwardIterator opts_begin,
        OptsForwardIterator opts_end);

    
    /*! Destructor. It destroys the pointer to the dictionary. */
    ~Options();

    /*!
     * Gets the value of the key passed as parameter.
     * \param  key - Key of the options to get. Key must be contained
     *               in this object, use opts_cbegin and opts_cend to
     *               use std algorithm for containment check.
     * \return Value of the option represented by the key.
     *
     * <h3> CONTRACT </h3>
     * \pre  This is a valid object and key passed as parameter must
     *       be contained in this object.
     * \post This is still a valid object and returned pointer is not
     *        NULL
     */
    value_type at(char key) const noexcept;

    /*!
     * operator[] overloading, returns the value paired with the key
     * passed as parameter. This method calls the 'at' method.
     * \param  key - Key of the options to get. Key must be contained
     *               in this object, use opts_cbegin and opts_cend to
     *               use std algorithm for containment check
     * \return Value of the option represented by the key.
     *
     * <h3> CONTRACT </h3>
     * \pre  This is a valid object and key passed as parameter must
     *       be contained in this object.
     * \post This is still a valid object and returned pointer is not
     *        NULL
     */
    value_type operator[](char key) const noexcept;

    /*!
     * Gets a const iterator to the begin of the options collection.
     * \return An iterator pointing to the begin of the options
     *         collection.
     *
     * <h3> CONTRACT </h3>
     * \pre  This must be a valid.
     * \post This is still valid.
     */
    options_const_iterator options_cbegin() const noexcept;

    /*!
     * Gets a const iterator to the next element after the last one
     * of the options collection.
     * \return A const iterator pointing the next element after the
     *         last one option.
     *
     * <h3> CONTRACT </h3>
     * \pre  This must be a valid.
     * \post This is still valid.
     */
    options_const_iterator options_cend() const noexcept;

    /*!
     * Gets a const iterator to the begin of the arguments collection.
     * \return An iterator pointing to the end of the arguments
     *         collection.
     *
     * <h3> CONTRACT </h3>
     * \pre  This must be a valid.
     * \post This is still valid.
     */
    arguments_const_iterator arguments_cbegin() const noexcept;

    /*!
     * Gets a const iterator to the next element after the last one
     * of the arguments collection.
     * \return A const iterator pointing the next element after the
     *         last one argument.
     *
     * <h3> CONTRACT </h3>
     * \pre  This must be a valid.
     * \post This is still valid.
     */
    arguments_const_iterator arguments_cend() const noexcept;

    /*!
     * Gets the name of the program lunched.
     * \return A constant reference to the name of the program
     *
     * <h3> CONTRACT </h3>
     * \pre  This must be a valid.
     * \post This is still valid.
     */
    const std::string& get_program_name() const noexcept;

private:
    /*! Private not implemented. */
    Options();    
    /*! Private not implemented. */
    Options(const Options&);
    /*! Private not implemented. */
    Options(const Options&&);
    Options& operator=(const Options&);

    class Impl;
    std::unique_ptr<Impl> _pimpl;
};

#include "options_priv.hpp"

#endif

