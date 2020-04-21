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
 * \file      plain_arguments.hh
 * \brief     This file contains the defintion of the plain arguments
 *            object container.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of the plain arguments object
 * container.
 */

#include <list>
#include <memory>

#ifndef LIBOPTOPARSE_PLAIN_ARGUMENTS_INCLUDE_GUARD_HH
#define LIBOPTOPARSE_PLAIN_ARGUMENTS_INCLUDE_GUARD_HH 1

/*!
 * This class represent the plain arguments passed to the CLI. It
 * is used to access theme after parse operations.
 * \tparam ArgumentValueType - Arguments value type.
 */
template<class ArgumentValueType>
class PlainArguments {
public:
    /*!
     * Typedefintion for value type. Constant type is used because
     * plain arguments must be readonly.
     */
    typedef ArgumentValueType value_type;
    /*! Typedefintion for constant iterator. */
    typedef typename std::list<value_type>::const_iterator
    const_iterator;
    
public:
    /*!
     * Constructor without parameters. Initialize plain arguments
     * with an empty collection.
     */
    PlainArguments();

    /*! Default destructor. */
    ~PlainArguments();
    
    /*!
     * Constructor with two parameters. Initialize plain arguments
     * with the ones passed as range parameters through iterators.
     * \param begin - Iterator to the begin of the collection to
     *                initialize arguments with.
     * \param end   - Iterator to the end of the collection to
     *                initialize arguments with.
     * \tparam ForwardIterator - Forward iterator containing values
     *                           of type value_type.
     */
    template<class ForwardIterator>
    PlainArguments(ForwardIterator begin, ForwardIterator end);

    /*!
     * Copy constructor. Initialize this instance as a copy of
     * the one passed as parameter.
     * \param plain_argument - PlainArguments object to copy.
     */
    PlainArguments(const PlainArguments& plain_argument);

    /*!
     * Move constructor.
     * \param plain_arguments - PlainArguments obejct to move.
     */
    PlainArguments(PlainArguments&& plain_arguments);

    /*!
     * Assignment operator overload. Assign each ergument of the
     * plain_arguments passed as parameter to this object.
     * \param plain_arguments - Plain arguments object to assign.
     * \return This object reference to allow assignment chaining.
     */
    PlainArguments& operator=(const PlainArguments& plain_arguments);

    /*!
     * Gets the const iterator at the begin of arguments collection.
     * \return A const iterator pointing to the begin of the arguments
     *         collection.
     */
    const_iterator cbegin() const;

    /*!
     * Gets the const iterator to the next element after the last
     * argument inside the collection.
     * \return A const iterator pointing the the next element after
     *         the last argument inside the argument collection.
     */
    const_iterator cend() const;

private:

    std::unique_ptr<std::list<value_type>> _impl;
};

#include "plain_arguments_priv.hpp"
#endif
