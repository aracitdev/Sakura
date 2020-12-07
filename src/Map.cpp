#include "Map.h"
#include "BinaryPacker.h"
#include "XMLFile.h"
#include <iostream>

namespace Sakura
{

bool Map::SaveToXML(const std::string& filename)
{
    return SaveXML(filename, SaveToElement());
}

bool Map::LoadFromXML(const std::string& filename)
{
    Element* e= LoadXML(filename, "Map");
    if(e == nullptr)
        return false;
    LoadFromElement(e);
    return true;
}

bool Map::SaveToBin(const std::string& filename)
{
    return BinaryPacker::Save(filename, SaveToElement());
}

bool Map::LoadFromBin(const std::string& filename)
{
    Element* e= BinaryPacker::Load(filename);
    if(e == nullptr)
        return false;
    LoadFromElement(e);
    return true;
}


Map::~Map()
{
    Clear();
}

Map::Map()
{
}

Map::Map(Element* e)
{
    LoadFromElement(e);
}

void Map::Clear(void)
{
    for(uint32_t i=0; i <rooms.size(); i++)
        delete rooms[i];
    rooms.clear();
    filler.clear();
    style=Stylegrounds();
}

void Map::LoadFromElement(Element* e)
{
    Clear();
    package = e->package;
    LoadListFromElement(filler,e->FindChildWithName("Filler"));
    LoadListFromElement(rooms,e->FindChildWithName("levels"));

    if(e->FindChildWithName("Style") == nullptr)
        std::cout <<"Failed to find style.\n";
    style.LoadFromElement(e->FindChildWithName("Style"));
}

Element* Map::SaveToElement(void)
{
    Element* returnV = new Element("Map");
    returnV->children.push_back(SaveListAsElement(filler,"Filler"));
    returnV->children.push_back(SaveListAsElement(rooms,"levels"));
    returnV->children.push_back(style.SaveToElement());
    returnV->package = package;
    return returnV;
}

}
