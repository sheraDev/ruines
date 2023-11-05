#include "character.h"

character::character(const position &p):groundElement{p}{}



int character::forcePoints() const
{
    return d_forcePoints;
}

int character::lifePoints() const
{
    return d_lifePoints;
}