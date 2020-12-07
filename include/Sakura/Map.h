/**
  * @file Map.h
  */

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "Room.h"
#include "Filler.h"
#include "Style.h"


namespace Sakura
{


/**
  * Contains all information relating to a Celeste map.
  */

class Map
{
public:

    /**
      * Destructor. Frees memeory for all rooms.
      */
    ~Map();
    Map();

/**
* @param e The element to load from.
* Creates a new map from an element.
* Calls LoadFromElement.
*/
    Map(Element* e);


    /**
      * @param filename The file to save to.
      * @return True on success, false on failure.
      * Saves a map to an XML file.
      */
    bool SaveToXML(const std::string& filename);

    /**
      * @param filename The file to load from.
      * @return True on success, false on failure.
      * Loads the map from an XML file.
      */
    bool LoadFromXML(const std::string& filename);

    /**
      * @param filename The file to Save to.
      * @return True on success, false on failure.
      * Saves the map to a celeste compatible bin file.
      */
    bool SaveToBin(const std::string& filename);

    /**
      * @param filename The file to load from.
      * @return True on success, false on failure.
      * Loads the map from a celeste compatible bin file.
      */
    bool LoadFromBin(const std::string& filename);

    /**
      * @param e The element to load from.
      * Loads the map from an element.
      */
    void LoadFromElement(Element* e);

    /**
      * @return The new element.
      * Constructs a new elemenent representing the map.
      * This element should be structured to save using binarypacker.
      */
    Element* SaveToElement(void);

    /**
      * Clears the map entirely, emptying rooms, filler, and style.
      */
    void Clear(void);

    std::vector<Filler> filler;
    Stylegrounds style;
    std::string package;
    std::vector<Room*> rooms;
private:
};
}
#endif // MAP_H_INCLUDED
