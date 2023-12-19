#include "groundElement.h"
#include "iostream"

groundElement::groundElement(const position& pos):d_position{pos}{}

void groundElement::changePosition(const position &pos)
{
   
     d_position.setPosition(pos.getLine(),pos.getColumn());


}

position groundElement::getPosition() const
{
    return d_position;
}