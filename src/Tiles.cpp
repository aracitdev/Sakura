#include "Tiles.h"

#include <iostream>
#include "StringFuncs.h"

namespace Sakura
{

Tiles::Tiles(std::string data)
{
    LoadFromString(data);
}

Tiles::Tiles(Element* e)
{
    LoadFromElement(e);
}

Tiles::Tiles()
{
}

bool Tiles::LoadFromElement(Element* e)
{
    if(e == nullptr || !e->HasAttr("innerText"))
        return false;
    return LoadFromString(e->Attr("innerText"));
}

bool Tiles::LoadFromString(std::string data)
{
    if(data.empty())
    {
        return false;
    }
    StringReplace(data,"\r\n","\n");
    if(data.at(data.size()-1) == '\n')
        data.erase(data.end()-1);
    mapData = SplitStringToCharArray(data, '\n');

    size_t maxX=0;
    for(size_t i=0; i < mapData.size(); i++)
        maxX = std::max(maxX, mapData[i].size());
    Resize(maxX, mapData.size());
    return true;
}

std::string Tiles::ToString(void)
{
    std::string output;
    for(uint32_t countery=0; countery < size.y; countery++)
    {
        for(uint32_t counterx=0; counterx < size.x; counterx++)
            output.push_back(mapData[countery][counterx]);
        if(countery != mapData.size()-1)
            output.push_back('\n');
    }
    return output;
}

std::string Tiles::CutTileString(void)
{
    std::string output;
    for(uint32_t countery=0; countery < size.y; countery++)
    {
        int32_t counterx;
        for(counterx=size.x-1; counterx >= 0; counterx--)
            if(GetTile(counterx,countery) != '0')
            break;

        if(counterx >= 0)   //non empty line?
            output.append(&mapData[countery][0],counterx+1);
        if(countery != mapData.size()-1)
            output.push_back('\n');
    }

    size_t lastChar = output.find_last_not_of('\n');
    return output.substr(0, lastChar+1);
}


char Tiles::GetTile(size_t x, size_t y) const
{
    return mapData[y][x];
}

void Tiles::SetTile(size_t x, size_t y, char in)
{
    mapData[y][x]=in;
}


char Tiles::GetTile(const Vector2<size_t> pos) const
{
    return GetTile(pos.x,pos.y);
}

void Tiles::SetTile(const Vector2<size_t> pos, char in)
{
    SetTile(pos.x,pos.y,in);
}

Vector2<size_t> Tiles::GetSize(void) const
{
    return size;
}

void Tiles::Resize(size_t newX, size_t newY)
{
    mapData.resize(newY);
    for(uint32_t i=0; i < mapData.size(); i++)
        mapData[i].resize(newX, '0');
    size=Vector2<size_t>(newX,newY);
}


Element* Tiles::SaveToElement(const std::string& name)
{
    Element* e = new Element(name);
    e->SetAttr("innerText",CutTileString());
    return e;
}


void Tiles::Resize(const Vector2<size_t>& newSz)
{
    Resize(newSz.x,newSz.y);
}


}
