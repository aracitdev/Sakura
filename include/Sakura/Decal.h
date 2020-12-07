/**
  * @file Decal.h
  */
#ifndef DECAL_H_INCLUDED
#define DECAL_H_INCLUDED
#include "Element.h"
#include <string>

/**
  * @namespace Sakura
  */
namespace Sakura
{

/**
  * Represents a Celeste decal (either foreground or background).
  * Can be loaded from an Element
  */
class Decal
{
public:

/**
  * Creates an empty decal.
  */
    Decal();

/**
  * @param e The element to load
  * Creates an empty decal and then loads from the element
  */
    Decal(Element* e);

/**
  * @param e
  * Loads a decal from an element.
  * Loads position, texture, and scale.
  */
    void LoadFromElement(Element* e);

/**
  * @return The element constructed from the decal.
  * Creates an element from a decal.
  */
    Element* SaveToElement(void);

    std::string texture;/**< The texture to use for the decal */
    int32_t x;/**< The x position of the decal */
    int32_t y;/**< The y position of the decal */
    int32_t scaleX;/**< Scale of the decal (negative means inversed) */
    int32_t scaleY;/**< Scale of the decal (negative means inversed) */
};

}
#endif // DECAL_H_INCLUDED
