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

extern const std::map<std::string,std::variant<int32_t,bool,float,std::string>> defaultMapData; /**< The default room defs dictionary */
extern const std::vector<std::string> blacklistedRoomAttributes;

/**
  * A class for a celeste room.
  * Contains all entities, tiles, triggers, in the room.
  */
class Room
{
public:

/**
  * @param e The element to construct from.
  * @brief Constructs a room from an element.
  */
    Room(Element* e);

/**
  * @param sz The size of the room to construct.
  * @brief Constructs a new room and resizes it to the specified size.
  */
    Room(const Vector2<size_t>& sz = Vector2<size_t>(320,184));

    std::vector<Decal> fgdecals;    /**< Foreground decal elements */
    std::vector<Decal> bgdecals;    /**< Background decal elements */

    std::vector<Entity> entities;   /**< A list of entities in the room */
    std::vector<Entity> triggers;   /**< A list of triggers in the room */

/**
  * @param e The element to load from.
  * @return Returns true on success, false on failure.
  * @brief Loads the room from a level element.
  */
    bool LoadFromElement(Element* e);

/**
  * @return A level element representation of the room.
  * @brief Constructs a Celeste compatible level element.
  */
    Element* SaveToElement(void);

/**
  * @param sz The new size.
  * @brief Resizes all the tiles to fit the new size.
  */
    void Resize(const Vector2<size_t> &sz);


/**
  * @param w The new width.
  * @param h The new height.
  * @brief Resizes all the tiles to fit the new size.
  */
    void Resize(size_t w, size_t h);

    Tiles fgTiles;  /**< A group of tiles that make up the foreground*/
    Tiles bgTiles;/**< A group of tiles that make up the background*/
    ObjTiles objTiles; /**< A group of object tiles in the room*/

    int32_t width;
    int32_t height;
    int32_t x;
    int32_t y;
    std::string name;
    std::map<std::string,std::variant<int32_t,bool,float,std::string>> defs;
private:

};

}

#endif // ROOM_H_INCLUDED
