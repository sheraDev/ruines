#include "door.h"
#include "viewManager.h"

door::door(const position &p):groundElement{p}{}



void door::display(const viewManager& view) const
{
    //APPELER LAFFICHEUR PASSE EN PARAM
    view.displayDoor(*this);
}