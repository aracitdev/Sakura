#include "StringFuncs.h"
#include <iostream>

namespace Sakura
{

std::vector<std::vector<int>> SplitStringToIntArray(const std::string& subject, char lineDelimeter, char elementDelimter)
{
    std::vector<std::string> lines = SplitString(subject, lineDelimeter);
    std::vector<std::vector<int>> returnV(lines.size());
    for(uint32_t i=0; i < lines.size(); i++)
    {
        std::vector<std::string> ints = SplitString(lines[i], elementDelimter);
        returnV[i].resize(ints.size());
        for(uint32_t j=0; j < ints.size(); j++)
            if(!ints[j].empty())
                returnV[i][j]=std::stoi(ints[j]);
    }
    return returnV;
}
std::vector<std::string> SplitString(const std::string& subject, char delimeter)
{
    std::vector<std::string> returnV(1);
    for(uint32_t i=0; i < subject.size(); i++)
        if(subject[i] == delimeter)
            returnV.push_back(std::string());
        else
            returnV[returnV.size()-1].push_back(subject[i]);
    return returnV;
}

std::vector<std::vector<char>> SplitStringToCharArray(const std::string& subject, char delimeter)
{
    std::vector<std::vector<char>> returnV(1);
    for(uint32_t i=0; i < subject.size(); i++)
        if(subject[i] == delimeter)
            returnV.push_back(std::vector<char>());
        else
            returnV[returnV.size()-1].push_back(subject[i]);
    return returnV;
}


void StringReplace(std::string& subject, const std::string& search, const std::string& replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

}
