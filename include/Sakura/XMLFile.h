#ifndef XMLFILE_H_INCLUDED
#define XMLFILE_H_INCLUDED
#include <fstream>
#include <tinyxml2.h>
#include "Element.h"
#include "AnyFuncs.h"

//this is ganna hurt

/**
  * @namespace Sakura
  */
namespace Sakura
{

/**
  * @param filename The file stream to save to.
  * @param e The element to save
  * @return Returns true on success, false on failure.
  * Saves an Element to an XML file.
  */
bool SaveXML(const std::string& filename, Element* e);

/**
  * @param filename The filename to load from.
  * @param baseElement the element to attempt to load from as the base.
  * @return The element loaded, null on failure.
  * Loads an Element from an XML file.
  */
Element* LoadXML(const std::string& filename, const std::string& baseElement="Map");

/**
  * @param element The element to load from.
  * @return The element loaded,null on failure.
  * Loads an Element from a tinyxml2 element.
  */
Element* LoadXML(tinyxml2::XMLElement* element);

/**
  * @param elementName The name of the element to clip
  * Cuts out the module name and returns it.
  * This specifically cuts out anything with /
  * Specifically for cutting out mod module names and putting them in an attribute instead.
  */
std::string ScrubModuleName(std::string& elementName);

/**
  * @param elementName The name of the element to search for a module.
  * Gets the name of the module an element belongs to.
  * Specifically returns everything up to the last instance of /
  */
std::string GetModuleName(const std::string& elementName);

}
#endif // XMLFILE_H_INCLUDED
