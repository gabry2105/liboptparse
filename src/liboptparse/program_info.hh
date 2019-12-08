/* <Program name and brief descritpion.>
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
 * \file      program_info.hh
 * \brief     Program info structure used for help and version
 *            message.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the defintion of the structure used to describe
 * the program when version or help to be required.
 */

#include <string>
#include <list>

#ifndef PROGRAM_INFO_INCLUDE_GUARD_HH
#define PROGRAM_INFO_INCLUDE_GUARD_HH 1

/*!
 * This is the data structure containing the informations of the
 * program.
 * DEF := A program info is a VALID ProgramInfo if program_name is not
 *        empty.
 */
struct ProgramInfo {
    /*! Default constructor. */
    ProgramInfo();

    explicit ProgramInfo(const std::string& name);
    explicit ProgramInfo(const std::string& name,
                         const std::string& help);
    explicit ProgramInfo(const std::string& name,
                         const std::string& help,
                         const std::string& version);
    explicit ProgramInfo(const ProgramInfo& program_info);
    
    /*! Default destructor. */
    ~ProgramInfo();

    /*!
     * Message shown when help option is passed as args as
     * follow: program_name --help
     */
    std::string program_help;

    /*! Name of the program.  */
    std::string program_name;

    /*!
     * Version of the program printed when --version options is passed
     * as arguments: program_name --version
     */
    std::string program_version;
};

#endif
