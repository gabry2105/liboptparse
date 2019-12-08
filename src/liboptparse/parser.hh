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
 * \file      parser.hh
 * \brief     Parser used to read command line arguments.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of the components used to parse
 * the command lin arguments.
 */

#include "optargs.hh"
#include "options.hh"
#include "program_info.hh"
#include <list>
#include <string>
#include <memory>

#ifndef LIBOPTPARSE_PARSER_INCLUDE_GUARD_HH
#define LIBOPTPARSE_PARSER_INCLUDE_GUARD_HH 1

/*!
 * This is the parser class used to configure option arguments and
 * parse command line.
 *
 * DEF: OptionParse is a VALID OptionParser if each argument inside it
 *      is valid and has not repetition: all OptionArgument are
 *      different (see operator== overload for OptionArgument). 
 */
class OptionParser {
public:
    /*! Typedefinition of the value of option argument list */
    typedef std::shared_ptr<OptionArgument> value_type;
    /*!
     * Type definition of the container used to store option arguments
     */
    typedef std::list<value_type>           container;
    /*!
     * Typedefinition of the iterator of the container that store
     * option arguments.
     */
    typedef container::const_iterator       const_iterator;

public:
    /*! Default constructor */
    OptionParser();

    explicit OptionParser(const ProgramInfo& program_info);
    
    /*! Default destructor */
    ~OptionParser();

    /*!
     * Add the option argument passed as parameter.
     * \param argument - Argument to add to the parse. It must be a
     *                   VALID Option Argument (see OptionArgument's
     *                   class documentation).
     * \return A reference to the option argument added to configure
     *         it using setter methods to make a chain.
     *
     * <h3> CONTRACT </h3>
     * \pre  Argument added must be valid and not added yet (use
     *       begin and and methods with std algorithm to check
     *       containment)
     * \post Argument returned is valid and equals to the argument
     *       passed as parameter. Parser is still valid.
     */
    OptionArgument& add(const OptionArgument& argument);

    /*!
     * Add an option  argument with short name specified.
     * \param short_name - Short name used to initialize an option
     *                     argument to add. It must be a VALID SHORT
     *                     NAME (see is_valid_short_name utility
     *                     function).
     * \return A reference to the option argument added to configure
     *         it using setter methods to make a chain.
     *
     * <h3> CONTRACT </h3>
     * \pre  Short name passed must be valid and not contained in this
     *       parser (use begin and and methods with std algorithm to
     *       check containment)
     * \post Argument returned is valid with the short name specified
     *       and parser is still valid.
     */
    OptionArgument& add(char short_name);

    /*!
     * Add an option  argument with short and long name specified.
     * \param short_name - Short name used to initialize an option
     *                     argument to add. It must be a VALID SHORT
     *                     NAME (see is_valid_short_name utility
     *                     function).
     * \param long_name -  Long name to assign to the argument added,
     *                     it must be a VALID LONG NAME (see
     *                     is_valid_long_name utility function).
     * \return A reference to the option argument added to configure
     *         it using setter methods to make a chain.
     *
     * <h3> CONTRACT </h3>
     * \pre  Short and long name passed must be valid and not
     *       contained in this parser (use begin and and methods with
     *       std algorithm to check containment)
     * \post Argument returned is valid with the short and long name
     *       specified and. Parser is still valid.
     */
    OptionArgument& add(char short_name, const std::string& long_name);

    /*!
     * Parse the option specified as parameter according to the option
     * arguments added before calling this method.
     *
     * <h3> CONTRACT </h3>
     * \pre  This parser must be valid, argc less than equals size
     *       of argv vector.
     * \post Options are VALID and parser is still valid.
     */
    std::shared_ptr<const Options> parse(int argc,
                                         const char *argv[]);

    /*!
     * Get the const iterator to the begin of the option argument
     * collection.
     * \return Const iterator to the begin of the option argument
     *         collection;
     * <h3> CONTRACT <h3>
     * \pre  This parser must be valid.
     * \post This parser is still valid.
     */
    const_iterator cbegin();

    /*!
     * Get the const iterator to the end of the option argument
     * collection.
     * \return Const iterator to the end of the option argument
     *         collection;
     * <h3> CONTRACT <h3>
     * \pre  This parser must be valid.
     * \post This parser is still valid.
     */
    const_iterator cend();
private:

    /*!
     * Assertion method used to check if this parser is valid or not.
     * \return True if this parser is valid, false otherwise.
     */
    bool OK() const noexcept;

    /*! Private not implemented */
    OptionParser(const OptionParser&)

    /*! Private not implemented */;
    OptionParser(const OptionParser&&);

    /*! Pointer to the option argument list. */
    std::unique_ptr<container>   _option_arguments;

    /*! Pointer to the program informations.  */
    std::shared_ptr<ProgramInfo> _program_info;
};

#endif
