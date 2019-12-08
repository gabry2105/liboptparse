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
 * \file      utils.hh
 * \brief     Utilities functions for liboptparse
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains a set of utilities used in the liboptparse. It
 * is for internal use only, do not include this header in your
 * project file.
 */

#include <string>

#include "optargs.hh"
#include "program_info.hh"

#ifndef LIBOPTARG_UTILS_INCLUDE_GUARD_HH
#define LIBOPTARG_UTILS_INCLUDE_GUARD_HH 1

namespace _LIBOPTPARSE_ {
    /*!
     * Check if the parameter passed is a valid short name.
     *
     * DEF: A name is a VALID SHORT NAME if it is an alphatic char.
     *
     * \param short_name - Name to check.
     * \return True id the parameter passed is a valid short name,
     *         false otherwise.
     */
    bool is_valid_short_name(char short_name);

    /*!
     * Check if parameter passed is a valid long name.
     * DEF: A name is a VALID LONG NAME if it is at least 2 character
     *      length string containing only alphabetic and minus
     *      character. It must begin with an alphabetic char.
     *
     * \param long_name - Name to check.
     * \return True id the parameter passed is a valid long name,
     *         false otherwise.
     */
    bool is_valid_long_name(const std::string& long_name);

    /*!
     * Check if parameter passed is a valid option argument. See
     * OptionArgument's class documentation for definition of VALID
     * OptionArgument.
     * \param option_argument - Argument to check.
     * \return True if the option argument passed is valid, false
     *         otherwise.
     */
    bool is_valid_opt_arg(const OptionArgument& option_argument);

    /*!
     * Check if parameter passed is a valid program_info argument. See
     * ProgramInfo's class documentation for definition of VALID
     * ProgramInfo.
     * \param program_info - Argument to check.
     * \return True if the program_info argument passed is valid,
     *         false otherwise.
     */
    bool is_valid_program_info(const ProgramInfo& program_info);
}

#endif
