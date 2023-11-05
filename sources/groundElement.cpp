#include "groundElement.h"

groundElement::groundElement(const position& pos):d_position{pos}{}

void groundElement::changePosition(const position &pos)
{
    d_position=pos;
}

position groundElement::getPosition() const
{
    return d_position;
}