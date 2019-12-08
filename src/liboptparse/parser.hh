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
#include "program_info.hh"
#include <list>
#include <string>
#include <map>
#include <memory>

#ifndef LIBOPTPARSE_PARSER_INCLUDE_GUARD_HH
#define LIBOPTPARSE_PARSER_INCLUDE_GUARD_HH 1

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
    typedef std::map<char, value_type>     opts_container;
    /*! Typedefinition for the container used for plain aguments. */
    typedef std::list<value_type>          args_container;
    /*! Typedefinition for option's container. */
    typedef opts_container::const_iterator opts_const_iterator;
    /*! Typedefinition for argument's container */
    typedef args_container::const_iterator args_const_iterator;

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
        ArgsForwardIterator args_end)
        : _args(new args_container(args_begin, args_end)),
          _program_info(new ProgramInfo(program_info)),
          _opts(new opts_container(opts_begin, opts_end)) { };

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
        OptsForwardIterator opts_end)
        : _args(new args_container()),
          _program_info(new ProgramInfo(program_info)),
          _opts(new opts_container(opts_begin, opts_end)) { };

    
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
    opts_const_iterator opts_cbegin() const noexcept;

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
    opts_const_iterator opts_cend() const noexcept;

    /*!
     * Gets a const iterator to the begin of the arguments collection.
     * \return An iterator pointing to the end of the arguments
     *         collection.
     *
     * <h3> CONTRACT </h3>
     * \pre  This must be a valid.
     * \post This is still valid.
     */
    args_const_iterator args_cbegin() const noexcept;

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
    args_const_iterator args_cend() const noexcept;

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
    /*! Assertion method used to check if this object is valid. */
    bool OK() const noexcept;
    
    /*! Private not implemented. */
    Options();    
    /*! Private not implemented. */
    Options(const Options&);
    /*! Private not implemented. */
    Options(const Options&&);

    std::unique_ptr<args_container> _args;
    /*! Pointer to the info about the program */
    std::shared_ptr<ProgramInfo>    _program_info;
    /*! Pointer to the dictionary of the options/values to gets. */
    std::unique_ptr<opts_container> _opts;

};

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
