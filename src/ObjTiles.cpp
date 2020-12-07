#include "ObjTiles.h"
#include "StringFuncs.h"
#include <sstream>

namespace Sakura
{

ObjTiles::ObjTiles()
{
}

ObjTiles::ObjTiles(const std::string& in)
{
    LoadFromString(in);
}

ObjTiles::ObjTiles(Element* in)
{
    LoadFromElement(in);
}


bool ObjTiles::LoadFromElement(Element* e)
{
    if(!e || !e->HasAttr("innerText"))
        return false;
    return LoadFromString(e->Attr("innerText",""));
}

bool ObjTiles::LoadFromString(std::string data)
{
    if(data.empty())
        return false;
    StringReplace(data,"\r\n","\n");
    if(data.at(data.size()-1) == '\n')
        data.erase(data.end()-1);

    mapData = SplitStringToIntArray(data, '\n',',');


    size_t maxX=0;
    for(size_t i=0; i < mapData.size(); i++)
        maxX = std::max(maxX, mapData[i].size());
    Resize(maxX, mapData.size());
    return true;
}


void ObjTiles::Resize(size_t newX, size_t newY)
{
    size=Vector2<size_t>(newX, newY);
    mapData.resize(newY);
    for(size_t i=0; i < mapData.size(); i++)
        mapData[i].resize(newX, -1);
}

Element* ObjTiles::SaveToElement(void)
{
    Element* e = new Element("objtiles");
    e->SetInt("exportMode",0);
    e->SetAttr("tileset","Scenery");
    e->SetAttr("innerText",CutTilesString());
    return e;
}

std::string ObjTiles::SaveToString(void)
{
    std::stringstream returnV;
    for(uint32_t countery=0; countery < mapData.size(); countery++)
    {
        for(uint32_t counterx=0; counterx < mapData[countery].size(); counterx++)
        {
            returnV << mapData[countery][counterx];
            if(counterx != mapData[countery].size()-1)
                returnV<<",";
        }
        if(countery != mapData.size()-1)
            returnV<<"\n";
    }
    return returnV.str();
}


std::string ObjTiles::CutTilesString(void)
{
    std::stringstream output;
    for(uint32_t countery=0; countery < size.y; countery++)
    {
        int32_t counterx;
        for(counterx=size.x-1; counterx >= 0; counterx--)
            if(GetTile(counterx,countery) != -1)
            break;

        if(counterx >= 0)   //non empty line?
            for(int32_t i=0; i < counterx+1; i++)
            {
                output << GetTile(counterx,countery);
                if(i != counterx)
                    output<<",";
            }
        if(countery != mapData.size()-1)
            output << '\n';
    }
    std::string returnV=output.str();
    if(returnV.find_first_not_of('\n') == std::string::npos)
        return std::string();
    return returnV;
}

int ObjTiles::GetTile(size_t x, size_t y) const
{
    return mapData[y][x];
}

int ObjTiles::GetTile(const Vector2<size_t>& pos) const
{
    return GetTile(pos.x,pos.y);
}

void ObjTiles::SetTile(size_t x, size_t y, int value)
{
    mapData[y][x]=value;
}

void ObjTiles::SetTile(const Vector2<size_t>& pos, int value)
{
    SetTile(pos.x,pos.y,value);
}

Vector2<size_t> ObjTiles::GetSize(void) const
{
    return size;
}


void ObjTiles::Resize(const Vector2<size_t>& newSz)
{
    Resize(newSz.x, newSz.y);
}

}
