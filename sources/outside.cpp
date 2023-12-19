#include "outside.h"
#include "viewManager.h"

outside::outside(const position &p):groundElement{p}{}



void outside::display(const viewManager& view) const
{
    //APPELER LAFFICHEUR PASSE EN PARAM
    view.displayOutside(*this);
}