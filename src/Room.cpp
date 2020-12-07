#include "Room.h"

namespace Sakura
{

const std::map<std::string,std::variant<int32_t,bool,float,std::string>> defaultMapData =
{
    {"x", (int32_t)(0)},
    {"y", (int32_t)(0)},
    {"width", (int32_t)(320)},
    {"height", (int32_t)(180)},
    {"name", "lvl_1"},
    {"c", (int32_t)0},
    {"musicLayer1", true},
    {"musicLayer2", true},
    {"musicLayer3", true},
    {"musicLayer4", true},
    {"delayAltMusicFade",false},
    {"dark", false},
    {"space", false},
    {"underwater", false},
    {"whisper", false},
    {"music", "music_oldsite_awake"},
    {"altMusic", (std::string())},
    {"disableDownTransition", (bool)(false)},
    {"windPattern",(std::string("None"))},
    {"cameraOffsetX", (float)(0.0)},
    {"cameraOffsetY", (float)(0.0)},
    {"musicProgress",(std::string())},
    {"ambienceProgress",(std::string())}
};


Room::Room(Element* e)
{
    LoadFromElement(e);
}

Room::Room(const Vector2<size_t>& sz)
{
    Resize(sz);
}


void Room::Resize(const Vector2<size_t> &sz)
{
    Resize(sz.x, sz.y);
}

void Room::Resize(size_t w, size_t h)
{
    defs["width"]=(int32_t)(w);
    defs["height"]=(int32_t)(h);
    int32_t nw = ceil(w/8);
    int32_t nh = ceil(h/8);
    bgTiles.Resize(nw,nh);
    fgTiles.Resize(nw,nh);
    objTiles.Resize(nw,nh);
}

Element* Room::SaveToElement(void)
{
    Element* levelElement = new Element("level",defs);
    levelElement->children.push_back(fgTiles.SaveToElement("solids"));
    levelElement->children.push_back(bgTiles.SaveToElement("bg"));
    levelElement->children.push_back(objTiles.SaveToElement());
    levelElement->children.push_back(SaveListAsElement(entities,"entities"));
    levelElement->children.push_back(SaveListAsElement(triggers,"triggers"));
    levelElement->children.push_back(SaveListAsElement(fgdecals,"fgdecals"));
    levelElement->children.push_back(SaveListAsElement(bgdecals,"bgdecals"));
    levelElement->children.push_back(new Element("fgtiles", std::map<std::string,std::variant<int32_t,bool,float,std::string>>( {{"tilset","Scenery"},{"exportMode",0}}) ));
    levelElement->children.push_back(new Element("bgtiles", std::map<std::string,std::variant<int32_t,bool,float,std::string>>( {{"tilset","Scenery"},{"exportMode",0}}) ));
    return levelElement;
}

bool Room::LoadFromElement(Element* e)
{
    defs=e->attributes;
    bgTiles.LoadFromElement(e->FindChildWithName("bg"));
    fgTiles.LoadFromElement(e->FindChildWithName("solids"));
    objTiles.LoadFromElement(e->FindChildWithName("objtiles"));

    LoadListFromElement(entities, e->FindChildWithName("entities"));
    LoadListFromElement(triggers, e->FindChildWithName("triggers"));
    LoadListFromElement(fgdecals, e->FindChildWithName("fgdecals"));
    LoadListFromElement(bgdecals, e->FindChildWithName("bgdecals"));
    Resize(std::get<int32_t>(defs["width"]), std::get<int32_t>(defs["height"]));
    return true;
}

}
