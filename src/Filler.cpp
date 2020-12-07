#include "Filler.h"


namespace Sakura
{
    Filler::Filler(Element* e)
    {
        LoadFromElement(e);
    }

    Filler::Filler()
    {
    }

    void Filler::LoadFromElement(Element* e)
    {
        x=e->AttrInt("x");
        y=e->AttrInt("y");
        w=e->AttrInt("w");
        h=e->AttrInt("h");
    }

    Element* Filler::SaveToElement(void)
    {
        Element* returnV=new Element("rect");
        returnV->SetInt("x", x);
        returnV->SetInt("y", y);
        returnV->SetInt("w", w);
        returnV->SetInt("h", h);
        return returnV;
    }
}
