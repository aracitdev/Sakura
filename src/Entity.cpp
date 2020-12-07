#include "Entity.h"
#include "Element.h"
#include <algorithm>

namespace Sakura
{

const std::vector<std::string> blacklistedEntityAttributes={"x","y","id"};

Entity::Entity(const std::string& nm) : name(nm), useNodes(false)
{
    id=-1;
}

Entity::Entity(const std::string& nm, Element* e): name(nm), useNodes(false)
{
    id=-1;
    LoadFromElement(e);
}


Entity::Entity(Element* e)
{
    id=-1;
    name = e->name;
    LoadFromElement(e);
}

void Entity::LoadFromElement(Element* e)
{
    for(size_t i=0; i < e->children.size(); i++)
    {
        Element* currentElement=e->children[i];
        if(currentElement->name == "node")  //we found a node, so this one can use nodes
        {
            useNodes = true;
            if(currentElement->HasAttr("x") && currentElement->HasAttr("y"))    //it contains attributes, so it specifies nodes
                nodes.push_back(std::pair<int32_t,int32_t>(currentElement->AttrInt("x"),currentElement->AttrInt("y")));
        }
    }

    LoadBlacklistedElements(defs, blacklistedEntityAttributes, e);
    //we take these out of std::any because they are used often in editor
    x=e->AttrInt("x",0);
    y=e->AttrInt("y",0);
    id=e->AttrInt("id",-1);
}

Element* Entity::SaveToElement(void)
{
    Element* returnV=new Element(name);
    returnV->attributes = defs;
    returnV->SetInt("x",x);
    returnV->SetInt("y",y);
    if(id >= 0)
        returnV->SetInt("id",id);
    if(useNodes)
    {
        returnV->children.resize(nodes.size());
        for(uint32_t i=0; i < nodes.size(); i++)
        {
            Element* nodeElement=new Element("node");
            nodeElement->SetInt("x",nodes[i].first);
            nodeElement->SetInt("y",nodes[i].second);
            returnV->children[i]=nodeElement;
        }
    }
    return returnV;
}

}
