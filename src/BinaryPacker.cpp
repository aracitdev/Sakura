#include "BinaryPacker.h"
#include "FileFunctions.h"
#include <iostream>
#include <filesystem>

namespace Sakura
{
namespace BinaryPacker
{

uint8_t GetType(std::map<std::string, std::variant<int32_t,bool,float,std::string>>::iterator it)
{
    if(std::holds_alternative<std::string>(it->second))    //horible way of doing this, fix
    {
        if(it->first == "innerText")
        {
            return 7;
        }
        else
            return 5;
    }
    if(std::holds_alternative<bool>(it->second))
        return 0;
    if(std::holds_alternative<float>(it->second))
        return 4;
    if(!std::holds_alternative<int32_t>(it->second))
        return 8;   //should throw an error
    int32_t v = std::get<int32_t>(it->second);
    if(v >= std::numeric_limits<uint8_t>::min() && v <= std::numeric_limits<uint8_t>::max())
        return 1;
    if(v >= std::numeric_limits<int16_t>::min() && v <= std::numeric_limits<int16_t>::max())
        return 2;
    return 3;
}



Element* Load(const std::string& filename)
{
    std::vector<std::string> stringLookup;
    std::ifstream in(filename.c_str(), std::ifstream::binary);
    if(!in.is_open())
        return nullptr;

    std::string celesteHeader = ReadString(in);
    std::string package = ReadString(in);
    stringLookup.resize(Read<int16_t>(in));
    for(uint16_t i=0; i < stringLookup.size(); i++)
        stringLookup[i]=ReadString(in);

    Element* returnV = new Element();
    Load(in, stringLookup,returnV);
    returnV->package = package;
    return returnV;
}

bool Save(const std::string& filename, Element*element)
{
    std::ofstream out(filename.c_str(), std::ofstream::binary);
    if(!out.is_open())
        return false;

    std::vector<std::string> stringLookup;
    CreateStringLookup(element, stringLookup);
    if(element->package.empty())
    {
        size_t endOfPath = filename.find_last_of("/") + 1;
        if(endOfPath == std::string::npos)
            endOfPath = 0;
        size_t endOfFilename = filename.find_last_of(".");
        if(endOfFilename == std::string::npos)
            element->package = filename.substr(endOfPath);
        else
            element->package = filename.substr(endOfPath, endOfFilename-endOfPath);
    }

    WriteString(out,"CELESTE MAP");
    WriteString(out,element->package);
    Write<int16_t>(out,stringLookup.size());
    for(uint16_t i=0; i < stringLookup.size(); i++)
        WriteString(out,stringLookup[i]);

    std::map<std::string, int16_t> reverseLookup;
    for(uint16_t i=0; i < stringLookup.size(); i++)
        reverseLookup[stringLookup[i]]=i;
    Save(out, reverseLookup,element);
    return true;
}

void CreateStringLookup(Element* element, std::vector<std::string>& lookup)
{
    if(std::find(lookup.begin(),lookup.end(),element->name) == std::end(lookup))
        lookup.push_back(element->name);
    for(auto it=element->attributes.begin(); it != element->attributes.end(); it++)
    {
        if(std::find(lookup.begin(), lookup.end(),it->first) == std::end(lookup))
            lookup.push_back(it->first);
        if(std::holds_alternative<std::string>(it->second) && it->first != "innerText" &&
           std::find(lookup.begin(),lookup.end(),std::get<std::string>(it->second)) == std::end(lookup))
            lookup.push_back(std::get<std::string>(it->second));
    }

    for(size_t i=0; i < element->children.size(); i++)
        CreateStringLookup(element->children[i],lookup);
}



void Save(std::ostream& out, std::map<std::string, int16_t>& reverseLookup, Element* element)
{
    Write<int16_t>(out,reverseLookup[element->name]);
    Write<uint8_t>(out,element->attributes.size());


    for(auto it = element->attributes.begin(); it != element->attributes.end(); it++)
        SaveAttribute(out,reverseLookup, it, element);

    Write<int16_t>(out,element->children.size());
    for(uint16_t i=0; i < element->children.size(); i++)
        Save(out,reverseLookup,element->children[i]);
}

void Load(std::istream& in, std::vector<std::string>& lookup, Element* element)
{
    element->name = lookup[Read<int16_t>(in)];
    uint8_t attributeCount = Read<uint8_t>(in);

    for(uint8_t i=0; i < attributeCount; i++)
        LoadAttribute(in, lookup,element);

    element->children.resize(Read<int16_t>(in));
    for(uint16_t i=0; i < element->children.size(); i++)
    {
        element->children[i]=new Element();
        Load(in,lookup,element->children[i]);
    }
}


void SaveAttribute(std::ostream& out, std::map<std::string, int16_t>& reverseLookup, std::map<std::string,std::variant<int32_t,bool,float,std::string>>::iterator it, Element* element)
{
    Write<int16_t>(out,reverseLookup[it->first]);
    uint8_t type = GetType(it);
    Write<uint8_t>(out,type);
    switch(type)
    {
    case 0:
        Write<uint8_t>(out,std::get<bool>(it->second));
        break;
    case 1:
        Write<uint8_t>(out,std::get<int32_t>(it->second));
        break;
    case 2:
        Write<int16_t>(out,std::get<int32_t>(it->second));
        break;
    case 3:
        Write<int32_t>(out,std::get<int32_t>(it->second));
        break;
    case 4:
        Write<float>(out,std::get<float>(it->second));
        break;
    case 5:
        Write<int16_t>(out, reverseLookup[std::get<std::string>(it->second)]);
        break;
    case 6:
        WriteString(out,std::get<std::string>(it->second));
        break;
    case  7:
        {
            std::string str = std::get<std::string>(it->second);
            std::string bout;
            for (size_t i = 0; i < str.size(); i++)
            {
                uint8_t b = 1;
                char c = str[i];
                while (i + 1 < str.size() && str[i + 1] == c && b < 255)
                {
                    b += 1;
                    i++;
                }
                bout.push_back(b);
                bout.push_back(c);
            }

            Write<int16_t>(out, bout.size());
            for(uint32_t counter=0; counter < bout.size(); counter++)
                Write<uint8_t>(out,bout[counter]);
        }
        break;

    default:
        throw std::runtime_error("ERROR: Invalid data type");
        break;
    }
}

void LoadAttribute(std::istream& in, std::vector<std::string>& lookup, Element* element)
{
    int16_t v = Read<int16_t>(in);
    std::string key = lookup[v];
    uint8_t type = Read<uint8_t>(in);

    switch(type)
    {
    case 0:
        element->attributes[key]=(bool)(Read<uint8_t>(in));
        break;
    case 1:
        element->attributes[key]=(int32_t)(Read<uint8_t>(in));
        break;
    case 2:
        element->attributes[key]=(int32_t)(Read<int16_t>(in));
        break;
    case 3:
        element->attributes[key]=(int32_t)(Read<int32_t>(in));
        break;
    case 4:
        element->attributes[key]=(float)(Read<float>(in));
        break;
    case 5:
        element->attributes[key]=(std::string)(lookup[Read<int16_t>(in)]);
        break;
    case 6:
        element->attributes[key]=(ReadString(in));
        break;
    case 7:
        {
            std::vector<uint8_t> bytes = ReadBytes(in, Read<int16_t>(in));
            std::string v;
            for (size_t i = 0; i < bytes.size(); i += 2)
            {
                v.append((int)bytes[i],(char)bytes[i + 1]);
            }
            element->attributes[key]=v;
        }
        break;
    default:
        throw std::runtime_error("ERORR: Invalid data type");
        break;
    }
}

}
}
