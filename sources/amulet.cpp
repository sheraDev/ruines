#include "amulet.h"
#include "viewManager.h"
#include <iostream>

amulet::amulet(const position &p):groundElement{p}{}




void amulet::display(const viewManager& view) const
{
    //DMD A LAFFICHEUR DE L AFFICHER
    view.displayAmulet(*this);
}
