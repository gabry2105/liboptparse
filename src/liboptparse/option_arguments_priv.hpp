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
 * \file      option_arguments.hpp
 * \brief     This file contains the definition of the template option
 *            arguments class.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of the template option arguments
 * class.
 * Don't include this file explictly.
 */


template <class K, class V>
OptionArguments<K, V>::OptionArguments()
    : _impl(new container()) { }

template <class K, class V> template<class ForwardIterator>
OptionArguments<K, V>::OptionArguments(
    ForwardIterator begin, ForwardIterator end)
    : _impl(new container(begin, end)) { }

template <class K, class V>
OptionArguments<K, V>::OptionArguments(
    const OptionArguments& option_arguments)
    : OptionArguments(option_arguments.cbegin(),
                      option_arguments.cend()) { }


template <class K, class V>
OptionArguments<K, V>::OptionArguments(
    OptionArguments&& option_arguments)
    : _impl(std::move(option_arguments._impl)) { }

template <class K, class V>
OptionArguments<K, V>::~OptionArguments() { }

template <class K, class V>
const typename OptionArguments<K, V>::value_type&
OptionArguments<K, V>::at(const K& key) const {
    return _impl -> at(key);
}

template <class K, class V>
bool OptionArguments<K, V>::contains(const K& key) const {
    return _impl -> find(key) != _impl -> end();
}

template <class K, class V>
typename OptionArguments<K, V>::const_iterator
OptionArguments<K, V>::cbegin() const {
    return _impl -> cbegin();
}

template <class K, class V>
typename OptionArguments<K, V>::const_iterator
OptionArguments<K, V>::cend() const {
    return _impl -> cend();
}

template <class K, class V>
const typename OptionArguments<K, V>::value_type&
OptionArguments<K, V>::operator[](const K& key) const {
    return at(key);
}

template <class K, class V>
OptionArguments<K, V>&
OptionArguments<K, V>::operator=(
    const OptionArguments& option_arguments) {
    *_impl = *option_arguments._impl;
    return *this;
}

