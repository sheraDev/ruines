#include "adventurer.h"
#include "viewManager.h"
#include "attackManager.h"

adventurer::adventurer(const position &pos,int pf,int pv,double swordSolidity,double armorySolidity,bool hasAmulet,bool isOut, int bourse):character{pos,pf,pv},d_sword{swordSolidity},d_armor{armorySolidity},d_hasAmulet{hasAmulet},d_isOut{isOut},d_bourse{bourse}{}

bool adventurer::hasAmulet() const
{
    return d_hasAmulet;
}

void adventurer::display(const viewManager& view) const 
{
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

int adventurer::getBourse() const
{
    return d_bourse;
}
        
        
void adventurer::addToBourse(int amount)
{
    d_bourse+=amount;
}
void adventurer::removeFromBourse(int amount)
{
    d_bourse-=amount;
}

    
void adventurer::setBourse(int val)
{
    d_bourse = val;
}
void adventurer::addToArmorSolidity(double f)
{
    d_armor.addToSolidity(f);
}
       
       
void adventurer::addToSwordSolidity(double f)
{
    d_sword.addToSolidity(f);
}