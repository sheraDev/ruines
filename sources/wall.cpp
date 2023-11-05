#include "wall.h"
#include "viewManager.h"

wall::wall(const position &p):groundElement{p}{}



void wall::display(const viewManager& view) const
{
    //APPELER LAFFICHEUR PASSE EN PARAM
    view.displayWall(*this);
}