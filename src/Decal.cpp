#include "Decal.h"

namespace Sakura
{

void Decal::LoadFromElement(Element* e)
{
    texture = e->Attr("texture","");

    size_t pngPos = texture.find(".png");
    if(pngPos != std::string::npos)
        texture.erase(pngPos);
    for(uint32_t i=0; i < texture.size(); i++)
        if(texture[i] == '\\')
        texture[i]='/';
    texture = "decals/" + texture;

    x = e->AttrInt("x",0);
    y = e->AttrInt("y",0);
    scaleX = e->AttrInt("scaleX");
    scaleY = e->AttrInt("scaleY");
}

Element* Decal::SaveToElement(void)
{
    Element* returnV = new Element("decal");
    std::string outTexture=texture;
    size_t decalsPos = outTexture.find("decals/");
    if(decalsPos != std::string::npos)
        outTexture.erase(decalsPos, 7);
    outTexture=outTexture+".png";
    returnV->SetAttr("texture",outTexture);
    returnV->SetInt("x",x);
    returnV->SetInt("y",y);
    returnV->SetInt("scaleX",scaleX);
    returnV->SetInt("scaleY",scaleY);
    return returnV;
}


Decal::Decal()
{
}

Decal::Decal(Element* e)
{
    LoadFromElement(e);
}

}
