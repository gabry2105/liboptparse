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
 * \file      plain_arguments_priv.hh
 * \brief     This fil econtains the definition of the template part
 *            of PlainArguments.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of the template part of
 * PlainArguments class.
 * Don't include this file directly!
 */

#ifndef PLAIN_ARGUMENTS_PRIV_INCLUDE_GUARD_HH
#define PLAIN_ARGUMENTS_PRIV_INCLUDE_GUARD_HH 1


template<class T>
PlainArguments<T>::PlainArguments()
    : _impl(new std::list<value_type>()) {}


template<class T>
PlainArguments<T>::PlainArguments(
    const PlainArguments<T>& plain_arguments)
    : PlainArguments(plain_arguments.cbegin(),
                     plain_arguments.cend()) {}

template<class T>
PlainArguments<T>::PlainArguments(
    PlainArguments<T>&& plain_arguments)
    : _impl(std::move(plain_arguments._impl)) {}

template<class T> template<class ForwardIterator>
PlainArguments<T>::PlainArguments(
    ForwardIterator begin, ForwardIterator end)
    : _impl(new std::list<value_type>(begin, end)) {}


template<class T>
PlainArguments<T>::~PlainArguments() {}


template<class T>
PlainArguments<T>& PlainArguments<T>::operator=(
    const PlainArguments<T>& plain_arguments) {
    *_impl = *plain_arguments._impl;
    return *this;
}


template<class T>
typename PlainArguments<T>::const_iterator
PlainArguments<T>::cbegin() const {
    return _impl -> cbegin();
}

template<class T>
typename PlainArguments<T>::const_iterator
PlainArguments<T>::cend() const {
    return _impl -> cend();
}
    
#endif
