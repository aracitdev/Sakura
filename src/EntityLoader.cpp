#include "EntityLoader.h"
#include "XMLFile.h"
#include "StringFuncs.h"
#include <iostream>

namespace Sakura
{

bool LoadEntityXML(const std::string& filename, std::map<std::string, Entity>& entities)
{
    Element* e = LoadXML(filename, "Entities");
    if(e == nullptr)
        return false;
    for(size_t i=0; i < e->children.size(); i++)
    {
        Element* currentChild = e->children[i];
        Entity* currentEntity = &(entities[currentChild->name]);
        currentEntity->name = currentChild->name;
        if(currentChild->HasAttr("__sub"))
        {
            if(entities.count(currentChild->Attr("__sub")))  //ensure that entities contains an existing entity
                *currentEntity = entities[currentChild->Attr("__sub")];
        }

        std::string module = GetModuleName(currentChild->name);
        currentEntity->LoadFromElement(currentChild);

        if(currentChild->HasAttr("__pseudo"))   //does the entity have pseudonyms?
        {
            std::vector<std::string> types = SplitString(currentChild->Attr("__pseudo"),',');   //split comma separated values
            for(uint32_t i=0; i < types.size(); i++)
                if(!module.empty())
                    entities[module + types[i]]=*currentEntity; //we need to prepend the module onto it
                else
                    entities[types[i]]=*currentEntity;
        }
    }
    delete e;
    return true;
}

}
