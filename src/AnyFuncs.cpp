#include "AnyFuncs.h"
#include <iostream>

namespace Sakura
{

std::string ToString(const std::any& in)
{
    if(in.type() == typeid(std::string))
        return std::any_cast<std::string>(in);
    if(in.type() == typeid(float))
        return std::to_string(std::any_cast<float>(in));
    if(in.type() == typeid(int32_t))
        return std::to_string(std::any_cast<int32_t>(in));
    if(in.type() == typeid(bool))
        return std::any_cast<bool>(in) ? "true" : "false";
    return std::string("invalid");
}

std::any FromString(const std::string& in)
{
    if(in.empty())
        return std::make_any<std::string>(in);
    if(in == "true" || in == "false")
        return std::make_any<bool>(in == "true");
    if(in.find_first_not_of("0123456789.-") == std::string::npos)
    {
        if(in.find('.') != std::string::npos)   //if we find a '.' its a float
            return std::make_any<float>(std::stof(in));
        else
        {
            std::any returnV;
            returnV = std::make_any<int32_t>(std::stoll(in));   //this can throw an exception
            return returnV;
        }
    }
    return std::make_any<std::string>(in);
}

}
