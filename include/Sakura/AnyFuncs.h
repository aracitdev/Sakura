/**
 * @file AnyFuncs.h
 * @brief Some helpful functions for dealing with std::any
 */

#ifndef ANYFUNCS_H_INCLUDED
#define ANYFUNCS_H_INCLUDED
#include <any>
#include <string>

/**
  * @namespace Sakura
  */

namespace Sakura
{

/**
 * @tparam T Type to check against
 * @param in Any to check against
 * @return returns true if the type of in and T are equal
 */
template <class T>
inline bool IsType(const std::any& in)
{
    return in.type() == typeid(T);
}


/**
 * @param in The std::any to convert.
 * @return A string equivalent of in.
 * Converts an std::any into a string equivalent.
 */
std::string ToString(const std::any& in);

/**
 * @param in The string to convert
 * @return An any equivalent to the string.
 * Converts a string into an std::any equivalent
 */
std::any FromString(const std::string& in);


}
#endif // ANYFUNCS_H_INCLUDED
