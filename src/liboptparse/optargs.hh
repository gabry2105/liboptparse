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
 * \file      optargs.hh
 * \brief     Data module for opt arguments.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the data strcuture used to represent the
 * option arguments.
 */

#include <string>
#include <memory>

#ifndef LIBOPTARGS_OPTARGS_INCLUDE_GUARD_HH
#define LIBOPTARGS_OPTARGS_INCLUDE_GUARD_HH 1

/*!
 * \brief This represent a value of an option.
 *
 * This class is used to represent a value of an option. It defines
 * all possible convert operators to handle value in a more
 * confortable way.
 */
class OptionArgumentValue {
public:
    /*! Default constructor. */
    OptionArgumentValue();

    /*!
     * Constructor with one parameter. Intialize the value with the
     * one passed as string.
     * \param value - Value to set as string.
     */
    explicit OptionArgumentValue(const std::string& value);

    /*!
     * Copy constructor. Initialize the current value with the same
     * passed.
     */
    OptionArgumentValue(const OptionArgumentValue& option_value);

    /*! Move constructor. */
    OptionArgumentValue(const OptionArgumentValue&& option_value);
    
    /*! Default constructor. */
    ~OptionArgumentValue();

    /*!
     * Convert the value to boolean. To be converted right the value
     * must be equals to "true" or "false" otherwise undefined
     * behavior. Use get_value method to check the inner string.
     */
    operator bool() const;
    
    /*!
     * Convert the value to int. To be converted right the value
     * must be a valid integer otherwise undefined behavior. This
     * method used standard input operator to perform convertion.
     */
    operator int() const;

    /*!
     * Convert the value to a shott. To be converted right the value
     * must be a valid short otherwise undefined behavior. This
     * method used standard input operator to perform convertion.
     */
    operator short() const;

    /*!
     * Convert the value to long. To be converted right the value
     * must be a valid long otherwise undefined behavior. This
     * method used standard input operator to perform convertion.
     */
    operator long() const;

    /*!
     * Convert the value to unsigned short. To be converted right the
     * value must be a valid unsigned short otherwise undefined
     * behavior. This method used standard input operator to perform
     * convertion.
     */
    operator unsigned short() const;

    /*!
     * Convert the value to unsigned long. To be converted right the
     * value must be a valid unsigned long otherwise undefined
     * behavior. This method used standard input operator to perform
     * convertion.
     */
    operator unsigned long() const;

    /*!
     * Convert the value to unsigned int. To be converted right the
     * value must be a valid unsigned int otherwise undefined
     * behavior. This method used standard input operator to perform
     * convertion.
     */
    operator unsigned int() const;

    /*!
     * Convert the value to float. To be converted right the value
     * must be a valid float otherwise undefined behavior. This
     * method used standard input operator to perform convertion.
     */
    operator float() const;

    /*!
     * Convert the value to double. To be converted right the value
     * must be a valid double otherwise undefined behavior. This
     * method used standard input operator to perform convertion.
     */
    operator double() const;

    /*!
     * Convert the value to a std::string. This calls get_value method
     * to return same value.
     */
    operator std::string() const;
    
    /*!
     * This is the getter method used to returns the value passed in
     * the constructor.
     * \return The string value inside the class.
     */
    const std::string& get_value() const noexcept;

    /*!
     * Assignment operator overload. Assging to this object the same
     * value of the one passed as parameter.
     * \param  value - Value to assgin to this object.
     * \return A reference to this object to perform assignment
     *         chaining.
     */
    OptionArgumentValue& operator=(
        const OptionArgumentValue& value) noexcept;

private:

    /*! Value of the argument. */
    std::string _value;
};

/*!
 * Equality operator overload. Checks if the two option value passed
 * are equals or not. Two option values are equals if they have same
 * value (get_value returned value).
 * \param  first  - First object to compare.
 * \param  second - Second object to compare.
 * \return True if two values are equals, false otherwise.
 */
bool operator==(const OptionArgumentValue& first,
                const OptionArgumentValue& second);

/*!
 * Not equals operator overload. Checks if the two option value passed
 * are different or not. Two option values are differents if they are
 * not equals: see operator==
 * \param  first  - First object to compare.
 * \param  second - Second object to compare.
 * \return True if two values are differents, false otherwise.
 */
bool operator!=(const OptionArgumentValue& first,
                const OptionArgumentValue& second);

/*!
 * ostream operator overload. It put the value in the out stream
 * passed as parameter.
 * \param os    - Out stream where put value
 * \param value - Valute to put in the out stream.
 * \return os reference to allow chaining.
 */
std::ostream& operator<<(std::ostream& os,
                         const OptionArgumentValue& value);
/*!
 * This is an enumeration type representing the value type of an
 * argument.
 */
enum OptionArgumentType {
    /*!
     * This type is used for arguments with a value to specify in the
     * right format. See usage documentation.
     */
    value = 0,
    /*!
     * This type is used for arguments representing a simple flag that
     * does not accept any value and can be true or false. See useage
     * documentation to know the right format.
     */
    flag  = 1
};

/*!
 * \brief This class represent a single option argument.
 * DEF: OptionArgment is a VALID OPTION ARGUMENT if:
 *        - has a short name valid.
 *        - if has a long name it is valid.
 */
class OptionArgument {

public:
    /*!
     * Constructor with one parameter. Initialize the option argument
     * with the short name given
     * \param short_name - Short name to give to the option. It must
     *                     be a valid short name.
     *
     * <h3> CONTRACT </h3>
     * \pre  Short name must be a valid short name.
     * \post The option argument is a valid OptionArgument
     */
    explicit OptionArgument(char short_name);

    /*!
     * Constructor with two parameters. Initialize the option argument
     * with the short and long name given.
     * \param short_name - Short name given. It must be a valid short
     *                     name.
     * \param long_name  - Long name to give to the option.
     *
     * <h3> CONTRACT </h3>
     * \pre  short_name must be a valid short name and long_name a
     *       valid long name.
     * \post The option argument is a valid OptionArgument
     */
    explicit OptionArgument(char short_name,
                            const std::string& long_name);

    /*!
     * Copy constructor. Initialize this object as a copy of the
     * one passed.
     * \param option_argument - Option to copy. It must be a valid
     *                          option.
     * <h3> CONTRACT </h3>
     * \pre  option to copy must be a valid option.
     * \post this option is a valid option.
     */
    OptionArgument(const OptionArgument& option_argument);

    /*!
     * Move constructor. It move each field from the instance passed
     * as parameter to this object.
     * \param option_argument - Object to move.
     *
     * <h3> CONTRACT </h3>
     * \pre  option to move must be a valid option.
     * \post this option is a valid option.
     */
    OptionArgument(OptionArgument&& option_argument);
    
    /*! Default destructor. */
    ~OptionArgument();

    /*!
     * Gets the short name.
     * \rerturn A valid short name.
     *
     * <h3> CONTRACT </h3>
     * \pre  This is a valid OptionArgument
     * \post Short name returned is a valid short name.
     */
    char get_short_name() const noexcept;

    /*!
     * Gets the long name.
     * \rerturn A valid long name.
     *
     * <h3> CONTRACT </h3>
     * \pre  This is a valid OptionArgument
     * \post Long name returned is a valid short name.
     */
    const std::string& get_long_name() const noexcept;

    /*!
     * Gest the help message.
     * \return The help message set by set_message method.
     *
     * <h3> CONTRACT </h3>
     * \pre  No preconditions.
     * \post No postconditions.
     */
    const std::string& get_help() const noexcept;

    /*!
     * Set the help message to show when usage to have been reported.
     * \param help - help message to set.
     * \return A reference to this object to make a chain.
     *
     * <h3> CONTRACT </h3>
     * \pre  No preconditions.
     * \post No postconditions.
     */
    OptionArgument& set_help(const std::string& help) noexcept;
    
    /*!
     * Gets the default value.
     * \return The default_value of this option.
     *
     * <h3> CONTRACT </h3>
     * \pre  No preconditions.
     * \post No postconditions.
     */
    const std::string& get_default_value() const noexcept;

    /*!
     * Set the default value for this option. Default option is used
     * after parse when user does not specify the value to use.
     * \return A reference to this object to make a chain.
     *
     * <h3> CONTRACT </h3>
     * \pre  No preconditions.
     * \post No postconditions.
     */
    OptionArgument& set_default_value(
        const std::string& default_value) noexcept;
    
    /*!
     * Gets the metavar value. It is the name to use to represent this
     * option inside the help message.
     * \return The metavar of this option.
     *
     * <h3> CONTRACT </h3>
     * \pre  No preconditions.
     * \post No postconditions.
     */
    const std::string& get_metavar() const noexcept;

    /*!
     * Set the metavar value for this option. Metavar is used to
     * represent this option inside the help message.
     *
     * <h3> CONTRACT </h3>
     * \pre  No preconditions.
     * \post No postconditions.
     */
    OptionArgument& set_metavar(const std::string& metavar) noexcept;

    /*!
     * Gets the type of this option. It is an enumeration used to know
     * what this argument represent: a valued option or a flag.
     * \return The type of this option. Default value is 'value'.
     *
     * <h3> CONTRACT </h3>
     * \pre  No preconditions.
     * \post No postconditions.
     */
    OptionArgumentType get_type() const noexcept;

    /*!
     * Set the type of this option. Type is used to know if this
     * option is a flag or a value container. Default is 'value'.
     * \param value_type - Type to set.
     *
     * <h3> CONTRACT </h3>
     * \pre  No preconditions.
     * \post No postconditions.
     */
    OptionArgument& set_type(OptionArgumentType value_type) noexcept;
private:
    OptionArgument& operator=(const OptionArgument&);
    
    class Impl;
    std::unique_ptr<Impl> _pimpl;
};

/*!
 * Equality operator overload.
 * \param first  - First element to compare.
 * \param second - Second element to compare.
 * \return True if the two arguments passed are equals. Two arguments
 *         are equals if short names are equals.
 */
bool operator==(const OptionArgument& first,
                const OptionArgument& second);

/*!
 * Not equal operator overload.
 * \param first  - First element to compare.
 * \param second - Second element to compare.
 * \return True if the two arguments are not equals, false otherwise.
 */
bool operator!=(const OptionArgument& first,
                const OptionArgument& second);

#endif
