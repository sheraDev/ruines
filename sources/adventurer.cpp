#include "adventurer.h"
#include "viewManager.h"
#include "attackManager.h"

adventurer::adventurer(const position &pos,double swordSolidity,double armorySolidity):character{pos},d_sword{swordSolidity},d_armor{armorySolidity}{}

bool adventurer::hasAmulet() const
{
    return d_hasAmulet;
}


/*
void adventurer::move(movementManager &movManager,ground &g)
{
    movManager.move(g);
}*/

void adventurer::display(const viewManager& view) const 
{
    //afficher via l afficheur passé en param
    view.displayAdventurer(*this);
}




void adventurer::setAmuletTrue()
{
    d_hasAmulet = true;
}

sword adventurer::getSword() const
{
    return d_sword;
}

armory adventurer::getArmor() const
{
    return d_armor;
}

/*
bool adventurer::receiveAttack(attackManager &attackManag,double force)
{
    bool mort = attackManag.receiveAttack(this,force);
    return mort;
}
double adventurer::attack(attackManager &attackManag)
{
    double force = attackManag.attack(this);
    return force;
}*/

void adventurer::setSwordSolidity(double sol)
{
    d_sword.setSolidity(sol);
}

void adventurer::setArmorSolidity(double sol)
{
    d_armor.setSolidity(sol);
}

bool adventurer::isOutWithAmulet() const
{
    return d_isOut;
}

void adventurer::setIsOutTrue() 
{
    d_isOut = true;
}
