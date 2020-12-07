#include "Decal.h"

namespace Sakura
{

void Decal::LoadFromElement(Element* e)
{
    texture = e->Attr("texture","");
    x = e->AttrInt("x",0);
    y = e->AttrInt("y",0);
    scaleX = e->AttrInt("scaleX");
    scaleY = e->AttrInt("scaleY");
}

Element* Decal::SaveToElement(void)
{
    Element* returnV = new Element("decal");
    returnV->SetAttr("texture",texture);
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
