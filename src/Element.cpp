#include "Element.h"
#include "FileFunctions.h"
#include "AnyFuncs.h"
#include <algorithm>
#include <iostream>

namespace Sakura
{

Element::Element(const std::string& nm): name(nm)
{
}

Element::Element(const std::string& nm, std::map<std::string,std::any> values): name(nm)
{
    attributes = values;
}

Element::Element(const std::string& nm, std::vector<std::pair<std::string, std::any>> values): name(nm)
{
    for(uint32_t i=0; i < values.size(); i++)
        attributes[values[i].first]=values[i].second;
}

Element::~Element()
{
    for(uint32_t counter=0; counter < children.size(); counter++)
        delete children[counter];
    children.clear();
}

std::string Element::Attr(const std::string& key, std::string def)
{
    if(!attributes.count(key))
        SetAttr(key,def);
    return std::any_cast<std::string>(attributes[key]);
}

bool Element::AttrBool(const std::string& key, bool def)
{
    if(!attributes.count(key))
        SetBool(key,def);
    return std::any_cast<bool>(attributes[key]);
}

float Element::AttrFloat(const std::string& key, float def)
{
    if(!attributes.count(key))
        SetFloat(key,def);
    auto it=attributes.find(key);
    if(IsType<float>(it->second))
        return std::any_cast<float>(it->second);
    if(IsType<int32_t>(it->second))
        return std::any_cast<int32_t>(it->second);
    throw std::runtime_error("Invalid type conversion of std::any in element AttrFloat " + name +" key " +key);
}

int32_t Element::AttrInt(const std::string& key, int32_t def)
{
    if(!attributes.count(key))
        SetInt(key,def);
    auto it=attributes.find(key);
    if(IsType<int32_t>(it->second))
        return std::any_cast<int32_t>(it->second);
    if(IsType<float>(it->second))
        return std::any_cast<float>(it->second);
    throw std::runtime_error("Invalid type conversion of std::any in element AttrInt " + name +" key " +key);
}


void Element::SetAttr(const std::string& key, std::string def)
{
    attributes[key] = std::make_any<std::string>(def);
}

void Element::SetBool(const std::string& key, bool def)
{
    attributes[key] = std::make_any<bool>(def);
}

void Element::SetFloat(const std::string& key, float def)
{
    attributes[key] = std::make_any<float>(def);
}

void Element::SetInt(const std::string& key, int32_t def)
{
    attributes[key] = std::make_any<int32_t>(def);
}

bool Element::HasAttr(const std::string& key)
{
    return attributes.count(key);
}

Element* Element::FindChildWithName(const std::string& name, bool searchSub)
{
    for(uint32_t i=0; i < children.size(); i++)
    {
        if(children[i]->name == name)
            return children[i];
        if(searchSub)
        {
            Element* returnV = children[i]->FindChildWithName(name, searchSub);
            if(returnV != nullptr)
                return returnV;
        }
    }
    return nullptr;
}

Element* Element::FindNextChild(Element* e)
{
    size_t i = InternalSearchChild(e);
    if(i + 1 >= children.size())
        return nullptr;
    return children[i+1];
}

Element* Element::FindNextChildWithName(Element* e, const std::string& name)
{
    //find the current one and start searching the index after
    for(size_t i = InternalSearchChild(e) + 1; i < children.size(); i++)
        if(children[i]->name == name)
        return children[i];
    return nullptr;
}

Element* Element::FindLastChildWithName(Element* current, const std::string& name)
{
    for(int32_t i= ((int32_t)InternalSearchChild(current))-1; i < (int32_t)children.size() && i >= 0; i--)
        if(children[i]->name == name)
        return children[i];
    return nullptr;
}



bool Element::RemoveChild(const std::string& name)
{
    for(int32_t i=children.size()-1; i>=0; i--)
        if(children[i]->name == name)
        {
            delete children[i];
            children.erase(children.begin()+i);
            return true;
        }
    return false;
}

bool Element::RemoveChild(Element* e)
{
    size_t i=InternalSearchChild(e);
    if(i >= children.size())
        return false;
    delete e;
    children.erase(children.begin() + i);
    return true;
}

void Element::ClearChildren(void)
{
    for(uint32_t i=0; i < children.size(); i++)
        if(children[i] != nullptr)
        delete children[i];
    children.clear();
}

bool Element::ReplaceChild(Element* toReplace, Element* newElement)
{
    size_t i=InternalSearchChild(toReplace);
    if(i >= children.size())
        return false;
    delete toReplace;
    children[i]=newElement;
    return true;
}


size_t Element::InternalSearchChild(Element* toSearch)
{
    for(size_t i=0; i < children.size(); i++)   //find the element
        if(children[i] == toSearch)
        return i;
    return children.size();
}


void LoadBlacklistedElements(std::map<std::string, std::any>& out, const std::vector<std::string>& blacklist, Element* e)
{
    for(auto it = e->attributes.begin(); it != e->attributes.end(); it++)
        if(it->first.find("__") != 0 && std::find(blacklist.begin(),blacklist.end(), it->first) == std::end(blacklist))   //ignore special tags and blacklists
            out[it->first] = it->second;
}

}
