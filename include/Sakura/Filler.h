#ifndef FILLER_H_INCLUDED
#define FILLER_H_INCLUDED
#include "Element.h"
namespace Sakura
{
    class Filler
    {
    public:
        Filler(Element* e);
        Filler();

        Element* SaveToElement(void);
        void LoadFromElement(Element* e);
        int32_t x,y,w,h;

    };
}

#endif // FILLER_H_INCLUDED
