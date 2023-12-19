#include "groundElement.h"
#include "iostream"

groundElement::groundElement(const position& pos):d_position{pos}{}

void groundElement::changePosition(const position &pos)
{
   // std::cout<<" jv changer ma pos ! (dans grnd elmt)\n";
   // std::cout<<" la nouvelle pos c'est : "<<pos.getLine()<<","<<pos.getColumn()<<"\n";
   // std::cout<<"l'ancienne ct ";
    //std::cout<<d_position.getLine()<<','<<d_position.getColumn()<<"\n";

    d_position.setPosition(pos.getLine(),pos.getColumn());

    //d_position=pos; 
   // d_position.d_line= pos.getLine();
   // d_position.d_column = pos.getColumn();  
   // std::cout<<" c fait !\n"; 
}

position groundElement::getPosition() const
{
    return d_position;
}