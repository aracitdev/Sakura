/**
  * @file BinaryPacker.h
  * Defines functions for saving Elements to a binary file
  */

#ifndef SAKURA_BINARYPACKER_H_INCLUDED
#define SAKURA_BINARYPACKER_H_INCLUDED
#include "Element.h"


/**
  * @namespace Sakura
  */
namespace Sakura
{


/*
 * Contains some functions for saving/loading elements.
 */
namespace BinaryPacker
{

/**
  * @param out The stream to save to
  * @param reverseLookup A string to integer reverse lookup for the string table at the beginning of map files.
  * @param e The element to save
  * Saves an element to a file as binary data. Specifically designed for Celeste map data.
  */
    void Save(std::ostream& out, std::map<std::string, int16_t>& reverseLookup, Element* e);

/**
  * @param in The stream to load from
  * @param lookup An integet to string lookup table for loading strings from integers.
  * @param e The element to load to
  * Loads an element from a file made of binary data. Specifically designed for Celeste map data.
  */
    void Load(std::istream& in, std::vector<std::string>& lookup, Element* e);

/**
  * @param out The stream to save to
  * @param reverseLookup The reverse lookup table for saving strings as integers.
  * @param it The iterator for the current attribute being saved.
  * @param e The element to save from.
  * Saves an attribute from it's iterator (the key value)
  * Uses a byte integer to identify the type of attribute
  * 0:bool 1:uint8_t 2:uint16_t 3:uint32_t 4:float 5:lookup string (integer) 6: string 7: length encoded string
  */
    void SaveAttribute(std::ostream& out, std::map<std::string, int16_t>& reverseLookup, std::map<std::string,std::any>::iterator it, Element* e);

/**
  * @param in The strema to load from.
  * @param lookup The lookup table for loading strings from integers.
  * @param e The element to load to.
  * Uses a byte integer to identify the type of attribute
  * 0:bool 1:uint8_t 2:uint16_t 3:uint32_t 4:float 5:lookup string (integer) 6: string 7: length encoded string
  */
    void LoadAttribute(std::istream& in, std::vector<std::string>& lookup, Element* e);

/**
  * @param it The iterator for the std::any
  * @return The type of the std::any as a celeste identifier.
  * Detects the type of the std::any and gets it as a celeste compatible binary identifier (see LoadAttribute)
  */
    uint8_t GetType(std::map<std::string, std::any>::iterator it);


/**
  * @param filename The file to load from
  * @return The element loaded (or null on failure)
  * Loads an element from a compatible file in the Celeste format.
  */
    Element* Load(const std::string& filename);

/**
  * @param filename The file to save to.
  * @param element The element to save to the file
  * @return Returns true on success, false on failure.
  * Saves an element to a celeste compatible XML file.
  */
    bool Save(const std::string& filename, Element* element);


/**
  * @param element The base element to create a lookup table from.
  & @param lookup The vector to save to.
  * Creates a table of string names from an element.
  * Includes the name of all children elements and attributes the contain.
  */
    void CreateStringLookup(Element* element, std::vector<std::string>& lookup);
};

}
#endif // SAKURA_BINARYPACKER_H_INCLUDED
