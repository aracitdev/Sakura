/**
  * @file EntityLoader.h
  * Includes some functions for loading entity packs.
  * This is mostly for defining default map entities in the editor.
  */
#ifndef ENTITYLOADER_H_INCLUDED
#define ENTITYLOADER_H_INCLUDED
#include <map>
#include <string>
#include "Entity.h"

/**
  * @namespace Sakura
  */
namespace Sakura
{

/**
  * @param filename The file to read from.
  * @param entities A map of entities to save the  types to.
  * @return Returns true on success, false on failure
  * @brief Loads a list of entity types from an XML file and puts them in a dictionary.
  * Should be used for defining entity types (especially default editor ones).
  */

bool LoadEntityXML(const std::string& filename, std::map<std::string, Entity>& entities);

/**
  * @param filename The file to read from.
  * @param entities A map of entities to save the types to.
  * @return Returns true on success, false on failure.
  * @brief Loads a list of entity types from a binary pack (the same as the celeste format) and puts them in a dictionary.
  * Should be used for defining entity types (especially default editor ones)
  */
bool LoadEntityPack(const std::string& filename, std::map<std::string, Entity>& entities);

/**
  * @param filename The file to write to
  * @param entities A map of entities to save
  * @return Returns true on success, false on failure.
  * @brief Saves a  list of entity types to a binary pack (the same as the celeste format) for later use in an editor.
  * Should be used for saving entity types (especially editor ones)
  */
bool SaveEntityPack(const std::string& filename, std::map<std::string,Entity>& entities);

/**
  * @param filename The file to write to.
  * @param entities A map of entities to save.
  * @return Returns true on success, false on failure.
  * @brief Saves a list of entity types to an XML file for later use in an editor.
  * Should be used for saving entity types (especially editor ones)
  */
bool SaveEntityXML(const std::string& filename, std::map<std::string, Entity>& entities);

}
#endif // ENTITYLOADER_H_INCLUDED
