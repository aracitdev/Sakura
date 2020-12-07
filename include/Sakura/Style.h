/**
  * @file Style.h
  * Includes styleground loading.
  * Also includes paralax and effect loading.
  */

#ifndef STYLE_H_INCLUDED
#define STYLE_H_INCLUDED
#include <map>
#include <string>
#include <any>
#include "Element.h"

namespace Sakura
{

/**
  * Contains a parallax background.
  * @note This is a bit bare bones right now. It is planned to move some stuff out of the dictionary and into dedicated variables.
  */
class Parallax
{
public:
    Parallax();

    /**
      * @param e The element to construct from.
      * Constructs a new Parallax then calls LoadFromElement.
      */
    Parallax(Element* e);

    /**
      * @param e The element to construct from.
      * @param apply The element to apply from.
      * Constructs a new Parallax then calls LoadFromElement with apply.
      */
    Parallax(Element* e, Element* apply);

    /**
      * @param e The element to load from.
      * Loads from an element, copying it's attributes to defs.
      */
    void LoadFromElement(Element* e);

    /**
      * @param e The element to load from.
      * @param apply The element to apply from.
      * Copies the attributes from apply first.
      * Then loads the attributes from e.
      */
    void LoadFromElement(Element* e, Element* apply);

    /**
      * @return The constructed element.
      * Creates a new element that represents the Parallax.
      * Name of the element is parallax.
      */
    Element* SaveToElement(void);

    std::map<std::string,std::any> defs; /**< Attributes that the parallax background has*/
};


/**
  * A styleground effect.
  */

class Effect
{
public:
    Effect();

/**
  * @param e The element to construct from.
  * Constructs an Effect from an element, calling LoadFromElement.
  */

    Effect(Element* e);

/**
  * @param e The element to construct from.
  * @param apply The element to apply first.
  * Constructs an Effect from an element and apply, calling loadFromElement.
  */
    Effect(Element* e, Element* apply);

/**
  * @param e The element to load from.
  * Loads an effect from an element.
  * Copies the name of the element into name, and the attributes into def.
  */
    void LoadFromElement(Element* e);


/**
  * @param e The element to load from.
  * @param apply The element to apply first.
  * Copies the attributes from apply first.
  * Then copies the attributes from the element e.
  * Copies the name of the element into name
  */
    void LoadFromElement(Element* e, Element* apply);

/**
  * @return The new element.
  * Creates a new element from the effect.
  * It's name is the string name.
  */
    Element* SaveToElement(void);
    void ApplyElement(Element* e);

    std::string name; /**< The type of effect */
    std::map<std::string,std::any> defs;    /**< The attributes of the effect*/
};


/**
  * Stores stylegrounds.
  * Stores foreground and background parallaxes and effects.
  */
class Stylegrounds
{
public:

    /**
      * @param e The element to load from.
      * Loads the stylegrounds from an element.
      * (In celeste this is the Style element)
      */
    void LoadFromElement(Element* e);
    Element* SaveToElement(void);
    void LoadLayerFromElement(std::vector<Effect>& effects, std::vector<Parallax>& parallaxes, Element* e);
    Element* SaveLayerToElement(std::vector<Effect>& effects, std::vector<Parallax>& parallaxes, const std::string& name);
    std::vector<Effect> fgEffects;
    std::vector<Parallax> fgParallaxes;
    std::vector<Effect> bgEffects;
    std::vector<Parallax> bgParallaxes;
};

/**
  * @param filename The file to load from.
  * @param out The dictionary to save to.
  * @return true on success, false on failure.
  * Loads a list of effect definitions from an XML file.
  */
bool LoadEffectsXML(const std::string& filename, std::map<std::string,Effect>& out);

}
#endif // STYLE_H_INCLUDED
