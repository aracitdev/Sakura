#include "Style.h"
#include "XMLFile.h"
#include <iostream>

namespace Sakura
{

    Parallax::Parallax(){}
    Parallax::Parallax(Element* e)
    {
        LoadFromElement(e);
    }

    Parallax::Parallax(Element* e, Element* apply)
    {
        LoadFromElement(e,apply);
    }

    void Parallax::LoadFromElement(Element* e)
    {
        defs = e->attributes;
    }

    void Parallax::LoadFromElement(Element* e, Element* apply)
    {
        for(auto it = apply->attributes.begin(); it != apply->attributes.end(); it++)
            defs[it->first]=it->second;
        LoadFromElement(e);
    }

    Element* Parallax::SaveToElement(void)
    {
        return new Element("parallax", defs);
    }

    Effect::Effect(){}

    Effect::Effect(Element* e)
    {
        LoadFromElement(e);
    }

    Effect::Effect(Element* e, Element* apply)
    {
        LoadFromElement(e,apply);
    }

    void Effect::LoadFromElement(Element* e)
    {
        name = e->name;
        defs = e->attributes;
    }

    void Effect::LoadFromElement(Element* e, Element* apply)
    {
        for(auto it = apply->attributes.begin(); it != apply->attributes.end(); it++)
            defs[it->first]=it->second;
        LoadFromElement(e);
    }

    Element* Effect::SaveToElement(void)
    {
        return new Element(name, defs);
    }

    void Stylegrounds::LoadLayerFromElement(std::vector<Effect>& effects, std::vector<Parallax>& parallaxes, Element* e)
    {
        std::cout <<"Stype has " <<e->children.size() << " elements.\n";
        for(uint32_t i=0; i < e->children.size(); i++)
        {
            Element* currentChild = e->children[i];
            if(currentChild->name == "parallax")
                parallaxes.push_back(Parallax(currentChild));
            else
            if(currentChild->name == "apply")
            {   //apply applies certain attributes to its children, so expand that
                for(uint32_t j=0; j < currentChild->children.size(); j++)
                    if(currentChild->children[j]->name == "parallax")
                        parallaxes.push_back(Parallax(currentChild->children[j], currentChild));
                    else
                        effects.push_back(Effect(currentChild->children[j],currentChild));
            }
            else
                effects.push_back(Effect(currentChild));

        }
    }

    Element* Stylegrounds::SaveLayerToElement(std::vector<Effect>& effects, std::vector<Parallax>& parallaxes, const std::string& name)
    {
        Element* returnV = new Element(name);
        for(uint32_t i=0; i < parallaxes.size(); i++)
            returnV->children.push_back(parallaxes[i].SaveToElement());
        for(uint32_t i=0; i < effects.size(); i++)
            returnV->children.push_back(effects[i].SaveToElement());
        return returnV;
    }

    void Stylegrounds::LoadFromElement(Element* e)
    {
        LoadLayerFromElement(bgEffects, bgParallaxes, e->FindChildWithName("Backgrounds"));
        LoadLayerFromElement(fgEffects, fgParallaxes, e->FindChildWithName("Foregrounds"));
    }

    Element* Stylegrounds::SaveToElement(void)
    {
        Element* e = new Element("Style");
        e->children.push_back(SaveLayerToElement(bgEffects, bgParallaxes, "Backgrounds"));
        e->children.push_back(SaveLayerToElement(fgEffects, fgParallaxes, "Foregrounds"));
        return e;
    }


    bool LoadEffectsXML(const std::string& filename, std::map<std::string,Effect>& out)
    {
        Element* base = LoadXML(filename, "Style");
        if(base == nullptr)
            return false;
        for(uint32_t i=0; i < base->children.size(); i++)
            out[base->children[i]->name] = Effect(base->children[i]);
        delete base;
        return true;
    }
}
