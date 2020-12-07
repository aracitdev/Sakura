#include "AnyFuncs.h"
#include <iostream>

namespace Sakura
{

std::string ToString(const std::variant<int32_t,bool,float,std::string>& in)
{
    if(std::holds_alternative<std::string>(in))
        return std::get<std::string>(in);
    if(std::holds_alternative<float>(in))
        return std::to_string(std::get<float>(in));
    if(std::holds_alternative<int32_t>(in))
        return std::to_string(std::get<int32_t>(in));
    if(std::holds_alternative<bool>(in))
        return (std::get<bool>(in)) ? "true" : "false";
    return std::string("invalid");
}

std::variant<int32_t,bool,float,std::string> FromString(const std::string& in)
{
    if(in.empty())
        return in;
    if(in == "true" || in == "false")
        return in == "true";
    if(in.find_first_not_of("0123456789.-") == std::string::npos)
    {
        if(in.find('.') != std::string::npos)   //if we find a '.' its a float
            return (float)std::stof(in);
        else
            return (int32_t)std::stoll(in);
    }
    return in;
}

}
