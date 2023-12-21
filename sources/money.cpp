#include "money.h"
#include "position.h"
#include "viewManager.h"


money::money(const position &p,int value):groundElement{p},d_value{value}{}

void money::display(const viewManager& view) const
{
    view.displayMoney(*this);
}

int money::getValue() const
{
    return d_value;
}