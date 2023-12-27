#include "amulet.h"
#include "viewManager.h"
#include <iostream>

amulet::amulet(const position &p):groundElement{p}{}


void amulet::display(const viewManager& view) const
{
    view.displayAmulet(*this);
}
