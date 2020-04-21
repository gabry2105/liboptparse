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
 * \file      option_arguments.hh
 * \brief     This file contains the definition of the option
 *            arguments.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the defintino of the option arguments, used to
 * represent the options passed to the CLI.
 */

#include <memory>
#include <map>

#ifndef OPTION_ARGUMENTS_INCLUDE_GUARD_HH
#define OPTION_ARGUMENTS_INCLUDE_GUARD_HH 1

/*!
 * This class represent the option arguments collection passed to
 * the CLI.
 * \tparam OptionArgumentKey   - Type used for option's keys.
 * \tparam OptionArgumentValue - Value of the options.
 */
template<class OptionArgumentKey, class OptionArgumentValue>
class OptionArguments {
private:
    typedef std::map<OptionArgumentKey, OptionArgumentValue>
    container;
public:
    /*! Type of the option keys. */
    typedef OptionArgumentKey                 key_type;

    /*! Value type of the options. */
    typedef OptionArgumentValue               value_type;

    /*! Const iterator type of the options container. */
    typedef typename container::const_iterator const_iterator;

public:
    /*!
     * Default constructor. Initialize an empty collection of
     * options.
     */
    OptionArguments();

    /*!
     * Constructor with two parameters. Initialize the option
     * arguments object with the pairs passed as iterator ranges.
     * \param begin - Iterator pointing to the begin of the
     *                collection.
     * \param end   - Iterator pointing to the next element after
     *                the last of the collection.
     */
    template<class ForwardIterator>
    OptionArguments(ForwardIterator begin, ForwardIterator end);

    /*!
     * Copy constrcutor. Initialize the option arguments as a copy
     * of the one passed as parameter.
     * \param option_arguments - Option arguments object to copy. 
     */
    OptionArguments(const OptionArguments& option_arguments);

    /*!
     * Move constructor.
     * \param option_arguments - Option arguments object to move.
     */
    OptionArguments(OptionArguments&& option_arguments);

    /*! Destructor. */
    ~OptionArguments();

    /*!
     * Gets the value identified by the key passed. If the key does
     * not identify any elements undefined behavior.
     * \param key - Key that identify an option inside the
     *              option arguments. If it does not identify any
     *              of theme, undefined behavior. See find member
     *              function.
     * \return Option value identified by the key passed.
     */
    const value_type& at(const OptionArgumentKey& key) const;

    /*!
     * Gets the constant iterator to the begin of option pairs.
     * \return Iterator pointing to the first pair of key value
     *          options.
     */
    const_iterator cbegin() const;
    
    /*!
     * Gets the constant iterator to the end of option pairs.
     * \return Iterator pointing to the next element after the last
     *         pair of key value options.
     */
    const_iterator cend() const;

    /*!
     * Check if the key passed as parameter identify an option
     * inside the collection.
     * \param key - Key to check.
     * \return True if the option identified by the key is inside
     *         the collection, false otherwise.
     */
    bool contains(const OptionArgumentKey& key) const;
    
    /*!
     * operator[] overload. It calls "at" member function.
     * \param key - Key that identify an option inside the
     *              option arguments. If it does not identify any
     *              of theme, undefined behavior. See find member
     *              function.
     * \return Option value identified by the key passed.
     */
    const value_type& operator[](const OptionArgumentKey& key) const;

    /*!
     * operator= overload. Assign the element passed as parameter to
     * this object.
     * \param option_arguments - Option arguments object to assign.
     * \returns A reference to this object to allow assignment
     *          chaining.
     */
    OptionArguments<key_type, value_type>& operator=(
        const OptionArguments<key_type, value_type>&
        option_arguments);

private:
    std::unique_ptr<container> _impl;
};

#include "./option_arguments_priv.hpp"
#endif
