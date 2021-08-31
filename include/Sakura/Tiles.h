/**
  * @file Tiles.h
  * Includes a class and some functions for dealing with tiles.
  */
#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <string>
#include <vector>
#include "Element.h"
#include "Vector2.h"

/**
  * @namespace Sakura
  */
namespace Sakura
{

/**
  * @brief A class that holds a group of tiles (either fg or bg).
  * Tiles are stored as a multidimentional vector of char.
  */
class Tiles
{
public:
/**
  * @param data The string to construct from.
  * @brief Constructs a set of tiles from string data.
  */
    Tiles(std::string data);

/**
  * @param e The element to construct from.
  * @brief Constructs a set of tiles from an element.
  * Constructs the tiles from the element's innertext string attribute.
  */
    Tiles(Element* e);

/**
  * @brief Constructs an empty set of tiles.
  */
    Tiles();

/**
  * @param e The element to load from.
  * @return True on success, false on failure.
  * @brief Loads a set of tiles from an element.
  * Loads as a string from the element's innerText attribute.
  */
    bool LoadFromElement(Element* e);

/**
  * @param data The string to load from
  * @return True on success, false on failure.
  * @brief Loads a set of tile data from a string.
  * Fits the size to the tile map.
  */
    bool LoadFromString(std::string data);

/**
  * @return The tile data encoded as a string.
  * @brief Encodes the tile data as a string.
  * The string includes all trailing zeros.
  * These zeroes are not necessary when saving (use CutTileString instead)
  */
    std::string ToString(void);

/**
  * @return The tile data encoded as a string.
  * @brief Encodes the tile data as a string.
  * The string is shortened for file loading.
  * Excess zeros are removed.
  */
    std::string CutTileString(void);

/**
  * @param name The name of the element.
  * @brief Saves the tile data to the elements innerText attribute.
  */
    Element* SaveToElement(const std::string& name);


/**
  * @param x The x position.
  * @param y THe y position
  * @return The char at that position.
  * @brief Gets a char representing the tile at the given position.
  */
    char GetTile(size_t x, size_t y) const;

/**
  * @param x The x position
  * @param y the y position
  * @param in The char to set the tile to.
  * @brief Sets a tile in the tile data to the provided char.
  */
    void SetTile(size_t x, size_t y, char in);

/**
  * @param pos The position of the tile (as a vector)
  * @return The tile at the position as a char.
  * @brief Gets a tile from the tiledata at the specified position and returns it as a char.
  */
    char GetTile(const Vector2<size_t> pos) const;

/**
  * @param pos The position of the tile to set (as a vector)
  * @param in The tile type to set it to.
  * @brief Sets the tile at the specified position to the char provided.
  */
    void SetTile(const Vector2<size_t> pos, char in);

/**
  * @return The size of the tile map.
  * @brief Gets the size of the tile set as a vector,
  */
    Vector2<size_t> GetSize(void) const;

/**
  * @param newX The new size of the tile map along the X axis.
  * @param newY The new size of the tile map along the Y axis.
  * @brief Resizes the tile map to fit the specified dimension.
  * Cuts off excess characters (ones that aren't within the new size that were in before).
  * Fills in excess characters with '0' air (ones that weren't within the size but are now)
  */
    void Resize(size_t newX, size_t newY);

/**
  * @param newSz The new size of the tile map.
  * @brief Resizes the tile map to fit the specified dimension.
  * Cuts off excess characters (ones that aren't within the new size that were in before).
  * Fills in excess characters with '0' air (ones that weren't within the size but are now)
  */
    void Resize(const Vector2<size_t>& newSz);
private:
    std::vector<std::vector<char>> mapData;
    Vector2<size_t> size;
};

}
#endif // TILES_H_INCLUDED
