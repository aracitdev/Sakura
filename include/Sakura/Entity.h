/**
  * @file Entity.h
  */

#ifndef SAKURA_ENTITY_H_INCLUDED
#define SAKURA_ENTITY_H_INCLUDED
#include <string>
#include <map>
#include <vector>
#include <variant>


/**
  * @namespace Sakura
  */
namespace Sakura
{

class Element;


    extern const std::vector<std::string> blacklistedEntityAttributes;/**< contains attributes Entity isn't supposed to store in defs.*/


/**
  * A class for string entities and triggers.
  * Also has some functions for storing and saving them to elements.
  */
class Entity
{
public:

/**
  * @param nm The name of the entity to construct
  * Constructs a blank entity, id =-1
  */
    Entity(const std::string& nm="");

/**
  * @param nm The name of the entity to construct
  * @param e The element to construct from
  * Constructs a blank entity and loads from an element.
  */
    Entity(const std::string& nm, Element* e);

/**
  * @param e The element to load from.
  * Constructs an entity from an element.
  */
    Entity(Element* e);

/**
  * @param e The element to load from
  * Loads an element's attributes (and noads if present).
  * Ignores attributes starting with __ and those in the blacklist.
  */
    void LoadFromElement(Element* e);

/**
  * @return A new entity that can be saved as an element.
  * Constructs an element representing the entity.
  * Only saves id if positive.
  */
    Element* SaveToElement(void);


    int32_t x; /**< X position of the entity*/
    int32_t y; /**< Y position of the entity*/

    std::optional<int32_t> width;
    std::optional<int32_t> height;
    std::optional<int32_t> originX;
    std::optional<int32_t> originY;

    int32_t id;/**< Unique id of the entity, used for referencing the entity from triggers/other entities*/
    std::string name; /**<The type of entity*/
    std::map<std::string,std::variant<int32_t,bool,float,std::string>> defs; /**< List of entity attributes*/

    std::vector<std::pair<int32_t,int32_t>> nodes; /**< A list of nodes for entities who use the nodes element. Dash blocks, moving space jam, badeline bosses, ect..*/
    bool useNodes; /**< Whether or not the entity uses nodes. Many entities don't use nodes */
};

}
#endif // SAKURA_ENTITY_H_INCLUDED
