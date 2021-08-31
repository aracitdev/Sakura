/**
 * @file AnyFuncs.h
 * @brief Some helpful functions for dealing with variants
 */

#ifndef ANYFUNCS_H_INCLUDED
#define ANYFUNCS_H_INCLUDED
#include <string>
#include <variant>

/**
  * @namespace Sakura
  */

namespace Sakura
{

/**
 * @tparam T Type to check against
 * @param in Variant to check against
 * @return returns true if the type of in and T are equal
 */
template <class T>
inline bool IsType(const std::variant<int32_t,bool,float,std::string>& in)
{
    return std::holds_alternative<T>(in);
}


/**
 * @param in The variant to convert.
 * @return A string equivalent of in.
 * @brief Converts a variant into a string equivalent.
 */
std::string ToString(const std::variant<int32_t,bool,float,std::string>& in);

/**
 * @param in The string to convert
 * @return An string equivalent to in.
 * @brief Converts a string into an std::any equivalent
 */
std::variant<int32_t,bool,float,std::string> FromString(const std::string& in);


}
#endif // ANYFUNCS_H_INCLUDED
