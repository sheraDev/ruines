#include "monster.h"
#include "viewManager.h"
        
monster::monster(const position &pos) : character{pos} {}

void monster::attack()
{
    //LANCE UNE ATTAQUE : APPELLE LE GESTIONNAIRE D ATTAQUE
}

void monster::receiveAttack()
{
    //RECOIT UNE ATTAQUE : APPELLE LE GESTIONNAIRE D ATTAQUE
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