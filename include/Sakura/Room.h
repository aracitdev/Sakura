/**
  * @file Room.h
  */

#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <vector>

#include "Element.h"
#include "Decal.h"
#include "ObjTiles.h"
#include "Tiles.h"
#include "Entity.h"

namespace Sakura
{

extern const std::map<std::string,std::any> defaultMapData; /**< The default room defs dictionary */


/**
  * A class for a celeste room.
  * Contains all entities, tiles, triggers, in the room.
  */
class Room
{
public:

/**
  * @param e The element to construct from.
  * Constructs a room from an element.
  */
    Room(Element* e);

/**
  * @param sz The size of the room to construct.
  * Constructs a new room and resizes it to the specified size.
  */
    Room(const Vector2<size_t>& sz = Vector2<size_t>(320,184));

    std::vector<Decal> fgdecals;    /**< Foreground decal elements */
    std::vector<Decal> bgdecals;    /**< Background decal elements */

    std::vector<Entity> entities;   /**< A list of entities in the room */
    std::vector<Entity> triggers;   /**< A list of triggers in the room */

/**
  * @param e The element to load from.
  * @return Returns true on success, false on failure.
  * Loads the room from a level element.
  */
    bool LoadFromElement(Element* e);

/**
  * @return A level element representation of the room.
  * Constructs a Celeste compatible level element.
  */
    Element* SaveToElement(void);

/**
  * @param sz The new size.
  * Resizes all the tiles to fit the new size.
  */
    void Resize(const Vector2<size_t> &sz);


/**
  * @param w The new width.
  * @param h The new height.
  * Resizes all the tiles to fit the new size.
  */
    void Resize(size_t w, size_t h);

    Tiles fgTiles;  /**< A group of tiles that make up the foreground*/
    Tiles bgTiles;/**< A group of tiles that make up the background*/
    ObjTiles objTiles; /**< A group of object tiles in the room*/

    std::map<std::string,std::any> defs;
private:

};

}

#endif // ROOM_H_INCLUDED
