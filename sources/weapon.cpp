#include "weapon.h"

weapon::weapon(double solidite):d_solidity{solidite}{}

double weapon::getSolidity() const
{
    return d_solidity;
}

void weapon::setSolidity(double nouvforce)
{
    d_solidity =  nouvforce;
}
