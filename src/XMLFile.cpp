#include "XMLFile.h"
#include <sstream>
#include <algorithm>


namespace Sakura
{

std::string ScrubModuleName(std::string& elementName)
{
    size_t pos = elementName.find_last_of('/');
    if(pos == std::string::npos)
        return std::string();
    std::string returnV= elementName.substr(0, pos+1);  //copy the module name
    elementName.erase(0, pos+1);    //erase it out of the name string
    return returnV;
}

std::string GetModuleName(const std::string& elementName)
{
    size_t pos = elementName.find_last_of('/');
    if(pos == std::string::npos)
        return std::string();
    return elementName.substr(0, pos+1);
}

//kinda a jank way of doing this
//since it's just shoehorning in tinyxml2 (so I don't have to write an XML parser)
//hopefully I get around to replacing this out with a built in parser
tinyxml2::XMLElement* ConstructElement(Element* e, tinyxml2::XMLElement* parent, tinyxml2::XMLDocument& doc)
{
    std::string name = e->name.c_str();
    std::string moduleName = ScrubModuleName(name);
    tinyxml2::XMLElement* returnV = doc.NewElement(e->name.c_str());
    parent->InsertEndChild(returnV);
    for(auto it = e->attributes.begin(); it != e->attributes.end(); it++)
    {
        returnV->SetAttribute(it->first.c_str(), ToString(it->second).c_str());
    }
    if(!moduleName.empty())
        returnV->SetAttribute("__module",moduleName.c_str());   // we need to do this because slash can't be in the tags
    for(size_t i=0; i < e->children.size(); i++)
        ConstructElement(e->children[i],returnV,doc);
    return returnV;
}

bool SaveXML(const std::string& out, Element* e)
{
    tinyxml2::XMLDocument outDoc;
    tinyxml2::XMLElement* baseElement = outDoc.NewElement(e->name.c_str());
    outDoc.InsertEndChild(baseElement);
    for(size_t i=0; i < e->children.size(); i++)
    {
        ConstructElement(e->children[i],baseElement,outDoc);
    }
    return outDoc.SaveFile(out.c_str()) == tinyxml2::XML_SUCCESS;
}


Element* LoadXML(const std::string& filename, const std::string& baseElement)
{
    tinyxml2::XMLDocument doc;
    if(doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
        return nullptr; //failed to load
    tinyxml2::XMLElement* child = doc.FirstChildElement(baseElement.c_str());
    if(child != nullptr)
        return LoadXML(child);
    return nullptr;
}

Element* LoadXML(tinyxml2::XMLElement* element)
{
    Element* returnV;
    if(!element->Name())
        returnV = new Element();
    else
        returnV = new Element(element->Name());

    for(auto attr = element->FirstAttribute(); attr != nullptr; attr = attr->Next())
    {
        if(std::string(attr->Name()) == std::string("__module"))
            returnV->name = attr->Value() + returnV->name;
        else
            returnV->attributes[attr->Name()] = FromString(attr->Value());
    }

    for(auto it = element->FirstChildElement(); it != nullptr; it=it->NextSiblingElement())
    {
        Element* child = LoadXML(it);
        returnV->children.push_back(child);
    }
    return returnV;
}

}
