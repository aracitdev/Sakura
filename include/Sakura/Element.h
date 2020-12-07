/**
 * @file Element.h
 * Defines an XML like element.
 */


#ifndef SAKURA_ELEMENT_H_INCLUDED
#define SAKURA_ELEMENT_H_INCLUDED
#include <any>
#include <string>
#include <map>
#include <vector>
#include <fstream>

namespace Sakura
{




/**
 * Element is an XML like element, designed to store XML data.
 * This is specifically designed to work with the Celeste map format.
 * Has attributes and children, attributes stored as std::any
 * Attributes stored as a string : std::any dictionary
 */
class Element
{
public:

/**
  * @param nm The name of the element.
  * Constructs a blank element with name nm.
  */
    Element(const std::string& nm = "");

/**
  * @param nm The name of the element.
  * @param attr A map to copy in to the attributes.
  * Constructs a new element with attributes.
  */
    Element(const std::string& nm, std::map<std::string,std::any> attr);

/**
  * @param nm The name of the element.
  * @param attr A vector of key:value pairs to copy to attributes.
  * Constructs a new element with attributes.
  */
    Element(const std::string& nm, std::vector<std::pair<std::string,std::any>> attr);

/**
  * Destructor.
  * Destroys any child elements, freeing their memory.
  */
    ~Element();

/**
  * @param key The key of the attribute.
  * @param def The default value if the attribute doesn't exist.
  * @return The value of the attribute.
  * Gets the value of an attribute as a string.
  * Constructs the attribute if it doesn't already exist.
  * @warning This can throw an exception as it is casting an std::any
  */
    std::string Attr(const std::string& key, std::string def="");

/**
  * @param key The key of the attribute.
  * @param def The default value if the attribute doesn't exist.
  * @return The value of the attribute.
  * Gets the value of the attribute as a boolean.
  * Constructs the attribute if it doesn't already exist.
  * @warning This can throw an exception as it is casting an std::any
  */
    bool AttrBool(const std::string& key, bool def=false);

/**
  * @param key The key of the attribute.
  * @param def The default value if the attribute doesn't exist.
  * @return The value of the attribute.
  * Gets the value of the attribute as a float.
  * Constructs the attribute if it doesn't already exist.
  * @warning This can throw an exception as it is casting an std::any
  */
    float AttrFloat(const std::string& key, float def=0.0f);


/**
  * @param key The key of the attribute.
  * @param def The default value if the attribute doesn't exist.
  * @return The value of the attribute.
  * Gets the value of the attribute as a int.
  * Constructs the attribute if it doesn't already exist.
  * @warning This can throw an exception as it is casting an std::any
  */
    int32_t AttrInt(const std::string& key, int32_t def=0);

/**
  * @param key The attribute to check for
  * @return Whether or not the attribute exists
  */
    bool HasAttr(const std::string& key);



/**
  * @param key The attribute to set.
  * @param def The type to set it to
  * Sets the value of an attribute to a string.
  */
    void SetAttr(const std::string& key, std::string def);

/**
  * @param key The attribute to set.
  * @param def The type to set it to
  * Sets the value of an attribute to a boolean.
  */
    void SetBool(const std::string& key, bool def);

/**
  * @param key The attribute to set.
  * @param def The type to set it to
  * Sets the value of an attribute to a float.
  */
    void SetFloat(const std::string& key, float def);


/**
  * @param key The attribute to set.
  * @param def The type to set it to
  * Sets the value of an attribute to an int.
  */
    void SetInt(const std::string& key, int32_t def);

/**
  * @param name The element to remove
  * @return True if the element was found/removed, false on failure.
  * Searches children elements and removes the first found.
  */
    bool RemoveChild(const std::string& name);

/**
  * @param e The element to remove
  * @return True if the element was found/removed, false on failure
  * Removes a specific element from the children.
  */
    bool RemoveChild(Element* e);

/**
  * @param name The name of the element to search for.
  * @param searchSub Whether or not children should be search if it's not found.
  * @return Pointer to the element, null if none found.
  */
    Element* FindChildWithName(const std::string& name, bool searchSub=true);

/**
  * @param current The current element.
  * @return The element found, or null if the current was the last child.
  * Searches for the element after the one provided.
  */
    Element* FindNextChild(Element* current);
/**
  * @param current The current element.
  * @return The element found, or null if the current was the first child.
  * Searches for the element before the one provided.
  */
  Element* FindLastChild(Element* current);

/**
  * @param current The current element.
  * @param name The name to look for.
  * @return The element found, or null if one could not be found.
  * Searches for the element after the one provided with the given name.
  */
  Element* FindNextChildWithName(Element* current, const std::string& name);


/**
  * @param current The current element.
  * @param name The name to look for.
  * @return The element found, or null if one could not be found.
  * Searches for the element before the one provided with the given name.
  */
  Element* FindLastChildWithName(Element* current, const std::string& name);

/**
  * Clears all children, freeing their memory.
  */
  void ClearChildren(void);

/**
  * @param toReplace the child to search for and replace
  * @param newElement the child to replace it with
  * @return Returns true if the element was found, false otherwise.
  * Replaces out a child, freeing the old one's memeory.
  * @warning Memory of the newElement will not be freed if this function fails.
  */
  bool ReplaceChild(Element* toReplace, Element* newElement);
    std::map<std::string, std::any> attributes; /**< Contains all attributes stored by the element */
    std::vector<Element*> children; /**< Contains all children stored by the element */
    std::string package;/**< A package name (only used if it's the top element) */
    std::string name;/**< The name of the element (the tag) */

private:
    size_t InternalSearchChild(Element* toSearch);
};


/**
  * @param list the list to load to.
  * @param in The element to load from.
  * Loads a list of classes from an element.
  * Loops through the element's children.
  * Each child is passed to the construtor of type T.
  * T is expected to have a constructor which accepts an Element*.
  */
template <class T>
void LoadListFromElement(std::vector<T>& list, Element* in)
{
    if(!in)
        return;
    for(uint32_t i=0; i < in->children.size(); i++)
        list.push_back(T(in->children[i]));
}

/**
  * @param list the list to load to.
  * @param in The element to load from.
  * Loads a list of classes from an element.
  * Loops through the element's children.
  * Each child is passed to the construtor of type T.
  * T is expected to have a constructor which accepts an Element*.
  * Allocates a new instance of T (using new) for each child element.
  */
template <class T>
void LoadListFromElement(std::vector<T*>& list, Element* in)
{
    if(!in)
        return;
    for(uint32_t i=0; i < in->children.size(); i++)
        list.push_back(new T(in->children[i]));
}


/**
  * @param list The list to load from.
  * @param elementName The name of the element to construct.
  * @return The constructed element.
  * Constructs an element from a list of T.
  * T is expected to have a SaveToElement function.
  * Creates an element with the provided name, then adds children from the list.
  */
template <class T>
Element* SaveListAsElement(std::vector<T>& list, const std::string& elementName)
{
    Element* returnV=new Element(elementName);
    for(uint32_t i=0; i < list.size(); i++)
        returnV->children.push_back(list[i].SaveToElement());
    return returnV;
}


/**
  * @param list The list to load from.
  * @param elementName The name of the element to construct.
  * @return The constructed element.
  * Constructs an element from a list of T.
  * T is expected to have a SaveToElement function.
  * Creates an element with the provided name, then adds children from the list.
  */
template <class T>
Element* SaveListAsElement(std::vector<T*>& list, const std::string& elementName)
{
    Element* returnV=new Element(elementName);
    for(uint32_t i=0; i < list.size(); i++)
        returnV->children.push_back(list[i]->SaveToElement());
    return returnV;
}

/**
  * @param out The map to save to.
  * @param blacklist A list of keys to ignore when copying.
  * @param e The element to load from.
  * Copies attributes from the element to an output map.
  * Ignores attributes with keys that are in the blacklist.
  */

void LoadBlacklistedElements(std::map<std::string, std::any>& out, const std::vector<std::string>& blacklist, Element* e);


}
#endif // SAKURA_ELEMENT_H_INCLUDED
