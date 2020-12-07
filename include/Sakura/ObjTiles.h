/**
  * @file ObjTiles.h
  * Defines a class for dealing with room object tiles.
  */

#ifndef OBJTILES_H_INCLUDED
#define OBJTILES_H_INCLUDED
#include "Element.h"
#include "vector2.h"
#include <string>

namespace Sakura
{

/**
  * Holds a collection of object tiles.
  * Very similar to the Tiles class, except holds integers rather than characters.
  * Generates/loads comma separated values.
  */

class ObjTiles
{
public:

/**
  * Default constructor.
  * Constructs size to zero.
  */
    ObjTiles();

/**
  * @param csv The comma separated string to load from.
  * Constructs it from a CSV string.
  */
    ObjTiles(const std::string& csv);

/**
  * @param e The element to load form.
  * Loads a group of object tiles from the element's innnerText.
  */
    ObjTiles(Element* e);

/**
  * @param e The element to load from
  * @return True on success, false on failure.
  * Loads a group of object tiles from the element's innerText.
  * Check the LoadFromString for the format of the text.
  * Object tiles are resized to fit.
  */
    bool LoadFromElement(Element* e);

/**
  * @param data A comma separated set of tiles to load form.
  * @return true On success, false on failure.
  * Loads a set of tiles from a list of comma separated values.
  * Elements within a row are separated by a comma.
  * A newline character indicates a new row.
  * Object tiles are resized to fit.
  */
    bool LoadFromString(std::string data);

/**
  * Saves the group of tiles to an element's innertext.
  * Creates a string equivalent of the tile set and saves it into the provided element.
  */
    Element* SaveToElement(void);

/**
  * @return The string equivalent of the tile set.
  * Creates a string that's equivalent of the group of object tiles.
  * This is not shortened and is the full tile size.
  */
    std::string SaveToString(void);

/**
  * @return The string equivalent of the tile set.
  * Creates a string that's equivalent of the group of object tiles.
  * Trailing empty (-1) values are cut off the ends of lines.
  * Excess empty rows are cut off.
  */
    std::string CutTilesString(void);

/**
  * @param x The x position to get from.
  * @param y The y position to get from.
  * @return The object tile found.
  * Gets an object tile from the tile group.
  */
    int GetTile(size_t x, size_t y) const;


/**
  * @param pos The position to get from.
  * @return The object tile found.
  * Gets an object tile from the tile group.
  */
    int GetTile(const Vector2<size_t>& pos) const;

/**
  * @param x The x position to set.
  * @param y The y position to set.
  * @param value The value to set it to.
  * Sets an object tile in the tile group.
  */
    void SetTile(size_t x, size_t y, int value);


/**
  * @param pos The position to set.
  * @param value The value to set it to.
  * Sets an object tile in the tile group.
  */
    void SetTile(const Vector2<size_t>& pos, int value);

/**
  * @return The size of the tile group.
  */
    Vector2<size_t> GetSize(void) const;

/**
  * @param newX The new size x
  * @param newY The new size y
  * Resizes the tile group to fit the given size.
  * Cuts off excess tiles, and fills new tiles with -1.
  */
    void Resize(size_t newX, size_t newY);


/**
  * @param newSz The new size.
  * Resizes the tile group to fit the given size.
  * Cuts off excess tiles, and fills new tiles with -1.
  */
    void Resize(const Vector2<size_t>& newSz);
private:
    std::vector<std::vector<int>> mapData;
    Vector2<size_t> size;
};

}
#endif // OBJTILES_H_INCLUDED
