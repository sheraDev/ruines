#include "adventurer.h"
#include "viewManager.h"

adventurer::adventurer(const position &pos):character{pos}{}

bool adventurer::hasAmulet() const
{
    return d_hasAmulet;
}

void adventurer::attack()
{
    //GESTIONNAIRE D ATTAQUE
}

void adventurer::receiveAttack()
{
    //GESTIONNAIRE D ATTAQUE
}

void adventurer::moveAt(const position &pos)
{
    //GESTIONNAIRE DE DEPLACEMENT
}

void adventurer::display(const viewManager& view) const 
{
    //afficher via l afficheur passé en param
    view.displayAdventurer(*this);
}

void adventurer::setAmuletTrue(bool haveAmulet)
{
    d_hasAmulet = haveAmulet;
}