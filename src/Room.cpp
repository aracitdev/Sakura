#include "Room.h"

namespace Sakura
{

const std::map<std::string,std::any> defaultMapData =
{
    {"x", std::make_any<int32_t>(0)},
    {"y", std::make_any<int32_t>(0)},
    {"width", std::make_any<int32_t>(320)},
    {"height", std::make_any<int32_t>(180)},
    {"name", std::make_any<std::string>("lvl_1")},
    {"c", std::make_any<int32_t>(0)},
    {"musicLayer1", std::make_any<bool>(true)},
    {"musicLayer2", std::make_any<bool>(true)},
    {"musicLayer3", std::make_any<bool>(true)},
    {"musicLayer4", std::make_any<bool>(true)},
    {"delayAltMusicFade",std::make_any<bool>(false)},
    {"dark", std::make_any<bool>(false)},
    {"space", std::make_any<bool>(false)},
    {"underwater", std::make_any<bool>(false)},
    {"whisper", std::make_any<bool>(false)},
    {"music", std::make_any<std::string>("music_oldsite_awake")},
    {"altMusic", std::make_any<std::string>()},
    {"disableDownTransition", std::make_any<bool>(false)},
    {"windPattern",std::make_any<std::string>("None")},
    {"cameraOffsetX", std::make_any<float>(0.0)},
    {"cameraOffsetY", std::make_any<float>(0.0)},
    {"musicProgress",std::make_any<std::string>()},
    {"ambienceProgress",std::make_any<std::string>()}
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
    defs["width"]=std::make_any<int32_t>(w);
    defs["height"]=std::make_any<int32_t>(h);
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
    levelElement->children.push_back(new Element("fgtiles", std::map<std::string,std::any>( {{"tilset",std::make_any<std::string>("Scenery")},{"exportMode",std::make_any<int32_t>(0)}}) ));
    levelElement->children.push_back(new Element("bgtiles", std::map<std::string,std::any>( {{"tilset",std::make_any<std::string>("Scenery")},{"exportMode",std::make_any<int32_t>(0)}}) ));
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
    Resize(std::any_cast<int32_t>(defs["width"]), std::any_cast<int32_t>(defs["height"]));
    return true;
}

}
