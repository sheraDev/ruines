#include "monster.h"
#include "viewManager.h"
#include <iostream>
#include "attackManager.h"
#include "ground.h"
        
monster::monster(const position &pos,int pf,int pv, double hability) : character{pos,pf,pv},d_hability{hability} {}

bool monster::isAtOneCaseAdv(ground &g)
{
    int lineAdv = g.getAdventurerPosition().getLine();
    int colAdv = g.getAdventurerPosition().getColumn();
    int lineMonster = getPosition().getLine();
    int colMonster = getPosition().getColumn();

    int difLine=std::abs(lineMonster-lineAdv);
    int difCol =std::abs(colMonster-colAdv);
   
    return difLine<=1 && difCol<=1;
}


double monster::getHability() const
{
    return d_hability;
}

void monster::display(const viewManager& view) const
{
    //APPEL LAFFICHEUR QUI LAFFICHE (passer lafficheur en parametre)
    view.displayMonster(*this);
}

/*
double monster::attack(attackManager &attackManag)
{
    double force = attackManag.attack(this);
    return force;
}

bool monster::receiveAttack(attackManager &attackManag,double force)
{
    bool mort = attackManag.receiveAttack(this,force);
    return mort;
}*/